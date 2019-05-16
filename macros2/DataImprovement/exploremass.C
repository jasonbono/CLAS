/*
Date: July 8 2013  
Author: Jason Bono


*/



#include "TLine.h"

//------Define Global Varibles---------
///edit theese 5 quantities if changing widths
float sigmaA = 0.0113;
float sigmaB = 0.0107;
float sigmaC = 0.0031;
float sigmaD = 0.0030;
float depth = 3;

//theese are fixed
float widthA = depth*sigmaA;
float widthB = depth*sigmaB;
float widthC = depth*sigmaC;
float widthD = depth*sigmaD;
float MASS_Xi = 1.321;
float MASS_Lambda = 1.116;


TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic.root");
TTree *tData = (TTree*)fData->Get("v05");

TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i7-2kppim_Basic.root");
//TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i0t0-2kppim.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
//-----------------------------------



void exploremass()
{
	
	//setup the style
	StyleUp();
	//get the cuts
	TCut CutABCD,CutABCD_sb,CutABCD_sb2;
	GetHyperSphereCut(CutABCD);
	GetHyperSphereSideBand(CutABCD_sb);
	GetHyperSphereSideBand2(CutABCD_sb2);
	//get the hists
	GetHists();


	TTree *tree;
	const string choice;
	cout << "For Data or MC? (type Data or MC)";
	cin >> choice;
	if (choice.compare("Data") == 0) 
	{		
		tree = tData;
	}
	else if (choice.compare("MC") == 0)
	{
		tree = tMC;
	}
	
	

	//draw all four plots
	TCanvas *cA=new TCanvas("cA","cA",1200,800);
	tree->Draw("mmkpkp >> hA",CutABCD);
	TCanvas *cB=new TCanvas("cB","cB",1200,800);
	tree->Draw("mmkpkppim >> hB",CutABCD);
	TCanvas *cC=new TCanvas("cC","cC",1200,800);
	tree->Draw("mlampim >> hC",CutABCD);
	TCanvas *cD=new TCanvas("cD","cD",1200,800);
	tree->Draw("mcasmMpim >> hD",CutABCD);
	
	//side band
	cA->cd();
	tree->Draw("mmkpkp >> hA_sb",CutABCD_sb,"SAME");		
	cB->cd();
	tree->Draw("mmkpkppim >> hB_sb",CutABCD_sb,"SAME");
	cC->cd();
	tree->Draw("mlampim >> hC_sb",CutABCD_sb,"SAME");
	cD->cd();
	tree->Draw("mcasmMpim >> hD_sb",CutABCD_sb,"SAME");
	
	//side band
	cA->cd();
	tree->Draw("mmkpkp >> hA_sb2",CutABCD_sb2,"SAME");		
	cB->cd();
	tree->Draw("mmkpkppim >> hB_sb2",CutABCD_sb2,"SAME");
	cC->cd();
	tree->Draw("mlampim >> hC_sb2",CutABCD_sb2,"SAME");
	cD->cd();
	tree->Draw("mcasmMpim >> hD_sb2",CutABCD_sb2,"SAME");


}

////////////////////////////////////////////////////////////


void beerbuddy()
{
	
	StyleUp();
	gStyle->SetOptStat(1);
	
	TTree *tree;
	const string choice;
	cout << "For Data or MC? (type Data or MC)";
	cin >> choice;
	if (choice.compare("Data") == 0) 
	{		
		tree = tData;
	}
	else if (choice.compare("MC") == 0)
	{
		tree = tMC;
	}


	
	//get the cuts and hists
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts(CutA,CutB,CutC,CutD);	
	GetHists();
	
	
	//1d plots
	TCanvas *cABCD=new TCanvas("cA","cA",1200,800);
	cABCD->Divide(2,2);
	cABCD->cd(1);
	tree->Draw("mmkpkp >> hA",CutC&&CutD);
	cABCD->cd(2);
	tree->Draw("mmkpkppim >> hB",CutC&&CutD);
	cABCD->cd(3);
	tree->Draw("mlampim >> hC",CutA&&CutB);
	cABCD->cd(4);
	tree->Draw("mcasmMpim >> hD",CutA&&CutB);

	//2d plots
	//TCanvas *cmvsm=new TCanvas("cmvsm","cmvsm",1200,800);
	//TH2F *hmvsm=new TH2F("hmvsm","",200,1,1.4,200,1,1.4);
	//tree->Draw("mlampim:mcasmMpim >> hmvsm",CutA&&CutB);


}






void XivsLam()
{	
	StyleUp();
	TTree *tree;
	const string choice;
	cout << "For Data or MC? (type Data or MC)";
	cin >> choice;
	if (choice.compare("Data") == 0) 
	{		
		tree = tData;
	}
	else if (choice.compare("MC") == 0)
	{
		tree = tMC;
	}
	
	
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts(CutA,CutB,CutC,CutD);

	//line A
	float low,high;
	low = MASS_Xi - widthA;
	high = 	MASS_Xi + widthA;
	TLine *linelowA = new TLine(0,low,5,low);
	TLine *linehighA = new TLine(0,high,5,high);
	linelowA->SetLineColor(kRed);
	linehighA->SetLineColor(kRed);
	//line B
	low = MASS_Lambda - widthB;
	high = 	MASS_Lambda + widthB;
	TLine *linelowB = new TLine(low,0,low,5);
	TLine *linehighB = new TLine(high,0,high,5);
	linelowB->SetLineColor(kRed);
	linehighB->SetLineColor(kRed);
	//line C
	low = MASS_Xi - widthC;
	high = 	MASS_Xi + widthC;
	TLine *linelowC = new TLine(0,low,5,low);
	TLine *linehighC = new TLine(0,high,5,high);
	linelowC->SetLineColor(kRed);
	linehighC->SetLineColor(kRed);
	//line D
	low = MASS_Lambda - widthD;
	high = 	MASS_Lambda + widthD;
	TLine *linelowD = new TLine(low,0,low,5);
	TLine *linehighD = new TLine(high,0,high,5);
	linelowD->SetLineColor(kRed);
	linehighD->SetLineColor(kRed);

	
	//A vs B
	TCanvas *cAB=new TCanvas("cAB","",1200,800);
	TH2F *hAB=new TH2F("hAB","",300,1.07,1.16,300,1.2801,1.3701);
	hAB->GetYaxis()->SetTitle(" MM(K^{+}K^{+})");
	hAB->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-})");
	tree->Draw("mmkpkp:mmkpkppim>>hAB",CutC&&CutD,"colz");
	linelowA->Draw("SAME");
	linehighA->Draw("SAME");
	linelowB->Draw("SAME");
	linehighB->Draw("SAME");

	// C vs D
	TCanvas *cCD=new TCanvas("cCD","",1200,800);
	TH2F *hCD=new TH2F("hCD","",300,1.09,1.14,300,1.3,1.34);
	hCD->GetYaxis()->SetTitle(" M(#Lambda + #pi^{-})");
	hCD->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-})");
	tree->Draw("mlampim:mcasmMpim>>hCD",CutA&&CutB,"colz");
	linelowC->Draw("SAME");
	linehighC->Draw("SAME");
	linelowD->Draw("SAME");
	linehighD->Draw("SAME");
	
	
	
	
	// A vs C
	TCanvas *cAC=new TCanvas("cAC","",1200,800);
	TH2F *hAC=new TH2F("hAC","",300,1.26,1.34,300,1.26,1.34);
	hAC->GetYaxis()->SetTitle(" MM(K^{+}K^{+})");
	hAC->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-})");
	tree->Draw("mmkpkp:mlampim>>hAC",CutB,"colz");
	
	
	// A vs D
	TCanvas *cAD=new TCanvas("cAD","",1200,800);
	TH2F *hAD=new TH2F("hAD","",300,1.09,1.16,300,1.26,1.34);
	hAD->GetYaxis()->SetTitle(" MM(K^{+}K^{+})");
	hAD->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-})");
	tree->Draw("mmkpkp:mcasmMpim>>hAD",CutB,"colz");
	
	
	
	// B vs C
	TCanvas *cBC=new TCanvas("cBC","",1200,800);
	TH2F *hBC=new TH2F("hBC","",300,1.26,1.34,300,1.09,1.16);
	hBC->GetYaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-})");
	hBC->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-})");
	tree->Draw("mmkpkppim:mlampim>>hBC",CutA,"colz");
	
	
	// B vs D
	TCanvas *cBD=new TCanvas("cBD","",1200,800);
	TH2F *hBD=new TH2F("hBD","",300,1.09,1.16,300,1.09,1.16);
	hBD->GetYaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-})");
	hBD->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-})");
	tree->Draw("mmkpkppim:mcasmMpim>>hBD",CutA,"colz");

	
		
}














//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//------------------------
void GetHyperSphereCut(TCut &CutABCD)
{
	
	CutABCD = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	
}



void GetHyperSphereSideBand(TCut &CutABCD_sb)
{
	TCut cond1,cond2;
	
	
	cond1 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > 1"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	
	cond2 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1.189207"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	
	CutABCD_sb = cond1&&cond2;
}

void GetHyperSphereSideBand2(TCut &CutABCD_sb2)
{
	TCut cond1,cond2;
	
	
	cond1 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > 1.189207"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	
	cond2 = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1.316074"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	
	CutABCD_sb2 = cond1&&cond2;
}

void GetSeperateCuts(TCut &CutA,TCut &CutB,TCut &CutC,TCut &CutD)
{
	
	CutA = Form("sqrt( (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) ) < 1 ",MASS_Xi,MASS_Xi,widthA,widthA);
	CutB = Form("sqrt( (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) ) < 1 ",MASS_Lambda,MASS_Lambda,widthB,widthB);
	CutC = Form("sqrt( (mlampim  - %f)*(mlampim  - %f)/(%f*%f) ) < 1 ",MASS_Xi,MASS_Xi,widthC,widthC);
	CutD = Form("sqrt( (mcasmMpim  - %f)*(mcasmMpim  - %f)/(%f*%f) ) < 1 ",MASS_Lambda,MASS_Lambda,widthD,widthD);		
	
}


//------------------------
void GetHists()
{
	
		
		//hist models
		TH1F *hCas=new TH1F("hCas","",480,1.2,1.68);  //160   //480
		hCas->SetMinimum(0);
		hCas->SetFillColor(4);
		TH1F *hLam=new TH1F("hLam","",480,1.0,1.48); //160  //480
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







void StyleUp()
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



