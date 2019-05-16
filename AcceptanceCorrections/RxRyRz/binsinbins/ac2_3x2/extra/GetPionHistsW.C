/*
Name: GetPionHists.C
Author: Jason Bono
Date: April 4 2013
Purpose: First step in the calculation of the acceptance corrected pion distributions.

Input: .../MC_i3_2kppim_Basic_Mass.root, .../MC_i3_2kppim_Basic_Mass.root
Output: ./hists/PionHists.root
*/


#include "/Users/Bono/clas/myDefinitions/WBins.h" 
#include "/Users/Bono/clas/myDefinitions/EXiBins.h"


void GetPionHists()
{	

	int Nk = 50; //# of pion bins
	
	//~~~~~~~~~~~~~~~~~~~~~files~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//MC
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC-i5-2kppim_Basic_Mass.root");  
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	//Gen
	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/MC-i5-gamproot-100.root");
	TTree *tGen = (TTree*)fGen->Get("GampTree");
	Double_t gampfactor = 100;
	
	//New file of histograms
	TFile* fHistos = new TFile(Form("./hists/PionHists-%ibins.root",Nk),"RECREATE");
	// . . . . . . . . . . . . . . . . . . . . . . . . . . 
	
		
	//-----------The Weighting Factors---------
	if(NWBins == 27){
		
		ifstream in("/Users/Bono/clas/myDefinitions/txt/Winfo-i5-NoPol.txt"); // input
	  	if(!in) {
	    	cout << "Cannot open txt file.\n";
			gROOT->ProcessLine(".q");
	  	}
		double W[NWBins] = {0},eW[NWBins] = {0};

		for (int z = 0; z < NWBins ; z++) 
		{
	  		in >> W[z] >> eW[z];
	  		cout << "W[z], eW[z] = " << W[z] << ", " << eW[z] << "\n";
		}
			in.close();		
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . 	
	
	
				
	// Create model for the missing mass histograms (will use as clone)
	TH1D *h=new TH1D("h","",Nk,-1.0,1.0); // 2/2000 = 0.001
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);	
	
	
	//a=datatype, b=bintype, c=binnumber, d=piaxis
	const int Na = 2,Nb = 2,Nc = 3,Nd = 3;
	const char* DataType[Na] = {"MC","Gen"};
	const char* BinType[Nb] = {"E","Xi"};
	const char* BinNumber[Nc] = {"0","1","2"};
	const char* Axis[Nd] = {"x","y","z"};
    
	const TTree* TreeType[Na];
	TreeType[0] = tMC;
	TreeType[1] = tGen;
	TH1D *hPion[Na][Nb][Nc][Nd];
	TH1D *hPionW[Na][Nb][Nc][Nd][NWBins];
	//TH1D *hAc[Nb][Nc][Nd];
		
	//define the cuts
	TCut Cut[Na][Nb][Nc];
	TCut CutAndW[Na][Nb][Nc][NWBins];
	TString String_CutAndW[Na][Nb][Nc][NWBins];
	for (int a = 0; a < Na; a++)
	{
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				//if (a == 0) Cut[a][b][c] = hypersphere && EXiBin[b][c];  //the cuts used to be different for MC and Gen. now all filtering is done first :)
				if (a == 0) Cut[a][b][c] = EXiBin[b][c];
				else if (a == 1) Cut[a][b][c] = EXiBin[b][c];
				else cout << "error... sorry buddy" <<endl;
				
				for (int k = 0; k < NWBins ; k++) 
				{
					CutAndW[a][b][c][k] = Cut[a][b][c] && WBin[k];
					String_CutAndW[a][b][c][k] = CutAndW[a][b][c][k]; //for dubugging
					
					
					cout <<" --------------- " << endl;
					cout << String_CutAndW[a][b][c][k] << endl;
					cout << " . . . . . . . " <<endl;
				}
			}
		}
	}
	
	
	//determine factors to normize the events
	Double_t NoEvents[Na][Nb][Nc] = {0};
	Double_t NoWEvents[Na][Nb][Nc] = {0};
	Double_t Factor[Na][Nb][Nc] = {0};
	TH1D ("hcouter","hcounter",Nk,0.0,6.0); 
	for (int a = 0; a < Na; a++)
	{
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				TreeType[a]->Draw("beam>>hcounter",Cut[a][b][c]);
				NoEvents[a][b][c] = hcounter->GetEntries();
				cout << "NoEvents["<<a<<"]["<<b<<"]["<<c<<"] = " <<NoEvents[a][b][c]<<endl;
			}
		}
	}
	

	//*//fill the hists
	for (int a = 0; a < Na; a++)
	{
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				for (int d = 0; d < Nd; d++)
				{
					hPion[a][b][c][d] = (TH1D*)h->Clone(Form("h%s-%sBin%s-PiAxis%s",DataType[a],BinType[b],BinNumber[c],Axis[d]));
					for (int k = 0; k < NWBins; k++) 
					{
						hPionW[a][b][c][d][k] = (TH1D*)h->Clone(Form("h%s-%sBin%s-PiAxis%s-W%i",DataType[a],BinType[b],BinNumber[c],Axis[d],k));
						
						TreeType[a]->Draw(Form("COS_pi_%s>>h%s-%sBin%s-PiAxis%s-W%i",Axis[d],DataType[a],BinType[b],BinNumber[c],Axis[d],k),CutAndW[a][b][c][k]);				
						
						//fill the histogram
						if (hPionW[a][b][c][d][k]->GetEntries() > 0)
						{	
							//cout <<" Good! the cut is:"<<endl;
							//cout << String_CutAndW[a][b][c][k] <<endl;
							//cout << " - - - - - - - - - -" <<endl;
							hPionW[a][b][c][d][k]->SetMinimum(0);					
							hPion[a][b][c][d]->Add(hPionW[a][b][c][d][k],W[k]);					
						}
						else 
						{
							//cout <<"Bad!!"<<endl;
							//cout << String_CutAndW[a][b][c][k] <<endl;
							//cout << " - - - - - - - - - -" <<endl;
						}
					}
					//normalize 
					NoWEvents[a][b][c] = hPion[a][b][c][d]->GetEntries();
					if (a==0)
					{
						Factor[a][b][c] = NoEvents[a][b][c] / NoWEvents[a][b][c];
					}
					else if (a==1)
					{
						Factor[a][b][c] = gampfactor * NoEvents[a][b][c] / NoWEvents[a][b][c];
					}
					cout << "Factor["<<a<<"]["<<b<<"]["<<c<<"] = " <<Factor[a][b][c]<<endl;
					hPion[a][b][c][d]->Add(hPion[a][b][c][d],Factor[a][b][c] - 1);
					cout << "The number of entries are:" <<endl;
					cout << "hPion["<<a<<"]["<<b<<"]["<<c<<"]["<<d<<"] = " <<hPion[a][b][c][d]->GetEntries()<<endl;
					hPion[a][b][c][d]->SetMinimum(0);
					hPion[a][b][c][d]->Write();
				}
			
			}
		}
	}


gROOT->ProcessLine(".q");

}