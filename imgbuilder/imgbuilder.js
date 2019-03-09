const info = console.info;
const error = console.info;
const { spawn } = require("child_process");
const fs = require("fs").promises;

function ex(file, ...args) {
    info(file, ...args);
    return new Promise((resolve, reject) => {
        let process = spawn(file, args);
        let stdout = "";
        let stderr = "";

        process.stdout.on("data", data => {
            data = data.toString();
            stdout += data;
            info(data);
        });

        process.stderr.on("data", data => {
            data = data.toString();
            stderr += data;
            error(data);
        });

        process.on("close", code => {
            if (code) {
                reject({
                    code,
                    message: stderr
                });
            } else {
                resolve(stdout);
            }
        });

    });
}

async function buildImage(options) {
    let sourceImage = options.sourceImage || "source.img";
    let targetImage = options.targetImage || "target.img";
    let extraSpaceMB = options.extraSpaceMB || 100;
    let mountPoint = options.mountPoint || "/tmp/imgbuilder"

    async function chroot(...args) {
        return await ex("chroot", mountPoint, ...args);
    }

    async function cleanup() {

        async function unmount(path) {
            try {
                await ex("umount", `${mountPoint}${path}`);
            } catch{
                // fallthrough
            }
        }

        for (let sfs of ["dev", "proc", "sys"]) {
            await unmount(`/${sfs}`);
        }
        await unmount("/");

        await ex("kpartx", "-dv", targetImage);
    }

    await cleanup();

    await ex("dd", "bs=1M", `if=${sourceImage}`, `of=${targetImage}`);

    await ex("truncate", `--size=+${extraSpaceMB}M`, targetImage);

    await ex("parted", targetImage, "resizepart", 1, "100%");

    let loopName = "/dev/mapper/" + (/^add map (\w+) /.exec(await ex("kpartx", "-slav", targetImage))[1]);

    await ex("resize2fs", "-p", loopName);

    try {
        await fs.mkdir(mountPoint);
    } catch (e) {
        if (e.code !== "EEXIST") throw e;
    }
    await ex("mount", loopName, mountPoint);
    for (let sfs of ["dev", "proc", "sys"]) {
        await ex("mount", "--bind", `/${sfs}`, `${mountPoint}/${sfs}`);
    }

    await ex("cp", "/usr/bin/qemu-arm-static", mountPoint + "/usr/bin");

    if (options.hostname) {
        await fs.writeFile(mountPoint + "/etc/hostname", options.hostname);
    }

    await chroot("apt", "update");
    await chroot("apt", "upgrade");
    await chroot("apt", "install", "mc", "htop", "tree", "git");

    await chroot("wget", "-O", "/root/node.gz", options.nodeDownloadUrl || "https://nodejs.org/dist/v10.15.3/node-v10.15.3-linux-armv7l.tar.gz");
    await chroot("tar", "-xf", "/root/node.gz", "--directory", "/usr/local", "--strip-components", "1");

}


buildImage({
    sourceImage: "/home/paul/Downloads/Armbian_5.75_Orangepizero_Ubuntu_bionic_next_4.19.20.img",
    targetImage: "/home/paul/Downloads/retradio.img",
    hostname: "retradio"
}).catch(e => console.error("Error:", e.message || e));