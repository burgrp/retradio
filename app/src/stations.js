module.exports = async config => {

    return {
        getStations() {
            return config.default;
        }
    };
}