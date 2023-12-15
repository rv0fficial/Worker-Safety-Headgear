// NRF24L01 Module Tutorial - Code for Receiver using Arduino UNO

//Include needed Libraries at beginning
#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01
float text[3];
void setup(void) {

 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Receiverow");
 lcd.setCursor(0, 1);
 lcd.print("ready");
 delay(2000);

 radio.begin(); // Start the NRF24L01
 // Max power
// radio.setPALevel( RF24_PA_MAX ) ;

 // Min speed (for better range I presume)
 radio.setDataRate( RF24_250KBPS ) ;

 // 8 bits CRC
// radio.setCRCLength( RF24_CRC_8 ) ;

 // increase the delay between retries & # of retries
//radio.setRetries(15, 15);
 radio.setAutoAck(false);
 radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
 radio.startListening(); // Listen to see if information received

}

void loop(void) {

 while (radio.available())
 {
/*
 radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
 outputToLCD("Received data:", (String) ReceivedMessage[0], 0);
 delay(10);
 */

 /*
 char text1[32] = ""; //Saving the incoming data
 char text2[32] = "";
 char text3[32] = "";
//int accelerometer_x;
radio.read(&text1, sizeof(text1)); //Reading the data

lcd.clear();
lcd.setCursor(0,0);
lcd.print(text1);


radio.read(&text2, sizeof(text2)); //Reading the data
lcd.setCursor(0,1);
lcd.print(text2);


radio.read(&text3, sizeof(text3)); //Reading the data
*/
radio.read(&text, sizeof(text)); 

lcd.clear();
lcd.setCursor(0,0);
lcd.print(text[1]);


 delay(1000);
 }
}

/*
void outputToLCD(String message1, String message2, int delayValue) {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(message1);
 lcd.setCursor(0, 1);
 lcd.print(message2);
 delay(delayValue);
*/
//}