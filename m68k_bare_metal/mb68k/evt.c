#include <stdio.h>
#include <stdint.h>
#include "mc68681.h"
#include "machine.h"

/* 
* Exception handlers do not return a value, so they are void. 
* They also do not take any parameters. __attribute__((interrupt)) 
* tells the compiler to insert the correct return instruction, 
* rte instead of rts, when returning from an interrupt.
*/

void __attribute__((interrupt)) 
    ZeroDivide(void){

}

void __attribute__((interrupt))
    DUARTInterruptHandler(void){
    printf("%c", *DUART_RBA);
}

