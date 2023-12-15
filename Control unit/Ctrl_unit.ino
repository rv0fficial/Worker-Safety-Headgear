
//Include needed Libraries at beginning
#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

float accl[7]; //accleration and the temperatur

int upButton = 7;
int downButton = 6;
int selectButton = 5;
int menu = 1;


// setting animation speed (delay between frames)
int x = 300;
// setting time for Man waiting
int y = 3000;

// START setting all the pixel-art
//setting pixels for standing man:
//step 1 of 1:
  byte stepA1[8] = {B00011,B00111,B00111,B00111,B00111,B00001,B00011,B00111};
  byte stepA2[8] = {B00001,B00001,B00011,B00011,B00011,B00001,B00000,B00001};
  byte stepA3[8] = {B11111,B11111,B11111,B11111,B11111,B11011,B10001,B10001};
  byte stepA4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte stepA5[8] = {B11000,B11100,B11100,B11100,B11100,B10000,B11000,B11100};
  byte stepA6[8] = {B00000,B10000,B11000,B00000,B11000,B11100,B11000,B10000};
  
//setting pixels for running man right:
//step 1 of 3:
  byte stepB1[8] = {B00011,B00011,B00011,B00011,B00001,B00000,B00000,B00000};
  byte stepB2[8] = {B00000,B00001,B00001,B00011,B00011,B00011,B00000,B00001};
  byte stepB3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11110};
  byte stepB4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte stepB5[8] = {B00000,B00000,B10000,B10000,B10000,B00000,B10000,B00000};
  byte stepB6[8] = {B00000,B11000,B00000,B11000,B11100,B11000,B10000,B00000};

//step 2 of 3
  byte stepC1[8] = {B11111,B11111,B11101,B00011,B00111,B01111,B01111,B00111};
  byte stepC2[8] = {B00000,B00001,B00001,B00011,B00011,B00011,B00000,B00111};
  byte stepC3[8] = {B11111,B11111,B11111,B11111,B11111,B10011,B00000,B00000};
  byte stepC4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte stepC5[8] = {B11110,B11110,B01100,B11100,B11100,B11100,B00000,B00000};
  byte stepC6[8] = {B00000,B11000,B00000,B11000,B11100,B11000,B10000,B00000};
  
//step 3 of 3
  byte stepD1[8] = {B00001,B00011,B00111,B00111,B00111,B01111,B01100,B00000};
  byte stepD2[8] = {B00000,B00000,B00001,B00001,B00011,B00011,B00011,B00000};
  byte stepD3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11110,B11111};
  byte stepD4[8] = {B00000,B11111,B11111,B11101,B11101,B11111,B11111,B11111};
  byte stepD5[8] = {B10000,B11000,B10000,B00000,B00000,B00000,B00000,B00000};
  byte stepD6[8] = {B00000,B00000,B11000,B00000,B11000,B11100,B11000,B10000};

//setting pixels for man slipping right
//step 1 of 3
  byte slipA1[8] = {B00111,B00111,B00011,B00011,B00001,B01111,B01111,B00111};
  byte slipA2[8] = {B00000,B00011,B00111,B01111,B01111,B00111,B00011,B00111};
  byte slipA3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11000,B10000};
  byte slipA4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte slipA5[8] = {B11000,B11000,B10000,B00000,B00000,B00000,B00000,B00000};
  byte slipA6[8] = {B00000,B11000,B00000,B11100,B11100,B11000,B10000,B11000};

//step 2 of 3
  byte slipB1[8] = {B00011,B00011,B00001,B00001,B00000,B00111,B00111,B00011};
  byte slipB2[8] = {B00000,B00001,B00011,B00111,B00111,B00011,B00001,B00011};
  byte slipB3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11100,B11000};
  byte slipB4[8] = {B11111,B11111,B11110,B11110,B11111,B11111,B11111,B11111};
  byte slipB5[8] = {B11100,B11100,B11000,B10000,B10000,B00000,B00000,B00000};
  byte slipB6[8] = {B00000,B11000,B10000,B11100,B11110,B11100,B11000,B11100};

//step 3 of 3
  byte slipC1[8] = {B00001,B00001,B00000,B00000,B00000,B00011,B00011,B00001};
  byte slipC2[8] = {B00000,B00000,B00001,B00011,B00011,B00001,B00000,B00001};
  byte slipC3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11110,B11100};
  byte slipC4[8] = {B01111,B11111,B11111,B11111,B11111,B11111,B11111,B11111};
  byte slipC5[8] = {B11110,B11110,B11100,B11000,B11000,B10000,B00000,B00000};
  byte slipC6[8] = {B10000,B11100,B11000,B11110,B11111,B11110,B11100,B11110};

//setting pixels for man running left
//step 1 of 3
  byte stepE1[8] = {B00000,B00001,B00001,B00001,B00000,B00000,B00001,B00000};
  byte stepE2[8] = {B00000,B00011,B00000,B00011,B00111,B00011,B00001,B00000};
  byte stepE3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B01111};
  byte stepE4[8] = {B11111,B11111,B10111,B10111,B11111,B11111,B11111,B11111};
  byte stepE5[8] = {B11000,B11000,B11000,B11000,B10000,B00000,B00000,B00000};
  byte stepE6[8] = {B00000,B10000,B10000,B11000,B11000,B11000,B10000,B10000};
  
//step 2 of 3
  byte stepF1[8] = {B01111,B01111,B01100,B00111,B00111,B00111,B00000,B00000};
  byte stepF2[8] = {B00000,B00011,B00000,B00011,B00111,B00011,B00001,B00000};
  byte stepF3[8] = {B11111,B11111,B11111,B11111,B11111,B11001,B00000,B00000};
  byte stepF4[8] = {B11111,B11111,B10111,B10111,B11111,B11111,B11111,B11111};
  byte stepF5[8] = {B11111,B11111,B10111,B11000,B11100,B11110,B11110,B11100};
  byte stepF6[8] = {B00000,B10000,B10000,B11000,B11000,B11000,B00000,B11100};
  
//step 3 of 3
  byte stepG1[8] = {B00001,B00011,B00001,B00000,B00000,B00000,B00000,B00000};
  byte stepG2[8] = {B00000,B00000,B00011,B00000,B00011,B00111,B00011,B00001};
  byte stepG3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B01111,B11111};
  byte stepG4[8] = {B00000,B11111,B11111,B10111,B10111,B11111,B11111,B11111};
  byte stepG5[8] = {B10000,B11000,B11100,B11100,B11100,B11110,B00110,B00000};
  byte stepG6[8] = {B00000,B00000,B10000,B10000,B11000,B11000,B11000,B00000};
  
//setting pixels for man slipping left
//step 1 of 3
  byte slipD1[8] = {B00011,B00011,B00001,B00000,B00000,B00000,B00000,B00000};
  byte slipD2[8] = {B00000,B00001,B00000,B00011,B00111,B00011,B00001,B00011};
  byte slipD3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B00011,B00001};
  byte slipD4[8] = {B11111,B11111,B10111,B10111,B11111,B11111,B11111,B11111};
  byte slipD5[8] = {B11100,B11100,B11000,B11000,B10000,B11110,B11110,B11100};
  byte slipD6[8] = {B00000,B11000,B11100,B11110,B11110,B11100,B11000,B11100};

//step 2 of 3
  byte slipE1[8] = {B00111,B00111,B00111,B00011,B00001,B00000,B00000,B00000};
  byte slipE2[8] = {B00000,B00011,B00001,B00111,B01111,B00111,B00011,B00111};
  byte slipE3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B00111,B00011};
  byte slipE4[8] = {B11111,B11111,B01111,B01111,B11111,B11111,B11111,B11111};
  byte slipE5[8] = {B11000,B11000,B10000,B00000,B10000,B11100,B11100,B11000};
  byte slipE6[8] = {B00000,B00000,B11000,B11100,B11100,B11000,B10000,B11000};
  
//step 3 of 3
  byte slipF1[8] = {B01111,B01111,B00111,B00111,B00011,B00001,B00000,B00000};
  byte slipF2[8] = {B00001,B00111,B00011,B01111,B11111,B01111,B00111,B01111};
  byte slipF3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B01111,B00111};
  byte slipF4[8] = {B11110,B11111,B11111,B11111,B11111,B11111,B11111,B11111};
  byte slipF5[8] = {B00000,B00000,B00000,B00000,B00000,B11000,B11000,B10000};
  byte slipF6[8] = {B00000,B00000,B10000,B11000,B11000,B10000,B00000,B10000};
// END setting all the pixel-art




void setup() { //VOID function

 // set up the LCD's number of columns and rows:
 lcd.init();
 lcd.backlight();
 // clear the LCD screen:
 lcd.clear();
 
 // get the standing man part on the screen:
    standingMan();
        // delay(y);
    lcd.setCursor(1,0);
    lcd.print("Safety headgear");

   lcd.setCursor(4,1);//Changed row
   lcd.print("NTP/22/27"); 

   lcd.setCursor(7-4,2);//Changed row
   lcd.print("CSNE");

   lcd.setCursor(7-4,3);//Changed row
   lcd.print("2022");

   delay(2000);
   lcd.clear();
   standingMan();
       // delay(y);

   //Aditinally added line(----)
   lcd.setCursor(0,0);
   lcd.print("---------------");
   lcd.setCursor(0-4,3);
   lcd.print("---------------");
       
   lcd.setCursor(3,1);
   lcd.print("Please");
   lcd.setCursor(8-4,2);//Changed row
   lcd.print("Wait..."); 
   delay(5000);
        lcd.clear();

  //start the Man animation:
     // run to the the right:
        runningManR();
     // slip to the right:
        ManslipR();
     // now run to the left:
        runningManL();
     // slip to the left:
        ManslipL();

    //Aditinally added line(----)
    lcd.setCursor(0,0);
    lcd.print("---------------");
    lcd.setCursor(0-4,3);
    lcd.print("---------------");
    
    lcd.setCursor(4, 1);
    lcd.print("Receive row");
    lcd.setCursor(4-4, 2);
    lcd.print("ready!");
     delay(2000);

     radio.begin(); // Start the NRF24L01
     // Max power
   //radio.setPALevel( RF24_PA_MAX ) ;
    
     // Min speed (for better range I presume)
     radio.setDataRate( RF24_250KBPS ) ;
    
     // 8 bits CRC
   //radio.setCRCLength( RF24_CRC_8 ) ;
    
     // increase the delay between retries & # of retries
   //radio.setRetries(15, 15);
     radio.setAutoAck(false);
     radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
     radio.startListening(); // Listen to see if information received
 
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();
}

// START putting al the pixel-art we defined before in his place for each animation part
// standing man animation part
void standingMan(){
  int a = 0;
  int b = a + 1;
  int c = a + 2;
  lcd.createChar(1, stepA1);
  lcd.createChar(2, stepA2);
  lcd.createChar(3, stepA3);
  lcd.createChar(4, stepA4);
  lcd.createChar(5, stepA5);
  lcd.createChar(6, stepA6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
}

// running man to the right animation part
void runningManR() {
  for (int a=0;a<11;a+=4){
  int b = a + 1;
  int c = a + 2;
  int d = a + 3;
  int e = a + 4;
  int f = a + 5;
  int g = a + 6;
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepB1);
  lcd.createChar(2, stepB2);
  lcd.createChar(3, stepB3);
  lcd.createChar(4, stepB4);
  lcd.createChar(5, stepB5);
  lcd.createChar(6, stepB6);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(b,1);
  lcd.write(2);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(c,1);
  lcd.write(4);
  lcd.setCursor(d-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(d,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepC1);
  lcd.createChar(2, stepC2);
  lcd.createChar(3, stepC3);
  lcd.createChar(4, stepC4);
  lcd.createChar(5, stepC5);
  lcd.createChar(6, stepC6);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(c,1);
  lcd.write(2);
  lcd.setCursor(d-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(d,1);
  lcd.write(4);
  lcd.setCursor(e-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(e,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepB1);
  lcd.createChar(2, stepB2);
  lcd.createChar(3, stepB3);
  lcd.createChar(4, stepB4);
  lcd.createChar(5, stepB5);
  lcd.createChar(6, stepB6);
  lcd.setCursor(d-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(d,1);
  lcd.write(2);
  lcd.setCursor(e-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(e,1);
  lcd.write(4);
  lcd.setCursor(f-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(f,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepD1);
  lcd.createChar(2, stepD2);
  lcd.createChar(3, stepD3);
  lcd.createChar(4, stepD4);
  lcd.createChar(5, stepD5);
  lcd.createChar(6, stepD6);
  lcd.setCursor(e-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(e,1);
  lcd.write(2);
  lcd.setCursor(f-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(f,1);
  lcd.write(4);
  lcd.setCursor(g-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(g,1);
  lcd.write(6);
  delay(x);
  }
}

// slipping man the the right animation part
void ManslipR(){
  int a = 13;
  int b = a + 1;
  int c = a + 2;
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, slipA1);
  lcd.createChar(2, slipA2);
  lcd.createChar(3, slipA3);
  lcd.createChar(4, slipA4);
  lcd.createChar(5, slipA5);
  lcd.createChar(6, slipA6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, slipB1);
  lcd.createChar(2, slipB2);
  lcd.createChar(3, slipB3);
  lcd.createChar(4, slipB4);
  lcd.createChar(5, slipB5);
  lcd.createChar(6, slipB6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
  lcd.createChar(1, slipC1);
  lcd.createChar(2, slipC2);
  lcd.createChar(3, slipC3);
  lcd.createChar(4, slipC4);
  lcd.createChar(5, slipC5);
  lcd.createChar(6, slipC6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
}

// running man to the left animation part
void runningManL(){
  for (int a=16;a>4;a-=4){
  int b = a - 1;
  int c = a - 2;
  int d = a - 3;
  int e = a - 4;
  int f = a - 5;
  int g = a - 6;
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepE1);
  lcd.createChar(2, stepE2);
  lcd.createChar(3, stepE3);
  lcd.createChar(4, stepE4);
  lcd.createChar(5, stepE5);
  lcd.createChar(6, stepE6);
  lcd.setCursor(d-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(d,1);
  lcd.write(2);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(c,1);
  lcd.write(4);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(b,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepF1);
  lcd.createChar(2, stepF2);
  lcd.createChar(3, stepF3);
  lcd.createChar(4, stepF4);
  lcd.createChar(5, stepF5);
  lcd.createChar(6, stepF6);
  lcd.setCursor(e-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(e,1);
  lcd.write(2);
  lcd.setCursor(d-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(d,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepE1);
  lcd.createChar(2, stepE2);
  lcd.createChar(3, stepE3);
  lcd.createChar(4, stepE4);
  lcd.createChar(5, stepE5);
  lcd.createChar(6, stepE6);
  lcd.setCursor(f-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(f,1);
  lcd.write(2);
  lcd.setCursor(e-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(e,1);
  lcd.write(4);
  lcd.setCursor(d-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(d,1);
  lcd.write(6);
  delay(x);
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, stepG1);
  lcd.createChar(2, stepG2);
  lcd.createChar(3, stepG3);
  lcd.createChar(4, stepG4);
  lcd.createChar(5, stepG5);
  lcd.createChar(6, stepG6);
  lcd.setCursor(g-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(g,1);
  lcd.write(2);
  lcd.setCursor(f-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(f,1);
  lcd.write(4);
  lcd.setCursor(e-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(e,1);
  lcd.write(6);
  delay(x);
  }
}

// slipping man to the leftt animation part
void ManslipL(){
  int a = 1;
  int b = a + 1;
  int c = a + 2;
  lcd.clear();

  //Aditinally added line(----)
  //Aditinally added word(Almost there)
  lcd.setCursor(0,0);
  lcd.print("-----Almost----"); 
  lcd.setCursor(-4,3);
  lcd.print("-----there-----");
  
  lcd.createChar(1, slipD1);
  lcd.createChar(2, slipD2);
  lcd.createChar(3, slipD3);
  lcd.createChar(4, slipD4);
  lcd.createChar(5, slipD5);
  lcd.createChar(6, slipD6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
  lcd.clear();
  
  //In this place didn't add any charaters as before.(Almostthere, ---)
  
  lcd.createChar(1, slipE1);
  lcd.createChar(2, slipE2);
  lcd.createChar(3, slipE3);
  lcd.createChar(4, slipE4);
  lcd.createChar(5, slipE5);
  lcd.createChar(6, slipE6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
  lcd.createChar(1, slipF1);
  lcd.createChar(2, slipF2);
  lcd.createChar(3, slipF3);
  lcd.createChar(4, slipF4);
  lcd.createChar(5, slipF5);
  lcd.createChar(6, slipF6);
  lcd.setCursor(a-4,2);//Changed row
  lcd.write(1);
  lcd.setCursor(a,1);
  lcd.write(2);
  lcd.setCursor(b-4,2);//Changed row
  lcd.write(3);
  lcd.setCursor(b,1);
  lcd.write(4);
  lcd.setCursor(c-4,2);//Changed row
  lcd.write(5);
  lcd.setCursor(c,1);
  lcd.write(6);
  delay(x);
}

void loop() { //LOOP

   while (radio.available()){
      radio.read(&accl, sizeof(accl)); 

      lcd.setCursor(0,0);
      lcd.print("Dist:");
      lcd.setCursor(5,0);
      lcd.print(accl[0]);

      lcd.setCursor(0,1);
      lcd.print("Dist:");
      lcd.setCursor(5,1);
      lcd.print(accl[1]);

      lcd.setCursor(-4,2);
      lcd.print("Air:");
      lcd.setCursor(1,2);
      lcd.print(accl[4]);
       //delay(1000);
 }

  if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
 
}

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(-4, 3);
      lcd.print(">>Envir");
      lcd.setCursor(3, 3);
      lcd.print("  About");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(-4, 3);
      lcd.print("  Envir");
      lcd.setCursor(3, 3);
      lcd.print(">>About");
      break;
    case 3:
      menu = 2;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;

  }
}

void action1() {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Tmp:");
  lcd.setCursor(5, 0);
  lcd.print(accl[5]);
  
  lcd.setCursor(0, 1);
  lcd.print("Lng:");
  lcd.setCursor(5, 1);
  lcd.print(accl[3]);
  
  lcd.setCursor(-4, 2);
  lcd.print("Lat:");
  lcd.setCursor(1, 2);
  lcd.print(accl[2]);

   lcd.setCursor(-4, 3);
  lcd.print("Prs:");
  lcd.setCursor(1, 3);
  lcd.print(accl[6]);
  
  //pacM();//PACMAN function
  delay(1500);
}
void action2() {
  lcd.clear();
  
  lcd.print("  > 2nd Page <");
  lcd.setCursor(0, 1);
  lcd.print("NTP/22/27");
  pacM();//PACMAN function
  delay(1500);
}

//PACMAN function
void pacM() {

uint8_t pacman[8] = {0b00000,0b00000,0b01110,0b11011,0b11111,0b01110,0b00000,0b00000};
uint8_t pacmanOpen[] = {0b00000,0b00000,0b01110,0b11011,0b11100,0b01110,0b00000,0b00000};
uint8_t dot[] = {0b00000,0b00000,0b00000,0b00110,0b00110,0b00000,0b00000,0b00000};

  lcd.createChar(1, pacman);
  lcd.createChar(2, dot);
  //lcd.begin(20, 4);

 for (int i =-2 ; i < 10; i++) {
    lcd.setCursor(i, 3);
    lcd.print("\1");
    for (int j = i + 1; j < 10; j++) {
      lcd.setCursor(j, 3);
      lcd.print("\2");
    }
    lcd.createChar(1, pacman);
    delay(200);
    lcd.createChar(1, pacmanOpen);
    delay(200);
    lcd.setCursor(i, 3);
    lcd.print(" ");
  }
  //delay(1000);
}
