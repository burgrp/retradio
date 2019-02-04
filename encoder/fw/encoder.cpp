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
