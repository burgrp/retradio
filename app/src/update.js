const Git = require("simple-git/promise");


module.exports = async config => {

    let git = Git(__dirname);
    
    return {
        async check() {
            await git.fetch();
    
            let status = await git.status();
        
            let log = await git.log([status.tracking]);
        
            let updates = [];
            for (let logLine of log.all) {
                if (logLine.message.indexOf(" (HEAD -> ") > -1) {
                    break;
                }
                updates.push({
                    date: logLine.date,
                    message: logLine.message
                });
            }
            return updates;
        },

        async download() {
            await git.merge(["--ff-only"]);
        }
    }

}