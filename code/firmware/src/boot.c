/** 
* @Author: Mats Brorson
* @Date: 2023-01-27
*
* @Description: Motorola 68000/68010 vector table and reset Handler to be initialized at boot time, and act as entrypoint
* for code execution. An special .elf section(.ipl-section) to be used by linker to place the 32-bit addresses for entrypoint 
* at the correct place.
*/

#include "hwdefs.h"
#define RESERVED 0 // Set all reserved vectors to zero
#define USER_DEFINED 0 // Set all user definable vectors to 0
typedef unsigned long int uint32_t;

/* Symbols created by linker to be used for copying .data to correct addresses i RAM and clearing .bss */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;


// Main prototype
int main(void);

/* Entrypoint prototype. This function is the start of code execution after vectors are set */
void Reset_Handler(void);

/* Exception Handler prototypes */
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

/*We add reset and exception vector table with pointers as an array. we place it in our 
* own .ipl-vectors section in .elf binary to ensure code ends up starting at 0x00000000
*/
uint32_t vectors[] __attribute__ ((section (".ipl_vector"))) = {
    STACK_POINTER,
    (uint32_t)&Reset_Handler,
    (uint32_t)&BUS_ERROR_Handler,
    (uint32_t)&ADDRESS_ERROR_Handler,
    (uint32_t)&ILLEGAL_INSTRUCTION_Handler,
    (uint32_t)&INT_DIVIDE_BY_ZERO_Handler,
    (uint32_t)&CHK_Handler,
    (uint32_t)&TRAPV_Handler,
    (uint32_t)&PRIVILEGE_VIOLATION_Handler,
    (uint32_t)&TRACE_Handler,
    (uint32_t)&LINE_1010_Handler,
    (uint32_t)&LINE_1111_Handler,
    RESERVED,
    RESERVED,
    (uint32_t)&FORMAT_ERROR_Handler,
    (uint32_t)&UNINITIALIZED_VECTOR_Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    (uint32_t)&SPURIOUS_INTERRUPT_Handler,
    (uint32_t)&LEVEL1_AUTO_Handler,
    (uint32_t)&LEVEL2_AUTO_Handler, 
    (uint32_t)&LEVEL3_AUTO_Handler, 
    (uint32_t)&LEVEL4_AUTO_Handler, 
    (uint32_t)&LEVEL5_AUTO_Handler, 
    (uint32_t)&LEVEL6_AUTO_Handler, 
    (uint32_t)&LEVEL7_AUTO_Handler,
    (uint32_t)&TRAP0_Handler,
    (uint32_t)&TRAP1_Handler,
    (uint32_t)&TRAP2_Handler,
    (uint32_t)&TRAP3_Handler,
    (uint32_t)&TRAP4_Handler,
    (uint32_t)&TRAP5_Handler,
    (uint32_t)&TRAP6_Handler,
    (uint32_t)&TRAP7_Handler,
    (uint32_t)&TRAP8_Handler,
    (uint32_t)&TRAP9_Handler,
    (uint32_t)&TRAP10_Handler,
    (uint32_t)&TRAP11_Handler,
    (uint32_t)&TRAP12_Handler,
    (uint32_t)&TRAP13_Handler,
    (uint32_t)&TRAP14_Handler,
    (uint32_t)&TRAP15_Handler,
    (uint32_t)&FP_UNORDERD_COND_Handler,
    (uint32_t)&FP_INEXACT_RESULT_Handler,
    (uint32_t)&FP_DIVIDE_BY_ZERO_Handler,
    (uint32_t)&FP_UNDERFLOW_Handler,
    (uint32_t)&FP_OPERAND_ERROR_Handler,
    (uint32_t)&FP_OVERFLOW_Handler,
    (uint32_t)&FP_SIGNAL_NAN_Handler,
    (uint32_t)&FP_UNIMPL_DATA_TYPE_Handler,
    (uint32_t)&MMU_CONFIG_ERROR_Handler,
    (uint32_t)&MMU_ILLEGAL_OPERATION_Handler,
    (uint32_t)&MMU_ACCESS_VIOLATION_Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED,
    USER_DEFINED
};

/* bus error handler*/
void BUS_ERROR_Handler(void)
{
    while(1);
}

/* Generic exception handler */
void Generic_Handler(void)
{
    while(1);
}

/* This function is the entrypoint of execution and it's address is set on boot at memory location: 0x00000004 */
void Reset_Handler(void)
{
	/* copy .data section to RAM */
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata; // gets the size of .data section
 	uint32_t *ptrDestination = (uint32_t*)&_sdata; //ram
	uint32_t *ptrSource = (uint32_t*)&_la_data; //flash

	for(uint32_t i =0 ; i < size ; i++)
	{
		*ptrDestination++ = *ptrSource++;
	}

	/* Zero out the .bss section in RAM */
	size = (uint32_t)&_ebss - (uint32_t)&_sbss; // Gets the size of .bss
 	ptrDestination = (uint32_t*)&_sbss;
    
	for(uint32_t i =0 ; i < size ; i++)
	{
		*ptrDestination++ = 0;
	}   

    /* Then execute the main function linked with this file (will be overwritten by 
    * linker as we only have the prototype here), and not the funcction itself */
    main();

    /* Just in case main terminates */
    while(1);

}
