# m68k
A over ambitious project to build a usable computer from scratch. Based on bits and pieces from the interwebb, but with my own twists and turns. Some decisions made from my part:

- Assembler is fun in small doses, so my plan is to NOT write firmware in assembler, but instead go down the C route and messing with sections and linkerscripts. Reason beeing that this will make me learn not only the ELF format, but also how an toolchain works in more details.
- Build C-stdlib baesd on newlib (https://sourceware.org/newlib/)

Initial hardware:
- CPU: MC68010@12MHz
- DUART: MC68681
- A bunch of 74LS/HCT chips
- A bunch of breadboards
- Some GAL's to replace discrete glue logic in the end

## Version info
0.1.2 - Milestone. I finally got the grips on gcc, linkerscripts, memory maps etc. Building an ELF and object dump an binary now generates binary file with an valid reset vector. What a fun ride it have been.

0.1.1 - Milestone. Got a fre running CPU stepping through memory and blinking leds, by tying databus to ground (all zeros)

## Folder structure

