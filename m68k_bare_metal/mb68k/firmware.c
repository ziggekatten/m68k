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

/* The glue function for libmetal printf */
int putchar_(char buf) {
    serial_putchar(buf);
    return 0;
}


int _fmain(void){
    disable_interrupts();       // Disable CPU interrupts

        /*
        1. disable CPU interrupts
        2. disable DUART interrupts
        3. initialize DUART
        4. disable rx
        5. hw and memtest
        6. enable CPU interrupts
        7. enable DUART interrupts
        6. enable RX
        */
    /* Test code for init of pysim DUART */
    serial_init();              // Initialize DUART

    enable_interrupts();        // Enable CPU interrupts

    // Some welcome stuff
    char *build_str = "Brocomp 68010 Generic Computer. Version:" __DATE__ " " __TIME__ "\r\nReleased under MIT license\r\nHappy hacking!\r\n->";
    printf(build_str);

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
