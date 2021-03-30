void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
float val = analogRead(A0);
val=val*5.0/1024.0;
double temp = (val-.5)*100.0;

Serial.print(temp);
Serial.println(" degrees C");

}
