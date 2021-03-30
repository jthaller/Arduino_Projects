#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2); //lcd is 16char wide and 2 tall

lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
lcd.setCursor(0,0);

lcd.print("Wyatt is rather");
lcd.setCursor(0,1);
lcd.print("gollumpus ");

lcd.print(millis()/1000);
lcd.print(" ");
delay(1000);
lcd.print(random(0,100));

}
