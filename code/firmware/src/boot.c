/** 
* @Author: Mats Brorson
* @Date: 2023-01-27
*
* @Description: Motorola 68000/68010 vector table and reset Handler to be initialized at boot time, and act as entrypoint
* for code execution. An special .elf section(.ipl-section) to be used by linker to place the 32-bit addresses for entrypoint 
* at the correct place.
*/
#include <stdint.h>
#include "include/hwdefs.h"
#include "include/mc68681.h"
#include "include/boot.h"
#define RESERVED 0 // Set all reserved vectors to zero
#define USER_DEFINED 0 // Set all user definable vectors to 0

/* Symbols created by linker to be used for copying .data to correct addresses in RAM and clearing .bss */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;


/* We add reset and exception vector table with pointers as an array. we place it in our 
* own .ipl-vectors section in .elf binary to ensure code ends up starting at 0x00000000
* by relying on linker script
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
};

/* Generic exception handler */
void Generic_Handler(void)
{
    while(1);
};

/* This function is the entrypoint of execution and it's address is set on boot
* at memory location: 0x00000004 
*/
void Reset_Handler(void)
{
	/* copy .data section to RAM */
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;          // Gets the size of .data section
 	uint32_t *ptrDestination = (uint32_t*)&_sdata;                  // ram
	uint32_t *ptrSource = (uint32_t*)&_la_data;                     // flash

	for(uint32_t i =0 ; i < size ; i++)
	{
		*ptrDestination++ = *ptrSource++;
	}

	/* Zero out the .bss section in RAM */
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;                     // Gets the size of .bss
 	ptrDestination = (uint32_t*)&_sbss;
    
	for(uint32_t i = 0; i < size ; i++)
	{
		*ptrDestination++ = 0;                                      // Zero out uninitialized values
	}   

    /* initialize Port A at 9600 baud, 8 databits, 1 stop bit, no parity, no flow control 
    * TODO: Parameterize this
    */

    //serial_init_default_port();
    
    
    /* Test code for init of sim68000 DUART */
    *DUART_CRA  = 0x10;
    *DUART_MR1A = 0x23;
    *DUART_MR1A = 0x07;
    *DUART_CSRA = 0xBB;
    *DUART_CRA  = 0x05;

    /* Let us output some welcome stuff to console 
    TODO: Memory check would be nice before this and dump errors to terminal. But how to test memory without using it? Tricky stuff
    */
    const char *build_str = "Brocomp 68010 Generic Computer. Version: " FIRMWARE_VERSION_MAJOR "." FIRMWARE_VERSION_MINOR " " __DATE__ " " __TIME__ "\r\nReleased under MIT license\r\nHappy hacking!\r\n->";
    int i = 0;
        while (build_str[i] != '\0') {          /* Stop looping when we reach the null-character. */
         serial_putchar(build_str[i]);          /* Print each character of the string. */
        i++;
    } 
    
    /* 
    * Then execute the main function linked with this file (will be handled by 
    * linker) which will me the place for firmware features 
    */
    _fmain();

    /* Just in case main terminates */
    while(1);

};
