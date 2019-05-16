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
	cout << "What kind of cuts? (Basic_Mass3, Basic_Mass1, Basic_Mass9, Basic_BadPion, Basic_UnknownBackground,  ):";
	const string cuts;
	cin >> cuts;
	
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

	cout <<Form("The %s%s  simulation will be evaluated",choice.c_str(),fid.c_str())<<endl;
	//MC
	TFile* fMC = new TFile(Form("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t4-t4%s-2kppim_%s%s.root",choice.c_str(),cuts.c_str(),fid.c_str())); 
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	//Gen
	Int_t gampfactor = 10;
	TFile* fGen = new TFile(Form("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t4-t4%s-gamproot-%i.root",choice.c_str(),gampfactor));
	TTree *tGen = (TTree*)fGen->Get("GampTree");
	//new
	TFile* fHistos = new TFile(Form("./hists/PionHists%s-%i_%i_%ibins_%s%s.root",choice.c_str(),Nk,Nbq,Ncq,cuts.c_str(),fid.c_str()),"RECREATE");
	
	
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