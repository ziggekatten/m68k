#include <Arduino.h>
#include <68681.h>

  /* We need to define the following for doing DUART testing:
  * 1. An 4-bit address bus on a port or paralell write to simulate memory mapped registers WRITE (PORTF. Pin 54-57)
  * 2. An 8-bit data bus, on port for paralell READ and WRITE (PORTK. Pin 62-69)
  * 3. Monitoring of 68681 interrupt: INPUT (pull up/downs??) Pin 22
  * 4. Monitoring of 68681 DTACKN to see if DTACK is asserted when writing to control registers (pull up 1k2 ohm) Pin 23
  * 5. A reset pin (active low?) Pin 24
  * 6. An read/write pin Pin 25
  * 7. AN button connected to interrupt pin 2 to step through code
  */

#define DTACK 3                            // DTACK interrup input pin used to catch DTACK
#define CS 24                              // Chip select. This is the way to add cycles to the chip
#define RW 25                              // Read/Write pin
#define STEP 2                             // A interrupt pin used with button to step through code
#define RESET 26                           // Chip reset pin

const byte DUART_BASE   =B0000;             // DUART base address 
const byte DUART_MR1A   =DUART_BASE+B0000;  // Mode Register Port A. first read or write (MR1A)
const byte DUART_SRA    =DUART_BASE+B0001;  // Status Register A 
const byte DUART_CSRA   =DUART_BASE+B0001;  // Clock-Select Register A 
const byte DUART_CRA    =DUART_BASE+B0010;  // Command Register A. Remember to wwait until command is done!!
const byte DUART_RBA    =DUART_BASE+B0011;  // Receive Buffer A 
const byte DUART_TBA    =DUART_BASE+B0011;  // Transmit Buffer A 
const byte DUART_IPCR   =DUART_BASE+B0100;  // Input Port Change Register 
const byte DUART_ACR    =DUART_BASE+B0100;  // Auxiliary Control Register 
const byte DUART_ISR    =DUART_BASE+B0101;  // Interrupt Status Register 
const byte DUART_IMR    =DUART_BASE+B0101;  // Interrupt Mask Register 
const byte DUART_CUR    =DUART_BASE+B0110;  // Counter Mode: current MSB 
const byte DUART_CTUR   =DUART_BASE+B0110;  // Counter/Timer upper reg 
const byte DUART_CLR    =DUART_BASE+B0111;  // Counter Mode: current LSB 
const byte DUART_CTLR   =DUART_BASE+B0111;  // Counter/Timer lower reg 
const byte DUART_MR1B   =DUART_BASE+B1000;  // Mode Register Port B. first read or write (MR1B) 
const byte DUART_MR2B   =DUART_BASE+B1000;  // Mode Register Port B. second read or write (MR2B) 
const byte DUART_SRB    =DUART_BASE+B1001;  // Status Register B 
const byte DUART_CSRB   =DUART_BASE+B1001;  // Clock-Select Register B 
const byte DUART_CRB    =DUART_BASE+B1010;  // Command Register B 
const byte DUART_RBB    =DUART_BASE+B1011;  // Receive Buffer B 
const byte DUART_TBB    =DUART_BASE+B1011;  // Transmit Buffer A 
const byte DUART_IVR    =DUART_BASE+B1100;  // Interrupt Vector Register 
const byte DUART_IP     =DUART_BASE+B1101;  // Input Port 
const byte DUART_OPCR   =DUART_BASE+B1101;  // Output Port Configuration Reg. 
const byte DUART_STRTCC =DUART_BASE+B1110;  // Start-Counter command 
const byte DUART_OPRSET =DUART_BASE+B1110;  // Output Port Reg, SET bits 
const byte DUART_STOPCC =DUART_BASE+B1111;  // Stop-Counter command 
const byte DUART_OPRRST =DUART_BASE+B1111;  // Output Port Reg, ReSeT bits

/*
* Global variable to hold at witch state we are in when stepping throug code
*/
uint8_t step_pointer = 0;
uint8_t dtackstate = 0;

void setup() {
  /* Set the CS pin to OUTPUT and start at HIGH*/
  pinMode(CS,OUTPUT);
  digitalWrite(CS, HIGH);

  /* Prepare reet pin */
  pinMode(RESET,OUTPUT);
  digitalWrite(RESET,HIGH);

   
  /* Now we set the pin for reading DTACKN status*/
  pinMode(DTACK,INPUT);
  attachInterrupt(digitalPinToInterrupt(DTACK), dtackfunction, FALLING);
 
  /* Set adress and databus to output*/                                                        
  DDRF = B11111111;
  PORTF = B00000000;
  DDRK = B11111111;
  PORTK = B00000000;  
  
  /* set up serial feedback */
  Serial.begin(9600);
  Serial.print("Starting up....\n");
}

void loop() {
  /* We need to define some use cases her that we can trace in the serial monitor.
  * This means that we need to use Serial.input() to be able to step through things,
  * and read values from the bus as well as data registers. Tricky stuff
  */
  Serial.println("Enter DUART command:");
  while (Serial.available() == 0) {}     //wait for data available
  String command = Serial.readString();  //read until timeout
  command.trim();                        // remove any \r \n whitespace at the end of the String

  
  if (command == "init") {
    duart_init();
    } else if (command == "flow"){
      serial_flow_control();
    } else if (command == "baud"){
      serial_baud_rate();
    } else if (command == "enable"){
      serial_enable();
    } else if (command == "writechar"){
      print_char();
    } else if (command == "runall"){
      duart_init();
      serial_flow_control();
      serial_baud_rate();
      serial_flow_control();
    } else {
      Serial.println("Invalid command");  
    }
  }

/* Function for initializing DUART serial commmunication */
void duart_init(void) {
  Serial.print("Initializing DUART...\n");
  
  /* Reset hard on pin */
  digitalWrite(RESET,LOW);
  delay(1000);
  digitalWrite(RESET, HIGH);
  delay(1000);
  
  /* Reset reciever by setting value in CRA register */
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_CRA;                          // Write address to CRA register on adress bus (port F)
  PORTK = B00100000;                          // Write first command to CRA register
  digitalWrite(CS,LOW);                       // Enable the chip

  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000); 
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag
  Serial.println("Done init reciever!");       // Print to serial monitor
  
  /* Reset transmitter by setting value in CRA register */
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_CRA;                          // Write address to CRA register on adress bus (port F)
  PORTK = B00110000;                          // Write second command to CRA register
  digitalWrite(CS,LOW);                       // Enable the chip

  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1

  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag
  Serial.println("Done init transmitter!");   // Print to serial monitor
  delay(1000);
  
  /* Reset error status by setting value in CRA register */
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_CRA;                          // Write address to CRA register on adress bus (port F)
  PORTK = B01000000;                          // Write third command to CRA register
  digitalWrite(CS,LOW);                       // Enable the chip

  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag                    
  Serial.println("Done init error reg!");     // Print to serial monitor
  delay(1000);
 /*  Reset Mode Register pointer to MR1 */
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_CRA;                          // Write address to CRA register on adress bus (port F)
  PORTK = B00010000;                          // Write third command to CRA register
  digitalWrite(CS,LOW);                       // Enable the chip

  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag                    
  Serial.println("Done setting to MR1!");     // Print to serial monitor
}

/* Function for setting flow control */
void serial_flow_control(void){

  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_MR1A;                         // Write address to MR1A register on adress bus (port F)
  PORTK = 0x13;                               // Write to the first pointer
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag

  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_MR1A;                         // Write address to MR1A register on adress bus (port F)
  PORTK = 0x07;                               // Write third command to second pointer
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag
  Serial.println("Done setting to 8 data bits, no parity, no flow control, 1 stop bit");

}

/* Set baudrate */  
void serial_baud_rate(void){
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_CSRA;                         // Write address to CRA register on adress bus (port F)
  PORTK = 0xCC;                               // Write o CSRA register
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag

  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_ACR;                          // Write address to CRA register on adress bus (port F)
  PORTK = 0x80;                               // Write o ACR register
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag  
  Serial.println("Done setting to 9600 baud");  
}

/* Enable reciever and transmitter */
void serial_enable(void){
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_CRA;                          // Write address to CRA register on adress bus (port F)
  PORTK = 0x05;                               // Write o CRA register
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag

  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_IMR;                          // Write address to IMR register on adress bus (port F)
  PORTK = 0x00;                               // Write o IMR register to disable interrupt
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag
  Serial.println("Done enabling serial port A and disabling interrupt");  
}

/*Write to DUART port 1*/
void print_char(void) {
  pinMode(RW, OUTPUT);                        // Set RW pin to output
  digitalWrite(RW,LOW);                       // Set RW pin to WRITE
  PORTF = DUART_TBA;                          // Write address to Transmit buffer register on adress bus (port F)
  PORTK = 0xFF;                               // Write a byte to TBA register
  digitalWrite(CS,LOW);                       // Enable the chip
  while (dtackstate == 0)                     // Don't do anything untill DTACK have been asserted by interrupt handler and flag set to 1
  delay(1000);
  digitalWrite(CS,HIGH);                      // Disable chip
  dtackstate = 0;                             // Reset DTACK flag
  Serial.println("Done sending character to port");
}
  
/* Interrupt function for catching if DTACK is asserted (going high and then low). 
 * We trigger interrupt on falling edge
*/
void dtackfunction() {
  dtackstate = 1;
  Serial.println("DTACK have been sent to CPU");

}