/*
Name: GetPionHists.C
Author: Jason Bono
Date: Jun 12 2013
Purpose: First step in the calculation of the acceptance corrected pion distributions.

Input: *MC*.root,
*Gen*.root
Output: *PionHists*.root

Update: ac2 was created to implement aproximately 27x3x2 different acceptance corrections 

Update: altered to take into account 10x10 bins as oposed to seperate bins
*/

#include "./SimEXiBins.h"

void GetPionHists()
{	
	int Nk = 40; //# of pion bins

	//interactively choose Simulation type
	cout << "enter choice ( NoPol or PosPol or NegPol):";
	const string choice;
	cin >> choice;
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

	cout <<Form("The %s%s  simulation will be evaluated",choice.c_str(),fid.c_str())<<endl;
	//MC
	TFile* fMC = new TFile(Form("~/clas/rootfiles/LINKS/MC-i9t4-t5-%s-2kppim_Basic_Mass%s.root",choice.c_str(),fid.c_str())); 
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	//Gen
	TFile* fGen = new TFile(Form("~/clas/rootfiles/LINKS/MC-i9t4-t5-%s-gamproot.root",choice.c_str()));
	TTree *tGen = (TTree*)fGen->Get("GampTree");
	Double_t gampfactor = 10;	
	//New File
	TFile* fHistos = new TFile(Form("./hists/PionHists-%s-%i_%i_%ibins%s.root",choice.c_str(),Nk,Nbq,Ncq,fid.c_str()),"RECREATE");
				
	// Create model for the pion histograms (will use as clone)
	TH1D *h=new TH1D("h","",Nk,-1.0,1.0); // 2/2000 = 0.001
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);	
	
	
	//a=datatype, b=enegybins, c=xibins, d=piaxis
	const int Na = 2,Nd = 3;
	const char* DataType[Na] = {"MC","Gen"};
	const char* Axis[Nd] = {"x","y","z"};
    
	const TTree* TreeType[Na];
	TreeType[0] = tMC;
	TreeType[1] = tGen;
	TH1D *hPion[Na][Nbq][Ncq][Nd];

	///fill the hists
	for (int a = 0; a < Na; a++)
	{
		if (a == 0)
		{
			double factor = 1;
		}
		else if (a == 1)
		{
			double factor = gampfactor;
		}
		for (int bq = 0; bq < Nbq; bq++)
		{
			for (int cq = 0; cq < Ncq; cq++)
			{
				for (int d = 0; d < Nd; d++)
				{
					hPion[a][bq][cq][d] = (TH1D*)h->Clone(Form("h%s-ebin%i-xbin%i-PiAxis%s",DataType[a],bq,cq,Axis[d]));
					TreeType[a]->Draw(Form("COS_pi_%s>>h%s-ebin%i-xbin%i-PiAxis%s",Axis[d],DataType[a],bq,cq,Axis[d]),exibin[bq][cq]);
					hPion[a][bq][cq][d]->Add(hPion[a][bq][cq][d],factor - 1);
					hPion[a][bq][cq][d]->SetMinimum(0);
					hPion[a][bq][cq][d]->Write();
				}			
			}
		}
	}
	gROOT->ProcessLine(".q");
}