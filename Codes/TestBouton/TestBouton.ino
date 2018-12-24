int bouton1;
int bouton2=9;
int bouton3;
int bouton4;

void setup() {
  Serial.begin(9600);
  pinMode(bouton1, INPUT);
  Serial.print("debut du programme");
}

void loop() {
  if(digitalRead(bouton2)==LOW){
    Serial.println("bouton préssé");
    delay(100);}
    }
