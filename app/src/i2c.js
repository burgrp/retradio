const fs = require("fs");
const error = require("debug")("app:error");
const info = require("debug")("app:info");


function createDummyDriver() {
    return {
        async read() {
            throw "Dummy driver does not read";
        },
        async write() {
            throw "Dummy driver does not read";
        },
        alert() {
            return new Promise(() => { });
        }
    }
}

async function createHwI2C() {

    const pin = 198;

    const dir = `/sys/class/gpio/gpio${pin}`;

    try {
        await fs.promises.writeFile("/sys/class/gpio/unexport", pin);
    } catch {
        // fall through
    }

    await fs.promises.writeFile("/sys/class/gpio/export", pin);

    await fs.promises.writeFile(`${dir}/direction`, "in");
    await fs.promises.writeFile(`${dir}/edge`, "falling");

    let interruptCallback;

    async function readInterrupt() {
        try {
            let stateStr = await fs.promises.readFile(`${dir}/value`);
            let pending = stateStr.toString().trim() === "0";
            //console.info("INT: ", stateStr, pending,interruptCallback);
            if (pending && interruptCallback) {
                let cb = interruptCallback;
                interruptCallback = undefined;
                try {
                    cb();
                } catch (e) {
                    error("Error in I2C alert callback:", e);
                }
            }
        } catch (e) {
            error("Error in I2C alert check:", e);
        }
        setTimeout(readInterrupt, 50);
    }

    const bus = await require("i2c-bus").openPromisified(0); //TODO configurable I2C bus #

    await readInterrupt();

    return {
        async read(address, length) {
            let buffer = Buffer.alloc(length);
            let read = (await bus.i2cRead(parseInt(address), length, buffer)).bytesRead;
            if (read !== length) {
                throw `Could read only ${read} bytes from ${length}`;
            }
            return Uint8Array.from(buffer);
        },

        async write(address, data) {
            let buffer = Buffer.from(data);
            let written = (await bus.i2cWrite(parseInt(address), data.length, buffer)).bytesWritten;
            if (written !== data.length) {
                throw `Could write only ${written} bytes from ${data.length}`;
            }
        },

        alert() {
            return new Promise((resolve) => {
                interruptCallback = resolve;
            });
        }

    }

}

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

    let bus;

    info("Initializing I2C bus...");
    try {
        bus = await createHwI2C();
    } catch (e) {
        error("Hardware I2C driver failed, trying USB.", e.message || e);
        try {
            bus = await require("@device.farm/usb-i2c-driver").open();
        } catch (e2) {
            error("USB I2C driver failed, falling back to dummy driver.", e2.message || e2);
            bus = createDummyDriver();
        }
    }

    let devices = {};

    for (let address = 0x40; address < 0x78; address++) {
        try {
            await bus.write(address, []);
            let device = createDevice(address, bus);
            devices[address] = device;
            info(`Detected I2C device ${addrToStr(address)}: ${device.title}`);
        } catch (e) {
            if (e.code !== "ENXIO") {
                error(`Error probing I2C device at ${addrToStr(address)}`, e);
            }
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
        error("Error in I2C handleAlert loop", e);
    });
}