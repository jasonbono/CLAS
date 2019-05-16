/* 

Important Details:  the mytmic.C file must be included through diffrent paths for local runing and jlab running.

Author: Jason Bono
Date: September 4 2012:
Purpose: To read in the four-vector information from gamp format (see below) and make a root ntuple from it
Usage:
		> analyzegamp work.gamp
		with output: work.gamp.root

Caution: change the included path to mytmin.C depending on what system you are using.



Things to think about: 
*interchanging pim1 and pim2
*the calculation of tkp1



==============================================
GAMP FORMAT LOOKS LIKE WHAT IS PASTED BELOW::
6
1 0 0.000000 0.000000 4.000000 4.000000
9 -1 0.028103 0.015128 0.348114 0.376406
14 1 -0.130590 0.082074 1.163450 1.502583
9 -1 -0.085124 -0.043838 0.130992 0.214025
11 1 0.209546 0.245731 0.378473 0.700895
11 1 0.151293 -0.197184 2.181397 2.250330
6
1 0 0.000000 0.000000 4.000000 4.000000
9 -1 0.061945 0.177248 0.268121 0.355841
14 1 0.014178 0.137692 0.920274 1.321520
9 -1 0.066848 0.070498 0.087142 0.191081
11 1 -0.171628 -0.064559 0.565573 0.772798
11 1 -0.031044 -0.262325 2.338919 2.405003
6
============================================




October 8 2012:  added w,polarization angles: {w,COS_pi_x,COS_pi_y,COS_pi_z,Xcmtheta}

October 8 2012 v03:  fixed issue regarding the boosting. it looks like my method is right.



*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string>
#include <stdio.h>

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

#include "/u/home/jbono/macros/mytmin.C"
//#include "/Users/Bono/clas/scripts/mytmin.C"


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

int main(int argc, char *argv[]) //use argc & argv to pass the file names through the commandline
{	
	
	
	//string file = "test.gamp";
	//string file = argv[1].gamp;
	std::string file(argv[1]);
	std::string inext(".gamp");
	std::string outext(".root");
	//std::string infile = file + inext;
	//std::string outfile = file + inext + outext;
	std::string infile = file;
	std::string outfile = file + outext;
	
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
	myfile.open(infile.c_str());    // open the gamp file (opening requires a const char*)
	
	//local files
  	TFile *newf = new TFile(outfile.c_str(),"RECREATE");  
	cout << "=========" << infile << "  " << outfile << "=======" <<endl;
	
	// setup the new trees
	TTree *tree = new TTree("GampTree"," ");
	
	// setup the branches for the forvectree
	Float_t beam;
	Float_t kp1x,kp1y,kp1z,kp1t;
	Float_t pim1x,pim1y,pim1z,pim1t;
	Float_t prox,proy,proz,prot;
	Float_t pim2x,pim2y,pim2z,pim2t;	
	Float_t kp2x,kp2y,kp2z,kp2t;
	Float_t tkp1,tminkp1,tpkp1;
	Float_t w,COS_pi_x,COS_pi_y,COS_pi_z,Xcmtheta;
	Float_t KPKPcmtheta;
//	Float_t mmkp1;
	//tree->Branch("id",&id,"id/I");
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
	
	//setup the branches for the masses
	TLorentzVector fbeam,ftarget,fkp1,fkp2,fpim1,fpro,fpim2;
	Float_t mmkpkp,mmkpkppim,mkp1,mkp2,mpim1,mpro,mpim2,mmkp1,mmkp2;
	tree->Branch("mmkpkp",&mmkpkp,"mmkpkp/F");
	tree->Branch("mmkpkppim",&mmkpkppim,"mmkpkppim/F");	
	tree->Branch("mkp1",&mkp1,"mkp1/F");
	tree->Branch("mpim1",&mpim1,"mpim1/F");
	tree->Branch("mpro",&mpro,"mpro/F");
	tree->Branch("mpim2",&mpim2,"mpim2/F");	
	tree->Branch("mkp2",&mkp2,"mkp2/F");
	tree->Branch("mmkp1",&mmkp1,"mmkp1/F");
	tree->Branch("mmkp2",&mmkp2,"mmkp2/F");
	
	//	and the mandastam varable t,tmin,tp.
	tree->Branch("tkp1",&tkp1,"tkp1/F");	
	tree->Branch("tminkp1",&tminkp1,"tminkp1/F");
	tree->Branch("tpkp1",&tpkp1,"tpkp1/F");
	
	//setup tree for w,COS_pi_x,COS_pi_y,COS_pi_z,Xcmtheta
	tree->Branch("w",&w,"w/F");
	tree->Branch("COS_pi_x",&COS_pi_x,"COS_pi_x/F");
	tree->Branch("COS_pi_y",&COS_pi_y,"COS_pi_y/F");
	tree->Branch("COS_pi_z",&COS_pi_z,"COS_pi_z/F");
	tree->Branch("Xcmtheta",&Xcmtheta,"Xcmtheta/F");
	tree->Branch("KPKPcmtheta",&KPKPcmtheta,"KPKPcmtheta/F");
	// setup struct
	EventStruct AnEvent;
	
	//set up a count for diagnostics
	int count=0;  //must be from cpp rather than root to do % operator on it
	//fill the branches
	while (ReadAnEvent(myfile, AnEvent)) 
	{	
		//increment the counter 
		count = count + 1; 
		
		//fill the branches
		//id = AnEvent.eventID;
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
		
		//------------------------------------- fill the TLorentz vectors of the particles-----------------------------------------
		fbeam.SetPxPyPzE(0,0,beam,beam);
		ftarget.SetXYZM(0,0,0,0.93827);
		fkp1.SetPxPyPzE(kp1x,kp1y,kp1z,kp1t);
		fpim1.SetPxPyPzE(pim1x,pim1y,pim1z,pim1t);
		fpro.SetPxPyPzE(prox,proy,proz,prot);
		fpim2.SetPxPyPzE(pim2x,pim2y,pim2z,pim2t);
		fkp2.SetPxPyPzE(kp2x,kp2y,kp2z,kp2t);
		
		mmkpkp = (fbeam + ftarget - fkp1 - fkp2).Mag();
		mmkpkppim = (fbeam + ftarget - fkp1 - fkp2 - fpim1).Mag();
		
		mkp1 = fkp1.Mag();
		mpim1 = fpim1.Mag();
		mpro = fpro.Mag();
		mpim2 = fpim2.Mag();
		mkp2 = fkp2.Mag();
		
		mmkp1 = (fbeam + ftarget - fkp1).Mag();
		mmkp2 = (fbeam + ftarget - fkp2).Mag();
		
		// -------------------------------------------- calculate mandalstam tkp1,tminkp1 ------------------------------------------------------------
		Float_t mkp = 0.493667;
		Float_t mpr = 0.938272;
		Float_t mmkp1 = (fbeam + ftarget - fkp1).Mag();
		Float_t pkp1 = sqrt(kp1x*kp1x + kp1y*kp1y + kp1z*kp1z);
		tkp1 = mkp*mkp - 2*beam*kp1t + 2*beam*sqrt(kp1z*kp1z) ;
		tminkp1 = tmin(beam,0.0,mpr,mkp,mmkp1);
		tpkp1 = sqrt((tkp1 - tminkp1)*(tkp1 - tminkp1));
		//tkp1 = mkp*mkp - 2*beam*ekp1 + 2*beam*pkp1*kp1labtheta ;
		
		
		//------------------------------------------------------compute w -------------------------------------------------------------------
		
		
		TLorentzVector fw = fbeam + ftarget;
		w = fw.M();
		
		
		//-------------------------------------COMPUTE PION ANGLES IN GOTTFRIED JACKSON FRAME--------------------------------------------------
		
		
		//declarations and initializations for boosts.
		Float_t Mcas=1.32131;
		TLorentzVector fcm = fbeam + ftarget;
		TLorentzVector fkpkp = fkp1 + fkp2;
		TLorentzVector fcas = fbeam + ftarget - fkpkp;
		TVector3 Bcas,Bcm;  //boosts
		Bcm = -fcm.BoostVector();
		TVector3 tbeam_lab;
		tbeam_lab.SetXYZ(fbeam(0), fbeam(1), fbeam(2)); 
		TVector3 tkpkp_lab;
		tkpkp_lab.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
		TVector3 tcas_lab;
		tcas_lab.SetXYZ(fcas(0), fcas(1), fcas(2));
		
		//define lab coordinate system
		TVector3 unitZ_lab;
	  	TVector3 unitY_lab;
	  	TVector3 unitX_lab;
		unitZ_lab = tbeam_lab.Unit(); 
		unitY_lab = tbeam_lab.Cross(tcas_lab).Unit();
		unitX_lab = unitZ_lab.Cross(unitY_lab).Unit();	
	
		//boost beam, kpkp, pion to jackson frame 
		Bcas = -fcas.BoostVector();
	    fbeam.Boost(Bcas);
		fkpkp.Boost(Bcas);
		fpim1.Boost(Bcas);
	
		//fill boosted fourvector momentum into three vectors
		TVector3 tbeam_jackson, tkpkp_jackson, tpi_jackson;
	  	tbeam_jackson.SetXYZ(fbeam(0), fbeam(1), fbeam(2));
	  	tkpkp_jackson.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
	  	tpi_jackson.SetXYZ(fpim1(0), fpim1(1), fpim1(2));
	  	
	  	//boost to back to lab frame
	  	fbeam.Boost(-Bcas);
		fkpkp.Boost(-Bcas);
		fpim1.Boost(-Bcas);
	
		//define cooridinate system in gottfried-jackson frame
	  	TVector3 unitZ_jackson;
	  	TVector3 unitY_jackson;
	  	TVector3 unitX_jackson;
	  	unitZ_jackson = (tbeam_jackson).Unit();  //beam
	  	unitY_jackson = tbeam_jackson.Cross(tkpkp_jackson).Unit(); //beam.x.kpkp
	  	unitX_jackson = unitZ_jackson.Cross(unitY_jackson).Unit(); //Z.x.Y

		//pion angles in jackson frame
		COS_pi_x = cos(unitX_jackson.Angle(tpi_jackson)); 
		COS_pi_y = cos(unitY_jackson.Angle(tpi_jackson));
		COS_pi_z = cos(unitZ_jackson.Angle(tpi_jackson));
		
		///pion angles in lab frame
		//COS_pi_x = cos(unitX_lab.Angle(tpi_jackson)); 
		//COS_pi_y = cos(unitY_lab.Angle(tpi_jackson));
		//COS_pi_z = cos(unitZ_lab.Angle(tpi_jackson));
		
		//------------------------------------------------------Xi ANGLES IN CM FRAME ------------------------------------------------------------------
		fcas.Boost(Bcm);
		fkpkp.Boost(Bcm);
		
		//store components into three vector
		TVector3 tcas_cm,tkpkp_cm;
		tcas_cm.SetXYZ(fcas(0), fcas(1), fcas(2));
		tkpkp_cm.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));

		//boost back to lab
		fcas.Boost(-Bcm);
		fkpkp.Boost(-Bcm);
		//compute angle with the beam (the beam dosent have to be boosted to cm for angle computation)
		Xcmtheta = cos(tbeam_lab.Angle(tcas_cm));
		KPKPcmtheta = cos(tbeam_lab.Angle(tkpkp_cm));
		
		//----------------------------------------------------------------------------------------------------------	
		
		
		
		//--------------------------------------run some tests and diagnostics------------------------------------------
		Float_t tkp1B = (fbeam - fkp1).M2();
		Float_t tkp1C = (fbeam - fkp1).Mag2();
		if(count % 1000==0)
  		{
			//cout << "tkp1= " << tkp1 << " tkp1B=" << tkp1B << " tkp1C=" << tkp1C <<endl;
			//cout << "mkp= " << mkp << "  kp1t= " << kp1t << " fkp1.Energy()= " << fkp1.Energy() 
			//	<< "  kp1z= " << kp1z << endl;
			cout <<"--------------------------------------------------------------------------------------------------" <<endl;
			//cout << "mmkp1 = " << mmkp1 << "  tminkp1 = " <<tminkp1 <<endl;
			//cout << endl;
			//cout << endl;
			//cout << "Ecas = " << Ecas <<endl;
			//cout << endl;
			//cout << "checking X " << unitX_jackson.Angle(unitX_jackson) << "  " << unitX_jackson.Mag() << " " << unitX_jackson.Angle(unitY_jackson) <<endl;
			cout << " check the coordinate system" <<endl;
			cout << " lab vs jackson coordinates: " << cos(unitX_jackson.Angle(unitX_lab)) << " " <<  cos(unitY_jackson.Angle(unitY_lab)) << " " <<  cos(unitZ_jackson.Angle(unitZ_lab)) << endl;
			cout << " jackson coordinates:  " << cos(unitX_jackson.Angle(unitY_jackson)) << " " <<  cos(unitX_jackson.Angle(unitZ_jackson)) << " " <<  cos(unitY_jackson.Angle(unitZ_jackson)) << endl;
			cout << " lab coordinates:  " << cos(unitX_lab.Angle(unitY_lab)) << " " <<  cos(unitX_lab.Angle(unitZ_lab)) << " " <<  cos(unitY_lab.Angle(unitZ_lab)) << endl;
			cout << " magnitudes:  " << unitX_lab.Mag() << unitY_lab.Mag() << unitZ_lab.Mag() << unitX_jackson.Mag() << unitY_jackson.Mag() << unitZ_lab.Mag() <<endl;
			cout << " " <<endl;
			cout << " angle between Xi and kpkp in cm: " << cos(tcas_cm.Angle(tkpkp_cm)) <<endl;
			cout  << " angle between Xi and -Xi in cm: " << cos(tcas_cm.Angle(-tcas_cm)) <<endl;
			cout << " angle between Xi and kpkp in lab: " << cos(fcas.Vect().Angle(fkpkp.Vect())) <<endl;
			cout << " angle between Xi and kpkp in lab: " << cos(tkpkp_lab.Angle(tcas_lab))<<endl;
		}
		//fill the tree with the branches for each event
		tree->Fill();
	}
	
	//close the data file
	myfile.close();
	//write the new tree
	newf->Write();
	//finish
	return 1;
}




bool ReadAnEvent(ifstream & myfile, EventStruct & AnEvent)
{

	// reading of an event will happen here
	float tempF;
	int tempI;
	bool result = false;

	if (myfile >> tempI
	>> tempI >> tempI >> tempF >> tempF >> AnEvent.Beam >> tempF
	>> tempI >> tempI >> AnEvent.pim1[0] >> AnEvent.pim1[1] >> AnEvent.pim1[2] >> AnEvent.pim1[3] 
	>> tempI >> tempI >> AnEvent.pro[0] >> AnEvent.pro[1] >> AnEvent.pro[2] >> AnEvent.pro[3] 
	>> tempI >> tempI >> AnEvent.pim2[0] >> AnEvent.pim2[1] >> AnEvent.pim2[2] >> AnEvent.pim2[3] 
	>> tempI >> tempI >> AnEvent.kp2[0] >> AnEvent.kp2[1] >> AnEvent.kp2[2] >> AnEvent.kp2[3] 
	>> tempI >> tempI >> AnEvent.kp1[0] >> AnEvent.kp1[1] >> AnEvent.kp1[2] >> AnEvent.kp1[3]) 
	{

 		result = true;
	}
	return result;

}