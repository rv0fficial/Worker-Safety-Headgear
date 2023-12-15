
//Include needed Libraries at beginning
#include <nRF24L01.h> //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include <RF24.h>
#include <SPI.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//#include <LowPower.h>
#include <LiquidCrystal_I2C.h>

//for GPS module libray files
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


//For BMP180 library
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

Adafruit_MPU6050 mpu;
float accl[7];


/*//////////////////////////////////variable declaration of GPS module starting/////////////////////////////*/
static const int RXPin = 4, TXPin = 3; // Here we make pin 4 as RX of arduino & pin 3 as TX of arduino
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
/*//////////////////////////////////variable declaration of GPS module starting/////////////////////////////*/


/*//////////////////////////////////variable declaration of MQ135 module starting/////////////////////////////*/

const int aqsensor = A0;  //output of mq135 connected to A0 pin of Arduino
int threshold = 250;      //Threshold level for Air Quality

/*//////////////////////////////////variable declaration of MQ135 module starting/////////////////////////////*/


/*//////////////////////////////////variable declaration of BMP180 module starting/////////////////////////////*/

Adafruit_BMP085 bmp;

/*//////////////////////////////////variable declaration of BMP180 module starting/////////////////////////////*/

////////////////////////////////////////////////
static int last_time = millis();
int current_time = millis();
////////////////////////////////////////////

void setup(void) {

  Serial.begin(115200);

//  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  // lcd.print("Initializinglcd.setCursor(0, 1)");
  // lcd.print("Transmitterdelay(2000)");
  // delay(2000);


  /* ////////////////////////////GPS module void setup part starting //////////////////////////////////////////////*/
  //Serial.begin(115200);
  ss.begin(GPSBaud);

  /* ////////////////////////////GPS module void setup part ending //////////////////////////////////////////////*/


  /* ////////////////////////////MQ135 module void setup part starting //////////////////////////////////////////////*/

  pinMode (aqsensor, INPUT); // MQ135 is connected as INPUT to arduino

  /* ////////////////////////////MQ135 module void setup part ending //////////////////////////////////////////////*/


  /* ////////////////////////////BMP180 module void setup part starting //////////////////////////////////////////////*/
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  /* ////////////////////////////BMP180 module void setup part ending //////////////////////////////////////////////*/

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
  delay(1000);

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);


  radio.begin(); // Start the NRF24L01

  // Max power
  radio.setPALevel( RF24_PA_MAX ) ;

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

  /*//////////////////////////////// GPS module running code begining ///////////////////////////////////////*/
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (current_time - last_time >= 5000 && gps.charsProcessed() < 10)
      {
        Serial.println(F("No GPS detected: check wiring."));
        while (true);
      }

      displayInfo();
    }
  }
  /*///////////////////////////////// GPS module running code ///////////////////////////////////////////// */


  /*//////////////////////////////// MQ135 module running code begining ///////////////////////////////////////*/
    int ppm = analogRead(aqsensor); //read MQ135 analog outputs at A0 and store it in ppm
  
    Serial.print("Air Quality: ");  //print message in serail monitor
    Serial.println(ppm);            //print value of ppm in serial monitor
  
    if (ppm > threshold)            // check is ppm is greater than threshold or not
    {
      Serial.println("AQ Level HIGH");
    }
    else
    {
      Serial.println("AQ Level Good");
    }
    // delay (500);
    /*///////////////////////////////// MQ135 module running code ///////////////////////////////////////////// */
  
  
    /*///////////////////////////////// BMP180 module running begining code ///////////////////////////////////////////// */
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
  
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

     Serial.println();
     
    //delay(500);
    /*///////////////////////////////// BMP180 module running begining code ///////////////////////////////////////////// */
  
  
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
  
    
    accl[0] = a.acceleration.x;
    accl[1] = a.acceleration.y;
    accl[2] = gps.location.lat();
    accl[3] = gps.location.lng();
    //accl[4] = temp.temperature;
    accl[4] = ppm;
    accl[5] = bmp.readTemperature();
    accl[6] = bmp.readPressure();
    
  
    radio.write(accl, sizeof(accl));
    //delay (1000);
  
  }

/*//////////////////////////////// GPS module function begining ///////////////////////////////////////*/
void displayInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }


  Serial.println();
  //delay (1000);

}

/*//////////////////////////////// GPS module function begining ///////////////////////////////////////*/
