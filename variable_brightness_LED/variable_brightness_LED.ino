void setup() {
  // put your setup code here, to run once:

pinMode(6,OUTPUT);
Serial.begin(9600); //bog rate
}

void loop() {
  // put your main code here, to run repeatedly:

int potVal= analogRead(A0); //between 0-1023
/*
float normalized = potVal/1023.0; //between 0-1
int voltage = normalized*255; //between 0-255
*/


int voltage = map(potVal,120,355,0,255);
analogWrite(6,voltage);

Serial.println(potVal);
}
