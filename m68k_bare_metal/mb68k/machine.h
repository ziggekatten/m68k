/*** Generic macros for the mb68k SBC
Author:     Mats Brorson
Revision:   2023-12-01

 *    ______           _____                         _   _  __  
 *    | ___ \         /  __ \                       | | | |/  | 
 *    | |_/ /_ __ ___ | /  \/ ___  _ __ ___  _ __   | | | |`| | 
 *    | ___ \ '__/ _ \| |    / _ \| '_ ` _ \| '_ \  | | | | | | 
 *    | |_/ / | | (_) | \__/\ (_) | | | | | | |_) | \ \_/ /_| |_
 *    \____/|_|  \___/ \____/\___/|_| |_| |_| .__/   \___/ \___/
 *                                          | |                 
 *                                          |_|                 
 */



#ifndef MB68K_MACHINE_H_
#define MB68K_MACHINE_H_
#include <stdint.h>

#define     FW_AUTHOR     "Author: Mats Brorson"
#define     FW_BOOT_TEXT  "Brocomp 68010 Generic Computer firmware.\r\nVersion: " __DATE__ " " __TIME__ " " FW_AUTHOR "\r\nReleased under MIT license\r\nType 'h' for help. Happy hacking!\n\n"
#define     FW_PROMPT      "->"
#define     DUART_BASE    0x00D00000        // Base address of the mc68681
#define     DUART_IV_ADR  0x40              // Interupt vector address used for mc6861 
#define     CF_BASE       0x00E00000        // Base address for IDE CompactFlash

/* Some basic ASCII character definitions used by firmware/monitor */
#define CR              (char)0x0d
#define LF              (char)0x0a
#define BLANK           (char)0x20
#define BACKSPACE       (char)0x08


#define DUART_IRQ_MASK  (char)0x02

/* Enums for i/o ports */
enum ioports {
    SER_A = 0,
    SER_B = 1
};


#endif