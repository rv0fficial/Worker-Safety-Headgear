// NRF24L01 Module Tutorial - Code for Transmitter using Arduino NANO

//Include needed Libraries at beginning
#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//#include <LowPower.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

Adafruit_MPU6050 mpu;
float accl[4];

void setup(void) {
  
 Serial.begin(115200);

 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Initializing..."); 
// lcd.print("Initializinglcd.setCursor(0, 1)");
// lcd.print("Transmitterdelay(2000)");
 delay(2000);


 Wire.begin();
 //mpu.begin();

  // Try to initialize!
 if (!mpu.begin()) 
 {
    lcd.println("Failed find MPU");
    while (1) 
    {
      delay(10);
    }
 }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("MPU6050 Found!");
  delay(2000);

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);


 radio.begin(); // Start the NRF24L01
 
 // Max power
 //radio.setPALevel( RF24_PA_MAX ) ;

 // Min speed (for better range I presume)
 radio.setDataRate( RF24_250KBPS ) ;

 // 8 bits CRC
 // radio.setCRCLength( RF24_CRC_8 ) ;

 // increase the delay between retries & # of retries
 //radio.setRetries(15, 15);
 radio.setAutoAck(false);
 radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void) {
 
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

// float text1,text2,text3;
accl[0]=a.acceleration.x;
accl[1]=a.acceleration.y;
accl[2]=a.acceleration.z;
accl[3]=temp.temperature;

radio.write(accl, sizeof(accl));

lcd.clear();
lcd.setCursor(0, 0);
lcd.print(a.acceleration.x);

lcd.setCursor(0, 1);
lcd.print(a.acceleration.y);


lcd.setCursor(5, 0);
lcd.print(a.acceleration.z);

lcd.setCursor(5, 1);
lcd.print(temp.temperature);

 delay(1000);

}
