const int PIN_ADDR1 = 8;
const int PIN_ADDR2 = 9;

const int PIN_SAFEBOOT = 25;

const int PIN_ENC_A = 2;
const int PIN_ENC_B = 4;
const int EXT_INT_ENC_A = 2;
const int EXT_INT_ENC_B = 4;

const int PIN_ENC_P = 24;

const int PIN_SDA = 14;
const int PIN_SCL = 15;

class Device {
public:
  class : public atsamd::i2c::Slave {
  public:
    Device *that;

    struct {
      unsigned char protocol = 1;
      short position = 0;
      unsigned char flags = 0;
    } __attribute__((packed)) txData;

    void init(Device *that, int address) {
      this->that = that;

      Slave::init(address, 0, atsamd::i2c::AddressMode::MASK, 0, target::gclk::CLKCTRL::GEN::GCLK0, PIN_SDA, PIN_SCL,
                  target::port::PMUX::PMUXE::C);
    }

    virtual int getTxByte(int index) {
      if (index == 0) {
        txData.position = that->encoder.position;
        that->encoder.position = 0;
      }
      return index < sizeof(txData) ? ((unsigned char *)&txData)[index] : 0;
    }

  } slave;

  class : public atsamd::encoder::Encoder {
  public:
    Device *that;

    void init(Device *that) {
      this->that = that;
      Encoder::init(PIN_ENC_A, PIN_ENC_B, EXT_INT_ENC_A, EXT_INT_ENC_B);
    }
  } encoder;

  void init() {

    // TC1 for motor PWM

    target::PM.APBCMASK.setTC(1, true);

    target::GCLK.CLKCTRL = target::GCLK.CLKCTRL.bare()
                               .setID(target::gclk::CLKCTRL::ID::TC1_TC2)
                               .setGEN(target::gclk::CLKCTRL::GEN::GCLK0)
                               .setCLKEN(true);

    while (target::GCLK.STATUS.getSYNCBUSY())
      ;

    // ADC for WNH7070 current sense

    target::PM.APBCMASK.setADC(true);

    target::GCLK.CLKCTRL = target::GCLK.CLKCTRL.bare()
                               .setID(target::gclk::CLKCTRL::ID::ADC)
                               .setGEN(target::gclk::CLKCTRL::GEN::GCLK0)
                               .setCLKEN(true);

    encoder.init(this);

    int address = 0x40 + atsamd::configPin::readConfigPin(PIN_ADDR1) + 3 * atsamd::configPin::readConfigPin(PIN_ADDR2);
    slave.init(this, address);
  }
};

Device device;

void interruptHandlerSERCOM0() { device.slave.interruptHandlerSERCOM(); }
void interruptHandlerEIC() { device.encoder.interruptHandlerEIC(); }

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
  target::NVIC.ISER.setSETENA(1 << target::interrupts::External::EIC);
}