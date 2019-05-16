/* 

Date: April 17 2012: 

Author: jason bono

Purpose: reads in the output file from genr8 (which came from try4 directory on the clas work disk)
and builds a root tree with all of the beam and fourvector information



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
	float pim1[4];
	float pro[4];
	float pim2[4];
	float kp2[4];	
};

//function prototype
bool ReadAnEvent(ifstream &, EventStruct &);

int main() 
{	
		
	file = "myXi_try4.ascii";
	
	/* a little left over note from puneet about const char *
	string file = "myXismall.gamp"; // "myXismall.gamp" == const char *
	char name[256] = "myXismall.gamp";   // char* 
	could convert the string 'file' to a const char* by the following
	const char* var = file.c_str();
	and this would give the output 'm y'
	cout << var[0] << " " << var[1] << endl;
	*/
	
	//open the file
	ifstream myfile;
	myfile.open(file.c_str());    // open(const char*)
		
	
	//local files
	TFile *newf = new TFile("myXi_try4.root","RECREATE"); 
  

	// setup the new trees
	TTree *tree = new TTree("FourVecTree"," 4-vecs,beam,id");
	TTree *mmtree = new TTree("MassTree","masses,beam,id");
	
	
	// setup the branches for the forvectree
	Int_t id;
	Float_t  beam;
	Float_t kp1x,kp1y,kp1z,kp1t;
	Float_t pim1x,pim1y,pim1z,pim1t;
	Float_t prox,proy,proz,prot;
	Float_t pim2x,pim2y,pim2z,pim2t;	
	Float_t kp2x,kp2y,kp2z,kp2t;
	tree->Branch("id",&id,"id/I");
	tree->Branch("beam",&beam,"beam/F");
	tree->Branch("kp1x",&kp1x,"kp1x/F");
	tree->Branch("kp1y",&kp1y,"kp1y/F");
	tree->Branch("kp1z",&kp1z,"kp1z/F");
	tree->Branch("kp1t",&kp1t,"kp1t/F");
	tree->Branch("pim1x",&pim1x,"pim1x/F");
	tree->Branch("pim1y",&pim1y,"pim1y/F");
	tree->Branch("pim1z",&pim1z,"pim1z/F");
	tree->Branch("pim1t",&pim1t,"pim1t/F");
	tree->Branch("prox",&prox,"prox/F");
	tree->Branch("proy",&proy,"proy/F");
	tree->Branch("proz",&proz,"proz/F");
	tree->Branch("prot",&prot,"prot/F");
	tree->Branch("pim2x",&pim2x,"pim2x/F");
	tree->Branch("pim2y",&pim2y,"pim2y/F");
	tree->Branch("pim2z",&pim2z,"pim2z/F");
	tree->Branch("pim2t",&pim2t,"pim2t/F");
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
	tree->Branch("mpim1",&mpim1,"mpim1/F");
	tree->Branch("mpro",&mpro,"mpro/F");
	tree->Branch("mpim2",&mpim2,"mpim2/F");	
	tree->Branch("mkp2",&mkp2,"mkp2/F");	
	
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
		pim1x = AnEvent.pim1[0];
		pim1y = AnEvent.pim1[1];
		pim1z = AnEvent.pim1[2];
		pim1t = AnEvent.pim1[3];
		prox = AnEvent.pro[0];
		proy = AnEvent.pro[1];
		proz = AnEvent.pro[2];
		prot = AnEvent.pro[3];
		pim2x = AnEvent.pim2[0];
		pim2y = AnEvent.pim2[1];
		pim2z = AnEvent.pim2[2];
		pim2t = AnEvent.pim2[3];		
		kp2x = AnEvent.kp2[0];
		kp2y = AnEvent.kp2[1];
		kp2z = AnEvent.kp2[2];
		kp2t = AnEvent.kp2[3];
		
		
		//now fill the TLorentz vectors of the particles
		fbeam.SetPxPyPzE(0,0,beam,beam);
		ftarget.SetXYZM(0,0,0,0.93827*0.93827);
		fkp1.SetPxPyPzE(kp1x,kp1y,kp1z,kp1t);
		fpim1.SetPxPyPzE(pim1x,pim1y,pim1z,pim1t);
		fpro.SetPxPyPzE(prox,proy,proz,prot);
		fpim2.SetPxPyPzE(pim2x,pim2y,pim2z,pim2t);
		fkp2.SetPxPyPzE(kp2x,kp2y,kp2z,kp2t);
		
		
		mmkpkp = (fbeam + ftarget - fkp1 - fkp2).Mag();
		mmkpkppim = (fbeam + ftarget - fkp1 - fkp2 - fpim).Mag();
		
		mkp1 = fkp1.Mag();
		mpim1 = fpim1.Mag();
		mpro = fpro.Mag();
		mpim2 = fpim2.Mag();
		mkp2 = fkp2.Mag();
		
		//fill the tree with the branches for each event
		tree->Fill();
	}
	
	//close the data file
	myfile.close();
	
	//look at the new tree
	//tree->Print();
	
	//rename the tree
	tree->Write("FourVecTree2");
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
	>> tempI >> AnEvent.pim1[0] >> AnEvent.pim1[1] >> AnEvent.pim1[2] >> AnEvent.pim1[3]
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.pro[0] >> AnEvent.pro[1] >> AnEvent.pro[2] >> AnEvent.pro[3]
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.pim2[0] >> AnEvent.pim2[1] >> AnEvent.pim2[2] >> AnEvent.pim2[3]
	>> tempI >> tempI >> tempF
	>> tempI >> AnEvent.kp2[0] >> AnEvent.kp2[1] >> AnEvent.kp2[2] >> AnEvent.kp2[3])
	{
 		result = true;    
	}
	return result;

}
