/*

Date: May 6 2013

Author: Jason Bono

Purpose: To find the normalization factor in order to effectively match the beam energy spectra of the simulation and the data.

Input: Data,MC,MC-PosPol,WBins.h
Output: ./txt/Winfo.txt

Notes: 
		W is simply the Yeild of the Data divided by the Yield of the MC in each energy bin.
		Werr[i] is calculated assuming yieldData and yieldMC are unclorrelated ie the covarience is zero.


*/

#include "/Users/Bono/clas/myDefinitions/WBins.h"


void GetW(){




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CHOOSE SIGNAL OR SIDEBAND~~~~~~~~~~~~~~~~~~~~~~~~~
	//*//<----2a------FOR SIGNAL
	TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
	TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i5-2kppim_Basic_Mass.root");
	TFile *fMCP = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i5-PosPol-2kppim_Basic_Mass.root");
 	TTree *tData = (TTree*)fData->Get("v05");
	
	ofstream myWfile;
	//interactively choose MC or PosPol
	cout << "enter choice (MC or MCP ):";
	const string choice;
	cin >> choice;
	if (choice.compare("MC") == 0)
	{
	  	cout <<"The MC  with zero polarization will be evaluated" <<endl;	
		TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
		myWfile.open ("./Winfo-i5-NoPol.txt");

	}
	else if (choice.compare("MCP") == 0) 
	{
		cout <<"The MC with positive polarization will be evaluated" <<endl;	
		TTree *tMC = (TTree*)fMCP->Get("gpp2kppim");
		myWfile.open ("./Winfo-i5-PosPol.txt");
	}
	else
	{ 
		cout << "choice error, quiting! " <<endl;
		gROOT->ProcessLine(".q");
	}

	

	//*///
		
	/*//<------2b---FOR SIDEBAND
	TFile* fData = new TFile("~/clas/rootfiles/Links/Reduced/2kppim-v05-sb.root"); 
	TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/sim/Reduced/MC_i2_2kppim_sb.root");
	TTree *tData = (TTree*)fData->Get("v05_sb"); //<------
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_sb");
	//*///
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	
	
	//~~~~~~~~~~~~~~~~~~~~DELCARE~~~~~~~~~~~~~~~~~~~~~~~
	Double_t YieldData[NWBins] = {0}, YieldMC[NWBins] = {0} ;
	Int_t YieldDataErr[NWBins] = {0}, YieldMCErr[NWBins] = {0};
	Double_t W[NWBins] = {0},Werr[NWBins] = {0};
	Double_t TotalWeight = 0;
	
	//canvases
	TCanvas *c0=new TCanvas("c0","",700,400);
	TCanvas *cData=new TCanvas("cData","cData",1200,800);	
	TCanvas *cMC=new TCanvas("cMC","cMC",1200,800);
	cData->Divide(6,5);
	cMC->Divide(6,5);
	c0->cd();
		
	//set up the histograms
	TH1D *h=new TH1D("h","",100,2.6,5.6);
	tData->Draw("beam>>h");
	h->GetYaxis()->SetTitle("Events/3MeV/");  
	h->GetXaxis()->SetTitle(" Eg (GeV)");
	TH1D *hData[NWBins], *hMC[NWBins];

	//-----------------------------------------start the iteration------------------------------------
	for (int i = 0; i < NWBins ; i++)
 	{
		//Data
		cData->cd(i + 1);
		hData[i] = (TH1D*)h->Clone(Form("hData%i",i));	
		tData->Draw(Form("beam>>hData%i",i),WBin[i]);	
		YieldData[i] = hData[i]->GetEntries();
		YieldDataErr[i] = sqrt(YieldData[i]);	
		
		//MC
		cMC->cd(i + 1);
		hMC[i] = (TH1D*)h->Clone(Form("hMC%i",i));	
		tMC->Draw(Form("beam>>hMC%i",i),WBin[i]);	
		YieldMC[i] = hMC[i]->GetEntries();
		YieldMCErr[i] = sqrt(YieldMC[i]);

		//Compute W and Werr 
		W[i] = YieldData[i]/YieldMC[i];
		Werr[i] = W[i]*sqrt((YieldDataErr[i]/YieldData[i])*(YieldDataErr[i]/YieldData[i]) + (YieldMCErr[i]/YieldMC[i])*(YieldMCErr[i]/YieldMC[i]));
		
		//add to Total weight
		TotalWeight += W[i]*W[i]; //this is incorrect
		cout <<" total weight = " << TotalWeight <<endl;
	}
	//Double_t RenormFactor = 1/TotalWeight;

	double TotalMC = tMC->GetEntries(), TotalData = tData->GetEntries();
	Double_t RenormFactorMC = TotalMC/TotalData;



	//Check
	double CountMC = 0, CountData = 0;
	for (int i = 0; i < NWBins ; i++) 
	{
		cout << "yield for data is:  " <<YieldData[i] << " +- " << YieldDataErr[i] <<endl;
		cout << "yield for MC is:    " <<YieldMC[i] << " +- " << YieldMCErr[i] <<endl;
		cout << "the weighting factor is:    " <<W[i] << " +- " << Werr[i] <<endl;
		cout << endl;
		CountData += YieldData[i];
		CountMC += YieldMC[i];
	}
	
	//output the results to the screen
	for (int i = 0; i < NWBins ; i++) 
	{
		cout <<W[i] << ", ";
	}
	cout << ""<<endl;
	cout << "======================================W above, Werr below ==================================" << endl;
	cout << "" <<endl;
	for (int i = 0; i < NWBins ; i++) 
	{
		cout << Werr[i] << ", ";
		
		//record the W info into the txt file
		if(W[i] > 0 && W[i] < 9000000){  //only for good values
			myWfile << W[i]<< " " <<Werr[i] <<endl;
		} 
		else // if get something like inf or nan then just print zero to the file
		{
			W[i] = 0;
			Werr[i] = 0;
			myWfile << W[i]<< " " <<Werr[i] <<endl;
		}
	}
	myWfile << RenormFactorMC;
//---------------------------------------------
	cout <<endl;
	cout << "  Reconstruced events: " << tMC->GetEntries() << "  Data events: " << tData->GetEntries() <<endl;
	cout << "  RenormFactorMC: " << RenormFactorMC <<endl;
	myWfile.close();
		
		
		
		
}