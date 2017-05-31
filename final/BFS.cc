/* BFS.cc
   source file for BFS class */

/* Revision History
 * 6/13/02: Added BFS.cc to CVS. author: Shang-Lin Chen
 * 6/14/02: Finished extensive debugging.
 *          author: Shang-Lin Chen
 */
#include <iostream>
#include "BFS.h"
using namespace std;

/**
 * Description: 
 *
 * The BFS class implements a breadth-first search for checking reachability
 * and connectedness in a Level. A graph is created from the map of a Level.
 * The breadth-first search is performed on this graph.
 *
 **/

// Initializes the mainArray from the map of an instance of Level. The color
// of each aVertex* in mainArray is set to 0 (white).
//
// args: Space** myMap- array of pointers to Space that represents the map
//                      of a level
void BFS::initialize ( Space** myMap){
  int i, j, tmp;
  char n[6] = {'n', 'e', 's', 'w', 'u', 'd'};
  char tmpCh;
  int x, y, z;
  
  //cerr<<"Initializing..."<<endl;

   


  for (i = 0; i < the_size; i++){

    // Initialize the pointer.
    mainArray[i] = new aVertex;
    //cerr<<"vertex initialized"<<endl;
    if (myMap[i] == NULL){
      //cerr<<"empty space detected"<<endl;
       mainArray[i]->isEmpty = true;
       mainArray[i]->posIndx = -99;
       continue;
    }
    else{ 
      mainArray[i]->isEmpty = false;
      mainArray[i]->color= 0;
      mainArray[i]->posIndx = i;
    } // end of else
  }  // end for
      
  //cerr<<"setting neighbors"<<endl;
  // set neighbors
  for (i=0; i < the_size; i++){
    if (mainArray[i]->isEmpty){
      for (j=0; j<6; j++){
        mainArray[i]->neighbor[j] = -99;
      }

    } // end of if
    // set the neighbors of nonempty vertices
    else{
      for (j = 0; j < 6; j++){
	tmpCh = n[j]; 
        // if the neighbor is empty
	if (myMap[i]->getNeighbor(tmpCh) == NULL){
	  mainArray[i]->neighbor[j] = -99;
	}  // end of if
        // if the neighbor is not empty
	else{
	  x = myMap[i]->getNeighbor(tmpCh)->getX();
	  y = myMap[i]->getNeighbor(tmpCh)->getY();
	  z = myMap[i]->getNeighbor(tmpCh)->getZ();
	  tmp = x + y * width + z* width * length;
	  mainArray[i]->neighbor[j] = tmp;
	}   // end of else
      }  // end of inner for
      // cerr<<"outer for loop ended"<<endl;
    } // end of else


  } // end of outer for

  //cerr<<"initialization done"<<endl;
}      // end of function initialize



   
// Utility function that adds a new node to the tail of the list.
//
// args: Q_node *anode- pointer to the node that needs to be added
void BFS::addToQ (Q_node *anode){
  anode->daughter = Q_head;
  anode->parent = Q_head->parent;
  
  
  // reassign daughters and parents of Q_head
  Q_head->parent->daughter = anode;
  Q_head->parent = anode;
}  
// end of functon addToQ



/* Public methods */

// Uses a breadth-first search to check that the whole level is
// connected to the pacman starting point with the input coordinates 
// (pacMx,pacMy,pacMz).
// 1 is returned if successful, 0 otherwise.
//
// args: int pacMx- x-coordinate of the pacman starting point to check
//       int pacMy- y-coordinate ""
//       int pacMz- z-coordinate ""
int BFS::check_connect (int pacMx, int pacMy, int pacMz){
  int i, tmpI, tmpJ, j, nb;
  Q_node *tmpQ, *newQ;

  int Connectivity = 1;

  // index of the pacman starting point in the array
  int pacman = pacMx + pacMy * width + pacMz * width * length;

  // does pacman exist?
  if (mainArray[pacman]->isEmpty == true){
    cout << "the pacman does not exist" << endl;
    return 0;
  }

  // set pacman color to 1
  mainArray[pacman]->color = 1;
  mainArray[pacman]->distance = 0;
  mainArray[pacman]->parent = -99;

  // add pacman to the queue
  tmpQ = new Q_node;
  tmpQ->posIndx = pacman;
  addToQ (tmpQ);
  //cerr<<"pacman="<<pacman<<" first in queue "<<Q_head->daughter->posIndx<<endl;
  // start the while loop for the breadth-first search
  while (Q_head->daughter != Q_head){
    tmpI = Q_head->daughter->posIndx;
    //cerr<<"Processing "<<tmpI<<endl;
    for (i = 0; i < 6; i++){
      // if the neighbor of tmpI does not exit, skip
      if (mainArray[tmpI]->neighbor[i] < 0){
	continue;
      }    
      // if the color of the neighbor is not 0(white), skip
      nb = mainArray[tmpI]->neighbor[i];
      if (mainArray[nb]->color != 0)
	continue;
      
      // set color of the neighbor to 1(grey)
      mainArray[nb]->color = 1;
      // set parent as tmpI and distance as 1 plus that of the parent
      mainArray[nb]->parent = tmpI;
      mainArray[nb]->distance = mainArray[tmpI]->distance + 1;

      //cerr<<"set color to 1 for "<<nb<<endl;
      
      // add that neighbor to queue
      tmpJ = mainArray[nb]->posIndx;
      newQ = new Q_node;
      newQ->posIndx = tmpJ;
      addToQ (newQ);
    } // end of for loop
    
      // set the color of tmpI to 2 (black)
    mainArray[tmpI]->color = 2;
    
    
    // remove tmpQ from the queue
    Q_head->daughter->daughter->parent = Q_head;
    Q_head->daughter = Q_head->daughter->daughter;
    //cerr<<" color set to 2 and removed "<<tmpI<<endl;
  }  //end of while
  
  // final check of the reachability from the pacman
  for (i = 0; i < the_size; i++){
    if ((!(mainArray[i]->isEmpty)) && (mainArray[i]->color == 0)){
      Connectivity = 0;
      //cerr<<"i= "<<i<<" color="<<mainArray[i]->color<<endl;
      //cerr<<"width= "<<width<<" length="<<length<<" floor="<<floor<<endl;
      
      break;
    }
  }  // end of for

  return Connectivity;
}  // end of function check_connect


// Constructor

// Creates an array of vertices from the map of a Level.
//
// args: Space **aMap- an array of pointers to Spaces that represents the map
//                     in a Level
//       int theWidth- width of the Level represented by amap
//       int theLength- length ""
//       int theFloor- number of floors (height) of ""
BFS::BFS(Space **aMap, int theWidth, int theLength, int theFloor){
  // assignment
  //myMap = aMap;
    width = theWidth;
    length = theLength;
    floors = theFloor;

    // calculate total size of the main array
    the_size = width * length * floors;

    // calculate pacman's position index
    //pacman = pacMx + pacMy * width + pacMz * width * length;

    // initialize the main array
    mainArray = new aVertex* [the_size];

    initialize(aMap);

    // initialize the queue
    Q_head = new Q_node;
    //cerr<<"initialized the listhead"<<endl;
    Q_head->daughter = Q_head;
    //cerr<<"set daughter node"<<endl;
    Q_head->parent = Q_head;
    //cerr<<"set parent node"<<endl;
    Q_head->posIndx = -99;
    //cerr<<"set index"<<endl;
} // end of the constructor


// Destructor

// Deallocates memory assigned to the array of vertices.
BFS::~BFS(){
  for (int i=0; i<the_size; i++){
    if (mainArray[i]!=NULL){
      delete mainArray[i];
    }
  
  }
  delete[] mainArray;
}
