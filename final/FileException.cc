/* FileException.cc- source file for FileException */

/* Revision History
 * 4/14/02- Generated this .cc file.
 *          author: Shang-Lin Chen
 * 4/20/02- Implemented subclasses FileNotFoundException and 
 *          BadFileFormatException, which are thrown when specific errors
 *          occur.
 *          author: Shang-Lin Chen
 * 4/21/02- Implemented constructors for the subclasses.
 *          author: Shang-Lin Chen
 * 6/06/02- Decided not to use inheritance after all. The subclasses were 
 *          really unnecessary. Added a print method.
 *          author: Shang-Lin Chen
 */


#include "FileException.h"



// Returns the type of file exception. 
FileExceptionType FileException::getType( void ) {
  return fet;
}

// Writes to an output stream an error description and, if this a 
// BadFileFormatException with coordinates defined, the location where the 
// error occurred. Returns a reference to the output stream.
//
// args: ostream& os- reference to the output stream to which the error 
//                    description should be written

ostream& FileException::print(ostream& os){
 
  if (fet==BadFileFormatException && x>-1 && y>-1 && z>-1){
    os<<"column "<<x<<", row "<<y<<", floor "<<z<<": "<<endl;
  }
  os<<FileException::getDescription()<<endl;
  return os;
}

// Constructor(s)

// Creates a FileException with a description of the error. The description is
// stored in a data member inherited from Exception.
//
// args: string desc- description of the error
FileException::FileException(string desc) : Exception(desc){
  fet = GeneralFileException;
  x = -1;
  y = -1;
  z = -1;
}

// Creates a FileException with the description of the error and the 
// coordinates where the error 
// occurred. The description is stored in a data member inherited from 
// Exception.
//
// args: string desc- description of the error
//       int c- column in the level where the error occurred
//       int r- row ""
//       int f- floor""
FileException::FileException(string desc, int c, int r, int f) : Exception(desc){
  fet = BadFileFormatException;
  x = c;
  y = r;
  z = f;
}

// Destructor

FileException::~FileException ( void ) {
  
}

/*
  FileNotFoundException::FileNotFoundException(string desc) 
  : FileException(desc){
  fet = FileNotFound;
  }
  
  BadFileFormatException::BadFileFormatException(int r, int c, int f, string desc) : FileException(desc){
  row = r;
  col = c;
  floor = f;
  fet = BadFileFormat;
  }
  
  BadFileFormatException::BadFileFormatException(string desc) : FileException(desc){
  fet = BadFileFormat;
  }
*/





