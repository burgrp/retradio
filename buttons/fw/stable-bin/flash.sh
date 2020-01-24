#!/bin/sh
openocd -f interface/cmsis-dap.cfg -ftarget/stm32f0x.cfg -c "init; reset halt; flash erase_address pad 0x08000000 0x00004000; flash write_bank 0 stable.bin 0; exit"