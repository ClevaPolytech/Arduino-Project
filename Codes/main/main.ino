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
    if(val1==HIGH||val2==LOW||val3==HIGH||val4==HIGH){
      ecranErreur();
      }
    }
  }
  
void achat(){
  if (credit>=prix){
    checkBouton();
    if (val1==HIGH){validation=1;}
    else if(val2==LOW){validation=2;}
    else if(val3==HIGH){validation=3;}
    else if(val4==HIGH){validation=4;}
    else {validation=0;}
      
      if (validation!=0){credit=credit-prix;
      
        ecranAchat();
        delay(1000);
        setupEcran(); }
  }
}

void setup() {
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  lcd.begin(16,2);
  setupEcran();
  Serial.begin(9600);
}

void loop() {
  checkPiece();
  afficheCredit();
  newcred=credit;
  achat();
  erreurAchat();
  temps();
      }
