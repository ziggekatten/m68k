/**
* @Author: Mats Brorson
* @Date: 2023-0127
*
* @Description: All definition for the mb68k SBC memory map is found here
* Memory map is quite simple: ROM at the base (1 MB), followedd by 14 MB SRAM, leaving top 1 MB for I/O space
*/

//ROM start address
#define ROM_BASE        0x00000000
#define ROM_SIZE        (ROMBASE + 0x000FFFFF) // 1 MB of ROM (2 * 512k)
//RAM start address
#define RAM_BASE        0x00100000



// Stack pointer start (must be even. remember, sp is decreased BEFORE adding data to stack)
#define STACK_POINTER   0x00200000