/*
Name: GetPionHists.C
Author: Jason Bono
Date: Jun 12 2013
Purpose: First step in the calculation of the acceptance corrected pion distributions.

Input: *MC*.root, *Gen*.root 
Output: *PionHists*.root

Update: ac2 was created to implement aproximately 27x3x2 different acceptance corrections 

*/


//#include "/Users/Bono/clas/myDefinitions/WBins.h" 
//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "./SimEXiBins.h"


void GetPionHists()
{	

	int Nk = 60; //# of pion bins
	//const int Nq = 20; //number of energy and Xi bins for acceptance corrections
	
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
	//New File
	TFile* fHistos = new TFile(Form("./hists/PionHists%s-%i_%ibins_%s%s.root",choice.c_str(),Nk,Nq,cuts.c_str(),fid.c_str()),"RECREATE");
			
	// Create model for the pion histograms (will use as clone)
	TH1D *h=new TH1D("h","",Nk,-1.0,1.0); // 2/2000 = 0.001
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);	
	
	//a=datatype, b=bintype, c=binnumber, d=piaxis
	const int Na = 2,Nb = 2,Nd = 3;
	const char* DataType[Na] = {"MC","Gen"};
	const char* BinType[Nb] = {"E","Xi"};
	//const char* BinNumber[Nc] = {"0","1","2"};
	const char* Axis[Nd] = {"x","y","z"};
    
	const TTree* TreeType[Na];
	TreeType[0] = tMC;
	TreeType[1] = tGen;
	TH1D *hPion[Na][Nb][Nq][Nd];

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
		for (int b = 0; b < Nb; b++)
		{
			for (int q = 0; q < Nq; q++)
			{
				for (int d = 0; d < Nd; d++)
				{
					hPion[a][b][q][d] = (TH1D*)h->Clone(Form("h%s-%sBin%i-PiAxis%s",DataType[a],BinType[b],q,Axis[d]));
					TreeType[a]->Draw(Form("COS_pi_%s>>h%s-%sBin%i-PiAxis%s",Axis[d],DataType[a],BinType[b],q,Axis[d]),exibin[b][q]);
					hPion[a][b][q][d]->Add(hPion[a][b][q][d],factor - 1);
					hPion[a][b][q][d]->SetMinimum(0);
					hPion[a][b][q][d]->Write();
				}			
			}
		}
	}


gROOT->ProcessLine(".q");

}