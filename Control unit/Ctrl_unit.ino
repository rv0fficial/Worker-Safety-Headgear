
//Include needed Libraries at beginning
#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

float accl[4]; //accleration and the temperatur

int upButton = 7;
int downButton = 6;
int selectButton = 5;
int menu = 1;


void setup() { //VOID function

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Receiverow");
    lcd.setCursor(0, 1);
    lcd.print("ready");
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
      lcd.print("Dist:");
      lcd.setCursor(1,2);
      lcd.print(accl[2]);
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
  lcd.print("  > 1st Page <");
  lcd.setCursor(0, 1);
  lcd.print("Temperature:");
  lcd.setCursor(0, 2);
  lcd.print(accl[3]);

  delay(1500);
}
void action2() {
  lcd.clear();
  lcd.print("  > 2nd Page <");
   lcd.setCursor(0, 1);
  lcd.print("NTP/22/27");
  delay(1500);
}

