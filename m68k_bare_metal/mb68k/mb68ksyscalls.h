/*
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Function prototypes for syscalls that have to be
* done by using assembler
*/
#include <stdbool.h>
#include <stdint.h>
#ifndef MB68K_SYSCALLS_H_
#define MB68K_SYSCALLS_H_

void disable_interrupts();
void enable_interrupts();

static inline uint16_t get_sr() {
    uint16_t result;
    __asm__ volatile (
        "move.w %%sr, %0"
        : "=d" (result)
        :
        : "memory"
    );
    return result;
}
#endif
