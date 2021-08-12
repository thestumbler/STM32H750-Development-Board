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

The example program `aliman.py` demonstrates the following points:

* U3 W25Q128W16 is active and providing 16 MB flash drive
* SD card recognized, if one is inserted
* CPU clock speed is configured correctly at 480 MHz
* LED output D5 operational
* Serial port loopback tests
* RTC clock date/time stamps (not persistent)

Copy the file `aliman.py` to the `/flash` drive, and from the REPL
prompt type:
```
>>> import aliman
>>> aliman.main()
```

Example output:

```
===========================================
Aliman STM32H750 Demo Board Example Program
started at: 20:39:45.456  12-Aug-2021
   flash: 15 MiB  (size)   15 MiB  (free)
      sd: 29 GiB  (size)   29 GiB  (free)
cpu freq: 480.0 MHz
 sysname: pyboard
nodename: pyboard
 release: 1.16.0
 version: v1.16-198-g42d1a1635-dirty on 2021-08-12
 machine: ALIMAN_STM32H750VBTX with STM32H7XX
blinking:  __ ** __ ** __ ** __ ** __ **
Serial Port Loopback, short RX(#1) to TX(#2) on J4
------
  Sent string:  ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
  Sending 52 letters encoded as 52 bytes
  Received 52 letters encoded as 52 bytes
  Reply string: ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
  Strings Match: True
------
  Sent string:  ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎㅏㅓㅗㅜㅡㅣㅐㅔㅑㅕㅛㅠ
  Sending 26 letters encoded as 78 bytes
  Received 26 letters encoded as 78 bytes
  Reply string: ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎㅏㅓㅗㅜㅡㅣㅐㅔㅑㅕㅛㅠ
  Strings Match: True
------
  Sent string:  Welcome to Aliman's H750 Demo Board
  Sending 35 letters encoded as 35 bytes
  Received 35 letters encoded as 35 bytes
  Reply string: Welcome to Aliman's H750 Demo Board
  Strings Match: True
------
  Sent string:  알리맨의 H750 대모보드에 어서오십시요
  Sending 22 letters encoded as 52 bytes
  Received 22 letters encoded as 52 bytes
  Reply string: 알리맨의 H750 대모보드에 어서오십시요
  Strings Match: True
Serial Port Loopback Done.
Aliman STM32H750 Demo Board Example Program
finished at: 20:39:47.979  12-Aug-2021
runtime: 2.523 secs
=================================== The End
>>>
```

