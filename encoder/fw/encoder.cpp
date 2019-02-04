class DebouncedGpio : public genericTimer::Timer
{
	virtual void onChange(int state) = 0;

	void onTimer()
	{
		onChange(port->IDR.getIDR(pin));
	}

  public:
	int pin;
	target::gpio_a::Peripheral *port;

	void init(target::gpio_a::Peripheral *port, int pin)
	{
		this->pin = pin;
		this->port = port;

		port->MODER.setMODER(pin, 0);
		port->PUPDR.setPUPDR(pin, 1);
		target::EXTI.FTSR.setTR(pin, 1);
		target::EXTI.RTSR.setTR(pin, 1);
		target::EXTI.IMR.setMR(pin, 1);
	}
	void handleInterrupt()
	{
		if (target::EXTI.PR.getPR(pin))
		{
			target::EXTI.PR.setPR(pin, 1);
			start(1);
		}
	}
};

class ButtonListener
{
  public:
	virtual void onButtonChange(bool state) = 0;
};

class Button : public DebouncedGpio
{
	ButtonListener *listener;

  public:
	void init(target::gpio_a::Peripheral *port, int pin, ButtonListener *listener)
	{
		this->listener = listener;
		DebouncedGpio::init(port, pin);
	}

	virtual void onChange(int state)
	{
		listener->onButtonChange(state);
	}
};

class EncoderListener
{
  public:
	virtual void onEncoderChange(int change) = 0;
};

class Encoder : public DebouncedGpio
{
	int dataPin;
	EncoderListener *encoderListener;

  public:
	void init(target::gpio_a::Peripheral *port, int clkPin, int dataPin, EncoderListener *encoderListener)
	{
		this->dataPin = dataPin;
		this->encoderListener = encoderListener;

		port->MODER.setMODER(dataPin, 0);
		port->PUPDR.setPUPDR(dataPin, 1);

		DebouncedGpio::init(port, clkPin);
	}

	virtual void onChange(int state)
	{
		if (state)
		{
			encoderListener->onEncoderChange(port->IDR.getIDR(dataPin) ? -1 : 1);
		}
	}
};

class Device : public ButtonListener, public EncoderListener
{

	iwdg::Driver iwdg;

	struct
	{
		short position = 0;
		unsigned char flags = 0;
	} __attribute__((packed)) data;

  public:
	Button button;
	Encoder encoder;

	i2c::hw::BufferedSlave i2c;

	void init(target::i2c::Peripheral *peripheral, int address)
	{
		iwdg.init();
		i2c.init(peripheral, address, NULL, 0, (unsigned char *)&data, sizeof(data));
		button.init(&target::GPIOA, 2, this);
		encoder.init(&target::GPIOA, 0, 1, this);
	}

	void alert(bool state)
	{
	}

	void onButtonChange(bool state)
	{
		data.flags |= 1 << state;
		alert(true);
	}

	virtual void onEncoderChange(int change)
	{
		data.position += change;
		alert(true);
	}

	virtual void onRxComplete()
	{
		data.flags = 0;
		data.position = 0;
		alert(false);
	}
};

Device device;

void interruptHandlerI2C1()
{
	device.i2c.handleInterrupt();
}

void interruptHandlerEXTI0_1()
{
	device.encoder.handleInterrupt();
}

void interruptHandlerEXTI2_3()
{
	device.button.handleInterrupt();
}

void initApplication()
{

	target::RCC.AHBENR.setIOPAEN(true);

	// I2C peripheral
	target::GPIOA.AFRH.setAFRH(9, 4);
	target::GPIOA.AFRH.setAFRH(10, 4);
	target::GPIOA.MODER.setMODER(9, 2);
	target::GPIOA.MODER.setMODER(10, 2);
	target::RCC.APB1ENR.setC_EN(1, 1);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::I2C1);

	// check address switch
	// const int addrPin = 1;
	// volatile target::gpio_b_f::Peripheral* addrPort = &target::GPIOB;
	// int address;
	// addrPort->MODER.setMODER(addrPin, 0);
	// addrPort->PUPDR.setPUPDR(addrPin, 1);
	// for (volatile int c = 0; c < 1000; c++);
	// if (addrPort->IDR.getIDR(addrPin) == 0) {
	// 	address = 0x70;
	// } else {
	// 	addrPort->PUPDR.setPUPDR(addrPin, 2);
	// 	for (volatile int c = 0; c < 1000; c++);
	// 	if (addrPort->IDR.getIDR(addrPin) == 1) {
	// 		address = 0x71;
	// 	} else {
	// 		address = 0x72;
	// 	}
	// }

	int address = 0x70;
	device.init(&target::I2C1, address);

	// EXTI
	target::SYSCFG.EXTICR1.setEXTI(0, 0);
	target::SYSCFG.EXTICR1.setEXTI(2, 0);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI0_1);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI2_3);
}
