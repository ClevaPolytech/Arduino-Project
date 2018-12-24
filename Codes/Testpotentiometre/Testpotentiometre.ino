int sortie=5;
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(float(analogRead(sortie)*5)/1023);
  
  delay(50);
}
