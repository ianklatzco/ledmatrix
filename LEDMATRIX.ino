#include <SPI.h>
#include "font_table.h"

// needed for LED output/SPI communication
#define SHIFT_DAT P1_7
#define SHIFT_CLK P1_5
#define SHIFT_CLR P1_3
#define SHIFT_LAT P1_4
#define SHIFT_EN  P1_0
#define DRIVE_RST P2_0

// non-essential
#define SHIFT_OUT P1_6

// the setup routine runs once when you press reset:
void setup() {
  // initialize the interface pins as outputs.
  pinMode(SHIFT_CLR, OUTPUT);
  pinMode(SHIFT_LAT, OUTPUT);
  pinMode(SHIFT_DAT, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_EN,  OUTPUT);
  pinMode(DRIVE_RST, OUTPUT);

  // set up SPI protocol module to talk to shift registers
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(LSBFIRST);

  // disable shift registers outputs
  digitalWrite(SHIFT_EN, HIGH);

  // clear registers and anode driver
  digitalWrite(SHIFT_CLR, LOW);
  digitalWrite(DRIVE_RST, LOW);

  // disable loading of data into register outputs
  digitalWrite(SHIFT_LAT, LOW);

  // enable and stop clearing registers
  digitalWrite(SHIFT_EN, LOW);
  digitalWrite(SHIFT_CLR, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
    blah("WINNER WINNER CHICKEN DINNER");
  //prints("JUST DO IT");
}

void blah(char* str){ 
  int y;
  int a;
  int x;
  int i;
  int z;
  int array[28] = {55,41,46,46,37,50,0,55,41,46,46,37,50,0,35,40,41,35,43,37,46,0,36,41,46,46,37,50};
   for(int x = 0; x < 28; x++){ 
   for(int n = 0; n< 500; n++){  
      for(int i = 0; i < 9; i++){ // for each row
        // disable shift register loading data until transmission done
        digitalWrite(SHIFT_LAT, LOW);
        // transfer anode (row)
        SPI.transfer(0x80 >> i);
        // transfer (inverted) data for cathode registers
        //for(x = 0; x< 28; x++){
          SPI.transfer(~0x00); //BLUE
          SPI.transfer(~0x00); //GREEN
//          SPI.transfer(~0xFF);
//          SPI.transfer(~font_table[array[x]][i]); //RED
            SPI.transfer(~font_table[*char[x]][i]); //RED
                 //}
        //digitalWrite(SHIFT_EN, HIGH);
        // disable outputs momentarily
        digitalWrite(DRIVE_RST, LOW);
        // signal to anode driver it is safe to pull in new data
        digitalWrite(SHIFT_LAT, HIGH);
        // extra clock cycle because data gets shifted to registers, then another for registers to LED driver, then enable outputs

        digitalWrite(SHIFT_LAT, LOW);
        digitalWrite(DRIVE_RST, HIGH);
        digitalWrite(SHIFT_LAT, HIGH);
        digitalWrite(SHIFT_LAT, LOW);

        delayMicroseconds(100);
      }
   }
   int n = 0;
}

}

// print string
void prints(char* str){
  int a;
  // while the string has not ended
  while(*str){
    a = 0;
    for(a = 0; a < 50; a++){ // loop 50 times to make visible
      int i = 0;
      for(i = 0; i < 8; i++){ // for each row
        // disable shift register loading data until transmission done
        digitalWrite(SHIFT_LAT, LOW);
        // transfer anode (row)
            // YOUR CODE HERE
        // transfer inverted font data for the current row
            // note that font data must be inverted since the first 3 (rgb)
            // shift registers control the cathodes (ground sides) of the LEDs
            // YOUR CODE HERE


        //digitalWrite(SHIFT_EN, HIGH);
        // disable outputs momentarily
        digitalWrite(DRIVE_RST, LOW);
        // signal to anode driver it is safe to pull in new data
        digitalWrite(SHIFT_LAT, HIGH);
        // extra clock cycle because data gets shifted to registers, then another for registers to LED driver, then enable outputs

        delay(1);
      }
    }
    str++;
  }

  // print out blank character
  for(a = 0; a < 50*8; a++){
  // disable shift register loading data until transmission done
    digitalWrite(SHIFT_LAT, LOW);
    // transfer anode (row)
    SPI.transfer(0x00);
    // transfer inverted font data
    SPI.transfer(0xFF);
    SPI.transfer(0xFF);
    SPI.transfer(0xFF);
    delay(1);
    digitalWrite(SHIFT_LAT, HIGH);
  }
}


// scrolling print string (CHALLENGE MODE)
void sprints(char* str, int loops){
  int a, b;
  unsigned char char1, char2;
  int charwidth = 5;

  // while the string is not empty
  while(*str){
      str++;
  }
}

