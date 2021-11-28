const fs = require("fs");
const error = require("debug")("i2c:error");
const info = require("debug")("i2c:info");
const debug = require("debug")("i2c:debug");
const I2C = require("@burgrp/i2c");
const { resolve } = require("path");

// async function createHwI2C() {

//     const pin = 198;

//     const dir = `/sys/class/gpio/gpio${pin}`;

//     try {
//         await fs.promises.writeFile("/sys/class/gpio/unexport", pin.toString());
//     } catch {
//         // fall through
//     }

//     await fs.promises.writeFile("/sys/class/gpio/export", pin.toString());

//     await fs.promises.writeFile(`${dir}/direction`, "in");
//     await fs.promises.writeFile(`${dir}/edge`, "falling");

//     let interruptCallback;

//     async function readInterrupt() {
//         try {
//             let stateStr = await fs.promises.readFile(`${dir}/value`);
//             let pending = stateStr.toString().trim() === "0";
//             //console.info("INT: ", stateStr, pending,interruptCallback);
//             if (pending && interruptCallback) {
//                 let cb = interruptCallback;
//                 interruptCallback = undefined;
//                 try {
//                     cb();
//                 } catch (e) {
//                     error("Error in I2C alert callback:", e);
//                 }
//             }
//         } catch (e) {
//             error("Error in I2C alert check:", e);
//         }
//         setTimeout(readInterrupt, 50);
//     }

//     const bus = await require("i2c-bus").openPromisified(0); //TODO configurable I2C bus #

//     await readInterrupt();

//     return {
//         async read(address, length) {
//             let buffer = Buffer.alloc(length);
//             let read = (await bus.i2cRead(parseInt(address), length, buffer)).bytesRead;
//             if (read !== length) {
//                 throw `Could read only ${read} bytes from ${length}`;
//             }
//             return Uint8Array.from(buffer);
//         },

//         async write(address, data) {
//             let buffer = Buffer.from(data);
//             let written = (await bus.i2cWrite(parseInt(address), data.length, buffer)).bytesWritten;
//             if (written !== data.length) {
//                 throw `Could write only ${written} bytes from ${data.length}`;
//             }
//         },

//         alert() {
//             return new Promise((resolve) => {
//                 interruptCallback = resolve;
//             });
//         }

//     }

// }

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

    info("Initializing I2C bus...");
    let bus = await I2C(process.env.I2C || "sys");

    let devices = [];

    for (let address = 0x40; address < 0x78; address++) {
        try {
            await bus.i2cRead(address, 1);
            let device = createDevice(address, bus);
            devices.push(device);
            info(`Detected I2C device ${addrToStr(address)}: ${device.title}`);
        } catch (e) {
            debug(`Probing I2C device at ${addrToStr(address)}: ${e.message || e}`);
        }
    }

    async function check() {
        while (true) {
            let period = new Promise(resolve => setTimeout(resolve, 100));

            try {
                debug("I2C check");

                for (let device of devices) {
                    await device.check();
                }

            } catch(e) {
                error("Error in I2C check loop:", e);
            }

            await(period);
        }
    }

    check().catch(e => {
        error("Unhandled error in I2C check loop:", e);
    });
}