const int PIN_ADDR1 = 8;
const int PIN_ADDR2 = 9;

const int PIN_SAFEBOOT = 16;

const int PIN_BUTTONS[8] = {23, 24, 25, 2, 3, 4, 6, 5};

const int PIN_SDA = 14;
const int PIN_SCL = 15;

const int KEY_TIMER_MS = 100;

class Device {
public:
  class : public atsamd::i2c::Slave {
  public:
    Device *that;

    struct {
      unsigned char protocol = 2;
      unsigned char buttons = 0;
    } __attribute__((packed)) txData;

    void init(Device *that, int address) {
      this->that = that;

      Slave::init(address, 0, atsamd::i2c::AddressMode::MASK, 0, target::gclk::CLKCTRL::GEN::GCLK0, PIN_SDA, PIN_SCL,
                  target::port::PMUX::PMUXE::C);
    }

    virtual int getTxByte(int index) { return index < sizeof(txData) ? ((unsigned char *)&txData)[index] : 0; }

  } slave;

  class : public genericTimer::Timer {
  public:
    Device *that;

    void init(Device *that) {
      this->that = that;
      start(KEY_TIMER_MS / 10);
    }

    void onTimer() {

      int states = 0;
      for (int button = 0; button < 8; button++) {
        int pin = PIN_BUTTONS[button];
        states |= (!(target::PORT.IN >> pin & 1) & 1) << button;
      }

      that->slave.txData.buttons = states;
      
      start(KEY_TIMER_MS / 10);
    }

  } timer;

  void init() {

    // TC1 for motor PWM

    target::PM.APBCMASK.setTC(1, true);

    target::GCLK.CLKCTRL = target::GCLK.CLKCTRL.bare()
                               .setID(target::gclk::CLKCTRL::ID::TC1_TC2)
                               .setGEN(target::gclk::CLKCTRL::GEN::GCLK0)
                               .setCLKEN(true);

    while (target::GCLK.STATUS.getSYNCBUSY())
      ;

    timer.init(this);

    int address = 0x49 + atsamd::configPin::readConfigPin(PIN_ADDR1) + 3 * atsamd::configPin::readConfigPin(PIN_ADDR2);
    slave.init(this, address);
  }
};

Device device;

void interruptHandlerSERCOM0() { device.slave.interruptHandlerSERCOM(); }

void initApplication() {

  // enable safeboot
  atsamd::safeboot::init(PIN_SAFEBOOT, false);

  // MCU clocked at 8MHz
  target::SYSCTRL.OSC8M.setPRESC(target::sysctrl::OSC8M::PRESC::_1);
  genericTimer::clkHz = 8E6;

  device.init();

  // enable interrupts
  target::NVIC.IPR[target::interrupts::External::SERCOM0 >> 2].setPRI(target::interrupts::External::SERCOM0 & 0x03, 3);
  target::NVIC.ISER.setSETENA(1 << target::interrupts::External::SERCOM0);

  // configure buttons
  for (int button = 0; button < 8; button++) {
    int pin = PIN_BUTTONS[button];
    target::PORT.DIRCLR = 1 << pin;
    target::PORT.PINCFG[pin].setINEN(true).setPULLEN(true);
    target::PORT.OUTSET = 1 << pin;
  }
}
