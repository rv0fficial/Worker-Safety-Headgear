
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

int upButton = 7;
int downButton = 6;
int selectButton = 5;
int menu = 1;


void setup() { //VOID function
//  lcd.begin();
    lcd.init();

  lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();
}


void loop() { //LOOP
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
  lcd.print("  ------------");

  delay(1500);
}
void action2() {
  lcd.clear();
  lcd.print("  > 2nd Page <");
   lcd.setCursor(0, 1);
  lcd.print("  ------------");
  delay(1500);
}

