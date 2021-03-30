const int trigPin = 11;
const int echoPin =12;

const int redPin = 3;
const int greenPin =5;
const int bluePin =6;
const int speakerPin = 13;


float distance = 0;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);

//set RGB LED PINS to output
pinMode(greenPin,OUTPUT);
pinMode(redPin,OUTPUT);
pinMode(bluePin,OUTPUT);
pinMode(speakerPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
distance = getDistance();

Serial.print(distance);
Serial.println(" in");

if(distance <= 10)
{
  //make RGB LED red
  analogWrite(redPin,255);
  analogWrite(greenPin,0);
  analogWrite(bluePin,0);
  tone(speakerPin,440,500);
delay(200);
}

else if(10 < distance && distance < 20)
{
  //make RGB yellow
  analogWrite(redPin,255);
  analogWrite(greenPin,50);
  analogWrite(bluePin,0);
}

else{
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);
}

delay(50);
}

float getDistance(){
  float echoTime;
  float calculatedDistance;

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  echoTime = pulseIn(echoPin,HIGH);
  calculatedDistance = echoTime / 148.0;
  return calculatedDistance;
}
