int port=1;
void setup() {
Serial.begin(9600);
}

void loop() {
int var=analogRead(port);
Serial.print(var);
if (var<400){Serial.println(" detection : OK");}
else{Serial.println(" detection : NO");}
delay(100);


}
