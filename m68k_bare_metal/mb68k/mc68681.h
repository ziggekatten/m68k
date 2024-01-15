/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * 
 * @brief Function prototypes to initialize and start serial communications, and
 * configure timers and other features of the Motorola MC68681 chip.
 * 
 * @license The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef MB68K_MC68681_H_
#define MB68K_MC68681_H_
/* 
* DUART register definition using a base addres from hardware header file and adds some offsets
* Depending on read or write, the use of register changes for some offsets! Keep in mind two things:
    - Pointers, pointers, pointers....Using pure values in constructor as base for pointers in .c file fails miserably. Defining
        pointers in the header file seems to work. Must be my lack of C knowledge why this is. Spent hours debugging
        assembly output before finding that values was sent to registers as values and not as references until defining
        things as pointers in the header files.
    - Odd adressing is key as only lower 8 bits are connected
*/
#define DUART_MR1A      ((volatile uint8_t *)DUART_BASE+0x01)  // Mode Register Port A. first read or write (MR1A)
#define DUART_MR2A      ((volatile uint8_t *)DUART_BASE+0x01)  // Mode Register Port A. second read or write (MR1A)
#define DUART_SRA       ((volatile uint8_t *)DUART_BASE+0x03)  // Status Register A 
#define DUART_CSRA      ((volatile uint8_t *)DUART_BASE+0x03)  // Clock-Select Register A 
#define DUART_CRA       ((volatile uint8_t *)DUART_BASE+0x05)  // Command Register A. Remember to wait until command is done!!
#define DUART_RBA       ((volatile uint8_t *)DUART_BASE+0x07)  // Receive Buffer A 
#define DUART_TBA       ((volatile uint8_t *)DUART_BASE+0x07)  // Transmit Buffer A 
#define DUART_IPCR      ((volatile uint8_t *)DUART_BASE+0x09)  // Input Port Change Register 
#define DUART_ACR       ((volatile uint8_t *)DUART_BASE+0x09)  // Auxiliary Control Register 
#define DUART_ISR       ((volatile uint8_t *)DUART_BASE+0x0B)  // Interrupt Status Register 
#define DUART_IMR       ((volatile uint8_t *)DUART_BASE+0x0B)  // Interrupt Mask Register 
#define DUART_CUR       ((volatile uint8_t *)DUART_BASE+0x0D)  // Counter Mode: current MSB 
#define DUART_CTUR      ((volatile uint8_t *)DUART_BASE+0x0D)  // Counter/Timer upper reg 
#define DUART_CLR       ((volatile uint8_t *)DUART_BASE+0x0F)  // Counter Mode: current LSB 
#define DUART_CTLR      ((volatile uint8_t *)DUART_BASE+0x0F)  // Counter/Timer lower reg 
#define DUART_MR1B      ((volatile uint8_t *)DUART_BASE+0x11)  // Mode Register Port B. first read or write (MR1B) 
#define DUART_MR2B      ((volatile uint8_t *)DUART_BASE+0x11)  // Mode Register Port B. second read or write (MR2B) 
#define DUART_SRB       ((volatile uint8_t *)DUART_BASE+0x13)  // Status Register B 
#define DUART_CSRB      ((volatile uint8_t *)DUART_BASE+0x13)  // Clock-Select Register B 
#define DUART_CRB       ((volatile uint8_t *)DUART_BASE+0x15)  // Command Register B 
#define DUART_RBB       ((volatile uint8_t *)DUART_BASE+0x17)  // Receive Buffer B 
#define DUART_TBB       ((volatile uint8_t *)DUART_BASE+0x17)  // Transmit Buffer A 
#define DUART_IVR       ((volatile uint8_t *)DUART_BASE+0x19)  // Interrupt Vector Register 
#define DUART_IP        ((volatile uint8_t *)DUART_BASE+0x1B)  // Input Port 
#define DUART_OPCR      ((volatile uint8_t *)DUART_BASE+0x1B)  // Output Port Configuration Reg. 
#define DUART_STRTCC    ((volatile uint8_t *)DUART_BASE+0x1D)  // Start-Counter command 
#define DUART_OPRSET    ((volatile uint8_t *)DUART_BASE+0x1D)  // Output Port Reg, SET bits 
#define DUART_STOPCC    ((volatile uint8_t *)DUART_BASE+0x1F)  // Stop-Counter command 
#define DUART_OPRRST    ((volatile uint8_t *)DUART_BASE+0x1F)  // Output Port Reg, ReSeT bits

// MC68681 Command Numbers
#define CMD_RESET_MR			0x10
#define CMD_RESET_RX			0x20
#define CMD_RESET_TX			0x30
#define CMD_RESET_ERROR			0x40
#define CMD_ENABLE_TX_RX		0x05
#define CMD_ENABLE_RX			0x01
#define CMD_DISABLE_RX			0x02
#define CMD_ENABLE_TX			0x04
#define CMD_DISABLE_TX			0x08
#define CMD_START_BREAK			0x60
#define CMD_STOP_BREAK			0x70


// MC68681 Default Configuration Values
#define MR1A_MODE_A_REG_1_CONFIG	    0b10010011	// RxRTS Enabled, 8 bits, No Parity
#define MR2A_MODE_A_REG_2_CONFIG	    0b00000111	// Normal mode, CTS Disabled, 1 stop bit
#define CSRA_CLK_SELECT_REG_A_CONFIG	0b11001100	// 38400 bps @ 3.6864MHz
#define ACR_AUX_CONTROL_REG_CONFIG	    0b01111000	// Set1, External Clock / 16, IRQs disabled except IP3


// Status Register Bits (SRA/SRB)
#define SR_RECEIVED_BREAK		0x80
#define SR_FRAMING_ERROR		0x40
#define SR_PARITY_ERROR			0x20
#define SR_OVERRUN_ERROR		0x10
#define SR_TX_EMPTY			    0x08
#define SR_TX_READY			    0x04
#define SR_RX_FULL			    0x02
#define SR_RX_READY			    0x01

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

/* Function: serial_putchar: Sends a char to the DUART
* arguments: char to output
* returns: int) 0 if all ok. 
*/
int serial_putchar(char ch);

/* Function: serial_getchar: Gets a char to the DUART 
* parameters: 
* returns: char from DUART buffer.
* TODO: Interrupt and handler to run this function?
*/
char serial_getchar();

void serial_putstr(char *);

#endif
