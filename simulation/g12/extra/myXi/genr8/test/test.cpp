#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
#define MAX_LINES 25
#define MAX_IN_LINE 50

int main() {
  //open our file
  ifstream myfile ("test.txt");
  //initialize our array's
  int myarray[MAX_LINES][MAX_IN_LINE];
  //used for knowing how many numbers are stored in each array
  int totalargs[MAX_LINES];
  //rest of variables
  string line,tempnum;
  int end=0;
  int firstarg=0,secondarg=0;
  int num;

  //set all of our arrays to be zero'd out
  memset(myarray,0,MAX_LINES*MAX_IN_LINE);
  memset(totalargs,0,MAX_LINES);

  //make sure file is opened
  if (myfile.is_open()) {
    //get a line
    getline(myfile,line);  // this reads the first line and writes it to the string "line", if done sequentialy it will read the next line and redefine
    //the first line is the number, so set it to num
    num=atoi(line.c_str());
	cout << "the first line is: " << line <<endl;
    while(!myfile.eof()) {
      getline(myfile,line);
      //if there is a space in the line we have gotten
      while((end=line.find(' ',0))!=string::npos) {
        //get the number before the space
        tempnum=line.substr(0,end);
        myarray[firstarg][secondarg]=atoi(tempnum.c_str());
        secondarg++;
        //erase the part of the line we have gotten
        line.erase(0,end+1);
      }
      //we will have an extra number at the end after that loop
      //this gets that last number
      tempnum=line.substr(0,line.length());
      myarray[firstarg][secondarg]=atoi(tempnum.c_str());
      //set the number of args to our array
      totalargs[firstarg]=secondarg;
      firstarg++;
      //reset arg.
      secondarg=0;
    }
  } else {
    cout << "cannot open";
  }

  //this is extra, but it just shows you your variables and that
  //they really do have numbers in them.
  cout << "num: " << num << endl;
  for (int x=0;x<firstarg;x++) {
    cout << "Array " << x+1 << ": " << myarray[x][0];
    for (int y=1;y<=totalargs[x];y++) {
      cout << "," << myarray[x][y];
    }
    cout << endl;
  }
}