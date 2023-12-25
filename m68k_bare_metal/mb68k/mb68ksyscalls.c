/*
* @Author: Mats Brorson
* @Date: 2023-11-27
* 
* @Description: Syscalls that have to be
* done by using assembler (SR/SP-operations)
*/

#include <stdbool.h>
#include "mb68ksyscalls.h"

// Enables or disables interrupts   
void set_interrupts(bool enabled) {
    if (enabled) {
        /*  Set minimum interupt = 0
        * The output of bitwise AND is 1 if the corresponding bits of two operands is 1.
        * If either bit of an operand is 0, the result of corresponding bit is evaluated to 0.
        */
        asm("and.w #0xF8FF, %sr");
    } else {
        /* Set minimum interrupt = 7
        * The output of bitwise OR is 1 if at least one corresponding bit of two operands is 1.
        */
        asm("or.w #0x700, %sr");
    }

}