const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;

//left motor
const int PWMB = 10;
const int BIN2 = 9;
const int BIN1 = 8;

int switchPin = 7;
const int driveTime = 20;
const int turnTime = 8;

String botDirection;
String distance;
String motorSpeed = "0";
int speed =0;

void setup() {
  // put your setup code here, to run once:
pinMode(switchPin, INPUT_PULLUP);
pinMode(AIN1,OUTPUT);
pinMode(AIN2,OUTPUT);
pinMode(PWMA, OUTPUT);

pinMode(BIN1, OUTPUT);
pinMode(BIN2,OUTPUT);
pinMode(PWMB,OUTPUT);

Serial.begin(9600);

Serial.println("Enter a direction followed by a distance followed by a speed (0-255).");
Serial.println("f - forward, b = backward, r = turn right, 1 = turn left");
Serial.println("Example command: f 50 250");

}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(digitalRead(7) == LOW) // switch is in on position
  {
    if (Serial.available() > 0)
    {
      botDirection = Serial.readStringUntil(' ');
      distance = Serial.readStringUntil(' ');
      motorSpeed = Serial.readStringUntil(' ');

      Serial.print(botDirection);
      Serial.print(" ");
      Serial.print(distance.toInt());
      Serial.print(" ");
      Serial.println(motorSpeed.toInt());
      speed= motorSpeed.toInt();

      if(botDirection == "f")
      {
          rightMotor(speed); //int drive speed
          leftMotor(speed); // int drive speed
          delay(driveTime*distance.toInt());

          rightMotor(0);
          leftMotor(0);
      }
      else if(botDirection == "b")
      {
         rightMotor(-speed); //int drive speed
          leftMotor(-speed); // int drive speed
           delay(driveTime*distance.toInt());

          rightMotor(0);
          leftMotor(0);   
      }
      else if(botDirection=="r")
      {
        rightMotor(-200);
        leftMotor(255);
        delay(turnTime * distance.toInt());

        rightMotor(0);
        leftMotor(0);
      }
      else if(botDirection == "l")
      {
        rightMotor(255);
        leftMotor(-255);

        delay(turnTime*distance.toInt());

       rightMotor(0);
       leftMotor(0);  
      }
    } 
  }
  else
  {
      rightMotor(0);
      leftMotor(0);  
  }
}

  
// if (Serial.available() > 0)
// {
//   motorSpeed = Serial.parseInt();
//   Serial.print("Motor Speed: ");
//   Serial.println(motorSpeed);
// }

// if(digitalRead(7) == LOW) // if switch is on
// {
//   spinMotor(motorSpeed);
// }
// else{
//   spinMotor(0);
// }

// }


void rightMotor( int motorSpeed)
{
  if (motorSpeed > 0){
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
  }
  else if (motorSpeed < 0){
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,HIGH);
  }
  else{
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
}

void leftMotor( int motorSpeed)
{
  if (motorSpeed > 0){
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,LOW);
  }
  else if (motorSpeed < 0){
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,HIGH);
  }
  else{
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,LOW);
  }
  analogWrite(PWMB, abs(motorSpeed));
}
