// class: Time
// header file: Time.h

#ifndef TIME_H    // preprocessor directive to prevent multiple inclusions of 
#define TIME_H    // the header file

// libraries included ////////////////////////////////////////////////////////

#include <string>

using namespace std;

// class definition //////////////////////////////////////////////////////////
class Time {

public:   // public data types and member functions
  // constructors and destructors
  Time();                        // default constructor
  Time(int, int, int);           // second constructor
  Time(const Time &);            // copy constructor
  ~Time();                       // default destructor
  
  // set functions: modifier member functions
  void SetTime(int, int, int);   // set hour, minute, second
  void SetHour(int);             // set hour
  void SetMinute(int);           // set minute
  void SetSecond(int);           // set second
  
  // get functions: accessor member functions
  int GetHour() const;           // return hour
  int GetMinute() const;         // return minute
  int GetSecond() const;         // return second
  
  string GetUniversal() const;   // return universal time
  string GetStandard() const;    // return standard time 
  
private:  // private data types and member functions
  int hour;                      // 0 - 23 (24-hour clock format)
  int minute;                    // 0 - 59
  int second;                    // 0 - 59

};  // end of class time

#endif          