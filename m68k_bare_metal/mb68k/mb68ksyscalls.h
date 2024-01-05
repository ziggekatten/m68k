/*
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Function prototypes for syscalls that have to be
* done by using assembler
*/
#include <stdbool.h>
#ifndef MB68K_SYSCALLS_H_
#define MB68K_SYSCALLS_H_

void disable_interrupts(bool enabled);

#endif
