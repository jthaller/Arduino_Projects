int speakerPin = 12;
// https://i.pinimg.com/736x/10/18/2a/10182afd25f96627904a58765b18e8cd.jpg 

void setup() {
pinMode(speakerPin,OUTPUT);
}

void loop() {

play("f", 4); //the
play("F",4); //simp
play("F#",12); //sons


play("b",.5);
play("b",.5);
play("b",.5);
play("e",.5);

play(" ",.5);
play("b",.5);
play("b",.5);
play("b",.5);

play("b",.5);
play("b",.5);
play("b",.5);
play("e",.5);

play("b",.5);
play("e",.5);
play("b",.5);
play("e",.5);

play("b",1.5);
play("F#",1);

play("G#",1);
play("B",.5);

play("A",1.5);
play("F#",1);

play("D",1);
play("B",.5);

play("G#",.5);
play("G#",.5);
play("G#",.5);
play("A",2.5);



}





void play( String note, double beats)
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


tone(speakerPin,currentFrequency, beats * beatLength);
delay(beats * beatLength);
delay(50);
}

