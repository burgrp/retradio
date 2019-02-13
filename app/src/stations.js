const fs = require("fs");
const pro = require("util").promisify;

module.exports = async config => {

    let dir = __dirname + "/..";
    let stations = (await Promise.all(
        (await pro(fs.readdir)(dir))
            .filter(fn => fn.endsWith(".m3u"))
            .sort()
            .map(fn => pro(fs.readFile)(dir + "/" + fn))
    )).map(
        plBuffer => plBuffer
        .toString()
        .split("\n")
        .map(line => line.trim())
        .filter(line => line !== "" && !line.startsWith("#"))
    );

    return stations;
}