require("@burgrp/appglue")({ require, file: __dirname + "/../config.json" }).main(async config => {

    await config.webglue.start();

});