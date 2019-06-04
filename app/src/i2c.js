const fs = require("fs");
const error = require("debug")("app:error");
const info = require("debug")("app:info");


function createDummyDriver() {
    return {
        async read() {
            throw new "Dummy driver does not read";
        },
        async write() {
            throw new "Dummy driver does not read";
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

<<<<<<< HEAD
    const fd = await fs.promises.open(`${dir}/value`, "r");

    function read() {
        const buffer = Buffer.alloc(1);
        fs.readSync(fd.fd, buffer, 0, 1, 0);
        return buffer.toString() === "1";
    }

    let interruptCallback;

    const poller = new Epoll(function (err, fd, events) {
        console.info("INT", err, fd, events);
        if (interruptCallback) {
            //	    interruptCallback();
        }
        read();
    });

    read();
    poller.add(fd.fd, Epoll.EPOLLPRI);

=======
    let interruptCallback;

    async function readInterrupt() {
        let pending = (await fs.promises.readFile(`${dir}/value`)).readUInt8() === "0".charCodeAt(0);
        if (pending && interruptCallback) {
            let cb = interruptCallback;
            interruptCallback = undefined;
            try {
                cb();
            } catch (e) {
                error("Error in I2C alter callback", e);
            }
        }
        setTimeout(readInterrupt, 10);
    }
>>>>>>> release

    const Bus = require("i2c-bus-promised").Bus;
    const bus = new Bus(0); //TODO configurable I2C bus #
    await bus.open();

    await readInterrupt();

    return {
        async read(address, length) {
            let buffer = Buffer.alloc(length);
            let read = await bus.read(parseInt(address), length, buffer);
            if (read !== length) {
                throw `Could read only ${read} bytes from ${length}`;
            }
            return Uint8Array.from(buffer);
        },

        async write(address, data) {
            let buffer = Buffer.from(data);
            let written = await bus.write(parseInt(address), data.length, buffer);
            if (written !== data.length) {
                throw `Could write only ${read} bytes from ${data.length}`;
            }
        },

        alert() {
            return new Promise((resolve) => {
<<<<<<< HEAD
                setTimeout(resolve, 100);
                //interruptCallback = resolve;
=======
                interruptCallback = resolve;
>>>>>>> release
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