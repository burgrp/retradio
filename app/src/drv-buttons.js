module.exports = async config => {
    return (address, bus, player) => {
        return {
            title: `bands switch`,
            async handleAlert() {
                let data = Buffer.from(await bus.read(address, 4));

                let protocol = data.readUInt8();
                if (protocol !== 1) {
                    throw new Error(`unsupported protocol ${protocol}`);
                }
                
                let down = data.readUInt8(1);
                let up = data.readUInt8(2);

                for (let b = 0; b < 8; b++) {
                    if ((down >> b) & 1) {
                        await player.playStation(b, 0);
                        break;
                    }
                }
            }
        }
    }
}