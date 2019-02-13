module.exports = async config => {
    return (address, bus, player) => {
        return {
            title: `${[config.onRotate, config.onPush].join("/")} rotary encoder`,
            async handleAlert() {
                let data = Buffer.from(await bus.read(address, 4));

                let protocol = data.readUInt8();
                if (protocol !== 1) {
                    throw new Error(`unsupported protocol ${protocol}`);
                }

                let rotation = data.readInt16LE(1);
                let push = (data.readUInt8(3) & 1) === 1;

                if (push && config.onPush) {
                    let action = config.onPush;
                    await player[action]();
                }

                if (rotation && config.onRotate) {
                    let action = config.onRotate;
                    await player[action](rotation, push);
                }

            }
        }
    }
}