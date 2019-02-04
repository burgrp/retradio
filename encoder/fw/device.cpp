class Device : public i2c::hw::BufferedSlave, Alert
{

	iwdg::Driver iwdg;

	const int pinEncClk = 0;
	const int pinEncData = 1;
	const int pinEncButton = 2;

	const int pinAddrAB = 3;
	const int pinAddrCD = 4;

	const int pinAlert = 7;
	const int pinScl = 9;
	const int pinSda = 10;

	struct
	{
		short position = 0;
		unsigned char flags = 0;
	} __attribute__((packed)) data;

  public:
	Button button;
	Encoder encoder;

	int probeTriStateInput(target::gpio_a::Peripheral* port, int pin) {
		port->MODER.setMODER(pin, 0);
		port->PUPDR.setPUPDR(pin, 1);
		for (volatile int w = 0; w < 100; w++);
		if (port->IDR.getIDR(pin) == 0) {
			return 1;
		} else {
			port->PUPDR.setPUPDR(pin, 2);
			for (volatile int w = 0; w < 100; w++);
			if (port->IDR.getIDR(pin) == 1) {
				return 2;
			} else {
				return 0;
			}
		}
	}

	void init()
	{
		target::RCC.AHBENR.setIOPAEN(true);

		iwdg.init();

		// I2C peripheral
		target::GPIOA.BSRR.setBS(pinAlert, 1);
		target::GPIOA.OTYPER.setOT(pinAlert, 1);
		target::GPIOA.MODER.setMODER(pinAlert, 1);
		target::GPIOA.AFRH.setAFRH(pinScl, 4);
		target::GPIOA.AFRH.setAFRH(pinSda, 4);
		target::GPIOA.MODER.setMODER(pinScl, 2);
		target::GPIOA.MODER.setMODER(pinSda, 2);
		target::RCC.APB1ENR.setC_EN(1, 1);
		target::NVIC.ISER.setSETENA(1 << target::interrupts::External::I2C1);

		int address = 0x40 + probeTriStateInput(&target::GPIOA, pinAddrAB) + 3 * probeTriStateInput(&target::GPIOA, pinAddrCD);
		i2c::hw::BufferedSlave::init(&target::I2C1, address, NULL, 0, (unsigned char *)&data, sizeof(data));

		button.init(&target::GPIOA, pinEncButton, this);
		encoder.init(&target::GPIOA, pinEncClk, pinEncData, this);
	}

	void alert()
	{
		target::GPIOA.BSRR.setBR(pinAlert, 1);
	}

	virtual void onTxComplete()
	{
		target::GPIOA.BSRR.setBS(pinAlert, 1);
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
	device.init();

	// EXTI
	target::SYSCFG.EXTICR1.setEXTI(0, 0);
	target::SYSCFG.EXTICR1.setEXTI(2, 0);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI0_1);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI2_3);
}
