/* 
* Author: Mats Brorson
* Date: 2023-01-27
*
* Motorola 68000/68010 vector table to be initialized at boot time
* 
*/
#include "platform.h"
#define RESERVED 0x00000000
typedef unsigned long int uint32_t;


//Exception handlers
void BUS_ERROR_HANDLER(void);                                                              // Bus cycle couldn't complete properly.
void ADDRESS_ERROR_HANDLER(void)                __attribute__((alias("GENERIC_HANDLER"))); // Misaligned (odd) word or longword memory access.
void ILLEGAL_INSTRUCTION_HANDLER(void)          __attribute__((alias("GENERIC_HANDLER"))); // Tried executing an invalid opcode 
void INT_DIVIDE_BY_ZERO_HANDLER(void)           __attribute__((alias("GENERIC_HANDLER"))); // DIVUed or DIVSed by zero.
void CHK_HANDLER(void)                          __attribute__((alias("GENERIC_HANDLER"))); // CHK resulted in "out of bounds".
void TRAPV_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAPV with overflow flag set
void PRIVILEGE_VIOLATION_HANDLER(void)          __attribute__((alias("GENERIC_HANDLER"))); // Use of privileged instruction.
void TRACE_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // After each executed instruction when 68k is in trace mode (debugger function)
void LINE_1010_HANDLER(void)                    __attribute__((alias("GENERIC_HANDLER"))); // Line 1010 Emulator
void LINE_1111_HANDLER(void)                    __attribute__((alias("GENERIC_HANDLER"))); // Line 1111 Emulator
void FORMAT_ERROR_HANDLER(void)                 __attribute__((alias("GENERIC_HANDLER"))); // Format error (MC68010 Only)
void UNINITIALIZED_VECTOR_HANDLER(void)         __attribute__((alias("GENERIC_HANDLER"))); // Uninitialized Vector
void SPURIOUS_INTERRUPT_HANDLER(void)           __attribute__((alias("GENERIC_HANDLER"))); // Spurious Interrupt
void LEVEL1_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 1 Interrupt Autovector
void LEVEL2_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 2 Interrupt Autovector
void LEVEL3_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 3 Interrupt Autovector
void LEVEL4_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 4 Interrupt Autovector
void LEVEL5_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 5 Interrupt Autovector
void LEVEL6_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 6 Interrupt Autovector
void LEVEL7_AUTO_HANDLER(void)                  __attribute__((alias("GENERIC_HANDLER"))); // Level 7 Interrupt Autovector
void TRAP0_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #0 Instruction Vector
void TRAP1_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #1 Instruction Vector 
void TRAP2_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #2 Instruction Vector 
void TRAP3_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #3 Instruction Vector 
void TRAP4_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #4 Instruction Vector 
void TRAP5_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #5 Instruction Vector 
void TRAP6_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #6 Instruction Vector 
void TRAP7_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #7 Instruction Vector 
void TRAP8_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #8 Instruction Vector 
void TRAP9_HANDLER(void)                        __attribute__((alias("GENERIC_HANDLER"))); // TRAP #9 Instruction Vector 
void TRAP10_HANDLER(void)                       __attribute__((alias("GENERIC_HANDLER"))); // TRAP #10 Instruction Vector 
void TRAP11_HANDLER(void)                       __attribute__((alias("GENERIC_HANDLER"))); // TRAP #11 Instruction Vector 
void TRAP12_HANDLER(void)                       __attribute__((alias("GENERIC_HANDLER"))); // TRAP #12 Instruction Vector 
void TRAP13_HANDLER(void)                       __attribute__((alias("GENERIC_HANDLER"))); // TRAP #13 Instruction Vector 
void TRAP14_HANDLER(void)                       __attribute__((alias("GENERIC_HANDLER"))); // TRAP #14 Instruction Vector 
void TRAP15_HANDLER(void)                       __attribute__((alias("GENERIC_HANDLER"))); // TRAP #15 Instruction Vector 


/*We add reset and exception vector table with pointers as an array. we place it in our 
* own .ipl-vectors section in .elf binary to ensure code ends up starting at 0x00000000
*/
uint32_t vectors[] __attribute__ ((section (".ipl-vector"))) = {
    STACK_POINTER,
    (uint32_t)&BUS_ERROR_HANDLER,
    (uint32_t)&ADDRESS_ERROR_HANDLER,
    (uint32_t)&ILLEGAL_INSTRUCTION_HANDLER,
    (uint32_t)&INT_DIVIDE_BY_ZERO_HANDLER,
    (uint32_t)&CHK_HANDLER,
    (uint32_t)&TRAPV_HANDLER,
    (uint32_t)&PRIVILEGE_VIOLATION_HANDLER,
    (uint32_t)&TRACE_HANDLER,
    (uint32_t)&LINE_1010_HANDLER,
    (uint32_t)&LINE_1111_HANDLER,
    RESERVED,
    RESERVED,
    (uint32_t)&FORMAT_ERROR_HANDLER,
    (uint32_t)&UNINITIALIZED_VECTOR_HANDLER,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    (uint32_t)&LEVEL1_AUTO_HANDLER,
    (uint32_t)&LEVEL2_AUTO_HANDLER, 
    (uint32_t)&LEVEL3_AUTO_HANDLER, 
    (uint32_t)&LEVEL4_AUTO_HANDLER, 
    (uint32_t)&LEVEL5_AUTO_HANDLER, 
    (uint32_t)&LEVEL6_AUTO_HANDLER, 
    (uint32_t)&LEVEL7_AUTO_HANDLER,
    (uint32_t)&TRAP0_HANDLER,
    (uint32_t)&TRAP1_HANDLER,
    (uint32_t)&TRAP2_HANDLER,
    (uint32_t)&TRAP3_HANDLER,
    (uint32_t)&TRAP4_HANDLER,
    (uint32_t)&TRAP5_HANDLER,
    (uint32_t)&TRAP6_HANDLER,
    (uint32_t)&TRAP7_HANDLER,
    (uint32_t)&TRAP8_HANDLER,
    (uint32_t)&TRAP9_HANDLER,
    (uint32_t)&TRAP10_HANDLER,
    (uint32_t)&TRAP11_HANDLER,
    (uint32_t)&TRAP12_HANDLER,
    (uint32_t)&TRAP13_HANDLER,
    (uint32_t)&TRAP14_HANDLER,
    (uint32_t)&TRAP15_HANDLER
};

void BUS_ERROR_HANDLER(void)
{

};

void GENERIC_HANDLER(void)
{
    while(1);
}