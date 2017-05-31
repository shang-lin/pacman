#include "genlevel.h"
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

int main (void){

	// reseed the random # generator
	srand (time (NULL));

	cerr << "Setting up random level generator object.." << endl;
	RandomLevelGenerator * rlg ;

	rlg = new RandomLevelGenerator ( 25, 25, 5, 10, 10 );
	
	cerr << "Writing level data.." << endl;
	
	int numhalls = 0;
	
	for (int k = 0; k <  rlg->getFloors( ) ; k++){
	cerr << "  Floor # " << k << ".." << endl;
		cout << "Floor # " << k << endl;
		for (int i = 0; i <  rlg->getWidth( ) ; i++){
			for (int j = 0; j <  rlg->getHeight( ) ; j++){
				cout << rlg->getValue(i,j,k);
				numhalls += (rlg->isHallway(i,j,k) ? 1 : 0 );
			}
			cout << endl;
		}
		cout << endl;
	}
	cerr << "  done." << endl;
	
	cerr << "This level contains:" << endl;
	cerr <<  "   " << numhalls << " hallway spaces" << endl;
	cerr <<  "   " << (rlg->getFloors( ) * rlg->getWidth( ) * rlg->getHeight( )) << " total spaces" << endl;
	cerr <<  "   It is " << (int)((100 * numhalls) / (rlg->getFloors( ) * rlg->getWidth( ) * rlg->getHeight( ))) << "% hallway" << endl;
	
	cerr << "Cleaning up.." << endl;
	delete (rlg);
	
	cerr << "Done." << endl;
	return 0;
}
