class Encoder : public DebouncedGpio
{
	int pinB;
	int position;
	Alert *alert;

  public:
	void init(target::gpio_a::Peripheral *port, int pinA, int pinB, Alert *alert)
	{
		this->pinB = pinB;
		this->alert = alert;

		port->MODER.setMODER(pinB, 0);
		port->PUPDR.setPUPDR(pinB, 1);

		DebouncedGpio::init(port, pinA);
	}

	virtual void onChange(int state)
	{
		if (state)
		{
			position += port->IDR.getIDR(pinB) ? -1 : 1;
			alert->alert();
		}
	}

	int readPosition()
	{
		int p = position;
		position = 0;
		return p;
	}
};
