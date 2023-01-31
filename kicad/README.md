# Hardware design

Basic principles:
- Use of buffers when in doubt. The 68010 pins can't drive that much current 

TODO: description

- CPU: MC68010@12MHz
- DUART: MC68681
- 2 * 512K FLASH ROM
- 2 x 512K SRAM


## Memory map

TODO: description

| Start address (hex) | End address (hex) | Usage                              |
|:-------------------:|:-----------------:|:----------------------------------:|
|0x00100000           |0x00200000         | Onboard RAM                        |
|0x00000000           |0x00100000         | Onboard ROM                        |