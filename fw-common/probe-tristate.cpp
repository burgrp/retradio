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
