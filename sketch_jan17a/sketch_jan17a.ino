void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int i;

  //S
  for(i=0;i<3;i++)
  {
digitalWrite(13,HIGH);
delay(300);
digitalWrite(13,LOW);
delay(230);
}

//O
for(i=0;i<3;i++)
{
digitalWrite(13,HIGH);
delay(900);
digitalWrite(13,LOW);
delay(230);
}

//S
  for(i=0;i<3;i++)
  {
digitalWrite(13,HIGH);
delay(300);
digitalWrite(13,LOW);
delay(300);
}

//Full Stop
digitalWrite(13,HIGH);
delay(300);
digitalWrite(13,LOW);
delay(230);
digitalWrite(13,HIGH);
delay(900);
digitalWrite(13,LOW);
delay(230);
digitalWrite(13,HIGH);
delay(300);
digitalWrite(13,LOW);
delay(230);
digitalWrite(13,HIGH);
delay(900);
digitalWrite(13,LOW);
delay(230);

}
