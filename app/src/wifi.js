const error = require("debug")("app:error");
const info = require("debug")("app:info");
const flashConfig = require("flash-config").flashConfig();
const networkManager = require("flash-config").networkManager();
 
module.exports = async config => {

    flashConfig.watch({
        name: "wifi.txt",
        format: flashConfig.text,
        callback: async config => {
            await networkManager.configure(config, "retradio");
            info(`Connected to ${config.ssid}`);
        }
    });
    

    return {
        checkNetwork() {
            console.info("--------------------- CHECK NET -----------------------------")
        }
    }
}