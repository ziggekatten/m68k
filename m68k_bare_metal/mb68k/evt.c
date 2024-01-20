/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * @brief Interrupt and exception vector code for the BroComp mc68010
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

#include <stdio.h>
#include <stdint.h>
#include "mc68681.h"
#include "machine.h"
#include "firmware.h"

/* 
* Exception handlers do not return a value, so they are void. 
* They also do not take any parameters. __attribute__((interrupt)) 
* tells the compiler to insert the correct return instruction, 
* rte instead of rts, when returning from an interrupt.
*/

void __attribute__((interrupt)) ZeroDivide(void){

}

/* IRQ5 is used for the duart, and we have chosen to use vector 64 dec (40 hex)
 * See: machine.h and platform.ld
 */
void __attribute__((interrupt)) DUARTInterruptHandler(void) {
    /* We first need to check what is causing the interrupt
     * This is done by checking the ISR register and AND it 
     * with the value set in the IMR register to know what fired the interrupt
    */
    char isr = *DUART_ISR & 0x02;   // Bitwise AND with defined Interrupt mask
    switch (isr) {
        case 2:                     // rx ready port A is source of interrupt
            serialhandler();        // call serial handler. ToDo: define port that called interrupt with call to function
            break;
        default:
            break;
    }

}
