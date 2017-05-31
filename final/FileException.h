/* FileException.h- header file for FileException */


 

/* Revision History
 * 4/14/02- Generated header file.
 *          author: Shang-Lin Chen
 * 4/20/02- Added subclasses FileNotFoundException and BadFileFormatException.
 *          author: Shang-Lin Chen
 * 4/21/02- Changed private data members of FileException to protected so that
 *          subclasses would be able to access them.
 *          author: Shang-Lin Chen
 * 6/06/02- Decided not to use subclasses of FileException. 
 *          author: Shang-Lin Chen
 */



#ifndef _FILEEXCEPTION_H_
#define _FILEEXCEPTION_H_



class FileException;
// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "Exception.h"
#include<string>


// An enumerated type describing the type of FileException.
enum FileExceptionType{GeneralFileException, BadFileFormatException};



/**
 *  
 * Description:
 * 
 * FileException is a subclass of Exception that handles errors in level 
 * validation. 
 *
 **/
class FileException : public Exception{
                // Data Members

 private:

  // Indicates the type of FileException.
  FileExceptionType fet;

  // The coordinates in the Level where the FileException occurred.
  int x, y, z;

 public:

  // Returns the type of file exception 
  FileExceptionType getType( void );
  
 
// Writes to an output stream an error description and, if this a 
// BadFileFormatException with coordinates defined, the location where the 
// error occurred. Returns a reference to the output stream.
//
// args: ostream& os- reference to the output stream to which the error 
//                    description should be written
  ostream& print(ostream& os);
  
  // Constructor(s)


  // Creates a FileException with a description.  The description is
  // stored in a data member inherited from Exception.
  //
  // args: string desc- description of the error.
  FileException(string desc);

  // Creates a FileException with the description of the error and the 
  // coordinates where the error 
  // occurred. The description is stored in a data member inherited from 
  // Exception.
  //
  // args: string desc- description of the error
  //       int c- column in the level where the error occurred
  //       int r- row ""
  //       int f- floor""
  
  FileException(string desc, int c, int r, int f);
  
  // Destructor
  
  ~FileException ( void );
  
};




// We don't need these subclasses anymore.
#ifdef MORE_LEVEL_EXCEPTIONS
// A subclass of FileException that is thrown when a level file cannot be 
// found.
class FileNotFoundException : public FileException{
 public:
  FileNotFoundException(string desc);
};

// A subclass of FileException that is thrown when a level file is in 
// illegal format.
class BadFileFormatException : public FileException{
 private:
  // The row, column, and floor where the formatting error occurred.
  int row, col, floor;
 public:
  BadFileFormatException(int r, int c, int f, string desc);
  BadFileFormatException(string desc);
};
  
#endif
#endif

