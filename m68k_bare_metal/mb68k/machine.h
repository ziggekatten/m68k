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

#define     FW_MACHINE_ID "BroComp 68010 Generic Computer."
#define     FW_VERSION    "Version: " + __DATE__
#define     FW_AUTHOR     "Author: Mats Brorson"
#define     FW_LICENSE    "Released under MIT license. Happy hacking!"
#define     FW_PROMPT      "->"
#define     DUART_BASE    0x00D00000        // Base address of the mc68681
#define     DUART_IV_ADR  0x40              // Interupt vector address used for mc6861 
#define     CF_BASE       0x00E00000        // Base address for IDE CompactFlash

/* Some basic ASCII character definitions used by firmware/monitor */
#define CR              (char)0x0d
#define LF              (char)0x0a
#define BLANK           (char)0x20
#define BACKSPACE       (char)0x08
#define FW_HELP         (char)0x68
#define FW_READ         (char)0x72
#define FW_WRITE        (char)0x77
#define FW_BOOT         (char)0x62

#define DUART_IRQ_MASK  (char)0x02

/* Enums for i/o ports */
enum ioports {
    SER_A = 0,
    SER_B = 1
};


#endif