const Git = require("simple-git/promise");


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
            await git.merge(["--ff-only"]);
        }
    }

}