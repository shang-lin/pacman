/* Level.cc- source file for Level */



using namespace std;

/*
 * Revision History
 * 2/21/02- Generated from documentation and added to repository. 
 *          author: Shang-Lin Chen
 * 2/27/02- Implemented constructors. author: Shang-Lin Chen
 * 3/13/02- Implemented most of the algorithms to load the map and tested
 *          some algorithms in test_validate.cc. author: Shang-Lin Chen
 * 3/22/02- Added code for validating a Space in checkValid. Did more testing.
 *          author: Shang-Lin Chen
 * 3/24/02: Corrected numerous errors in the validation algorithms.
 *          author: Shang-Lin Chen
 * 4/03/02- Tested the algorithm that checks for double rows and double columns
 *          in checkValid. 
 *          author: Shang-Lin Chen
 * 4/23/02- Fixed #include's. author: Shang-Lin Chen
 * 4/29/02- Rewrote checkValid to be clearer and more efficient. Added code to
 *          check that there are at least two spaces between parallel rows/
 *          columns. 
 *          author: Shang-Lin Chen
 * 5/09/02: Fixed syntax and type errors throughout. author: Shang-Lin Chen
 * 5/19/02: Removed exception-throwing code that wasn't working. Changed
 *          data types of args of initializeFields and parseFile to const
 *          char *. author: Shang-Lin Chen 
 * 5/20/02: Implemented getWidth(), getLength(), and getHeight(). Changed the
 *          private member "height" to "length."
 *          author: Shang-Lin Chen
 * 5/23/02: Implemented getSpace(int, int, int). author: Shang-Lin Chen
 * 5/24/02: Modified setAllNeighbors so that it handles wrap-arounds.
 *          author: Shang-Lin Chen
 * 6/01/02: Finished up the random level generator. added using namespace
 *          std. changed getHeight to getFloors for compatibility reasons.
 *          author: clara graham
 * 6/01/02: Changed order of args in getSpace and findIndex for compatibility.
 *          author: Shang-Lin Chen
 * 6/03/02: Modified saveLevel so that it doesn't call BaseItem.
 *          author: Shang-Lin Chen
 * 6/04/02: Debugged validation algorithms. author: Shang-Lin Chen
 * 6/05/02: Fixed some of the seg-faulting at warps. when you hit
 *          a warp going north or east, you now continue off to 
 *          infinity instead of seg-faulting. i'll try to figure
 *          out how to get it to actually warp sometime tomorrow
 *          when it isn't 5:30AM 
 *            author: clara graham
 * 6/06/02: Fixed the warps so that warps at the top of a floor actually 
 *          connect to the warps at the bottom. Also modified exception 
 *          handling. Now the program exits cleanly when a level file fails.
 *          author: Shang-Lin Chen
 * 6/09/02: Fixed a bug that was causing segfaults in saveLevel(). Modified 
 *          saveLevel() so that it saves the character representing the items
 *          originally assigned to the map.
 *          author: Shang-Lin Chen
 * 6/13/02: Added a reachability test to make sure that all points are 
 *          reachable.
 *          author: Shang-Lin Chen
 */

// Includes
#include "opengl.h"
#include "Level.h"
#include "FileException.h"
#include "genlevel.h"
#include "playerlist.h"
#include "BFS.h"
#include<string>
#include <math.h>
#include<fstream>
#include<iostream>


//PlayerID of the current player...we need to know which level to draw here....
extern int myID;
extern PlayerList playerlist;


/**
 * Class description:
 *
 * The Level class stores information about the state of the current level, 
 * which includes the maze, its dimensions, and its contents. The level can
 * be loaded from a level file, or it can be generated randomly from 
 * user-provided information about the
 * number of columns, number of rows, number of floors, number of Pacmen, and
 * number of ghosts.
 *
 **/

// Randomly generates the map as a 3-D array of pointers to Space 
// objects. Precondition is that memory for the map has already been 
// allocated by the constructor.
void Level::generateRandom(){
  

	// We create a random level generator object
	RandomLevelGenerator rlg ( width, length, floors , numpacmen, numghosts);

	// this character array will hold the map.
	char tempmap [width * length * floors];
	
	// now, copy the character array into tempmap;
	for ( int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			for (int k = 0; k< floors; k++)
				tempmap[findIndex(i, j, k)] = rlg.getValue ( i, j, k);
			
	// and send the character array to loadMap()
	loadMap ( tempmap);
}

// Helper function that loads the map array from a character array if it 
// represents a valid level.
// The helper function checkValid is called to check each character.
// An exception is thrown if there is any error in the map.
// Preconditions: The size of the char array must be width*length*floors.
//
// args: const char *textmap- char array containing the ASCII representation
//                            of a level
//
void Level::loadMap( const char* textmap) {

  int x=0, y=0, z=0; //row, column, floor

  // Number of main pacman starting points
  int main_pacstart = 0;

  // The current character read from textmap
  char this_char;

  // The current index in the map
  int index;
  
  // Error message
  string error_msg;

  // Go through the textmap element-by-element while
  // the dimensions are within bounds.
  while (z<floors && x<width && y<length){
    index = findIndex(x,y,z);
    
    // The character at these coordinates
    this_char = textmap[index];
    
    // If this character is legal...
    if (legal_chars.find(this_char)!=string::npos){
      // Check that this character is valid for the map by calling checkValid.
      if (!(checkValid(textmap,x,y,z))){
	// Throw an exception.

	error_msg = "Level file validation failed.";
	throw FileException(error_msg, x, y, z);
      }
    
      // If the character is valid...
      else{ 
	
	//added by Dax
	if(this_char == ' ' || this_char=='\0' || !this_char)
	  map[index]=NULL;
	
	else
	  {
	    // ...initialize the Space* in the map.
	    map[index] = new Space(this_char, x, y, z);
	    
	    
	    
	    switch (this_char){
	    case 'P':
	      // A 'P' indicates a main pacman starting point.
	      main_pacstart++;
	      numpacmen++;
	      pacmanStart.push_back(map[index]);
	      break;
	    case 'p':  
	      // A 'p' indicates a regular pacman starting point.
	      // Add the starting point to the pacmanStart vector.
	      pacmanStart.push_back(map[index]);
	      numpacmen++;
	      break;
	    case 'g': 
	      //'g' indicates a ghost spawning point.
	      // Add the spawning point to the ghostStart vector.
	      ghostStart.push_back(map[index]);
	      numghosts++;
	      break;
	    default:
	      break;
	    }
	  }
      }
      
    }
  
    // Adjust values of x, y, and z.
    // If in the middle of a row, increment the column.
    if (x<width-1)
      x++;
    // If at the end of a row, increment the row and reset column to 0.
    else if (x==width-1 && y<length-1){
      y++;
      x=0;
    }
    // If the end of a row is also the end of a floor, increment the floor
    // and reset the row and column to 0.
    else if (x==width-1 && y==length-1){
      z++;
      x=0;
      y=0;
    }
    else{
      error_msg = "Invalid dimensions.";
      throw FileException(error_msg, x,y,z);
    }
  }

  x=0; y=0; z=0; //row, column, floor
  while (z<floors && x<width && y<length){
    index = findIndex(x,y,z);
    
    // If this one isn't NULL
    if (map[index]){
      setAllNeighbors(textmap, x, y, z);
    }
    // Adjust values of x, y, and z.
    // If in the middle of a row, increment the column.
    if (x<width-1)
      x++;
    // If at the end of a row, increment the row and reset column to 0.
    else if (x==width-1 && y<length-1){
      y++;
      x=0;
    }
    // If the end of a row is also the end of a floor, increment the floor
    // and reset the row and column to 0.
    else if (x==width-1 && y==length-1){
      z++;
      x=0;
      y=0;
    }
    else{
      error_msg = "Invalid dimensions.";
      throw FileException(error_msg, x,y,z);
    }
  }

  // Make sure that there is only one main pacman starting point.
  if (main_pacstart != 1){
    error_msg = "Only one main Pacman starting point allowed.";
    throw FileException(error_msg);		          
  }


  //printNeighbors();
  if (!checkReachable()) {
    throw FileException("Not all points are reachable.");
  }
  cerr<<"Level loaded successfully"<<endl;
  //cerr<<"exiting loadMap"<<endl;
}

// Helper for loadMap that checks that the character in a character array 
// at a specific row, column, and floor can represent a valid Space* in the 
// actual map. The character array is an ASCII representation of the actual 
// map defined in the level file. 
// Returns true if the character is valid, false otherwise.  
//
// Preconditions: The size of textmap must be width*length*floors. 
// r, c, and f must be between 0 and length, 0 and width, and 0 and floors,
// respectively.
//
// args: const char *textmap- char array representing the level
//       const int c- column of the character currently being checked
//       const int r- row of the character currently being checked
//       const int f- floor ""
bool Level::checkValid(const char* textmap, const int c, const int r, const int f){
  int index = findIndex(c,r,f);
  char this_char = textmap[index];
  char lower_right, right, upper_right, above, below, lower_left, left, upper_left;
  
  // Store the characters neigboring this_char. This occupies more lines of
  // code but makes the later code easier to read and reduces calls to 
  // findIndex.

  // If the row below this one is still smaller than the length of a floor,
  // then store the character below this_char.
  if (r+1<length){
    below = textmap[findIndex(c,r+1,f)];
  }
  // Otherwise, set below to null.
  else
    below = '\0';

  // If the character above this one exists, store it in above. Otherwise,
  // set above to null.
  if (r-1>=0){
    above = textmap[findIndex(c,r-1,f)];
  }
  else
    above = '\0';

  // If the lower right character exists, store it in lower_right. Otherwise,
  // set lower_right to null.
  if (r+1<length && c+1<width){
    lower_right = textmap[findIndex(c+1,r+1,f)];
  }
  else
    lower_right = '\0';

  // If the char to the right exists, store it in right. Otherwise, set right
  // to null.
  if (c+1<width){
    right = textmap[findIndex(c+1,r,f)];
  }
  else
    right = '\0';

  // If the char to the upper right exists, store it in upper_right. Otherwise,
  // set upper_right to null.
  if (r-1>=0 && c+1<width){
    upper_right = textmap[findIndex(c+1,r-1,f)];
  }
  else
    upper_right = '\0';

  // Do the same as above with the characters to the left, lower left, and 
  // upper left.

  if (c-1>=0){
    left = textmap[findIndex(c-1,r,f)];
  }
  else
    left = '\0';

  if (c-1>=0 && r+1<length){
    lower_left = textmap[findIndex(c-1,r+1,f)];
  }
  else 
    lower_left = '\0';

  if (c-1>=0 && r-1>=width){
    upper_left = textmap[findIndex(c-1,r-1,f)];
  }
  else
    upper_left = '\0';
  
  bool is_valid = true;
  //cerr<<"in checkValid\n";
  
  // If the character we want to check exists and is not a blank...
  if (this_char!='\0' && this_char != ' '){
 
    // If the character one row below it is blank but the character two rows
    // below it is not blank, then there is only one space between rows.
    // This is illegal.
    if (r+1<length && r+2<length && (below=='\0' || below==' ')
	&& (textmap[findIndex(c,r+2,f)]!='\0' && textmap[findIndex(c,r+2,f)]!=' ')){
      is_valid = false;
      cerr<<"double space check between rows failed"<<endl;
      cerr<<r<<" "<<c<<" "<<f<<endl;
      cerr<<"below="<<below<<" textmap[findIndex(r+2,c,f)]="<<textmap[findIndex(r+2,c,f)]<<endl;
    }

    // If the char to the right is blank but the char two spaces to the right 
    // is not blank, then there is only one space between columns.
    // This is also illegal.
    if (is_valid && c+1<width && c+2<width && (right=='\0' || right ==' ')
	&& textmap[findIndex(c+2,r,f)]!='\0' && textmap[findIndex(c+2,r,f)]!=' '){
    is_valid = false;
    cerr<<"double space check between columns failed"<<endl;
    cerr<<r<<" "<<c<<" "<<f<<endl;
    cerr<<"right="<<right<<" textmap[findIndex(r,c+2,f)]="<<textmap[findIndex(c+2,r,f)]<<endl;
      
      }

    // The following block checks for adjacent rows or columns, such as the 
    // following two lines in
    // a level file:
    //        ..
    //        ..
    // These types of rows or columns are illegal.

    // Check the character in the next row...
    if (is_valid && r+1<length && below!='\0' && below!=' '){
      // ...if it is not blank, check the characters to the right and the lower
      // right...
      if (c+1<width && right!='\0' && right!=' ' && lower_right!='\0' && lower_right!=' '){
	// ...if they are not blank, there are adjacent rows/columns. This
	// is illegal.
	cerr<<this_char<<endl;
	cerr<<"right and lower right test failed\n";
	cerr<<this_char<<right<<lower_right<<endl;
	cerr<<lower_right<<endl;
	is_valid = false;
      }
    }

  }

  return is_valid;
}


// Parses a user-provided level file to build the level. 
// The characters in the level file are stored in a character array
// which is then passed to the loadMap method. loadMap checks that
// the characters can represent a valid map and loads the map from the char 
// array  if all the tests are passed.
//
// args: const char *filename- the name of the level file.
void Level::parseFile(const char* filename){
  assert((width>=0) && (length>=0) && (floors>=0) && (numpacmen>=0) && (numghosts>=0));

  // a_space is the current character, prev_char is the previous character 
  // read.
  char a_space, prev_char;

  // Coordinates
  int x=0, y=0, z=0;

  char *textmap = new char[width*length*floors];
  ifstream levelfile(filename);
  //cerr<<"starting parseFile"<<endl;
  if (!levelfile){
    throw FileException("Level file not found");
  }
  else{
    // If the level file exists, go through it character-by-character
    while (levelfile.get(a_space)){
      
      if (legal_chars.find(a_space)==string::npos){
	// Throw an exception if there is an illegal character.
	throw FileException(string("Illegal character"));
      }
      else{			  
	//assert(x<width && y<length && z<floors);
	switch(a_space){
	case '\n':
	  // A newline indicates the end of a row.
	  if (x<=width-1)
	    y++;
	  x=0;
	  if ( prev_char=='\n'){
	    // Two consecutive newlines indicate the end of a floor.
	    z++;
	    y=0; 
	  }
	  break;


	default:
	  // If the character is not a newline, then load it into the 
	  // character array.
	  if (x<width && y<length && z<floors){
	    textmap[findIndex(x,y,z)] = a_space;
	  }

	  // Increment the column
	  if (x<width-1){
	    x++;
	  }
	  break;
	}
	// Save the current char so that the next time around, it'll be the
	// previously read character.
	prev_char = a_space;
      }
      
    }
    //cerr<<"loop done"<<endl;
    loadMap(textmap);
  }
  //cerr<<"Level loaded."<<endl;
  levelfile.close();
  //cerr<<"done with parseFile"<<endl;
}


// Initializes the dimensions of the map when the input to the constructor
// is a level file. 
//
// args: const char *filename- the name of the level file.
void Level::initializeFields(const char *filename){
  char *line;
  line = new char[MAXWIDTH];  
  int floor_length = 0; //length of the current floor
  floors = 1;
  ifstream levelfile(filename);
  //cerr<<"initializing fields"<<endl;
  if (!levelfile){
    throw FileException("Level file not found\n");
  }


  else{
    // Go through level file line-by-line and get the dimensions of the map
    // by determining the size of the user-drawn map.
    while (levelfile.getline(line, MAXWIDTH)){
      string tmp(line);

      // update the max width if a line is longer      
      if (tmp.length() > (unsigned)width){
	width = tmp.length();
      }
      // A blank line indicates a new floor
      if (tmp==""){ 
	floors++;
	if (floor_length > length){
	  length = floor_length;
	}
	floor_length = 0;
      }
      else{
	floor_length++;
      }
    
      // update max number of floors if necessary
      if (floor_length > length){
	length = floor_length;
      }
    }

    // Throw an exception if the dimensions are too large.
    if ((length > MAXLENGTH) || (width > MAXWIDTH) || (floors > MAXFLOORS)){
      throw FileException(string("Invalid dimensions"));
    }
    			
    map = new Space*[width*length*floors];
  }
  
  levelfile.close();
  //cerr<<"done initializing fields"<<endl;
}

// Given x, y, and z coordinates, returns the appropriate index in the map.
//
// args: int x- column
//       int y- row
//       int z- floor
int Level::findIndex(int x, int y, int z){
  return y*width + x + z*width*length;
}

// Sets all neighbors of the Space in the map located at row r, column c,
// floor f. 
// 
// args: const char *textmap- char representation of the map.
//                            size is assumed to be length*with*floors.
//       const int c- column of the char to check
//       const int r- row of the char to check
//       const int f- floor of the char to check
void Level::setAllNeighbors(const char *textmap, const int c, const int r, const int f){

  assert(r>=0 && r<length && c>=0 && c<width && f>=0 && f<floors);
  int index = findIndex(c,r,f);
  int neighbor; // the index of the current neighbor
  assert(index < width*length*floors);
  
  // Set the neighbor to the east.
  if (c<width-1){
    // Determine the index of the east neighbor.
    neighbor = findIndex(c+1, r, f);

    // Check if the east neighbor exists.
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      // If there is a neighbor to the east, but its pointer has not been 
      // defined in the actual map yet, define it.
      if (!map[neighbor] ){
	map[neighbor] = new Space(textmap[neighbor],c+1,r,f);
      }
      if (map[index] && map[index]->getNeighbor('e') != map[neighbor]){
	// If this space's pointer to the neighbor has not yet been set, set
	// it.
	map[index]->setNeighbor('e', map[neighbor]);
      }
    }

		// clara added:
		// this elseif statement checks for warps and sets up the 
		// pointers correctly. unfortunately, there seems to be
		// something else telling pacman where he is, so it doesn't
		// actually draw it warping. it doesn't seg-fault if you go
		// east now though. i'd try to figure out how to get it to
		// draw, but it's very late
	} else if (c == width - 1){
		if (textmap[index] != ' ' && textmap[findIndex(0,r,f)] != ' '){
			map[index]->setNeighbor('e', map[findIndex(0,r,f)]);
			map[findIndex(0,r,f)]->setNeighbor('w', map[index]);
		}
		
	}
	
  // Set the west neighbor.
  if (c>0){
    neighbor = findIndex(c-1, r, f);
    if (textmap[neighbor] && textmap[neighbor] != ' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor], c-1,r,f);
      }
      if (map[index] && map[index]->getNeighbor('w')!=map[neighbor]){
	map[index]->setNeighbor('w', map[neighbor]);
      }
    }
  }
  // Set the north neighbor.
  if (r>0){
    neighbor = findIndex(c, r-1, f);
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],c,r-1,f);
      }
      if (map[index] && map[index]->getNeighbor('n')!=map[neighbor]){
	map[index]->setNeighbor('n', map[neighbor]);
      }
    }
  }
  /*  else if (r==0){
    neighbor = findIndex(c,length-1,f);
    cout<<"vertical wraparound neighbor's row is "<<length-1<<endl;
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],c,length-1,f);
      }
      if (map[index] && map[index]->getNeighbor('n')!=map[neighbor]){
	map[index]->setNeighbor('n', map[neighbor]);
	map[neighbor]->setNeighbor('s', map[neighbor]);
      }
    }
    }*/

  // Set the south neighbor.
  if (r<length-1){
    neighbor = findIndex(c, r+1, f);
    if (textmap[neighbor] && textmap[neighbor]!= ' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],c,r+1,f);
      }
      if (map[index] && map[index]->getNeighbor('s')!=map[neighbor]){
	map[index]->setNeighbor('s', map[neighbor]);
      }
    }
  }

  // Set the up neighbor.
  if (textmap[index] == 'u'){
    neighbor = findIndex(c, r, f+1);
    //assert(neighbor>=0 && neighbor<width*length*floors);
    if (!map[neighbor]){
      map[neighbor] = new Space(textmap[neighbor],c,r,f+1);
    }
    if (map[index] && map[index]->getNeighbor('u')!=map[neighbor]){
      map[index]->setNeighbor('u', map[neighbor]);
    }
  }
  // Set the down neighbor.
  if (textmap[index]=='d'){
    assert(f<=floors-1);
    neighbor = findIndex(c,r,f-1);
    assert(neighbor>=0 && neighbor<width*length*floors);
    if (!map[neighbor]){
      map[neighbor] = new Space(textmap[neighbor],c,r,f-1);
    }
    if (map[index] && map[index]->getNeighbor('d')!=map[neighbor]){
      map[index]->setNeighbor('d', map[neighbor]);  
    }
  }

  // Special cases for setting neighbors if the coordinates are at a horizontal
  // wrap-around.

  // Set the left horizontal wrap-arounds.
  // If the space is on the left edge of the board...
  if (c==0){

    // Its neighbor is on the right edge.
    neighbor = findIndex(width-1,r,f);
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],width-1,r,f);
      }
      map[index]->setNeighbor('w', map[neighbor]);
      //map[neighbor]->setNeighbor('e', map[index]);
    }
    else{
      throw FileException("Mismatched wrap-around.", c, r, f);
    }
  }
  
  // Set right horizontal wrap-arounds.
  // If the space is on the right edge of the board...
  if (c==width-1){
    neighbor = findIndex(0,r,f);
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],0,r,f);
      }
      map[index]->setNeighbor('e', map[neighbor]);
      //map[neighbor]->setNeighbor('w', map[index]);
    }
    else{
      throw FileException("Mismatched wrap-around.", c, r, f);
    }
  }

  // Set north vertical wrap-arounds if the space is in row 0.
  if (r==0){
    neighbor = findIndex(c,length-1,f);
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],c,length-1,f);
      }
      map[index]->setNeighbor('n', map[neighbor]);
      //      map[neighbor]->setNeighbor('s', map[index]);
    }
    else{
      throw FileException("Mismatched wrap-around.", c, r, f);
    }
  }

  // Set south vertical wrap-arounds if the space is in the last row of
  // a floor.
  if (r==length-1){
    neighbor = findIndex(c,0,f);
    if (textmap[neighbor] && textmap[neighbor]!=' '){
      if (!map[neighbor]){
	map[neighbor] = new Space(textmap[neighbor],c,0,f);
      }
      map[index]->setNeighbor('s', map[neighbor]);
      //map[neighbor]->setNeighbor('n', map[index]);
    }
    else{
      throw FileException("Mismatched wrap-around.", c, r, f);
    }
  }
}

// Returns true if every valid Space in the map is reachable from each Pacman
// starting point. Returns false if the test fails. A BFS object is
// declared to model the Level as a graph. Then a breadth-first search is
// performed on the graph to perform the test.
bool Level::checkReachable(){
  //cerr<<"checking reachability"<<endl;
 
  BFS checker(map, width, length, floors);
  //cerr<<"Checker initialized"<<endl;
  //cerr<<"BFS initialized"<<endl;
  if (!checker.check_connect(pacmanStart[0]->getX(), pacmanStart[0]->getY(), pacmanStart[0]->getZ())){
  return false;
  }
  //cerr<<"checkReachable done"<<endl;
  return true;

}

/*
 * Public Methods
 */

// Calculates the shortest path from (x1,y1,z1) to (x2,y2,z2) 
// in the level (using BFS). This method is used by the AI. 
//
// TO-DO: This function stil has to be implemented. The AI no longer uses it.
int Level::distance( int x1, int y1, int z1, int x2, int y2, int z2 ) {
  return 0; //for now
}


// Saves this level to an output text file. Each Space* in the map is written
// to the output file as an ASCII character determined by the type of item
// it contains.
//
// args: string filename- name of the output file
void Level::saveLevel( string filename ) {
  string name = filename;
  int index;
  //  class BaseItem* item_ptr;
  //string item_desc;
  int x, y, z;

  // Coordinates of the Space* being written.
  int currX=0;
  int currY = 0;
  int currZ=0;

  int len = name.length();
  // If the provided filename does not end with ".txt," add that extension.
  if (name.rfind(".txt") != (unsigned)len - 4){
    name += ".txt";
  }

  // File streams requre a C-style string.
  const char* fname = name.c_str();
  
  // Open an output stream for the output file.
  ofstream out(fname);
  if (!out){
    throw FileException(string("Could not create output file\n"));
  }
  
  // Go through map floor by floor, row by row, column by column.
  for (z=0; z<floors; z++){
    for (y=0; y<length; y++){
      for (x=0; x<width; x++){

	// Compute the index for the current coordinates.
	index = findIndex(x,y,z);

	// If there is a Space* at this index, write the character representing
	// its originally assigned item to the output file.
	if (map[index]){
	  out<<map[index]->getOrigItemKey();
	}
	else{
	  // If there is no Space* here, write a blank to the output file.
	  out<<' ';
	}
	 
	// Write a newline at the end of a row.
	if (x==width-1){
	  out<<endl;
	  if (y==length-1 && z!=floors-1){
	    out<<endl;
	  }
	    
	}
	
      }
      
    }
    
  }//end outermost for
  out.close(); // close the output stream
}

// Draws the level.
void Level::draw( void ){
 
  //before the level draws itself, it has to move to the space that pacman is in
  //this player's pacman should always be in the center of the screen.
  //this has been taken care of in opengl.cpp
  
  //find the current player's level first
  int zlevel = (int)playerlist.getPlayer(myID)->getZ();

  //	zlevel = 1;
  //	cout<<zlevel<<endl;

      
  //set the cool blue for the walls
  glColor3f(0, 0, 1);
  
  
  
  //with GL_LINES, lines are given in sets of pairs
  glBegin(GL_LINES);
  
  
  //DO THE TOP LINES
  for(int j=0; j<length; j++)
    {
      for(int i=0; i<width; i++)
	{
	  
	  //if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
	  
	  if(getSpace(i,j,zlevel) != NULL && ( j == 0 || j == length - 1 || i == 0 || i == width - 1 ) )
	    {
	      //				cout<<"this is a special space: "<<i<<", "<<j<<endl;
	      //needs special processing, it's a wrap around tunnel
	    }
	  //else if(level[j][i] && !level[j-1][i]) //if there isn't one above it
	  else if(getSpace(i,j,zlevel)!=NULL && getSpace(i,j-1,zlevel)==NULL) //if there isn't one above it
	    {
	      //				cout<<"there isn't one above it: "<<i<<", "<<j<<endl;
	      //if(!level[j][i-1]) //there's no neighbor to the left
	      if(getSpace(i-1,j,zlevel)==NULL) //there's no neighbor to the left
		{
		  //draw 1 and 2
		  glVertex2f(i*6-6, -j*6+6);
		  glVertex2f(i*6, -j*6+6);
		}
	      //else if(!level[j-1][i-1]) //the left neighbor has no neighbor above it
	      else if(getSpace(i-1,j-1,zlevel)==NULL) //the left neighbor has no neighbor above it
		{
		  //draw 2
		  glVertex2f(i*6-3, -j*6+6);
		  glVertex2f(i*6, -j*6+6);
		}
	      
	      //if(!level[j][i+1]) //there's no neighbor to the right
	      if(getSpace(i+1,j,zlevel)==NULL) //there's no neighbor to the right
		{
		  //draw 3 and 4
		  glVertex2f(i*6, -j*6+6);
		  glVertex2f(i*6+6, -j*6+6);
		}
	      //else if(!level[j-1][i+1]) //the right neighbor has no neighbor above it
	      else if(getSpace(i+1,j-1,zlevel)==NULL) //the right neighbor has no neighbor above it
		{
		  //draw 3
		  glVertex2f(i*6, -j*6+6);
		  glVertex2f(i*6+3, -j*6+6);
		}
	    }
	}
    }


  //do the right side
  for(int j=0; j<length; j++)
    {
      for(int i=0; i<width; i++)
	{
	  //if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
	  if(getSpace(i,j,zlevel)!=NULL && ( j == 0 || j == length - 1 || i == 0 || i == width - 1 ) )
	    {
	      //needs special processing, it's a wrap around tunnel
	    }
	  //else if(level[j][i] && !level[j][i+1]) //if there isn't a space to the right of it
	  else if(getSpace(i,j,zlevel)!=NULL && getSpace(i+1,j,zlevel)==NULL) //if there isn't a space to the right of it
	    {
	      //if(!level[j-1][i]) //there's no neighbor above it, draw a wall on the right
	      if(getSpace(i,j-1,zlevel)==NULL) //there's no neighbor above it, draw a wall on the right
		{
		  //draw 1 and 2
		  glVertex2f(i*6+6, -j*6+6);
		  glVertex2f(i*6+6, -j*6);
		}
	      //else if(!level[j-1][i+1]) //the above neighbor has no neighbor to it's right
	      else if(getSpace(i+1,j-1,zlevel)==NULL) //the above neighbor has no neighbor to it's right
		{
		  //draw 2
		  glVertex2f(i*6+6, -j*6+3);
		  glVertex2f(i*6+6, -j*6);
		}
	      
	      //if(!level[j+1][i]) //there's no neighbor below it
	      if(getSpace(i,j+1,zlevel)==NULL) //there's no neighbor below it
		{
		  //draw 3 and 4
		  glVertex2f(i*6+6, -j*6);
		  glVertex2f(i*6+6, -j*6-6);
		}
	      //else if(!level[j+1][i+1]) //the below neighbor has no neighbor to it's right
	      else if(getSpace(i+1,j+1,zlevel)==NULL) //the below neighbor has no neighbor to it's right
		{
		  //draw 3
		  glVertex2f(i*6+6, -j*6);
		  glVertex2f(i*6+6, -j*6-3);
		}
	    }
	}
    }

  //do the left side
  for(int j=0; j<length; j++)
    {
      for(int i=0; i<width; i++)
	{
	  //if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
	  if(getSpace(i,j,zlevel)!=NULL && ( j == 0 || j == length - 1 || i == 0 || i == width - 1 ) )
	    {
	      //needs special processing, it's a wrap around tunnel
	    }
	  //else if(level[j][i] && !level[j][i-1]) //if there isn't a space to the left of it
	  else if(getSpace(i,j,zlevel)!=NULL && getSpace(i-1,j,zlevel)==NULL) //if there isn't a space to the left of it
	    {
	      //if(!level[j-1][i]) //there's no neighbor above it, draw a wall on the left
	      if(getSpace(i,j-1,zlevel)==NULL) //there's no neighbor above it, draw a wall on the left
		{
		  //draw 1 and 2
		  glVertex2f(i*6-6, -j*6+6);
		  glVertex2f(i*6-6, -j*6);
		}
	      //else if(!level[j-1][i-1]) //the above neighbor has no neighbor to it's left
	      else if(getSpace(i-1,j-1,zlevel)==NULL) //the above neighbor has no neighbor to it's left
		{
		  //draw 2
		  glVertex2f(i*6-6, -j*6+3);
		  glVertex2f(i*6-6, -j*6);
		}
	      
	      //if(!level[j+1][i]) //there's no neighbor below it
	      if(getSpace(i,j+1,zlevel)==NULL) //there's no neighbor below it
		{
		  //draw 3 and 4
		  glVertex2f(i*6-6, -j*6);
		  glVertex2f(i*6-6, -j*6-6);
		}
	      //else if(!level[j+1][i-1]) //the below neighbor has no neighbor to it's left
	      else if(getSpace(i-1,j+1,zlevel)==NULL) //the below neighbor has no neighbor to it's left
		{
		  //draw 3
		  glVertex2f(i*6-6, -j*6);
		  glVertex2f(i*6-6, -j*6-3);
		}
	    }
	}
    }


  //do the bottom side
  for(int j=0; j<length; j++)
    {
      for(int i=0; i<width; i++)
	{
	  //if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
	  if(getSpace(i,j,zlevel)!=NULL && ( j == 0 || j == length - 1 || i == 0 || i == width - 1 ) )
	    {
	      //needs special processing, it's a wrap around tunnel
	    }
	  //else if(level[j][i] && !level[j+1][i]) //if there isn't one below it
	  else if(getSpace(i,j,zlevel)!=NULL && getSpace(i,j+1,zlevel)==NULL) //if there isn't one below it
	    {
	      //if(!level[j][i-1]) //there's no neighbor to the left
	      if(getSpace(i-1,j,zlevel)==NULL) //there's no neighbor to the left
		{
		  //draw 1 and 2
		  glVertex2f(i*6-6, -j*6-6);
		  glVertex2f(i*6, -j*6-6);
		}
	      //else if(!level[j+1][i-1]) //the left neighbor has no neighbor below it
	      else if(getSpace(i-1,j+1,zlevel)==NULL) //the left neighbor has no neighbor below it
		{
		  //draw 2
		  glVertex2f(i*6-3, -j*6-6);
		  glVertex2f(i*6, -j*6-6);
		}
	      
	      //if(!level[j][i+1]) //there's no neighbor to the right
	      if(getSpace(i+1,j,zlevel)==NULL) //there's no neighbor to the right
		{
		  //draw 3 and 4
		  glVertex2f(i*6, -j*6-6);
		  glVertex2f(i*6+6, -j*6-6);
		}
	      //else if(!level[j+1][i+1]) //the right neighbor has no neighbor below it
	      else if(getSpace(i+1,j+1,zlevel)==NULL) //the right neighbor has no neighbor below it
		{
		  //draw 3
		  glVertex2f(i*6, -j*6-6);
		  glVertex2f(i*6+3, -j*6-6);
		}
	    }
	}
    }
  
  
  glEnd();
  
  //draw the spaces, it doesn't matter in what order, but you 
  //can't draw the spaces WITHIN the level drawing code below
  glColor3f(1, 1, 1);
  for(int j=0; j<length; j++)
    {
      for(int i=0; i<width; i++)
	{
	  if(getSpace(i, j, zlevel))
	    {
	      getSpace(i, j, zlevel)->draw();
	    }
	}
    }
  
  glutPostRedisplay();
}



// Prints the coordinates of the neighbors of each Space* in the map of the 
// level. This method is for debugging use only.
void Level::printNeighbors(){

  // temporary Space* to hold the neighbor of the Space* being checked.
  Space *neighbor;

  for (int i=0; i<length*width*floors; i++){
    if (map[i]){
      cout<<"checking "<<map[i]->getX()<<", "<<map[i]->getY()<<", "<<map[i]->getZ()<<": "<<map[i]->getItemKey()<<endl;
      if ((neighbor=map[i]->getNeighbor('n'))!=NULL){
	cout<<"Getting north neighbor"<<endl;
	cout<<"north: "<<neighbor->getX()<<", "<<neighbor->getY()<<", "<<neighbor->getZ()<<endl;
      }
      if ((neighbor=map[i]->getNeighbor('s')) != NULL){
	cout<<"south: "<<neighbor->getX()<<", "<<neighbor->getY()<<", "<<neighbor->getZ()<<endl;
      }
      if ((neighbor=map[i]->getNeighbor('w'))){
	cout<<"west: "<<neighbor->getX()<<", "<<neighbor->getY()<<", "<<neighbor->getZ()<<endl;
      }
      if ((neighbor=map[i]->getNeighbor('e'))){
	cout<<"east: "<<neighbor->getX()<<", "<<neighbor->getY()<<", "<<neighbor->getZ()<<endl;
      }
      if ((neighbor=map[i]->getNeighbor('u'))){
	cout<<"up: "<<neighbor->getX()<<", "<<neighbor->getY()<<", "<<neighbor->getZ()<<endl;
      }
      if ((neighbor=map[i]->getNeighbor('d'))){
	cout<<"down: "<<neighbor->getX()<<", "<<neighbor->getY()<<", "<<neighbor->getZ()<<endl;
      }
    }
  }
}

// returns a random pacman starting position
Space * Level::getPacmanStart ( void ){
	// the start positions are stored in:
	// vector <Space *> pacmanStart

	int numstarts = pacmanStart.size();
	int randomly_picked_start = rand() % numstarts;
	return pacmanStart[randomly_picked_start];
}

// returns a random ghost starting position
Space * Level::getGhostStart ( void ){
	// the start positions are stored in:
	// vector <Space *> ghostStart

	int numstarts = ghostStart.size();
	int randomly_picked_start = rand() % numstarts;
	return ghostStart[randomly_picked_start];
}

// Constructor(s)

// Generates the level from the contents of an input text file that contains an
// ASCII representation of the actual map using only  
// legal characters as defined in the header file. The level is only generated
// if the file passes all validation tests.
//
// args: string filename- name of the level file. must end with .txt extension.
Level::Level ( string filename ) {
  int len = filename.length();
  width = 0;
  length = 0;
  floors = 0;
  numpacmen = 0;
  numghosts = 0;

  
  //Error if the file does not end with the .txt extension.
  if (filename.rfind(".txt") != ((unsigned)len - 4)){
    throw FileException(string("Invalid level file name: must have .txt extension"));
  }
  else{ // If the extension is correct...
    // Initialize the dimensions of the map from the level file.
    const char *fname = filename.c_str();
    initializeFields(fname); // Initialize the length, width, and no. of floors
    parseFile(fname); // Construct the map.
  }


}


// Creates a level from the specified information and the array of chars.
// 
// args: int xrange- number of columns in the level
//       int yrange- number of rows ""
//       int numfloors- number of floors ""
//       int maxpacmen- maximum number of pacmen
//       int numghosts- number of ghosts
//       char *textmap- chars representing the level

Level::Level ( int xrange, int yrange, int numfloors, int maxpacmen, int numGhosts, char* tempmap) {
  //Initialize data members.
  width = xrange;
  length = yrange;
  floors = numfloors;
  numpacmen = maxpacmen;
  numghosts = numGhosts;

  // Allocate memory for the map.
  map = new Space*[width*length*floors];

  // Load the map. 
  loadMap(tempmap);
 
 
}

// Randomly generates a level with the user-provided parameters. The randomly
// generated level must pass all validation tests.
//
// args: int xrange- number of columns in the randomly generated level
//       int yrange- number of rows ""
//       int numfloors- number of floors ""
//       int maxpacmen- maximum number of Pacmen allowed and also number
//                      of Pacman starting points
//       int numGhosts- maximum number of ghosts allowed
Level::Level ( int xrange, int yrange, int numfloors, int maxpacmen, int numGhosts ) {
  //Initialize data members.
  width = xrange;
  length = yrange;
  floors = numfloors;
  numpacmen = maxpacmen;
  numghosts = numGhosts;

  // Allocate memory for the map.
  map = new Space*[width*length*floors];


  generateRandom();


}

// Returns the maximum number of columns in the level.
int Level::getWidth(){
  return width;
}

// Returns the maximum number of rows in a floor of the level.
int Level::getLength(){
  return length;
}

// Returns the number of floors in the level.
int Level::getFloors(){
  return floors;
}

// Returns the pointer to a Space at a specified row, column, and floor in
// the map of the level.
//
// args: int c- column
//       int r- row
//       int f- floor
Space* Level::getSpace(int c, int r, int f){
  return map[findIndex(c,r,f)];
}

// Destructor

// Deallocates memory.
Level::~Level ( void ) {
	cerr << "destructor\n";
	pacmanStart.clear();
	ghostStart.clear();
	cerr << "pacmanStart.size() = " << pacmanStart.size() << "\n";
	for(int i=0;i<width*length*floors;i++){
		if(map[i]!=NULL){
			delete map[i];
			map[i] = NULL;
		}
	}
  delete[] map;
}
