/*
Author: Mats Brorson
Date: 2023-0127

All definition for the mb68k SBC memory map is found here

*/


//ROM start address
#define ROM_BASE        0x00000000
//RAM start address
#define RAM_BASE        0x00100000
// Stack pointer start (must be even. remember, sp is decreased BEFORE adding data to stack)
#define STACK_POINTER   0x00200000