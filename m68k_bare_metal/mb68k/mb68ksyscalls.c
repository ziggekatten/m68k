/*
* @Author: Mats Brorson
* @Date: 2023-11-27
* 
* @Description: Syscalls that have to be
* done by using assembler (SR/SP-operations) or gluelogic towards
* libmetal and other C-libraries
*/

#include <stdbool.h>
#include <stdint.h>

// Enables or disables interrupts   
void disable_interrupts() {

    /* Set minimum interrupt = 7
    * The output of bitwise OR is 1 if at least one corresponding bit of two operands is 1.
    */
    asm("or.w #0x700, %sr");

}

void enable_interrupts() {
    /*  Set minimum interupt = 0
    * The output of bitwise AND is 1 if the corresponding bits of two operands is 1.
    * If either bit of an operand is 0, the result of corresponding bit is evaluated to 0.
    */
    asm("and.w #0xF8FF, %sr");

}

