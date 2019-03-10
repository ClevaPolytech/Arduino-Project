#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Adafruit_NeoPixel.h>

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25 // moteur1

#define IN5 26
#define IN6 27
#define IN7 28
#define IN8 29//moteur2

#define IN9 30
#define IN10 31
#define IN11 32
#define IN12 33//moteur3

#define IN13 34
#define IN14 35
#define IN15 36
#define IN16 37//moteur4

char Data;
int temp =5;
int m=0;
int nombreDePas=32*64;
LiquidCrystal lcd(2,3,4,5,6,7); //écran
Adafruit_NeoPixel strip = Adafruit_NeoPixel(22, 20, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripBouton = Adafruit_NeoPixel(4, 52, NEO_GRB + NEO_KHZ800);

const int bouton1=10;
const int bouton2=9;
const int bouton3=8;
const int bouton4=11;

int validation=0;
int var1;
int i=1;
double prix=1;
double credit=0;
double newcred=-1;
unsigned long Temps;
long intervalle;
long chrono;
int val1;
int val2;
int val3;
int val4;



void setupEcran(){ //initialise l'écran de bienvenue
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenue au");
  lcd.setCursor(0,1);
  lcd.print("PolyShop");
  }


void temps(){
  intervalle=millis()-chrono;//intervalle = temps actuel - temps du chrono
  if (credit>0&&intervalle>30000){//s'il y a des crédits et au bout d'un certain intervalle de temps
      credit=0;
      setupEcran();
      }
  }

void bluetooth(){
  if (Serial1.available()){Data=Serial1.read();
  Serial.print(Data);
    switch(Data){
      case 'A':
      credit=credit+2;
      break;
      case 'B':
      credit=credit+0.5;
      break;
      case 'C':
      credit=credit+1;
      break;
      case 'D':
      credit=credit+0.2;
      break;
      case 'E':
      credit=credit+0.1;
      break;
      case 'F':
      credit=0;
      setupEcran();
      break;
      }
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
          chrono=millis();//lance le chrono (ref fonction "temps")
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

void checkBouton(){//vérifie si un bouton a été préssé
   val1=digitalRead(bouton1);
   val2=digitalRead(bouton2);
   val3=digitalRead(bouton3);
   val4=digitalRead(bouton4);
  }

void ecranErreur(){//affiche le nombre de crédits manquant
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Il manque ");
  lcd.setCursor(0,1);
  lcd.print(prix-credit);
  lcd.print(" euro(s)");  
}

void ecranAchat(){//affiche le message de confirmation d'achat.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Merci pour");
  lcd.setCursor(0,1);
  lcd.print("votre achat");}

void erreurAchat(){//traite le cas dans lequel il manque des crédits pour un achat.
  checkBouton();
  if(credit<prix){
    if(val1==LOW||val2==LOW||val3==LOW||val4==LOW){
      if(val1==LOW){stripBouton.setPixelColor(2, 223, 0, 0);
    stripBouton.show();}
      if(val2==LOW){stripBouton.setPixelColor(3, 223, 0, 0);
    stripBouton.show();}
      if(val3==LOW){stripBouton.setPixelColor(1, 223, 0, 0);
    stripBouton.show();}
      if(val4==LOW){stripBouton.setPixelColor(0, 223, 0, 0);
    stripBouton.show();}
      lumiere(223,0,0);
      ecranErreur();
      }
    }
  }

 void chargement(int n){
  if(n%23==0){  
    strip.setPixelColor(n/23,0,223,0);
    strip.show();}
  }

void moteur1(){Serial.begin(115200);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
for (m=0; m <= 511; m++){
Serial.println(m);
chargement(m);
digitalWrite(IN4, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN1, LOW);
delay(temp);
digitalWrite(IN4, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN1, LOW);
delay(temp);
digitalWrite(IN4, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN1, LOW);
delay(temp);
digitalWrite(IN4, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN1, HIGH);
delay(temp); }}

void moteur2(){Serial.begin(115200);
pinMode(IN5, OUTPUT);
pinMode(IN6, OUTPUT);
pinMode(IN7, OUTPUT);
pinMode(IN8, OUTPUT);
for (m=0; m <= 511; m++){
Serial.println(m);
chargement(m);
digitalWrite(IN8, HIGH);
digitalWrite(IN7, LOW);
digitalWrite(IN6, LOW);
digitalWrite(IN5, LOW);
delay(temp);
digitalWrite(IN8, LOW);
digitalWrite(IN7, HIGH);
digitalWrite(IN6, LOW);
digitalWrite(IN5, LOW);
delay(temp);
digitalWrite(IN8, LOW);
digitalWrite(IN7, LOW);
digitalWrite(IN6, HIGH);
digitalWrite(IN5, LOW);
delay(temp);
digitalWrite(IN8, LOW);
digitalWrite(IN7, LOW);
digitalWrite(IN6, LOW);
digitalWrite(IN5, HIGH);
delay(temp); }}

void moteur3(){Serial.begin(115200);
pinMode(IN9, OUTPUT);
pinMode(IN10, OUTPUT);
pinMode(IN11, OUTPUT);
pinMode(IN12, OUTPUT);
for (m=0; m <= 511; m++){
Serial.println(m);
chargement(m);
digitalWrite(IN12, HIGH);
digitalWrite(IN11, LOW);
digitalWrite(IN10, LOW);
digitalWrite(IN9, LOW);
delay(temp);
digitalWrite(IN12, LOW);
digitalWrite(IN11, HIGH);
digitalWrite(IN10, LOW);
digitalWrite(IN9, LOW);
delay(temp);
digitalWrite(IN12, LOW);
digitalWrite(IN11, LOW);
digitalWrite(IN10, HIGH);
digitalWrite(IN9, LOW);
delay(temp);
digitalWrite(IN12, LOW);
digitalWrite(IN11, LOW);
digitalWrite(IN10, LOW);
digitalWrite(IN9, HIGH);
delay(temp); }}

void moteur4(){Serial.begin(9600);
pinMode(IN16, OUTPUT);
pinMode(IN15, OUTPUT);
pinMode(IN14, OUTPUT);
pinMode(IN13, OUTPUT);
for (m=0; m <= 511; m++){
Serial.println(m);
chargement(m);
digitalWrite(IN16, HIGH);
digitalWrite(IN15, LOW);
digitalWrite(IN14, LOW);
digitalWrite(IN13, LOW);
delay(temp);
digitalWrite(IN16, LOW);
digitalWrite(IN15, HIGH);
digitalWrite(IN13, LOW);
digitalWrite(IN12, LOW);
delay(temp);
digitalWrite(IN16, LOW);
digitalWrite(IN15, LOW);
digitalWrite(IN14, HIGH);
digitalWrite(IN13, LOW);
delay(temp);
digitalWrite(IN16, LOW);
digitalWrite(IN15, LOW);
digitalWrite(IN13, LOW);
digitalWrite(IN12, HIGH);
delay(temp); }}

void achat(){
  if (credit>=prix){
    lumiere(223,0,0);
    checkBouton();
    if (val1==LOW){validation=1;
stripBouton.setPixelColor(2, 0, 223, 0);
    stripBouton.show();
    moteur1();}
    else if(val2==LOW){validation=2;
stripBouton.setPixelColor(3, 0, 223, 0);
    stripBouton.show(); 
    moteur2();}
    else if(val3==LOW){validation=3;
      stripBouton.setPixelColor(1, 0, 223, 0);
    stripBouton.show();
      moteur3();}
    else if(val4==LOW){validation=4;
    stripBouton.setPixelColor(0, 0, 223, 0);
    stripBouton.show();

      moteur4();}
    else {validation=0;}
      
      if (validation!=0){credit=credit-prix;
        ecranAchat();
        delay(1000);
        setupEcran(); }
  }
}

void resetLumiereBouton(){
     stripBouton.setPixelColor(0, 0, 0, 223);
     stripBouton.setPixelColor(1, 0, 0, 223);
     stripBouton.setPixelColor(2, 0, 0, 223);
     stripBouton.setPixelColor(3, 0, 0, 223);
     stripBouton.show();

}


void lumiere(int r,int g,int b){
  int X=22;
  for(int i = 0; i < X; i++ ) { // On fait une boucle pour définir la couleur de chaque led
        // setPixelColor(n° de led, Rouge, Vert, Bleu)
    strip.setPixelColor(i, 223, 0, 0);       
    }
    strip.show(); // on affiche 
  }

void setup() {
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  lcd.begin(16,2);
  setupEcran();
  strip.begin();
  stripBouton.begin();
  lumiere(223,0,0);
  strip.show();
  Serial.begin(9600);
  Serial.println("Bonjour -Pret pour les commandes AT");
  Serial1.begin(9600);


}


void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));

 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < 22; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void loop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
  checkPiece();
  bluetooth();
  afficheCredit();
  newcred=credit;
  achat();
  erreurAchat();
  resetLumiereBouton();
  //temps();
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
  checkPiece();
  bluetooth();
  afficheCredit();
  newcred=credit;
  achat();
  erreurAchat();
  resetLumiereBouton();
  //temps();
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}
  
