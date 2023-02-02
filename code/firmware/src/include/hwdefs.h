/**
* @Author: Mats Brorson
* @Date: 2023-0127
*
* @Description: All definition for the mb68k SBC memory map is found here
* Memory map is quite simple: ROM at the base (1 MB), followedd by 14 MB SRAM, leaving top 1 MB for I/O space
*/
#ifndef _MB68K_HWDEFS_H
#define _MB68K_HWDEFS_H

/* ROM start address */
#define ROM_BASE                        0x00000000
#define ROM_SIZE                        (ROM_BASE + 0x000FFFFF) // 1 MB of ROM (2 * 512k)
/* RAM start address */
#define RAM_BASE                        0x00100000
#define RAM_SIZE                        (RAM_BASE + 0x000FFFFF) 

/* 
* Stack pointer at end of onboard 1 MB (must be at even address. 
* Remember, sp is decreased BEFORE adding data to stack) 
*/
#define STACK_POINTER                   0x00200000


/* MC68661 DUART definitions used for boot */
#define DUART_BASE                      0x00300000              // Base I/O memory mapped address of the DUART
#define DUART_DEFAULT_STOP_BITS         1                       // Default stop bits 
#define DUART_DEFAULT_BAUDRATE          19200                   // Default baud rate 
#define DUART_DEFAULT_PARITY            0                       // Default parity
#define DUART_DEFAULT_FLOWCONTROL       0                       // Default flowcontrol. 0 = none


#endif