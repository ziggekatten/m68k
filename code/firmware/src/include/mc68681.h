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
* DUART register definition using a base addres from hardware headerfile and adds some offsets
* Depending on read or write, the use of register changes for some offsets!
*/
#define DUART_MR1A      (DUART_BASE+0x00)  // Mode Register Port A. first read or write (MR1A)
#define DUART_SRA       (DUART_BASE+0x01)  // Status Register A 
#define DUART_CSRA      (DUART_BASE+0x01)  // Clock-Select Register A 
#define DUART_CRA       (DUART_BASE+0x02)  // Command Register A. Remember to wwait until command is done!!
#define DUART_RBA       (DUART_BASE+0x03)  // Receive Buffer A 
#define DUART_TBA       (DUART_BASE+0x03)  // Transmit Buffer A 
#define DUART_IPCR      (DUART_BASE+0x04)  // Input Port Change Register 
#define DUART_ACR       (DUART_BASE+0x04)  // Auxiliary Control Register 
#define DUART_ISR       (DUART_BASE+0x05)  // Interrupt Status Register 
#define DUART_IMR       (DUART_BASE+0x05)  // Interrupt Mask Register 
#define DUART_CUR       (DUART_BASE+0x06)  // Counter Mode: current MSB 
#define DUART_CTUR      (DUART_BASE+0x06)  // Counter/Timer upper reg 
#define DUART_CLR       (DUART_BASE+0x07)  // Counter Mode: current LSB 
#define DUART_CTLR      (DUART_BASE+0x07)  // Counter/Timer lower reg 
#define DUART_MR1B      (DUART_BASE+0x08)  // Mode Register Port B. first read or write (MR1B) 
#define DUART_MR2B      (DUART_BASE+0x08)  // Mode Register Port B. second read or write (MR2B) 
#define DUART_SRB       (DUART_BASE+0x09)  // Status Register B 
#define DUART_CSRB      (DUART_BASE+0x09)  // Clock-Select Register B 
#define DUART_CRB       (DUART_BASE+0x0A)  // Command Register B 
#define DUART_RBB       (DUART_BASE+0x0B)  // Receive Buffer B 
#define DUART_TBB       (DUART_BASE+0x0B)  // Transmit Buffer A 
#define DUART_IVR       (DUART_BASE+0x0C)  // Interrupt Vector Register 
#define DUART_IP        (DUART_BASE+0x0D)  // Input Port 
#define DUART_OPCR      (DUART_BASE+0x0D)  // Output Port Configuration Reg. 
#define DUART_STRTCC    (DUART_BASE+0x0E)  // Start-Counter command 
#define DUART_OPRSET    (DUART_BASE+0x0E)  // Output Port Reg, SET bits 
#define DUART_STOPCC    (DUART_BASE+0x0F)  // Stop-Counter command 
#define DUART_OPRRST    (DUART_BASE+0x0F)  // Output Port Reg, ReSeT bits


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
int serial_getchar();


#endif