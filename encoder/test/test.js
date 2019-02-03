const i2c = require("@device.farm/usb-i2c-driver").open();


// (async () => {
    
//     let data = await i2c.read(0x70, 5);
//     console.info(data);

// })().catch(console.error);

setInterval(() => {
    i2c.read(0x70, 5).then(console.info, console.error);
}, 1000);