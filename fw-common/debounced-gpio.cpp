class DebouncedGpio
{
	virtual void onChange(int state) = 0;

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
			for (volatile int w = 0; w < 1000; w++)
				;
			target::EXTI.PR.setPR(pin, 1);
			onChange(port->IDR.getIDR(pin));
		}
	}
};
