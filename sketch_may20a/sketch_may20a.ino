void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

int potVal = analogRead(A1); //0-1023
digitalWrite(13,HIGH);
delay(potVal);
digitalWrite(13,LOW);
delay(potVal);
Serial.println(potVal);

}
