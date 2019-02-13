const spawn = require("child_process").spawn;
const error = require("debug")("app:error");
const info = require("debug")("app:info");
const mplayerOut = require("debug")("mplayer:out");
const mplayerErr = require("debug")("mplayer:err");

module.exports = async config => {

    let mplayer;

    let stations = config.stations;
    let bandIndex = 0;
    let stationIndex = 0;

    function mpStart() {

        mplayer = spawn("mplayer", [
            "-ao",
            "alsa",
            "-quiet",
            "-nolirc",
            "-slave",
            stations[bandIndex][stationIndex]
        ]);

        mplayer.stdout.on("data", (data) => {
            mplayerOut(data.toString());
        });

        mplayer.stderr.on("data", (data) => {
            mplayerErr(data.toString());
        });

        mplayer.on("close", (code) => {
            error(`mplayer closed with code ${code}`);
            mpStart();
        });
    }

    function asyncWait(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }

    async function mpDo(...cmd) {
        if (mplayer) {
            info(...cmd);
            mplayer.stdin.write(cmd.join(" ") + "\n");
        }
    }

    async function changeStation() {
        await mpDo("loadfile", stations[bandIndex][stationIndex]);
        await asyncWait(2000);
    }

    mpStart();

    return {
        async changeVolume(change) {
            info(`Change volume: ${change}`);
            await mpDo("volume", change);
        },

        async changeTuning(change) {
            stationIndex += change;
            if (stationIndex < 0) {
                stationIndex = 0;
            }
            if (stationIndex >= stations[bandIndex].length) {
                stationIndex = stations[bandIndex].length - 1;
            }
            await changeStation();
        },

        async resetTuning() {
            stationIndex = 0;
            await changeStation();
        },

        async changeBand(change) {
            stationIndex = 0;
            bandIndex += change;
            if (bandIndex < 0) {
                bandIndex = 0;
            }
            if (bandIndex >= stations.length) {
                bandIndex = stations.length - 1;
            }
            await changeStation();
        },

        async resetBand() {
            stationIndex = 0;
            bandIndex = 0;
            changeStation();
        }
    }
}