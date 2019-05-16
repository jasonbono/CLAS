/*structures:
librarys
variables
function prototypes
int main
subroutines

*/
#include <iostream>

using namespace std;


int main(int bob, char** eric) {   // first argument is total number of parameters given to the command line including the name of the executable
  // the second argument is the whitespace separated parameters specified at the command line stored as an array of strings
  // local variables

  cout << "total number of input args: " << bob << endl;
  
  for (int i = 0; i < bob; i++) {
    cout << "argument " << i << ": " << eric[i] << endl;
  }

  // statements

  return 0;  
}
