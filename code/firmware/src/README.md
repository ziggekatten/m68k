# Firmware source code
This is the base folder for all firmware code, including header files 

## Folder structure

| File/folder       | Description                                                                              |
|-------------------|------------------------------------------------------------------------------------------|
| include/boot.h    | Prototypes for exception handlers and kmain external function                              |
| include/hwdefs.h  | Various basic declarations of hardware specific memory map etc.                          |
| include/mc68681.h | Prototypes for functions related to  serial communication via DUART                      |
| boot.c            | Struct and prototypes for reset vectors, and the entrypoint of the firmware              |
| m68681.c          | Functions for initialize and use the MC68681 DUART                                       |
| main.c            | Placeholder for monitor logic                                                            |
| firmware.ld       | Linker script to ensure that structs and vectors end up at the right place when building |                                      |
| Makefile          | Makefile                                                                                 |

## Building

Building is simple:

make clean
make all

Generates .o files for each C-file, an complete .elf, memory .map file, as well as an raw binary in .bin

