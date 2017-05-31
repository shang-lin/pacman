/* BFS.h 
   header file for BFS class */

#include "Space.h"

/* Revision History
 * 6/13/02: Added BFS.h to CVS. author: Shang-Lin Chen
 * 6/14/02: Debugged initialize() and addToQ and fixed various other errors, so
 *          the BFS is working now.
 *          author: Shang-Lin Chen
 */

// This struct represents a vertex in a colored graph. Vertices are initialized
// from the map of a Level.
typedef struct aVertex{
  bool isEmpty; // flag that is true if there is a Pacman in this vertex
  int color; // color of the node
  int posIndx; // index of this vertex in the level
  int distance; // store the distance from the source vertex
  int parent;  // the position index of the predecessor vertex
  int neighbor[6];
} aVertex;

// This struct represents a node in a circular doubly-linked list.
 typedef struct Q_node{
   int posIndx; // corresponds to the index in the level 
   Q_node *parent; // pointer to previous node in the list
   Q_node *daughter; // pointer to next node in the list
 } Q_node;



/**
 * Description: 
 *
 * The BFS class implements a breadth-first search for checking reachability
 * and connectedness in a Level. A graph is created from the map of a Level.
 * The breadth-first search is performed on this graph.
 *
 * A BFS object is initialized by calling the constructor with an array of
 * pointers to Space. This array represents the map of a Level. To find if
 * all spaces in the map are reachable from a specific Space, pass the 
 * coordinates of that Space to the method check_connect(int, int, int).
 *
 **/

class BFS{
    
   /* Data members */

 private:

  // Array of vertices
  aVertex **mainArray;
  
  // Dimensions of the Level to be checked by BFS.
  int width;
  int length;
  int floors;

  // Maximum size of mainArray
  int the_size;

  // Head of a circular doubly-linked list
  Q_node *Q_head;

 public:

  /* Methods */

 private:


  // Utility function that adds a new node to the tail of the list.
  //
  // args: Q_node *anode- pointer to the node that needs to be added
  void addToQ( Q_node * );
   

  // Initializes the mainArray, setting the color of each element to 0 (white).
  // Also builds the adjacency list of each element.
  //
  // args: Space** myMap- array of pointers to Space that represents the map
  //                      of a level
  void initialize( Space ** );

 public:

  // Checks that the whole level is
  // connected to the pacman starting point with the input coordinates 
  // (pacMx,pacMy,pacMz).
  // 1 is returned if successful, 0 otherwise.
  //
  // args: int pacMx- x-coordinate of the pacman starting point to check
  //       int pacMy- y-coordinate ""
  //       int pacMz- z-coordinate "" 
  int check_connect( int, int, int );



  // Constructor
  
  // Creates an array of vertices from the map of a Level.
  //
  // args: Space **aMap- an array of pointers to Spaces that represents the map
  //                     in a Level
  //       int theWidth- width of the Level represented by amap
  //       int theLength- length ""
  //       int theFloor- number of floors (height) of ""
  BFS(Space **, int, int, int );


  // Destructor

  // Deallocates memory assigned to the array of vertices.
  ~BFS();

};
