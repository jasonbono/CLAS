
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
	
	

	std::string infile(argv[1]); // input file name will be first input argument
	std::string PosPrefix("PosPol"); //going to add "PosPolarized" as a prefix (need to learn how to chop off the file extention)
	std::string NegPrefix("NegPol"); 	 
	std::string posoutfile = PosPrefix + infile;
	std::string negoutfile = NegPrefix + infile;
	

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
	
	//boost
	TVector3 Bcas; 

	//three momenta
	TVector3 tbeam_lab;
	TVector3 tkpkp_lab;
	TVector3 tcas_lab;
	TVector3 tbeam_jackson, tkpkp_jackson, tpi_jackson;
	
	//coordinate system
	TVector3 unitZ_lab;
  	TVector3 unitY_lab;
  	TVector3 unitX_lab;

	
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
		
		//fill lab three vectors
		tbeam_lab.SetXYZ(fbeam(0), fbeam(1), fbeam(2));
		tkpkp_lab.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
		tcas_lab.SetXYZ(fcas(0), fcas(1), fcas(2));
		
		//define lab coordinate system
		unitZ_lab = tbeam_lab.Unit(); 
		unitY_lab = tbeam_lab.Cross(tcas_lab).Unit();
		unitX_lab = unitZ_lab.Cross(unitY_lab).Unit();	
	
		//boost beam, kpkp, pion to jackson frame and fill boosted fourvector momentum into three vectors. then boost back
		Bcas = -fcas.BoostVector();
	    fbeam.Boost(Bcas);
		fkpkp.Boost(Bcas);
		fpim1.Boost(Bcas);
	  	tbeam_jackson.SetXYZ(fbeam(0), fbeam(1), fbeam(2));
	  	tkpkp_jackson.SetXYZ(fkpkp(0), fkpkp(1), fkpkp(2));
	  	tpi_jackson.SetXYZ(fpim1(0), fpim1(1), fpim1(2));
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
		
	
		//the selection critera		
		double RandomNumberx = rx.Rndm();
		double RandomNumbery = ry.Rndm();
		double RandomNumberz = rz.Rndm();
		double RandomNumberReduction = rReduction.Rndm(); 
		double ProbSuccessPosX = B - B*alpha*PosPol*COS_pi_x;
		double ProbSuccessPosY = B - B*alpha*PosPol*COS_pi_y; 
		double ProbSuccessPosZ = B - B*alpha*PosPol*COS_pi_z;
		double ProbSuccessNegX = B - B*alpha*NegPol*COS_pi_x;
		double ProbSuccessNegY = B - B*alpha*NegPol*COS_pi_y;
		double ProbSuccessNegZ = B - B*alpha*NegPol*COS_pi_z;
		
		if(RandomNumberReduction < 0.1 ) //reduce output off the bat by 90% 
		{
			if ((ProbSuccessPosX > RandomNumberx) && (ProbSuccessPosY > RandomNumbery) && (ProbSuccessPosZ > RandomNumberz) )
			{ 
				WriteAnEvent(MyPosOutFile, AnEvent);
			}
	
			if ((ProbSuccessNegX > RandomNumberx) && (ProbSuccessNegY > RandomNumbery) && (ProbSuccessNegZ > RandomNumberz) )
			{ 
				WriteAnEvent(MyNegOutFile, AnEvent);
			}
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


