const int buttonCount = 7;

class Device : public i2c::hw::BufferedSlave, Alert
{

	iwdg::Driver iwdg;

	const int pinButton0 = 0;

	const int pinAddrAB = 3;
	const int pinAddrCD = 4;

	const int pinAlert = 7;
	const int pinScl = 9;
	const int pinSda = 10;

	struct
	{
		unsigned char protocol = 1;
		unsigned char down = 0;
		unsigned char up = 0;
	} __attribute__((packed)) txData;

  public:
	Button buttons[buttonCount];

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

		int address = 0x49 + probeTriStateInput(&target::GPIOA, pinAddrAB) + 3 * probeTriStateInput(&target::GPIOA, pinAddrCD);
		i2c::hw::BufferedSlave::init(&target::I2C1, address, NULL, 0, (unsigned char *)&txData, sizeof(txData));

		for (int b = 0; b < buttonCount; b++) {
			buttons[b].init(&target::GPIOA, pinButton0 + b, this);
		}
	}

	void alert()
	{
		target::GPIOA.BSRR.setBR(pinAlert, 1);
	}

	virtual void onTxStart()
	{
		txData.down = 0;
		txData.up = 0;
		for (int b = 0; b < buttonCount; b++) {
			int flags = buttons[b].readFlags();
			txData.down |= (flags & 1) << b;
			txData.up |= ((flags >> 1) & 1) << b;
		}
		target::GPIOA.BSRR.setBS(pinAlert, 1);
	}

	void handleButtonInterrupt() {
		for (int b = 0; b < buttonCount; b++) {
			buttons[b].handleInterrupt();
		}
	}
};

Device device;

void interruptHandlerI2C1()
{
	device.handleInterrupt();
}

void interruptHandlerEXTI0_1()
{
	device.handleButtonInterrupt();
}

void interruptHandlerEXTI2_3()
{
	device.handleButtonInterrupt();
}

void interruptHandlerEXTI4_15()
{
	device.handleButtonInterrupt();
}

void initApplication()
{
	device.init();

	// EXTI
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI0_1);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI2_3);
	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EXTI4_15);
}
