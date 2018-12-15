#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int bouton1=8;
int bouton2=9;
int bouton3=10;
int bouton4=11;
int validation=0;
int var1;
int i=1;
double prix=1;
double credit=0;
double newcred=-1;
unsigned long Temps;
long intervalle;
long chrono;



void setupEcran(){ //initialise l'écran de bienvenue
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenue au");
  lcd.setCursor(0,1);
  lcd.print("PolyShop");
  }


void temps(){
  intervalle=millis()-chrono;
  if (credit>0&&intervalle>30000){
      credit=0;
      setupEcran();
      }
  }

void checkPiece(){ //verifie si une piece est insérée dans la machine
    for (int i=0; i<5; i++){ //parcours detecteur IR 1 à 5
      var1=analogRead(i);     
        if (var1<400){
          if (i==0){
            credit=credit+2;}
          else if(i==1){
            credit=credit+0.5;}
          else if(i==2){
            credit=credit+1;}
          else if(i==3){
            credit=credit+0.2;}
          else {
            credit=credit+0.1;}
  
          Serial.print(credit);
          Serial.println(" euros");
          chrono=millis();
          delay(1000);
          }
       }
  }

void afficheCredit(){ //affiche le nombre de crédit actuellement
  if(credit!=newcred&&credit>0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Credits : ");
    lcd.print(credit);}
  }

void checkBouton(){
  val1=digitalRead(bouton1);
  val2=digitalRead(bouton2);
  val3=digitalRead(bouton3);
  val4=digitalRead(bouton4);
  }

void achat(){
  if (credit>=prix){
    checkBouton();
    if (val1==LOW){validation=1;}
    else if(val2==LOW){validation=2;}
    else if(val3==LOW){validation=3;}
    else if(val4==LOW){validation=4;}
    else {validation=0;}

      if (validation!=0){credit=credit-prix;}
    }
  }

void setup() {
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  pinMode(4,INPUT); //detecte piece 10 cent
  pinMode(3,INPUT); //detecte piece 20 cent
  pinMode(2,INPUT); //detecte piece 1 euro
  pinMode(1,INPUT); //detecte piece de 50 cent
  pinMode(0,INPUT); //detecte piece de 2 euros
  lcd.begin(16,2);
  setupEcran();
  Serial.begin(9600);
}

void loop() {
  checkPiece();
  afficheCredit();
  newcred=credit;
  achat();
  temps();
      }
