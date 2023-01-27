/* 
Author: Mats Brorson
Date: 2023-01-27

Motorola 68000/68010 vector table to be initialized att boot time

*/
#include "platform.h"

//Exception handlers
void BUS_ERROR_HANDLER(void);

//Reset vectors att inital boot as an array. we place it in our own .ipl-vectors section in .elf binary
unsigned long int vectors[] __attribute__ ((section (".ipl-vector"))) = {
    STACK_POINTER
};

void BUS_ERROR_HANDLER(void)
{

};

void GENERIC_HANDLER(void)
{
    while(1);
}