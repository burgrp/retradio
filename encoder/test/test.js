const i2c = require("@device.farm/usb-i2c-driver").open();

// setInterval(() => {
//     i2c.read(0x40, 3).then(console.info, console.error);
// }, 1000);

function asyncWait(ms) {
    return new Promise(resolve => {
        setTimeout(resolve, ms);
    });
}

async function start() {
    while(true){
        //console.info("Reading...")
        console.info(await i2c.read(0x45, 4));
        //console.info("Waiting for alert...");
        await i2c.alert();
        //await asyncWait(1000);
    }
}

start().catch(console.error);

