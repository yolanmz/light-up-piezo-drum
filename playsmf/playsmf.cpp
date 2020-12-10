// Based on a simple program to test the MidiFileIn class by reading and playing
// a single track from a given Standard MIDI file by Gary Scavone, 2003.

// Compile the program by `make` command 
// Create a folder midifiles and add your MIDI file into the folder 
// Run `./playsmf midifiles/mymidi.mid` (normal speed by default)
// Run `./playsmf midifiles/mymidi.mid 0.5` (half speed)

#include "MidiFileIn.h"
#include "RtMidi.h"
#include <signal.h>
#include <unistd.h>

using namespace stk;

bool done = false;
static void finish(int ignore){ done = true; }
bool chooseMidiPort( RtMidi *rtmidi );

void usage(void) {
  // Error function in case of incorrect command-line
  // argument specifications.
  std::cout << "\nusage: playsmf file speed <port>\n";
  std::cout << "   where file = a standard MIDI file,\n";
  std::cout << "   and an optional speed integer identifier can be specified\n";
  std::cout << "   (default = 0) or a value of -1 to use a virtual MIDI output port.\n\n";
  exit(0);
}

int main( int argc, char *argv[] )
{
  RtMidiOut *midiout = 0;
  float speed = 1.0;
  if ( argc == 3 ){
    speed = atof( argv[2]);
  } 
  if ( argc < 2 || argc > 3 ) usage();

  // Attempt to instantiate MIDI output class.
  try {
    midiout = new RtMidiOut();
    if ( chooseMidiPort( midiout ) == false ) goto cleanup;
  }
  catch ( RtMidiError& error ) {
    error.printMessage();
    exit(0);
  }

  // Install an interrupt handler function.  Type "ctrl-c" to quit the
  // program.
  (void) signal(SIGINT, finish);
  
  try {
    MidiFileIn midiFile( argv[1] );

    // Print a little information about the file.
    std::cout << "\nThe MIDI file (" << argv[1] << ") information:\n";
    std::cout << "  - format = " << midiFile.getFileFormat() << "\n";
    std::cout << "  - tracks = " << midiFile.getNumberOfTracks() << "\n";
    std::cout << "  - seconds / ticks = " << midiFile.getTickSeconds() << "\n";
    std::cout << "  - speed = " << speed << "\n";
    std::cout << "\nPress <enter> to start reading/playing ... type Ctrl-C to quit.\n";
    char input;
    std::cin.get(input);
    
    int nTracks = midiFile.getNumberOfTracks();
    std::vector<long> ticks( nTracks );
    std::vector<std::vector<unsigned char> > events( nTracks );
    for (int j=0; j<nTracks; j++ ){
      ticks[j] = midiFile.getNextMidiEvent( &events[j], j );
      if ( events[j].size() == 0 ){
        ticks[j] = -1;
      } 
    } 
    unsigned long minTicks;
    unsigned int minTrack;
    int eventsSize ;
    while ( !done ) {
      for (int k=0; k<nTracks; k++){
        // Give an initial value for minTick 
        if (ticks[k] >= 0){
            minTicks = ticks[k];
            break;
        }    
      }      
      for (int k=0; k<nTracks; k++){
        eventsSize = eventsSize + events[k].size();
        if (ticks[k] < minTicks && ticks[k] >= 0){   
          //find the minTicks
          minTicks = ticks[k];
          minTrack = k;
        }
      } 
      //Determine if all events are done for all tracks
      if (eventsSize == 0){
          done = true;
          goto clear;
      }
      else{
        eventsSize = 0;
      }
      Stk::sleep( (unsigned long) (minTicks * midiFile.getTickSeconds( minTrack ) * (1000/speed)));
      for (int i=0; i<nTracks;i++){
        ticks[i] -= minTicks;
        if ( ticks[i] == 0 ) { // send out this event and reload
          midiout->sendMessage( &events[i] );

          ticks[i] = midiFile.getNextMidiEvent( &events[i], i );
          if ( events[i].size() == 0 ) {
            ticks[i] = -1;
          }
        }    
      }
    }
  clear:
    // Send an "all notes off" to the synthesizer on all 16 channels.
    for ( int i=0; i<16; i++ ) {
      events[0].clear();
      events[0].push_back( 0xb0+i );
      events[0].push_back( 0x7b );
      events[0].push_back( 0x0 );
      midiout->sendMessage( &events[0] );
    }
  }
  catch ( StkError & ) {
    // You might want to do something more useful here.
    std::cout << "\nAborting program!\n";
    goto cleanup;
  }

cleanup:
  delete midiout;

  return 0;
}

bool chooseMidiPort( RtMidi *rtmidi )
{
  bool isInput = false;
  if ( typeid( *rtmidi ) == typeid( RtMidiIn ) )
    isInput = true;

  if ( isInput )
    std::cout << "\nWould you like to open a virtual input port? [y/N] ";
  else
    std::cout << "\nWould you like to open a virtual output port? [y/N] ";

  std::string keyHit;
  std::getline( std::cin, keyHit );
  if ( keyHit == "y" ) {
    rtmidi->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    if ( isInput )
      std::cout << "No input ports available!" << std::endl;
    else
      std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      if ( isInput )
        std::cout << "  Input port #" << i << ": " << portName << '\n';
      else
        std::cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
    std::getline( std::cin, keyHit );  // used to clear out stdin
  }

  std::cout << "\n";
  rtmidi->openPort( i );

  return true;
}
