/*
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Function prototypes to initialize and start serial communications, and
* configure timers and other features of the chip
*/
#ifndef _MB68K_MC68661_H
#define _MB68K_MC68681_H
#include "hwdefs.h"
#include <stdint.h>

/* 
* DUART register definition using a base addres from hardware header file and adds some offsets
* Depending on read or write, the use of register changes for some offsets!
*/
#define DUART_MR1A      ((volatile uint8_t *)DUART_BASE+0x00)  // Mode Register Port A. first read or write (MR1A)
#define DUART_SRA       ((volatile uint8_t *)DUART_BASE+0x02)  // Status Register A 
#define DUART_CSRA      ((volatile uint8_t *)DUART_BASE+0x02)  // Clock-Select Register A 
#define DUART_CRA       ((volatile uint8_t *)DUART_BASE+0x04)  // Command Register A. Remember to wait until command is done!!
#define DUART_RBA       ((volatile uint8_t *)DUART_BASE+0x06)  // Receive Buffer A 
#define DUART_TBA       ((volatile uint8_t *)DUART_BASE+0x06)  // Transmit Buffer A 
#define DUART_IPCR      ((volatile uint8_t *)DUART_BASE+0x08)  // Input Port Change Register 
#define DUART_ACR       ((volatile uint8_t *)DUART_BASE+0x08)  // Auxiliary Control Register 
#define DUART_ISR       ((volatile uint8_t *)DUART_BASE+0x0A)  // Interrupt Status Register 
#define DUART_IMR       ((volatile uint8_t *)DUART_BASE+0x0A)  // Interrupt Mask Register 
#define DUART_CUR       ((volatile uint8_t *)DUART_BASE+0x0C)  // Counter Mode: current MSB 
#define DUART_CTUR      ((volatile uint8_t *)DUART_BASE+0x0C)  // Counter/Timer upper reg 
#define DUART_CLR       ((volatile uint8_t *)DUART_BASE+0x0E)  // Counter Mode: current LSB 
#define DUART_CTLR      ((volatile uint8_t *)DUART_BASE+0x0E)  // Counter/Timer lower reg 
#define DUART_MR1B      ((volatile uint8_t *)DUART_BASE+0x10)  // Mode Register Port B. first read or write (MR1B) 
#define DUART_MR2B      ((volatile uint8_t *)DUART_BASE+0x10)  // Mode Register Port B. second read or write (MR2B) 
#define DUART_SRB       ((volatile uint8_t *)DUART_BASE+0x12)  // Status Register B 
#define DUART_CSRB      ((volatile uint8_t *)DUART_BASE+0x12)  // Clock-Select Register B 
#define DUART_CRB       ((volatile uint8_t *)DUART_BASE+0x14)  // Command Register B 
#define DUART_RBB       ((volatile uint8_t *)DUART_BASE+0x16)  // Receive Buffer B 
#define DUART_TBB       ((volatile uint8_t *)DUART_BASE+0x16)  // Transmit Buffer A 
#define DUART_IVR       ((volatile uint8_t *)DUART_BASE+0x18)  // Interrupt Vector Register 
#define DUART_IP        ((volatile uint8_t *)DUART_BASE+0x1A)  // Input Port 
#define DUART_OPCR      ((volatile uint8_t *)DUART_BASE+0x1A)  // Output Port Configuration Reg. 
#define DUART_STRTCC    ((volatile uint8_t *)DUART_BASE+0x1C)  // Start-Counter command 
#define DUART_OPRSET    ((volatile uint8_t *)DUART_BASE+0x1C)  // Output Port Reg, SET bits 
#define DUART_STOPCC    ((volatile uint8_t *)DUART_BASE+0x1E)  // Stop-Counter command 
#define DUART_OPRRST    ((volatile uint8_t *)DUART_BASE+0x1E)  // Output Port Reg, ReSeT bits


/* 
* prototype for initializing Serial commmunication function in DUART. Should
* probably should return something to indicate if it was successful
* TODO:
* prototypes for (and expose as symbols for those to be configurable in userspace later on)
* 1. Reset reciever, transmitter, error status, mode register pointer (CRA)
* 2. configure data bit, parity in the mode register (MR1A)
* 3. configure flow control ans stop bits in mode register (MR2A)
* 4. configure baud rate
* 5. enable Rx and Tx (CRA)
* 6. set ACR[7] = 0
* 7. disable interrupt
* Rmove dependencies to hwdefs in this header for reusability
*/
void serial_init_default_port(void);       // for initialize default settings at boot. In effect, running below functions
void serial_init(void);                    // Reset of chip
void serial_flow_control(void);            // Set up flow control
void serial_baud_rate(void);               // Set up baudrate
void serial_enable(void);                  // Enable tranciever and reciever

/* Function: serial_putc: Sends a char to the DUART
* arguments: char to output
* returns: int) 0 if all ok. 
*/
int serial_putchar(char data);

/* Function: serial_getc: Sends a char to the DUART 
* parameters: 
* returns: char from DUART buffer.
* TODO: Interrupt and handler to run this function?
*/
char serial_getchar();


#endif