struct
{
	int position = 0xFF;
	unsigned char flags = 1;
} __attribute__((packed)) data;

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

class Button : public DebouncedGpio
{
  public:
	void init(target::gpio_a::Peripheral *port, int pin)
	{
		DebouncedGpio::init(port, pin);
	}

	virtual void onChange(int state)
	{
		data.flags++;
	}
};

class Encoder : public DebouncedGpio
{
	int dataPin;
  public:
	void init(target::gpio_a::Peripheral *port, int clkPin, int dataPin)
	{
		this->dataPin = dataPin;
		port->MODER.setMODER(dataPin, 0);
		port->PUPDR.setPUPDR(dataPin, 1);

		DebouncedGpio::init(port, clkPin);
	}

	virtual void onChange(int state)
	{
		if (state) {
			if (port->IDR.getIDR(dataPin)) {
				data.position++;
			} else {
				data.position--;
			}
			
		}
	}
};

class Device
{

	iwdg::Driver iwdg;

  public:
	Button button;
	Encoder encoder;

	i2c::hw::BufferedSlave i2c;

	void init(target::i2c::Peripheral *peripheral, int address)
	{
		iwdg.init();
		i2c.init(peripheral, address, NULL, 0, (unsigned char *)&data, sizeof(data));
		button.init(&target::GPIOA, 2);
		encoder.init(&target::GPIOA, 0, 1);
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
