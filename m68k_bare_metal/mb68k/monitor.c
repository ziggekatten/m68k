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
#include "firmware.h"
#include "machine.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readmem() {
    //char h[16] = {"0","1","2","3","4","5","6","7","8","A","B","C","D","E","F"};
    
    uint32_t baseadr = 0x1850;
    printf("\nAddress   | 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F \n");
    printf("-----------------------------------------------------------\n");

    int rows;                                       // rows to return
    int byte = 0;                                   // Byte counter
    char b[320];                                    // Array to store all bytes 20 rows times 16 bytes
    int i;
    for (i = 0; i < 320; i++){
        b[i] = *((volatile uint8_t *)baseadr+i);
    }
    i = 0; 
    for (rows = 0; rows < 20; rows++){
        printf("%#010x: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", baseadr+byte, 
            b[byte], b[byte+1], b[byte+2], b[byte+3],
            b[byte+4], b[byte+5], b[byte+6], b[byte+7],
            b[byte+8], b[byte+9], b[byte+10], b[byte+11],
            b[byte+12], b[byte+13], b[byte+14], b[byte+15]
            );
        byte = byte + 16;                           // Increment by 16 bytes
    } 
    printf("\n%s", prompt);

    /* this works!
    char b[320];
    int i;
    for (i = 0; i < 32; i++) {
        char t = *((volatile uint8_t *)baseadr+i);
        b[i] = t;
        printf("%02x %02x\n ", t, b[i]);
    } 
    printf("\n%s", prompt);
    char* test = "9";
    printf("This represents: %02x",atoi(test)); */

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
            printf("Help goes here...\n%s", prompt);
            resetbuffer(buf);
            break;
        default:
            printf("Invalid command! Type 'h' for help.\b\e[K\n%s", prompt);
            readmem();
            resetbuffer(buf);
            break;
        }
}
