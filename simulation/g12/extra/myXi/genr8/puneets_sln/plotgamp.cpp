/* april 10 2012: 

developer: jason bono

use: reads in the output file from genr8 and builds a root tree with all of the beam and fourvector information

change the gamp file name and the root file name


*/





#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
//#include <Float_t.h>

using namespace std;

struct EventStruct {
	// items of the event will go here
	int eventID;
	float Beam;
	float kp1[4];
	float pim[4];
	float lam[4];
	float kp2[4];	
};

//function prototype
bool ReadAnEvent(ifstream &, EventStruct &);

int main() 
{	
	
	
	
	string file = "myXismall.gamp"; // "myXismall.gamp" == const char *
	//char name[256] = "myXismall.gamp";   // char* 
	// could convert the string 'file' to a const char* by the following
	//const char* var = file.c_str();
	//and this would give the output 'm y'
	//cout << var[0] << " " << var[1] << endl;
	
	//open the file
	ifstream myfile;
	myfile.open(file.c_str());    // open(const char*)
		
	
	//local files
	TFile *newf = new TFile("myXismall.root","RECREATE"); 
  

	// setup the new trees
	TTree *tree = new TTree("fourvec tree"," 4-vecs,beam,id");
	TTree *mmtree = new TTree("masstree","masses,beam,id");
	
	
	// setup the branches for the forvectree
	Int_t id;
	Float_t  beam;
	Float_t kp1x,kp1y,kp1z,kp1t;
	Float_t pimx,pimy,pimz,pimt;
	Float_t lamx,lamy,lamz,lamt;	
	Float_t kp2x,kp2y,kp2z,kp2t;
	tree->Branch("id",&id,"id/I");
	tree->Branch("beam",&beam,"beam/F");
	tree->Branch("kp1x",&kp1x,"kp1x/F");
	tree->Branch("kp1y",&kp1y,"kp1y/F");
	tree->Branch("kp1z",&kp1z,"kp1z/F");
	tree->Branch("kp1t",&kp1t,"kp1t/F");
	tree->Branch("pimx",&pimx,"pimx/F");
	tree->Branch("pimy",&pimy,"pimy/F");
	tree->Branch("pimz",&pimz,"pimz/F");
	tree->Branch("pimt",&pimt,"pimt/F");
	tree->Branch("lamx",&lamx,"lamx/F");
	tree->Branch("lamy",&lamy,"lamy/F");
	tree->Branch("lamz",&lamz,"lamz/F");
	tree->Branch("lamt",&lamt,"lamt/F");
	tree->Branch("kp2x",&kp2x,"kp2x/F");
	tree->Branch("kp2y",&kp2y,"kp2y/F");
	tree->Branch("kp2z",&kp2z,"kp2z/F");
	tree->Branch("kp2t",&kp2t,"kp2t/F");
	
	
	//setup the branches for the masstree
	TLorentzVector fbeam,ftarget,fkp1,fkp2,fpim,flam;
	Float_t mmkpkp,mmkpkppim,mkp1,mkp2,mpim,mlam;
	tree->Branch("mmkpkp",&mmkpkp,"mmkpkp/F");
	tree->Branch("mmkpkppim",&mmkpkppim,"mmkpkppim/F");
	tree->Branch("mkp1",&mkp1,"mkp1/F");
	tree->Branch("mkp2",&mkp2,"mkp2/F");
	tree->Branch("mpim",&mpim,"mpim/F");
	tree->Branch("mlam",&mlam,"mlam/F");
	
	// setup struct
	EventStruct AnEvent;
	
	//fill the branches
	while (ReadAnEvent(myfile, AnEvent)) 
	{	
		//fill the branches
		id = AnEvent.eventID;
		beam = AnEvent.Beam;
		kp1x = AnEvent.kp1[0];
		kp1y = AnEvent.kp1[1];
		kp1z = AnEvent.kp1[2];
		kp1t = AnEvent.kp1[3];
		pimx = AnEvent.pim[0];
		pimy = AnEvent.pim[1];
		pimz = AnEvent.pim[2];
		pimt = AnEvent.pim[3];
		lamx = AnEvent.lam[0];
		lamy = AnEvent.lam[1];
		lamz = AnEvent.lam[2];
		lamt = AnEvent.lam[3];
		kp2x = AnEvent.kp2[0];
		kp2y = AnEvent.kp2[1];
		kp2z = AnEvent.kp2[2];
		kp2t = AnEvent.kp2[3];
		
		
		//now fill the TLorentz vectors of the particles
		fbeam.SetPxPyPzE(0,0,beam,beam);
		ftarget.SetXYZM(0,0,0,0.93827*0.93827);
		fkp1.SetPxPyPzE(kp1x,kp1y,kp1z,kp1t);
		fkp2.SetPxPyPzE(kp2x,kp2y,kp2z,kp2t);
		fpim.SetPxPyPzE(pimx,pimy,pimz,pimt);
		flam.SetPxPyPzE(lamx,lamy,lamz,lamt);
		
		mmkpkp = (fbeam + ftarget - fkp1 - fkp2).Mag();
		mmkpkppim = (fbeam + ftarget - fkp1 - fkp2 - fpim).Mag();
		mkp1 = fkp1.Mag();
		mkp2 = fkp2.Mag();
		mpim = fpim.Mag();
		mlam = flam.Mag();
		
		
		//fill the tree with the branches for each event
		tree->Fill();
	}
	
	//close the data file
	myfile.close();
	
	//look at the new tree
	//tree->Print();
	
	//write the new tree
	newf->Write();
	
	return 1;
}

bool ReadAnEvent(ifstream & myfile, EventStruct & AnEvent)
{
	// reading of an event will happen here
	float tempF;
	int tempI;
	bool result = false;

	if (myfile >> tempI >> AnEvent.eventID >> tempI >> tempF >> tempF >> AnEvent.Beam >> tempF
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.kp1[0] >> AnEvent.kp1[1] >> AnEvent.kp1[2] >> AnEvent.kp1[3] 
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.pim[0] >> AnEvent.pim[1] >> AnEvent.pim[2] >> AnEvent.pim[3]
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.lam[0] >> AnEvent.lam[1] >> AnEvent.lam[2] >> AnEvent.lam[3]
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.kp2[0] >> AnEvent.kp2[1] >> AnEvent.kp2[2] >> AnEvent.kp2[3])
	{
 		result = true;    
	}
	return result;

}
