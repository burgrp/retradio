const Git = require("simple-git/promise");
const { spawn } = require("child_process");
const info = require("debug")("app:info");
const error = require("debug")("app:error");

function exec(file, ...args) {
    return new Promise((resolve, reject) => {

        let output = "";
        let process = spawn(file, args);

        process.stdout.on('data', (data) => {
            let dataStr = data.toString();
            output += dataStr;
            info(dataStr);
        });

        process.stderr.on('data', (data) => {
            let dataStr = data.toString();
            output += dataStr;
            error(dataStr);
        });

        process.on('close', (code) => {
            if (code) {
                reject(new Error(output));
            } else {
                resolve(output);
            }
        });

    });
}

module.exports = async config => {

    let git = Git(__dirname);

    return {
        async check() {
            await git.fetch();

            let status = await git.status();

            let log = await git.log([status.tracking]);

            let updates = log.all.slice(0, status.behind).map(logLine => ({
                date: logLine.date,
                message: logLine.message
            }));

            return updates;
        },

        async download() {
            await git.stash(["save"]);
            await git.merge(["--ff-only"]);
            await exec("npm", "install");
            await exec("systemctl", "restart", config.service + ".service");
        }
    }

}