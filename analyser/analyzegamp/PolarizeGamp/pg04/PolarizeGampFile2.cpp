/*
Author: Jason Bono
Date: March 8 2014 (pg03)
Purpose: To change the angular distributions of the pion across any gotfried-jackson axis as to simulate having come from a polarized Xi

Usage: PolarizeGampFile2 file.gamp x     (polarizses only x axis)
or,    PolarizeGampFile2 file.gamp y
or     PolarizeGampFile2 file.gamp z
or     PolarizeGampFile2 file.gamp x y    (polarizes x and y axis)
or     PolarizeGampFile2 file.gamp x y z  (polarizes all three axes)





Notes:
 PolarizeGampFile2.cpp is the same PolarizeGampFile.cpp exept that it doesnt further reduce the file by the factor of 10
well it was, now PolarizeGampFile is out of date.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string>
#include <stdio.h>


#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

//#include "/u/home/jbono/macros/mytmin.C"
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
	float SomeFloat[3];
	int SomeInt[13];
};

//function prototype
bool ReadAnEvent(ifstream &, EventStruct &);
void WriteAnEvent(ofstream &, EventStruct &);

int main(int argc, char *argv[]) //use argc & argv to pass the file names through the commandline
{	
	
	// exit if x y or z are not specified.
	if (argc < 3) 
	{
		cout << "You must specify which axis to polarize! Exiting:"<<endl;
		exit(1); 
	}

	

	std::string infile(argv[1]); // input file name will be first input argument
	std::string PosPrefix("PosPol"); //going to add "PosPolarized" as a prefix (need to learn how to chop off the file extention)
	std::string NegPrefix("NegPol"); 	 
	std::string posoutfile = PosPrefix + infile;
	std::string negoutfile = NegPrefix + infile;


	int polX = 0;
	int polY = 0;
	int polZ = 0;
	//read in the arguments and switch the approprate polarization axes
	for(int n=0; n < argc; n++ )
	{	
		std::string temps = argv[n];
		if (temps == "x")
		{
			polX = 1;
		}
		if (temps == "y")
		{
			polY = 1;
		}
		if (temps == "z")
		{
			polZ = 1;
		}
	}
	
	//Input and output files
	ifstream MyInFile;
	MyInFile.open(infile.c_str());    // opening requires a const char* which is the function of c_str()
	ofstream MyPosOutFile,MyNegOutFile;
	MyPosOutFile.open(posoutfile.c_str());
	MyNegOutFile.open(negoutfile.c_str());

	//create 4 independent Trandom3 object 
	TRandom3 rx(0);//specifying 0 means a unique seed will be automatically generated using TUUID
	TRandom3 ry(0);
	TRandom3 rz(0);	
	TRandom3 rReduction(0);  //for uniformly reducing the output 
	
	
	//setup for the polarizaiton
	const Float_t Pol = 0.5;
	const Float_t PosPol = sqrt(Pol*Pol);
	const Float_t NegPol = -PosPol;
	const Float_t alpha = -0.458;
	const Float_t B = (1/(1-alpha*PosPol));
	
	
	//four vectors of the interesting particles
	TLorentzVector fbeam,ftarget,fkp1,fkp2,fpim1; //by default initized to zero
	TLorentzVector fkpkp;
	TLorentzVector fcas;
	TLorentzVector fcm;
	
	//boost
	TVector3 Bcas;
	TVector3 Bcm; 

	//three momenta
	TVector3 tbeam_lab;
	TVector3 tkpkp_lab;
	TVector3 tcas_lab;
	TVector3 tbeam_xi, tkpkp_xi, tpi_xi;
	TVector3 tbeam_cm, tkpkp_cm, tpi_cm;
	
	
	//coordinate system
	TVector3 unitZ_lab;
  	TVector3 unitY_lab;
  	TVector3 unitX_lab;
	TVector3 unitZ_cm;
  	TVector3 unitY_cm;
  	TVector3 unitX_cm;

	
	
	
	// setup struct
	EventStruct AnEvent;
	
	//the angles
	Float_t COS_pi_x = 0,COS_pi_y = 0,COS_pi_z = 0;		


	// parts of the struct. Some varaibles are superfulous but included anyway.
	Float_t beam;
	Float_t kp1x,kp1y,kp1z,kp1t;
	Float_t pim1x,pim1y,pim1z,pim1t;
	Float_t prox,proy,proz,prot;
	Float_t pim2x,pim2y,pim2z,pim2t;	
	Float_t kp2x,kp2y,kp2z,kp2t;
	
	while (ReadAnEvent(MyInFile, AnEvent)) 
	{	
		//the struct
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
				
		//fill the basic TLorentz vectors
		fbeam.SetPxPyPzE(0,0,beam,beam);
		ftarget.SetXYZM(0,0,0,0.93827);
		fkp1.SetPxPyPzE(kp1x,kp1y,kp1z,kp1t);
		fpim1.SetPxPyPzE(pim1x,pim1y,pim1z,pim1t);
		fkp2.SetPxPyPzE(kp2x,kp2y,kp2z,kp2t);
		fkpkp = fkp1 + fkp2;
		fcas = fbeam + ftarget - fkpkp;
		fcm = fbeam + ftarget;
		
		//fill lab three vectors
		tbeam_lab.SetXYZ(fbeam(0), fbeam(1), fbeam(2));
		tkpkp_lab.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
		tcas_lab.SetXYZ(fcas(0), fcas(1), fcas(2));
		
		//define lab coordinate system
		unitZ_lab = tbeam_lab.Unit(); 
		unitY_lab = tbeam_lab.Cross(tcas_lab).Unit();
		unitX_lab = unitZ_lab.Cross(unitY_lab).Unit();	
	
		//boost to cm frame
		Bcm = -fcm.BoostVector();
	    fbeam.Boost(Bcm);
		fkpkp.Boost(Bcm);
		fpim1.Boost(Bcm);
		fcas.Boost(Bcm);
	  		tbeam_cm.SetXYZ(fbeam(0), fbeam(1), fbeam(2));
	  		tkpkp_cm.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
	  		tpi_cm.SetXYZ(fpim1(0), fpim1(1), fpim1(2));
			//boost to xi frame
			Bcas = -fcas.BoostVector();
		    fbeam.Boost(Bcas);
			fkpkp.Boost(Bcas);
			fpim1.Boost(Bcas);
		  		tbeam_xi.SetXYZ(fbeam(0), fbeam(1), fbeam(2));
		  		tkpkp_xi.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
		  		tpi_xi.SetXYZ(fpim1(0), fpim1(1), fpim1(2));
		  	fbeam.Boost(-Bcas);
			fkpkp.Boost(-Bcas);
			fpim1.Boost(-Bcas);
		fbeam.Boost(-Bcm);
		fkpkp.Boost(-Bcm);
		fpim1.Boost(-Bcm);
		fcas.Boost(-Bcm);
		
		
	
	

	
		//define cooridinate system in gottfried-jackson frame
	  	TVector3 unitZ_cm;
	  	TVector3 unitY_cm;
	  	TVector3 unitX_cm;
	  	unitZ_cm = (tbeam_cm).Unit();  //beam
	  	unitY_cm = tbeam_cm.Cross(tkpkp_cm).Unit(); //beam.x.kpkp
	  	unitX_cm = unitZ_cm.Cross(unitY_cm).Unit(); //Z.x.Y

		//pion angles in jackson frame
		COS_pi_x = cos(unitX_cm.Angle(tpi_xi)); 
		COS_pi_y = cos(unitY_cm.Angle(tpi_xi));
		COS_pi_z = cos(unitZ_cm.Angle(tpi_xi));
		
	
		//the selection critera		
		double RandomNumberx = rx.Rndm();
		double RandomNumbery = ry.Rndm();
		double RandomNumberz = rz.Rndm();
		double RandomNumberReduction = rReduction.Rndm(); 
		double ProbSuccessPosX = B + B*alpha*PosPol*COS_pi_x;
		double ProbSuccessPosY = B + B*alpha*PosPol*COS_pi_y; 
		double ProbSuccessPosZ = B + B*alpha*PosPol*COS_pi_z;
		double ProbSuccessNegX = B + B*alpha*NegPol*COS_pi_x;
		double ProbSuccessNegY = B + B*alpha*NegPol*COS_pi_y;
		double ProbSuccessNegZ = B + B*alpha*NegPol*COS_pi_z;
		
	
		if (  ((polX == 0)||(ProbSuccessPosX > RandomNumberx)) && ((polY == 0)||(ProbSuccessPosY > RandomNumbery)) && ((polZ == 0)||(ProbSuccessPosZ > RandomNumberz))  )
		{ 
			WriteAnEvent(MyPosOutFile, AnEvent);
		}
	
		if (  ((polX == 0)||(ProbSuccessNegX > RandomNumberx)) && ((polY == 0)||(ProbSuccessNegY > RandomNumbery)) && ((polZ == 0)||(ProbSuccessNegZ > RandomNumberz))  )
		{ 
			WriteAnEvent(MyNegOutFile, AnEvent);
		}	
	}
	
	//close the data files
	MyInFile.close();
	MyPosOutFile.close();
	MyNegOutFile.close();

	return 1;
}




bool ReadAnEvent(ifstream & MyInFile, EventStruct & AnEvent)
{
	bool result = false;

	if (MyInFile >> AnEvent.SomeInt[0] 
	>> AnEvent.SomeInt[1] >> AnEvent.SomeInt[2] >> AnEvent.SomeFloat[0] >> AnEvent.SomeFloat[1] >> AnEvent.Beam >> AnEvent.SomeFloat[2]
	>> AnEvent.SomeInt[3] >> AnEvent.SomeInt[4] >> AnEvent.pim1[0] >> AnEvent.pim1[1] >> AnEvent.pim1[2] >> AnEvent.pim1[3] 
	>> AnEvent.SomeInt[5] >> AnEvent.SomeInt[6] >> AnEvent.pro[0] >> AnEvent.pro[1] >> AnEvent.pro[2] >> AnEvent.pro[3] 
	>> AnEvent.SomeInt[7] >> AnEvent.SomeInt[8] >> AnEvent.pim2[0] >> AnEvent.pim2[1] >> AnEvent.pim2[2] >> AnEvent.pim2[3] 
	>> AnEvent.SomeInt[9] >> AnEvent.SomeInt[10] >> AnEvent.kp2[0] >> AnEvent.kp2[1] >> AnEvent.kp2[2] >> AnEvent.kp2[3] 
	>> AnEvent.SomeInt[11] >> AnEvent.SomeInt[12] >> AnEvent.kp1[0] >> AnEvent.kp1[1] >> AnEvent.kp1[2] >> AnEvent.kp1[3]) 
	{
 		result = true;
	}

	return result;
}



void WriteAnEvent(ofstream & MyOutFile, EventStruct & AnEvent)
{
	MyOutFile <<" "<< AnEvent.SomeInt[0] <<"\n"
	<< AnEvent.SomeInt[1] <<" "<< AnEvent.SomeInt[2] <<" "<< AnEvent.SomeFloat[0] <<" "<< AnEvent.SomeFloat[1] <<" "<< AnEvent.Beam <<" "<< AnEvent.SomeFloat[2] <<"\n"
	<< AnEvent.SomeInt[3] <<" "<< AnEvent.SomeInt[4] <<" "<< AnEvent.pim1[0] <<" "<< AnEvent.pim1[1] <<" "<< AnEvent.pim1[2] <<" "<< AnEvent.pim1[3] <<"\n"
	<< AnEvent.SomeInt[5] <<" "<< AnEvent.SomeInt[6] <<" "<< AnEvent.pro[0] <<" "<< AnEvent.pro[1] <<" "<< AnEvent.pro[2] <<" "<< AnEvent.pro[3] <<"\n" 
	<< AnEvent.SomeInt[7] <<" "<< AnEvent.SomeInt[8] <<" "<< AnEvent.pim2[0] <<" "<< AnEvent.pim2[1] <<" "<< AnEvent.pim2[2] <<" "<< AnEvent.pim2[3] <<"\n" 
	<< AnEvent.SomeInt[9] <<" "<< AnEvent.SomeInt[10] <<" "<< AnEvent.kp2[0] <<" "<< AnEvent.kp2[1] <<" "<< AnEvent.kp2[2] <<" "<< AnEvent.kp2[3] <<"\n"
	<< AnEvent.SomeInt[11] <<" "<< AnEvent.SomeInt[12] <<" "<< AnEvent.kp1[0] <<" "<< AnEvent.kp1[1] <<" "<< AnEvent.kp1[2] <<" "<< AnEvent.kp1[3] <<"\n";
	
	return;
}






///using the old less complete struct that erased certain paremeters of the event is below

/*
bool ReadAnEvent(ifstream & MyInFile, EventStruct & AnEvent)
{

	// reading of an event will happen here
	float tempF;
	int tempI;
	bool result = false;

	if (MyInFile >> tempI 
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



void WriteAnEvent(ofstream & MyOutFile, EventStruct & AnEvent)
{

	float tempF = 0;  //note that the new file has lost information wherever a temp variable is writen. theese are not important variables however ie pid number
	int tempI = 0;

	MyOutFile <<" "<< tempI <<"\n"
	<< tempI <<" "<< tempI <<" "<< tempF <<" "<< tempF <<" "<< AnEvent.Beam <<" "<< tempF <<"\n"
	<< tempI <<" "<< tempI <<" "<< AnEvent.pim1[0] <<" "<< AnEvent.pim1[1] <<" "<< AnEvent.pim1[2] <<" "<< AnEvent.pim1[3] <<"\n"
	<< tempI <<" "<< tempI <<" "<< AnEvent.pro[0] <<" "<< AnEvent.pro[1] <<" "<< AnEvent.pro[2] <<" "<< AnEvent.pro[3] <<"\n" 
	<< tempI <<" "<< tempI <<" "<< AnEvent.pim2[0] <<" "<< AnEvent.pim2[1] <<" "<< AnEvent.pim2[2] <<" "<< AnEvent.pim2[3] <<"\n" 
	<< tempI <<" "<< tempI <<" "<< AnEvent.kp2[0] <<" "<< AnEvent.kp2[1] <<" "<< AnEvent.kp2[2] <<" "<< AnEvent.kp2[3] <<"\n"
	<< tempI <<" "<< tempI <<" "<< AnEvent.kp1[0] <<" "<< AnEvent.kp1[1] <<" "<< AnEvent.kp1[2] <<" "<< AnEvent.kp1[3] <<"\n";
	
	return;
}



*/


