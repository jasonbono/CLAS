// program: classes
// 
// input: none
// output: formatted streams of text
// 
// written by: Puneet Khetarpal
// date: October 27, 2011

// libraries included /////////////////////////////////////////////////////////
#include <iostream>
#include "Time.h"

using namespace std;

// global constants ///////////////////////////////////////////////////////////

// function prototypes ////////////////////////////////////////////////////////
// level 0
void Print(const Time &);                    // t


// function definitions ///////////////////////////////////////////////////////

int main() {
  // declare an instance of the Time object using the default constructor
  Time aTime;
  // print the current state of the object
  cout << "aTime:\n";
  Print(aTime);
  
  // declare an instance of the Time object using the second constructor
  Time aTime2(22, 56, 43);
  // print the current state of the object
  cout << "aTime2\n";
  Print(aTime2);
  
  // declare an instance of the Time object using the copy constructor
  Time aTime3(aTime2);
  // print the current state of the object
  cout << "aTime3\n";
  Print(aTime3);
  
  // dynamically create and initialize the Time object
  Time *myTime = new Time(5, 25, 0);
  cout << "myTime\n";
  Print(*myTime);
  
  // set the attributes of the last two times
  aTime3.SetHour(2);
  myTime->SetMinute(12);
  // print out the information
  cout << "aTime3\n";
  Print(aTime3);
  cout << "myTime\n";
  Print(*myTime);
  
  // setup time in NY city
  Time *nyTime = new Time(0, 29, 00);
  // get the hour of the ny time
  int nyHour = nyTime->GetHour();
  //  compute the hours at LA
  int laHour = (nyHour == 0) ? 21 : nyHour - 3;
  // set the time at LA
  Time *laTime = new Time(*nyTime);
  laTime->SetHour(laHour);
  
  cout << "nyTime\n";
  Print(*nyTime);
  cout << "laTime\n";
  Print(*laTime);
  
  cout << "deleting objects\nmyTime: ";
  delete myTime;
  cout << "nyTime: ";
  delete nyTime;
  cout << "laTime: ";
  delete laTime;
  
  return 0;
}

// level 1 ////////////////////////////////////////////////////////////////////

// preconditions: none
// postconditions: the universal and standard time is printed
void Print(const Time & t) {
  cout << "Universal time: " << t.GetUniversal() << endl;
  
  cout << "Standard Time: " << t.GetStandard() << endl << endl;
  
  return;
}

