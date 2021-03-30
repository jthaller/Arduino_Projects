void setup() {
  // put your setup code here, to run once:
pinMode(12,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
int A = 440;
int B = 494;
int G = 392;
int highG=784;
int highB = 988;

tone(12,B,50000);
delay(200);

tone(12,G,50000);
delay(200);

tone(12,highG,50000);
delay(200);

tone(12,G,50000);
delay(200);

tone(12,highG,50000);
delay(200);

tone(12,highB,50000);
delay(200);

tone(12,highG,50000);
delay(200);

tone(12,G,50000);
delay(200);

tone(12,highB,50000);
delay(200);

tone(12,highG,50000);
delay(200);

tone(12,G,50000);
delay(200);

tone(12,highG,200);
delay(600);

}
