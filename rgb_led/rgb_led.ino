void setup() {
  // put your setup code here, to run once:
pinMode(12,OUTPUT);
pinMode(8,OUTPUT);
pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

pulseGreen();
delay(5);
pulseRed();
delay(5);
pulseBlue();
delay(5);

}
//PULSE GREEN
void pulseGreen(){
  for(int i=200;i>0;i--)
{
  analogWrite(12,i);
  delay(5);
}

for(int i=0;i<200;i++)
{
  analogWrite(12,i);
  delay(5);
}
}

//PULSE RED
void pulseRed(){
for(int i=200;i>0;i--)
{
  analogWrite(2,i);
  delay(5);
}

for(int i=0;i<200;i++)
{
  analogWrite(2,i);
  delay(5);
}
}


//PULSE BLUE
void pulseBlue(){
for(int i=200;i>0;i--)
{
  analogWrite(8,i);
  delay(5);
}

for(int i=0;i<200;i++)
{
  analogWrite(8,i);
  delay(5);
}
}



