/* levelLoader.cc
 * This file is another test program for the Level class. Unlike 
 * test_validate.cc, it directly calls Level.
 */

/* Revision History 
 * 5/18/02: Created. author: Shang-Lin Chen
 */

#include"Level.h"
#include<iostream>

int main(int argc, char** argv){
  string filename(argv[1]);
  Level mylevel(filename);
  return 0;
}
