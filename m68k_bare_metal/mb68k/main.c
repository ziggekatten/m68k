#include "machine.h"
#include "mb68ksyscalls.h"
#include "mc68681.h"
#include <stdbool.h>
#include <stdint.h>
int _fmain(void){
    disable_interrupts(true);       // Disable CPU interrupts

        /*
        1. disable CPU interrupts
        2. disable DUART interrupts
        3. initialize DUART
        4. disable rx
        5. hw and memtest
        6. enable CPU interrupts
        7. enable DUART interrupts
        6. enable RX
        */
    /* Test code for init of pysim DUART */
    *DUART_IVR  = 0x00; // Disable interrupts
    *DUART_CRA  = 0x10; // Reset MRA pointer
    *DUART_CRA  = 0x20; // Reset RX register
    *DUART_CRA  = 0x30; // Reset TX register
    *DUART_CRA  = 0x40; // Reset error
    
    *DUART_MR1A = 0x23; // RxRTS Disabled, 8 bits, No Parity
    *DUART_MR1A = 0x07; // Normal mode, CTS Disabled, 1 stop bit, no parity
    *DUART_CSRA = 0xCC; // 9600 bps @ 3.6864MHz
    *DUART_CRA  = 0x05; // Enable TX and RX

    /* Let us output some welcome stuff to console 
    TODO: Memory check would be nice before this and dump errors to terminal. But how to test memory without using it? Tricky stuff
    */

    
    /*    
    char memaddr[8];
    uint32_t addr = 0xa5b5c5d5;
    char * outp = itohexa(memaddr, addr);
    for (int i=0; i <= 9; i++) {
        serial_putchar(outp[i]);
    }
    */

    char *build_str = "Brocomp 68010 Generic Computer. Version:" __DATE__ " " __TIME__ "\r\nReleased under MIT license\r\nHappy hacking!\r\n->";
    
    serial_putstr(build_str);

    while (1){

    };
}
