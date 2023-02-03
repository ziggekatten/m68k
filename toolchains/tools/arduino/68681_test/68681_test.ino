void setup() {
  /* We need to define the following for doing DUART testing:
  * 1. An 4-bit address bus on a port or paralell write to simulate memory mapped registers WRITE (PORTF. Pin 54-57)
  * 2. An 8-bit data bus, on port for paralell READ and WRITE (PORTK. Pin 62-69)
  * 3. Monitoring of 68681 interrupt: INPUT (pull up/downs??) Pin 22
  * 4. Monitoring of 68681 DTACKN to see if DTACK is asserted when writing to control registers (pull up/downs?) Pin 23
  * 5. A reset pin (active low?) Pin 24
  * 6. An read/write pin Pin 25
  */

  /* set up serial feedback */
  Serial.begin(9600);

  /* We start by setting address bus */
  pinMode(54,OUTPUT); //Duart address pin 0
  pinMode(55,OUTPUT); //Duart address pin 1
  pinMode(56,OUTPUT); //Duart address pin 2
  pinMode(57,OUTPUT); //Duart address pin 3

  /* Now we set the pin for reading interrupt */
  pinMode(22,INPUT); 

  /* Now we set the pin for reading DTACKN status*/
  pinMode(23,INPUT);

  /* Now we set the pin for reset */
  pinMode(24,OUTPUT); 

  /* Now we set the pin for R/W  to inital WRITE */
  pinMode(25,OUTPUT);  

}

void loop() {
  /* We need to define some use cases her that we can trace in the serial monitor.
  * This means that we need to use the button to be able to step through things,
  * and read values from the bus as well as data registers. Tricky stuff
  */

  /* We know that an reset of the chip is a good thing 
  * then we need to set up a bunch of registers before even thinking about
  * putting data to the DUART
  */
}

/* A function to define if we are reading or writing to the DUART*/
void set_read_write(char mode) {
  if mode == 'W' {
    //Set pins to write

  } else {
    //Set pins to read 
  }
  
}
