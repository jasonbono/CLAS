/*
Author: Jason Bono
Date: October 2017
 
 copied from GetBinCenter to get the mean of each bin in the 3x3 scheeme
*/


#include "./Binning/DataEXiBins_3x3.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"

TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
TTree *tData = (TTree*)fData->Get("v15");

void GetBinCenter3x3()
{
	//StyleUp();





	TCanvas *cane = new TCanvas("cane","",1200,1000);
	cane->Divide(Nc,Nb);
    TCanvas *canx = new TCanvas("canx","",1200,1000);
    canx->Divide(Nc,Nb);
	TH1F *he=new TH1F("he","he",100,2.2,5.5);
	TH1F *hxi=new TH1F("hxi","hxi",100,-1,1);
	TH1F *hise[Nb][Nc];
    TH1F *hisxi[Nb][Nc];

		int cancount=1;
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
                
                
				cane->cd(cancount);
                hise[b][c] = (TH1F*)he->Clone(Form("he%i%i",b,c));
                tData->Draw(Form("beam>>he%i%i",b,c),EXibin[b][c]);
                cout << "e_Avg (EXiBin["<<b<<"]["<<c<<"] )= " <<hise[b][c]->GetMean()<<endl;
                
                canx->cd(cancount);
                hisxi[b][c] = (TH1F*)hxi->Clone(Form("hxi%i%i",b,c));
                tData->Draw(Form("Xcmtheta>>hxi%i%i",b,c),EXibin[b][c]);
                cout << "xi_Avg (EXiBin["<<b<<"]["<<c<<"] )= "<<hisxi[b][c]->GetMean()<<endl;
                
				cancount += 1;
				
				
			}
		}
				

}



StyleUp()
{
	gStyle->SetTitleXOffset(0.6);
	gStyle->SetTitleYOffset(0.75);
	gStyle->SetTitleSize(0.07);
	gStyle->SetTitleYSize(0.06); 
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
}
