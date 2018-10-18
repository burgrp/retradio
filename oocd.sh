#!/bin/bash
cd ~/esp/openocd-esp32
src/openocd -s tcl/ -f interface/altera-usb-blaster.cfg -f board/esp-wroom-32.cfg