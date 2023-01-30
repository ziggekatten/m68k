# Toolchains and simulators/emulators!

Some useful stuff related to Simulators nad toolchains. Let us start with...

## Simulators
Yes, especially simulators are gold when developing for homebrew hardware. Popping flash ROM in an out of breadboards are tedious, and by chance I stumbled over the sim6000 simulator. An simulator written in C++ and Tkl, but it has two brilliant features:
- Simulation of an mc68681 DUART, with selectable base address! This is golden to test stuff in software. Loads Motorola S-records and of you go. 
- Multiple definable memory areas

The code can be found at: https://github.com/BSVC/bsvc
clone, make and make install and you are up and running. Requires wish and xterm though (apt install xterm wish on Ubuntu or in my case, latest version of Pop!_OS), and the UI...well, time have not been friendly to this app....but it works! It booted my firmware completely written in C. Now I can start messing with serial stuff. It comes with ssome samples including Tutor(!) using an xterm as serial I/O.

TODO: Maybe evolve this codebase and udate UI???

Apart from that, the EASy68k emulator is a good tool if you are into assembler and no pheripherals. The UI is WAY better than sim68000, but no peripherals built in. You can find it here: http://www.easy68k.com/


## Toolchains

Instead of messing up your local linux install or VM's, usage of containers is an pragmatic way for running toolchains.
Several options exists, and this repo have currently three different ones to pick from. Two versions of LLVM for future use of zig and/or rust instead of C.
Third option is to use the toolchan created by: https://rosco-m68k.com/ 

- Dockerfile.15: LLVM 1.15.x build with m68k support. To be used with zig (experimental and not complete!!!)
- Dockerfile.16: LLVM 1.16.x build with m68k support. To be used with rust (experimental and not complete!!!)
- Dockerfile.rosco: A containerized implementation of Rosco SBC toolchain https://rosco-m68k.com/docs/toolchain-installation