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
