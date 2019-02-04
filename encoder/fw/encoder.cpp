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

class Alert
{
  public:
	virtual void alert() = 0;
};

class Button : public DebouncedGpio
{
	Alert *alert;
	int flags;

  public:
	void init(target::gpio_a::Peripheral *port, int pin, Alert *alert)
	{
		this->alert = alert;
		DebouncedGpio::init(port, pin);
	}

	virtual void onChange(int state)
	{
		flags |= 1 << state;
		alert->alert();
	}

	int readFlags() {
		int f = flags;
		flags = 0;
		return f;
	}
};

class Encoder : public DebouncedGpio
{
	int dataPin;
	int position;
	Alert *alert;

  public:
	void init(target::gpio_a::Peripheral *port, int clkPin, int dataPin, Alert *alert)
	{
		this->dataPin = dataPin;
		this->alert = alert;

		port->MODER.setMODER(dataPin, 0);
		port->PUPDR.setPUPDR(dataPin, 1);

		DebouncedGpio::init(port, clkPin);
	}

	virtual void onChange(int state)
	{
		if (state)
		{
			position += port->IDR.getIDR(dataPin) ? -1 : 1;
			alert->alert();
		}
	}

	int readPosition() {
		int p = position;
		position = 0;
		return p;
	}
};

class Device : public i2c::hw::BufferedSlave, Alert
{

	iwdg::Driver iwdg;

	const int alertPin = 7;

	struct
	{
		short position = 0;
		unsigned char flags = 0;
	} __attribute__((packed)) data;

  public:
	Button button;
	Encoder encoder;

	void init(target::i2c::Peripheral *peripheral, int address)
	{
		iwdg.init();
		i2c::hw::BufferedSlave::init(peripheral, address, NULL, 0, (unsigned char *)&data, sizeof(data));
		button.init(&target::GPIOA, 2, this);
		encoder.init(&target::GPIOA, 0, 1, this);
		
	}

	void alert()
	{
	}

	virtual void onTxComplete()
	{
		data.flags = button.readFlags();
		data.position = encoder.readPosition();
	}
};

Device device;

void interruptHandlerI2C1()
{
	device.handleInterrupt();
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
