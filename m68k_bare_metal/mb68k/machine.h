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
#define     DUART_BASE    0x00D00000
#define     DUART_IV_ADR  0x40
#define     CF_BASE       0x00E00000

/* Some basic ASCII character definitions */
#define CR              (char)0x0d
#define LF              (char)0x0a
#define BLANK           (char)0x20
#define FW_HELP         (char)0x68
#define FW_READ         (char)0x72
#define FW_WRITE        (char)0x77
#define FW_BOOT         (char)0x62


/* Enums for various stuff */



/* Global buffer for basic firmware serial input */
extern char ser_buf[64];
extern uint8_t ser_buf_idx;





#endif