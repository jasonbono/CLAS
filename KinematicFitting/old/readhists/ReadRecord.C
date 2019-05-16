

  /*

  jan 19 2012 

  making a code to read in the numbers of output file from genr8


  */




#include <TFile.h> 
#include <TTree.h> 
#include <Riostream.h>
#include <TLorentzVector.h>



//define the structs: one to loop over each event and the other to loop over the particles in that event.
//----------------------------------------------------------------------------------------------------- 




  struct ParticleStruct {
   int pid;
   float mass;
   int charge;	
   TLorentzVector v;   	
  };
  


  struct EventStruct {
   int eventid;
   float beamenergy;
	ParticleStruct particles[5];	
   TLorentzVector v;   	
  };







//  -------------------------------------------open the file--------------------------------------------

  EventStruct evnt;
  ifstream file ("myKstarKstar.output");
  
  while (ReadRecord (myKstarKstar.output, EventStruct)) {
	
	
  }

  myKstarKstar.output.close();

//-------------------------------------------------------------------------------------

  bool ReadRecord (ifstream & myKstarKstar.output, EventStruct & evnt){
	bool result = false;
	
	//local varibles, its tricky, i use theese for multiple meanings. checkout the data file to see the meanings  
	int temp_int[3];
	float temp_float[5];

	myKstarKstar.output >> temp_int[0] >> temp_int[1] >> temp_int[2] 
	>> temp_float[0] >> temp_float[1] >> temp_float[2] >> temp_float[3];
	
	evnt.eventid = temp_int [1];
	evnt.beamenergy = tmp_float[2];
	
	//now loop over all the particles
	for (int i = 0; i < 5; i++){
		myKstarKstar.output >> temp_int[0] >> temp_int[1] >> temp_float[0] 
		>> temp_int[2] >> temp_float[1] >> temp_float[2] >> temp_float[3] >> temp_float[4];	
		
		particle[i].pid = temp_int[1];
		particle[i].mass = temp_int[1];
		particle[i].charge = temp_int[1];
		particle[i].v.SetPxPyPzE(temp_float[1], temp_float[2], temp_float[3], temp_float[4]);
	
	
	}
	
	result = true;
  }
