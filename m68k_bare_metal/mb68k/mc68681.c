/**
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Functions to initialize and configure serial communication, timers and other 
* features using Motorola MC68681 DUART at boot time, but also for enabling control in software, 
* for example enabling port B, or changing speed, parity, flow control etc
*/

#include <stdint.h>
#include "machine.h"
#include "mc68681.h"

/* Function for initializing serial commmunication
* TODO: Add parameters for selection of baudrates and port
*/
void serial_init(void)
{
    *DUART_CRA = (uint8_t)0x20;                                          // Reset reciever by setting value in CRA register
    /* delay should go here*/
    *DUART_CRA = (uint8_t)0x30;                                          // Reset transmitter by setting value in CRA register
    /* delay should go here*/
    *DUART_CRA = (uint8_t)0x40;                                          // Reset error status by setting value in CRA register
    /* delay should go here*/
    *DUART_CRA = (uint8_t)0x10;                                          // Reset Mode Register pointer to MR1
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