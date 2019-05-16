/*
Author: Jason Bono
Date: April 15 2014
*/

#include "./Binning/DataEXiBins_3and3.h"
//#include "./Binning/DataEXiBins_3x3.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h" 

TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
TTree *tData = (TTree*)fData->Get("v15");

void GetBinCenter()
{
	//StyleUp();





	TCanvas *can = new TCanvas("can","",1200,1000);
	can->Divide(Nc,Nb);
	TH1F *he=new TH1F("he","he",100,2.2,5.5);
	TH1F *hxi=new TH1F("hxi","hxi",100,-1,1);
	TH1F *his[Nb][Nc];

		int cancount=1;
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
                cout <<"can = "<<cancount<<", b="<<b<<", c="<<c<<endl;
				can->cd(cancount);
				cancount += 1;
                
				
				if(b == 0){
					his[b][c] = (TH1F*)he->Clone(Form("h%i%i",b,c));
					tData->Draw(Form("beam>>h%i%i",b,c),EXibin[b][c]);
				}
				if(b == 1){
					his[b][c] = (TH1F*)hxi->Clone(Form("h%i%i",b,c));
					tData->Draw(Form("Xcmtheta>>h%i%i",b,c),EXibin[b][c]);
				}	
				
				
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
