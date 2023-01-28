# m68k
A over ambitious project to build a usable computer from scratch. Based on bits and pieces from the interwebb, but with my own twists and turns. Some decisions made from my part:

- Assembler is fun in small doses, so my plan is to NOT write firmware in assembler, but instead go down the C route and messing with sections and linkerscripts. Reason beeing that this will make me learn not only the various segments and the ELF format, but also how an toolchain works in more details.
- Build C-stdlib based on newlib (https://sourceware.org/newlib/)
- Serial interface and an HW-moitor as initial I/0 path to the SBC 


Initial hardware:
- CPU: MC68010@12MHz
- DUART: MC68681
- 2 * 512K FLASH ROM
- 2 x 512K SRAM
- A bunch of 74LS/HCT chips
- A bunch of breadboards
- Some GAL's to replace discrete glue logic in the end

## Version info
0.1.2 - Milestone. I finally got the grips on gcc, linkerscripts, memory maps etc. Building an ELF and object dump an binary now generates binary file with an valid reset vector. What a fun ride it have been.

0.1.1 - Milestone. Got a free running CPU stepping through memory and blinking leds, by tying databus to ground (all zeros) throug pulldown resistors

## Toolchain(s)
Currently using GCC on Ubuntu 20.04 cross compiled for m68k.
In parallel building an LLVM toolchain for exploring the capabbilities of using Rust and/or Zig instead of C. This is somewhat in an experimental phase, as some basic compilation efforts is beeing tried out. My toolchains run in docker, and Dockerfiles can be foun in the [toolchains] folder.

## Folder structure
