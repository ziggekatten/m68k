# Note to myself: I hate C pointers and macros.......

# m68k
A over ambitious project to build a usable computer from scratch. Based on bits and pieces from the interwebb, but with my own twists and turns. This main README will change frequently when I change my mind and decisions. Some decisions made from my part:

- Assembler is fun in small doses, so my plan is to NOT write firmware in assembler, but instead go down the C route and messing with sections and linkerscripts. Reason beeing that this will make me learn not only the various segments and the ELF format, but also how the GCC/LLVM toolchains works in more details. I would like to use Zig (primary) or Rust (secondary), but as an non compiler wizard, this is currently on the back foot, and O'l trusted C will do. There are some chanllenges though, that are quite simple in assembler, but when using C and segregation of duty, requires some more thoughts. For example, when using interrupts on the serial line, how do you pass the input from the exceptionhandler to your main kernel code? Simple answer one would say, some defined pseudo registers monitored by your main code in combination of global variables/structs in C. But this comes at an cost of CPU cycles as stuff needs to pass memory in several stages. Not easy decisions. Also, as I'm building some built in monitoring stuff in the firmwware to see values of stack pointer and register values, I might need to add som asssembler in the end. It will be inline if that's the case. It hurts, but unless I can use some GCC low level stuff I probably need to do this.
- Build my own stdlib based on newlib (https://sourceware.org/newlib/)
- Serial interface and an HW-monitor as initial I/0 path to the SBC 

Initial hardware:
- CPU: MC68010@12MHz
- DUART: MC68681
- 2 * 512K FLASH ROM
- 2 x 512K SRAM
- A bunch of 74LS/HCT chips
- A bunch of breadboards
- Some PAL/GAL's to replace discrete glue logic in the end
- Reset circuitry based on 555 timer and with both a reset button as well as an single step function, using DTACK.

## Some loose thoughts
- Use ELF as a base segment standard instead of Motorola S-records. This means that i need to steal someone elses ELF loader I guess... 
- When basic serial I/O is done. It's time to look at keyboard input as well as graphics display. The keyboard stuff is easy enough if using PS/2 standard. The graphics stuff however is a little bit more complicated. Signal wise it is easy, just output the correct voltages and Bob's your uncle. But getting data in a format that does not bog down CPU to some memory mapped hardware, and the get the display circuit to effectively interpret data and do stuff, is a different story. The 680x0 CPU is not capable to feed pixel data at rates needed if just pushing pixels, so there have to be stuff in between. Amigas, Ataris and others have this done in custom chips, which means that I have to do the same. But this is where I draw the line (pun intended) and don't design my own blitter, copper etc. I will probably interface to already done parts, using APIs or existing hardware designs. In the end, designing at this level means also supply low level libraries and stuff. However, an pure vector based drawing design is in my head, so one never know....

## Memory map of the design
I keep it simple, and plan using the VBR register in the MC68010, so there is no shadowing or moving of ROM in my design.

| Address                 | Description                                                             |
|-------------------------|-------------------------------------------------------------------------|
| 0x00000000 - 0x000FFFFF | ROM ( 2 x 512K)                                                         |
| 0x00100000 - 0x001FFFFF | Onboard RAM (1 MB)                                                      |
| 0x00200000 - 0x00CFFFFF | Space for additional (14 MB) RAM                                        |
| 0x00D00000 - 0x00FFFFFF  | I/O space  (2 MB)                                                       | 

## Version history
0.1.8 - Switched to PlatformIO for Arduino stuff

0.1.7 - Got the firmware to configure DUART and spit out stuff on the terminal in sim68000 using pure C. Hardware is tested in an sense that I can control the DUART from an Arduiono Mega, and the CPU stuff on the breadboard is free running, and are awaiting the pairing of DUART and firmware code.

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
| toolchains | Things related to toolchains. Docker files etc                                       |
| tests      | Arduino stuff used to test and program various parts of the design                   |

## Some experiences to share

MC68000/10 memory mapping and external pheripherals are always an challenge. That said, the m68k has the most beautiful register/memory layout and assembler syntax known to man. If todays CPU's had this layout, ohh man... Normally external peripherals only use a few address lines and more importantly only half the data bus (unless on an MC68008). What this means is that you really need to understand how the processor address memory and in which order it's doing stuff. First of all, as you might have noted on the CPU there is no address line of 0. First physical address line is A1, which will cause som confusion to newbies (as it did to me!). To explain this we need to understand two other physical pins on the CPU: UDS and LDS. UDS means Upper Data Strobe, and LDS means Lower Data Strobe. These pins define if you are in the upper 8-bit or lower 8-bit of an word (16 bit). 

Now, this is what caught me, even adresses is always the upper 8-bits. Easiest way of explain this is by starting at at the lowest address in hex: 0x00000000. This is an even address, and accessing this address will assert the UDS-pin signaling that the upper 8-bits of the data bus will be read/written from/to (bit 15-8). When designing your memory map, things can be confusing. Let us say that memory 0x00000000 to 0x000FFFFF is your first MB of RAM, and you think that address 0x00100000 is the first byte in the I/O space, you would be wrong. Address 0x00100000 is the upper 8-bits of the 16-bit word, and if you have the pheriperal connected to the D0-D7, the effective address is actually 0x00100001!. 

What this means is, that you need to take care when accessing 8-bit memory mapped peripherals. Let us take an simple example here using the MC68681 DUART chip as an example. It has an 4-bit addressing bus for it's registers that we normally connect to A1-A4, and an 8-bit address bus, connected to the A0-A7 physical bus. According to the documentation the registers are one byte in between on the chip itself. 

But this is not true in the scope of the CPU, as the least significant address bus is never seen by the chip. It sees A1, not A0(UDS). In effect, this means that your code needs to have an offset of two(2) whereas the chip has an offset of only one(1).
In general, working with bytes is an pain as you need to think about alignment, and if possible use words....