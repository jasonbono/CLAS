/*

Author: Jason Bono
Date: Jan 25 2013
Purpose: To display the spectra of the following quantities for Data and MC :
1) angles between the two kaons,CM angle of Xi
2) momenta of the K1, Momenta of K2
3) M(K1 + Xi-), M(K2 + Xi-)

Usage: 	.L FundemantalSpectra.C
		PlotAngles()
		PlotPionAngles()
		PlotMomenta()
		PlotMass()
		ShowTiming()
		PlotBeam()
		
		
		extra: PlotGen(),GetHyperonWidth

or .x FundemantalSpectra.C 

*/


#include "/Users/Bono/clas/myDefinitions/WBins.h" 
#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"

const int Nb = 2,Nc = 3,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
const char* BinType[Nb] = {"E","Xi"};
const char* BinNumber[Nc] = {"0","1","2"};
const char* Axis[Nd] = {"x","y","z"};


float MASS_Kaon_CHARGED = 0.493677;
float MASS_Pion_CHARGED = 0.13957018; 



TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
TTree *tData = (TTree*)fData->Get("v05");
TFile *fGen = TFile::Open("~/clas/rootfiles/LINKS/MC-i5-gamproot-100.root");
TTree *tGen = (TTree*)fGen->Get("GampTree");


//*///
TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i5-2kppim_Basic_Mass.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
///*///


/*///
TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i5-PosPol-2kppim_Basic_Mass.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
///*///






//TFile *fOrigData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05.root");
//TTree *tOrigData = (TTree*)fOrigData->Get("v05");
//TFile *fOrigMC = TFile::Open("~/clas/rootfiles/LINKS/MC_i4_2kppim.root");
//TTree *tOrigMC = (TTree*)fOrigMC->Get("gpp2kppim");

//-----------------------------------

void FundemantalSpectra()
{
	
	//PlotGen();
	PlotAngles();
	PlotMomenta();
	PlotMass();
	//PlotPionAngles()
	//ShowTiming();
	//PlotBeam();
	//GetHyperonWidth();
	
	
}


void GetHyperonWidth()
{

	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	StyleUp();
		
	
	TCanvas *cGetHyperon=new TCanvas("cGetHyperon","cGetHyperon",1200,800);
	cGetHyperon->Divide(2,2);
	TCanvas *cGetHyperonMC=new TCanvas("cGetHyperonMC","cGetHyperonMC",1200,800);
	cGetHyperonMC->Divide(2,2);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Data~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMassData=new TH1F("hMass","",150,1.5,3);  //1500/150 = 10 MeV
	hMassData->SetMinimum(0);
	hMassData->SetMarkerStyle(21);
	hMassData->SetFillStyle(3002);
	hMassData->SetFillColor(3);
	hMassData->GetYaxis()->SetTitle("Events");
	hMassData->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c) ");
	
	
	//Data
	hHyperonWidthE0 = (TH1F*)hMassData->Clone("hHyperonWidthE0");
	hHyperonWidthE1 = (TH1F*)hMassData->Clone("hHyperonWidthE1");
	hHyperonWidthE2 = (TH1F*)hMassData->Clone("hHyperonWidthE2");
	hHyperonWidthAll = (TH1F*)hMassData->Clone("hHyperonWidthAll");

	int bin1 = 0;
	int bin2 = 0;
	double mass = 0;
	double fwhm = 0;

	//draw the hists
	cGetHyperon->cd(1);
	tData->Draw("mcasmkp2>>hHyperonWidthE0",EBin[0]);
	bin1 = hHyperonWidthE0->FindFirstBinAbove(hHyperonWidthE0->GetMaximum()/2);
   	bin2 = hHyperonWidthE0->FindLastBinAbove(hHyperonWidthE0->GetMaximum()/2);
	mass =  (hHyperonWidthE0->GetBinCenter(bin2) + hHyperonWidthE0->GetBinCenter(bin1))/2;  
  	fwhm = hHyperonWidthE0->GetBinCenter(bin2) - hHyperonWidthE0->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;
	

	bin1 = 0;
	bin2 = 0;
	fwhm = 0;
	cGetHyperon->cd(2);
	tData->Draw("mcasmkp2>>hHyperonWidthE1",EBin[1]);
	bin1 = hHyperonWidthE1->FindFirstBinAbove(hHyperonWidthE1->GetMaximum()/2);
   	bin2 = hHyperonWidthE1->FindLastBinAbove(hHyperonWidthE1->GetMaximum()/2);
	mass =  (hHyperonWidthE1->GetBinCenter(bin2) + hHyperonWidthE1->GetBinCenter(bin1))/2;  
   	fwhm = hHyperonWidthE1->GetBinCenter(bin2) - hHyperonWidthE1->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;
	
	bin1 = 0;
	bin2 = 0;
	fwhm = 0;
	cGetHyperon->cd(3);
	tData->Draw("mcasmkp2>>hHyperonWidthE2",EBin[2]);
	bin1 = hHyperonWidthE2->FindFirstBinAbove(hHyperonWidthE2->GetMaximum()/2);
   	bin2 = hHyperonWidthE2->FindLastBinAbove(hHyperonWidthE2->GetMaximum()/2);
	mass =  (hHyperonWidthE2->GetBinCenter(bin2) + hHyperonWidthE2->GetBinCenter(bin1))/2;  
   	fwhm = hHyperonWidthE2->GetBinCenter(bin2) - hHyperonWidthE2->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;
	
	
	bin1 = 0;
	bin2 = 0;
	fwhm = 0;
	cGetHyperon->cd(4);
	tData->Draw("mcasmkp2>>hHyperonWidthAll");
	bin1 = hHyperonWidthAll->FindFirstBinAbove(hHyperonWidthAll->GetMaximum()/2);
   	bin2 = hHyperonWidthAll->FindLastBinAbove(hHyperonWidthAll->GetMaximum()/2);
	mass =  (hHyperonWidthAll->GetBinCenter(bin2) + hHyperonWidthAll->GetBinCenter(bin1))/2;  
   	fwhm = hHyperonWidthAll->GetBinCenter(bin2) - hHyperonWidthAll->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//histos
	//model
	TH1F *hMassMC=new TH1F("hMass","",80,1.6,2.4);  //800/80 = 40 MeV
	hMassMC->SetMinimum(0);
	hMassMC->SetMarkerStyle(21);
	hMassMC->SetFillStyle(3002);
	hMassMC->SetFillColor(2);
	hMassMC->GetYaxis()->SetTitle("Events");
	hMassMC->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c) ");


	//MC
	hHyperonWidthE0MC = (TH1F*)hMassMC->Clone("hHyperonWidthE0MC");
	hHyperonWidthE1MC = (TH1F*)hMassMC->Clone("hHyperonWidthE1MC");
	hHyperonWidthE2MC = (TH1F*)hMassMC->Clone("hHyperonWidthE2MC");
	hHyperonWidthAllMC = (TH1F*)hMassMC->Clone("hHyperonWidthAllMC");

	int bin1 = 0;
	int bin2 = 0;
	double fwhm = 0;

	//draw the hists
	cGetHyperonMC->cd(1);
	tMC->Draw("mcasmkp2>>hHyperonWidthE0MC",EBin[0]);
	bin1 = hHyperonWidthE0MC->FindFirstBinAbove(hHyperonWidthE0MC->GetMaximum()/2);
	bin2 = hHyperonWidthE0MC->FindLastBinAbove(hHyperonWidthE0MC->GetMaximum()/2);
	mass =  (hHyperonWidthE0MC->GetBinCenter(bin2) + hHyperonWidthE0MC->GetBinCenter(bin1))/2;  
	fwhm = hHyperonWidthE0MC->GetBinCenter(bin2) - hHyperonWidthE0MC->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;


	bin1 = 0;
	bin2 = 0;
	fwhm = 0;
	cGetHyperonMC->cd(2);
	tMC->Draw("mcasmkp2>>hHyperonWidthE1MC",EBin[1]);
	bin1 = hHyperonWidthE1MC->FindFirstBinAbove(hHyperonWidthE1MC->GetMaximum()/2);
	bin2 = hHyperonWidthE1MC->FindLastBinAbove(hHyperonWidthE1MC->GetMaximum()/2);
	mass =  (hHyperonWidthE1MC->GetBinCenter(bin2) + hHyperonWidthE1MC->GetBinCenter(bin1))/2;  
	fwhm = hHyperonWidthE1MC->GetBinCenter(bin2) - hHyperonWidthE1MC->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;

	bin1 = 0;
	bin2 = 0;
	fwhm = 0;
	cGetHyperonMC->cd(3);
	tMC->Draw("mcasmkp2>>hHyperonWidthE2MC",EBin[2]);
	bin1 = hHyperonWidthE2MC->FindFirstBinAbove(hHyperonWidthE2MC->GetMaximum()/2);
	bin2 = hHyperonWidthE2MC->FindLastBinAbove(hHyperonWidthE2MC->GetMaximum()/2);
	mass =  (hHyperonWidthE2MC->GetBinCenter(bin2) + hHyperonWidthE2MC->GetBinCenter(bin1))/2;  
	fwhm = hHyperonWidthE2MC->GetBinCenter(bin2) - hHyperonWidthE2MC->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;


	bin1 = 0;
	bin2 = 0;
	fwhm = 0;
	cGetHyperonMC->cd(4);
	tMC->Draw("mcasmkp2>>hHyperonWidthAllMC");
	bin1 = hHyperonWidthAllMC->FindFirstBinAbove(hHyperonWidthAllMC->GetMaximum()/2);
	bin2 = hHyperonWidthAllMC->FindLastBinAbove(hHyperonWidthAllMC->GetMaximum()/2);
	mass =  (hHyperonWidthAllMC->GetBinCenter(bin2) + hHyperonWidthAllMC->GetBinCenter(bin1))/2;  
	fwhm = hHyperonWidthAllMC->GetBinCenter(bin2) - hHyperonWidthAllMC->GetBinCenter(bin1);
	cout << "bin1,bin2,mass,fwhm = " <<bin1<<", "<<bin2<<", " <<mass<<", "<<fwhm<<endl;


	//cCompareMassK2Xi->Print("./pics/CompareMassK2Xi_overlay.eps");
	//gROOT->ProcessLine(".q");
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
	
	StyleUp();
	
	
	//Get W factor
	Float_t W[NWBins] = {0};
	Float_t Werr[NWBins] = {0};
	readWfile(W, Werr);
	

	
	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Xi angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	//histos
	//model
	TH1F *hAngles=new TH1F("hAngles","",25,-1,1); 
	hAngles->SetMinimum(0);
	hAngles->SetMarkerStyle(21);
	//Data
	hXiAnglesData = (TH1F*)hAngles->Clone("hXiAnglesData");
	hXiAnglesData->SetMinimum(0);
	hXiAnglesData->GetYaxis()->SetTitle("Events");
	hXiAnglesData->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");
	//MC
	hXiAnglesMC = (TH1F*)hAngles->Clone("hXiAnglesMC");
	hXiAnglesMC->SetMinimum(0);
	hXiAnglesMC->GetYaxis()->SetTitle("Events");
	hXiAnglesMC->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");
	//MC_Wtot (with beam energy spectrum matched)
	hXiAnglesMC_Wtot = (TH1F*)hAngles->Clone("hXiAnglesMC_Wtot");
	hXiAnglesMC_Wtot->SetMinimum(0);
	hXiAnglesMC_Wtot->GetYaxis()->SetTitle("Events");
	hXiAnglesMC_Wtot->GetXaxis()->SetTitle("#Theta^{#Xi^{-}}_{cm} ");
	
	TH1F *hXiAnglesMC_W[NWBins];

	
	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hXiAnglesMC_W[k] = (TH1F*)hAngles->Clone(Form("hXiAnglesMC_W%i",k));
		tMC->Draw(Form("Xcmtheta>>hXiAnglesMC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hXiAnglesMC_W[k]->GetEntries() <<endl;	
		hXiAnglesMC_Wtot->Add(hXiAnglesMC_W[k],W[k]);	
		cout << "# of entries in tot: " << hXiAnglesMC_Wtot->GetEntries() <<endl;
	}
	
	//draw the hists
	cblank->cd(0);
	//TCanvas *cXiAnglesData=new TCanvas("cXiAnglesData","cXiAnglesData",1200,800);
	tData->Draw("Xcmtheta>>hXiAnglesData");
	//TCanvas *cXiAnglesMC=new TCanvas("cXiAnglesMC","cXiAnglesMC",1200,800);
	tMC->Draw("Xcmtheta>>hXiAnglesMC");
	//TCanvas *cXiAnglesMC_Wtot=new TCanvas("cXiAnglesMC_Wtot","cXiAnglesMC_Wtot",1200,800);
	hXiAnglesMC_Wtot->Draw();

	//cXiAnglesData->Print("./pics/CompareXiAngleData.eps");
	//cXiAnglesMC->Print("./pics/CompareXiAngleMC.eps");
	//cXiAnglesMC_Wtot->Print("./pics/CompareXiAngleMC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareXiAngles=new TCanvas("cCompareXiAngles","cCompareXiAngles",1200,800);
	hXiAnglesData->SetMarkerStyle(21);
	hXiAnglesData->SetFillColor(3);
	hXiAnglesData->Draw();
	hXiAnglesMC_Wtot->SetMarkerStyle(21);
	hXiAnglesMC_Wtot->SetFillStyle(3002);
	hXiAnglesMC_Wtot->SetFillColor(2);
	hXiAnglesMC_Wtot->Draw("SAME");
	cCompareXiAngles->Print("./pics/CompareXiAngles_overlay.eps");
	cblank->cd(0);
	//..................................................................................................


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~kaon angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	//histos
	//model
	TH1F *hAngles=new TH1F("hAngles","",25,-1,1);
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
	//MC_Wtot (with beam energy spectrum matched)
	hKaonAnglesMC_Wtot = (TH1F*)hAngles->Clone("hKaonAnglesMC_Wtot");
	hKaonAnglesMC_Wtot->SetMinimum(0);
	hKaonAnglesMC_Wtot->GetYaxis()->SetTitle("Events");
	hKaonAnglesMC_Wtot->GetXaxis()->SetTitle("#Theta^{Kaons}_{cm}");
	
	TH1F *hKaonAnglesMC_W[NWBins];

	
	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hKaonAnglesMC_W[k] = (TH1F*)hAngles->Clone(Form("hKaonAnglesMC_W%i",k));
		tMC->Draw(Form("(sin(kp1labtheta)*sin(kp2labtheta)*cos(kp1labphi)*cos(kp2labphi) + sin(kp1labtheta)*sin(kp2labtheta)*sin(kp1labphi)*sin(kp2labphi) + cos(kp1labtheta)*cos(kp2labtheta))>>hKaonAnglesMC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hKaonAnglesMC_W[k]->GetEntries() <<endl;	
		hKaonAnglesMC_Wtot->Add(hKaonAnglesMC_W[k],W[k]);	
		cout << "# of entries in tot: " << hKaonAnglesMC_Wtot->GetEntries() <<endl;
	}
	//"(sin(kp1labtheta)*sin(kp2labtheta)*cos(kp1labphi)*cos(kp2labphi) + sin(kp1labtheta)*sin(kp2labtheta)*sin(kp1labphi)*sin(kp2labphi) + cos(kp1labtheta)*cos(kp2labtheta)"
	//draw the hists
	cblank->cd(0);
	//TCanvas *cKaonAnglesData=new TCanvas("cKaonAnglesData","cKaonAnglesData",1200,800);
	tData->Draw("(sin(kp1labtheta)*sin(kp2labtheta)*cos(kp1labphi)*cos(kp2labphi) + sin(kp1labtheta)*sin(kp2labtheta)*sin(kp1labphi)*sin(kp2labphi) + cos(kp1labtheta)*cos(kp2labtheta))>>hKaonAnglesData");
	//TCanvas *cKaonAnglesMC=new TCanvas("cKaonAnglesMC","cKaonAnglesMC",1200,800);
	tMC->Draw("(sin(kp1labtheta)*sin(kp2labtheta)*cos(kp1labphi)*cos(kp2labphi) + sin(kp1labtheta)*sin(kp2labtheta)*sin(kp1labphi)*sin(kp2labphi) + cos(kp1labtheta)*cos(kp2labtheta))>>hKaonAnglesMC");
	//TCanvas *cKaonAnglesMC_Wtot=new TCanvas("cKaonAnglesMC_Wtot","cKaonAnglesMC_Wtot",1200,800);
	hKaonAnglesMC_Wtot->Draw();
	//cblank->cd(0);
	//cKaonAnglesData->Print("./pics/CompareKaonAngleData.eps");
	//cKaonAnglesMC->Print("./pics/CompareKaonAngleMC.eps");
	//cKaonAnglesMC_Wtot->Print("./pics/CompareKaonAngleMC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareKaonAngles=new TCanvas("cCompareKaonAngles","cCompareKaonAngles",1200,800);
	hKaonAnglesData->SetMarkerStyle(21);
	hKaonAnglesData->SetFillColor(3);
	hKaonAnglesData->SetMaximum(hKaonAnglesMC_Wtot->GetMaximum());
	hKaonAnglesData->Draw();
	hKaonAnglesMC_Wtot->SetMarkerStyle(21);
	hKaonAnglesMC_Wtot->SetFillStyle(3002);
	hKaonAnglesMC_Wtot->SetFillColor(2);
	hKaonAnglesMC_Wtot->Draw("SAME");

	cCompareKaonAngles->Print("./pics/CompareKaonAngles_overlay.eps");
	cblank->cd(0);
//	gROOT->ProcessLine(".q");
}
	//............................................................................................................................................................................





void PlotPionAngles()
{
	StyleUp();
	//Get W factor
	Float_t W[NWBins] = {0};
	Float_t Werr[NWBins] = {0};
	readWfile(W, Werr);
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
	TH1F* hPiMC_W[Nb][Nc][Nd][NWBins];
	TH1F* hPiMC_Wtot[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				hPiData[b][c][d] = (TH1F*)hAngles->Clone(Form("hPiData-%sBin%s-PiAxis%s",BinType[b],BinNumber[c],Axis[d]));
				hPiData[b][c][d]->GetYaxis()->SetTitle("Events");
				hPiData[b][c][d]->GetXaxis()->SetTitle(Form("#Theta^{#pi^{-}}_{%s}  %sBin%s ",Axis[d],BinType[b],BinNumber[c]));
				tData->Draw(Form("COS_pi_%s>>hPiData-%sBin%s-PiAxis%s",Axis[d],BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]);
				hPiMC[b][c][d] = (TH1F*)hAngles->Clone(Form("hPiMC-%sBin%s-PiAxis%s",BinType[b],BinNumber[c],Axis[d]));
				tMC->Draw(Form("COS_pi_%s>>hPiMC-%sBin%s-PiAxis%s",Axis[d],BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]);
				hPiMC_Wtot[b][c][d] = (TH1F*)hAngles->Clone(Form("hPiMC_Wtot-%sBin%s-PiAxis%s",BinType[b],BinNumber[c],Axis[d]));
				for (int k = 0; k < NWBins ; k++) 
				{
					hPiMC_W[b][c][d][k] = (TH1F*)hAngles->Clone(Form("hPiMC_W%i-%sBin%s-PiAxis%s",k,BinType[b],BinNumber[c],Axis[d]));
					tMC->Draw(Form("COS_pi_%s>>hPiMC_W%i-%sBin%s-PiAxis%s",Axis[d],k,WBin[k],BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]&&WBin[k]);
					
					cout << "# Of Entries In W Bin: " << hPiMC_W[b][c][d][k]->GetEntries() <<endl;	
					hPiMC_Wtot[b][c][d]->Add(hPiMC_W[b][c][d][k],W[k]);
					cout << "# Of Entries In tot: " << hPiMC_W[b][c][d][k]->GetEntries() <<endl;
					
				}
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
				
				hPiMC_Wtot[b][c][d]->SetMarkerStyle(21);
				hPiMC_Wtot[b][c][d]->SetFillStyle(3002);
				hPiMC_Wtot[b][c][d]->SetFillColor(2);
				hPiMC_Wtot[b][c][d]->Draw("SAME");

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
	//MC_Wtot (with beam energy spectrum matched)
	hPixMC_Wtot = (TH1F*)hPixData->Clone("hPixMC_Wtot");
	hPiyMC_Wtot = (TH1F*)hPiyData->Clone("hPiyMC_Wtot");
	hPizMC_Wtot = (TH1F*)hPizData->Clone("hPizMC_Wtot");	
	
	TH1F *hPixMC_W[NWBins];
	TH1F *hPiyMC_W[NWBins];	
	TH1F *hPizMC_W[NWBins];	
	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hPixMC_W[k] = (TH1F*)hAngles->Clone(Form("hPixMC_W%i",k));
		hPiyMC_W[k] = (TH1F*)hAngles->Clone(Form("hPiyMC_W%i",k));
		hPizMC_W[k] = (TH1F*)hAngles->Clone(Form("hPizMC_W%i",k));
		tMC->Draw(Form("COS_pi_x>>hPixMC_W%i",k),WBin[k]);
		tMC->Draw(Form("COS_pi_y>>hPiyMC_W%i",k),WBin[k]);
		tMC->Draw(Form("COS_pi_z>>hPizMC_W%i",k),WBin[k]);
		
		cout << "# of entries in W Bin: " << hPixMC_W[k]->GetEntries() <<endl;	
		hPixMC_Wtot->Add(hPixMC_W[k],W[k]);	
		hPiyMC_Wtot->Add(hPiyMC_W[k],W[k]);	
		hPizMC_Wtot->Add(hPizMC_W[k],W[k]);	
		cout << "# of entries in tot: " << hPixMC_Wtot->GetEntries() <<endl;
	}
	
	//fill the hists
	cblank->cd(0);

	tData->Draw("COS_pi_x>>hPixData");
	tData->Draw("COS_pi_y>>hPiyData");
	tData->Draw("COS_pi_z>>hPizData");
	tMC->Draw("COS_pi_x>>hPixMC");
	tMC->Draw("COS_pi_y>>hPiyMC");
	tMC->Draw("COS_pi_z>>hPizMC");

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
	hPixMC_Wtot->SetMarkerStyle(21);
	hPixMC_Wtot->SetFillStyle(3002);
	hPixMC_Wtot->SetFillColor(2);
	hPiyMC_Wtot->SetMarkerStyle(21);
	hPiyMC_Wtot->SetFillStyle(3002);
	hPiyMC_Wtot->SetFillColor(2);
	hPizMC_Wtot->SetMarkerStyle(21);
	hPizMC_Wtot->SetFillStyle(3002);
	hPizMC_Wtot->SetFillColor(2);
	cPiIntegrated->cd(1);
	hPixMC_Wtot->Draw("SAME");
	cPiIntegrated->cd(2);
	hPiyMC_Wtot->Draw("SAME");
	cPiIntegrated->cd(3);
	hPizMC_Wtot->Draw("SAME");	
	cPiIntegrated->Print("./pics/ComparePiAngles_overlay.eps");
	cblank->cd(0);
}
	//............................................................................................................................................................................






void PlotMomenta()
{
	StyleUp();
	

	
	//Get W factor
	Float_t W[NWBins] = {0};
	Float_t Werr[NWBins] = {0};
	readWfile(W, Werr);
	

	
	TCanvas *cblank=new TCanvas("cblank","cblank",12,8);
	
	//*///<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Kp1 momentum spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	//histos
	//model
	TH1F *hMomenta=new TH1F("hMomenta","",30,0,3); // 3000/30 = 100MeV
	hMomenta->SetMinimum(0);
	hMomenta->SetMarkerStyle(21);
	//Data
	hMomentaK1Data = (TH1F*)hMomenta->Clone("hMomentaK1Data");
	hMomentaK1Data->SetMinimum(0);
	hMomentaK1Data->GetYaxis()->SetTitle("Events");
	hMomentaK1Data->GetXaxis()->SetTitle("p^{k^{+}_{fast}} (GeV/c) ");
	//MC
	hMomentaK1MC = (TH1F*)hMomenta->Clone("hMomentaK1MC");
	hMomentaK1MC->SetMinimum(0);
	hMomentaK1MC->GetYaxis()->SetTitle("Events");
	hMomentaK1MC->GetXaxis()->SetTitle("p^{k^{+}_{fast}} (GeV/c)");
	//MC_Wtot (with beam energy spectrum matched)
	hMomentaK1MC_Wtot = (TH1F*)hMomenta->Clone("hMomentaK1MC_Wtot");
	hMomentaK1MC_Wtot->SetMinimum(0);
	hMomentaK1MC_Wtot->GetYaxis()->SetTitle("Events");
	hMomentaK1MC_Wtot->GetXaxis()->SetTitle("p^{k^{+}_{fast}} (GeV/c)");
	
	TH1F *hMomentaK1MC_W[NWBins];

	
	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hMomentaK1MC_W[k] = (TH1F*)hMomenta->Clone(Form("hMomentaK1MC_W%i",k));
		tMC->Draw(Form("pkp1>>hMomentaK1MC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hMomentaK1MC_W[k]->GetEntries() <<endl;	
		hMomentaK1MC_Wtot->Add(hMomentaK1MC_W[k],W[k]);
		cout << "# of entries in tot: " << hMomentaK1MC_Wtot->GetEntries() <<endl;
	}
	
	//draw the hists
	cblank->cd(0);
	//TCanvas *cMomentaK1Data=new TCanvas("cMomentaK1Data","cMomentaK1Data",1200,800);
	tData->Draw("pkp1>>hMomentaK1Data");
	//TCanvas *cMomentaK1MC=new TCanvas("cMomentaK1MC","cMomentaK1MC",1200,800);
	tMC->Draw("pkp1>>hMomentaK1MC");
	//TCanvas *cMomentaK1MC_Wtot=new TCanvas("cMomentaK1MC_Wtot","cMomentaK1MC_Wtot",1200,800);
	hMomentaK1MC_Wtot->Draw();
	cblank->cd(0);
	//cMomentaK1Data->Print("./pics/CompareMomentaK1Data.eps");
	//cMomentaK1MC->Print("./pics/CompareMomentaK1MC.eps");
	//cMomentaK1MC_Wtot->Print("./pics/CompareMomentaK1MC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareMomentaK1=new TCanvas("cCompareMomentaK1","cCompareMomentaK1",1200,800);
	hMomentaK1Data->SetMarkerStyle(21);
	hMomentaK1Data->SetFillColor(3);
	hMomentaK1Data->Draw();
	hMomentaK1MC_Wtot->SetMarkerStyle(21);
	hMomentaK1MC_Wtot->SetFillStyle(3002);
	hMomentaK1MC_Wtot->SetFillColor(2);
	hMomentaK1MC_Wtot->Draw("SAME");
	cCompareMomentaK1->Print("./pics/CompareMomentaK1_overlay.eps");
	cblank->cd(0);
	//*///..................................................................................................
	
	
	//*///<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Kp2 momentum spectrum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	//histos
	//model
	TH1F *hMomenta=new TH1F("hMomenta","",30,0,3);  // 3000 / 30 = 100MeV
	hMomenta->SetMinimum(0);
	hMomenta->SetMarkerStyle(21);
	//Data
	hMomentaK2Data = (TH1F*)hMomenta->Clone("hMomentaK2Data");
	hMomentaK2Data->SetMinimum(0);
	hMomentaK2Data->GetYaxis()->SetTitle("Events");
	hMomentaK2Data->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c) ");
	//MC
	hMomentaK2MC = (TH1F*)hMomenta->Clone("hMomentaK2MC");
	hMomentaK2MC->SetMinimum(0);
	hMomentaK2MC->GetYaxis()->SetTitle("Events");
	hMomentaK2MC->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c)");
	//MC_Wtot (with beam energy spectrum matched)
	hMomentaK2MC_Wtot = (TH1F*)hMomenta->Clone("hMomentaK2MC_Wtot");
	hMomentaK2MC_Wtot->SetMinimum(0);
	hMomentaK2MC_Wtot->GetYaxis()->SetTitle("Events");
	hMomentaK2MC_Wtot->GetXaxis()->SetTitle("p^{k^{+}_{slow}} (GeV/c)");
	
	TH1F *hMomentaK2MC_W[NWBins];

	
	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hMomentaK2MC_W[k] = (TH1F*)hMomenta->Clone(Form("hMomentaK2MC_W%i",k));
		tMC->Draw(Form("pkp2>>hMomentaK2MC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hMomentaK2MC_W[k]->GetEntries() <<endl;	
		hMomentaK2MC_Wtot->Add(hMomentaK2MC_W[k],W[k]);	
		cout << "# of entries in tot: " << hMomentaK2MC_Wtot->GetEntries() <<endl;
	}
	
	//draw the hists
	cblank->cd(0);
	//TCanvas *cMomentaK2Data=new TCanvas("cMomentaK2Data","cMomentaK2Data",1200,800);
	tData->Draw("pkp2>>hMomentaK2Data");
	//TCanvas *cMomentaK2MC=new TCanvas("cMomentaK2MC","cMomentaK2MC",1200,800);
	tMC->Draw("pkp2>>hMomentaK2MC");
	//TCanvas *cMomentaK2MC_Wtot=new TCanvas("cMomentaK2MC_Wtot","cMomentaK2MC_Wtot",1200,800);
	hMomentaK2MC_Wtot->Draw();
	cblank->cd(0);
	//cMomentaK2Data->Print("./pics/CompareMomentaK2Data.eps");
	//cMomentaK2MC->Print("./pics/CompareMomentaK2MC.eps");
	//cMomentaK2MC_Wtot->Print("./pics/CompareMomentaK2MC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareMomentaK2=new TCanvas("cCompareMomentaK2","cCompareMomentaK2",1200,800);
	hMomentaK2Data->SetMarkerStyle(21);
	hMomentaK2Data->SetFillColor(3);
	hMomentaK2Data->Draw();
	hMomentaK2MC_Wtot->SetMarkerStyle(21);
	hMomentaK2MC_Wtot->SetFillStyle(3002);
	hMomentaK2MC_Wtot->SetFillColor(2);
	hMomentaK2MC_Wtot->Draw("SAME");
	cCompareMomentaK2->Print("./pics/CompareMomentaK2_overlay.eps");
	cblank->cd(0);
	//gROOT->ProcessLine(".q");

}
	//*///..................................................................................................


void PlotMass()
{
	
	StyleUp();
		
	//get cuts
	
	//Get W factor
	Float_t W[NWBins] = {0};
	Float_t Werr[NWBins] = {0};
	readWfile(W, Werr);


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
	hMassK1XiData->GetYaxis()->SetTitle("Events");
	hMassK1XiData->GetXaxis()->SetTitle("m(#Xi^{-} k^{+}_{fast}) (GeV/c^2)");
	//MC
	hMassK1XiMC = (TH1F*)hMass->Clone("hMassK1XiMC");
	hMassK1XiMC->SetMinimum(0);
	hMassK1XiMC->GetYaxis()->SetTitle("Events");
	hMassK1XiMC->GetXaxis()->SetTitle("m(#Xi^{-} k^{+}_{fast}) (GeV/c^2) ");
	//MC_Wtot (with beam energy spectrum matched)
	hMassK1XiMC_Wtot = (TH1F*)hMass->Clone("hMassK1XiMC_Wtot");
	hMassK1XiMC_Wtot->SetMinimum(0);
	hMassK1XiMC_Wtot->GetYaxis()->SetTitle("Events");
	hMassK1XiMC_Wtot->GetXaxis()->SetTitle("m(#Xi^{-} k^{+}_{fast}) (GeV/c^2) ");

	TH1F *hMassK1XiMC_W[NWBins];


	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hMassK1XiMC_W[k] = (TH1F*)hMass->Clone(Form("hMassK1XiMC_W%i",k));
		tMC->Draw(Form("mcasmkp1>>hMassK1XiMC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hMassK1XiMC_W[k]->GetEntries() <<endl;	
		hMassK1XiMC_Wtot->Add(hMassK1XiMC_W[k],W[k]);
		cout << "# of entries in tot: " << hMassK1XiMC_Wtot->GetEntries() <<endl;
	}

	//draw the hists
	cblank->cd(0);
	//TCanvas *cMassK1XiData=new TCanvas("cMassK1XiData","cMassK1XiData",1200,800);
	tData->Draw("mcasmkp1>>hMassK1XiData");
	//TCanvas *cMassK1XiMC=new TCanvas("cMassK1XiMC","cMassK1XiMC",1200,800);
	tMC->Draw("mcasmkp1>>hMassK1XiMC");
	//TCanvas *cMassK1XiMC_Wtot=new TCanvas("cMassK1XiMC_Wtot","cMassK1XiMC_Wtot",1200,800);
	hMassK1XiMC_Wtot->Draw();
	cblank->cd(0);
	//cMassK1XiData->Print("./pics/CompareMassK1XiData.eps");
	//cMassK1XiMC->Print("./pics/CompareMassK1XiMC.eps");
	//cMassK1XiMC_Wtot->Print("./pics/CompareMassK1XiMC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareMassK1Xi=new TCanvas("cCompareMassK1Xi","cCompareMassK1Xi",1200,800);
	hMassK1XiData->SetMarkerStyle(21);
	hMassK1XiData->SetFillColor(3);
	hMassK1XiData->Draw();
	hMassK1XiMC_Wtot->SetMarkerStyle(21);
	hMassK1XiMC_Wtot->SetFillStyle(3002);
	hMassK1XiMC_Wtot->SetFillColor(2);
	hMassK1XiMC_Wtot->Draw("SAME");
	cCompareMassK1Xi->Print("./pics/CompareMassK1Xi_overlay.eps");
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
	hMassK2XiData->GetYaxis()->SetTitle("Events");
	hMassK2XiData->GetXaxis()->SetTitle(" m(#Xi^{-} k^{+}_{slow}) (GeV/c^2) ");
	//MC
	hMassK2XiMC = (TH1F*)hMass->Clone("hMassK2XiMC");
	hMassK2XiMC->SetMinimum(0);
	hMassK2XiMC->GetYaxis()->SetTitle("Events");
	hMassK2XiMC->GetXaxis()->SetTitle("m(#Xi^{-} k^{+}_{slow}) (GeV/c)");
	//MC_Wtot (with beam energy spectrum matched)
	hMassK2XiMC_Wtot = (TH1F*)hMass->Clone("hMassK2XiMC_Wtot");
	hMassK2XiMC_Wtot->SetMinimum(0);
	hMassK2XiMC_Wtot->GetYaxis()->SetTitle("Events");
	hMassK2XiMC_Wtot->GetXaxis()->SetTitle("m(#Xi^{-} k^{+}_{slow}) (GeV/c)");

	TH1F *hMassK2XiMC_W[NWBins];


	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hMassK2XiMC_W[k] = (TH1F*)hMass->Clone(Form("hMassK2XiMC_W%i",k));
		tMC->Draw(Form("mcasmkp2>>hMassK2XiMC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hMassK2XiMC_W[k]->GetEntries() <<endl;	
		hMassK2XiMC_Wtot->Add(hMassK2XiMC_W[k],W[k]);	
		cout << "# of entries in tot: " << hMassK2XiMC_Wtot->GetEntries() <<endl;
	}

	//draw the hists
	cblank->cd(0);
	//TCanvas *cMassK2XiData=new TCanvas("cMassK2XiData","cMassK2XiData",1200,800);
	tData->Draw("mcasmkp2>>hMassK2XiData");
	//TCanvas *cMassK2XiMC=new TCanvas("cMassK2XiMC","cMassK2XiMC",1200,800);
	tMC->Draw("mcasmkp2>>hMassK2XiMC");
	//TCanvas *cMassK2XiMC_Wtot=new TCanvas("cMassK2XiMC_Wtot","cMassK2XiMC_Wtot",1200,800);
	hMassK2XiMC_Wtot->Draw();
	cblank->cd(0);
	//cMassK2XiData->Print("./pics/CompareMassK2XiData.eps");
	//cMassK2XiMC->Print("./pics/CompareMassK2XiMC.eps");
	//cMassK2XiMC_Wtot->Print("./pics/CompareMassK2XiMC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareMassK2Xi=new TCanvas("cCompareMassK2Xi","cCompareMassK2Xi",1200,800);
	hMassK2XiData->SetMarkerStyle(21);
	hMassK2XiData->SetFillColor(3);
	hMassK2XiData->Draw();
	hMassK2XiMC_Wtot->SetMarkerStyle(21);
	hMassK2XiMC_Wtot->SetFillStyle(3002);
	hMassK2XiMC_Wtot->SetFillColor(2);
	hMassK2XiMC_Wtot->Draw("SAME");
	cCompareMassK2Xi->Print("./pics/CompareMassK2Xi_overlay.eps");
	
	//gROOT->ProcessLine(".q");
}
	






void PlotBeam()
{
	
	StyleUp();
		
	
	//Get W factor
	Float_t W[NWBins] = {0};
	Float_t Werr[NWBins] = {0};
	readWfile(W, Werr);


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
	//MC_Wtot (with beam energy spectrum matched)
	hBeamMC_Wtot = (TH1F*)hBeam->Clone("hBeamMC_Wtot");
	hBeamMC_Wtot->SetMinimum(0);
	hBeamMC_Wtot->GetYaxis()->SetTitle("Events");
	hBeamMC_Wtot->GetXaxis()->SetTitle("Beam Energy (GeV/c^2) ");

	TH1F *hBeamMC_W[NWBins];


	for (int k = 0; k < NWBins ; k++) 
	{
		cout << "now: W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		hBeamMC_W[k] = (TH1F*)hBeam->Clone(Form("hBeamMC_W%i",k));
		tMC->Draw(Form("beam>>hBeamMC_W%i",k),WBin[k]);
		cout << "# of entries in W Bin: " << hBeamMC_W[k]->GetEntries() <<endl;	
		hBeamMC_Wtot->Add(hBeamMC_W[k],W[k]);
		cout << "# of entries in tot: " << hBeamMC_Wtot->GetEntries() <<endl;
	}

	//draw the hists
	cblank->cd(0);
	//TCanvas *cBeamData=new TCanvas("cBeamData","cBeamData",1200,800);
	tData->Draw("beam>>hBeamData");
	//TCanvas *cBeamMC=new TCanvas("cBeamMC","cBeamMC",1200,800);
	tMC->Draw("beam>>hBeamMC");
	//TCanvas *cBeamMC_Wtot=new TCanvas("cBeamMC_Wtot","cBeamMC_Wtot",1200,800);
	hBeamMC_Wtot->Draw();
	cblank->cd(0);
	//cBeamData->Print("./pics/CompareBeamData.eps");
	//cBeamMC->Print("./pics/CompareBeamMC.eps");
	//cBeamMC_Wtot->Print("./pics/CompareBeamMC_Wtot.eps");
	
	//for thesis
	TCanvas *cCompareBeam=new TCanvas("cCompareBeam","cCompareBeam",1200,800);
	hBeamData->SetMarkerStyle(21);
	hBeamData->SetFillColor(3);
	hBeamData->Draw();
	hBeamMC_Wtot->SetMarkerStyle(21);
	hBeamMC_Wtot->SetFillStyle(3002);
	hBeamMC_Wtot->SetFillColor(2);
	hBeamMC_Wtot->Draw("SAME");
	cCompareBeam->Print("./pics/CompareBeam_overlay.eps");
	cblank->cd(0);

	//gROOT->ProcessLine(".q");
}



void ShowTiming()
{
	//StyleUp();

	TH1F *hTime=new TH1F("hTime","",100,-3,3); // 4000/400 = 10 MeV
	hTime->SetMinimum(0);
	hTime->GetYaxis()->SetTitle("Events");
	hTime->GetXaxis()->SetTitle("Timing Difference (ns) ");
	hTime->SetMarkerStyle(21);

	//Data before basic cuts
	TCanvas *cOrigDataTime=new TCanvas("cOrigDataTime","cOrigDataTime",1500,1000);
	cOrigDataTime->Divide(3,1);
	cOrigDataTime->cd(1);
	hOrigDataST = (TH1F*)hTime->Clone("hOrigDataST");
	hOrigDataST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tOrigData->Draw("stv-scv>>hOrigDataST");	
	cOrigDataTime->cd(2);	
	hOrigDataTOF1 = (TH1F*)hTime->Clone("hOrigDataTOF1");
	hOrigDataTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tOrigData->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hOrigDataTOF1");
	cOrigDataTime->cd(3);
	hOrigDataTOF2 = (TH1F*)hTime->Clone("hOrigDataTOF2");
	hOrigDataTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tOrigData->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hOrigDataTOF2");


	//Data after basic cuts
	TCanvas *cDataTime=new TCanvas("cDataTime","cDataTime",1500,1000);
	cDataTime->Divide(3,1);
	cDataTime->cd(1);
	hDataST = (TH1F*)hTime->Clone("hDataST");
	hDataST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tData->Draw("stv-scv>>hDataST");	
	cDataTime->cd(2);	
	hDataTOF1 = (TH1F*)hTime->Clone("hDataTOF1");
	hDataTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tData->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hDataTOF1");
	cDataTime->cd(3);
	hDataTOF2 = (TH1F*)hTime->Clone("hDataTOF2");
	hDataTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tData->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hDataTOF2");



	//MC before basic cuts
	TCanvas *cOrigMCTime=new TCanvas("cOrigMCTime","cOrigMCTime",1500,1000);
	cOrigMCTime->Divide(3,1);
	cOrigMCTime->cd(1);
	hOrigMCST = (TH1F*)hTime->Clone("hOrigMCST");
	hOrigMCST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tOrigMC->Draw("stv-scv>>hOrigMCST");	
	cOrigMCTime->cd(2);	
	hOrigMCTOF1 = (TH1F*)hTime->Clone("hOrigMCTOF1");
	hOrigMCTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tOrigMC->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hOrigMCTOF1");
	cOrigMCTime->cd(3);
	hOrigMCTOF2 = (TH1F*)hTime->Clone("hOrigMCTOF2");
	hOrigMCTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tOrigMC->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hOrigMCTOF2");


	//MC after basic cuts
	TCanvas *cMCTime=new TCanvas("cMCTime","cMCTime",1500,1000);
	cMCTime->Divide(3,1);
	cMCTime->cd(1);
	hMCST = (TH1F*)hTime->Clone("hMCST");
	hMCST->GetXaxis()->SetTitle(" stv - scv (ns) ");
	tMC->Draw("stv-scv>>hMCST");	
	cMCTime->cd(2);	
	hMCTOF1 = (TH1F*)hTime->Clone("hMCTOF1");
	hMCTOF1->GetXaxis()->SetTitle("RF - kp1TOF (ns)  ");
	tMC->Draw("vtime-(sctkp1-sclkp1/(betakp1*29.99))>>hMCTOF1");
	cMCTime->cd(3);
	hMCTOF2 = (TH1F*)hTime->Clone("hMCTOF2");
	hMCTOF2->GetXaxis()->SetTitle("RF - kp2TOF (ns) ");
	tMC->Draw("vtime-(sctkp2-sclkp2/(betakp2*29.99))>>hMCTOF2");





//	TCanvas *cMCTime=new TCanvas("cMCTime","cMCTime",1500,1000);
//	cMCTime->Divide(2,2);
	


	

	
//	tGen->Draw("sqrt(kp1t*kp1t -  0.493677*0.493677)>>hMomentaK1Gen");	
//	cGen->cd(2);
//	tGen->Draw("sqrt(kp2t*kp2t -  0.493677*0.493677)>>hMomentaK2Gen");	
//	cGen->cd(3);
//	tGen->Draw("sqrt(pim1t*pim1t -  0.13957018*0.13957018)>>hMomentaPimGen");
}






//=========================================================================================================================================================================================
//==========================================================================Functions Called===============================================================================================
//=========================================================================================================================================================================================

void ChooseTrees(TTree* tData, TTree* tMC,TTree* tGen)
//void ChooseTrees()
{
	cout <<"IN CHOOSETREES"<<endl;


/*
	TFile *fMCP = TFile::Open("~/clas/rootfiles/LINKS/MC-i5-PosPol-2kppim_Basic_Mass.root");
	//interactively choose MC or PosPol
	cout << "enter choice (MC or MCP ):";
	const string choice;
	cin >> choice;
	if (choice.compare("MC") == 0)
	{
	  	cout <<"The MC  with zero polarization will be evaluated" <<endl;	
		TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	//	myWfile.open ("./Winfo-i5.txt");

	}
	else if (choice.compare("MCP") == 0) 
	{
		cout <<"The MC with positive polarization will be evaluated" <<endl;	
		TTree *tMC = (TTree*)fMCP->Get("gpp2kppim");
	//	myWfile.open ("./Winfo-i5-PosPol.txt");
	}
	else
	{ 
		cout << "choice error, quiting! " <<endl;
		gROOT->ProcessLine(".q");
	}
	
*/	
	
}

void readWfile(Float_t W[NWBins], Float_t Werr[NWBins])
{
	
	if(NWBins == 27)
	{
		const string doW;
		cout << "Use the W factors? (type yes or no)"<<endl;
		cin >> doW;
		if (doW.compare("yes")==0)
		{
		
			const string polchoice,ichoice;
			cout <<"are you using NoPol, PosPol or NegPol?"<<endl;
			cin >> polchoice;
			cout << "what iteration? (i4,i5,i6...)"<<endl;
			cin >> ichoice;
		
			ifstream in(Form("/Users/Bono/clas/myDefinitions/txt/Winfo-%s-%s.txt",ichoice.c_str(),polchoice.c_str()));
			if(!in) 
			{
    			cout << "Cannot open txt file.\n";
				gROOT->ProcessLine(".q");
  			}
		
			for (int k = 0; k < NWBins ; k++) 
			{
  				in >> W[k] >> Werr[k];
  				//cout << "W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
			}
			in.close();	
		}
		else if (doW.compare("no")==0)
		{
			for (int k = 0; k < NWBins ; k++) 
			{
				//cout << tMC->GetEntries() <<endl;
				float temp1 = tData->GetEntries();
				float temp2 = tMC->GetEntries();
				W[k] = temp1/temp2; 
 				Werr[k] = 0;		
			}
		}
		else
		{
			cout << "check on NWBins \n";
			gROOT->ProcessLine(".q");
		}
	}
		
}







void GetHists()
{
			
		//hist models
		TH1F *hCas=new TH1F("hCas","",480,1.2,1.68);  // 480/480 = 1 MeV
		hCas->SetMinimum(0);
		hCas->SetFillColor(4);
		TH1F *hLam=new TH1F("hLam","",480,1.0,1.48);  // 480/480 = 1 MeV 
		hLam->SetMinimum(0);
		hLam->SetFillColor(4);

		//good signal hists
		hA = (TH1F*)hCas->Clone("hA");
		hA->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
		hA->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");  
		hC = (TH1F*)hCas->Clone("hC");
		hC->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hC->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
		hB = (TH1F*)hLam->Clone("hB");
		hB->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hB->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
		hD = (TH1F*)hLam->Clone("hD");	
		hD->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hD->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
	

		//sideband hists
		hA_sb = (TH1F*)hA->Clone("hA_sb");
		hA_sb->SetMinimum(0);
		hA_sb->SetFillColor(2);
		hC_sb = (TH1F*)hC->Clone("hC_sb");
		hC_sb->SetMinimum(0);
		hC_sb->SetFillColor(2);
		hB_sb = (TH1F*)hB->Clone("hB_sb");
		hB_sb->SetMinimum(0);
		hB_sb->SetFillColor(2);
		hD_sb = (TH1F*)hD->Clone("hD_sb");
		hD_sb->SetMinimum(0);
		hD_sb->SetFillColor(2);

		//sideband2 hists
		hA_sb2 = (TH1F*)hA->Clone("hA_sb2");
		hA_sb2->SetMinimum(0);
		hA_sb2->SetFillColor(1);
		hC_sb2 = (TH1F*)hC->Clone("hC_sb2");
		hC_sb2->SetMinimum(0);
		hC_sb2->SetFillColor(1);
		hB_sb2 = (TH1F*)hB->Clone("hB_sb2");
		hB_sb2->SetMinimum(0);
		hB_sb2->SetFillColor(1);
		hD_sb2 = (TH1F*)hD->Clone("hD_sb2");
		hD_sb2->SetMinimum(0);
		hD_sb2->SetFillColor(1);
	
}



StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.08);
	gStyle->SetTitleYSize(0.07); 
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
}
