module.exports = async ({ bands, apertures }) => {
    return (address, bus, player) => {

        let prevDown;

        return {
            title: `bands switch`,
            async check() {
                let data = await bus.i2cRead(address, 3);

                let protocol = data.readUInt8();
                let down;
                if (protocol == 1) {
                    down = data.readUInt8(1);
                } else if (protocol == 2) {
                    let newDown = data.readUInt8(1);
                    down = ~prevDown & newDown;
                    prevDown = newDown;
                } else {
                    throw new Error(`unsupported protocol ${protocol}`);
                }

                let band = down & (Math.pow(2, bands) - 1);
                if (band) {
                    band = Math.round(Math.log2(band));
                    await player.playStation(band, 0);
                }

                let aperture = down >> bands;
                if (aperture) {
                    aperture = Math.round(Math.log2(aperture) * 10 / (apertures - 1));
                    await player.setAperture(aperture);
                }
                
            }
        }
    }
}