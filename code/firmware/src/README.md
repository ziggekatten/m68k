# Firmware source code

## Folder structure
| File/folder       | Description                                                                            |
|-------------------|----------------------------------------------------------------------------------------|
| boot.c            | Struct and prototypes for reset vectors, and the entrypoint of the firmware            |
| m68681.c          | Functions for initialize and use the MC68681 DUART                                     |
| main.c            | Digital simulator for messing with glue logic and generation WinCUPL code in the end   |
| firmware.ld       | Linker file to ensure that structs and vectors end up at the right place when building |                                      |
| Makefile          | Makefile                                                                               |

## Building

Building is simple:

make clean
make all

Generates .o files for each C-file, an complete .elf, as well as an raw binary in .bin

