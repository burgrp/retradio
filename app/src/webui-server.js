module.exports = async config => {
    return {
        client: __dirname + "/webui-client",
        api: {
            webui: {
                async getStations() {
                    return await config.stations.getStations();
                }
            }
        }
    }
}