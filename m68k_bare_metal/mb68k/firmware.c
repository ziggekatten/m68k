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

/* The glue function for libmetal printf */
int putchar_(char c) {
    serial_putchar(c);
    return c;
}

/* Set serial input buffer and index to initial value */
uint8_t ser_buf_idx = 0;
char ser_buf[64];

/* Default fimware prompt */
const char *prompt = FW_PROMPT;

/* Parse function for incoming data from keyboard or serial communication*/
void ParseCommand() {
    switch (ser_buf[0]) {
        case FW_HELP:
            printf("Help goes here...\n%s", prompt);
            memset(ser_buf, 0, sizeof(ser_buf));    // Reset input buffer completely!!! Otherwise bad things WILL happen....                
            ser_buf_idx = 0;                        // Reset buffer index
            break;
        default:
            printf("Invalid command! Type 'h' for help.\n%s", prompt);
            memset(ser_buf, 0, sizeof(ser_buf));
            ser_buf_idx = 0;
        }

}

/* Keyboard handler used by interrupt service routine for serial PORTA*/
void KeyboardHandler(char character) {
    ser_buf[ser_buf_idx] = character;
    if (character == CR){
        ParseCommand();
    } else {
        ser_buf_idx++;
    }
}

int _fmain(void){
    disable_interrupts();       // Disable CPU interrupts

    serial_init();              // Initialize DUART

    /*  Some welcome stuff */
    char *build_str = "Brocomp 68010 Generic Computer. Version:" __DATE__ " " __TIME__ "\r\nReleased under MIT license\r\nHappy hacking!";
    printf("%s\n%s", build_str, FW_PROMPT);

    enable_interrupts();        // Enable CPU interrupts so we can get keyboard input and stuff


    //char *adr = "kalle";
    //printf("Address: %p has value: %s\n", adr, adr );
    
    //uint8_t *t = DUART_RBA; 
    //printf("Interrupt vector register IVR set to: %u\n", *DUART_IVR);
    //printf("SRA set to: %u\n", *DUART_SRA);
    //printf("MR1A set to: %u\n", *DUART_MR1A);
    //printf("MR2A set to: %u\n", *DUART_MR2A);
    //printf("ISR set to: %u\n", *DUART_ISR);
    //uint16_t statusreg = get_sr();
    //printf("Status register: %x\n", statusreg);
    
    while (1){
        
    };
}
