/**
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Functions to initialize and configure serial communication, timers and other 
* features using Motorola MC68681 DUART at boot time, but also for enabling control in software, 
* for examnple enabling port B, or changing speedd, parity, flow control etc
*/
#include <stdint.h>
#include "include/hwdefs.h"
#include "include/mc68681.h"

/* Functions for initializing serial commmunication */
void serial_init(void)
{
/*
* TODO: add parameter for port A and B
*/
    uint32_t volatile *ptrReset = (uint32_t volatile *)DUART_CRA;       // pointer to the CRA register
    *ptrReset = (uint8_t)0x20;                     // Reset reciever by setting value in CRA register
    /* delay should go here*/
    *ptrReset = (uint8_t)0x30;                     // Reset transmitter by setting value in CRA register
    /* delay should go here*/
    *ptrReset = (uint8_t)0x40;                     // Reset error status by setting value in CRA register
    /* delay should go here*/
    *ptrReset = (uint8_t)0x10;                     // Reset Mode Register pointer to MR1
};

void serial_flow_control(void)
/*
* TODO: Add parameters for selection of baudrates
*/
{
    uint32_t volatile *ptrFlowControl = (uint32_t volatile *)DUART_MR1A;
    *ptrFlowControl = (uint8_t)0x13;               // 8 data bits, no parity. First write goes into MR1A
    *ptrFlowControl = (uint8_t)0x07;               //No flowcontrol, 1 stop bit Second write goes into MR2A
};

void serial_baud_rate(void)
/*
* TODO: Add parameters for selection of baudrates
*/
{
    uint32_t volatile *ptrBaudRate = (uint32_t volatile *)DUART_CSRA;
    uint32_t volatile *ptrBaudRateACR = (uint32_t volatile *)DUART_ACR;
    *ptrBaudRate = (uint8_t)0xCC;                   // Set speed to 19 200 buad in CSRA
    *ptrBaudRateACR = (uint8_t)0x80;                // Set bit highest bit in Aux Control Register for 19 200
};

void serial_enable(void)
{
    uint32_t volatile *ptrEnableSerial = (uint32_t volatile *)DUART_CRA;
    uint32_t volatile *ptrInterrupt = (uint32_t volatile *)DUART_IMR;
    *ptrEnableSerial = (uint8_t)0x05;                // Enable transmitter and reciever
    *ptrInterrupt = (uint8_t)0x00;                // Disable interrupts for not
    
};

/* This function to be run for setting Port A to default settings at boot for console access */
void serial_init_default_port(void)
{
    serial_init();
    serial_flow_control();
    serial_baud_rate();
    serial_flow_control();
};

/* Put char to the DUART*/
int serial_putchar(char data)
{
    /* Create a pointer to the transmitter buffer
    * TODO: ENsure buffer is not full?
    */
    uint32_t volatile *ptrBuffer = (uint32_t volatile *)DUART_TBA;

    /*Send the char*/
    *ptrBuffer = data;
    return 0;
};

/* Get char from the DUART */
int serial_getchar(void)
{
    return 0;
};
