/*
Author: Jason Bono
Date: Jun 13 2013
*/

#include "./Binning/DataEXiBins_1x1.h"
//#include "./Binning/DataEXiBins_3x3.h"
//#include "./Binning/DataEXiBins_3and3.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h" 

const int dofit = 0;


//TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_Xi3.root");
//TTree *tData = (TTree*)fData->Get("v13");

 TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
 TTree *tData = (TTree*)fData->Get("v15");
// TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_BadPion.root");
// TTree *tData = (TTree*)fData->Get("v13");
//TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_UnknownBackground.root");
//TTree *tData = (TTree*)fData->Get("v13");


TFile *fDataFid = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3_Fid.root");
//TTree *tData = (TTree*)fDataFid->Get("v15Loose");
//TTree *tData = (TTree*)fDataFid->Get("v15Reg");
//TTree *tData = (TTree*)fDataFid->Get("v15Tight");





//TFile *fDataFid = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_Mass3_Fid.root");
//TTree *tData = (TTree*)fDataFid->Get("v13Loose");
//TTree *tData = (TTree*)fDataFid->Get("v13Reg");
//TTree *tData = (TTree*)fDataFid->Get("v13Tight");

//*
TFile *fPos = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t3-t3-PosPolY-2kppim_Basic_Mass3.root");
TTree *tPos = (TTree*)fPos->Get("gpp2kppim");
TFile *fNeg = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t3-t3-NegPolY-2kppim_Basic_Mass3.root");
TTree *tNeg = (TTree*)fNeg->Get("gpp2kppim");
//*/



TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t3-t3-2kppim_Basic_Mass3.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");

const float alpha = -0.458;
//const float ealpha = 0.012;
const float ealpha = 0.000000;  //if you dont want to include error from analyzing power

void Pasy()
{
	StyleUp();

	
	//StyleUp();
	//set up helicity
	TCut negHelBin = "COS_pi_y < 0";	
	TCut posHelBin = "COS_pi_y > 0";
	

	//set up the Xilab angle bins
	TCut Xforward = "Xcmtheta <= -0.8";	
	double negN[Nb][Nc] = {0};
	double posN[Nb][Nc] = {0};
	double asy[Nb][Nc] = {0};
	double enegN[Nb][Nc] = {0};
	double eposN[Nb][Nc] = {0};
	double easy[Nb][Nc] = {0};
	// vector<double> xx;
	// vector<double> yy;
	// vector<double> exx;
	// vector<double> eyy;
	// double x; //note that the dimention of plotting variables are Np but will endup ploting x pts where x <=Np
	// double y;
	// double ex;
	// double ey;

	TCanvas *cPol;
	double GraphTop[Nb][Nc] = {0};
	TGraphErrors *storegr[Nb][Nc];
	TLatex *storetex[Nb][Nc];

	
	TH1F *h=new TH1F("h","",100,-1,1);
	h->GetXaxis()->SetTitle("Cos(#theta_{#pi^{-}}^{y})");
	h->GetYaxis()->SetTitle("Events");
	TH1F *hisn[Nb][Nc];
	TH1F *hisp[Nb][Nc];

	int cancount=1;
	cPol = new TCanvas("cPol","cP",1200,1000);
	cPol->Divide(Nc,Nb);
	ctemp = new TCanvas("temp","",10,10);
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			cPol->cd(cancount);
			cancount+=1;
			float asytot = 0;
			float negtot = 0;
			float postot = 0;
	
			hisn[b][c] = (TH1F*)h->Clone(Form("h%i%in",b,c));
			hisn[b][c]->SetFillColor(46);		
			tData->Draw(Form("COS_pi_y>>h%i%in",b,c),EXibin[b][c]&&negHelBin);
			GraphTop[b][c] = hisn[b][c]->GetMaximum();
			negN[b][c] = hisn[b][c]->GetEntries();							
			enegN[b][c] = sqrt(negN[b][c]);							
			hisp[b][c] = (TH1F*)h->Clone(Form("h%i%ip",b,c));
			hisp[b][c]->SetFillColor(43);
			tData->Draw(Form("COS_pi_y>>h%i%ip",b,c),EXibin[b][c]&&posHelBin,"SAME");
			if(hisp[b][c]->GetMaximum() > GraphTop[b][c]) {
				GraphTop[b][c] = hisp[b][c]->GetMaximum();
				hisn[b][c]->SetMaximum(hisp[b][c]->GetMaximum());
			}
			posN[b][c] = hisp[b][c]->GetEntries();	
			eposN[b][c] = sqrt(posN[b][c]);
			
				
			asy[b][c] = (posN[b][c] - negN[b][c])/(posN[b][c] + negN[b][c]);
			float tp = posN[b][c];
			float tep = eposN[b][c];
			float tn = negN[b][c];
		    float ten = enegN[b][c];
			float ta = asy[b][c];
			float tea =  ( 2/( (tp+tn)*(tp+tn) ) ) * sqrt(tn*tn*tep*tep + tp*tp*ten*ten );
			float tP = -2*ta/alpha;
			float teP = sqrt( pow(2*tea/alpha,2) + pow(2*ta*ealpha/(alpha*alpha),2) );
			easy[b][c] = tea;
			cout << "b=" << b << " c=" <<c<<" ta="<<ta<<" tea="<<tea<<endl;
			cout << "tP=" << tP << " teP=" <<teP<<endl;
			
			TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
			mytex=new TLatex(-0.9, 0.9*GraphTop[b][c],Form("P = %5.3f #pm %5.3f ",tP,teP));
			mytex->SetTextSize(0.06); 
			mytex->SetTextColor(4);
			mytex->Draw("SAME");
			
			TLatex *mytex2=new TLatex(0.0, 0.0,"mytex2");
			TLatex *mytex3=new TLatex(0.0, 0.0,"mytex3");			
			if(XVal[0][0] == 1000)
			{
				mytex2=new TLatex(-0.9, 0.8*GraphTop[b][c],Form(" %s ",EString[b][c]));
				mytex3=new TLatex(-0.9, 0.7*GraphTop[b][c],Form(" %s ",XString[b][c]));
			}
			else
			{				
				
				mytex2=new TLatex(-0.9, 0.8*GraphTop[b][c],Form(" %1.2f < E_{#gamma} < %1.2f ",EVal[b],EVal[b+1]));
				mytex3=new TLatex(-0.9, 0.7*GraphTop[b][c],Form(" %1.2f < cos(#theta_{#Xi}^{cm}) < %1.2f  ",XVal[b][c],XVal[b][c+1]));				
			}
			mytex2->SetTextSize(0.06); 
			mytex2->SetTextColor(4);
		    mytex2->Draw("SAME");
		    mytex3->SetTextSize(0.06); 
			mytex3->SetTextColor(4);
		    mytex3->Draw("SAME");
		


		
				
		}
	}
	ctemp->cd(0);
}



StyleUp()
{
	gStyle->SetTitleXOffset(0.6);
	gStyle->SetTitleYOffset(0.75);
	gStyle->SetTitleSize(0.063);
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
