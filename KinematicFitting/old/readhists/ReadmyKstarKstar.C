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





struct ParticleStruct 
{
	int pid;
	float mass;
	int charge;	
	TLorentzVector v;	   	
};
  


struct EventStruct
{
	int eventid;
	float beamenergy;
	ParticleStruct particle[5];	
  	
};



//---------------------------------------level 0-----------------------------------------
//  ---------------------------------------------------------------------------------------

void ReadmyKstarKstar()
{
	
	//define local variables
	EventStruct evnt;
	int eventcout = 0;
	int MAXevent = 8;
	// open file for reading
	ifstream myfile ("myKstarKstar.output");
	

	// while ReadRecord returns true... this returns false at the end of the data file.
	// ReadRecord reads an event from the file and stores it in evnt
	// this accualy forces the loop to generate untill the end of the file. 
	// the while loop accualy controls things outside of its scope. it does this
	// by asking "ReadRecord" to start. ReadRecord starts from where it left off in the code
	// durring the last "iteration"
	while (ReadRecord(myfile, evnt) || eventcout < MAXevent )
	{
		cout << "reading records: eventcount=" << eventcout << endl;
		eventcout = eventcout + 1;
	}

	  myfile.close();	

	

}



 

//-------------------------------------------------------------------------------------
// passing myfile and evnt by refrence 
bool ReadRecord (ifstream & myfile, EventStruct & evnt)
{
	bool result = false;
	
	//local varibles, its tricky, i use theese for multiple meanings. checkout the data file to see the meanings  
	int temp_int[3];
	float temp_float[5];

	myfile >> temp_int[0] >> temp_int[1] >> temp_int[2] 
	>> temp_float[0] >> temp_float[1] >> temp_float[2] >> temp_float[3];
	
	evnt.eventid = temp_int [1];
	evnt.beamenergy = temp_float[2];
	//now loop over all the particles
	for (int i = 0; i < 5; i++)
	{
		myfile >> temp_int[0] >> temp_int[1] >> temp_float[0] 
		>> temp_int[2] >> temp_float[1] >> temp_float[2] >> temp_float[3] >> temp_float[4];	
		
		particle[i].pid = temp_int[1];
		particle[i].mass = temp_float[0];
		particle[i].charge = temp_int[2];
		particle[i].v = TLorentzVector(temp_float[1], temp_float[2], temp_float[3], temp_float[4]);
		
		cout << " i=" << i << " pid=" << temp_int[1] << " mass=" << temp_float[0] 
		<< " charge " << temp_int[2] << endl; 
		
		   

	}
	

	// return true result if not at the end of the file
	if (!myfile.eof())
	{
		result = true;
	}
	
	// return the boolian value to ReadRecord which goes to the while loop in level0
	return result;
}

