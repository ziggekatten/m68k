/**
* @Author: Mats Brorson
* @Date: 2023-01-27
* 
* @Description: Functions to initialize serial communication
*/
#include "include/hwdefs.h"
#include "include/mc68681.h"
typedef unsigned long int u32_t;
typedef unsigned char u8_t;

/* prototypes for initializing Serial commmunication */
void init_serial(void)
{
/*
* TODO: add parameter for port A and B
*/
    u32_t volatile *ptrReset = (u32_t volatile *)DUART_CRA;       // pointer to the CRA register
    *ptrReset = (u8_t)0x20;                     // Reset reciever by setting value in CRA register
    /* delay should go here*/
    *ptrReset = (u8_t)0x30;                     // Reset transmitter by setting value in CRA register
    /* delay should go here*/
    *ptrReset = (u8_t)0x40;                     // Reset error status by setting value in CRA register
    /* delay should go here*/
    *ptrReset = (u8_t)0x10;                     // Reset Mode Register pointer to MR1
};

void flow_control(void)
{
    u32_t volatile *ptrFlowControl = (u32_t volatile *)DUART_MR1A;
    *ptrFlowControl = (u8_t)0x13;               // 8 data bits, no parity. First write goes into MR1A
    *ptrFlowControl = (u8_t)0x07;               //No flowcontrol, 1 stop bit Second write goes into MR2A
};

void baud_rate(void)
/*
* TODO: Add parameters for selection of baudrates
*/
{
    u32_t volatile *ptrBaudRate = (u32_t volatile *)DUART_CSRA;
    u32_t volatile *ptrBaudRateACR = (u32_t volatile *)DUART_ACR;
    *ptrBaudRate = (u8_t)0xCC;                   // Set speed to 19 200 buad in CSRA
    *ptrBaudRateACR = (u8_t)0x80;                // Set bit highest bit in Aux Control Register for 19 200
};

void enable_serial(void){
    u32_t volatile *ptrEnableSerial = (u32_t volatile *)DUART_CRA;
    u32_t volatile *ptrInterrupt = (u32_t volatile *)DUART_IMR;
    *ptrEnableSerial = (u8_t)0x05;                // Enable transmitter and reciever
    *ptrInterrupt = (u8_t)0x00;                // Disable interrupts for not
    
};