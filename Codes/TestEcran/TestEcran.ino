#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
lcd.begin(16,2);
lcd.clear();

}

void loop() {
 lcd.setCursor(0,0);
lcd.print("test ligne1");
delay(1000);
lcd.clear();
lcd.setCursor(1,2);
lcd.print("test ligne2");
delay(1000);
lcd.clear();
}
