/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * @brief Functions to initialize and configure serial communication, timers and other 
 * features using Motorola MC68681 DUART at boot time, but also for enabling control in software, 
 * for example enabling port B, or changing speed, parity, flow control etc
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

#include <stdint.h>
#include "machine.h"
#include "mc68681.h"

/* Function for initializing serial commmunication
* TODO: Add parameters for selection of baudrates and port
*/
void serial_init(void)
{
    *DUART_IMR  = 0x00;         // Disable interrupts
    /* *DUART_ACR  = 0x60; // set 115kbaud
    *DUART_CSRA = 0x66; // set 115kbaud
    *DUART_CUR  = 0x00; // set 115kbaud
    *DUART_CLR  = 0x02; // set 115kbaud */

    *DUART_CRA  = 0x10;           // Reset MRA pointer
    *DUART_CRA  = 0x20;           // Reset RX register
    *DUART_CRA  = 0x30;           // Reset TX register
    *DUART_CRA  = 0x40;           // Reset error
    
    *DUART_MR1A = 0x13;           // RxRTS Disabled, 8 bits, No Parity
    *DUART_MR2A = 0x07;           // Normal mode, CTS Disabled, 1 stop bit, no parity
    *DUART_MR1B = 0x13;           // RxRTS Disabled, 8 bits, No Parity
    *DUART_MR2B = 0x07;           // Normal mode, CTS Disabled, 1 stop bit, no parity
    *DUART_CSRA = 0xCC;           // 9600 bps @ 3.6864MHz
    *DUART_CRA  = 0x05;           // Enable TX and RX
    *DUART_IVR  = DUART_IV_ADR;   // Set vector for IRQ (using IRQ5)
    *DUART_IMR  = DUART_IRQ_MASK; // Default value from machine.h
    
    //*DUART_CRA = (uint8_t)0x20;                                          // Reset reciever by setting value in CRA register
    /* delay should go here*/
    //*DUART_CRA = (uint8_t)0x30;                                          // Reset transmitter by setting value in CRA register
    /* delay should go here*/
    //*DUART_CRA = (uint8_t)0x40;                                          // Reset error status by setting value in CRA register
    /* delay should go here*/
    //*DUART_CRA = (uint8_t)0x10;                                          // Reset Mode Register pointer to MR1
};

/* Function for setting flow control
* TODO: Add parameters for selection of bits, parity, flowcontrol and port
*/
void serial_flow_control(void)
{
    *DUART_MR1A = (uint8_t)0x13;               // 8 data bits, no parity. First write goes into MR1A
    *DUART_MR1A = (uint8_t)0x07;               //No flowcontrol, 1 stop bit Second write goes into MR2A
};

/* Set baudrate
* TODO: Add parameters for selection of baudrates and port
*/
void serial_baud_rate(void)
{
    *DUART_CSRA = (uint8_t)0xCC;               // Set speed to 19 200 buad in CSRA
    *DUART_ACR = (uint8_t)0x80;                // Set bit highest bit in Aux Control Register for 19 200
};

/* Enable reciever and transmitter
* TODO: port as parameter
*/
void serial_enable(void)
{
    *DUART_CRA = (uint8_t)0x05;                // Enable transmitter and reciever
    *DUART_IMR = (uint8_t)0x00;                // Disable interrupts
    
};

/* This function to be run for setting Port A to default settings
* at boot for console access
*/
void serial_init_default_port(void)
{
    serial_init();
    serial_flow_control();
    serial_baud_rate();
    serial_enable();
};

/* Function for putting char to the DUART
*/
int serial_putchar(char ch)
{
    /* Create a pointer to the transmitter buffer
    * TODO: Handle port as param. Ensure buffer is not full?
    */

    /*Send the char*/
    *DUART_TBA = ch;
    return ch;
}

/* Function for getting char from the DUART
*/
char serial_getchar()
{
    /* Create a pointer to the recieve buffer
    * TODO: Handle port as param. Ensure buffer is not empty? 
    * Is buffer cleared when reading or do I need to clear byte?
    */

    /* Return the byte */
    //char x = (char)DUART_RBA;
    //return x;
    return 0;
}
void serial_putstr(char *inputbuf){
    for (int i = 0; inputbuf[i] != '\0'; i++) { 
        serial_putchar(inputbuf[i]);      
        }
}