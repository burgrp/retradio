const i2c = require("@device.farm/usb-i2c-driver").open();

setInterval(() => {
    i2c.read(0x40, 3).then(console.info, console.error);
}, 1000);