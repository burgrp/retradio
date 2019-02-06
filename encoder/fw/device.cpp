class Device : public i2c::hw::BufferedSlave, Alert
{

	iwdg::Driver iwdg;

	const int pinEncA = 0;
	const int pinEncB = 1;
	const int pinEncButton = 2;

	const int pinAddrAB = 3;
	const int pinAddrCD = 4;

	const int pinAlert = 7;
	const int pinScl = 9;
	const int pinSda = 10;

	struct
	{
		unsigned char protocol = 1;
		short position = 0;
		unsigned char flags = 0;
	} __attribute__((packed)) txData;

  public:
	Button button;
	Encoder encoder;

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
		i2c::hw::BufferedSlave::init(&target::I2C1, address, NULL, 0, (unsigned char *)&txData, sizeof(txData));

		button.init(&target::GPIOA, pinEncButton, this);
		encoder.init(&target::GPIOA, pinEncA, pinEncB, this);
	}

	void alert()
	{
		target::GPIOA.BSRR.setBR(pinAlert, 1);
	}

	virtual void onTxStart()
	{
		txData.flags = button.readFlags();
		txData.position = encoder.readPosition();
		target::GPIOA.BSRR.setBS(pinAlert, 1);
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
