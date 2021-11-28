module.exports = async config => {
    return (address, bus, player) => {

        let prevPosition;
        let prevRotation;

        return {
            title: `${[config.onRotate, config.onPush].join("/")} rotary encoder`,
            async check() {
                let data = await bus.i2cRead(address, 6);

                let rotation;
                let push;

                let protocol = data.readUInt8();
                if (protocol == 1) {
                    rotation = data.readInt16LE(1);
                    push = (data.readUInt8(3) & 1) === 1;
                } else if (protocol == 2) {
                    let position = data.readInt32LE(1);
                    rotation = isFinite(prevPosition)? position - prevPosition: 0;                        
                    prevPosition = position;                   
                    push = (data.readUInt8(5) & 1) === 1;
                } else {
                    throw new Error(`unsupported protocol ${protocol}`);
                }

                if (config.reduced) {
                    let reducedRotation = Math.sign(prevRotation) == Math.sign(rotation) ? 0: Math.sign(rotation);
                    prevRotation = rotation;
                    rotation = reducedRotation;
                 } 

                function checkAction(action) {
                    if (typeof player[action] !== "function") {
                        throw `Player does not implement ${action}.`;
                    }
                    return player[action];
                }

                if (push && config.onPush) {
                    let action = config.onPush;
                    await checkAction(action)();
                }

                if (rotation && config.onRotate) {
                    let action = config.onRotate;
                    await checkAction(action)(rotation, push);
                }

            }
        }
    }
}