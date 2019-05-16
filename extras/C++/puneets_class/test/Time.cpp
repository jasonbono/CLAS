// class: Time
// class definition file: Time.cpp

// libraries included ////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <cstdio>
#include "Time.h"  // time class definition 

using namespace std;

// constructors //////////////////////////////////////////////////////////////

// preconditions: none
// postconditions: the object is constructed and datatypes init to 0
Time::Time() {     // default constructor
  SetTime(0, 0, 0);
}

// preconditions: hr, min, and sec are integers
// postconditions: the obect is constructed with the specified pars
Time::Time(int hr, int min, int sec) { // second constructor
  SetTime(hr, min, sec);
}

// preconditions: aTime is a Time object
// postconditions: the contents of aTime are copied to current object's
//    data types
Time::Time(const Time & aTime) {  // copy constructor
  SetTime(aTime.GetHour(), aTime.GetMinute(), aTime.GetSecond());
}

// destructors ///////////////////////////////////////////////////////////////
Time::~Time() {
  cout << "Destroying a Time object" << endl;
}

// modifiers /////////////////////////////////////////////////////////////////

// preconditions: hour, min and seconds are integers
// postconditions: the hour, minute and seconds are set to specified pars
void Time::SetTime(int hr, int min, int sec) {
  SetHour(hr);
  SetMinute(min);
  SetSecond(sec);
  
  return;
}

// preconditions: the hour is between 0 and 23
// postconditions: the hour is set
void Time::SetHour(int hr) {
  // if parameter is not between [0, 23], then set to 0
  this->hour = (hr >= 0 && hr < 24) ? hr : 0;
  
  return;
}

// preconditions: the minute is between 0 and 59
// postconditions: the minute is set
void Time::SetMinute(int minute) {
  // if parameter is not between [0, 59], then set to 0
  this->minute = (minute >= 0 && minute < 60) ? minute : 0;
  
  return;
}

// preconditions: the second is between 0 and 59
// postconditions: the second is set
void Time::SetSecond(int sec) {
  // if parameter is not between [0, 59], then set to 0
  this->second = (sec >= 0 && sec < 60) ? sec : 0;
  
  return;
}


// accessors /////////////////////////////////////////////////////////////////

// preconditions: none
// postconditions: the hour value is returned
int Time::GetHour() const {
  return hour;
}

// preconditions: none
// postconditions: the minute value is returned
int Time::GetMinute() const {
  return minute;
}

// preconditions: none
// postconditions: the second value is returned
int Time::GetSecond() const {
  return second;
}

// preconditions: none
// postconditions: returns the time in universal 24hr format
string Time::GetUniversal() const {
  // local variable 
  char buffer[50];

  // format the string buffer
  sprintf(buffer, "%02d:%02d:%02d", hour, minute, second);

  return buffer;
}

// preconditions: none
// postconditions: returns the time in standard AM-PM format
string Time::GetStandard() const {
  // local variables
  char buffer[50];
  int hrStd = (hour == 0 || hour == 12) ? 12 : hour % 12;
  
  // format the string buffer
  sprintf(buffer, "%02d:%02d:%02d %s", hrStd, minute, second, 
    (hour < 12) ? "AM" : "PM");
  
  return buffer;  
}
