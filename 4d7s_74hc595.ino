#include <SPI.h>
/*
  * CS - to digital pin 10  (SS pin) -> 74HC595 Pin 12
  * SDI - to digital pin 11 (MOSI pin) -> 74HC595 Pin 14
  * CLK - to digital pin 13 (SCK pin) -> 74HC595 Pin 11 
*/

const int ssPin = 10;    

const byte digit[10] = {     //seven segment digits in bits
//  gfedcba 
  B01000000, //0
  B01111001, //1
  B00100100, //2
  B00110000, //3
  B00011001, //4
  B00010010, //5
  B00000010, //6
  B01111000, //7
  B00000000, //8
  B00010000  //9
};

const byte errorMessage[4] = {
//  gfedcba 
  B00000110, // E
  B00101111, // r
  B00101111, // r
  B00100011  // o
};

const int pos[4] = {  
  256,
  512,
  1024,
  2048
};


void setup() {  
  pinMode(ssPin, OUTPUT);
  SPI.begin();
  Serial.begin(115200);
}

int c,n= 9990;

void loop() {

  c++;
  if (c > 25) {
    c = 0;
    n++;
  }
  displayNumber(n);  
}

void displayNumber(int num) {

  byte digit3, digit2, digit1, digit0;
  
  num = abs(num);
  if (num > 9999 ) {
    displayError();
  } else {
    digit3 = int(num / 1000);
    digit2 = int((num % 1000) / 100);
    digit1 = int(((num % 1000) % 100) / 10);
    digit0 = int(((num % 1000) % 100) % 10);

    display(3,digit[digit3]);
    display(2,digit[digit2]);
    display(1,digit[digit1]);
    display(0,digit[digit0]);    
  }
}

void display(int p, int v){
  digitalWrite(ssPin, LOW);
  SPI.transfer16(pos[p] + v);
  digitalWrite(ssPin, HIGH);
  delay(5);
}

void displayError(){  
  display(3,errorMessage[0]); 
  display(2,errorMessage[1]);
  display(1,errorMessage[2]);
  display(0,errorMessage[3]);
}
