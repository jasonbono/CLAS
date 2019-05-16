/* 
Author: Jason Bono

Date: May 15 2013

Purpose: To take an existing gamp file with zero polarization and create a new file with polarzation.

Explanation of method:  See picture in iPad.

*/


#include "TMath.h"


void GampPol2()
{


	const Float_t PosPol = 0.5;
	const Float_t NegPol = -PosPol;
	const Float_t alpha = -0.458;

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
	
	
	//* //<--------------- FOR TEST ON LOCAL
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
	TRandom3 r(0);  //specifying 0 means a unique seed will be automatically generated using TUUID
	TRandom3 r2(0);
	
	//loop over all entries
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i += 10 )
	{
		tOriginal->GetEntry(i);
		
		double RandomNumber = r.Rndm(); //RandomNumber is a double between 0 and 1 excluding 0	
		double RandomNumber2 = r2.Rndm(); //another independent random number		
		double ProbSuccessPosX = 1 - 3*alpha*PosPol*COS_pi_x;
		double ProbSuccessPosY = 1 - 3*alpha*PosPol*COS_pi_y;
		double ProbSuccessPosZ = 1 - 3*alpha*PosPol*COS_pi_z;
		double ProbSuccessNegX = 1 - 3*alpha*NegPol*COS_pi_x;
		double ProbSuccessNegY = 1 - 3*alpha*NegPol*COS_pi_y;
		double ProbSuccessNegZ = 1 - 3*alpha*NegPol*COS_pi_z;
	
		Float_t tempi = i;
		Float_t tempN = nentries;
		cout <<"nentires is " << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		cout << "PosPol = " <<PosPol<< "  RandomNumber = " <<RandomNumber<<endl;
		cout << "  ProbSuccessPosX = " << ProbSuccessPosX <<"  ProbSuccessPosY = " << ProbSuccessPosY <<"  ProbSuccessPosZ = " << ProbSuccessPosZ << endl;
		cout << "  ProbSuccessNegX = " << ProbSuccessNegX <<"  ProbSuccessNegY = " << ProbSuccessNegY <<"  ProbSuccessNegZ = " << ProbSuccessNegZ << endl;
		
	
		

		//Pos X
		if (ProbSuccessPosX > 1)
		{ 
			tNewPos->Fill();
			if ( ( ProbSuccessPosX - 1) > RandomNumber){tNewPos->Fill();}
		}
		else if (ProbSuccessPosX > RandomNumber){tNewPos->Fill();}
		
		//Pos Y
		if (ProbSuccessPosY > 1)
		{ 
			tNewPos->Fill();
			if ( ( ProbSuccessPosY - 1) > RandomNumber){tNewPos->Fill();}
		}
		else if (ProbSuccessPosY > RandomNumber){tNewPos->Fill();}
		
		//Pos Z
		if (ProbSuccessPosZ > 1)
		{ 
			tNewPos->Fill();
			if ( ( ProbSuccessPosZ - 1) > RandomNumber){tNewPos->Fill();}
		}
		else if (ProbSuccessPosZ > RandomNumber){tNewPos->Fill();}	
			
			


		//Neg X
		if (ProbSuccessNegX > 1)
		{ 
			tNewNeg->Fill();
			if ( ( ProbSuccessNegX - 1) > RandomNumber){tNewNeg->Fill();}
		}
		else if (ProbSuccessNegX > RandomNumber){tNewNeg->Fill();}


		//Neg Y
		if (ProbSuccessNegY > 1)
		{ 
			tNewNeg->Fill();
			if ( ( ProbSuccessNegY - 1) > RandomNumber){tNewNeg->Fill();}
		}
		else if (ProbSuccessNegY > RandomNumber){tNewNeg->Fill();}

		//Neg Z
		if (ProbSuccessNegZ > 1)
		{ 
			tNewNeg->Fill();
			if ( ( ProbSuccessNegZ - 1) > RandomNumber){tNewNeg->Fill();}
		}
		else if (ProbSuccessNegZ > RandomNumber){tNewNeg->Fill();}




		


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

	


	//close the file
	fileNew->Close();
	
	gROOT->ProcessLine(".q");

}
