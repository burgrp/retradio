const spawn = require("child_process").spawn;
const error = require("debug")("player:error");
const info = require("debug")("player:info");
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
    let apertureLevel = 0;

    function getEqualizer() {
        let levels = [bassLevel, bassLevel, 2 * bassLevel / 3, bassLevel / 3, 0, 0, trebleLevel / 3, 2 * trebleLevel / 3, trebleLevel, trebleLevel];
        return levels.map(l => Math.round(l / 2 - 6)).join(":");
    }

    let mpErrors = 0;

    let currentMedia = () => ({
        ...stations[bandIndex][stationIndex],
        playlist: stations[bandIndex][stationIndex].url.endsWith(".m3u")
    });

    setInterval(() => mpErrors -= mpErrors ? 1 : 0, 1000);

    function mpStart() {

        let media = currentMedia();

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
            ...(media.playlist ? ["-playlist", media.url] : [media.url])
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
            }
        });

        mplayer.on("close", (code) => {
            error(`mplayer closed with code ${code}`);
            mplayer = undefined;
            setTimeout(() => {
                if (!mplayer) {
                    mpStart();
                }
            }, 1000);
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
            let media = currentMedia();
            await mpDo(media.playlist ? "loadlist" : "loadfile", media.url);
            await events.emit("stationChanged", bandIndex, stationIndex);
        } else {
            mpStart();
        }
    }

    async function updateEqualizer() {
        await mpDo("af_cmdline", "equalizer", getEqualizer());
    }

    async function updateAperature() {
        trebleLevel = 13 * apertureLevel / 10 -3;
        bassLevel = 24 * apertureLevel / 10 -12;
        await updateEqualizer();
    }


    function changeValue(current, change, min, max) {
        return Math.max(Math.min(current + change, max), min);
    }

    mpStart();

    return {
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
            await updateEqualizer();
        },

        async resetTreble() {
            trebleLevel = 0;
            await updateEqualizer();
        },

        async changeBass(change) {
            bassLevel = changeValue(bassLevel, change, -12, 12);
            await updateEqualizer();
        },

        async resetBass() {
            bassLevel = 0;
            await updateEqualizer();
        },

        async toggleAperture() {
            apertureLevel = apertureLevel ? 0 : 10;
            await updateAperature();
        },

        async changeAperture(change) {
            apertureLevel = changeValue(apertureLevel, change, 0, 10);
            await updateAperature();
        },

        async setAperture(ap) {
            apertureLevel = ap;
            await updateAperature();
        },

        async resetAperture() {
            apertureLevel = 0;
            await updateAperature();
        },

        async playStation(bi, si) {
            if (bi < stations.length && si < stations[bi].length) {
                bandIndex = bi;
                stationIndex = si;
                await changeMedia();
            }
        }

    }
}