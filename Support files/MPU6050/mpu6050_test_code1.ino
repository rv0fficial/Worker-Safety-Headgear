#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include <Wire.h>
#include "SPI.h"
#include <LiquidCrystal_I2C.h>
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup(void) {

lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);

 delay(2000);

	// Try to initialize!
	if (!mpu.begin()) {
		lcd.println("Failed to find MPU6050 chip");
		while (1) {
		  delay(10);
		}
	}
	lcd.println("MPU6050 Found!");

	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

	delay(100);
}

void loop() {
	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

	/* Print out the values
	lcd.print("Acceleration X: ");
	lcd.print(a.acceleration.x);
	lcd.print(", Y: ");
	lcd.print(a.acceleration.y);
	lcd.print(", Z: ");
	lcd.print(a.acceleration.z);
	lcd.println(" m/s^2"); */
/*
	lcd.print("Rotation X: ");
	lcd.print(g.gyro.x);
	lcd.print(", Y: ");
	lcd.print(g.gyro.y);
	lcd.print(", Z: ");
	lcd.print(g.gyro.z);
	lcd.println(" rad/s");

	lcd.print("Temperature: ");
	lcd.print(temp.temperature);
	lcd.println(" degC");
*/
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(a.acceleration.x);
 lcd.setCursor(0, 1);
 lcd.print(a.acceleration.y);
lcd.setCursor(0, 2);
 lcd.print(a.acceleration.z);
 //delay(delayValue);
	delay(500);
}