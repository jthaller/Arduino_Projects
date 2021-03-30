/* Arduino Altimeter

This arduino altimeter has an LCD screen that displays the altitude and temperature.  When the switch is toggled, it switches between american and SI units.
The potentiometer cahnges the screen brightness and the yellow button toggles between the alt/temp and what floor of TPL you are on.  It assumes that you 
start the program while in the lab on the second floor. The RGB LED changes colors when you change floors in TPL.


How to use the BMP180:
https://www.sparkfun.com/products/11824

Hardware connections:

- (GND) to GND
+ (VDD) to 3.3V

(WARNING: do not connect + to 5V or the sensor will be damaged!)

You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:

Any Arduino pins labeled:  SDA  SCL
Uno, Redboard, Pro:        A4   A5
Mega2560, Due:             20   21
Leonardo:                   2    3

Leave the IO (VDDIO) pin unconnected. This pin is for connecting
the BMP180 to systems with lower logic levels such as 1.8V

The SFE_BMP180 library uses floating-point equations developed by the
Weather Station Data Logger project: http://wmrx00.sourceforge.net/

Basic BMP180 code provided by:
V10 Mike Grusin, SparkFun Electronics 10/24/2013
V1.1.2 Updates for Arduino 1.6.4 5/2015
*/

// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);



SFE_BMP180 pressure; //create an SFE_BMP180 object, here called "pressure":
double T; //Temperature
String aUnit = " m";
//char degreeSymbol = (char) 248;
//String tUnit = degreeSymbol + " C";
String tUnit = " deg C";
double baseline; // baseline pressure
int switchPin = 7;
int i=0; //the iterator
double aVals [10];
double aAvg =0;
const int buttonPin = 3;
bool buttonPressed = false;
int storey;

//this is a square degree symbol. 
//we decided it looked best, but it's up to you
byte degreeSymbol[8] = {
  B00011,
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

//this is a diamond-like shaped degree symbol
// byte degreeSymbol[8] = {
//   B00010,
//   B00101,
//   B00010,
//   B00000,
//   B00000,
//   B00000,
//   B00000,
// };


// *************************VOID SETUP *********************************
void setup()
{

  //LCD
  lcd.begin(16,2); //lcd is 16char wide and 2 tall
  lcd.clear();
  //SWITCH UNITS TOGGLE
  pinMode(switchPin, INPUT_PULLUP);
  //RGB LED
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT); 
  pinMode(6,OUTPUT);
  //pin 3 is the yellow button
  pinMode(3,INPUT_PULLUP);

  lcd.createChar(0, degreeSymbol); // Create a new degrees character on the LCD

  Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

  // Get the baseline pressure:
  baseline = getPressure();
  //print it in the serial
  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");  
}

//**********************************LOOP******************************************
void loop()
{ 
  //if yellow button is pressed, toggle boolean buttonPressed
  //this is so you can switch between units
  if(!digitalRead(3)){ 
    buttonPressed=!buttonPressed;
    i=10; //set iterator to 10 so you automatically switch the screen, 
    //without having to wait for 10 altitude measurements 
  }

  if (i>9) {
    
     i=0;
     takeAAvg(); //get average of last 10 altitude measurements.
      //print on LCD your alt and temp
    if (!buttonPressed) {
      lcd.clear();  
      lcd.setCursor(0,0);
      lcd.print("Alt: ");
      lcd.print(aAvg); 
      lcd.print(aUnit);
  
      lcd.setCursor(0,1);
    
      lcd.print("Temp: ");
      lcd.print(T);
      lcd.write(byte(0));
      lcd.print(tUnit);
    } else { //print on lcd your TPL floor
      lcd.clear();
      lcd.setCursor(0,0);
      switch (storey) {
        case 1:
          lcd.print("1st Floor");
          break;
        case 2:
          lcd.print("2nd Floor");
          break;
        case 3:
          lcd.print("3rd Floor");
          break;
        case 4:
          lcd.print("4th Floor");
          break;
        default:
          lcd.print("Calculating...");
          
      }
      
    }
  }


  double a,P; //altitude and pressure
  
  // Get a new pressure reading:

  P = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:
  a = pressure.altitude(P,baseline);

  aVals[i]=a; //set the ith value of aVals to be the altitude you just measured
  i++;


  char status = pressure.startTemperature(); //start the temperature reading
  

  //here in the loop, a is always in metric.
  //Change color of LED depending on what floor you're on
  if (a < 3.8){
   analogWrite(4,255);
   analogWrite(5,0);
   analogWrite(6,0);
   storey = 2;
  }

  else if (a<8 && a>3.8){
   analogWrite(4,0);
   analogWrite(5,255);
   analogWrite(6,0);
   storey = 3;
  }

  else if (a>7.9){
   analogWrite(4,255);
   analogWrite(5,255);
   analogWrite(6,255);
   storey = 4;
  }

  if (a<-3.8){
   analogWrite(4,0);
   analogWrite(5,0);
   analogWrite(6,255);
   storey = 1;
  }


  
  // Serial Printing
  Serial.print("relative altitude: ");
  if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
  Serial.print(a,1);
  Serial.print(" meters, ");
  if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
  Serial.print(a*3.28084,0);
  Serial.println(" feet");
  Serial.print(aAvg); Serial.println(" ");

//are you done measureing the temp yet?
  if (status != 0){

delay(status);
status = pressure.getTemperature(T);
if (status != 0){
//switch is in SI units
    if(digitalRead(switchPin) == LOW){
    aUnit = " m";
    tUnit = "C";
    a = pressure.altitude(P,baseline); 
   // pressure.getTemperature(T);
    Serial.print(T); Serial.println(" Deg C");
  }
  else //switch is in American units
  {
    aUnit = " ft";
    tUnit = "F";
    a = pressure.altitude(P,baseline)*3.28084;
    //pressure.getTemperature(T);
    T = T*1.8 + 32.0;
    Serial.print(T); Serial.println(" Deg F");
  }

}
}
  
  //this delay determines how many alt readings you get.
  //we found 100 to work best for the yellow toggle
  delay(100);

}

//*****************************GET PRESSURE*************************************
double getPressure()
{
  char status;
  double P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.  
// IS THIS IMPORTANT? COULD WE JUST NEED TO REFERENCE THE ADDRESS INSTEAD OF THE VALUE? ****************************8

    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}


//get the average altitude from the last 10 measurements
void takeAAvg(){
 double sum=0; 
 for (int j = 0; j < 10; ++j)
 {
     sum += aVals[j];
 }
 aAvg = ((float)sum)/10.0; //or cast sum to double before division
}







