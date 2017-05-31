/* OggPlayer.cc */

/* Revision History
 * 5/5/02: Generated MP3.cc. author: Shang-Lin Chen
 * 5/23/02: Changed to OggPlayer.cc. author: Shang-Lin Chen
 * 6/09/02: Tried to implement play() with OSS. author: Shang-Lin Chen
 * 6/12/02: I decided to use libao instead of OSS. play() now plays decoded 
 *          Ogg Vorbis bitstreams successfully.
 *          author: Shang-Lin Chen
 * 6/13/02: Integrated with decoder.
 *          author: Shang-Lin Chen
 * 
 */

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "OggPlayer.h"
#include <fstream.h>
#include <stdio.h>
#include <iostream>


/**
 * Description:
 *
 * OggPlayer is a wrapper class for  a playable Ogg Vorbis file in the 
 * libvorbis and libao APIs.
 * 
 * libvorbis is used to decode the Ogg Vorbis file.
 * The libao API (http:://www.xiph.org/ogg/vorbis) is used to play the decoded
 * Ogg Vorbis file.
 *
 **/


// Plays the Ogg Vorbis file at normal speed.
void OggPlayer::play() {

  int len;  

  // Find the name of the WAV file where raw audio will be written by the 
  // decoder.
  int ext_start = filename.rfind(".");
  const char *aufile;
  string tmp = filename.substr(0, ext_start) + ".wav";
  aufile = tmp.c_str();

  // The decoded bitstream is stored in a raw audio file.
  decoder->decode(aufile);

  // Print out information about the currently playing Ogg file.
  cout<<"Now playing: "<<filename<<endl; 
  char **comments = decoder->getUserComments();
  while (*comments){
    cout<<*comments<<endl;
    comments++;
  }

 

  // The following block of code uses the OSS API, which I decided not to use.
#ifdef _OSS
  cerr<<"OSS being used..."<<endl;

  /* Open the device */
  if ((audio_fd=open("/dev/dsp", O_WRONLY, 0)) == -1) {
    /* Open the device failed */
    perror ("/dev/dspW");
    exit (1);
  }

  format = AFMT_U8;
  if (ioctl(audio_fd, SNDCTL_DSP_SETFMT, &format) == -1){
    /* Fatal error, format not supported */
    perror ("SNDCTL_DSP_DETFMT");
    exit (1);
  }

  // Check that this format is supported
  if (format != AFMT_U8){
    cerr<<"8-bit format not supported"<<endl;
    exit(1);
  }

  /* Select channel */
  channel = 2;
  if (ioctl(audio_fd, SNDCTL_DSP_CHANNELS, &channel) == -1){
    /* Fatal error, channel not supported */
    perror ("SNDCTL_DSP_CHANNELS");
    exit (1);
  }

  speed = 44100;
  speed /= 2;
  //speed = 22050;
  //speed = 8000;
  if (ioctl(audio_fd, SNDCTL_DSP_SPEED, &speed)){
    /* Fatal error, sample rate not supported */
    perror ("SNDCTL_DSP_SPEED");
    exit (1);
  }

  ifstream raw_audio(src_file);
  if (!raw_audio){
    cerr<<"Raw audio file could not be opened."<<endl;
  }
  char ch;
  int i=0;
  cerr<<"about to read the raw audio file."<<endl;
  while (raw_audio.get(ch)){
    cerr<<"Got a char from the raw audio file."<<endl;
    if (i<BUFFSIZE){
      audio_buffer[i] = ch;
      cerr<<"stored char in audio buffer"<<endl;
      i++;
    }
    else if (i==BUFFSIZE){
      cerr<<"writing audio buffer to sound card"<<endl;
      if ((len = write(audio_fd, audio_buffer, BUFFSIZE))==-1){
	cerr<<"Audio write error."<<endl;
	exit(1);
      }
      i = 0;
    }
    else{}

    // cerr<<"done playing"<<endl;  

  }
  raw_audio.close();
  cerr<<"done playing"<<endl;
#endif

  
  bool eof = false; // not at the end of the raw audio file
  int default_driver = ao_default_driver_id();

  // Open the default audio device.  
  device = ao_open_live(default_driver, &format, NULL);
  if (device==NULL){
    cerr<<"Error opening device."<<endl;
    return;
  }

  // Open the raw audio input file.
  ifstream raw_audio(aufile);
  if (!raw_audio){
    cerr<<"Raw audio file could not be opened."<<endl;
  }

  char ch;
  int i=0;

  // Set the size of the buffer that will be written to the audio
  // device.
  int buf_size = format.bits/8 * format.channels * format.rate;
  audio_buffer = new char[buf_size];

#ifdef NOT_WORKING
  while (raw_audio.get(ch)){
    cerr<<"Got a char from the raw audio file."<<endl;
    if (i<BUFFSIZE){
      audio_buffer[i] = ch;
      cerr<<"stored char in audio buffer"<<endl;
      i++;
    }
    else if (i==BUFFSIZE){
      cerr<<"writing audio buffer to sound card"<<endl;
      ao_play(device, audio_buffer, BUFFSIZE);
      i = 0;
    }
    else{}

    // cerr<<"done playing"<<endl;  

    }

#endif


  // Get chars from the input file while the end-of-file hasn't been reached 
  // yet...
  while (!eof){

    // Fill the buffer with characters from the input file.
    for (int i=0; i<buf_size; i++){
 
      // If the input file has ended, exit the loop.
      if (!(raw_audio.get(ch))){
	cout<<"Done playing."<<endl;
	eof = true;
	break;
      }
      
      // If the input ile has not ended, copy the char from the 
      // input file to the audio buffer.
      else{
	audio_buffer[i] = ch;
      }
    }

    // Write the buffer to the audio device to play sound.
    ao_play(device, audio_buffer, buf_size);
  }	

  // Close the device when playing is done.
  ao_close(device);
  raw_audio.close();

}

// Stops the Ogg Vorbis file that is currently playing.
void OggPlayer::stop( void ){

}

// Speeds up the Ogg Vorbis file if it is currently playing at normal speed.
// Not implemented ye.
void OggPlayer::speedUp( void ) {
  // Not done yet
}

// Returns the Ogg Vorbis file to normal speed if it is currently being played
// fast.
// Not yet implemented.
void OggPlayer::normalSpeed( void ) {
  // If the file is already playing at normal speed, do nothing.
  if (!fast){}

  // Not done yet
}



// Constructor(s)

// Sets up libao and the OggDecoder. Sets the format of the Ogg Vorbis 
// bitstream.
//
// args: string fname- name of the raw audio file to play
OggPlayer::OggPlayer ( string fname ) {
  filename = fname;

  // Initialize the decoder.
  decoder = new OggDecoder(filename.c_str());
  fast = false;

  //audio_buffer = new char[BUFFSIZE];
  device = NULL; // for now, the device is undefined

  // Initialize libao.
  ao_initialize();

  // Initialize formatting information.
  format.bits = 16; 
  format.channels = 2; // stereo
  format.rate = 44100; // standard sample rate for digital audio
  format.byte_format = AO_FMT_LITTLE; // little-endian

}



// Destructor

// Deallocates memory and cleans up libao.
OggPlayer::~OggPlayer ( void ) {
  
  //ao_shutdown();

  delete[] audio_buffer;
}

