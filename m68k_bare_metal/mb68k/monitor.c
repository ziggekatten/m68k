/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * @brief Code for firmware monitor such as reading and writing to memory
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
#include "monitor.h"
#include "machine.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *fwhelp = HELP_H; 
#define DATA_ROW = "%#010x: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n";
static char *header = "\nAddress     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F \n"
                      "-----------------------------------------------------------\n";

void readmem(uint32_t baseadr) {
    //char h[16] = {"0","1","2","3","4","5","6","7","8","A","B","C","D","E","F"};
    printf("%s",header);
    volatile uint8_t *p = (uint8_t *)baseadr;       // Pointer to base address to read
    int rows;                                       // Rows to return. set in for loop
    for (rows = 0; rows < 20; rows++){
        printf("%#010x: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", (uint32_t)p, 
            *p, *(p+1), *(p+2), *(p+3),
            *(p+4), *(p+5), *(p+6), *(p+7),
            *(p+8), *(p+9), *(p+10), *(p+11),
            *(p+12), *(p+13), *(p+14), *(p+15)
            );
        p = p + 16;                                 // Increment address pointer
    } 
    printf("\n%s", prompt);
}

/* reset serial buffer. ToDo: handle selectable buffer */
void resetbuffer(serialstruct *buf) {
    memset(buf->buf, 0, sizeof(buf->buf));            // Reset input buffer completely!!! Otherwise bad things WILL happen....                
    buf->idx = 0;                                     // Reset buffer index
}

/* Pseudo parse function for incoming data from keyboard or serial communication 
* This will be an true tree parser at some point.... */
void parsecommand(serialstruct *buf) {
    switch (buf->buf[0]) {
        case FW_HELP:
            printf("%s\n%s", fwhelp, prompt);
            resetbuffer(buf);
            break;
        default:
            printf("Invalid command! Type 'h' for help.\b\e[K\n%s", prompt);
            readmem(0x1850);
            resetbuffer(buf);
            break;
        }
}
