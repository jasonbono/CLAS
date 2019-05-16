// program: structs
// 
// input: none
// output: formatted streams of text
// 
// written by: Puneet Khetarpal
// date: October 27, 2011

// libraries included /////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

// global constants ///////////////////////////////////////////////////////////

// structures and typedefs ////////////////////////////////////////////////////
struct TargetGeometry {   
  float x;                       // x position of target in cm
  float y;                       // y position of target in cm
  float z;                       // z position of target in cm
  float radius;                  // radius of the target in cm
  float length;                  // length of the target in cm
  int material;                  // material of target; 0=empty, 1=Hydrogen
};


// function prototypes ////////////////////////////////////////////////////////
// level 1 
void PrintTargetGeometry(const TargetGeometry &);     // a target
void PrintTargetGeometry(const TargetGeometry *);     // a target

// function definitions ///////////////////////////////////////////////////////

// level 0 ////////////////////////////////////////////////////////////////////

int main() {
  // one can declare a variable of datatype as defined from a struct
  TargetGeometry aTarget;   // 'aTarget' is an "instance" of the TargetGeometry 
                            // object
  
  // you can access the attributes of the object by using the '.' operator:
  cout << "aTarget:\n";
  PrintTargetGeometry(aTarget);

  // we can initialize the object at the time of declaration just like an array
  TargetGeometry aTarget2 = {0.0, 0.0, -4.2, 2.5, 5.1, 1};  
  cout << "aTarget2\n";
  PrintTargetGeometry(aTarget2);
  
  // one can also modify the object's attributes individually
  aTarget2.x = 0.107;
  aTarget2.y = -0.910;
  cout << "aTarget2 (modified)\n";
  PrintTargetGeometry(aTarget2);
  
  // we can also declare objects of any time dynamically in C++
  TargetGeometry *aTarget3 = new TargetGeometry();   
  // TargetGeometry() is a constructor that constructs an object of the 
  // type TargetGeometry. It is automatically generated for any user defined
  // object by the compiler. 'new' dynamically creates an object of type
  // TargetGeometry and returns a pointer of that type
  cout << "aTarget3\n";
  PrintTargetGeometry(*aTarget3);  // not the way the parameter is passed
  
  // attributes of a pointer to an object can be dereferenced by the '->' 
  // operator
  aTarget3->radius = 3.0;
  (*aTarget3).length = 30.0;      // dereference using the '*' and '.' operator 
  cout << "aTarget3 (modified)\n";
  PrintTargetGeometry(aTarget3);  // note the way the parameter is passed
      
  // dynamically objects can also be created for any data types
  int* x = NULL;     // at this point, x points to NULL 
  // to create an array of 10 integers using new:
  x = new int [10]; // this creates 10 integers and returns a pointer to the 
                    // first element of the array to x
  // if this fails, then the program throws a 'bad_alloc' exception and 
  // the program may be terminated if it isn't handled correctly
  
  // you can access the elements of the array as usual
  x[4] = 10;
  cout << "x[4] = " << x[4] << endl;
  
  // all dynamically created objects must be destroyed at the end of the scope
  delete aTarget3;
  delete[] x;
  
  return 0;
}

// level 1 ////////////////////////////////////////////////////////////////////

// preconditions: the target geometry object has been declared
// postconditions: the attributes of the object are sent to stdout
void PrintTargetGeometry(const TargetGeometry & aTarget) {
  cout << "x = " << aTarget.x << endl
       << "y = " << aTarget.y << endl
       << "z = " << aTarget.z << endl
       << "radius = " << aTarget.radius << endl
       << "length = " << aTarget.length << endl
       << "material = " << aTarget.material << endl << endl;
  
  return; 
}

// preconditions: the target geometry object has been declared
// postconditions: the attributes of the object are sent to stdout
void PrintTargetGeometry(const TargetGeometry * aTarget) {
  cout << "x = " << aTarget->x << endl
       << "y = " << aTarget->y << endl
       << "z = " << aTarget->z << endl
       << "radius = " << aTarget->radius << endl
       << "length = " << aTarget->length << endl
       << "material = " << aTarget->material << endl << endl;
  
  return; 
}