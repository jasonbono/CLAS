/*

Name: .C
Author: Jason Bono
Date: Nov 18 2013

Purpose: the purpose is 3 fold with three main functions in this script.
1) To define the fringe in each EXi bin.   
2) to check the fringe function in Fringe.h is working
3) to define the pion binning

Usage: 
1) the ouput of DefineFringe() should be copy pasted into Fringe.h

There are two extra functions, ShowFringeCut and DefinePionBins which should only be run after Fringe.h is updated.

2) ShowFringeCut() simply shows the effect of the fringe cut as a crosscheck to ensure events are being selected in an expected way

3) DefinePionBins()'s is to define the binning of the pion dists for measurment of polarization. 
the output should be copy pasted into Pionbins.h.  
*/

#include "../DataEXiBins.h"
#include "../Fringe.h" //for ShowFringeCut()

//define some global variables
TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root"); 
TTree *tData = (TTree*)fData->Get("v05");
TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC-i9t4-t5-NoPol-2kppim_Basic_Mass.root"); 
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
TTree *myTree[2];
myTree[0] = tData;
myTree[1] = tMC;
//a=datatype, b=ebins, c=xibins, d=piaxis
const int Na = 2,Nd = 3;
const char* DataType[Na] = {"Data","MC"};
const char* Axis[Nd] = {"x","y","z"};
//the "acceptance cut"
Double_t perc = 0.3;
Int_t nbins = 30;

void DefineFringe()
{
	StyleUp();	
	
	//model for the pion histograms (will use as clone)
	TH1F *h=new TH1F("h","",nbins,-1.0,1.0);
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);	
	
	TCanvas *cFringe[Na][Nd];
	TH1F *hPion[Na][Nb][Nc][Nd];
	Double_t low[Na][Nb][Nc][Nd] = 0;
	Double_t high[Na][Nb][Nc][Nd] = 0;
	TLine *linelow[Na][Nb][Nc][Nd];
	TLine *linehigh[Na][Nb][Nc][Nd];	
	for (int a = 0; a < Na; a++)
	{
		for (int d = 0; d < Nd; d++)
		{
			int cancount = 1;
			cFringe[a][d] = new TCanvas(Form("c%s%s",DataType[a],Axis[d]),Form("c%s%s",DataType[a],Axis[d]),1200,1000);
			cFringe[a][d]->Divide(Nb,Nc);
			for (int b = 0; b < Nb; b++)
			{ 
				for (int c = 0; c < Nc; c++)
				{
					cFringe[a][d]->cd(cancount);	
					hPion[a][b][c][d] = (TH1F*)h->Clone(Form("h%s-ebin%i-xbin%i-PiAxis%s",DataType[a],b,c,Axis[d]));
					myTree[a]->Draw(Form("COS_pi_%s>>h%s-ebin%i-xbin%i-PiAxis%s",Axis[d],DataType[a],b,c,Axis[d]),EXibin[b][c]);			
					hPion[a][b][c][d]->SetMinimum(0);
					Double_t max = hPion[a][b][c][d]->GetMaximum();
					cout << "max = " <<max<<endl;
					Int_t lowbin = hPion[a][b][c][d]->FindFirstBinAbove(max*perc,1);
					Int_t highbin = hPion[a][b][c][d]->FindLastBinAbove(max*perc,1);
					double lowtest = hPion[a][b][c][d]->GetBinContent(lowbin);
					double hightest = hPion[a][b][c][d]->GetBinContent(highbin);
					if(d==1)
					{
						low[a][b][c][d] = -0.95;
						high[a][b][c][d] = 0.95;
						
					}
					else
					{
						if(lowtest == max)
						{
							low[a][b][c][d] = -1;
						}
						else
						{
							low[a][b][c][d] = hPion[a][b][c][d]->GetBinCenter(lowbin);
						}
						if(hightest == max)
						{
							high[a][b][c][d] = 1;
						}
						else
						{
							high[a][b][c][d] = hPion[a][b][c][d]->GetBinCenter(highbin);
						}
					}
					cout <<" low =  " <<low[a][b][c][d]<<"   high = " <<high[a][b][c][d]<<endl;
					
					linelow[a][b][c][d] = new TLine(low[a][b][c][d],0,low[a][b][c][d],max*perc);
					linelow[a][b][c][d]->SetLineColor(kRed);
					linelow[a][b][c][d]->SetLineWidth(2);
					linelow[a][b][c][d]->Draw("same");
					linehigh[a][b][c][d] = new TLine(high[a][b][c][d],0,high[a][b][c][d],max*perc);
					linehigh[a][b][c][d]->SetLineColor(kRed);
					linehigh[a][b][c][d]->SetLineWidth(3);
					linehigh[a][b][c][d]->Draw("same");
										
					cancount += 1;
				}
			}
		}
	}

	//overlay data histograms over mc results
	TCanvas *cOverlay[Nd];
	for (int d = 0; d < Nd; d++)
	{
		cOverlay[d] = new TCanvas(Form("c%s",Axis[d]),Form("c%s",Axis[d]),1200,1000);
		cOverlay[d]->Divide(Nb,Nc);
		int cancount = 1;
		for (int b = 0; b < Nb; b++)
		{ 
			for (int c = 0; c < Nc; c++)
			{
				cOverlay[d]->cd(cancount);
				//hPion[0][b][c][d]->SetBins(10, -1, 1);
				float temp1 = hPion[0][b][c][d]->GetEntries();
				float temp2 = hPion[1][b][c][d]->GetEntries();
				float normfac = temp1/temp2;
				hPion[1][b][c][d]->Add(hPion[1][b][c][d], normfac - 1);
				float oldmax = linelow[1][b][c][d]->GetY2();
				linelow[1][b][c][d]->SetY2(oldmax*normfac);
				float oldmax = linehigh[1][b][c][d]->GetY2();
				linehigh[1][b][c][d]->SetY2(oldmax*normfac);
				hPion[0][b][c][d]->SetMarkerStyle(21);
				hPion[0][b][c][d]->Draw("e");
				hPion[1][b][c][d]->SetLineColor(kRed);
				hPion[1][b][c][d]->Draw("same");
				linelow[1][b][c][d]->Draw("same");
				linehigh[1][b][c][d]->Draw("same");
				cancount += 1;
			}
		}
	}
		
	cout <<"copy and paste below: "<<endl;

	for (int b = 0; b < Nb; b++)
	{ 
		for (int d = 0; d < Nd; d++)
		{
			for (int c = 0; c < Nc; c++)
			{
				cout << Form("( (z < %f)||(z > %f) ))",low[1][b][c][d],high[1][b][c][d])<<endl;
			}
		}
	}
}





void ShowFringeCut()
{	
	Float_t beam_Data,Xcmtheta_Data,COS_pi_x_Data,COS_pi_y_Data,COS_pi_z_Data;
	myTree[0]->SetBranchAddress("beam", &beam_Data);
	myTree[0]->SetBranchAddress("Xcmtheta", &Xcmtheta_Data);
	myTree[0]->SetBranchAddress("COS_pi_x", &COS_pi_x_Data);
	myTree[0]->SetBranchAddress("COS_pi_y", &COS_pi_y_Data);
	myTree[0]->SetBranchAddress("COS_pi_z", &COS_pi_z_Data);
	
	Float_t beam_MC,Xcmtheta_MC,COS_pi_x_MC,COS_pi_y_MC,COS_pi_z_MC;
	myTree[1]->SetBranchAddress("beam", &beam_MC);
	myTree[1]->SetBranchAddress("Xcmtheta", &Xcmtheta_MC);
	myTree[1]->SetBranchAddress("COS_pi_x", &COS_pi_x_MC);
	myTree[1]->SetBranchAddress("COS_pi_y", &COS_pi_y_MC);
	myTree[1]->SetBranchAddress("COS_pi_z", &COS_pi_z_MC);
	Float_t beam[Na],Xcmtheta[Na],COS_pi_x[Na],COS_pi_y[Na],COS_pi_z[Na];
	Float_t varX[Na],varY[Na],varZ[Na][Nd];
	
	//model for the pion histograms (will use as clone)
	TH1F *h=new TH1F("h","",2*nbins,-1.0,1.0);
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);
	TH1F *hshow[Na][Nb][Nc][Nd];
	for (int a = 0; a < Na; a++)
	{
		for (int d = 0; d < Nd; d++)
		{
			for (int b = 0; b < Nb; b++)
			{ 
				for (int c = 0; c < Nc; c++)
				{	
					hshow[a][b][c][d] = (TH1F*)h->Clone(Form("hshow%s-ebin%i-xbin%i-PiAxis%s",DataType[a],b,c,Axis[d]));
				}
			}
		}
	}
	
	for (int a = 0; a < Na; a++)
	{
		//loop over the entries and fill the histogram
		Long64_t nentries = myTree[a]->GetEntries();
		for (Long64_t ii=0; ii<nentries; ii++)
		{
			myTree[a]->GetEntry(ii);
			beam[0] = beam_Data;
			Xcmtheta[0] = Xcmtheta_Data;
			COS_pi_x[0] = COS_pi_x_Data;
			COS_pi_y[0] = COS_pi_y_Data;
			COS_pi_z[0] = COS_pi_z_Data;
			beam[1] = beam_MC;
			Xcmtheta[1] = Xcmtheta_MC;
			COS_pi_x[1] = COS_pi_x_MC;
			COS_pi_y[1] = COS_pi_y_MC;
			COS_pi_z[1] = COS_pi_z_MC;
			varX[a] = beam[a]; 
			varY[a] = Xcmtheta[a];	
			varZ[a][0] = COS_pi_x[a];
			varZ[a][1] = COS_pi_y[a];
			varZ[a][2] = COS_pi_z[a];
				
			//cout <<"varX = " <<varX[a] <<"    varY = " <<varY[a]<<endl; 
			for (int b = 0; b < Nb; b++)
			{
				for (int c = 0; c < Nc; c++)
				{
					bool bin = false;
					if ( (varX[a] >= EVal[b] && varX[a] < EVal[b+1]) && (varY[a] >= XVal[b][c] && varY[a] < XVal[b][c+1]) ) {bin = true;} //bin in exi
					for (int d = 0; d < Nd; d++)
					{
						bool good = NoFringe_6bins(varX[a],varY[a],varZ[a][d],d);
						bool fill = bin&&good;
						if(fill)
						{
							hshow[a][b][c][d]->Fill(varZ[a][d]);
						}
					}	
				}
			}
		}
	}	
	
	TCanvas *cShow[Na][Nd];
	for (int a = 0; a < Na; a++)
	{
		for (int d = 0; d < Nd; d++)
		{
			int cancount = 1;
			cShow[a][d] = new TCanvas(Form("cshow%s%s",DataType[a],Axis[d]),Form("cshow%s%s",DataType[a],Axis[d]),1200,1000);
			cShow[a][d]->Divide(Nb,Nc);
			for (int b = 0; b < Nb; b++)
			{ 
				for (int c = 0; c < Nc; c++)
				{
					cShow[a][d]->cd(cancount);
					hshow[a][b][c][d]->Draw();
					cancount += 1;
				}
			}
		}
	}
}



void DefinePionBins()
{
	StyleUp();
	const int Np = 5;//the number of pion bins to derive
	const int Ni = 100;// the number of bins in the histogram to derive the Np bins
	int a = 0; //for data

	Float_t beam,Xcmtheta,COS_pi_x,COS_pi_y,COS_pi_z;
	Float_t varX,varY,varZ[Nd];

	tData->SetBranchAddress("beam", &beam);
	tData->SetBranchAddress("Xcmtheta", &Xcmtheta);
	tData->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tData->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tData->SetBranchAddress("COS_pi_z", &COS_pi_z);
	
	//model for the pion histograms (will use as clone)
	TH1F *h=new TH1F("h","",Ni,-1.0,1.0);
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);
	TH1F *hshow[Nb][Nc][Nd];
	for (int d = 0; d < Nd; d++)
	{
		for (int b = 0; b < Nb; b++)
		{ 
			for (int c = 0; c < Nc; c++)
			{
	
				hshow[b][c][d] = (TH1F*)h->Clone(Form("h-ebin%i-xbin%i-PiAxis%s",b,c,Axis[d]));
			}
		}
	}	
	//loop over the entries and fill the histogram
	Long64_t nentries = tData->GetEntries();
	for (Long64_t ii=0; ii<nentries; ii++)
	{
		tData->GetEntry(ii);
		varX = beam; 
		varY = Xcmtheta;	
		varZ[0] = COS_pi_x;
		varZ[1] = COS_pi_y;
		varZ[2] = COS_pi_z;
				
		//cout <<"varX = " <<varX <<"    varY = " <<varY<<endl; 
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				bool bin = false;
				if ( (varX >= EVal[b] && varX < EVal[b+1]) && (varY >= XVal[b][c] && varY < XVal[b][c+1]) ) {bin = true;} //bin in exi
				for (int d = 0; d < Nd; d++)
				{
					bool good = NoFringe_6bins(varX,varY,varZ[d],d);
					bool fill = bin&&good;
					if(fill)
					{
						hshow[b][c][d]->Fill(varZ[d]);
					}
				}	
			}
		}
	}	
	//show the initial histograms
	TCanvas *cShow[Nd];
	for (int d = 0; d < Nd; d++)
	{
		int cancount = 1;
		cShow[d] = new TCanvas(Form("c%s",Axis[d]),Form("c%s",Axis[d]),1200,1000);
		cShow[d]->Divide(Nb,Nc);
		for (int b = 0; b < Nb; b++)
		{ 
			for (int c = 0; c < Nc; c++)
			{
				 cShow[d]->cd(cancount);
				 hshow[b][c][d]->Draw();
				 cancount += 1;
			}
		}
	}
	float pbinlow[Nb][Nc][Nd];
	float pbinhigh[Nb][Nc][Nd];
	float plow[Nb][Nc][Nd];
	float phigh[Nb][Nc][Nd];
	Int_t pCritera[Nb][Nc][Nd];//really dont need extra Nd dimention
	float pval[Nb][Nc][Nd][Np - 1];
	float pVal[Nb][Nc][Nd][Np + 1];
	TCut pcut[Nb][Nc][Nd][Np];
	for (int d = 0; d < Nd; d++)
	{
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				pbinlow[b][c][d] = hshow[b][c][d]->FindFirstBinAbove(0);
				pbinhigh[b][c][d] = hshow[b][c][d]->FindLastBinAbove(0);
				plow[b][c][d] = hshow[b][c][d]->GetBinCenter(pbinlow[b][c][d] );
				phigh[b][c][d] = hshow[b][c][d]->GetBinCenter(pbinhigh[b][c][d] );
				TCut plowcut[b][c][d] = Form("COS_pi_%s > %f",Axis[d],plow[b][c][d]);
				TCut phighcut[b][c][d] = Form("COS_pi_%s < %f",Axis[d],phigh[b][c][d]);
				pCritera[b][c][d] = hshow[b][c][d]->GetEntries()/Np;
				cout <<"critera = "	<<pCritera[b][c][d]<<endl;			
				int pbin = 0;
				int ppop =0;
				for (int p = 0; p < Np - 1; p++)
				{
					for (int i = 0; i < Ni; i++)
					{
						pbin = pbinlow[b][c][d] + i;			
						ppop = hshow[b][c][d]->Integral(pbinlow[b][c][d],pbin);
						if (ppop >= pCritera[b][c][d])
						{
							float ptempval =  hshow[b][c][d]->GetBinCenter(pbin);
							pval[b][c][d][p] = ptempval; //store the value
							pbinlow[b][c][d] = pbin; //lowbin for the next b iteration should be the current bin for this iteration.
							i = Ni; //kill i loop the loop		
					   }
					}
				}
				pVal[b][c][d][0] = plow[b][c][d];
				pVal[b][c][d][Np] = phigh[b][c][d];
				for (int p=0; p< Np - 1; p++)
				{
					pVal[b][c][d][p+1] = pval[b][c][d][p];
				}				
			}
		}
	}
	
	//write and cout the cuts
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p<Np; p++)
				{
					pcut[b][c][d][p] =  Form("Pibin[%i][%i][%i][%i] = \" COS_pi_%s > %f && COS_pi_%s < %f \"; ",b,c,d,p,Axis[d],pVal[b][c][d][p],Axis[d],pVal[b][c][d][p+1]);
					TString temp = pcut[b][c][d][p];
					cout << temp << endl;
				}
			}
		}
	}
	cout<<endl;
	//write and cout the vals	
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p<Np+1; p++)
				{
					cout <<  Form("PiVal[%i][%i][%i][%i] =  %f ; ",b,c,d,p,pVal[b][c][d][p])<<endl;
				}
			}
		}
	}
}







StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.08);
	gStyle->SetTitleYSize(0.07); 
	gStyle->SetPadTopMargin(0.06);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit();
}