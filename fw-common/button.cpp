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

	int readFlags()
	{
		int f = flags;
		flags = 0;
		return f;
	}
};
