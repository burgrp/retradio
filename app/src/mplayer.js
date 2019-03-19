const spawn = require("child_process").spawn;
const error = require("debug")("app:error");
const info = require("debug")("app:info");
const mplayerOut = require("debug")("mplayer:out");
const mplayerErr = require("debug")("mplayer:err");

module.exports = async config => {

    let events = config.events;

    let mplayer;

    let stations = await config.stations.getStations();
    let bandIndex = 0;
    let stationIndex = 0;
    let trebleLevel = 0;
    let bassLevel = 0;
    let aperture;

    let checkNetwork;

    function getEqualizer() {
        //let levels = [bassLevel, bassLevel, 2 * bassLevel / 3, bassLevel / 3, 0, 0, trebleLevel / 3, 2 * trebleLevel / 3, trebleLevel, trebleLevel];
        let levels = [bassLevel, 2 * bassLevel / 3, bassLevel / 3, 0, 0, 0, 0, trebleLevel / 3, 2 * trebleLevel / 3, trebleLevel];
        //let levels = [bassLevel, bassLevel / 2, 0, 0, 0, 0, 0, 0, trebleLevel / 2, trebleLevel];
        return levels.map(l => l / 2 - 6).join(":");
    }

    let mpErrors = 0;
    let oneshotMedia;
    let resumeAfterOneshot;

    let currentMedia = () => oneshotMedia ? oneshotMedia : stations[bandIndex][stationIndex].url;

    setInterval(() => mpErrors -= mpErrors ? 1 : 0, 1000);

    function mpStart() {

        let params = [
            "-ao",
            "alsa",
	    "-mixer-channel",
	    "Line Out",
            "-quiet",
            "-nolirc",
            "-slave",
            "-af",
            "equalizer=" + getEqualizer() + ",stats,volnorm",
            currentMedia()
        ];

        info("mplayer", ...params);
        mplayer = spawn("mplayer", params);

        mplayer.stdout.on("data", data => {
            mplayerOut(data.toString());
        });

        mplayer.stderr.on("data", data => {
            let msg = data.toString().trim();
            mplayerErr(msg);
            mpErrors++;
            if (mpErrors > 10) {
                mpErrors = 0;
                error(msg, "- killing mplayer...");
                if (mplayer) {
                    mplayer.kill();
                    mplayer = undefined;
                }
                if (checkNetwork) {
                    checkNetwork();
                }
            }
        });

        mplayer.on("close", (code) => {
            error(`mplayer closed with code ${code}`);
            mplayer = undefined;
            let restart = true;
            // clear oneshotMedia only if played successfully 
            if (oneshotMedia) {
                oneshotMedia = undefined;
                restart = resumeAfterOneshot;
            }
            if (restart) {
                setTimeout(() => {
                    if (!mplayer) {
                        mpStart();
                    }
                }, 1000);
            }
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

    async function changeMedia() {
        if (mplayer) {
            await mpDo("loadfile", currentMedia());
            await events.emit("stationChanged", bandIndex, stationIndex);
            await asyncWait(2000);
        } else {
            mpStart();
        }
    }

    async function changeEqualizer() {
        await mpDo("af_cmdline", "equalizer", getEqualizer());
    }

    function changeValue(current, change, min, max) {
        return Math.max(Math.min(current + change, max), min);
    }

    mpStart();

    return {
        setCheckNetwork: value => checkNetwork = value,

        async playOneshot(media, resume) {
            oneshotMedia = media;
            resumeAfterOneshot = resume;
            await changeMedia();
        },

        async changeVolume(change) {
            await mpDo("volume", change);
        },

        async changeTuning(change) {
            stationIndex = changeValue(stationIndex, change, 0, stations[bandIndex].length - 1);
            await changeMedia();
        },

        async resetTuning() {
            stationIndex = 0;
            await changeMedia();
        },

        async changeBand(change) {
            stationIndex = 0;
            bandIndex = changeValue(bandIndex, change, 0, stations.length - 1);
            await changeMedia();
        },

        async resetBand() {
            stationIndex = 0;
            bandIndex = 0;
            await changeMedia();
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

        async toggleAperture() {
            aperture = !aperture;
            trebleLevel = aperture ? -3 : +10;
            bassLevel = aperture ? -12 : +12;
            await changeEqualizer();
        },

        async playStation(bi, si) {
            bandIndex = bi;
            stationIndex = si;
            await changeMedia();
        }

    }
}