#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

struct EventStruct {
	// items of the event will go here
	
};

bool ReadAnEvent(ifstream &, EventStruct &);

int main() 
{

	//---------------------------------------------function prototypes--------------------------	
	

	
	string file = "myXismall.gamp"; // "myXismall.gamp" == const char *
	//char name[256] = "myXismall.gamp";   // char* 
	
	//const char* var = file.c_str();
	cout << var[0] << " " << var[1] << endl;
	
	
	// string.h
	// public: 
	// 
	// const char * c_str(); 
	// 
	
	ifstream myfile;
	myfile.open(file.c_str());    // open(const char*)
	
	EventStruct AnEvent;
	
	while (ReadAnEvent(myfile, AnEvent)) {
		// Add the event to a tree
		
		// add the event info to fill histograms here
	}

	myfile.close();

	return 1;
}




bool ReadAnEvent(ifstream & str, EventStruct & AnEvent) {
	// reading of an event will happen here
	
	return;
}

/*

//--------------------------------------count lines-----------------------------
int countlines(string f)
{
	
	
	cout << "called function"<<endl;
	ifstream myfile;
	myfile.open(f);
	cout <<"opened file"<<endl;
	myfile.close();
	cout <<"close file" <<endl;
	
	return 1;


}
//------------------------------------------------------------------------------
*/