#define MIDI_ON 144
#define MIDI_OFF 128
#define RIDE_CYMBAL 0
#define TOM_DRUM 1
#define BASS_DRUM 2
#define SNARE_DRUM 3
#define HI_HAT 4
#define CRASH_CYMBAL 5
#define DRUM_CHANNEL 9
#define RIDE 51
#define TOM 43
#define KICK 35
#define HAT 42
#define SNARE 38
#define CRASH 49
#define THRESHOLD 80

byte rideCymbalVal = 0;
byte tomDrumVal = 0;
byte bassDrumVal = 0;
byte snareDrumVal = 0;
byte hiHatVal = 0;
byte crashCymbalVal = 0;

int rideLed = 7;
int tomLed = 8;
int bassLed = 9;
int snareLed = 10;
int hitHatLed = 11;
int crashLed = 12;

int value;

// midi2Max function declaration with optional arguments
void midi2Max( int cmd, int data1 = -1, int data2 = -1 );

void setup() {
  // put your setup code here, to run once:
  pinMode(rideLed, OUTPUT);
  pinMode(tomLed, OUTPUT);
  pinMode(bassLed, OUTPUT);
  pinMode(snareLed, OUTPUT);
  pinMode(hitHatLed, OUTPUT);
  pinMode(crashLed, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()){
    value = Serial.read(); 
    midi2Max( MIDI_OFF + DRUM_CHANNEL, RIDE, 0 );
    midi2Max( MIDI_OFF + DRUM_CHANNEL, TOM, 0 );
    midi2Max( MIDI_OFF + DRUM_CHANNEL, KICK, 0 );
    midi2Max( MIDI_OFF + DRUM_CHANNEL, SNARE, 0 );
    midi2Max( MIDI_OFF + DRUM_CHANNEL, HAT, 0 );
    midi2Max( MIDI_OFF + DRUM_CHANNEL, CRASH, 0 );
    digitalWrite(rideLed, LOW);
    digitalWrite(tomLed, LOW);
    digitalWrite(bassLed, LOW);
    digitalWrite(snareLed, LOW);
    digitalWrite(hitHatLed, LOW);
    digitalWrite(crashLed, LOW);
    if(value == 51 or value == 59){
      digitalWrite(rideLed, HIGH);
    }
    if(value == 41 or value == 43 or value == 45 or \
    value == 47 or value == 48 or value == 50){
      digitalWrite(tomLed, HIGH);
    }
    if(value == 35 or value == 36){
      digitalWrite(bassLed, HIGH);
    }
    if(value == 38 or value == 40){
      digitalWrite(snareLed, HIGH);
    }
    if(value == 42 or value == 44 or value == 46){
      digitalWrite(hitHatLed, HIGH);
    }
    if(value == 49 or value ==57){
      digitalWrite(crashLed, HIGH);
    }
  }
  rideCymbalVal = analogRead(RIDE_CYMBAL);
  if (rideCymbalVal > THRESHOLD){
    midi2Max( MIDI_OFF + DRUM_CHANNEL, RIDE, 0 );
    midi2Max( MIDI_ON + DRUM_CHANNEL, RIDE, rideCymbalVal/2 );
  }
  tomDrumVal = analogRead(TOM_DRUM);
  if (tomDrumVal > THRESHOLD){
    midi2Max( MIDI_OFF + DRUM_CHANNEL, TOM, 0 );
    midi2Max( MIDI_ON + DRUM_CHANNEL, TOM, tomDrumVal/2 );
  }
  bassDrumVal = analogRead(BASS_DRUM);
  if (bassDrumVal > THRESHOLD){
    midi2Max( MIDI_OFF + DRUM_CHANNEL, KICK, 0 );
    midi2Max( MIDI_ON + DRUM_CHANNEL, KICK, bassDrumVal/2 );   
  }
  snareDrumVal = analogRead(SNARE_DRUM);
  if (snareDrumVal > THRESHOLD){
    midi2Max( MIDI_OFF + DRUM_CHANNEL, SNARE, 0 );
    midi2Max( MIDI_ON + DRUM_CHANNEL, SNARE, snareDrumVal/2 );
  }
  hiHatVal = analogRead(HI_HAT);
  if (hiHatVal > THRESHOLD){
    midi2Max( MIDI_OFF + DRUM_CHANNEL, HAT, 0 ); 
    midi2Max( MIDI_ON + DRUM_CHANNEL, HAT, hiHatVal/2 );
  }
  crashCymbalVal = analogRead(CRASH_CYMBAL);
  if (crashCymbalVal > THRESHOLD){
    midi2Max( MIDI_OFF + DRUM_CHANNEL, CRASH, 0 );
    midi2Max( MIDI_ON + DRUM_CHANNEL, CRASH, crashCymbalVal/2 );
  }
  Serial.println(rideCymbalVal, DEC);
  Serial.println(tomDrumVal, DEC);
  Serial.println(bassDrumVal, DEC);
  Serial.println(snareDrumVal, DEC);
  Serial.println(hiHatVal, DEC);
  Serial.println(crashCymbalVal, DEC);
}
void midi2Max( int cmd, int data1, int data2 )
{
  Serial.print( cmd );
  if ( data1 >= 0 ) {
    Serial.print(' ');
    Serial.print( data1 );
  }
  if ( data2 >= 0 ) {
    Serial.print(' ');
    Serial.print( data2 );
  }
  Serial.println();
}
