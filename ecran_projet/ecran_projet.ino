#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int credit=0;


void setupEcran(){
  lcd.setCursor(0,0);
lcd.print("Bienvenue au");
lcd.setCursor(0,1);
lcd.print("PolyShop");
  }
  
void setup() {
lcd.begin(16,2);
setupEcran();
}



void loop() {

  if(credit>0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Credit : ");
    lcd.print(credit);}
    credit++;
    delay(1000);

}
