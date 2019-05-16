#include "/Users/Bono/clas/myDefinitions/Hypersphere.h" 
		
//TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_Xi3.root");
//TTree *tData = (TTree*)fData->Get("v13");
//TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t2-t2-2kppim_Basic_Xi2.root");
//TTree *tMC = (TTree*)fMC->Get("gpp2kppim");

//2016 right here
TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
TTree *tData = (TTree*)fData->Get("v16");



void Yield()
{
		gROOT->ProcessLine(".L /Users/Bono/clas/scripts/new/BgSubtractedYield.C");
	TH1F *his=new TH1F("his","",100,1.28,1.36);  //160   //480
	his->SetMinimum(0);
	his->SetFillColor(4);
	tData->Draw("mlampim>>his");
	int y = GetYield(his);
	
	cout <<" y = "<<y<< " +/- "<< y <<endl;
}



	// TF1 *fSignal = new TF1("fSignal","gaus",1.29,1.35);
	// TF1 *fBackground = new TF1("fBackground","pol4",1.29,1.35);
	// TF1 *fSprectrum = new TF1("fSpectrum","gaus + pol4(3)",1.29,1.35);	
	// fSpectrum->SetParNames("Strenth","Mean","Sigma","P0","P1","P2","P3","P4");
	// fSpectrum->SetParameters(1000,1.32,0.01,0,0,0,0,0);
	// his->Fit("fSpectrum","","",1.29,1.35);
	// cout<<"test"<<endl;
	// Double_t param[8];
	// fSpectrum->GetParameters(param);
	// fSignal->SetParameters(&param[0]);
	// fBackground->SetParameters(&param[3]);
	// TH1D *hisSignal = new TH1D(*his);
	// hisSignal->Sumw2();
	// hisSignal->Add(fBackground,-1);
	// his->Draw("e");hisSignal->Draw("SAME");
	// fSignal->SetLineColor(1);
	// fBackground->SetLineColor(9);
	// fSignal->Draw("Same");fBackground->Draw("SAME");
	// 
	// 
	// Double_t binw = his->GetBinWidth(1);
	// Double_t intSpectrum = fSpectrum->Integral(param[1] - 3*param[2], param[1] + 3*param[2]); //three sigma
	// Int_t YieldSpectrum = intSpectrum/binw;
	// Int_t eYieldSpectrum = sqrt(YieldSpectrum);
	// cout <<" YieldSpectrum = "<<YieldSpectrum<< " +/- "<< eYieldSpectrum <<endl;	
	// Double_t intSignal = fSignal->Integral(param[1] - 3*param[2], param[1] + 3*param[2]); //three sigma
	// Int_t YieldSignal = intSignal/binw;
	// Int_t YieldSignal = intSignal/binw;
	// Int_t eYieldSignal = sqrt(YieldSignal);
	// cout <<" YieldSignal = "<<YieldSignal<< " +/- "<< eYieldSignal <<endl;
