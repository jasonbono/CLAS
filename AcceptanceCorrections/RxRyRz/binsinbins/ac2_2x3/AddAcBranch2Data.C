/*
Name: AddAcBranch2Data.C
Author: Jason Bono
Date: April 12 2013
Purpose: Third step in  of the acceptance corrected pion distributions. This Writes R factors (acceptances) to a data file.

Input:  *originalrootfile*.root,  *RxRyRz*.txt, *CovMatrixfile*.txt
Output: *NewRootFileWithACAsABranch*.root

*/


//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "./SimEXiBins.h"
#include "./constants.h"

#include <Riostream.h>
#include <TMath.h>
#include "TMath.h"
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
#include <cmath>

gSystem.Load("libPhysics.so");

void AddAcBranch2Data()
{	
	//interactively choose Data or Simulation
	cout << "enter the type of file you would like to apply acceptance corrections to (Data , NoPol, PosPol or NegPol):";
	const string choice;
	cin >> choice;
	//second question
	cout << "enter where you would like to have had the acceptance derived from ( NoPol, PosPol or NegPol):";
	const string choiceAC;
	cin >> choiceAC;
	cout << "Fiducial cuts? (type yes or no):";
	const string fidchoice;
	cin >> fidchoice;
	if (fidchoice == "yes")
	{
		const string fid = "-Fid";
	}
	else if (fidchoice == "no")
	{
		const string fid = "";
	}
	else
	{
		cout << "fidchoice bad"<<endl;
		exit(1);
	}
	cout <<Form("The acceptance from the %s%s will be used",choice.c_str(),fid.c_str()) <<endl;
	if (choice.compare("Data") == 0)
	{
	  	cout <<"The data will be evaluated using Ac" <<  choiceAC.c_str() << endl;	
		TFile *file = TFile::Open(Form("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass%s.root",fid.c_str()));
		TTree *tOriginal = (TTree*)file->Get("v05");
		TFile *fileNew = new TFile(Form("./NewRootFiles/%s-Basic-Mass-Ac%s-%i_%i_%ibins%s.root",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,fid.c_str()),"RECREATE");
		TTree *tNew = tOriginal->CloneTree(0);
		TString tNewName = "New";
	}
	else
	{
		cout <<"The simulation will be evaluated using Ac"<<choiceAC.c_str() <<endl;
		TFile* file = new TFile(Form("~/clas/rootfiles/LINKS/MC-i9t4-t5-%s-2kppim_Basic_Mass%s.root",choice.c_str(),fid.c_str()));  
		TTree *tOriginal = (TTree*)file->Get("gpp2kppim");
		TFile *fileNew = new TFile(Form("./NewRootFiles/%s-Basic-Mass-Ac%s-%i_%i_%ibins%s.root",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,fid.c_str()),"RECREATE");
		TTree *tNew = tOriginal->CloneTree(0);
		TString tNewName = "New";	
	}
	//old branches
	float beam=0, Xcmtheta=0;
	float COS_pi_x, COS_pi_y, COS_pi_z;
	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("Xcmtheta", &Xcmtheta);
	tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);
	cout<<"test1"<<endl;
	
	//New, unified branches: 
	float RUni[Nd];
	float eRUni[Nd];
	const char* RUniString[Nd];
	const char* eRUniString[Nd];
	const char* RUniString[Nd];
	const char* eRUniString[Nd];
	RUniString[0] = "Rx", RUniString[1] = "Ry", RUniString[2] = "Rz";
	eRUniString[0] = "eRx", eRUniString[1] = "eRy", eRUniString[2] = "eRz";

	TBranch* RUniBranch[Nd];
	TBranch* eRUniBranch[Nd];
	cout<<"test2"<<endl;
	for (int d = 0; d < Nd; d++)
	{
		RUniBranch[d] = tNew->Branch(Form("%s",RUniString[d]), &RUni[d], Form("%s/F",RUniString[d]));
		eRUniBranch[d] = tNew->Branch(Form("%s",eRUniString[d]), &eRUni[d], Form("%s/F",eRUniString[d]));
	}
	//-------------------------read in the acceptance correction parameters and error matrix observables------------------------------
	ifstream myParFile(Form("./txt/RxRyRz-%s-%i_%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nbq,Ncq,fid.c_str()));
	ifstream myCovMatrixFile(Form("./txt/CovMatrixfile-%s-%i_%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nbq,Ncq,fid.c_str()));
	if( !myParFile || !myCovMatrixFile) 
	{
		cout << "Cannot open one of the text files. \n";
		cout << Form("./txt/RxRyRz-%s-%i_%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nbq,Ncq,fit.c_str()) <<endl;
		cout << Form("./txt/CovMatrixfile-%s-%i_%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nbq,Ncq,fid.c_str())<<endl;
		gROOT->ProcessLine(".q");
	}
	float P[Nbq][Ncq][Nd][Ne] = {0};  //fit parameters
	float eP[Nbq][Ncq][Nd][Ne] = {0};
	float covMatrix[Nbq][Ncq][Nd][Ne][Ne] = {0};  //array of NeXNe matrixes representing the error in the fitting
		
	for (int bq = 0; bq < Nbq; bq++)
	{
		for (int cq = 0; cq < Ncq; cq++)
		{
			for (int d = 0; d < Nd; d++)
			{
				cout << "--------- bq = "<<bq<<", cq = "<<cq<<", d = "<<d<<" ------------"<<endl;
				for (int e = 0; e < Ne; e++)
				{
					cout << "  -- e = " << e <<"  --" << endl;
					myParFile >> P[bq][cq][d][e] >> eP[bq][cq][d][e]; //the error is not actualy used
					cout << "   P = " << P[bq][cq][d][e] << "  eP = " << eP[bq][cq][d][e] <<endl;
					for (int j = 0; j < Ne; j++)
					{
						myCovMatrixFile >> covMatrix[bq][cq][d][e][j];
						cout <<"   " << covMatrix[bq][cq][d][e][j];				
					}
					cout <<endl<<endl;
				}
			}
		}
	}
		
	//check for correspondence with the ascii file.
	for (int bq = 0; bq < Nbq; bq++)
	{
		for (int cq = 0; cq < Ncq; cq++)
		{
			for (int d = 0; d < Nd; d++)
			{
				for (int e = 0; e < Ne; e++)
				{
					cout << P[bq][cq][d][e] << "  " << eP[bq][cq][d][e] <<endl;
				}
			}
		}
	}		
	myParFile.close();	
	myCovMatrixFile.close();	
	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	float R[Nbq][Ncq][Nd] = {0}; //acceptance factor
	float eR[Nbq][Ncq][Nd] = {0};
	float Z[Nd] = {0};	//pion angle
	float testcounter = 0;
	int nentries = (int)tOriginal->GetEntries(); 
	for (int i=0; i<nentries; i++) 
	{
		//cout << "!!!!!!!STARTING EVENT " << " " << i << "  !!!!!!!!!!!" <<endl;
		tOriginal->GetEntry(i);
	
		Z[0] = COS_pi_x, Z[1] = COS_pi_y, Z[2] = COS_pi_z;		
		//cout << "beam = " << beam << "  Xcmtheta = " << Xcmtheta <<endl;
		//cout << "COS_pi_x = " << COS_pi_x << "  COS_pi_y = " << COS_pi_y << "  COS_pi_z = " << COS_pi_z << endl;	
		//fill the seperate branches
		//cout << endl;
		//cout  << "Seperate Branches" <<endl;
		for (int bq = 0; bq < Nbq; bq++)
		{
			for (int cq = 0; cq < Ncq; cq++)
			{
				for (int d = 0; d < Nd; d++)
				{
					R[bq][cq][d] = 0;
					eR[bq][cq][d] = 0;
					
					//calculate the acceptance and the error in the acceptance
					for (int e = 0; e < Ne; e++)
					{
						R[bq][cq][d] += P[bq][cq][d][e]*pow(Z[d],e); 
						for (int j = 0; j < Ne; j++)
						{
							eR[bq][cq][d] += covMatrix[bq][cq][d][e][j]*pow(Z[d],e)*pow(Z[d],j); //this equals the error squared
						}
					}
					eR[bq][cq][d] = eR[bq][cq][d]*eR[bq][cq][d]; //square to get a positve number
					eR[bq][cq][d] =  sqrt(sqrt(eR[bq][cq][d])); // finaly get the error. 
					//}
					//cout << "- - - -  bq = "<<bq<<", cq = "<<cq<<", d = "<<d<<" - - - - "<<endl;
					//cout << "  P[bq][c][d][0] = " << P[bq][c][d][0] << "  P[bq][c][d][1] = "<<P[bq][c][d][1]<<"  P[bq][c][d][2] = "<<P[bq][c][d][2]<<"  P[bq][c][d][3] = "<<P[bq][c][d][3]<<"  P[bq][c][d][4] = "<<P[bq][c][d][4]<<endl;
					//cout << "Z[d] = " << Z[d] << endl; 
					//cout << "R = " << R[bq][c][d] << "  eR = " << eR[bq][c][d] <<endl;

					testcounter = testcounter + 1;
					//cout << "testcounter = " << testcounter <<  " so passing through cut " << testcounter/(i+1.0) << " times per event " << endl;			
				}
			}
		}	
		//set up the boolian criteron for sorting out the exi bins
		bool ebin[Nbq],xbin[Nbq][Ncq];
		bool exbin[Nbq][Ncq];
		for (int bq=0;bq<Nbq;bq++)
		{	
			ebin[bq] = beam >= eVal[bq] && beam <= eVal[bq+1];
			for (int cq=0;cq<Ncq;cq++)
			{
				xbin[bq][cq] = Xcmtheta >=  xVal[bq][cq] && Xcmtheta <= xVal[bq][cq+1];
				exbin[bq][cq] = ebin[bq]&&xbin[bq][cq];
			}
		}	
		//fill the unified branches with
		int pass = 0;
		for (int bq = 0; bq < Nbq; bq++) 
		{
			for (int cq = 0; cq < Ncq; cq++) 
			{
				if (exbin[bq][cq])
				{
					pass += 1;
					for (int d = 0; d < Nd; d++)  //fill x y z
					{
						RUni[d] = R[bq][cq][d];
						eRUni[d] = eR[bq][cq][d];
					}	
				}
			}
		}		
		if (pass != 1)
		{	
			//if falls outside maximum Xi bin than move on, this event will be excluded in the CorrectPion macro
			if (Xcmtheta > 0.8)
			{
				for (int d = 0; d < Nd; d++)  //fill x y z
				{
					RUni[d] = 0;
					eRUni[d] = 0;
					cout <<"EXCLUDING EVENT: event has xi angle outside of set range"<<endl;
				}
			}
			//otherwise quit
			else
			{
				cout <<" EVENT SEEMS TO HAVE ENERGY AND/OR XI ANGLE OUTSIDE OF PERMISIBLE RANGE" <<endl;
				cout << "bq, d = " << bq <<", "<<d<<endl;
				cout << "beam = " <<beam <<endl;
				cout << "Xcmtheta = " << Xcmtheta <<endl;
				cout << "pass = " <<pass<<endl;
				gROOT->ProcessLine(".q");
			}
		}
		int printnumber = 10;
		float tempf = nentries/printnumber;
		int tempi = tempf;
		
		if (i % tempi==100)
		{
			cout << " - - - - - -" << i << " - - - - - - -" <<endl;
			cout << "beam = " << beam << "  Xcmtheta = " << Xcmtheta <<endl;
			cout << "COS_pi_x = " << COS_pi_x << "  COS_pi_y = " << COS_pi_y << "  COS_pi_z = " << COS_pi_z << endl;
			cout << "Rx = " << RUni[0] << "  Ry = " << RUni[1] << "  Rz = " << RUni[2] <<endl;
			cout <<endl;
		}		
		//Fill the tree with that event			
		tNew->Fill();	
		//cout << endl;
	}
	// Write the new tree to the new file and quit
	tNew->Write(tNewName);
	 gROOT->ProcessLine(".q");
}