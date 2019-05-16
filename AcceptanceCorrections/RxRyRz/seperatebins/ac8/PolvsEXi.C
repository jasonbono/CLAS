



//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "./DataEXiBins.h" 
#include "./SimEXiBins.h"


PolvsEXi()
{
  	//gStyle->SetPadGridX(kTRUE);
  	gStyle->SetPadGridY(kTRUE);

	StyleUp();
	const int Nb = 2,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
	const int Np = 10; //number of pion bins
	int Nk = 60; //# of pion bins used to get the acceptance parameters

		
	const char* BinType[Nb] = {"E","Xi"};
	const char* Axis[Nd] = {"x","y","z"};

	const Int_t colorsLei[5] = {1, 2, 4, 6, 8};
	const Int_t styleLei[5] = {22, 21, 20, 23, 33};
	
	
	//interactively choose Data or Simulation
	cout << "enter choice of what you want to look at (Data, NoPol, PosPol or NegPol):";
	const string choice;
	cin >> choice;
	//second question
	cout << "enter where you would like to have had the acceptance derived from ( NoPol, PosPol or NegPol):";
	const string choiceAC;
	cin >> choiceAC;
	if ( (choiceAC.compare("NoPol") != 0) && (choiceAC.compare("PosPol") != 0) && (choiceAC.compare("NegPol") != 0) )
	{
		cout << "incorect of choice of AC. quiting" <<endl;
		gROOT->ProcessLine(".q");
	}
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
	
	//myfile.open (Form("./txt/%s-Ac%sCorrected-PolResults-%i_%i_%ibins%s.txt",choice.c_str(),choiceAC.c_str(),Nk,Nq,Nc,fid.c_str()));
	//polarizaton input
	ifstream in(Form("./txt/%s-Ac%sCorrected-PolResults-%i_%i_%ibins%s.txt",choice.c_str(),choiceAC.c_str(),Nk,Nq,Nc,fid.c_str()));
	if(!in)
	{
	    cout << "Cannot open txt file.\n";
		gROOT->ProcessLine(".q");
	}
	Double_t Polarization[Nb][Nc][Nd] = {0};
	Double_t ePolarization[Nb][Nc][Nd] = {0};
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{	
				in >> Polarization[b][c][d] >> ePolarization[b][c][d];
				cout << Polarization[b][c][d] << " " << ePolarization[b][c][d] <<endl;
			}
		}
	}




	TH1F *hEXi[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				hEXi[b][c][d] = new TH1F(Form("h%s-%sBin%i",Axis[d],BinType[b],c),Form("h%s-%sBin%i",Axis[d],BinType[b],c),100,-1,6);
			}
		}
	}



	
	//from the output of ...AcceptanceCorrections/EXi/EXiAcceptance.C
	Double_t EXiMean[Nb][Nc];
	EXiMean[0][0] = 3.47165;
	EXiMean[0][1] = 4.14768;
	EXiMean[0][2] = 5.02795;
	EXiMean[1][0] = -0.838769;
	EXiMean[1][1] = -0.425452;
	EXiMean[1][2] = 0.33643;


	//ploting vectors
	Double_t Y[Nb][Nd][Nc] = {0};
	Double_t eY[Nb][Nd][Nc] = {0};
	Double_t X[Nb][Nd][Nc] = {0};


	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{	
				X[b][d][c] = EXiMean[b][c];
				cout << " - - -   X = " << X[b][d][c] << " - - - "<<endl;
				Y[b][d][c] = Polarization[b][c][d];
				eY[b][d][c] = ePolarization[b][c][d];
				cout << "Y = " << Y[b][d][c] << "  eY = " << eY[b][d][c] <<endl<<endl;
			}
		}
	}




	TCanvas *cPol = new TCanvas("cPol", "cPol", 1200, 1000);
	cPol->Divide(2,1);
	TGraphErrors *gr[Nb][Nd];
	TLegend* leg[Nb];
	for (int b = 0; b < Nb; b++)
	{
		leg[b] = new TLegend(.7, .7, .9, .9); //top right
		for (int d = 0; d < Nd; d++)
		{
			cPol->cd(b+1);
			gr[b][d] = new TGraphErrors(Nc, X[b][d], Y[b][d], 0, eY[b][d]);
    		gPad->SetMargin(.15, .1, .15, .1);
    		gr[b][d]->SetMarkerSize(1.5);
    		gr[b][d]->SetMarkerColor(colorsLei[d]);
			gr[b][d]->SetMarkerStyle(styleLei[d]);
   			TString xaxis = (b == 0)? "E_{#gamma} (GeV)" : "Cos#theta^{cm}_{#Xi}";
			gr[b][d]->GetXaxis()->SetTitle(xaxis);
    		gr[b][d]->GetXaxis()->CenterTitle();
			gr[b][d]->GetXaxis()->SetTitleSize(0.06);
			gr[b][d]->GetXaxis()->SetTitleOffset(0.8);
   			gr[b][d]->GetYaxis()->SetTitle("Polarization");
    		gr[b][d]->GetYaxis()->CenterTitle();
			gr[b][d]->GetYaxis()->SetTitleSize(0.06);
    		gr[b][d]->SetTitle();

    		gr[b][d]->GetYaxis()->SetTitleOffset(0.7);
    		gr[b][d]->GetYaxis()->SetRangeUser(-2, 2);
			gr[b][d]->SetMinimum(-1.2);
			gr[b][d]->SetMaximum(1.2);
    		TString opt = (d == 0) ? "AP" : "Psame";
    		gr[b][d]->Draw(opt);
    		gPad->Update();
    		leg[b]->AddEntry(gr[b][d], (d==0)?"C_{x}":(d==1)?"P":"C_{z}", "p");

		}
		leg[b]->Draw("same");
	}

	TCanvas	*cblank = new TCanvas("cblank","cblank", 1, 1);

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////


StyleUp()
{
	gStyle->SetTitleXOffset(0.4);
	gStyle->SetTitleYOffset(0.6);
	gStyle->SetTitleSize(0.09);
	gStyle->SetTitleYSize(0.07); 
	gStyle->SetPadTopMargin(0.1);
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




	//E-Xi bin center input
	/*
	the old way
	Double_t EXiMean[Nb][Nc][Nd];
	TFile *file = TFile::Open(Form("./NewRootFiles/Data-Basic-Mass-AcNoPol-%i_%ibins.root",Nk,Nq));
	TTree *tOriginal = (TTree*)file->Get("New");
	TCanvas	*cbeam = new TCanvas("cbeam","cbeam", 1200, 1000);
	cbeam->Divide(5,5);
	int ccount = 1;
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{	
				cbeam->cd(ccount);
				if (b==0)
				{
					hEXi[b][c][d] = new TH1F(Form("h%s-%sBin%i",Axis[d],BinType[b],c),Form("h%s-%sBin%i",Axis[d],BinType[b],c),200,2.8,5.5);
					tOriginal->Draw(Form("beam >> h%s-%sBin%i",Axis[d],BinType[b],c),Form("1/R%s%s",BinType[b],Axis[d])*(EXiBin[b][c]));
				}
				if (b==1)
				{
					hEXi[b][c][d] = new TH1F(Form("h%s-%sBin%i",Axis[d],BinType[b],c),Form("h%s-%sBin%i",Axis[d],BinType[b],c),200,-1,1);
					tOriginal->Draw(Form("Xcmtheta >> h%s-%sBin%i",Axis[d],BinType[b],c),Form("1/R%s%s",BinType[b],Axis[d])*(EXiBin[b][c]));
				}
				
				EXiMean[b][c][d] = hEXi[b][c][d]->GetMean();
				cout << "eximean = " <<EXiMean[b][c][d] <<endl;
				ccount += 1;
			}
		}
	}
	*/