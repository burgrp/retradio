#!/bin/sh
openocd -f interface/cmsis-dap.cfg -ftarget/stm32f0x.cfg -c "init; reset halt; flash read_bank 0 stable.bin 0 0x00004000; exit"
