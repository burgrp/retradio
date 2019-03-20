module.exports = async config => {

    config.events.on("stationChanged", (bandIndex, stationIndex) => {
        console.info(bandIndex, stationIndex);
    });

    return {
        client: __dirname + "/webui-client",
        api: {
            webui: {
                getStations: config.stations.getStations,
                playStation: config.player.playStation,
                checkForUpdates: config.update.check,
                downloadUpdates: config.update.download
            }
        }
    }
}