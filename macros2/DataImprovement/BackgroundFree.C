/*
Date: December 7 2012  
Author: Jason Bono.
Purpose: To show there is zero background (within error) in the signal

Usage: .L BackgroundFree.C
StyleUp()
Show....
*/



#include "TLine.h"

//Define Global Varibles
TFile *fileData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05.root");
TTree *tData = (TTree*)fileData->Get("v05_Basic");
float MASS_Xi = 1.321;
float MASS_Lambda = 1.116;


void BackgroundFree()
{


	ShowCutRegions();
	
	ShowAllData();

	ShowSignal();
	
	XivsLam();


}



/////////////////////////////////////////////////////////////////////



void XivsLam()
{
	
	StyleUp();
		
	//get the cuts
	TCut  CutCasMM,CutCasM,CutCas,CutLamMM,CutLamM,CutLam,CutCasMM_sb,CutCasM_sb,CutCas_sb,CutLamMM_sb,CutLamM_sb,CutLam_sb;
	float WIDTHMM,WIDTHM;
	DefineCuts( CutCasMM,  CutCasM,  CutCas, CutLamMM,  CutLamM,  CutLam,  CutCasMM_sb, CutCasM_sb,  CutCas_sb, 
		CutLamMM_sb,  CutLamM_sb,  CutLam_sb, WIDTHMM, WIDTHM);
	
	
	//get the lines
	//TLine linelow1, linehigh1, linelow2, linehigh2, linelow3, linehigh3, linelow4, linehigh4;
	//GetLines(linelow1, linehigh1, linelow2, linehigh2, linelow3, linehigh3, linelow4, linehigh4);
	//line model
	
	//1
	float low,high;
	low = MASS_Xi - WIDTHMM;
	high = 	MASS_Xi + WIDTHMM;
	TLine *linelow1 = new TLine(0,low,5,low);
	TLine *linehigh1 = new TLine(0,high,5,high);
	linelow1->SetLineColor(kRed);
	linehigh1->SetLineColor(kRed);
	//2
	low = MASS_Xi - WIDTHM;
	high = 	MASS_Xi + WIDTHM;
	TLine *linelow2 = new TLine(0,low,5,low);
	TLine *linehigh2 = new TLine(0,high,5,high);
	linelow2->SetLineColor(kRed);
	linehigh2->SetLineColor(kRed);
	//3
	low = MASS_Lambda - WIDTHMM;
	high = 	MASS_Lambda + WIDTHMM;
	TLine *linelow3 = new TLine(low,0,low,5);
	TLine *linehigh3 = new TLine(high,0,high,5);
	linelow3->SetLineColor(kRed);
	linehigh3->SetLineColor(kRed);
	//4
	low = MASS_Lambda - WIDTHM;
	high = 	MASS_Lambda + WIDTHM;
	TLine *linelow4 = new TLine(low,0,low,5);
	TLine *linehigh4 = new TLine(high,0,high,5);
	linelow4->SetLineColor(kRed);
	linehigh4->SetLineColor(kRed);

	//mm
	TCanvas *c2DMM=new TCanvas("c2DMM","",1200,800);
	TH2F *h2DMM=new TH2F("h2DMM","",100,1.07,1.16,100,1.2801,1.3701);
	h2DMM->GetYaxis()->SetTitle(" MM(K^{+}K^{+})");
	h2DMM->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-})");

	tData->Draw("mmkpkp:mmkpkppim>>h2DMM",CutCasM&&CutLamM,"colz");
	linelow1->Draw("SAME");
	linehigh1->Draw("SAME");
	linelow3->Draw("SAME");
	linehigh3->Draw("SAME");

	//m
	TCanvas *c2DM=new TCanvas("c2DM","",1200,800);
	TH2F *h2DM=new TH2F("h2DM","",100,1.07,1.16,100,1.28,1.37);
	h2DM->GetYaxis()->SetTitle(" M(#Lambda + #pi^{-})");
	h2DM->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-})");
	
	tData->Draw("mlampim:mcasmMpim>>h2DM",CutCasMM&&CutLamMM,"colz");
	linelow2->Draw("SAME");
	linehigh2->Draw("SAME");
	linelow4->Draw("SAME");
	linehigh4->Draw("SAME");
	
	
}








void ShowSignal()
{
	StyleUp();
		
	TCut  CutCasMM,CutCasM,CutCas,CutLamMM,CutLamM,CutLam,CutCasMM_sb,CutCasM_sb,CutCas_sb,CutLamMM_sb,CutLamM_sb,CutLam_sb;
	float WIDTHMM,WIDTHM;
	DefineCuts( CutCasMM,  CutCasM,  CutCas, CutLamMM,  CutLamM,  CutLam,  CutCasMM_sb, CutCasM_sb,  CutCas_sb, 
		CutLamMM_sb,  CutLamM_sb,  CutLam_sb, WIDTHMM, WIDTHM);
	

	//line model
	float low,high;
	low = MASS_Xi - WIDTHMM;
	high = 	MASS_Xi + WIDTHMM;
	TLine *linelow = new TLine(low,0,low,2000);
	TLine *linehigh = new TLine(high,0,high,2000);
  	linelow->SetLineColor(kRed);
  	linehigh->SetLineColor(kRed);
	linelow->SetX1(low);
	linelow->SetX2(low);
	linehigh->SetX1(high);
	linehigh->SetX2(high);
	
	//get the hists which will be stored in memory even tho they are outside of the scope for some reason
	GetHists();

	//start displaying
	TCanvas *c=new TCanvas("canvCas","1",1200,800);
	tData->Draw("mmkpkp>>hCasMM",CutLam);
	tData->Draw("mmkpkp>>hCasMM_sb",CutLam_sb,"SAME");
	//line
	low = MASS_Xi - WIDTHMM;
	high = 	MASS_Xi + WIDTHMM;
	TLine *linelow1 = (TLine*)linelow->Clone("linelow1");
	TLine *linehigh1 = (TLine*)linehigh->Clone("linehigh1");
	linelow1->SetX1(low);
	linelow1->SetX2(low);
	linehigh1->SetX1(high);
	linehigh1->SetX2(high);
	linelow1->Draw("SAME");
	linehigh1->Draw("SAME");

	TCanvas *c=new TCanvas("canvCas2","2",1200,800);
	//tData->Draw("mlampim>>hCasM_bad");
	tData->Draw("mlampim>>hCasM",CutLam);	
	tData->Draw("mlampim>>hCasM_sb",CutLam_sb,"SAME");
	//line
	low = MASS_Xi - WIDTHM;
	high = 	MASS_Xi + WIDTHM;
	TLine *linelow2 = (TLine*)linelow->Clone("linelow2");
	TLine *linehigh2 = (TLine*)linehigh->Clone("linehigh2");
	linelow2->SetX1(low);
	linelow2->SetX2(low);
	linehigh2->SetX1(high);
	linehigh2->SetX2(high);
	linelow2->Draw("SAME");
	linehigh2->Draw("SAME");

	
	
	TCanvas *c=new TCanvas("canvLam","3",1200,800);
	tData->Draw("mmkpkppim>>hLamMM",CutCas);	
	tData->Draw("mmkpkppim>>hLamMM_sb",CutCas_sb,"SAME");
	//line
	low = MASS_Lambda - WIDTHMM;
	high = 	MASS_Lambda + WIDTHMM;
	TLine *linelow3 = (TLine*)linelow->Clone("linelow13");
	TLine *linehigh3 = (TLine*)linehigh->Clone("linehigh3");
	linelow3->SetX1(low);
	linelow3->SetX2(low);
	linehigh3->SetX1(high);
	linehigh3->SetX2(high);
	linelow3->Draw("SAME");
	linehigh3->Draw("SAME");

	
	TCanvas *c=new TCanvas("canvLam2","4",1200,800);
	tData->Draw("mcasmMpim>>hLamM",CutCas);
	tData->Draw("mcasmMpim>>hLamM_sb",CutCas_sb,"SAME");
	//line
	low = MASS_Lambda - WIDTHM;
	high = 	MASS_Lambda + WIDTHM;
	TLine *linelow4 = (TLine*)linelow->Clone("linelow4");
	TLine *linehigh4 = (TLine*)linehigh->Clone("linehigh4");
	linelow4->SetX1(low);
	linelow4->SetX2(low);
	linehigh4->SetX1(high);
	linehigh4->SetX2(high);
	linelow4->Draw("SAME");
	linehigh4->Draw("SAME");

	
	
}




void ShowCutRegions()
{
		
	TCut  CutCasMM,CutCasM,CutCas,CutLamMM,CutLamM,CutLam,CutCasMM_sb,CutCasM_sb,CutCas_sb,CutLamMM_sb,CutLamM_sb,CutLam_sb;
	float WIDTHMM,WIDTHM;
	DefineCuts( CutCasMM,  CutCasM,  CutCas,
	 CutLamMM,  CutLamM,  CutLam,  CutCasMM_sb,
	 CutCasM_sb,  CutCas_sb,  CutLamMM_sb,  CutLamM_sb,  CutLam_sb, WIDTHMM, WIDTHM);
	
	//get the hists which will be stored in memory even tho they are outside of the scope for some reason
	GetHists();


	TCanvas *c=new TCanvas("canvCas","1",1200,800);
	tData->Draw("mmkpkp>>hCasMM_bad");
	tData->Draw("mmkpkp>>hCasMM",CutCasMM,"SAME");
	tData->Draw("mmkpkp>>hCasMM_sb",CutCasMM_sb,"SAME");
	
	
	TCanvas *c=new TCanvas("canvCas2","2",1200,800);
	tData->Draw("mlampim>>hCasM_bad");
	tData->Draw("mlampim>>hCasM",CutCasM,"SAME");	
	tData->Draw("mlampim>>hCasM_sb",CutCasM_sb,"SAME");
	
	TCanvas *c=new TCanvas("canvLam","3",1200,800);
	tData->Draw("mmkpkppim>>hLamMM_bad");
	tData->Draw("mmkpkppim>>hLamMM",CutLamMM,"SAME");	
	tData->Draw("mmkpkppim>>hLamMM_sb",CutLamMM_sb,"SAME");
	
	TCanvas *c=new TCanvas("canvLam2","4",1200,800);
	tData->Draw("mcasmMpim>>hLamM_bad");
	tData->Draw("mcasmMpim>>hLamM",CutLamM,"SAME");
	tData->Draw("mcasmMpim>>hLamM_sb",CutLamM_sb,"SAME");
	
}

void ShowAllData()
{
		
	TCut  CutCasMM,CutCasM,CutCas,CutLamMM,CutLamM,CutLam,CutCasMM_sb,CutCasM_sb,CutCas_sb,CutLamMM_sb,CutLamM_sb,CutLam_sb;
	float WIDTHMM,WIDTHM;
	DefineCuts( CutCasMM,  CutCasM,  CutCas,
	 CutLamMM,  CutLamM,  CutLam,  CutCasMM_sb,
	 CutCasM_sb,  CutCas_sb,  CutLamMM_sb,  CutLamM_sb,  CutLam_sb, WIDTHMM, WIDTHM);
	
	
	GetFullRangeHists();


	TCanvas *c=new TCanvas("canvCas","1",1200,800);
	tData->Draw("mmkpkp>>hCasMMall_bad");
	tData->Draw("mmkpkp>>hCasMMall",CutCasMM,"SAME");
	tData->Draw("mmkpkp>>hCasMMall_sb",CutCasMM_sb,"SAME");
	
	
	TCanvas *c=new TCanvas("canvCas2","2",1200,800);
	tData->Draw("mlampim>>hCasMall_bad");
	tData->Draw("mlampim>>hCasMall",CutCasM,"SAME");	
	tData->Draw("mlampim>>hCasMall_sb",CutCasM_sb,"SAME");
	
	TCanvas *c=new TCanvas("canvLam","3",1200,800);
	tData->Draw("mmkpkppim>>hLamMMall_bad");
	tData->Draw("mmkpkppim>>hLamMMall",CutLamMM,"SAME");	
	tData->Draw("mmkpkppim>>hLamMMall_sb",CutLamMM_sb,"SAME");
	
	TCanvas *c=new TCanvas("canvLam2","4",1200,800);
	tData->Draw("mcasmMpim>>hLamMall_bad");
	tData->Draw("mcasmMpim>>hLamMall",CutLamM,"SAME");
	tData->Draw("mcasmMpim>>hLamMall_sb",CutLamM_sb,"SAME");
	
}



void DefineCuts(TCut &CutCasMM, TCut &CutCasM, TCut &CutCas,
TCut &CutLamMM, TCut &CutLamM,TCut &CutLam, TCut &CutCasMM_sb,
TCut &CutCasM_sb, TCut &CutCas_sb, TCut &CutLamMM_sb, TCut &CutLamM_sb, TCut &CutLam_sb,
float &WIDTHMM, float &WIDTHM)
{
	
	
	float WIDTHMM=0.031;// 0.018
	float WIDTHM=0.009; // 0.015
	
	float sb_MM = 2*WIDTHMM;
	float sb_M = 2*WIDTHM;
	CutCasMM = Form("abs(mmkpkp - %f)<%f",MASS_Xi,WIDTHMM);
	CutCasM = Form("abs(mlampim-%f)<%f",MASS_Xi,WIDTHM);
	CutCas = CutCasMM&&CutCasM;
	CutLamMM = Form("abs(mmkpkppim-%f)<%f",MASS_Lambda,WIDTHMM);
	CutLamM = Form("abs(mcasmMpim-%f)<%f",MASS_Lambda,WIDTHM); 
	CutLam = CutLamMM&&CutLamM;
	Cut = CutLam&&CutCas;
	CutCasMM_sb = Form("abs(mmkpkp - %f)>%f && abs(mmkpkp - %f)<%f",MASS_Xi,WIDTHMM,MASS_Xi,sb_MM);
	CutCasM_sb = Form("abs(mlampim-%f)>%f && abs(mlampim-%f)<%f ",MASS_Xi,WIDTHM,MASS_Xi,sb_M);
	CutCas_sb = CutCasMM_sb&&CutCasM_sb;
	CutLamMM_sb = Form("abs(mmkpkppim-%f)>%f && abs(mmkpkppim-%f)<%f ",MASS_Lambda,WIDTHMM,MASS_Lambda,sb_MM);
	CutLamM_sb = Form("abs(mcasmMpim-%f)>%f && abs(mcasmMpim-%f)<%f",MASS_Lambda,WIDTHM,MASS_Lambda,sb_M); 
	CutLam_sb = CutLamMM_sb&&CutLamM_sb;
	Cut_sb = CutLam_sb&&CutCas_sb;	
}

void GetLines(TLine &linelow1, TLine &linehigh1, TLine &linelow2, 
TLine &linehigh2, TLine &linelow3, TLine &linehigh3, TLine &linelow4, TLine &linehigh4)
{
 	// 1) XiMM  : 2) XiM : 3) LamMM : 4) LamM


	//first call DefineCuts to obtain the widths
	TCut  CutCasMM,CutCasM,CutCas,CutLamMM,CutLamM,CutLam,CutCasMM_sb,CutCasM_sb,CutCas_sb,CutLamMM_sb,CutLamM_sb,CutLam_sb;
	float WIDTHMM,WIDTHM;
	DefineCuts( CutCasMM,  CutCasM,  CutCas, CutLamMM, 
	   	CutLamM,  CutLam,  CutCasMM_sb, CutCasM_sb,  CutCas_sb, 
		CutLamMM_sb,  CutLamM_sb,  CutLam_sb, WIDTHMM, WIDTHM);


	//line model
	float low,high;
	low = MASS_Xi - WIDTHMM;
	high = 	MASS_Xi + WIDTHMM;
	TLine *linelow = new TLine(low,0,low,2000);
	TLine *linehigh = new TLine(high,0,high,2000);
  	linelow->SetLineColor(kRed);
  	linehigh->SetLineColor(kRed);
	linelow->SetX1(low);
	linelow->SetX2(low);
	linehigh->SetX1(high);
	linehigh->SetX2(high);	
	
	//line1
	low = MASS_Xi - WIDTHMM;
	high = 	MASS_Xi + WIDTHMM;
	linelow1 = linelow;
	linehigh1 = linehigh;
	//TLine *linelow1 = (TLine*)linelow->Clone("linelow1");
	//TLine *linehigh1 = (TLine*)linehigh->Clone("linehigh1");
	linelow1.SetX1(low);
	linelow1.SetX2(low);
	linehigh1.SetX1(high);
	linehigh1.SetX2(high);

	//line2
	low = MASS_Xi - WIDTHM;
	high = 	MASS_Xi + WIDTHM;
	//TLine *linelow2 = (TLine*)linelow->Clone("linelow2");
	//TLine *linehigh2 = (TLine*)linehigh->Clone("linehigh2");
	linelow2.SetX1(low);
	linelow2.SetX2(low);
	linehigh2.SetX1(high);
	linehigh2.SetX2(high);

	//line3
	low = MASS_Lambda - WIDTHMM;
	high = 	MASS_Lambda + WIDTHMM;
	//TLine *linelow3 = (TLine*)linelow->Clone("linelow13");
	//TLine *linehigh3 = (TLine*)linehigh->Clone("linehigh3");
	linelow3.SetX1(low);
	linelow3.SetX2(low);
	linehigh3.SetX1(high);
	linehigh3.SetX2(high);


	//line4
	low = MASS_Lambda - WIDTHM;
	high = 	MASS_Lambda + WIDTHM;
	//TLine *linelow4 = (TLine*)linelow->Clone("linelow4");
	//TLine *linehigh4 = (TLine*)linehigh->Clone("linehigh4");
	linelow4.SetX1(low);
	linelow4.SetX2(low);
	linehigh4.SetX1(high);
	linehigh4.SetX2(high);

	
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


void GetHists()
{
	
		
		//hist models
		TH1F *hC=new TH1F("hC","",480,1.2,1.68);  //160   //480
		hC->SetMinimum(0);
		hC->SetFillColor(9);
		TH1F *hL=new TH1F("hL","",480,1.0,1.48); //160  //480
		hL->SetMinimum(0);
		hL->SetFillColor(9);

		//good signal hists
		hCasMM = (TH1F*)hC->Clone("hCasMM");
		hCasMM->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
		hCasMM->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");  
		hCasM = (TH1F*)hC->Clone("hCasM");
		hCasM->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hCasM->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
		hLamMM = (TH1F*)hL->Clone("hLamMM");
		hLamMM->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hLamMM->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
		hLamM = (TH1F*)hL->Clone("hLamM");	
		hLamM->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hLamM->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
		//bad hists
		hCasMM_bad = (TH1F*)hCasMM->Clone("hCasMM_bad");
		hCasMM_bad->SetMinimum(0);
		hCasMM_bad->SetFillColor(0);
		hCasM_bad = (TH1F*)hCasM->Clone("hCasM_bad");
		hCasM_bad->SetMinimum(0);
		hCasM_bad->SetFillColor(0);
		hLamMM_bad = (TH1F*)hLamMM->Clone("hLamMM_bad");
		hLamMM_bad->SetMinimum(0);
		hLamMM_bad->SetFillColor(0);
		hLamM_bad = (TH1F*)hLamM->Clone("hLamM_bad");
		hLamM_bad->SetMinimum(0);
		hLamM_bad->SetFillColor(0);
		//sideband hists
		hCasMM_sb = (TH1F*)hCasMM->Clone("hCasMM_sb");
		hCasMM_sb->SetMinimum(0);
		hCasMM_sb->SetFillColor(2);
		hCasM_sb = (TH1F*)hCasM->Clone("hCasM_sb");
		hCasM_sb->SetMinimum(0);
		hCasM_sb->SetFillColor(2);
		hLamMM_sb = (TH1F*)hLamMM->Clone("hLamMM_sb");
		hLamMM_sb->SetMinimum(0);
		hLamMM_sb->SetFillColor(2);
		hLamM_sb = (TH1F*)hLamM->Clone("hLamM_sb");
		hLamM_sb->SetMinimum(0);
		hLamM_sb->SetFillColor(2);
	
	
}

void GetFullRangeHists()
{
	//hist models
	TH1F *hAll=new TH1F("hAll","",1000,0,2.5);
	hAll->SetMinimum(0);
	hAll->SetFillColor(9);

	
	//good signal
	hCasMMall = (TH1F*)hAll->Clone("hCasMMall");
	hCasMMall->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
	hCasMMall->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");  
	hCasMall = (TH1F*)hAll->Clone("hCasMall");
	hCasMall->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
	hCasMall->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	hLamMMall = (TH1F*)hAll->Clone("hLamMMall");
	hLamMMall->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
	hLamMMall->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	hLamMall = (TH1F*)hAll->Clone("hLamMall");	
	hLamMall->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
	hLamMall->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
	//bad hists
	hCasMMall_bad = (TH1F*)hCasMMall->Clone("hCasMMall_bad");
	hCasMMall_bad->SetMinimum(0);
	hCasMMall_bad->SetFillColor(0);
	hCasMall_bad = (TH1F*)hCasMall->Clone("hCasMall_bad");
	hCasMall_bad->SetMinimum(0);
	hCasMall_bad->SetFillColor(0);
	hLamMMall_bad = (TH1F*)hLamMMall->Clone("hLamMMall_bad");
	hLamMMall_bad->SetMinimum(0);
	hLamMMall_bad->SetFillColor(0);
	hLamMall_bad = (TH1F*)hLamMall->Clone("hLamMall_bad");
	hLamMall_bad->SetMinimum(0);
	hLamMall_bad->SetFillColor(0);
	//sideband hists
	hCasMMall_sb = (TH1F*)hCasMMall->Clone("hCasMMall_sb");
	hCasMMall_sb->SetMinimum(0);
	hCasMMall_sb->SetFillColor(2);
	hCasMall_sb = (TH1F*)hCasMall->Clone("hCasMall_sb");
	hCasMall_sb->SetMinimum(0);
	hCasMall_sb->SetFillColor(2);
	hLamMMall_sb = (TH1F*)hLamMMall->Clone("hLamMMall_sb");
	hLamMMall_sb->SetMinimum(0);
	hLamMMall_sb->SetFillColor(2);
	hLamMall_sb = (TH1F*)hLamMall->Clone("hLamMall_sb");
	hLamMall_sb->SetMinimum(0);
	hLamMall_sb->SetFillColor(2);
	
}
