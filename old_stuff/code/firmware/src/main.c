/**
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Main program used for the built in firmware monitor features. This is an stepping stone into a future OS of
* some kind. But that is way in the future. All things here will be done using Supervisor mode
*/
#include <stdint.h>
#include "include/hwdefs.h"
#include "include/mc68681.h"
#include "include/utils.h"

void _fmain(void)
{
/* Plans and notes here are:
* - define layout of stuff
* - Avoid assembly as long as possible
* - Help function by typing ? (question mark) I need an parser...
* - define commands to be used. Base it on concept of opcode and operands? like "cd 0x300" to change to that address and thereafter commands
    are based from that adress? Memory filesystem-ish? Hmmmm.... treating addresses as directories based on words? Files a byte? Interesting...but is it effective?
* - execute program from adress
* - dump registers and memory/ROM contents. Needs assembly code....
* - change memory data(really?)
* - Breakpoints with traps or trace feature of CPU
* - diagnostics of hardware
* - change VBR. This might not be an good idea....
*/
    char *text = "SRA: ";
    char *nl = "\r\n->";
    char memaddr[8];
    serial_putstr(text);
    //uint8_t addr = (uint8_t)*DUART_SRA;
    uint8_t addr = DUART_SRA;
    char * outp = itohexa(memaddr, addr);
    serial_putstr(outp);
    serial_putstr(nl);

    text = "MR1A: ";
    serial_putstr(text);
    addr = DUART_MR1A;
    outp = itohexa(memaddr, addr);
    serial_putstr(outp);
    serial_putstr(nl);

    text = "MR2A: ";
    serial_putstr(text);
    addr = DUART_MR1A;
    outp = itohexa(memaddr, addr);
    serial_putstr(outp);
    serial_putstr(nl);

    text = "RBA: ";
    serial_putstr(text);
    addr = DUART_RBA;
    outp = itohexa(memaddr, addr);
    serial_putstr(outp);
    serial_putstr(nl);
    
    char *inputbuf = "Got a keypress!\r\n";
    while(1) {
        uint8_t test = DUART_RBA;
        if (test != 7) {
        for (int i = 0; inputbuf[i] != '\0'; i++) { 
            serial_putchar(inputbuf[i]);
            //if (DUART_SRA == 0x00) {
            //    inputbuf = DUART_RBA;
            //    serial_putchar(*inputbuf);         
            } 
        }
    }
}