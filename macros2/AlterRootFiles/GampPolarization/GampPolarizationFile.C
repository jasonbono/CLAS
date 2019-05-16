/* 
Author: Jason Bono

Date: May 15 2013

Purpose: To take an existing gamp file with zero polarization and create a new file with polarzation.


*/


#include "TMath.h"


void GampPolarizationFile()
{


	const Float_t Pol = 0.0;
	const Float_t PosPol = sqrt(Pol*Pol);
	const Float_t NegPol = -PosPol;
	const Float_t alpha = -0.458;

	const Float_t B = (1/(1-alpha*PosPol));
	const Float_t Bp = B*B*B;
	const Float_t Model = B - B*alpha*PosPol;
	const Float_t HighestProb = Model;
	//==========================================EDIT HERE========================================

	/* //<--------------- FOR SIMULATION ON FARM
	TFile *file = TFile::Open("/w/hallb/clasg12/jbono/sim/DATA/hadded/Reduced/MC_i4_gamp.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree");
	TFile *fileNew = new TFile("/w/hallb/clasg12/jbono/sim/DATA/hadded/Reduced/MC_i4_gamp_100.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewNamePos = "GampTree_100";
	//*/	
	
	/* //<--------------- FOR SIMULATION ON LOCAL
	TFile *file = TFile::Open("~/clas/rootfiles/LINKS/sim/MC_i2_gamp.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree");
	TFile *fileNew = new TFile("~/clas/rootfiles/g12/mc/reduced/MC_i2_gamp_100.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewNamePos = "GampTree_100";
	//*/	
	
	
	/* //<--------------- FOR TEST ON LOCAL
	TFile *file = TFile::Open("~/clas/rootfiles/LINKS/MC_i3_gamp_100.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree_100");
	TFile *fileNew = new TFile("./PolarizedGamp.root","RECREATE");
	TTree *tNewPos = tOriginal->CloneTree(0);
	TString tNewNamePos = "PosPolarized_Gamp";
	TTree *tNewNeg = tOriginal->CloneTree(0);
	TString tNewNameNeg = "NegPolarized_Gamp";
	//*/
	
	

	
	//===========================================================================================


	//varibles to use in the filter
	Float_t COS_pi_x, COS_pi_y, COS_pi_z;
	tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);		

	//create a Trandom3 object 
	TRandom3 rx(0);//specifying 0 means a unique seed will be automatically generated using TUUID
	TRandom3 ry(0);
	TRandom3 rz(0);  
	
	
	//loop over all entries
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i += 100 )
	{
		tOriginal->GetEntry(i);
		
		double RandomNumberx = rx.Rndm();
		double RandomNumbery = ry.Rndm();
		double RandomNumberz = rz.Rndm(); //RandomNumber is a double between 0 and 1 excluding 0
		//double B = 1/(1 - alpha*PosPol);//Pos since the absoulte value of Pol is needed

		
		double ProbSuccessPosX = B - B*alpha*PosPol*COS_pi_x;
		double ProbSuccessPosY = B - B*alpha*PosPol*COS_pi_y; 
		double ProbSuccessPosZ = B - B*alpha*PosPol*COS_pi_z;
		double ProbSuccessNegX = B - B*alpha*NegPol*COS_pi_x;
		double ProbSuccessNegY = B - B*alpha*NegPol*COS_pi_y;
		double ProbSuccessNegZ = B - B*alpha*NegPol*COS_pi_z;
		
		
	

		
		Float_t tempi = i;
		Float_t tempN = nentries;
		cout <<"nentires is " << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		cout << "PosPol = " <<PosPol<<"  abs(PosPol) = "<< sqrt(PosPol*PosPol)<< "   NegPol = " <<NegPol<<"  abs(NegPol) = "<< sqrt(NegPol*NegPol)<<endl;
		cout << "  ProbSuccessPosX = " << ProbSuccessPosX << "  ProbSuccessPosY = " << ProbSuccessPosY << "  ProbSuccessPosZ = " << ProbSuccessPosZ << endl;
		cout << "  ProbSuccessNegX = " << ProbSuccessNegX << "  ProbSuccessNegY = " << ProbSuccessNegY << "  ProbSuccessNegZ = " << ProbSuccessNegZ << endl;
		cout << "  RandomNumberx = " <<RandomNumberx<< "  RandomNumbery = " <<RandomNumbery<< "  RandomNumberz = " <<RandomNumberz<<endl;
		cout << " Bp = " <<Bp<< "   B = "<< B << "  HighestProb = " << HighestProb <<endl;
	



		if ((ProbSuccessPosX > RandomNumberx) && (ProbSuccessPosY > RandomNumbery) && (ProbSuccessPosZ > RandomNumberz) )
		{ 
			cout <<"Accepted: "<<endl;
			tNewPos->Fill();
			
		}
		else
		{
			cout <<"Rejected: "<<endl;
		}
		

		if ((ProbSuccessNegX > RandomNumberx) && (ProbSuccessNegY > RandomNumbery) && (ProbSuccessNegZ > RandomNumberz) )
		{ 
			cout <<"Accepted: "<<endl;
			tNewNeg->Fill();
			
		}
		else
		{
			cout <<"Rejected: "<<endl;
		}
		cout <<endl;
	
		
	}

	//fill the New tree
	cout <<"Filling the New trees" <<endl;
	tNewPos->Write(tNewNamePos);
	tNewNeg->Write(tNewNameNeg);


	float old = tOriginal->GetEntries();
	float pos = tNewPos->GetEntries();
	float neg = tNewNeg->GetEntries();
	//see how much the data was reduced
	cout << " # of entries in Original is " << old << endl;
	cout << " # of entries in NewPos is " << pos <<"  which is " << 100*pos/old <<"%" << endl;
	cout << " # of entries in NewNeg is " << neg <<"  which is " << 100*neg/old <<"%" << endl;
	cout << "  pos/neg = " <<pos/neg <<endl;
	float tothe = 1.0/3;
	cout << "test = " << pow(4,3) <<endl;
	


	//close the file
	fileNew->Close();
	
	gROOT->ProcessLine(".q");

}
