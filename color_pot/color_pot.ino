void setup() {
  // put your setup code here, to run once:

pinMode(5,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

int potVal= analogRead(A5); //between 0-1023
float normalized = potVal/1023.0; //between 0-1
int voltage = normalized*255; //between 0-255

if(potVal<255){
analogWrite(5,voltage);
analogWrite(10,255-voltage);
}

if(potVal>255 && potVal<510){
analogWrite(10,voltage);
analogWrite(5,510-voltage);
analogWrite(11,510-voltage);
}

if(potVal>510 && potVal<765){
analogWrite(11,voltage);
analogWrite(10,765-voltage);
analogWrite(5,765-voltage);
}

if(potVal>565){
analogWrite(10,voltage);
analogWrite(11,565-voltage);
}



analogWrite(11,voltage);

}
