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
    *DUART_IMR  = 0x00; // Disable interrupts
    /* *DUART_ACR  = 0x60; // set 115kbaud
    *DUART_CSRA = 0x66; // set 115kbaud
    *DUART_CUR  = 0x00; // set 115kbaud
    *DUART_CLR  = 0x02; // set 115kbaud */

    *DUART_CRA  = 0x10; // Reset MRA pointer
    *DUART_CRA  = 0x20; // Reset RX register
    *DUART_CRA  = 0x30; // Reset TX register
    *DUART_CRA  = 0x40; // Reset error
    
    *DUART_MR1A = 0x13; // RxRTS Disabled, 8 bits, No Parity
    *DUART_MR2A = 0x07; // Normal mode, CTS Disabled, 1 stop bit, no parity
    *DUART_MR1B = 0x13; // RxRTS Disabled, 8 bits, No Parity
    *DUART_MR2B = 0x07; // Normal mode, CTS Disabled, 1 stop bit, no parity
    *DUART_CSRA = 0xCC; // 9600 bps @ 3.6864MHz
    *DUART_CRA  = 0x05; // Enable TX and RX
    *DUART_IVR  = 0x40; // Set vector for IRQ (using IRQ5)
    *DUART_IMR  = 0x02; // Enable interupt on rx-ready




    enable_interrupts();       // Enable CPU interrupts

    /* Let us output some welcome stuff to console 
    TODO: Memory check would be nice before this and dump errors to terminal. But how to test memory without using it? Tricky stuff
    */

    
    /*    
    char memaddr[8];
    uint32_t addr = 0xa5b5c5d5;
    char * outp = itohexa(memaddr, addr);
    for (int i=0; i <= 9; i++) {
        serial_putchar(outp[i]);
    }
    */

    char *build_str = "Brocomp 68010 Generic Computer. Version:" __DATE__ " " __TIME__ "\r\nReleased under MIT license\r\nHappy hacking!\r\n->";
    printf(build_str);
    char *adr = "kalle";
    printf("Address: %p has value: %s\n", adr, adr );
    
    //uint8_t *t = DUART_RBA; 
    printf("Interrupt vector register IVR set to: %u\n", *DUART_IVR);
    printf("SRA set to: %u\n", *DUART_SRA);
    //printf("Recieve buffer register RBA set to: %u\n", *DUART_RBA);
    //printf("Recieve buffer register RBB set to: %u\n", *DUART_RBB);
    printf("MR1A set to: %u\n", *DUART_MR1A);
    printf("MR2A set to: %u\n", *DUART_MR2A);
    printf("ISR set to: %u\n", *DUART_ISR);
    uint16_t statusreg = get_sr();
    printf("Status register: %x\n", statusreg);
    
    while (1){

    };
}
