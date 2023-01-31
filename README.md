# m68k
A over ambitious project to build a usable computer from scratch. Based on bits and pieces from the interwebb, but with my own twists and turns. Some decisions made from my part:

- Assembler is fun in small doses, so my plan is to NOT write firmware in assembler, but instead go down the C route and messing with sections and linkerscripts. Reason beeing that this will make me learn not only the various segments and the ELF format, but also how the GCC/LLVM toolchains works in more details. I would like to use Zig (primary) or Rust (secondary), but as an non compiler wizard, this is currently on the back foot, and O'l trusted C will do.
- Build my own stdlib based on newlib (https://sourceware.org/newlib/)
- Serial interface and an HW-moitor as initial I/0 path to the SBC 

Initial hardware:
- CPU: MC68010@12MHz
- DUART: MC68681
- 2 * 512K FLASH ROM
- 2 x 512K SRAM
- A bunch of 74LS/HCT chips
- A bunch of breadboards
- Some PAL/GAL's to replace discrete glue logic in the end
- Reset circuitry based on 555 timer and with both a reset button as well as an single step function, using DTACK.

## Version history
0.1.6 - Cleaned upp some code and added some README stuff. All prototypes now in headers.

0.1.5 - Just cleaning stuff

0.1.4 - Milestone. Got my bare Firmware (just ending in an loop) running in sim68000

0.1.3 - Just a bunch of renaming and updates of README files. In essence, cleaning up my own mess

0.1.2 - Milestone. I finally got the grips on gcc, linkerscripts, .map files etc. Building an ELF and object dump an binary now generates binary file with an valid reset vector and correct sections copied to RAM. What a fun ride it have been.

0.1.1 - Milestone. Got a free running CPU stepping through memory and blinking leds, by tying databus to ground (all zeros) throug pulldown resistors

## Toolchain(s) and emulators/simulators
Currently using GCC on Ubuntu 20.04 cross compiled for m68k.
In parallel building an LLVM toolchain for exploring the capabilities of using Rust and/or Zig instead of C. This is somewhat in an experimental phase, as some basic compilation efforts on LLVM and Rust/Zig is currently beeing tried out. My toolchains run in docker, and Dockerfiles can be found in the [toolchains] folder.

## Folder structure
| Folder     | Description                                                                          |
|------------|--------------------------------------------------------------------------------------|
| code       | Code for firmware and other stuff goes in here                                       |
| kicad      | KiCAD 6.x schematics                                                                 |
| digital    | Digital simulator for messing with glue logic and generation WinCUPL code in the end |
| toolchains | THings related to toolchains. Docker files etc                                       |