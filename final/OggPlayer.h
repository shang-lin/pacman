/* OggPlayer.h */



/* Revision History
 * 5/05/02: MP3.h generated. author: Shang-Lin Chen
 * 5/19/02: MP3.h changed to OggPlayer.h, since we are using Ogg instead of 
 *          MP3. author: Shang-Lin Chen
 */

#ifndef __OGG_PLAYER_H__
#define __OGG_PLAYER_H__

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ao/ao.h>
#include "Ogg.h"

// Maximum size of audio buffer used for decoding.
#define BUFFSIZE 4096

// Description:
//
// Ogg files are loaded into this object. It is 
// a wrapper for the Ogg object in whatever API we use. 
// 

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
 * This class does not work on many UGCS machines. It has not been integrated 
 * with the rest of the game.
 **/

class OggPlayer{
                // Data Members

 private:
  // The filename of the Ogg file represented by this object. 
  string filename;

  // An Ogg Vorbis decoder
  OggDecoder *decoder;

  // Flag that is true if the Ogg file is currently being played fast,
  // false if the file is played at normal speed.
  bool fast;  

  // The audio buffer that will be written to the audio device.
  char* audio_buffer;

  // An pointer to an instance of the struct encapsulating the audio device. 
  // ao_device is defined in libao.
  ao_device *device;

  // An instance of the struct containing information about the bitstream 
  // format.
  ao_sample_format format;


  // Methods
  
 private:
  
  
 public:
  // Plays the Ogg Vorbis file at normal speed.
  void play( void );
  
  // Stops the Ogg Vorbis file that is currently playing. 
  void stop( void );
  
  // Speeds up the Ogg Vorbis file if it is currently playing at normal 
  // speed. 
  // Not implemented yet.
  void speedUp( void );
  
  // Returns the Ogg Vorbis file to normal speed if it is currently being 
  // played fast.
  // Not implemented yet.
  void normalSpeed( void );
  
  
  // Constructor(s)
  
  // Sets up libao and the OggDecoder. Sets the format of the Ogg Vorbis 
  // bitstream.
  OggPlayer ( string );
  
  
  
  // Destructor

  // Deallocates memory and cleans up libao.
  ~OggPlayer ( void );
  
};

#endif

