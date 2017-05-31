/* Ogg.h */



/* Revision History
 * 5/27/02: Created Ogg.h. author: Shang-Lin Chen
 * 6/01/02: Added decodable flag and changed decode() so that it returns a 
 *          string. author: Shang-Lin Chen
 * 6/09/02: Added ovf_comm and ovf_info structs. Added getUserComments() and
 *          getEncoderInfo(). author: Shang-Lin Chen
 */

#ifndef __OGG_DECODER_H__
#define __OGG_DECODER_H__

// libvorbis and libvorbisfile includes
#include<vorbis/codec.h>
#include<vorbis/vorbisfile.h>

#include<string>

using namespace std;


/**
 *
 * Description:
 * 
 * The OggDecoder class is a low-level decoder for Ogg Vorbis files. It uses 
 * the libvorbisfile API (http:://www.xiph.org/ogg/vorbis) to decode an Ogg 
 * Vorbis bitstream and to extract information about the bitstream.
 * 
 **/
class OggDecoder{

  // Data members

 private:

  // The main data structure encapsulateing an Ogg bitstream. Defined in 
  // libvorbisfile.
  OggVorbis_File ovf;

  // Data structures for the bitstream's header information.
  vorbis_comment *ovf_comm; //user comments- artist info
  vorbis_info *ovf_info; // bitstream info

  // Name of the Ogg Vorbis file to be decoded.
  const char *filename;

  // A pointer to the Ogg Vorbis file.
  FILE *file_ptr;

  // Flag that is true if the bitstream is decodable, false otherwise.
  bool decodable;

  // Methods

 private:

  // Sets up an OggVorbis_File struct by calling the libvorbisfile method 
  // ov_open. Returns 1 if successful, 0 otherwise. 
  int open();

 public:


  // Decodes the Ogg Vorbis file encapsulated by this object and writes the
  // resulting raw audio data to an output file. Returns 1 on success, 0 on
  // failure.
  //
  // args: const char *outf- name of the output file where the raw audio data
  //                        should be written
  int decode(const char *);
  

  // Returns an array of C-style strings containing user comments about the Ogg
  // Vorbis bitstream. User comments typically include the artist, song, and 
  // album names, as well as any other comments the creator of the file
  // might have added.
  char **getUserComments();
  

  // Returns the name and version of the encoder that created this Ogg Vorbis
  // bitstream.
  char *getEncoderInfo();

 
  // Constructor

  // Sets up the libvorbisfile data structures.
  //
  // args: const char *fname- name of the Ogg Vorbis file to be decoded
  OggDecoder(const char *);


  // Destructor

  // Tears down the OggVorbis_File struct and closes any open file pointers.
  ~OggDecoder();
};

#endif
