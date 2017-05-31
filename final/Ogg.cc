/* Ogg.cc */



/* Revision History
 * 5/27/02: Created Ogg.cc. author: Shang-Lin Chen
 * 5/30/02: Implemented initialization and destruction of the OggVorbis_File
 *          struct. author: Shang-Lin Chen
 * 6/01/02: Implemented decoding of an Ogg file.
 *          author: Shang-Lin Chen
 * 6/09/02: Added getUserComments and getEncoderInfo methods/
 *          author: Shang-Lin Chen
 * 6/12/02: Implemented decoder so that it writes raw audio data to a file.
 *          TO-DO: This should be changed in the future, since raw audio files
 *          take a lot of space.
 *          author: Shang-Lin Chen
 */

#include "Ogg.h"
#include<iostream>
#include<fstream>
#include<stdio.h>

/**
 * Class description:
 *
 * The OggDecoder class is a low-level decoder for Ogg Vorbis files. It uses 
 * the libvorbisfile API (http:://www.xiph.org/ogg/vorbis) to decode an Ogg 
 * Vorbis bitstream and to extract information about the bitstream.
 * 
 **/


// Sets up an OggVorbis_File struct by calling the libvorbisfile method
// ov_open. Returns 1 if successful, 0 otherwise.
int OggDecoder::open(){
  int flag = 1;

  // libvorbis's ov_read() function requires a C-style file pointer, so
  // open one for the Ogg Vorbis file to decode.
  file_ptr = fopen(filename, "r");
  if(file_ptr!=NULL){
    cerr<<"opened file\n";
   
    // Call the libvorbis method that sets up the OggVorbis_File.
    if (ov_open(file_ptr, &ovf, NULL, 0)<0){
      cerr<<"ov_open failed\n";
      fclose(file_ptr);
      flag = 0;
    }
  }
  else{
    // Error if the Ogg Vorbis bitstream could not be opened.
    cerr<<"could not open file\n";
    flag = 0;
  }
  //cerr<<"exiting open\n";
  //cerr<<flag<<endl;

  // Get user comments about the bitstream.
  ovf_comm = ov_comment(&ovf, -1);

  // Get the bitstream header information.
  ovf_info = ov_info(&ovf, -1);
  return flag;
}

/* Public methods */

// Decodes the Ogg Vorbis file encapsulated by this object and writes the 
// resulting raw audio data to an output file. Returns 1 on success, 0 on
// failure.
//
// args: const char *outf- name of the output file where the raw audio data
//                        should be written
int OggDecoder::decode(const char *outf){

  // This will be the return value of calls to ov_read.
  long retval = 1;

  // Flag that is 1 if the end of the Ogg Vorbis bitstream has been reached,
  // 0 otherwise.
  int eof = 0;

  // The string that will contain the final raw audio data
  string pcm_stream = "";

  //ofstream out(outf);

  // Open a FILE pointer to the output file.
  FILE *my_out;
  if ((my_out = fopen(outf, "w"))==NULL){
    cerr<<"Could not open output file"<<endl;
    return 0;
  }

  
  int current_section;
  //cerr<<"in decode\n";

  // The PCM buffer.
  char pcm[4096];
  //cerr<<"here\n";

  // If the Ogg file can be decoded...
  //if (decodable){
  cerr<<"Decoding..."<<endl;

  // Decoding loop continues while retval is not 0, i.e. not EOF.
  while (!eof){
    //cerr<<retval<<endl;
    
    // ov_read decodes a block of the file and stores the result in pcm.
    // The size of the block is the size of pcm.
    retval = ov_read(&ovf, pcm, sizeof(pcm), 0, 2, 1, &current_section);
    //cout<<pcm; //dump pcm to stdout
    
    if (retval==0){
      cerr<<"eof reached"<<endl;
      eof = 1;
    }
    
    // Negative return value indicates an error in ov_read().
    else if (retval<0){
      cerr<<"Error decoding bitstream in section "<<current_section<<endl;
      // Save the pcm output to the output file.
      //pcm_stream += pcm;
    }
    else{
      //cerr<<"about to write audio data"<<endl;
      //fwrite(pcm, sizeof(char), retval, stdout);
      fwrite(pcm, sizeof(char), retval, my_out);
      //out<<pcm;
      //cerr<<"audio data written"<<endl;
    }
  }
  cerr<<"Decoding complete"<<endl;
 
  //}
  //  out.close();

  fclose(my_out);
  return 1;
}

// Returns an array of C-style strings containing user comments about the Ogg
// Vorbis bitstream. User comments typically include the artist, song, and 
// album names, as well as any other comments the creator of the file
// might have added.
char** OggDecoder::getUserComments(){
  return ovf_comm->user_comments;
}

// Returns the name and version of the encoder that created this Ogg Vorbis
// bitstream.
char* OggDecoder::getEncoderInfo(){
  return ovf_comm->vendor;
}

// Constructor

// Sets up the libvorbisfile data structures.
//
// args: const char *fname- name of the Ogg Vorbis file to be decoded
OggDecoder::OggDecoder(const char *fname){
  filename = fname;

  // If the bitstream cannot be opened, it's not decodable.
  if (!open()){
    cerr<<"Invalid Ogg Vobis bitstream.\n";
    decodable = false;
  }
  else{
    decodable = true;
  }
}


// Destructor

// Tears down the OggVorbis_File struct and closes any open file pointers.
OggDecoder::~OggDecoder(){
  //cerr<<"Inside destructor"<<endl;

  // Call the libvorbisfile method that tears down an OggVorbis_File.
  ov_clear(&ovf);
  cerr<<"ovf cleared"<<endl;
  //fclose(file_ptr);
  //cerr<<"file_ptr closed"<<endl;
}

