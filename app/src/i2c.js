const driver = require("@device.farm/usb-i2c-driver");
const error = require("debug")("app:error");
const info = require("debug")("app:info");

module.exports = async config => {

    let addrToStr = address => "0x" + address.toString(16).toUpperCase();

    function createDevice(address, bus) {
        try {
            let driver = config.drivers[address] || config.drivers[addrToStr(address)];
            if (!driver) {
                throw new Error(`No driver registered for ${addrToStr(address)}`);
            }
            return driver(address, bus, config.player);
        } catch (e) {
            error(e.message || e);
            return {
                title: "unknown device",
                handleAlert() { }
            }
        }
    }

    let bus = await driver.open();
    let devices = {};

    for (let address = 0x40; address < 0x78; address++) {
        try {
            await bus.write(address, []);
            let device = createDevice(address, bus);
            devices[address] = device;
            info(`Detected I2C device ${addrToStr(address)}: ${device.title}`);
        } catch (e) {
        }
    }

    async function forEachDevice(cb) {
        for (let device of Object.values(devices)) {
            try {
                await cb(device);
            } catch (e) {
                error(`Device "${device.title}" thrown exception: ${e.message || e}`);
            }
        }
    }

    async function handleAlert() {
        while (true) {
            await forEachDevice(async device => {
                await device.handleAlert();
            });
            await bus.alert();
        }
    }

    handleAlert().catch(e => {
        error("Error in I2C handleAlert loop");
    });
}