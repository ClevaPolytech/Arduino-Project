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

int motorSpeed = 1250; //max speed du sep motor

/*int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor1Pin3 = 4;
int motor1Pin4 = 5;

int motor2Pin1 = 6;
int motor2Pin2 = 7;
int motor2Pin3 = 8;
int motor2Pin4 = 9;*/

int motor3Pin1 = 10;
int motor3Pin2 = 11;
int motor3Pin3 = 12;
int motor3Pin4 = 13;

//probleme de pin pour l'instant
/*int motor4Pin1 = ;
int motor4Pin2 = ;
int motor4Pin3 = ;
int motor4Pin4 = ;*/

int moteur1;
int moteur2;
int moteur3;
int moteur4;

int steps[8] = {0b01001, 0b00001, 0b00011, 0b00010, 0b00110,0b00100,0b01100, 0b01000};
// tableau de binaires, en décimal : 9,1,3,2,6,4,12,8
/* en fait, ça va permettre de faire les steps du moteur, pour que ça tourne
 *  de façon continue
 */


void setupEcran(){ //initialise l'écran de bienvenue
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenue au");
  lcd.setCursor(0,1);
  lcd.print("PolyShop");
  }

void setupMotor(){ //initialise les moteurs
  /*pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin3, OUTPUT);
  pinMode(motor1Pin4, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);*/

  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor3Pin3, OUTPUT);
  pinMode(motor3Pin4, OUTPUT);
  /*
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
  pinMode(motor4Pin3, OUTPUT);
  pinMode(motor4Pin4, OUTPUT);*/
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

void activeMoteur(){
  if(validation != 0){
    for(int i = 0; i < 8; i++) // 8 pulses
    {
      faireTournerMoteur(i,validation);
      delayMicroseconds(motorSpeed);
      if(i==8){
        break;
      }
    }
  }
  
}

void faireTournerMoteur(int elem, int motor){
  //pour avoir le numéro du moteur à faire tourner.
  /*if(motor == 1){
    int moteur1 = motor1Pin1;
    int moteur2 = motor1Pin2;
    int moteur3 = motor1Pin3;
    int moteur4 = motor1Pin4;
  }
  else if(motor == 2){
    int moteur1 = motor2Pin1;
    int moteur2 = motor2Pin2;
    int moteur3 = motor2Pin3;
    int moteur4 = motor2Pin4;
  }
  /*else if(motor == 3){*/
    int moteur1 = motor3Pin1;
    int moteur2 = motor3Pin2;
    int moteur3 = motor3Pin3;
    int moteur4 = motor3Pin4;
  //}
  /*else if(motor == 4){
    int moteur1 = motor4Pin1;
    int moteur2 = motor4Pin2;
    int moteur3 = motor4Pin3;
    int moteur4 = motor4Pin4;
  }*/

  /*permet d'attribuer la bonne valeur à chaque IN du moteur
   * pour que le moteur tourne en continu.
   */
   /* bitRead(binary x , rank n ) :
    *  permet de lire le bit du nombre binaire x au nème rang
    *  en partant du bit le plus à droite.
    */
  digitalWrite(moteur1, bitRead(steps[elem], 0));  //lit le 1er bit à droite
  digitalWrite(moteur2, bitRead(steps[elem], 1));  //lit le 2eme bit à droite
  digitalWrite(moteur3, bitRead(steps[elem], 2));  //lit le 3eme bit à droite
  digitalWrite(moteur4, bitRead(steps[elem], 3));  //lit le 4eme bit à droite*/
  Serial.println("fairetournermoteur");
  validation=0;
}

void setup() {
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  lcd.begin(16,2);
  setupEcran();
  setupMotor();
  Serial.begin(9600);
}

void loop() {
  checkPiece();
  afficheCredit();
  newcred=credit;
  achat();
  activeMoteur();
  erreurAchat();
  temps();
      }
