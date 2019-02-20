const spawn = require("child_process").spawn;
const error = require("debug")("app:error");
const info = require("debug")("app:info");
const mplayerOut = require("debug")("mplayer:out");
const mplayerErr = require("debug")("mplayer:err");

module.exports = async config => {

    let mplayer;

    let stations = config.stations;
    let bandIndex = 0;
    let stationIndex = 1;
    let trebleLevel = 0;
    let bassLevel = 0;
    let aperture;

    function getEqualizer() {
        //let levels = [bassLevel, bassLevel, 2 * bassLevel / 3, bassLevel / 3, 0, 0, trebleLevel / 3, 2 * trebleLevel / 3, trebleLevel, trebleLevel];
        let levels = [bassLevel, 2 * bassLevel / 3, bassLevel / 3, 0, 0, 0, 0, trebleLevel / 3, 2 * trebleLevel / 3, trebleLevel];
        //let levels = [bassLevel, bassLevel / 2, 0, 0, 0, 0, 0, 0, trebleLevel / 2, trebleLevel];
        return levels.map(l => l / 2 - 6).join(":");
    }

    function mpStart() {

        let params = [
            "-ao",
            "alsa",
            "-quiet",
            "-nolirc",
            "-slave",
            "-af",
            "equalizer=" + getEqualizer() + ",stats,volnorm",
            stations[bandIndex][stationIndex]
        ];

        info("mplayer", ...params);
        mplayer = spawn("mplayer", params);

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

    async function changeEqualizer() {
        await mpDo("af_cmdline", "equalizer", getEqualizer());
    }

    function changeValue(current, change, min, max) {
        return Math.max(Math.min(current + change, max), min);
    }

    mpStart();

    return {
        async changeVolume(change) {
            await mpDo("volume", change);
        },

        async changeTuning(change) {
            stationIndex = changeValue(stationIndex, change, 0, stations[bandIndex].length - 1);
            await changeStation();
        },

        async resetTuning() {
            stationIndex = 0;
            await changeStation();
        },

        async changeBand(change) {
            stationIndex = 0;
            bandIndex = changeValue(bandIndex, change, 0, stations.length - 1);
            await changeStation();
        },

        async changeTreble(change) {
            trebleLevel = changeValue(trebleLevel, change, -12, 12);
            await changeEqualizer();
        },

        async resetTreble() {
            trebleLevel = 0;
            await changeEqualizer();
        },

        async changeBass(change) {
            bassLevel = changeValue(bassLevel, change, -12, 12);
            await changeEqualizer();
        },

        async resetBass() {
            bassLevel = 0;
            await changeEqualizer();
        },

        async resetBand() {
            stationIndex = 0;
            bandIndex = 0;
            await changeStation();
        },

        async toggleAperture() {
            aperture = !aperture;
            trebleLevel = aperture ? -3 : +10;
            bassLevel = aperture ? -12 : +12;
            await changeEqualizer();
        }
    }
}