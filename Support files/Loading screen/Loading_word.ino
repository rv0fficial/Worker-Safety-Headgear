#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 16, 4);

byte prt1l[] = {B00111,B00111,B00111,B00111,B00111,B00111,B00111,B00111};

byte prt2l[] = {B00111,B00111,B00111,B00111,B00111,B00111,B00111,B00111};

byte prt3l[] = {B00000,B00000,B00000,B00000,B11111,B11111,B11111,B11111};



void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.createChar(1, prt1l);
  lcd.createChar(2, prt2l);
  lcd.createChar(3, prt3l);


  lcd.setCursor(4,1);
  lcd.write(1);
  
  lcd.setCursor(0,2);
  lcd.write(2);
  
  lcd.setCursor(1,2);
  lcd.write(3);
  
  lcd.setCursor(2,2);
  lcd.print("oading...");
}

void loop() { }