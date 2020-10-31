//*****************************************//
//  midiout.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI output.
//
//*****************************************//

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"

// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

#define BASS_CHANNEL 0
#define DRUM_CHANNEL 9
#define GUITAR_CHANNEL 1

#define BASS_PROGRAM 39
#define GUITAR_PROGRAM 28
#define MAIN_VOLUME 100

#define PROGRAM_CHANGE 192
#define CONTROL_CHANGE 176
#define MIDI_ON 144
#define MIDI_OFF 128

#define GAP_IN_MS 175

// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
bool chooseMidiPort( RtMidiOut *rtmidi );
void setNoteMessage(std::vector<unsigned char> &message, int m1, int m2, int m3);

int main( )
{
  RtMidiOut *midiout = nullptr;
  std::vector<unsigned char> bass_message;
  std::vector<unsigned char> guitar_message;
  std::vector<unsigned char> drum_message;

  // RtMidiOut constructor
  try {
    midiout = new RtMidiOut();
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }
  // Call function to select port.
  try {
    if (!chooseMidiPort(midiout)) goto cleanup;
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    goto cleanup;
  }

  // Send out a series of MIDI messages.

  // Program change for bass
  bass_message.push_back(PROGRAM_CHANGE + BASS_CHANNEL);
  bass_message.push_back(BASS_PROGRAM);
  midiout->sendMessage( &bass_message );

  // Program change for guitar
    guitar_message.push_back(PROGRAM_CHANGE + GUITAR_CHANNEL);
    guitar_message.push_back(GUITAR_PROGRAM);
    midiout->sendMessage( &guitar_message );

    SLEEP( GAP_IN_MS );
    // Set time code for bass and guitar
    bass_message[0] = 0xF1;
    bass_message[1] = 60;
  midiout->sendMessage( &bass_message );

    guitar_message[0] = 0xF1;
    guitar_message[1] = 60;
    midiout->sendMessage( &guitar_message );

    drum_message.push_back(0xF1);
    drum_message.push_back(60);
    drum_message.push_back(0);
    midiout->sendMessage( &drum_message );

  // Control Change: 176, 7, 100 (volume)
  bass_message[0] = CONTROL_CHANGE + BASS_CHANNEL;
    bass_message[1] = 7;
  bass_message.push_back(MAIN_VOLUME);
  midiout->sendMessage( &bass_message );

    guitar_message[0] = CONTROL_CHANGE + GUITAR_CHANNEL;
    guitar_message[1] = 7;
    guitar_message.push_back(MAIN_VOLUME);
    midiout->sendMessage( &guitar_message );

    while (true) {
        /*
         * @timestamp: 0
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 36, 90);
        midiout->sendMessage(&drum_message);


        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 1
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 36, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 2
        */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
        * @timestamp: 3
        */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 41, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 4
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 41, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 40, 90);
        midiout->sendMessage(&drum_message);
        SLEEP(GAP_IN_MS);

        /*
        * @timestamp: 5
        */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 40, 0);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
        * @timestamp: 6
        */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 36, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
        * @timestamp: 7
        */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 36, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 36, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 8
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 36, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 9
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 36, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 10
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 36, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 11
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 12
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 40, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 13
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 40, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 14
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 36, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);

        /*
         * @timestamp: 15
         */
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 44, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_OFF + DRUM_CHANNEL, 36, 0);
        midiout->sendMessage(&drum_message);
        setNoteMessage(drum_message, MIDI_ON + DRUM_CHANNEL, 44, 90);
        midiout->sendMessage(&drum_message);

        SLEEP(GAP_IN_MS);


    }

  // Sysex: 240, 67, 4, 3, 2, 247
  bass_message[0] = 240;
    bass_message[1] = 67;
    bass_message[2] = 4;
  bass_message.push_back(3 );
  bass_message.push_back(2 );
  bass_message.push_back(247 );
  midiout->sendMessage( &bass_message );

  // Clean up
 cleanup:
  delete midiout;

  return 0;
}

bool chooseMidiPort( RtMidiOut *rtmidi )
{
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
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      std::cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while ( i >= nPorts );
  }

  std::cout << "\n";
  rtmidi->openPort( i );

  return true;
}

void setNoteMessage(std::vector<unsigned char> &message, int m1, int m2, int m3) {
    message[0] = m1;
    message[1] = m2;
    message[2] = m3;
}
