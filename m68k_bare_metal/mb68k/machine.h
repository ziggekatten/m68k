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

#define     FW_MACHINE_ID "BroComp 68010 Generic Computer."
#define     FW_VERSION    "Version: " + __DATE__
#define     FW_AUTHOR     "Author: Mats Brorson"
#define     FW_LICENSE    "Released under MIT license. Happy hacking!"
#define     FW_PROMPT      "->"
#define     DUART_BASE    0x00D00001
#define     CF_BASE       0x00E00001

#endif