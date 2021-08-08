# Micropython Board Config Files

These customization files can be used to build a Micropython port of the
Aliman H750 demo board. Just follow the normal Micropython building methods.
Briefly,

## Installation (brief summary)

* Clone from the [Micropython GitHub repository](https://github.com/micropython/micropython)
* Follow the instructions to prepare the compiler toolchain (you
  will probably need to download the gnu-arm cross-compiler)
* Copy this `ALIMAN_H750` directory  to `ports/stm32/boards`
* From the `ports/stm32` diretory, perform the build:
  - `$ make BOARD=ALIMAN_H750 clean`
  - `$ make BOARD=ALIMAN_H750`
* Connect the H750 Demo board by USB, and boot it up in DFU mode
  - jumper `BOOT0` pin and `3.3V` pin during CPU reset
* Install Micropython to the demo board:
  - `$ make BOARD=ALIMAN_H750 deploy`

## Connect to the Board

You can now use Micropython on the H750 board. If you boot the board
after downloading the Micropython image, you should see a 16 MB flash
partition.

Two methods that I frequently to connect to Micropython boards:

* Thonny IDE
  - [https://thonny.org](https://thonny.org)
  - GitHub [repository](https://github.com/thonny/thonny) and
  [wiki](https://github.com/thonny/thonny/wiki)
  - [short article](https://hackaday.com/2021/04/29/wireless-micropython-programming-with-thonny/) I wrote about it

* rshell 
  - GitHub [repository](https://github.com/dhylands/rshell)
  - can install by `pip install rshell`

## Quick Demo Script

Copy the file `aliman.py` to the `/flash` drive, and from the REPL
prompt type 

`>>> import aliman`

You should see the following output:

```
>>> import aliman
   flash: 15 MiB  (size)   15 MiB  (free)
      sd: 29 GiB  (size)   29 GiB  (free)
cpu freq: 480.0 MHz
 sysname: pyboard
nodename: pyboard
 release: 1.16.0
 version: v1.16-171-gf834fef6b on 2021-08-08
 machine: ALIMAN_STM32H750VBTX with STM32H7XX
blinking:  __ ** __ ** __ ** __ ** __ **
Aliman STM32H750 Demo Board, The End.
>>>
```

This shows the following points:
* U3 W25Q128W16 is active and providing 16 MB flash drive
* SD card recognized, if one is inserted
* CPU clock speed is configured correctly at 480 MHz
* LED output D5 operational
* TBD: serial port tests

