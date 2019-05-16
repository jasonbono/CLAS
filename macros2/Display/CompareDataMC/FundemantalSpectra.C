/*
Author: Jason Bono
Date: Jun 13 2013
Purpose: To display the spectra of the following quantities for Data and MC without the w factors:

as of now (6/13/13) ShowTiming() is not working because it requires the full files before Basic cuts

Usage: 	.L FundemantalSpectra.C
		//GetHyperonWidth();
		//PlotGen();
		PlotAngles();
		//PlotPionAngles()
		PlotMomenta();
		PlotResMass();
		//PlotBeam();
		//FidBeam();
		//ShowTiming();
		//EvsX();

		extra: PlotGen(),GetHyperonWidth

or .x FundemantalSpectra.C
*/


//#include "/Users/Bono/clas/myDefinitions/WBins.h"
//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"
//#include "/Users/Bono/clas/AcceptanceCorrections/RxRyRz/ac4/DataEXiBins.h"
#include "/Users/Bono/clas/AcceptanceCorrections/RxRyRz/seperatebins/ac6/DataEXiBins.h"

const int Nb = 2,Nc = 3,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
const char* BinType[Nb] = {"E","Xi"};
const char* BinNumber[Nc] = {"0","1","2"};
const char* Axis[Nd] = {"x","y","z"};
float MASS_Kaon_CHARGED = 0.493677;
float MASS_Pion_CHARGED = 0.13957018;
const char* angletype[2] = {"theta","phi"};


//TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
//TTree *tData = (TTree*)fData->Get("v05");

TFile *fRawData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16Copy/hadded/2kppim-v16_VeryBasic_Mass3.root");
TTree *tRawData = (TTree*)fRawData->Get("v16");


TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic_Mass3.root");
TTree *tData = (TTree*)fData->Get("v16");

TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t5-t5-2kppim_Basic_Mass3.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");

//TFile *fMCNoDetach = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i4/MC_i4_2kppim_Basic_Mass.root");
//TTree *tMCNoDetach = (TTree*)fMCNoDetach->Get("gpp2kppim");

TFile *fGen = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t5-t5-gamproot-10.root");
TTree *tGen = (TTree*)fGen->Get("GampTree");




// TFile *fDataFid = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass-Fid.root");
// TTree *tDataFidReg = (TTree*)fDataFid->Get("v05Reg");
// TTree *tDataFidTight = (TTree*)fDataFid->Get("v05Tight");
// TTree *tDataFidLoose = (TTree*)fDataFid->Get("v05Loose");
//
// TFile *fMCFid = TFile::Open("~/clas/rootfiles/LINKS/MC-i8-2kppim_Basic_Mass_Fid.root");
// TTree *tMCFidReg = (TTree*)fMCFid->Get("gpp2kppimReg");
// TTree *tMCFidTight = (TTree*)fMCFid->Get("gpp2kppimTight");
// TTree *tMCFidLoose = (TTree*)fMCFid->Get("gpp2kppimLoose");



//TFile *fMCFid = TFile::Open("~/clas/rootfiles/LINKS/MC-i8-2kppim_Basic_Mass-Fid.root");
//TTree *tMCFid = (TTree*)fMCFid->Get("gpp2kppim");

/*///
TFile *fDataB = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic.root");
TTree *tDataB = (TTree*)fDataB->Get("v05");
TFile *fMCB = TFile::Open("~/clas/rootfiles/LINKS/MC-i8-2kppim_Basic.root");
TTree *tMCB = (TTree*)fMCB->Get("gpp2kppim");



TFile *fDataC = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Mass.root");
TTree *tDataC = (TTree*)fDataC->Get("v05");
//TFile *fMCC = TFile::Open("~/clas/rootfiles/LINKS/MC-i8-2kppim_Mass.root");
//TTree *tMCC = (TTree*)fMCC->Get("gpp2kppim");
///*///



//TFile *fMCTest1 = TFile::Open("~/clas/TESTS/Timing/try01/gpp2kppim_Basic_Mass.root");
//TTree *tMCTest1 = (TTree*)fMCTest1->Get("gpp2kppim");
//TFile *fMCTest2 = TFile::Open("~/clas/TESTS/Timing/try01/mygpp2kppim_Basic_Mass.root");
//TTree *tMCTest2 = (TTree*)fMCTest2->Get("mygpp2kppim");

/*
TFile *fMCTest1 = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i0/MC-2kppim-v05-4_5.i0t1.root");
TTree *tMCTest1 = (TTree*)fMCTest1->Get("gpp2kppim");
TFile *fMCTest2 = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i0/MC-2kppim-v05-4_5.i0t2.root");
TTree *tMCTest2 = (TTree*)fMCTest2->Get("gpp2kppim");

TFile *fMCMKWay = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/TimeingTests/MKWay.root");
TTree *tMCMKWay = (TTree*)fMCMKWay->Get("work");

TFile *fMCMKWay2 = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/TimeingTests/MKWay2.root");
TTree *tMCMKWay2 = (TTree*)fMCMKWay2->Get("work");
*/

//-----------------------------------

void FundemantalSpectra()
{

	//GimeMyPlotSmile();
	//ShowPL();
	//PlotBeam();
	// PlotAngles();
	 //GetHyperonWidth();
	 //PlotResMass();
	 //PlotMomenta();
	//ShowTiming();


	//ShowPhi();
	//PlotGen();
	//PlotK2Angles();
	//PlotPionAngles();
	//PlotGotfriedAngles();

	//FidBeam();

	//EvsX();
	//ShowFidEffect_PhiVsP_Data();
	//ShowFidEffect_PhiVsP_MC();
	//ShowFidEffect_PhiVsTheta_MC();
	//ShowFidEffect_clas_MC();
}

// void GimeMyPlotSmile();
// {
// 	TCanvas *can=new TCanvas("can","",1800,800);
// 	can->Divide(2,1);
// 	can->cd(1);
//
// 	TH1F *hmxk1=new TH1F("hmxk1","",50,1.5,3);  //1500/150 = 10 MeV
// 	hmxk1->SetMinimum(0);
// 	hmxk1->SetMarkerStyle(21);
// 	hmxk1->SetFillStyle(3001);
// 	hmxk1->SetFillColor(3);
// 	hmxk1->GetYaxis()->SetTitle("Events");
// 	hmxk1->GetXaxis()->SetTitle("M(#Xi^{-} k^{+}_{slow}) (GeV/c) ");
//
//}

void ShowPL(){
	StyleUp();
	gStyle->SetOptStat(1);
	TH1F *hData=new TH1F("hData","",125,500,750);
	hData->SetFillColor(kGreen);
	//hData->SetFillStyle(3001);
	TH1F *hMC=new TH1F("hMC","",125,500,750);
	hMC->SetFillColor(kRed);
	hMC->SetFillStyle(3001);
	TH1F *hMCNoDetach=new TH1F("hMCNoDetach","",125,500,750);
	hMCNoDetach->SetFillColor(kRed);
	hMCNoDetach->SetFillStyle(3001);
	hData->GetXaxis()->SetTitle("Data pion path length");
	hMC->GetXaxis()->SetTitle("Simulated pion path length");
	hMCNoDetach->GetXaxis()->SetTitle("Simulated pion path length (No Detachment)");

	TCanvas *can=new TCanvas("can","",1800,800);
	can->Divide(3,1);
	TTree *t1 = tData;
	TTree *t2 = tMC;
	TTree *t3 = tMCNoDetach;
	can->cd(1);
	t1->Draw("sclpim>>hData");
	can->cd(2);
	t2->Draw("sclpim>>hMC");
	can->cd(3);
	t3->Draw("sclpim>>hMCNoDetach");

	// float temp1 = hData->GetEntries();
	// float temp2 = hMC->GetEntries();
	// float temp3 = hMCNoDetach->GetEntries();
	// float	normfac = temp1/temp2;
	// float normfac2 = temp1/temp3;
	// hMC->Add(hMC, normfac - 1);
	// hMCNoDetach->Add(hMCNoDetach, normfac2 - 1);
	// hData->Draw("E");
	// hMCNoDetach->Draw("SAME");
	// hMC->Draw("SAME");


	///*////



}


void ShowPhi()
{
	StyleUp();
	gStyle->SetOptStat(1);
	//TTree *mytData = tDataFidLoose;
	//TTree *mytMC = tMCFid;
	TTree *mytData = tData;
	//TTree *mytMC = tMC;

	/*////mc and data hists
	TH1F *hMCphik1=new TH1F("hMCphik1","",90,-180,180);
	hMCphik1->GetXaxis()->SetTitle("#phi K^{+}_{fast}");
	TH1F *hMCphik2=new TH1F("hMCphik2","",90,-180,180);
	hMCphik2->GetXaxis()->SetTitle("#phi K^{+}_{slow}");
	TH1F *hMCphipi=new TH1F("hMCphipi","",90,-180,180);
	hMCphipi->GetXaxis()->SetTitle("#phi #pi^{-}");
	TH1F *hDataphik1=new TH1F("hDataphik1","",90,-180,180);
	hDataphik1->GetXaxis()->SetTitle("#phi K^{+}_{fast}");
	TH1F *hDataphik2=new TH1F("hDataphik2","",90,-180,180);
	hDataphik2->GetXaxis()->SetTitle("#phi K^{+}_{slow}");
	TH1F *hDataphipi=new TH1F("hDataphipi","",90,-180,180);
	hDataphipi->GetXaxis()->SetTitle("#phi #pi^{-}");
	//change mc color
	hMCphik1->SetLineColor(2);
	hMCphik2->SetLineColor(2);
	hMCphipi->SetLineColor(2);

	//fill the hists
	mytMC->Draw("180*kp1labphi>>hMCphik1");
	mytMC->Draw("180*kp2labphi>>hMCphik2");
	mytMC->Draw("180*pilabphi>>hMCphipi");
	mytData->Draw("180*kp1labphi>>hDataphik1");
	mytData->Draw("180*kp2labphi>>hDataphik2");
	mytData->Draw("180*pilabphi>>hDataphipi");



	TCanvas *cphi=new TCanvas("cphi","cphi",1000,800);
	cphi->Divide(2,2);



	float temp1 = hDataphik1->GetEntries();
	float temp2 = hMCphik1->GetEntries();
	float	normfac = temp1/temp2;
	hMCphik1->Add(hMCphik1, normfac - 1);
	hMCphik2->Add(hMCphik2, normfac - 1);
	hMCphipi->Add(hMCphipi, normfac - 1);
	cphi->cd(1);
	hDataphik1->Draw("E");
	hMCphik1->Draw("SAME");
	cphi->cd(2);
	hDataphik2->Draw("E");
	hMCphik2->Draw("SAME");
	cphi->cd(3);
	hDataphipi->Draw("E");
	hMCphipi->Draw("SAME");
	///*////


	/*///show clas detector (MC)
	TH2F *hMCclask1=new TH2F("hMCclask1","",90,0,90,360,-180,180);
	TH2F *hMCclask2=new TH2F("hMCclask2","",90,0,90,360,-180,180);
	TH2F *hMCclaspi=new TH2F("hMCclaspi","",90,0,90,360,-180,180);
	hMCclask1->GetYaxis()->SetTitle("#phi K^{+}_{fast}");
	hMCclask1->GetXaxis()->SetTitle("#theta  K^{+}_{fast}");
	hMCclask2->GetYaxis()->SetTitle("#phi  K^{+}_{slow}");
	hMCclask2->GetXaxis()->SetTitle("#theta  K^{+}_{slow}");
	hMCclaspi->GetYaxis()->SetTitle("#phi  #pi^{-}");
	hMCclaspi->GetXaxis()->SetTitle("#theta #pi^{-}");
	hMCclask1->SetTitle("MC");
	hMCclask2->SetTitle("MC");
	hMCclaspi->SetTitle("MC");
	TCanvas *cMCclas=new TCanvas("cMCclas","cMCclas",1000,800);
	cMCclas->Divide(2,2);
	cMCclas->cd(1);
	mytMC->Draw("180*kp1labphi:(180/3.1415)*acos(kp1labtheta)>>hMCclask1","","colz");
	cMCclas->cd(2);
	mytMC->Draw("180*kp2labphi:(180/3.1415)*acos(kp2labtheta)>>hMCclask2","","colz");
	cMCclas->cd(3);
	mytMC->Draw("180*pilabphi:(180/3.1415)*acos(pilabtheta)>>hMCclaspi","","colz");
	///*////


	//*///show clas detector (Data)
	TH2F *hDataclask1=new TH2F("hDataclask1","",90,0,90,360,-180,180);
	TH2F *hDataclask2=new TH2F("hDataclask2","",90,0,90,360,-180,180);
	TH2F *hDataclaspi=new TH2F("hDataclaspi","",90,0,90,360,-180,180);
	hDataclask1->GetYaxis()->SetTitle("#phi K^{+}_{fast}");
	hDataclask1->GetXaxis()->SetTitle("#theta  K^{+}_{fast}");
	hDataclask2->GetYaxis()->SetTitle("#phi  K^{+}_{slow}");
	hDataclask2->GetXaxis()->SetTitle("#theta  K^{+}_{slow}");
	hDataclaspi->GetYaxis()->SetTitle("#phi  #pi^{-}");
	hDataclaspi->GetXaxis()->SetTitle("#theta #pi^{-}");
	hDataclask1->SetTitle("Data");
	hDataclask2->SetTitle("Data");
	hDataclaspi->SetTitle("Data");
	TCanvas *cDataclas=new TCanvas("cDataclas","cDataclas",1000,800);
	cDataclas->Divide(2,2);
	cDataclas->cd(1);
	mytData->Draw("180*kp1labphi:(180/3.1415)*acos(kp1labtheta)>>hDataclask1","","colz");
	cDataclas->cd(2);
	mytData->Draw("180*kp2labphi:(180/3.1415)*acos(kp2labtheta)>>hDataclask2","","colz");
	cDataclas->cd(3);
	mytData->Draw("180*pilabphi:(180/3.1415)*acos(pilabtheta)>>hDataclaspi","","colz");
	///*///

}

void GetHyperonWidth()
{

	Double_t emin = 2.8;
    Double_t emax = 5.5;
    const Int_t Nebins = 6;
    Double_t estep = (emax - emin)/Nebins;
	TCut ebin[Nebins];
	for (int i=0;i<Nebins;i++)
	{
		ebin[i] = Form("beam >= 2.8 + %f && beam <= 2.8 + %f",i*estep,(i+1)*estep);
		cout << Form("beam >= 2.8 + %f && beam <= 2.8 + %f",i*estep,(i+1)*estep) <<endl;
	}
	cout <<"copy and paste below: "<<endl;
	for (int i=0;i<Nebins;i++)
	{
		cout<<Form("push(@ELOW,%5.3f);",2.8+i*estep)<<endl;
	}

//	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
//	StyleUp();


	TCanvas *cGetHyperon=new TCanvas("cGetHyperon","cGetHyperon",1200,800);
	cGetHyperon->Divide(3,2);

	//Data
	//histos
	//model
	TH1F *hMassData=new TH1F("hMass","",50,1.5,3);  //1500/150 = 10 MeV
	hMassData->SetMinimum(0);
	hMassData->SetMarkerStyle(21);
	hMassData->SetFillStyle(3001);
	hMassData->SetFillColor(3);
	hMassData->GetYaxis()->SetTitle("Events");
	hMassData->GetXaxis()->SetTitle("M(#Xi^{-} k^{+}_{slow}) (GeV/c) ");
	TH1F *hHyperonWidthE[Nebins];
	for (int i=0;i<Nebins;i++)
	{
			hHyperonWidthE[i] = (TH1F*)hMassData->Clone(Form("hHyperonWidthE%i",i));
			hHyperonWidthE[i]->SetTitle(Form("%5.2f < beam <= %5.2f",emin + i*estep,emin + (i+1)*estep));
	}

	hHyperonWidthAll = (TH1F*)hMassData->Clone("hHyperonWidthAll");

	TF1 *g1 = new TF1("g1","gaus",1,3);
	TF1 *g2 = new TF1("g2","gaus",1,2.15);
	TF1 *g3 = new TF1("g3","gaus",2.25,3);
	g1->SetLineColor(kBlack);
	g2->SetLineColor(kBlack);
	g3->SetLineColor(kBlack);
	int bin1 = 0;
	int bin2 = 0;
	double mass = 0;
	double rms = 0;
	double fwhm = 0;
	double mean = 0;
	double width = 0;
	double g1mass = 0;
	double g1width = 0;
	double g2mass = 0;
	double g2width = 0;
	double g3mass = 0;
	double g3width = 0;
	int cancount = 1;
	cout <<" - - - - Data - - - - - -" <<endl;


	TF1 *fmyBW=new TF1();

		cout <<"copy and past the following:"<<endl;
	for (int i=0;i<Nebins;i++)
	{
		cGetHyperon->cd(cancount);
		cancount += 1;
		tData->Draw(Form("mcasmkp2>>hHyperonWidthE%i",i),ebin[i]);
		hHyperonWidthE[i]->Draw("E");
		bin1 = hHyperonWidthE[i]->FindFirstBinAbove(hHyperonWidthE[i]->GetMaximum()/2);
   		bin2 = hHyperonWidthE[i]->FindLastBinAbove(hHyperonWidthE[i]->GetMaximum()/2);
		mass =  (hHyperonWidthE[i]->GetBinCenter(bin2) + hHyperonWidthE[i]->GetBinCenter(bin1))/2;
  		fwhm = hHyperonWidthE[i]->GetBinCenter(bin2) - hHyperonWidthE[i]->GetBinCenter(bin1);
		mean = hHyperonWidthE[i]->GetMean();
		rms = hHyperonWidthE[i]->GetRMS();
		width = 2.354*rms; //the relation between rms and fwhm for gaussian
		//cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;
		//cout << "mean,rms,width = " <<mean<<", "<<rms<<", "<<width<<endl;
		if(i<5)
		{
			hHyperonWidthE[i]->Fit(g1,"Q","",1,3);
			g1mass = g1->GetParameter(1);
			g1width = g1->GetParameter(2);
			float texheight =  hHyperonWidthE[i]->GetMaximum()/4.0;
			TLatex *mytex=new TLatex(1.6,texheight,Form("Mass = %5.3f #pm %5.3f",g1mass,g1width ));
			mytex->SetTextSize(0.07);
			mytex->SetTextColor(kBlack);
			mytex->Draw("SAME");
			cout<<Form("push(@Mass,%5.3f);",g1mass)<<endl;
			cout<<Form("push(@Width,%5.3f);",g1width)<<endl;
		}

		//fit the second gaussian for higher energy
		if(i>=5)
		{
			if(i>=6)
			{
				//could change fitting range for some
			}
			hHyperonWidthE[i]->Fit(g2,"QR");
			hHyperonWidthE[i]->Fit(g3,"QR+");

			g2mass = g2->GetParameter(1);
			g2width = g2->GetParameter(2);
			g3mass = g3->GetParameter(1);
			g3width = g3->GetParameter(2);

			//display the text
			float texheight =  hHyperonWidthE[i]->GetMaximum()/4.0;
			TLatex *mytex=new TLatex(1.6,texheight,Form("Mass = %5.3f #pm %5.3f",g2mass,g2width ));
			mytex->SetTextSize(0.07);
			mytex->SetTextColor(kBlack);
			mytex->Draw("SAME");
			//cout<<"MassB["<<i<<"]="<<g2mass<<";"<<endl;
			cout<<Form("push(@MassB,%5.3f);",g2mass)<<endl;
			cout<<Form("push(@WidthB,%5.3f);",g2width)<<endl;
			texheight =  hHyperonWidthE[i]->GetMaximum()/6.0;
			TLatex *mytex=new TLatex(1.6,texheight,Form("Mass2 = %5.3f #pm %5.3f",g3mass,g3width ));
			mytex->SetTextSize(0.07);
			mytex->SetTextColor(kBlack);
			mytex->Draw("SAME");
			//cout<<"MassC["<<i<<"]="<<g2mass<<";"<<endl;
			cout<<Form("push(@MassC,%5.3f);",g3mass)<<endl;
			cout<<Form("push(@WidthC,%5.3f);",g3width)<<endl;
		}
	}

	for (int i=0;i<Nebins;i++)
	{

	}

///*//
	//MC
	//histos
	//model
	TH1F *hMassMC=new TH1F("hMass","",50,1.5,3);  //800/80 = 40 MeV
	hMassMC->SetMinimum(0);
	hMassMC->SetMarkerStyle(21);
	hMassMC->SetFillStyle(3002);
	hMassMC->SetFillColor(2);
	hMassMC->GetYaxis()->SetTitle("Events");
	hMassMC->GetXaxis()->SetTitle("M(#Xi^{-} k^{+}_{slow}) (GeV/c)");
	TH1F *hMCHyperonWidthE[Nebins];
	for (int i=0;i<Nebins;i++)
	{
			hMCHyperonWidthE[i] = (TH1F*)hMassMC->Clone(Form("hMCHyperonWidthE%i",i));
	}
	hMCHyperonWidthAll = (TH1F*)hMassMC->Clone("hHyperonWidthAll");


	TCanvas *cblank=new TCanvas("cblank","",1,1);
	cout <<" - - - - MC - - - - - -" <<endl;
	for (int i=0;i<Nebins;i++)
	{

		tMC->Draw(Form("mcasmkp2>>hMCHyperonWidthE%i",i),ebin[i]);
		bin1 = hMCHyperonWidthE[i]->FindFirstBinAbove(hMCHyperonWidthE[i]->GetMaximum()/2);
   		bin2 = hMCHyperonWidthE[i]->FindLastBinAbove(hMCHyperonWidthE[i]->GetMaximum()/2);
		mass =  (hMCHyperonWidthE[i]->GetBinCenter(bin2) + hMCHyperonWidthE[i]->GetBinCenter(bin1))/2;
  		fwhm = hMCHyperonWidthE[i]->GetBinCenter(bin2) - hMCHyperonWidthE[i]->GetBinCenter(bin1);
		mean = hMCHyperonWidthE[i]->GetMean();
		rms = hMCHyperonWidthE[i]->GetRMS();
		width = 2.354*rms; //the relation between rms and fwhm for gaussian
		//cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;
		//cout << "mean,rms,width = " <<mean<<", "<<rms<<", "<<width<<endl;
	}

	int cancount = 1;
	for (int i=0;i<Nebins;i++)
	{
		cGetHyperon->cd(cancount);
		cancount += 1;
		float temp1 = hHyperonWidthE[i]->GetEntries();
		float temp2 = hMCHyperonWidthE[i]->GetEntries();
		float normfac = temp1/temp2;
		hMCHyperonWidthE[i]->Add(hMCHyperonWidthE[i], normfac - 1);
		//hHyperonWidthE[i]->Draw();
		hMCHyperonWidthE[i]->Draw("SAME");


	}

	cGetHyperon->Print("~/Desktop/resmass.png");

//*/
}



void PlotGen()
{
	StyleUp();

	TCanvas *cGen=new TCanvas("cGen","cGen",1500,1000);
	cGen->Divide(2,2);
	cGen->cd(1);

	TH1F *hMomenta=new TH1F("hMomenta","",400,0,4); // 4000/400 = 10 MeV
	hMomenta->SetMinimum(0);
	hMomenta->GetYaxis()->SetTitle("Events");
	hMomenta->SetMarkerStyle(21);

	hMomentaK1Gen = (TH1F*)hMomenta->Clone("hMomentaK1Gen");
	hMomentaK2Gen = (TH1F*)hMomenta->Clone("hMomentaK2Gen");
	hMomentaPimGen = (TH1F*)hMomenta->Clone("hMomentaPimGen");
	hMomentaK1Gen->GetXaxis()->SetTitle("p^{k^{+}_{fast}} (GeV/c) ");
	hMomentaK2Gen->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c) ");
	hMomentaPimGen->GetXaxis()->SetTitle("p^{#pi^{-}} (GeV/c) ");

	hMomentaK1Gen2 = (TH1F*)hMomenta->Clone("hMomentaK1Gen2");
	//tGen->Draw("sqrt(kp1x*kp1x + kp1y*kp1y + kp1z*kp1z)>>hMomentaK1Gen");
	tGen->Draw("sqrt(kp1t*kp1t -  0.493677*0.493677)>>hMomentaK1Gen");
	cGen->cd(2);
	tGen->Draw("sqrt(kp2t*kp2t -  0.493677*0.493677)>>hMomentaK2Gen");
	cGen->cd(3);
	tGen->Draw("sqrt(pim1t*pim1t -  0.13957018*0.13957018)>>hMomentaPimGen");

}




void PlotAngles()
{
	float temp1,temp2,normfac;
	StyleUp();
	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Xi angle integrated~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TCanvas *cCompareXiAnglesINT=new TCanvas("cCompareXiAnglesINT","cCompareXiAnglesINT",1200,800);
	cblank->cd(0);
	//hist model
	TH1F *hAnglesINT=new TH1F("hAnglesINT","",25,-1,1);
	hAnglesINT->SetMinimum(0);
	hAnglesINT->SetMarkerStyle(21);

	//Data and MC hists
	TH1F* hXiAnglesINTData;
	TH1F* hXiAnglesINTMC;

	cCompareXiAnglesINT->cd(0);
	hXiAnglesINTData = (TH1F*)hAnglesINT->Clone("hXiAnglesINTData");
	hXiAnglesINTData->SetMinimum(0);
	hXiAnglesINTData->GetYaxis()->SetTitle("Events");
	hXiAnglesINTData->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");

	//MC hist
	hXiAnglesINTMC = (TH1F*)hAnglesINT->Clone("hXiAnglesINTMC");
	hXiAnglesINTMC->SetMinimum(0);
	hXiAnglesINTMC->GetYaxis()->SetTitle("Events");
	hXiAnglesINTMC->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");

	tData->Draw("Xcmtheta>>hXiAnglesINTData");
	tMC->Draw("Xcmtheta>>hXiAnglesINTMC");
	temp1 = hXiAnglesINTData->GetEntries();
	temp2 = hXiAnglesINTMC->GetEntries();
	normfac = temp1/temp2;
	hXiAnglesINTMC->Add(hXiAnglesINTMC, normfac - 1);

	hXiAnglesINTData->SetMarkerStyle(21);
	hXiAnglesINTData->SetFillColor(3);
	hXiAnglesINTData->Draw("E");
	hXiAnglesINTMC->SetMarkerStyle(21);
	hXiAnglesINTMC->SetFillStyle(3002);
	hXiAnglesINTMC->SetFillColor(2);
	hXiAnglesINTMC->Draw("SAME");

	cblank->cd(0);

	cCompareXiAnglesINT->Print("~/Desktop/cmangle.png");




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Xi angle seperate~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TCanvas *cCompareXiAngles=new TCanvas("cCompareXiAngles","cCompareXiAngles",1200,800);
	cCompareXiAngles->Divide(4,2);
	cblank->cd(0);
	//hist model
	TH1F *hAngles=new TH1F("hAngles","",25,-1,1);
	hAngles->SetMinimum(0);
	hAngles->SetMarkerStyle(21);


	Double_t emin = 2.8;
    Double_t emax = 5.5;
    const Int_t Nebins = 8;
    Double_t estep = (emax - emin)/Nebins;
	TCut ebin[Nebins];
	for (int i=0;i<Nebins;i++)
	{
		ebin[i] = Form("beam >= 2.8 + %f && beam <= 2.8 + %f",i*estep,(i+1)*estep);
		cout << Form("beam >= 2.8 + %f && beam <= 2.8 + %f",i*estep,(i+1)*estep) <<endl;
	}

	//Data and MC hists
	TH1F* hXiAnglesData[Nebins];
	TH1F* hXiAnglesMC[Nebins];
	for (int i=0; i<Nebins; i++)
	{
		cCompareXiAngles->cd(i + 1);
		hXiAnglesData[i] = (TH1F*)hAngles->Clone(Form("hXiAnglesData-E%i",i));
		hXiAnglesData[i]->SetMinimum(0);
		hXiAnglesData[i]->GetYaxis()->SetTitle("Events");
		hXiAnglesData[i]->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");
		//MC hist
		hXiAnglesMC[i] = (TH1F*)hAngles->Clone(Form("hXiAnglesMC-E%i",i));
		hXiAnglesMC[i]->SetMinimum(0);
		hXiAnglesMC[i]->GetYaxis()->SetTitle("Events");
		hXiAnglesMC[i]->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");


		tData->Draw(Form("Xcmtheta>>hXiAnglesData-E%i",i),ebin[i]);
		tMC->Draw(Form("Xcmtheta>>hXiAnglesMC-E%i",i),ebin[i]);
		temp1 = hXiAnglesData[i]->GetEntries();
		temp2 = hXiAnglesMC[i]->GetEntries();
		normfac = temp1/temp2;
		hXiAnglesMC[i]->Add(hXiAnglesMC[i], normfac - 1);

		hXiAnglesData[i]->SetMarkerStyle(21);
		hXiAnglesData[i]->SetFillColor(3);
		hXiAnglesData[i]->Draw("E");
		hXiAnglesMC[i]->SetMarkerStyle(21);
		hXiAnglesMC[i]->SetFillStyle(3002);
		hXiAnglesMC[i]->SetFillColor(2);
		hXiAnglesMC[i]->Draw("SAME");
	}

	//cCompareXiAngles->Print("./pics/CompareXiAngles_overlay.eps");
	cblank->cd(0);
	//..................................................................................................


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~kaon angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hAngles=new TH1F("hAngles","",25,0,1);
	hAngles->SetMinimum(0);
	hAngles->SetMarkerStyle(21);
	//Data
	hKaonAnglesData = (TH1F*)hAngles->Clone("hKaonAnglesData");
	hKaonAnglesData->SetMinimum(0);
	hKaonAnglesData->GetYaxis()->SetTitle("Events");
	hKaonAnglesData->GetXaxis()->SetTitle("#Theta^{Kaons}_{cm} ");
	//MC
	hKaonAnglesMC = (TH1F*)hAngles->Clone("hKaonAnglesMC");
	hKaonAnglesMC->SetMinimum(0);
	hKaonAnglesMC->GetYaxis()->SetTitle("Events");
	hKaonAnglesMC->GetXaxis()->SetTitle("#Theta^{Kaons}_{cm}");


	cblank->cd(0);

	tData->Draw("(sin(kp1labtheta)*sin(kp2labtheta)*cos(kp1labphi)*cos(kp2labphi) + sin(kp1labtheta)*sin(kp2labtheta)*sin(kp1labphi)*sin(kp2labphi) + cos(kp1labtheta)*cos(kp2labtheta))>>hKaonAnglesData");
	tMC->Draw("(sin(kp1labtheta)*sin(kp2labtheta)*cos(kp1labphi)*cos(kp2labphi) + sin(kp1labtheta)*sin(kp2labtheta)*sin(kp1labphi)*sin(kp2labphi) + cos(kp1labtheta)*cos(kp2labtheta))>>hKaonAnglesMC");
	temp1 = hKaonAnglesData->GetEntries();
	temp2 = hKaonAnglesMC->GetEntries();
	normfac = temp1/temp2;
	hKaonAnglesMC->Add(hKaonAnglesMC, normfac - 1);


	//for thesis
	TCanvas *cCompareKaonAngles=new TCanvas("cCompareKaonAngles","cCompareKaonAngles",1200,800);
	hKaonAnglesData->SetMarkerStyle(21);
	hKaonAnglesData->SetFillColor(3);
	hKaonAnglesData->SetMaximum(hKaonAnglesMC->GetMaximum());
	hKaonAnglesData->Draw("E");
	hKaonAnglesMC->SetMarkerStyle(21);
	hKaonAnglesMC->SetFillStyle(3002);
	hKaonAnglesMC->SetFillColor(2);
	hKaonAnglesMC->Draw("SAME");

	cCompareKaonAngles->Print("~/Desktop/kkangle.png");
	cblank->cd(0);
//	gROOT->ProcessLine(".q");
}



















void PlotK2Angles()
{
	float temp1,temp2,normfac;
	StyleUp();

	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Kslow angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hAngles[2];
	hAngles[0] = new TH1F("hAngles","",100,0,1);
	hAngles[0]->SetMinimum(0);
	hAngles[0]->SetMarkerStyle(21);
	hAngles[1] = new TH1F("hAngles","",100,-1,1);
	hAngles[1]->SetMinimum(0);
	hAngles[1]->SetMarkerStyle(21);


	//////////////////////SEPERATE EXi BINS////////////////////////////////
	TH1F* hK2Data[Nb][Nc][Nd];
	TH1F* hK2MC[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < 2; d++)
			{
				hK2Data[b][c][d] = (TH1F*)hAngles[d]->Clone(Form("hK2Data-%sBin%s-K2%s",BinType[b],BinNumber[c],angletype[d]));
				hK2Data[b][c][d]->GetYaxis()->SetTitle("Events");
				hK2Data[b][c][d]->GetXaxis()->SetTitle(Form("#%s_{K_{slow}} %sBin%s ",angletype[d],BinType[b],BinNumber[c]));
				tData->Draw(Form("kp2lab%s>>hK2Data-%sBin%s-K2%s",angletype[d],BinType[b],BinNumber[c],angletype[d]),EXibin[b][c]);
				hK2MC[b][c][d] = (TH1F*)hAngles[d]->Clone(Form("hK2MC-%sBin%s-K2%s",BinType[b],BinNumber[c],angletype[d]));
				tMC->Draw(Form("kp2lab%s>>hK2MC-%sBin%s-K2%s",angletype[d],BinType[b],BinNumber[c],angletype[d]),EXibin[b][c]);

				temp1 = hK2Data[b][c][d]->GetEntries();
				temp2 = hK2MC[b][c][d]->GetEntries();
				normfac = temp1/temp2;
				hK2MC[b][c][d]->Add(hK2MC[b][c][d], normfac - 1);
			}
		}
	}

	TCanvas* cK2[2];
	for (int d = 0; d < 2; d++)
	{
		cK2[d] = new TCanvas(Form("cK2%s",angletype[d]),Form("cK2%s",angletype[d]),1200,800);
		cK2[d]->Divide(3,2);
	}

	int counter = 1;
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < 2; d++)
			{
				cK2[d]->cd(counter);
				hK2Data[b][c][d]->SetMarkerStyle(21);
				hK2Data[b][c][d]->SetFillColor(3);
				hK2Data[b][c][d]->Draw();
				hK2MC[b][c][d]->SetMarkerStyle(21);
				hK2MC[b][c][d]->SetFillStyle(3002);
				hK2MC[b][c][d]->SetFillColor(2);
				hK2MC[b][c][d]->Draw("SAME");
			}
			counter += 1;
		}
	}
	cblank->cd(0);



	/////////////////////INTEGRATED BINS////////////////////////////////
	//Data
	hK2xData = (TH1F*)hAngles[0]->Clone("hK2xData");
	hK2xData->SetMinimum(0);
	hK2xData->GetYaxis()->SetTitle("Events");
	hK2xData->GetXaxis()->SetTitle("#Theta_{K_{slow}^{-}}_{x} ");
	hK2yData = (TH1F*)hAngles[1]->Clone("hK2yData");
	hK2yData->SetMinimum(0);
	hK2yData->GetYaxis()->SetTitle("Events");
	hK2yData->GetXaxis()->SetTitle("#Theta_{K_{slow}^{-}}_{y} ");
	//MC
	hK2xMC = (TH1F*)hK2xData->Clone("hK2xMC");
	hK2yMC = (TH1F*)hK2yData->Clone("hK2yMC");


	//fill the hists
	cblank->cd(0);

	tData->Draw("kp2labtheta>>hK2xData");
	tData->Draw("kp2labphi>>hK2yData");
	tMC->Draw("kp2labtheta>>hK2xMC");
	tMC->Draw("kp2labphi>>hK2yMC");

	temp1 = hK2xData->GetEntries();
	temp2 = hK2xMC->GetEntries();
	normfac = temp1/temp2;
	hK2xMC->Add(hK2xMC, normfac - 1);
	temp1 = hK2yData->GetEntries();
	temp2 = hK2yMC->GetEntries();
	normfac = temp1/temp2;
	hK2yMC->Add(hK2yMC, normfac - 1);

	//Draw nice for thesis
	TCanvas *cK2Integrated=new TCanvas("cK2Integrated","cK2Integrated",1200,800);
	cK2Integrated->Divide(2,1);
	hK2xData->SetMarkerStyle(21);
	hK2xData->SetFillColor(3);
	hK2yData->SetMarkerStyle(21);
	hK2yData->SetFillColor(3);

	cK2Integrated->cd(1);
	hK2xData->Draw();
	cK2Integrated->cd(2);
	hK2yData->Draw();
	cK2Integrated->cd(3);

	hK2xMC->SetMarkerStyle(21);
	hK2xMC->SetFillStyle(3002);
	hK2xMC->SetFillColor(2);
	hK2yMC->SetMarkerStyle(21);
	hK2yMC->SetFillStyle(3002);
	hK2yMC->SetFillColor(2);
	cK2Integrated->cd(1);
	hK2xMC->Draw("SAME");
	cK2Integrated->cd(2);
	hK2yMC->Draw("SAME");
	//cK2Integrated->Print("./pics/CompareK2Angles_overlay.eps");
	cblank->cd(0);
}
	//............................................................................................................................................................................



























void PlotPionAngles()
{
	float temp1,temp2,normfac;
	StyleUp();

	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Kslow angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hAngles[2];
	hAngles[0] = new TH1F("hAngles","",100,0,1);
	hAngles[0]->SetMinimum(0);
	hAngles[0]->SetMarkerStyle(21);
	hAngles[1] = new TH1F("hAngles","",100,-1,1);
	hAngles[1]->SetMinimum(0);
	hAngles[1]->SetMarkerStyle(21);


	//////////////////////SEPERATE EXi BINS////////////////////////////////
	TH1F* hpionData[Nb][Nc][Nd];
	TH1F* hpionMC[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < 2; d++)
			{
				hpionData[b][c][d] = (TH1F*)hAngles[d]->Clone(Form("hpionData-%sBin%s-pion%s",BinType[b],BinNumber[c],angletype[d]));
				hpionData[b][c][d]->GetYaxis()->SetTitle("Events");
				hpionData[b][c][d]->GetXaxis()->SetTitle(Form("#%s_{#pi^{-}} %sBin%s ",angletype[d],BinType[b],BinNumber[c]));
				tData->Draw(Form("pilab%s>>hpionData-%sBin%s-pion%s",angletype[d],BinType[b],BinNumber[c],angletype[d]),EXibin[b][c]&&"hel==-1");
				hpionMC[b][c][d] = (TH1F*)hAngles[d]->Clone(Form("hpionMC-%sBin%s-pion%s",BinType[b],BinNumber[c],angletype[d]));
				tMC->Draw(Form("pilab%s>>hpionMC-%sBin%s-pion%s",angletype[d],BinType[b],BinNumber[c],angletype[d]),EXibin[b][c]);

				temp1 = hpionData[b][c][d]->GetEntries();
				temp2 = hpionMC[b][c][d]->GetEntries();
				normfac = temp1/temp2;
				hpionMC[b][c][d]->Add(hpionMC[b][c][d], normfac - 1);
			}
		}
	}

	TCanvas* cpion[2];
	for (int d = 0; d < 2; d++)
	{
		cpion[d] = new TCanvas(Form("cpion%s",angletype[d]),Form("cpion%s",angletype[d]),1200,800);
		cpion[d]->Divide(3,2);
	}

	int counter = 1;
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < 2; d++)
			{
				cpion[d]->cd(counter);
				hpionData[b][c][d]->SetMarkerStyle(21);
				hpionData[b][c][d]->SetFillColor(3);
				hpionData[b][c][d]->Draw();
				hpionMC[b][c][d]->SetMarkerStyle(21);
				hpionMC[b][c][d]->SetFillStyle(3002);
				hpionMC[b][c][d]->SetFillColor(2);
				hpionMC[b][c][d]->Draw("SAME");
			}
			counter += 1;
		}
	}
	cblank->cd(0);



	/////////////////////INTEGRATED BINS////////////////////////////////
	//Data
	hpionxData = (TH1F*)hAngles[0]->Clone("hpionxData");
	hpionxData->SetMinimum(0);
	hpionxData->GetYaxis()->SetTitle("Events");
	hpionxData->GetXaxis()->SetTitle("#Theta_{#pi}_{x} ");
	hpionyData = (TH1F*)hAngles[1]->Clone("hpionyData");
	hpionyData->SetMinimum(0);
	hpionyData->GetYaxis()->SetTitle("Events");
	hpionyData->GetXaxis()->SetTitle("#Theta_{#pi}_{y} ");
	//MC
	hpionxMC = (TH1F*)hpionxData->Clone("hpionxMC");
	hpionyMC = (TH1F*)hpionyData->Clone("hpionyMC");


	//fill the hists
	cblank->cd(0);

	tData->Draw("pilabtheta>>hpionxData");
	tData->Draw("pilabphi>>hpionyData");
	tMC->Draw("pilabtheta>>hpionxMC");
	tMC->Draw("pilabphi>>hpionyMC");

	temp1 = hpionxData->GetEntries();
	temp2 = hpionxMC->GetEntries();
	normfac = temp1/temp2;
	hpionxMC->Add(hpionxMC, normfac - 1);
	temp1 = hpionyData->GetEntries();
	temp2 = hpionyMC->GetEntries();
	normfac = temp1/temp2;
	hpionyMC->Add(hpionyMC, normfac - 1);

	//Draw nice for thesis
	TCanvas *cpionIntegrated=new TCanvas("cpionIntegrated","cpionIntegrated",1200,800);
	cpionIntegrated->Divide(2,1);
	hpionxData->SetMarkerStyle(21);
	hpionxData->SetFillColor(3);
	hpionyData->SetMarkerStyle(21);
	hpionyData->SetFillColor(3);

	cpionIntegrated->cd(1);
	hpionxData->Draw();
	cpionIntegrated->cd(2);
	hpionyData->Draw();
	cpionIntegrated->cd(3);

	hpionxMC->SetMarkerStyle(21);
	hpionxMC->SetFillStyle(3002);
	hpionxMC->SetFillColor(2);
	hpionyMC->SetMarkerStyle(21);
	hpionyMC->SetFillStyle(3002);
	hpionyMC->SetFillColor(2);
	cpionIntegrated->cd(1);
	hpionxMC->Draw("SAME");
	cpionIntegrated->cd(2);
	hpionyMC->Draw("SAME");
	//cpionIntegrated->Print("./pics/ComparepionAngles_overlay.eps");
	cblank->cd(0);
}
	//............................................................................................................................................................................



































void PlotGotfriedAngles()
{
	float temp1,temp2,normfac;
	StyleUp();

	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pion angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hAngles=new TH1F("hAngles","",25,-1,1);
	hAngles->SetMinimum(0);
	hAngles->SetMarkerStyle(21);


	//////////////////////SEPERATE EXi BINS////////////////////////////////
	TH1F* hPiData[Nb][Nc][Nd];
	TH1F* hPiMC[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				hPiData[b][c][d] = (TH1F*)hAngles->Clone(Form("hPiData-%sBin%s-PiAxis%s",BinType[b],BinNumber[c],Axis[d]));
				hPiData[b][c][d]->GetYaxis()->SetTitle("Events");
				hPiData[b][c][d]->GetXaxis()->SetTitle(Form("#Theta^{#pi^{-}}_{%s}  %sBin%s ",Axis[d],BinType[b],BinNumber[c]));
				tData->Draw(Form("COS_pi_%s>>hPiData-%sBin%s-PiAxis%s",Axis[d],BinType[b],BinNumber[c],Axis[d]),EXibin[b][c]);
				hPiMC[b][c][d] = (TH1F*)hAngles->Clone(Form("hPiMC-%sBin%s-PiAxis%s",BinType[b],BinNumber[c],Axis[d]));
				tMC->Draw(Form("COS_pi_%s>>hPiMC-%sBin%s-PiAxis%s",Axis[d],BinType[b],BinNumber[c],Axis[d]),EXibin[b][c]);

				temp1 = hPiData[b][c][d]->GetEntries();
				temp2 = hPiMC[b][c][d]->GetEntries();
				normfac = temp1/temp2;
				hPiMC[b][c][d]->Add(hPiMC[b][c][d], normfac - 1);
			}
		}
	}

	TCanvas* cPi[Nd];
	for (int d = 0; d < Nd; d++)
	{
		cPi[d] = new TCanvas(Form("cPi%s",Axis[d]),Form("cPi%s",Axis[d]),1200,800);
		cPi[d]->Divide(3,2);
	}

	int counter = 1;
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				cPi[d]->cd(counter);
				hPiData[b][c][d]->SetMarkerStyle(21);
				hPiData[b][c][d]->SetFillColor(3);
				hPiData[b][c][d]->Draw();

				hPiMC[b][c][d]->SetMarkerStyle(21);
				hPiMC[b][c][d]->SetFillStyle(3002);
				hPiMC[b][c][d]->SetFillColor(2);
				hPiMC[b][c][d]->Draw("SAME");

			}
			counter += 1;
		}
	}
	cblank->cd(0);



	/////////////////////INTEGRATED BINS////////////////////////////////
	//Data
	hPixData = (TH1F*)hAngles->Clone("hPixData");
	hPixData->SetMinimum(0);
	hPixData->GetYaxis()->SetTitle("Events");
	hPixData->GetXaxis()->SetTitle("#Theta^{#pi^{-}}_{x} ");
	hPiyData = (TH1F*)hAngles->Clone("hPiyData");
	hPiyData->SetMinimum(0);
	hPiyData->GetYaxis()->SetTitle("Events");
	hPiyData->GetXaxis()->SetTitle("#Theta^{#pi^{-}}_{y} ");
	hPizData = (TH1F*)hAngles->Clone("hPizData");
	hPizData->SetMinimum(0);
	hPizData->GetYaxis()->SetTitle("Events");
	hPizData->GetXaxis()->SetTitle("#Theta^{#pi^{-}}_{z} ");
	//MC
	hPixMC = (TH1F*)hPixData->Clone("hPixMC");
	hPiyMC = (TH1F*)hPiyData->Clone("hPiyMC");
	hPizMC = (TH1F*)hPizData->Clone("hPizMC");


	//fill the hists
	cblank->cd(0);

	tData->Draw("COS_pi_x>>hPixData");
	tData->Draw("COS_pi_y>>hPiyData");
	tData->Draw("COS_pi_z>>hPizData");
	tMC->Draw("COS_pi_x>>hPixMC");
	tMC->Draw("COS_pi_y>>hPiyMC");
	tMC->Draw("COS_pi_z>>hPizMC");

	temp1 = hPixData->GetEntries();
	temp2 = hPixMC->GetEntries();
	normfac = temp1/temp2;
	hPixMC->Add(hPixMC, normfac - 1);
	temp1 = hPiyData->GetEntries();
	temp2 = hPiyMC->GetEntries();
	normfac = temp1/temp2;
	hPiyMC->Add(hPiyMC, normfac - 1);
	temp1 = hPizData->GetEntries();
	temp2 = hPizMC->GetEntries();
	normfac = temp1/temp2;
	hPizMC->Add(hPizMC, normfac - 1);




	//Draw nice for thesis
	TCanvas *cPiIntegrated=new TCanvas("cPiIntegrated","cPiIntegrated",1200,800);
	cPiIntegrated->Divide(2,2);
	hPixData->SetMarkerStyle(21);
	hPixData->SetFillColor(3);
	hPiyData->SetMarkerStyle(21);
	hPiyData->SetFillColor(3);
	hPizData->SetMarkerStyle(21);
	hPizData->SetFillColor(3);
	cPiIntegrated->cd(1);
	hPixData->Draw();
	cPiIntegrated->cd(2);
	hPiyData->Draw();
	cPiIntegrated->cd(3);
	hPizData->Draw();
	hPixMC->SetMarkerStyle(21);
	hPixMC->SetFillStyle(3002);
	hPixMC->SetFillColor(2);
	hPiyMC->SetMarkerStyle(21);
	hPiyMC->SetFillStyle(3002);
	hPiyMC->SetFillColor(2);
	hPizMC->SetMarkerStyle(21);
	hPizMC->SetFillStyle(3002);
	hPizMC->SetFillColor(2);
	cPiIntegrated->cd(1);
	hPixMC->Draw("SAME");
	cPiIntegrated->cd(2);
	hPiyMC->Draw("SAME");
	cPiIntegrated->cd(3);
	hPizMC->Draw("SAME");
	//cPiIntegrated->Print("./pics/ComparePiAngles_overlay.eps");
	cblank->cd(0);
}
	//............................................................................................................................................................................






void PlotMomenta()
{
	float temp1,temp2,normfac;
	StyleUp();

	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.9);
	gStyle->SetTitleSize(0.08);
	gStyle->SetTitleYSize(0.05);
	gStyle->SetLabelSize(0.05);

	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);

	//*///<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Kp1 momentum spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMomenta=new TH1F("hMomenta","",30,0,3); // 3000/30 = 100MeV
	hMomenta->GetYaxis()->SetLabelSize(0.05);
	hMomenta->SetMinimum(0);
	hMomenta->SetMarkerStyle(21);
	//Data
	hMomentaK1Data = (TH1F*)hMomenta->Clone("hMomentaK1Data");
	hMomentaK1Data->SetMinimum(0);
	hMomentaK1Data->GetYaxis()->SetTitle("Events/100MeV");
	hMomentaK1Data->GetXaxis()->SetTitle("p^{k^{+}_{fast}} (GeV/c) ");
	//MC
	hMomentaK1MC = (TH1F*)hMomenta->Clone("hMomentaK1MC");
	hMomentaK1MC->SetMinimum(0);
	hMomentaK1MC->GetYaxis()->SetTitle("Events");
	hMomentaK1MC->GetXaxis()->SetTitle("p^{k^{+}_{fast}} (GeV/c)");

	//draw the hists
	cblank->cd(0);
	tData->Draw("pkp1>>hMomentaK1Data");
	tMC->Draw("pkp1>>hMomentaK1MC");
	temp1 = hMomentaK1Data->GetEntries();
	temp2 = hMomentaK1MC->GetEntries();
	normfac = temp1/temp2;
	hMomentaK1MC->Add(hMomentaK1MC, normfac - 1);

	cblank->cd(0);

	//for thesis
	TCanvas *cCompareMomentaK1=new TCanvas("cCompareMomentaK1","cCompareMomentaK1",1200,800);
	cCompareMomentaK1->Divide(3,0);
	cCompareMomentaK1->cd(1);
	hMomentaK1Data->SetMarkerStyle(21);
	hMomentaK1Data->SetFillColor(3);
	hMomentaK1Data->Draw("E");
	hMomentaK1MC->SetMarkerStyle(21);
	hMomentaK1MC->SetFillStyle(3002);
	hMomentaK1MC->SetFillColor(2);
	hMomentaK1MC->Draw("SAME");
	//cCompareMomentaK1->Print("./pics/CompareMomentaK1_overlay.eps");
	cblank->cd(0);
	//*///..................................................................................................


	//*///<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Kp2 momentum spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMomenta=new TH1F("hMomenta","",30,0,3);  // 3000 / 30 = 100MeV
	hMomenta->GetYaxis()->SetLabelSize(0.05);
	hMomenta->SetMinimum(0);
	hMomenta->SetMarkerStyle(21);
	//Data
	hMomentaK2Data = (TH1F*)hMomenta->Clone("hMomentaK2Data");
	hMomentaK2Data->SetMinimum(0);
	hMomentaK2Data->GetYaxis()->SetTitle("Events/100MeV");
	hMomentaK2Data->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c) ");
	//MC
	hMomentaK2MC = (TH1F*)hMomenta->Clone("hMomentaK2MC");
	hMomentaK2MC->SetMinimum(0);
	hMomentaK2MC->GetYaxis()->SetTitle("Events");
	hMomentaK2MC->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c)");

	//draw the hists
	cblank->cd(0);
	tData->Draw("pkp2>>hMomentaK2Data");
	tMC->Draw("pkp2>>hMomentaK2MC");

	temp1 = hMomentaK2Data->GetEntries();
	temp2 = hMomentaK2MC->GetEntries();
	normfac = temp1/temp2;
	hMomentaK2MC->Add(hMomentaK2MC, normfac - 1);

	cblank->cd(0);
	//for thesis
	//TCanvas *cCompareMomentaK2=new TCanvas("cCompareMomentaK2","cCompareMomentaK2",1200,800);
	cCompareMomentaK1->cd(2);
	hMomentaK2Data->SetMarkerStyle(21);
	hMomentaK2Data->SetFillColor(3);
	hMomentaK2Data->Draw("E");
	hMomentaK2MC->SetMarkerStyle(21);
	hMomentaK2MC->SetFillStyle(3002);
	hMomentaK2MC->SetFillColor(2);
	hMomentaK2MC->Draw("SAME");
	//cCompareMomentaK2->Print("./pics/CompareMomentaK2_overlay.eps");
	cblank->cd(0);
	//gROOT->ProcessLine(".q");



	//<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~pim momentum spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMomenta=new TH1F("hMomenta","",10,0,1);  // 3000 / 30 = 100MeV
	hMomenta->GetYaxis()->SetLabelSize(0.05);
	hMomenta->SetMinimum(0);
	hMomenta->SetMarkerStyle(21);
	//Data
	hMomentaPIData = (TH1F*)hMomenta->Clone("hMomentaPIData");
	hMomentaPIData->SetMinimum(0);
	hMomentaPIData->GetYaxis()->SetTitle("Events/100MeV");
	hMomentaPIData->GetXaxis()->SetTitle("p^{#pi^{-}} (GeV/c) ");
	//MC
	hMomentaPIMC = (TH1F*)hMomenta->Clone("hMomentaPIMC");
	hMomentaPIMC->SetMinimum(0);
	hMomentaPIMC->GetYaxis()->SetTitle("Events");
	hMomentaPIMC->GetXaxis()->SetTitle("p^{#pi^{-}} (GeV/c)");

	//draw the hists
	cblank->cd(0);
	tData->Draw("ppim>>hMomentaPIData");
	tMC->Draw("ppim>>hMomentaPIMC");

	temp1 = hMomentaPIData->GetEntries();
	temp2 = hMomentaPIMC->GetEntries();
	normfac = temp1/temp2;
	hMomentaPIMC->Add(hMomentaPIMC, normfac - 1);

	cblank->cd(0);
	//for thesis
	//TCanvas *cCompareMomentaPI=new TCanvas("cCompareMomentaPI","cCompareMomentaPI",1200,800);
	cCompareMomentaK1->cd(3);
	hMomentaPIData->SetMarkerStyle(21);
	hMomentaPIData->SetFillColor(3);
	hMomentaPIData->Draw("E");
	hMomentaPIMC->SetMarkerStyle(21);
	hMomentaPIMC->SetFillStyle(3002);
	hMomentaPIMC->SetFillColor(2);
	hMomentaPIMC->Draw("SAME");
	cCompareMomentaK1->Print("~/Desktop/p.png");
	cblank->cd(0);
	//gROOT->ProcessLine(".q");


	//cCompareMomentaK1->Print("~/Desktop/FundPics/Momentum.eps");
}
	//*///..................................................................................................









void PlotMass()
{
	float temp1,temp2,normfac;
	StyleUp();



	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~mmkpkp~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMass=new TH1F("hMass","",300,1,1.4);  // 1200/60 = 20 MeV
	hMass->SetMinimum(0);
	hMass->SetMarkerStyle(21);



	const char* quantity[4] = {"mmkpkp","mmkpkppim","mlampim","mcasmMpim"};


	TH1F *hData[4],*hMC[4];
	TCanvas *cMass=new TCanvas("cMass","cMass",1200,800);
	cMass->Divide(2,2);

	for (int i = 0; i<4; i++ )
	{
		hData[i] = (TH1F*)hMass->Clone(Form("h%i-Data",i));
		hData[i]->SetMinimum(0);
		hData[i]->GetYaxis()->SetTitle("Events");
		hData[i]->GetXaxis()->SetTitle(" (GeV/c^2)");

		hMC[i] = (TH1F*)hMass->Clone(Form("h%i-MC",i));
		hMC[i]->SetMinimum(0);
		hMC[i]->GetYaxis()->SetTitle("Events");
		hMC[i]->GetXaxis()->SetTitle(" (GeV/c^2)");


		cblank->cd(0);
		tDataB->Draw(Form("%s>>h%i-Data",quantity[i],i));
		tMCB->Draw(Form("%s>>h%i-MC",quantity[i],i));
		//temp1 = hData[i]->GetEntries();
		//temp2 = hMC[i]->GetEntries();
		//normfac = temp1/temp2;
		//hMC[i]->Add(hMC[i], normfac - 1);


		cMass->cd(i + 1);


		hData[i]->SetMarkerStyle(21);
		hData[i]->SetFillColor(3);
		hData[i]->Draw();
		hMC[i]->SetMarkerStyle(21);
		hMC[i]->SetFillStyle(3002);
		hMC[i]->SetFillColor(2);
		hMC[i]->Draw("SAME");
	}
	cblank->cd(0);



}






void PlotResMass()
{
	float temp1,temp2,normfac;
	StyleUp();

	//get cuts

	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Xi- + Kp1 mass spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMass=new TH1F("hMass","",60,1.8,3);  // 1200/60 = 20 MeV
	hMass->SetMinimum(0);
	hMass->SetMarkerStyle(21);
	//Data
	hMassK1XiData = (TH1F*)hMass->Clone("hMassK1XiData");
	hMassK1XiData->SetMinimum(0);
	hMassK1XiData->GetYaxis()->SetTitle("Events/20 MeV");
	hMassK1XiData->GetXaxis()->SetTitle("m(#Xi^{-} K^{+}_{fast}) (GeV/c^{2})");
	//MC
	hMassK1XiMC = (TH1F*)hMass->Clone("hMassK1XiMC");
	hMassK1XiMC->SetMinimum(0);
	hMassK1XiMC->GetYaxis()->SetTitle("Events");
	hMassK1XiMC->GetXaxis()->SetTitle("m(#Xi^{-} K^{+}_{fast}) (GeV/c^{2}) ");




	//draw the hists
	cblank->cd(0);
	tData->Draw("mcasmkp1>>hMassK1XiData");
if(0==1){
	tMC->Draw("mcasmkp1>>hMassK1XiMC");
	temp1 = hMassK1XiData->GetEntries();
	temp2 = hMassK1XiMC->GetEntries();
	normfac = temp1/temp2;
	hMassK1XiMC->Add(hMassK1XiMC, normfac - 1);
}
	cblank->cd(0);


	//for thesis
	TCanvas *cCompareMassK1Xi=new TCanvas("cCompareMassK1Xi","cCompareMassK1Xi",1200,800);
	hMassK1XiData->SetMarkerStyle(21);
	hMassK1XiData->SetFillColor(3);
	hMassK1XiData->Draw("E");
	hMassK1XiMC->SetMarkerStyle(21);
	hMassK1XiMC->SetFillStyle(3002);
	hMassK1XiMC->SetFillColor(2);
	hMassK1XiMC->Draw("SAME");
	cCompareMassK1Xi->Print("~/Desktop/mk1xi.png");
	cblank->cd(0);
	//..................................................................................................


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Xi- + Kp2 mass spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMass=new TH1F("hMass","",85,1.8,2.5); // 1700/85 = 20 MeV
	hMass->SetMinimum(0);
	hMass->SetMarkerStyle(21);
	//Data
	hMassK2XiData = (TH1F*)hMass->Clone("hMassK2XiData");
	hMassK2XiData->SetMinimum(0);
	hMassK2XiData->GetYaxis()->SetTitle("Events/20 MeV");
	hMassK2XiData->GetXaxis()->SetTitle(" m(#Xi^{-} K^{+}_{slow}) (GeV/c^{2}) ");
	//MC
	hMassK2XiMC = (TH1F*)hMass->Clone("hMassK2XiMC");
	hMassK2XiMC->SetMinimum(0);
	hMassK2XiMC->GetYaxis()->SetTitle("Events");
	hMassK2XiMC->GetXaxis()->SetTitle("m(#Xi^{-} K^{+}_{slow}) (GeV/{c})");


	//draw the hists
	cblank->cd(0);
	tData->Draw("mcasmkp2>>hMassK2XiData");
if(0==1){
	tMC->Draw("mcasmkp2>>hMassK2XiMC");
	temp1 = hMassK2XiData->GetEntries();
	temp2 = hMassK2XiMC->GetEntries();
	normfac = temp1/temp2;
	hMassK2XiMC->Add(hMassK2XiMC, normfac - 1);
}

	cblank->cd(0);

	TCanvas *cCompareMassK2Xi=new TCanvas("cCompareMassK2Xi","cCompareMassK2Xi",1200,800);
	hMassK2XiData->SetMarkerStyle(21);
	hMassK2XiData->SetFillColor(3);
	hMassK2XiData->Draw("E");
	hMassK2XiMC->SetMarkerStyle(21);
	hMassK2XiMC->SetFillStyle(3002);
	hMassK2XiMC->SetFillColor(2);
	hMassK2XiMC->Draw("SAME");
	cCompareMassK2Xi->Print("./pics/CompareMassK2Xi_overlay.eps");
	cCompareMassK2Xi->Print("~/Desktop/mk2xi.png");

	///// plot two energy bins side by side
	TH1F *hMass=new TH1F("hMass","",45,1.8,2.6); // 1800/85 = 40 MeV
	hMass->SetMinimum(0);
	hMass->SetMarkerStyle(21);


	hReselow = (TH1F*)hMass->Clone("hReselow");
	hReselow->SetMinimum(0);
	hReselow->GetYaxis()->SetTitle("Events/40 MeV");
	hReselow->GetXaxis()->SetTitle(" m(#Xi^{-} k^{+}_{slow}) (GeV/c^2) ");
	hReselow->SetTitle("E_{#gamma} < 4 GeV");
	hReselowMC = (TH1F*)hReselow->Clone("hReselowMC");
	hResehigh = (TH1F*)hReselow->Clone("hResehigh");
	hResehigh->SetTitle("E_{#gamma} > 4 GeV");
	hResehighMC = (TH1F*)hResehigh->Clone("hResehighMC");




	cblank->cd(0);
	TCut elow = "beam < 4";
	TCut ehigh = "beam > 4";
	tData->Draw("mcasmkp2>>hReselow",elow);
	tData->Draw("mcasmkp2>>hResehigh",ehigh);
	tMC->Draw("mcasmkp2>>hReselowMC",elow);
	tMC->Draw("mcasmkp2>>hResehighMC",ehigh);

	temp1 = hReselow->GetEntries();
	temp2 = hReselowMC->GetEntries();
	normfac = temp1/temp2;
	hReselowMC->Add(hReselowMC, normfac - 1);

	temp1 = hResehigh->GetEntries();
	temp2 = hResehighMC->GetEntries();
	normfac = temp1/temp2;
	hResehighMC->Add(hResehighMC, normfac - 1);



	TCanvas *cRes=new TCanvas("cRes","cRes",1200,800);
	cRes->Divide(2,1);
	cRes->cd(1);
	hReselow->SetMarkerStyle(21);
	hReselow->SetFillColor(3);
	hReselow->Draw("E");
	hReselowMC->SetMarkerStyle(21);
	hReselowMC->SetFillStyle(3002);
	hReselowMC->SetFillColor(2);
	//hReselowMC->Draw("SAME");
	cRes->cd(2);
	hResehigh->SetMarkerStyle(21);
	hResehigh->SetFillColor(3);
	hResehigh->Draw("E");
	hResehighMC->SetMarkerStyle(21);
	hResehighMC->SetFillStyle(3002);
	hResehighMC->SetFillColor(2);
	//hResehighMC->Draw("SAME");


	cRes->Print("~/Desktop/resmass_bins.png");



	TCanvas *c=new TCanvas("c","c",2000,1000);
	c->Divide(2,1);
	c->cd(1);
	hMassK1XiData->Draw("E");
	c->cd(2);
	hMassK2XiData->Draw("E");


	TCanvas *ck=new TCanvas("ck","",2000,1000);
	ck->Divide(2,1);
	ck->cd(2);
	hk = (TH1F*)hMassK1XiData->Clone("hk1");
	hk = (TH1F*)hMassK1XiData->Clone("hk2");
	hk = (TH1F*)hMassK1XiData->Clone("hk");


	tData->Draw("mcasmkp1>>hk1");
	tData->Draw("mcasmkp2>>hk2");
	hk->GetXaxis()->SetTitle(" m(#Xi^{-} K^{+}) (GeV/c^2) ");
	hk->Add(hk1);
	hk->Add(hk2);

	//hMassK1XiData->Add(hMassK2XiData,1);
	hk->Draw("E");


	cRes->cd();
}







void PlotBeam()
{
	float temp1,temp2,normfac;
	StyleUp();




	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Beam Energy Spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hBeam=new TH1F("hBeam","",28,2.7,5.5); // 1800/18 = 100 MeV
	hBeam->SetMinimum(0);
	hBeam->SetMarkerStyle(21);
	//Data
	hBeamData = (TH1F*)hBeam->Clone("hBeamData");
	hBeamData->SetMinimum(0);
	hBeamData->GetYaxis()->SetTitle("Events");
	hBeamData->GetXaxis()->SetTitle("Beam Energy (GeV)");
	//MC
	hBeamMC = (TH1F*)hBeam->Clone("hBeamMC");
	hBeamMC->SetMinimum(0);
	hBeamMC->GetYaxis()->SetTitle("Events");
	hBeamMC->GetXaxis()->SetTitle("Beam Energy (GeV) ");

	//draw the hists
	cblank->cd(0);
	tData->Draw("beam>>hBeamData","beam < 4.3");
	tMC->Draw("beam>>hBeamMC", "beam < 4.3");
	temp1 = hBeamData->GetEntries();
	temp2 = hBeamMC->GetEntries();
	normfac = temp1/temp2;
	hBeamMC->Add(hBeamMC, normfac - 1);

	cblank->cd(0);

	//for thesis
	TCanvas *cCompareBeam=new TCanvas("cCompareBeam","cCompareBeam",1200,800);
	hBeamData->SetMarkerStyle(21);
	hBeamData->SetFillColor(3);
	hBeamData->Draw("E");
	hBeamMC->SetMarkerStyle(21);
	hBeamMC->SetFillStyle(3002);
	hBeamMC->SetFillColor(2);
	hBeamMC->Draw("SAME");
	cblank->cd(0);

	cCompareBeam->Print("~/Desktop/beam.png");
}



void FidBeam()
{
	float temp1,temp2,normfac;
	StyleUp();


	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);

	//histos
	//model
	TH1F *hBeam=new TH1F("hBeam","",28,2.7,5.5); // 1800/18 = 100 MeV
	hBeam->SetMinimum(0);
	hBeam->SetMarkerStyle(21);
	//DataFid
	hBeamDataFid = (TH1F*)hBeam->Clone("hBeamDataFid");
	hBeamDataFid->SetMinimum(0);
	hBeamDataFid->GetYaxis()->SetTitle("Events");
	hBeamDataFid->GetXaxis()->SetTitle("Beam Energy (GeV)");
	//Data
	hBeamData = (TH1F*)hBeam->Clone("hBeamData");
	hBeamData->SetMinimum(0);
	hBeamData->GetYaxis()->SetTitle("Events");
	hBeamData->GetXaxis()->SetTitle("Beam Energy (GeV) ");

	//draw the hists
	cblank->cd(0);
	tDataFid->Draw("beam>>hBeamDataFid");
	tData->Draw("beam>>hBeamData");
	temp1 = hBeamDataFid->GetEntries();
	temp2 = hBeamData->GetEntries();
	normfac = temp1/temp2;
	hBeamData->Add(hBeamData, normfac - 1);

	cblank->cd(0);

	//for thesis
	TCanvas *cCompareBeam=new TCanvas("cCompareBeam","cCompareBeam",1200,800);
	hBeamDataFid->SetMarkerStyle(21);
	hBeamDataFid->SetFillColor(3);
	hBeamDataFid->Draw();
	hBeamData->SetMarkerStyle(21);
	hBeamData->SetFillStyle(3002);
	hBeamData->SetFillColor(2);
	hBeamData->Draw("SAME");
	cblank->cd(0);

}








void ShowTiming()
{


	TH1F *hTime=new TH1F("hTime","",100,-2,2); // 4000/400 = 10 MeV
	hTime->SetMinimum(0);
	hTime->GetYaxis()->SetTitle("Events");
	hTime->GetXaxis()->SetTitle("Timing Difference (ns) ");
	hTime->SetMarkerStyle(21);
	hTime->SetFillColor(kBlue);

	TF1 *f1 = new TF1("f1","gaus",-0.5,0.5);


	TCut tempcut = "abs(vtime - (sctkp2 - sclkp2/(betakp2*29.99))) < 1";

	//*///Data after basic cuts and mass cuts
	TCanvas *cDataTime=new TCanvas("cDataTime","cDataTime",1500,1000);
	cDataTime->Divide(2,2);
	cDataTime->cd(1);
	hDataST = (TH1F*)hTime->Clone("hDataST");
	hDataST->GetXaxis()->SetTitle("t_{vtx}(Tagger_{RF}) - t_{vtx}(StartCounter)) (ns) ");
	tRawData->Draw("vtime - stv>>hDataST");
	cDataTime->cd(2);
	hDataTOF1 = (TH1F*)hTime->Clone("hDataTOF1");
	hDataTOF1->GetXaxis()->SetTitle("t_{vtx}(Tagger_{RF}) - t_{vtx}(PathLenth/Velocity) (K^{+}_{fast}) (ns)  ");
	hDataTOF1->GetXaxis()->SetTitle("t_{vtx}(Tagger) - t_{vtx}(TOF)  (ns)  ");
	tData->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hDataTOF1");
	hDataTOF1->Fit("gaus","","",-0.5,0.5);
	cDataTime->cd(3);
	hDataTOF2 = (TH1F*)hTime->Clone("hDataTOF2");
	hDataTOF2->GetXaxis()->SetTitle("t_{vtx}(Tagger_{RF}) - t_{vtx}(PathLenth/Velocity) (K^{+}_{slow}) (ns) ");
	hDataTOF2->GetXaxis()->SetTitle("t_{vtx}(Tagger) - t_{vtx}(TOF) (ns) ");
	tData->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hDataTOF2",tempcut);
	hDataTOF2->Fit("gaus","","",-0.5,0.5);
	cDataTime->cd(4);
	hDataTOF3 = (TH1F*)hTime->Clone("hDataTOF3");
	hDataTOF3->GetXaxis()->SetTitle("t_{vtx}(Tagger_{RF}) - t_{vtx}(PathLenth/Velocity) (#pi^{-}) (ns)");
	tData->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hDataTOF3");
	hDataTOF3->Fit("gaus","","",-1.5,1);
	///*///


	StyleUp();
	gStyle->SetOptFit(1);
	gStyle->SetTitleYOffset(0.85);
	TCanvas *cDataTime2=new TCanvas("cDataTime2","cDataTime2",1500,400);
	TCanvas *cDataTime3=new TCanvas("cDataTime3","cDataTime3",1500,400);
	cDataTime2->Divide(2,1);
	cDataTime3->cd(1);
	hDataST->Draw();
    TF1 = new TF1("myfit","gaus");
    hDataST->Fit("myfit","","",-2,2);
	cDataTime2->cd(1);
	hDataTOF1->Draw();
	cDataTime2->cd(2);
	hDataTOF2->Draw();



    
    

	/*///Data with basic cuts and no mass cuts
	TCanvas *cDataTime=new TCanvas("cDataTime","cDataTime",1500,1000);
	cDataTime->Divide(2,2);
	cDataTime->cd(1);
	hDataST = (TH1F*)hTime->Clone("hDataST");
	hDataST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tDataB->Draw("stv-scv>>hDataST");
	cDataTime->cd(2);
	hDataTOF1 = (TH1F*)hTime->Clone("hDataTOF1");
	hDataTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tDataB->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hDataTOF1");
	hDataTOF1->Fit("gaus","","",-0.5,0.5);
	cDataTime->cd(3);
	hDataTOF2 = (TH1F*)hTime->Clone("hDataTOF2");
	hDataTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tDataB->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hDataTOF2");
	hDataTOF2->Fit("gaus","","",-0.5,0.5);
	cDataTime->cd(4);
	hDataTOF3 = (TH1F*)hTime->Clone("hDataTOF3");
	hDataTOF3->GetXaxis()->SetTitle("RF - piTOF (ns) ");
	tDataB->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hDataTOF3");
	hDataTOF3->Fit("gaus","","",-1.5,1);
	///*///







	/*//Data with mass cuts and no basic cuts
	TCanvas *cDataTimeC=new TCanvas("cDataTimeC","cDataTimeC",1500,1000);
	cDataTimeC->Divide(3,1);
	cDataTimeC->cd(1);
	hDataC = (TH1F*)hTime->Clone("hDataSTC");
	hDataC->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tDataC->Draw("stv-scv>>hDataSTC");
	cDataTimeC->cd(2);
	hDataTOF1C = (TH1F*)hTime->Clone("hDataTOF1C");
	hDataTOF1C->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tDataC->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hDataTOF1C");
	cDataTimeC->cd(3);
	hDataTOF2C = (TH1F*)hTime->Clone("hDataTOF2C");
	hDataTOF2C->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tDataC->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hDataTOF2C");
	cDataTimeC->cd(4);
	hDataTOF3C = (TH1F*)hTime->Clone("hDataTOF3C");
	hDataTOF3C->GetXaxis()->SetTitle("RF - piTOF (ns) ");
	tDataC->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hDataTOF3C");
	///*///


	/*/////MC with basic cuts and mass cuts
	TCanvas *cMCTime=new TCanvas("cMCTime","cMCTime",1500,1000);
	cMCTime->Divide(2,2);
	cMCTime->cd(1);
	hMCST = (TH1F*)hTime->Clone("hMCST");
	hMCST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMC->Draw("stv-scv>>hMCST");
	cMCTime->cd(2);
	hMCTOF1 = (TH1F*)hTime->Clone("hMCTOF1");
	hMCTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMC->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1");
	hMCTOF1->Fit("gaus","","",-1,1);
	cMCTime->cd(3);
	hMCTOF2 = (TH1F*)hTime->Clone("hMCTOF2");
	hMCTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMC->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2");
	hMCTOF2->Fit("gaus","","",-1,1);
	cMCTime->cd(4);
	hMCTOF3 = (TH1F*)hTime->Clone("hMCTOF3");
	hMCTOF3->GetXaxis()->SetTitle("RF - piTOF (ns) ");
	tMC->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hMCTOF3");
	hMCTOF3->Fit("gaus","","",-1,1);
	///*///




	/*/////MC with basic cuts and no mass cuts
	TCanvas *cMCTime=new TCanvas("cMCTime","cMCTime",1500,1000);
	cMCTime->Divide(2,2);
	cMCTime->cd(1);
	hMCST = (TH1F*)hTime->Clone("hMCST");
	hMCST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCB->Draw("stv-scv>>hMCST");
	cMCTime->cd(2);
	hMCTOF1 = (TH1F*)hTime->Clone("hMCTOF1");
	hMCTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCB->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1");
	hMCTOF1->Fit("gaus","","",-1,1);
	cMCTime->cd(3);
	hMCTOF2 = (TH1F*)hTime->Clone("hMCTOF2");
	hMCTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCB->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2");
	hMCTOF2->Fit("gaus","","",-1,1);
	cMCTime->cd(4);
	hMCTOF3 = (TH1F*)hTime->Clone("hMCTOF3");
	hMCTOF3->GetXaxis()->SetTitle("RF - piTOF (ns) ");
	tMCB->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hMCTOF3");
	hMCTOF3->Fit("gaus","","",-1,1);
	///*///






	/*//MC with mass cuts and no basic cuts
	TCanvas *cMCTimeC=new TCanvas("cMCTimeC","cMCTimeC",1500,1000);
	cMCTimeC->Divide(3,1);
	cMCTimeC->cd(1);
	hMCSTC = (TH1F*)hTime->Clone("hMCSTC");
	hMCSTC->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCC->Draw("stv-scv>>hMCSTC");
	cMCTimeC->cd(2);
	hMCTOF1C = (TH1F*)hTime->Clone("hMCTOF1C");
	hMCTOF1C->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCC->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1C");
	cMCTimeC->cd(3);
	hMCTOF2C = (TH1F*)hTime->Clone("hMCTOF2C");
	hMCTOF2C->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCC->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2C");
	///*///


	/*//i9 test one-vertex "test1" with basic cuts and mass cuts
	TCanvas *cMCTimeTest1=new TCanvas("cMCTimeTest1","cMCTimeTest1",1500,1000);
	cMCTimeTest1->Divide(2,2);
	cMCTimeTest1->cd(1);
	hMCSTTest1 = (TH1F*)hTime->Clone("hMCSTTest1");
	hMCSTTest1->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCTest1->Draw("stv-scv>>hMCSTTest1");
	cMCTimeTest1->cd(2);
	hMCTOF1Test1 = (TH1F*)hTime->Clone("hMCTOF1Test1");
	hMCTOF1Test1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCTest1->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1Test1");
	hMCTOF1Test1->Fit("gaus","","",-1,1);
	cMCTimeTest1->cd(3);
	hMCTOF2Test1 = (TH1F*)hTime->Clone("hMCTOF2Test1");
	hMCTOF2Test1->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCTest1->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2Test1");
	hMCTOF2Test1->Fit("gaus","","",-1,1);
	cMCTimeTest1->cd(4);
	hMCTOF3Test1 = (TH1F*)hTime->Clone("hMCTOF3Test1");
	hMCTOF3Test1->GetXaxis()->SetTitle("RF - piTOF (ns) ");
	tMCTest1->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hMCTOF3Test1");
	hMCTOF3Test1->Fit("gaus","","",-1,1);


	//i9 test detached-vertex "test2" with basic cuts no mass cuts
	TCanvas *cMCTimeTest2=new TCanvas("cMCTimeTest2","cMCTimeTest2",1500,1000);
	cMCTimeTest2->Divide(2,2);
	cMCTimeTest2->cd(1);
	hMCSTTest2 = (TH1F*)hTime->Clone("hMCSTTest2");
	hMCSTTest2->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCTest2->Draw("stv-scv>>hMCSTTest2");
	cMCTimeTest2->cd(2);
	hMCTOF1Test2 = (TH1F*)hTime->Clone("hMCTOF1Test2");
	hMCTOF1Test2->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCTest2->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1Test2");
	hMCTOF1Test2->Fit("gaus","","",-1,1);
	cMCTimeTest2->cd(3);
	hMCTOF2Test2 = (TH1F*)hTime->Clone("hMCTOF2Test2");
	hMCTOF2Test2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCTest2->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2Test2");
	hMCTOF2Test2->Fit("gaus","","",-1,1);
	cMCTimeTest2->cd(4);
	hMCTOF3Test2 = (TH1F*)hTime->Clone("hMCTOF3Test2");
	hMCTOF3Test2->GetXaxis()->SetTitle("RF - piTOF (ns) ");
	tMCTest2->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hMCTOF3Test2");
	hMCTOF3Test2->Fit("gaus","","",-1,1);
	//*///



	/*///
	//Test1
	TCanvas *cMCTimeTest1=new TCanvas("cMCTimeTest1","cMCTimeTest1",1500,1000);
	cMCTimeTest1->Divide(3,1);
	cMCTimeTest1->cd(1);
	hMCSTTest1 = (TH1F*)hTime->Clone("hMCSTTest1");
	hMCSTTest1->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCTest1->Draw("stv-scv>>hMCSTTest1");
	cMCTimeTest1->cd(2);
	hMCTOF1Test1 = (TH1F*)hTime->Clone("hMCTOF1Test1");
	hMCTOF1Test1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCTest1->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1Test1");
	cMCTimeTest1->cd(3);
	hMCTOF2Test1 = (TH1F*)hTime->Clone("hMCTOF2Test1");
	hMCTOF2Test1->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCTest1->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2Test1");




	//Test2
	TCanvas *cMCTimeTest2=new TCanvas("cMCTimeTest2","cMCTimeTest2",1500,1000);
	cMCTimeTest2->Divide(3,1);
	cMCTimeTest2->cd(1);
	hMCSTTest2 = (TH1F*)hTime->Clone("hMCSTTest2");
	hMCSTTest2->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCTest2->Draw("stv-scv>>hMCSTTest2");
	cMCTimeTest2->cd(2);
	hMCTOF1Test2 = (TH1F*)hTime->Clone("hMCTOF1Test2");
	hMCTOF1Test2->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCTest2->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1Test2");
	cMCTimeTest2->cd(3);
	hMCTOF2Test2 = (TH1F*)hTime->Clone("hMCTOF2Test2");
	hMCTOF2Test2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCTest2->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2Test2");


	//MKWay
	TCanvas *cMCTimeMKWay=new TCanvas("cMCTimeMKWay","cMCTimeMKWay",1500,1000);
	cMCTimeMKWay->Divide(3,1);
	cMCTimeMKWay->cd(1);
	hMCSTMKWay = (TH1F*)hTime->Clone("hMCSTMKWay");
	hMCSTMKWay->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCMKWay->Draw("stv-scv>>hMCSTMKWay");
	cMCTimeMKWay->cd(2);
	hMCTOF1MKWay = (TH1F*)hTime->Clone("hMCTOF1MKWay");
	hMCTOF1MKWay->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCMKWay->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1MKWay");
	cMCTimeMKWay->cd(3);
	hMCTOF2MKWay = (TH1F*)hTime->Clone("hMCTOF2MKWay");
	hMCTOF2MKWay->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCMKWay->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2MKWay");



	//MKWay2
	TCanvas *cMCTimeMKWay2=new TCanvas("cMCTimeMKWay2","cMCTimeMKWay2",1500,1000);
	cMCTimeMKWay2->Divide(3,1);
	cMCTimeMKWay2->cd(1);
	hMCSTMKWay2 = (TH1F*)hTime->Clone("hMCSTMKWay2");
	hMCSTMKWay2->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMCMKWay2->Draw("stv-scv>>hMCSTMKWay2");
	cMCTimeMKWay2->cd(2);
	hMCTOF1MKWay2 = (TH1F*)hTime->Clone("hMCTOF1MKWay2");
	hMCTOF1MKWay2->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMCMKWay2->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1MKWay2");
	cMCTimeMKWay2->cd(3);
	hMCTOF2MKWay2 = (TH1F*)hTime->Clone("hMCTOF2MKWay2");
	hMCTOF2MKWay2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMCMKWay2->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2MKWay2");
		///*///

}

void EvsX()
{
	StyleUp();
	TH2F *hDataEvsX=new TH2F("hDataEvsX","",50,2.7,5.6,50,-1,1);
	TH2F *hMCEvsX=new TH2F("hMCEvsX","",50,2.7,5.6,50,-1,1);
	hDataEvsX->GetYaxis()->SetTitle("cos(#theta_{#Xi}^{cm})");
	hDataEvsX->GetXaxis()->SetTitle("E#gamma");
	hMCEvsX->GetYaxis()->SetTitle("cos(#theta_{#Xi}^{cm})");
	hMCEvsX->GetXaxis()->SetTitle("E#gamma");
	hDataEvsX->SetTitle("Data");
	hMCEvsX->SetTitle("MC");


	TCanvas *cEvsX=new TCanvas("cEvsX","cEvsX",1000,800);
	cEvsX->Divide(2,0);
	cEvsX->cd(1);
	tData->Draw("Xcmtheta:beam>>hDataEvsX","","colz");
	cEvsX->cd(2);
	tMC->Draw("Xcmtheta:beam>>hMCEvsX","","colz");


	TLine *lXi[Nc];
	for (int c = 1; c < Nc; c++)
	{
		lXi[c] = new TLine(2.8,XVal[c],5.5,XVal[c]);
		lXi[c]->SetLineWidth(5);
		lXi[c]->SetLineColor(2);
		lXi[c]->Draw("same");
	}
	TLine *lE[Nc];
	for (int c = 1; c < Nc; c++)
	{
		lE[c] = new TLine(EVal[c],-1,EVal[c],1);
		lE[c]->SetLineWidth(5);
		lE[c]->SetLineColor(3);
		lE[c]->Draw("same");
	}
	cEvsX->cd(1);
	for (int c = 1; c < Nc; c++)
	{
		lXi[c] = new TLine(2.8,XVal[c],5.5,XVal[c]);
		lXi[c]->SetLineWidth(5);
		lXi[c]->SetLineColor(2);
		lXi[c]->Draw("same");
	}
	TLine *lE[Nc];
	for (int c = 1; c < Nc; c++)
	{
		lE[c] = new TLine(EVal[c],-1,EVal[c],1);
		lE[c]->SetLineWidth(5);
		lE[c]->SetLineColor(3);
		lE[c]->Draw("same");
	}

}



void ShowFidEffect_PhiVsP_Data()
{
	StyleUp();
	TH2F *hPhiVsP_kp1=new TH2F("hPhiVsP_kp1","",50,0,4,200,-180,180);
	hPhiVsP_kp1->GetXaxis()->SetTitle("Momentum  (k^{+}_{fast})");
	hPhiVsP_kp1->GetYaxis()->SetTitle("#phi  (k^{+}_{fast})");
	TH2F *hPhiVsP_kp1_1= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_1");
	TH2F *hPhiVsP_kp1_2= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_2");
	TH2F *hPhiVsP_kp1_3= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_3");
	TH2F *hPhiVsP_kp1_4= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_4");
	TCanvas *cPhiVsP_kp1=new TCanvas("cPhiVsP_kp1","cPhiVsP_kp1",1000,800);
	cPhiVsP_kp1->Divide(4,0);
	cPhiVsP_kp1->cd(1);
	tData->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_1","","colz");
	cPhiVsP_kp1->cd(2);
	tDataFidLoose->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_2","","colz");
	cPhiVsP_kp1->cd(3);
	tDataFidReg->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_3","","colz");
	cPhiVsP_kp1->cd(4);
	tDataFidTight->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_4","","colz");
	cPhiVsP_kp1->Print("~/Desktop/PhiVsP_kp1_Data.png");

	TH2F *hPhiVsP_kp2=new TH2F("hPhiVsP_kp2","",50,0,3,200,-180,180);
	hPhiVsP_kp2->GetXaxis()->SetTitle("Momentum  (k^{+}_{fast})");
	hPhiVsP_kp2->GetYaxis()->SetTitle("#phi  (k^{+}_{fast})");
	TH2F *hPhiVsP_kp2_1= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_1");
	TH2F *hPhiVsP_kp2_2= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_2");
	TH2F *hPhiVsP_kp2_3= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_3");
	TH2F *hPhiVsP_kp2_4= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_4");
	TCanvas *cPhiVsP_kp2=new TCanvas("cPhiVsP_kp2","cPhiVsP_kp2",1000,800);
	cPhiVsP_kp2->Divide(4,0);
	cPhiVsP_kp2->cd(1);
	tData->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_1","","colz");
	cPhiVsP_kp2->cd(2);
	tDataFidLoose->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_2","","colz");
	cPhiVsP_kp2->cd(3);
	tDataFidReg->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_3","","colz");
	cPhiVsP_kp2->cd(4);
	tDataFidTight->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_4","","colz");
	cPhiVsP_kp2->Print("~/Desktop/PhiVsP_kp2_Data.png");

	TH2F *hPhiVsP_pim=new TH2F("hPhiVsP_pim","",50,0,1,200,-180,180);
	hPhiVsP_pim->GetXaxis()->SetTitle("Momentum  (#pi^{+})");
	hPhiVsP_pim->GetYaxis()->SetTitle("#phi  (#pi^{+})");
	TH2F *hPhiVsP_pim_1= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_1");
	TH2F *hPhiVsP_pim_2= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_2");
	TH2F *hPhiVsP_pim_3= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_3");
	TH2F *hPhiVsP_pim_4= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_4");
	TCanvas *cPhiVsP_pim=new TCanvas("cPhiVsP_pim","cPhiVsP_pim",1000,800);
	cPhiVsP_pim->Divide(4,0);
	cPhiVsP_pim->cd(1);
	tData->Draw("180*pilabphi : ppim >> hPhiVsP_pim_1","","colz");
	cPhiVsP_pim->cd(2);
	tDataFidLoose->Draw("180*pilabphi : ppim >> hPhiVsP_pim_2","","colz");
	cPhiVsP_pim->cd(3);
	tDataFidReg->Draw("180*pilabphi : ppim >> hPhiVsP_pim_3","","colz");
	cPhiVsP_pim->cd(4);
	tDataFidTight->Draw("180*pilabphi : ppim >> hPhiVsP_pim_4","","colz");
	cPhiVsP_pim->Print("~/Desktop/PhiVsP_pim_Data.png");
}

void ShowFidEffect_PhiVsP_MC()
{
	StyleUp();
	TH2F *hPhiVsP_kp1=new TH2F("hPhiVsP_kp1","",50,0,4,200,-180,180);
	hPhiVsP_kp1->GetXaxis()->SetTitle("Momentum  (k^{+}_{fast})");
	hPhiVsP_kp1->GetYaxis()->SetTitle("#phi  (k^{+}_{fast})");
	TH2F *hPhiVsP_kp1_1= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_1");
	TH2F *hPhiVsP_kp1_2= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_2");
	TH2F *hPhiVsP_kp1_3= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_3");
	TH2F *hPhiVsP_kp1_4= (TH2F*)hPhiVsP_kp1->Clone("hPhiVsP_kp1_4");
	TCanvas *cPhiVsP_kp1=new TCanvas("cPhiVsP_kp1","cPhiVsP_kp1",1000,800);
	cPhiVsP_kp1->Divide(4,0);
	cPhiVsP_kp1->cd(1);
	tMC->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_1","","colz");
	cPhiVsP_kp1->cd(2);
	tMCFidLoose->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_2","","colz");
	cPhiVsP_kp1->cd(3);
	tMCFidReg->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_3","","colz");
	cPhiVsP_kp1->cd(4);
	tMCFidTight->Draw("180*kp1labphi : pkp1 >> hPhiVsP_kp1_4","","colz");
	cPhiVsP_kp1->Print("~/Desktop/PhiVsP_kp1_MC.png");

	TH2F *hPhiVsP_kp2=new TH2F("hPhiVsP_kp2","",50,0,3,200,-180,180);
	hPhiVsP_kp2->GetXaxis()->SetTitle("Momentum  (k^{+}_{fast})");
	hPhiVsP_kp2->GetYaxis()->SetTitle("#phi  (k^{+}_{fast})");
	TH2F *hPhiVsP_kp2_1= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_1");
	TH2F *hPhiVsP_kp2_2= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_2");
	TH2F *hPhiVsP_kp2_3= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_3");
	TH2F *hPhiVsP_kp2_4= (TH2F*)hPhiVsP_kp2->Clone("hPhiVsP_kp2_4");
	TCanvas *cPhiVsP_kp2=new TCanvas("cPhiVsP_kp2","cPhiVsP_kp2",1000,800);
	cPhiVsP_kp2->Divide(4,0);
	cPhiVsP_kp2->cd(1);
	tMC->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_1","","colz");
	cPhiVsP_kp2->cd(2);
	tMCFidLoose->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_2","","colz");
	cPhiVsP_kp2->cd(3);
	tMCFidReg->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_3","","colz");
	cPhiVsP_kp2->cd(4);
	tMCFidTight->Draw("180*kp2labphi : pkp2 >> hPhiVsP_kp2_4","","colz");
	cPhiVsP_kp2->Print("~/Desktop/PhiVsP_kp2_MC.png");

	TH2F *hPhiVsP_pim=new TH2F("hPhiVsP_pim","",50,0,1,200,-180,180);
	hPhiVsP_pim->GetXaxis()->SetTitle("Momentum  (#pi^{+})");
	hPhiVsP_pim->GetYaxis()->SetTitle("#phi  (#pi^{+})");
	TH2F *hPhiVsP_pim_1= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_1");
	TH2F *hPhiVsP_pim_2= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_2");
	TH2F *hPhiVsP_pim_3= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_3");
	TH2F *hPhiVsP_pim_4= (TH2F*)hPhiVsP_pim->Clone("hPhiVsP_pim_4");
	TCanvas *cPhiVsP_pim=new TCanvas("cPhiVsP_pim","cPhiVsP_pim",1000,800);
	cPhiVsP_pim->Divide(4,0);
	cPhiVsP_pim->cd(1);
	tMC->Draw("180*pilabphi : ppim >> hPhiVsP_pim_1","","colz");
	cPhiVsP_pim->cd(2);
	tMCFidLoose->Draw("180*pilabphi : ppim >> hPhiVsP_pim_2","","colz");
	cPhiVsP_pim->cd(3);
	tMCFidReg->Draw("180*pilabphi : ppim >> hPhiVsP_pim_3","","colz");
	cPhiVsP_pim->cd(4);
	tMCFidTight->Draw("180*pilabphi : ppim >> hPhiVsP_pim_4","","colz");
	cPhiVsP_pim->Print("~/Desktop/PhiVsP_pim_MC.png");
}

void ShowFidEffect_PhiVsTheta_MC()
{
	StyleUp();
	TH2F *hMCPhiVsTheta_kp1=new TH2F("hMCPhiVsTheta_kp1","",90,0,90,360,-180,180);
	hMCPhiVsTheta_kp1->GetYaxis()->SetTitle("#phi k^{+}_{fast}");
	hMCPhiVsTheta_kp1->GetXaxis()->SetTitle("#theta  k^{+}_{fast}");
	hMCPhiVsTheta_kp1->SetTitle("MC");
	TH2F *hMCPhiVsTheta_kp1_1= (TH2F*)hMCPhiVsTheta_kp1->Clone("hMCPhiVsTheta_kp1_1");
	TH2F *hMCPhiVsTheta_kp1_2= (TH2F*)hMCPhiVsTheta_kp1->Clone("hMCPhiVsTheta_kp1_2");
	TH2F *hMCPhiVsTheta_kp1_3= (TH2F*)hMCPhiVsTheta_kp1->Clone("hMCPhiVsTheta_kp1_3");
	TH2F *hMCPhiVsTheta_kp1_4= (TH2F*)hMCPhiVsTheta_kp1->Clone("hMCPhiVsTheta_kp1_4");
	TCanvas *cMCPhiVsTheta=new TCanvas("cMCPhiVsTheta","cMCPhiVsTheta",1000,800);
	cMCPhiVsTheta->Divide(4,0);
	cMCPhiVsTheta->cd(1);
	tMC->Draw("180*kp1labphi:(180/3.1415)*acos(kp1labtheta)>>hMCPhiVsTheta_kp1_1","","colz");
	cMCPhiVsTheta->cd(2);
	tMCFidLoose->Draw("180*kp1labphi:(180/3.1415)*acos(kp1labtheta)>>hMCPhiVsTheta_kp1_2","","colz");
	cMCPhiVsTheta->cd(3);
	tMCFidReg->Draw("180*kp1labphi:(180/3.1415)*acos(kp1labtheta)>>hMCPhiVsTheta_kp1_3","","colz");
	cMCPhiVsTheta->cd(4);
	tMCFidTight->Draw("180*kp1labphi:(180/3.1415)*acos(kp1labtheta)>>hMCPhiVsTheta_kp1_4","","colz");
	cMCPhiVsTheta->Print("~/Desktop/PhiVsTheta_kp1_MC.png");


	TH2F *hMCPhiVsTheta_kp2=new TH2F("hMCPhiVsTheta_kp2","",90,0,90,360,-180,180);
	hMCPhiVsTheta_kp2->GetYaxis()->SetTitle("#phi k^{+}_{fast}");
	hMCPhiVsTheta_kp2->GetXaxis()->SetTitle("#theta  k^{+}_{fast}");
	hMCPhiVsTheta_kp2->SetTitle("MC");
	TH2F *hMCPhiVsTheta_kp2_1= (TH2F*)hMCPhiVsTheta_kp2->Clone("hMCPhiVsTheta_kp2_1");
	TH2F *hMCPhiVsTheta_kp2_2= (TH2F*)hMCPhiVsTheta_kp2->Clone("hMCPhiVsTheta_kp2_2");
	TH2F *hMCPhiVsTheta_kp2_3= (TH2F*)hMCPhiVsTheta_kp2->Clone("hMCPhiVsTheta_kp2_3");
	TH2F *hMCPhiVsTheta_kp2_4= (TH2F*)hMCPhiVsTheta_kp2->Clone("hMCPhiVsTheta_kp2_4");
	TCanvas *cMCPhiVsTheta=new TCanvas("cMCPhiVsTheta","cMCPhiVsTheta",1000,800);
	cMCPhiVsTheta->Divide(4,0);
	cMCPhiVsTheta->cd(1);
	tMC->Draw("180*kp2labphi:(180/3.1415)*acos(kp2labtheta)>>hMCPhiVsTheta_kp2_1","","colz");
	cMCPhiVsTheta->cd(2);
	tMCFidLoose->Draw("180*kp2labphi:(180/3.1415)*acos(kp2labtheta)>>hMCPhiVsTheta_kp2_2","","colz");
	cMCPhiVsTheta->cd(3);
	tMCFidReg->Draw("180*kp2labphi:(180/3.1415)*acos(kp2labtheta)>>hMCPhiVsTheta_kp2_3","","colz");
	cMCPhiVsTheta->cd(4);
	tMCFidTight->Draw("180*kp2labphi:(180/3.1415)*acos(kp2labtheta)>>hMCPhiVsTheta_kp2_4","","colz");
	cMCPhiVsTheta->Print("~/Desktop/PhiVsTheta_kp2_MC.png");


	TH2F *hMCPhiVsTheta_pim=new TH2F("hMCPhiVsTheta_pim","",90,0,90,360,-180,180);
	hMCPhiVsTheta_pim->GetYaxis()->SetTitle("#phi k^{+}_{fast}");
	hMCPhiVsTheta_pim->GetXaxis()->SetTitle("#theta  k^{+}_{fast}");
	hMCPhiVsTheta_pim->SetTitle("MC");
	TH2F *hMCPhiVsTheta_pim_1= (TH2F*)hMCPhiVsTheta_pim->Clone("hMCPhiVsTheta_pim_1");
	TH2F *hMCPhiVsTheta_pim_2= (TH2F*)hMCPhiVsTheta_pim->Clone("hMCPhiVsTheta_pim_2");
	TH2F *hMCPhiVsTheta_pim_3= (TH2F*)hMCPhiVsTheta_pim->Clone("hMCPhiVsTheta_pim_3");
	TH2F *hMCPhiVsTheta_pim_4= (TH2F*)hMCPhiVsTheta_pim->Clone("hMCPhiVsTheta_pim_4");
	TCanvas *cMCPhiVsTheta=new TCanvas("cMCPhiVsTheta","cMCPhiVsTheta",1000,800);
	cMCPhiVsTheta->Divide(4,0);
	cMCPhiVsTheta->cd(1);
	tMC->Draw("180*pilabphi:(180/3.1415)*acos(pilabtheta)>>hMCPhiVsTheta_pim_1","","colz");
	cMCPhiVsTheta->cd(2);
	tMCFidLoose->Draw("180*pilabphi:(180/3.1415)*acos(pilabtheta)>>hMCPhiVsTheta_pim_2","","colz");
	cMCPhiVsTheta->cd(3);
	tMCFidReg->Draw("180*pilabphi:(180/3.1415)*acos(pilabtheta)>>hMCPhiVsTheta_pim_3","","colz");
	cMCPhiVsTheta->cd(4);
	tMCFidTight->Draw("180*pilabphi:(180/3.1415)*acos(pilabtheta)>>hMCPhiVsTheta_pim_4","","colz");
	cMCPhiVsTheta->Print("~/Desktop/PhiVsTheta_pim_MC.png");


}

void ShowFidEffect_clas_MC()
{
	StyleUp();
	TH2F *hMCclas_kp1=new TH2F("hMCclas_kp1","",180,-90,90,180,-90,90);
	hMCclas_kp1->GetXaxis()->SetTitle("#theta sin(#phi)  k^{+}_{fast}");
	hMCclas_kp1->GetYaxis()->SetTitle("#theta cos(#phi)  k^{+}_{fast}");
	hMCclas_kp1->SetTitle("MC");
	TH2F *hMCclas_kp1_1= (TH2F*)hMCclas_kp1->Clone("hMCclas_kp1_1");
	TH2F *hMCclas_kp1_2= (TH2F*)hMCclas_kp1->Clone("hMCclas_kp1_2");
	TH2F *hMCclas_kp1_3= (TH2F*)hMCclas_kp1->Clone("hMCclas_kp1_3");
	TH2F *hMCclas_kp1_4= (TH2F*)hMCclas_kp1->Clone("hMCclas_kp1_4");
	TCanvas *cMCclas=new TCanvas("cMCclas","cMCclas",1000,800);
	cMCclas->Divide(2,2);
	cMCclas->cd(1);
	tMC->Draw("90*acos(kp1labtheta)*cos(kp1labphi*TMath::Pi()) : 90*acos(kp1labtheta)*sin(kp1labphi*TMath::Pi())>>hMCclas_kp1_1","","colz");
	cMCclas->cd(2);
	tMCFidLoose->Draw("90*acos(kp1labtheta)*cos(kp1labphi*TMath::Pi()) : 90*acos(kp1labtheta)*sin(kp1labphi*TMath::Pi())>>hMCclas_kp1_2","","colz");
	cMCclas->cd(3);
	tMCFidReg->Draw("90*acos(kp1labtheta)*cos(kp1labphi*TMath::Pi()) : 90*acos(kp1labtheta)*sin(kp1labphi*TMath::Pi())>>hMCclas_kp1_3","","colz");
	cMCclas->cd(4);
	tMCFidTight->Draw("90*acos(kp1labtheta)*cos(kp1labphi*TMath::Pi()) : 90*acos(kp1labtheta)*sin(kp1labphi*TMath::Pi())>>hMCclas_kp1_4","","colz");
	cMCclas->Print("~/Desktop/clas_kp1_MC.png");

	TH2F *hMCclas_kp2=new TH2F("hMCclas_kp2","",180,-90,90,180,-90,90);
	hMCclas_kp2->GetXaxis()->SetTitle("#theta sin(#phi)  k^{+}_{slow}");
	hMCclas_kp2->GetYaxis()->SetTitle("#theta cos(#phi)  k^{+}_{slow}");
	hMCclas_kp2->SetTitle("MC");
	TH2F *hMCclas_kp2_1= (TH2F*)hMCclas_kp2->Clone("hMCclas_kp2_1");
	TH2F *hMCclas_kp2_2= (TH2F*)hMCclas_kp2->Clone("hMCclas_kp2_2");
	TH2F *hMCclas_kp2_3= (TH2F*)hMCclas_kp2->Clone("hMCclas_kp2_3");
	TH2F *hMCclas_kp2_4= (TH2F*)hMCclas_kp2->Clone("hMCclas_kp2_4");
	TCanvas *cMCclas=new TCanvas("cMCclas","cMCclas",1000,800);
	cMCclas->Divide(2,2);
	cMCclas->cd(1);
	tMC->Draw("90*acos(kp2labtheta)*cos(kp2labphi*TMath::Pi()) : 90*acos(kp2labtheta)*sin(kp2labphi*TMath::Pi())>>hMCclas_kp2_1","","colz");
	cMCclas->cd(2);
	tMCFidLoose->Draw("90*acos(kp2labtheta)*cos(kp2labphi*TMath::Pi()) : 90*acos(kp2labtheta)*sin(kp2labphi*TMath::Pi())>>hMCclas_kp2_2","","colz");
	cMCclas->cd(3);
	tMCFidReg->Draw("90*acos(kp2labtheta)*cos(kp2labphi*TMath::Pi()) : 90*acos(kp2labtheta)*sin(kp2labphi*TMath::Pi())>>hMCclas_kp2_3","","colz");
	cMCclas->cd(4);
	tMCFidTight->Draw("90*acos(kp2labtheta)*cos(kp2labphi*TMath::Pi()) : 90*acos(kp2labtheta)*sin(kp2labphi*TMath::Pi())>>hMCclas_kp2_4","","colz");
	cMCclas->Print("~/Desktop/clas_kp2_MC.png");

	TH2F *hMCclas_pim=new TH2F("hMCclas_pim","",180,-90,90,180,-90,90);
	hMCclas_pim->GetXaxis()->SetTitle("#theta sin(#phi)  #pi^{-}");
	hMCclas_pim->GetYaxis()->SetTitle("#theta cos(#phi)  #pi^{-}");
	hMCclas_pim->SetTitle("MC");
	TH2F *hMCclas_pim_1= (TH2F*)hMCclas_pim->Clone("hMCclas_pim_1");
	TH2F *hMCclas_pim_2= (TH2F*)hMCclas_pim->Clone("hMCclas_pim_2");
	TH2F *hMCclas_pim_3= (TH2F*)hMCclas_pim->Clone("hMCclas_pim_3");
	TH2F *hMCclas_pim_4= (TH2F*)hMCclas_pim->Clone("hMCclas_pim_4");
	TCanvas *cMCclas=new TCanvas("cMCclas","cMCclas",1000,800);
	cMCclas->Divide(2,2);
	cMCclas->cd(1);
	tMC->Draw("90*acos(pilabtheta)*cos(pilabphi*TMath::Pi()) : 90*acos(pilabtheta)*sin(pilabphi*TMath::Pi())>>hMCclas_pim_1","","colz");
	cMCclas->cd(2);
	tMCFidLoose->Draw("90*acos(pilabtheta)*cos(pilabphi*TMath::Pi()) : 90*acos(pilabtheta)*sin(pilabphi*TMath::Pi())>>hMCclas_pim_2","","colz");
	cMCclas->cd(3);
	tMCFidReg->Draw("90*acos(pilabtheta)*cos(pilabphi*TMath::Pi()) : 90*acos(pilabtheta)*sin(pilabphi*TMath::Pi())>>hMCclas_pim_3","","colz");
	cMCclas->cd(4);
	tMCFidTight->Draw("90*acos(pilabtheta)*cos(pilabphi*TMath::Pi()) : 90*acos(pilabtheta)*sin(pilabphi*TMath::Pi())>>hMCclas_pim_4","","colz");
	cMCclas->Print("~/Desktop/clas_pim_MC.png");

}


//=========================================================================================================================================================================================
//==========================================================================Functions Called===============================================================================================
//=========================================================================================================================================================================================





StyleUp()
{
	gStyle->SetTitleXOffset(0.99);
	gStyle->SetTitleYOffset(1.3);
	gStyle->SetTitleSize(0.04);
	gStyle->SetTitleYSize(0.04);
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
