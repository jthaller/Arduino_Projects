//THIS PROGRAM DOESN'T WORK. ALSO DON'T PLUT INTO COM 1 OR 0. IT BREAKS YOUR ARDUINO.

int speakerPin = 12;

void setup() {
pinMode(speakerPin,OUTPUT);
pinMode(5,INPUT_PULLUP);
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
}

void loop() {
  if(!digitalRead(5)){
    play("c");
  }

  else if(!digitalRead(2)){
    play("e");
  }

  
  else if(!digitalRead(3)){
    play("g");
  }

  else if(!digitalRead(3)){
    play("b");
  }
  
  else{
    noTone(12);
  }

}


void play( String note)
{
int numNotes=23;
String notes[]={"c","c#","d","d#","e","f","f#","g","g#","a","a#","b","C","C#","D","E","F","F#","G","G#","A","A#","B"," "};
int frequencies[]={131,139,147,155,165,175,185,196,208,220,233,247,262,277,294,311,330,349,370,392,415,440,466,494,0};

int currentFrequency=0;
  int beatLength=200;
for(int i=0;i<numNotes;i++)
{
  if (notes[i] == note){
    currentFrequency = frequencies[i];
  }
}


tone(speakerPin,currentFrequency);
delay(50);
}

