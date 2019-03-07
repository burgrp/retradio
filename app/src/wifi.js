const error = require("debug")("app:error");
const info = require("debug")("app:info");
const flashConfig = require("flash-config").flashConfig();
const networkManager = require("flash-config").networkManager();

module.exports = async config => {

    function tell(what, resume) {
        config.player.playOneshot(`${__dirname}/../voice/${what}.mp3`, resume).catch(console.error);
    }

    flashConfig.watch({
        name: "wifi.txt",
        format: flashConfig.text,
        callback: async config => {
            tell("wifi-config-found");
            try {
                await networkManager.configure(config, "retradio");
                tell("wifi-config-done", true);
            } catch (e) {
                tell("wifi-config-failed", true);
                throw e;
            }
        }
    });

    let noConnectionTold = false;

    return {
        checkNetwork() {
            if (!noConnectionTold) {
                noConnectionTold = true;
                tell("no-connection");
            }
        }
    }
}