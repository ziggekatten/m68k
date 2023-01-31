/*
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Function prototypes for firmware boot
*/
#ifndef _MB68K_BOOT_H
#define _MB68K_BOOT_H

/* Prototype for external main call*/
void _fmain(void);

/* Entrypoint prototype. This function is the start of code execution after vectors are set */
void Reset_Handler(void);

/* Exception Handler prototypes for the MC680x0 CPUs*/
void BUS_ERROR_Handler(void);                                                              // Bus cycle couldn't complete properly.
void ADDRESS_ERROR_Handler(void)                __attribute__((alias("Generic_Handler"))); // Misaligned (odd) word or longword memory access.
void ILLEGAL_INSTRUCTION_Handler(void)          __attribute__((alias("Generic_Handler"))); // Tried executing an invalid opcode 
void INT_DIVIDE_BY_ZERO_Handler(void)           __attribute__((alias("Generic_Handler"))); // DIVUed or DIVSed by zero.
void CHK_Handler(void)                          __attribute__((alias("Generic_Handler"))); // CHK resulted in "out of bounds".
void TRAPV_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAPV with overflow flag set
void PRIVILEGE_VIOLATION_Handler(void)          __attribute__((alias("Generic_Handler"))); // Use of privileged instruction.
void TRACE_Handler(void)                        __attribute__((alias("Generic_Handler"))); // After each executed instruction when 68k is in trace mode (debugger function)
void LINE_1010_Handler(void)                    __attribute__((alias("Generic_Handler"))); // Line 1010 Emulator
void LINE_1111_Handler(void)                    __attribute__((alias("Generic_Handler"))); // Line 1111 Emulator
void FORMAT_ERROR_Handler(void)                 __attribute__((alias("Generic_Handler"))); // Format error (MC68010 Only)
void UNINITIALIZED_VECTOR_Handler(void)         __attribute__((alias("Generic_Handler"))); // Uninitialized Vector
void SPURIOUS_INTERRUPT_Handler(void)           __attribute__((alias("Generic_Handler"))); // Spurious Interrupt
void LEVEL1_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 1 Interrupt Autovector
void LEVEL2_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 2 Interrupt Autovector
void LEVEL3_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 3 Interrupt Autovector
void LEVEL4_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 4 Interrupt Autovector
void LEVEL5_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 5 Interrupt Autovector
void LEVEL6_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 6 Interrupt Autovector
void LEVEL7_AUTO_Handler(void)                  __attribute__((alias("Generic_Handler"))); // Level 7 Interrupt Autovector
void TRAP0_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #0 Instruction Vector
void TRAP1_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #1 Instruction Vector 
void TRAP2_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #2 Instruction Vector 
void TRAP3_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #3 Instruction Vector 
void TRAP4_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #4 Instruction Vector 
void TRAP5_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #5 Instruction Vector 
void TRAP6_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #6 Instruction Vector 
void TRAP7_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #7 Instruction Vector 
void TRAP8_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #8 Instruction Vector 
void TRAP9_Handler(void)                        __attribute__((alias("Generic_Handler"))); // TRAP #9 Instruction Vector 
void TRAP10_Handler(void)                       __attribute__((alias("Generic_Handler"))); // TRAP #10 Instruction Vector 
void TRAP11_Handler(void)                       __attribute__((alias("Generic_Handler"))); // TRAP #11 Instruction Vector 
void TRAP12_Handler(void)                       __attribute__((alias("Generic_Handler"))); // TRAP #12 Instruction Vector 
void TRAP13_Handler(void)                       __attribute__((alias("Generic_Handler"))); // TRAP #13 Instruction Vector 
void TRAP14_Handler(void)                       __attribute__((alias("Generic_Handler"))); // TRAP #14 Instruction Vector 
void TRAP15_Handler(void)                       __attribute__((alias("Generic_Handler"))); // TRAP #15 Instruction Vector
void FP_UNORDERD_COND_Handler(void)             __attribute__((alias("Generic_Handler"))); // FP Branch or Set on Unordered Condition  
void FP_INEXACT_RESULT_Handler(void)            __attribute__((alias("Generic_Handler"))); // FP Inexact Result
void FP_DIVIDE_BY_ZERO_Handler(void)            __attribute__((alias("Generic_Handler"))); // FP Divide by Zero
void FP_UNDERFLOW_Handler(void)                 __attribute__((alias("Generic_Handler"))); // FP Underflow
void FP_OPERAND_ERROR_Handler(void)             __attribute__((alias("Generic_Handler"))); // FP Operand Error
void FP_OVERFLOW_Handler(void)                  __attribute__((alias("Generic_Handler"))); // FP Overflow
void FP_SIGNAL_NAN_Handler(void)                __attribute__((alias("Generic_Handler"))); // FP Signaling NAN
void FP_UNIMPL_DATA_TYPE_Handler(void)          __attribute__((alias("Generic_Handler"))); // FP Unimplemented Data Type (Defined for MC68040) 
void MMU_CONFIG_ERROR_Handler(void)             __attribute__((alias("Generic_Handler"))); // MMU Configuration Error 
void MMU_ILLEGAL_OPERATION_Handler(void)        __attribute__((alias("Generic_Handler"))); // MMU Illegal Operation Error
void MMU_ACCESS_VIOLATION_Handler(void)         __attribute__((alias("Generic_Handler"))); // MMU Access Level Violation Error

#endif