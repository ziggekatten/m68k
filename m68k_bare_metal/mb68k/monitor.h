/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * @brief Prototypes firmware monitor such as reading and writing to memory
 *
 *
 * @license The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef MB68K_MONITOR_H_
#define MB68K_MONITOR_H_
#include "firmware.h"

/* Monitor commands*/
#define FW_HELP         (char)0x68
#define FW_READ         (char)0x72
#define FW_WRITE        (char)0x77
#define FW_BOOT         (char)0x62
#define FW_BYTE         (char)0x62
#define FW_WORD         (char)0x77
#define FW_LONG         (char)0x6C

/* Monitor help*/
#define HELP_H          "\n'h'. Displays this help\n" \
                        "'r' <address>. Displays memory starting at closest even address\n" \
                        "'w' <b|w|l> <value> <address>. Writes an byte/word/longword at address\n" \
                        "'e' <address>. Start execution of code at address"

/* Monitor header for reading memory*/
#define READ_MEM_HEADER "\nAddress     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F \n" \
                        "-----------------------------------------------------------\n"                        


/* Prototype for parsing commands*/
void parsecommand(serialstruct*);

#endif