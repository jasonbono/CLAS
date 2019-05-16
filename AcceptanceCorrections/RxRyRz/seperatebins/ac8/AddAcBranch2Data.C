/*
Name: AddAcBranch2Data.C
Author: Jason Bono
Date: April 12 2013
Purpose: Third step in  of the acceptance corrected pion distributions. This Writes R factors (acceptances) to a data file.

Input:  *originalrootfile*.root,  *RxRyRz*.txt, *CovMatrixfile*.txt
Output: *NewRootFileWithACAsABranch*.root
test

*/


//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "./SimEXiBins.h"


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
	//Some important declarations 
	const int Nb = 2,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
	const int Ne=10; //number of paremters for polynomial
	int Nk = 60; //# of pion bins used to get the acceptance parameters
//	const int Nq = 20; //number of energy and Xi bins for acceptance corrections

/*	
	Double_t emin = 2.8;
    Double_t emax = 5.5;
    Double_t estep = (emax - emin)/Nq;
	Double_t ximin = -1;
	Double_t ximax = 1;
	Double_t xistep = (ximax - ximin)/Nq;
	TCut exibin[2][Nq];
	for (int q=0;q<Nq;q++)
	{
		exibin[0][q] = Form("beam >= 2.8 + %f && beam <= 2.8 + %f",q*estep,(q+1)*estep);
		cout << Form("beam >= 2.8 + %f && beam <= 2.8 + %f",q*estep,(q+1)*estep) <<endl;
		
		exibin[1][q] = Form("Xcmtheta >= -1 + %f && Xcmtheta <= -1 + %f",q*xistep,(q+1)*xistep);
		cout << Form("Xcmtheta >= -1 + %f && Xcmtheta <= -1 + %f",q*xistep,(q+1)*xistep) <<endl;
	}
*/
	
	//interactively choose Simulation type
	cout << "enter what you want to add a branch to ( Data, NoPol or PosPol or NegPol):";
	const string cchoice;
	cin >> cchoice;
	if(cchoice == "NoPol") 
	{
		const string choice="";
	}
	else 
	{
		const string choice = "-" + cchoice;
	}
	//second question
	cout << "What kind of cuts? (Basic_Mass3, Basic_BadPion, Basic_UnknownBackground,  ):";
	const string cuts;
	cin >> cuts;
	//third question
	cout << "enter where you would like to have had the acceptance derived from ( NoPol, PosPol or NegPol):";
	const string cchoiceAC;
	cin >> cchoiceAC;
	if(cchoiceAC == "NoPol") 
	{
		const string choiceAC ="";
	}
	else 
	{
		const string choiceAC = "-" + cchoiceAC;
	}	
	
		
	cout << "Fiducial cuts? (type yes or no):";
	const string fidchoice;
	cin >> fidchoice;
	if (fidchoice == "yes")
	{
		const string fid = "_Fid";
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
	if (choice.compare("-Data") == 0)
	{	
	  	cout <<"The data will be evaluated using Ac" <<  choiceAC.c_str() << endl;	
		TFile *file = TFile::Open(Form("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_%s%s.root",cuts.c_str(),fid.c_str()));
		TTree *tOriginal = (TTree*)file->Get("v15");
	}
	else
	{
		cout <<"The simulation will be evaluated using Ac"<<choiceAC.c_str() <<endl;
		TFile* file = new TFile(Form("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t4-t4%s-2kppim_%s%s.root",choice.c_str(),fid.c_str()));  
		TTree *tOriginal = (TTree*)file->Get("gpp2kppim");	
	}
	TFile *fileNew = new TFile(Form("./NewRootFiles/%sAc%s-%i_%ibins_%s%s.root",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nq,cuts.c_str(),fid.c_str()),"RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "New";

	//old branches
	float beam=0, Xcmtheta=0;
	float COS_pi_x, COS_pi_y, COS_pi_z;
	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("Xcmtheta", &Xcmtheta);
	tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);
	
	//New, seperate branches:
	float Rfactor[Nb][Nq][Nd];	
	float eRfactor[Nb][Nq][Nd];
	


	//New, unified branches: 
	float RUni[Nb][Nd];
	float eRUni[Nb][Nd];
	const char* RUniString[Nb][Nd];
	const char* eRUniString[Nb][Nd];
	const char* RUniString[Nb][Nd];
	const char* eRUniString[Nb][Nd];
	RUniString[0][0] = "REx", RUniString[0][1] = "REy", RUniString[0][2] = "REz";
	RUniString[1][0] = "RXix", RUniString[1][1] = "RXiy", RUniString[1][2] = "RXiz";
	eRUniString[0][0] = "eREx", eRUniString[0][1] = "eREy", eRUniString[0][2] = "eREz";
	eRUniString[1][0] = "eRXix", eRUniString[1][1] = "eRXiy", eRUniString[1][2] = "eRXiz";
	TBranch* RUniBranch[Nb][Nd];
	TBranch* eRUniBranch[Nb][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int d = 0; d < Nd; d++)
		{
			RUniBranch[b][d] = tNew->Branch(Form("%s",RUniString[b][d]), &RUni[b][d], Form("%s/F",RUniString[b][d]));
			eRUniBranch[b][d] = tNew->Branch(Form("%s",eRUniString[b][d]), &eRUni[b][d], Form("%s/F",eRUniString[b][d]));
		}
	}
	
	//Float_t Rtest;
	//TBranch* RtestBranch;
	//RtestBranch = tNew->Branch("Rtest", &Rtest, "Rtest/F");

	//-------------------------read in the acceptance correction parameters and error matrix observables------------------------------
	

	ifstream myParFile(Form("./txt/RxRyRz%s-%i_%ibins_%s%s.txt",choiceAC.c_str(),Nk,Nq,cuts.c_str(),fid.c_str()));
	ifstream myCovMatrixFile(Form("./txt/CovMatrixfile%s-%i_%ibins_%s%s.txt",choiceAC.c_str(),Nk,Nq,cuts.c_str(),fid.c_str()));
	if( !myParFile || !myCovMatrixFile) 
	{
		cout << "Cannot open one of the text files. \n";
		gROOT->ProcessLine(".q");
	}
	float P[Nb][Nq][Nd][Ne] = {0};  //fit parameters
	float eP[Nb][Nq][Nd][Ne] = {0};
	float covMatrix[Nb][Nq][Nd][Ne][Ne] = {0};  //array of NeXNe matrixes representing the error in the fitting
	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			for (int d = 0; d < Nd; d++)
			{
				cout << "--------- b = "<<b<<", q = "<<q<<", d = "<<d<<" ------------"<<endl;
				for (int e = 0; e < Ne; e++)
				{	
					cout << "  -- e = " << e <<"  --" << endl;
					myParFile >> P[b][q][d][e] >> eP[b][q][d][e]; //the error eP is not actualy used
					cout << "   P = " << P[b][q][d][e] << "  eP = " << eP[b][q][d][e] <<endl;
					for (int j = 0; j < Ne; j++)
					{
						myCovMatrixFile>>covMatrix[b][q][d][e][j];	
						cout <<"   " << covMatrix[b][q][d][e][j];
					
					}
					cout <<endl<<endl;
				}
			}
		}
	}
	
	//check for correspondence with the ascii file.
	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			for (int d = 0; d < Nd; d++)
			{
				for (int e = 0; e < Ne; e++)
				{
					cout << P[b][q][d][e] << "  " << eP[b][q][d][e] <<endl;
				}
			}
		}
	}		
	myParFile.close();	
	myCovMatrixFile.close();	
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	
	float R[Nb][Nq][Nd] = {0};
	float eR[Nb][Nq][Nd] = {0};
	float X[Nd] = {0};	
	float testcounter = 0;
	int nentries = (int)tOriginal->GetEntries(); 
	for (int i=0; i<nentries; i++) 
	{
		//cout << "!!!!!!!STARTING EVENT " << " " << i << "  !!!!!!!!!!!" <<endl;
		tOriginal->GetEntry(i);

		X[0] = COS_pi_x, X[1] = COS_pi_y, X[2] = COS_pi_z;		
		//cout << "beam = " << beam << "  Xcmtheta = " << Xcmtheta <<endl;
		//cout << "COS_pi_x = " << COS_pi_x << "  COS_pi_y = " << COS_pi_y << "  COS_pi_z = " << COS_pi_z << endl;	
		//fill the seperate branches
		//cout << endl;
		//cout  << "Seperate Branches" <<endl;
		for (int b = 0; b < Nb; b++)
		{
			for (int q = 0; q < Nq; q++)
			{
				for (int d = 0; d < Nd; d++)
				{
					R[b][q][d] = 0;
					eR[b][q][d] = 0;
					
					//if ( (d == 0 && X[0] < -0.6 )||( d==2 && X[2] > 0.6) ) //reject events outside of fitting range.
					//{
					//	//cout << "rejected:" <<endl;
					//	cout <<"d, X[0], X[2] = "<<d<<" "<<X[0]<<" "<< X[2]<<endl;
					//	R[b][c][d] = -0.01;
					//	eR[b][c][d] = -0.01;
					//}
					//else
					//{	
					
						//cout << "- - - -  b = "<<b<<", c = "<<c<<", d = "<<d<<" - - - - "<<endl;					
						//R[b][c][d] = P[b][c][d][0] + P[b][c][d][1]*X[d] + P[b][c][d][2]*X[d]*X[d] + P[b][c][d][3]*X[d]*X[d]*X[d] + P[b][c][d][4]*X[d]*X[d]*X[d]*X[d];	
						for (int e = 0; e < Ne; e++)
						{
							R[b][q][d] += P[b][q][d][e]*pow(X[d],e); 
							for (int j = 0; j < Ne; j++)
							{
								eR[b][q][d] += covMatrix[b][q][d][e][j]*pow(X[d],e)*pow(X[d],j); //this equals the error squared
								//cout << "e,j = " <<e<<" "<<j<<"  eR squared = " <<eR[b][c][d]<< " and the test = " << test << endl;
							}
						}
					
						
						
						//cout << "Finaly eR Squared = " <<eR[b][c][d] <<" ";
						eR[b][q][d] = eR[b][q][d]*eR[b][q][d]; //square to get a positve number
						eR[b][q][d] =  sqrt(sqrt(eR[b][q][d])); // finaly get the error. 
						//cout << "  and eR  = " <<eR[b][c][d] <<endl;
					//}
					//cout << "- - - -  b = "<<b<<", c = "<<c<<", d = "<<d<<" - - - - "<<endl;
					//cout << "  P[b][c][d][0] = " << P[b][c][d][0] << "  P[b][c][d][1] = "<<P[b][c][d][1]<<"  P[b][c][d][2] = "<<P[b][c][d][2]<<"  P[b][c][d][3] = "<<P[b][c][d][3]<<"  P[b][c][d][4] = "<<P[b][c][d][4]<<endl;
					//cout << "X[d] = " << X[d] << endl; 
					//cout << "R = " << R[b][c][d] << "  eR = " << eR[b][c][d] <<endl;
					Rfactor[b][q][d] = R[b][q][d];
					eRfactor[b][q][d] = eR[b][q][d];
					//RBranch[b][c][d]->Fill();
					//eRBranch[b][c][d]->Fill();
					testcounter = testcounter + 1;
					//cout << "testcounter = " << testcounter <<  " so passing through cut " << testcounter/(i+1.0) << " times per event " << endl;			
				}
			}
		}
	
		//set up the boolian criteron for beam and xi bins
		bool exibinBool[Nb][Nq];
		for (int q=0;q<Nq;q++)
		{
			exibinBool[0][q] = beam >= eVal[q] && beam <= eVal[q+1];
			exibinBool[1][q] = Xcmtheta >=  xVal[q] && Xcmtheta <= xVal[q+1];
			//exibinBool[0][q] = beam >=  emin + q*estep && beam <= emin + (q+1)*estep;
			//exibinBool[1][q] = Xcmtheta >=  ximin + q*xistep && Xcmtheta <=  ximin + (q+1)*xistep;
		}
		
		//fill the unified branches
		int pass = 0;
		for (int b = 0; b < Nb; b++)  //loop over bin type
		{
			for (int d = 0; d < Nd; d++)  //loop over x y z
			{
				pass = 0;
				for (int q=0;q<Nq;q++)
				{
					if (exibinBool[b][q])
					{
						RUni[b][d] = R[b][q][d];
						eRUni[b][d] = eR[b][q][d];
						pass += 1;
					}
				}
				if (pass != 1)
				{
					cout <<" THERE IS A HUGE ERROR" <<endl;
					cout << "b,d = " << b <<", "<<d<<endl;
					cout << "beam = " <<beam <<endl;
					cout << "Xcmtheta = " << Xcmtheta <<endl;
					gROOT->ProcessLine(".q");
				}				
	
				//cout << "thing = " << RUniBranch[b][d]->GetEntryNumber() <<endl; 
				//cout << RUni[b][d] <<" " ;
				//RUniBranch[b][d]->Fill();
				//eRUniBranch[b][d]->Fill();
			}
		}
		
		int printnumber = 10;
		float tempf = nentries/printnumber;
		int tempi = tempf;
		
		if (i % tempi==0)
		{
			cout << " - - - - - -" << i << " - - - - - - -" <<endl;
			cout << "beam = " << beam << "  Xcmtheta = " << Xcmtheta <<endl;
			cout << "COS_pi_x = " << COS_pi_x << "  COS_pi_y = " << COS_pi_y << "  COS_pi_z = " << COS_pi_z << endl;
			cout << "REx = " << RUni[0][0] << "  REy = " << RUni[0][1] << "  REz = " << RUni[0][2] <<endl;
			cout << "RXix = " << RUni[1][0] << "  RXiy = " << RUni[1][1] << "  RXiz = " << RUni[1][2] <<endl;
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