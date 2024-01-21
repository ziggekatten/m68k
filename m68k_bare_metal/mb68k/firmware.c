/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * @brief Base firmware for the BroCom m68k homebrew computer used to initialize
 * hardware and set up promt ready to execute code
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

#include "machine.h"
#include "mb68ksyscalls.h"
#include "mc68681.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* We need some basic stuff to determine if we are in firmware,
 * OS, or application mode. This is mainly for leaving control
 * of I/O devices to apropriate destination */
enum state {
    FW = 0,
    OS = 1,
    EASY68K = 2 
};

/* Initialize state to Firmware state */
enum state runstate = FW;   

/* Struct used for serial data stuff*/
typedef struct serialstruct{
    char buf[64];
    uint8_t idx;
} serialstruct;

/* Initialize data buffers for DUART */  
serialstruct serialdata_a;

/* Default fimware prompt */
const char *prompt = FW_PROMPT;

/* The glue function for libmetal printf using function in the MC68681 library*/
int putchar_(char c) {
    serial_putchar(c);
    return c;
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
            resetbuffer(buf);
            break;
        }

}

/* Serial port handler.
 * ToDo: handle both port A and B
 * ToDo: Handle state. Firmware, OS or Trap handler? */
void serialhandler(char port) {
    switch (port) {
        case 0:                                                             // First DUART port is console
            disable_interrupts();                                           // disable CPU interrupts until some logic is done
            if (serialdata_a.idx > sizeof(serialdata_a.buf)-1) {            // Buffer owerflow protection!
                serialdata_a.idx--;                                         // Decrement index
            }

            serialdata_a.buf[serialdata_a.idx] = *DUART_RBA;                // Get data from DUART RX port A into buffer
            if (serialdata_a.buf[serialdata_a.idx]== CR){                   // Check if we have an CR, and if so
                printf("%c", serialdata_a.buf[serialdata_a.idx]);           // Output char to console
                parsecommand(&serialdata_a);                                // We have pressed enter. Let us try interpret the command

            } else if (serialdata_a.buf[serialdata_a.idx] == BACKSPACE) {   // Handle backspace so we clear buffer and decrement index
                if (serialdata_a.idx !=0){                                  
                    printf("\b\e[K");                                       // Sending vt100 ESC-code to erase char in terminal
                    serialdata_a.buf[serialdata_a.idx] = 0;                 // Clear buffer
                    serialdata_a.idx--;                                     // Decrement index
                } 
                                            
            } else {
                printf("%c", serialdata_a.buf[serialdata_a.idx]);           // Output char to console
                serialdata_a.idx++;                                         // No enter, so we just increase index of buffer
            }
            enable_interrupts();                                            // Enable CPU interrupts again
            break;
        default:
            break;
    }
}


/* Firmware main */
int _fmain(void){

    serialdata_a.idx = 0;                           // initialize serial buffer index
    disable_interrupts();                         // Disable CPU interrupts
    serial_init();                                // Initialize DUART

    /*  Some welcome stuff */
    char *build_str = "Brocomp 68010 Generic Computer. Version:" __DATE__ " " __TIME__ "\r\nReleased under MIT license\r\nHappy hacking!";
    printf("%s\n%s", build_str, FW_PROMPT);

    enable_interrupts();                          // Enable CPU interrupts so we can get keyboard input and stuff

    while (1){

    };
}
