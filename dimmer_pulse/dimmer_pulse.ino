void setup() {
  // put your setup code here, to run once:
pinMode(10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//0-255, where 255 is 5 volts. So 128 is 50% duty cycle

for(int i=256;i>0;i--)
{
  analogWrite(10,i);
  delay(5);
}

for(int i=0;i<256;i++)
{
  analogWrite(10,i);
  delay(5);
}


}
