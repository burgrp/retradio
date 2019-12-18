module.exports = async config => {

    config.events.on("stationChanged", (bandIndex, stationIndex) => {
    });

    return {
        client: __dirname + "/webui-client",
        api: {
            webui: {
                getStations: config.stations.getStations,
                playStation: config.player.playStation
            }
        }
    }
}