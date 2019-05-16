/*

Made September 2016 from hyperspherecuts.C
 
 
 
Date: December 13 2012  
Author: Jason Bono.
Purpose: To show there the effect of using the hypersphere cuts.

Usage: 

1) choose sigmaA,sigmaB,sigmaC,sigmaD (to choose run the FindSigmas() function)
	this is done by
	 
	>  .L hyperspherecuts.C
	>  FindSigmas()

2) choose the depth (depth dictates how many sigma the cuts are)

3) execute the script
	this is done by
	> .x hyperespherecuts.C


Notes
the four kinematic cuts A,B,C,D
A) mmkpkp       (Xi)
B) mmkpkppim    (Lam)
C) mlampim      (Xi)
D) mcasmMpim    (Lam)

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
float MASS_Xi = 1.32131;
float MASS_Lambda = 1.115683;




TFile *fDataB = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
TTree *tDataB = (TTree*)fDataB->Get("v16");

TFile *ftemp = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
TTree *ttemp = (TTree*)ftemp->Get("v16");





void MassForPaper()
{


    Double_t fitWidth = 0.015;
    Double_t fitWidthFloat = 0.15;
    
    //*
    //setup the style
    StyleUp();
    //get the cuts
    TCut CutABCD,CutABCD_sb,CutABCD_sb2;
    GetHyperSphereCut(CutABCD);
    GetHyperSphereSideBand(CutABCD_sb);
    GetHyperSphereSideBand2(CutABCD_sb2);
    //get the cuts
    TCut CutA,CutB,CutC,CutD;
    GetSeperateCuts(CutA,CutB,CutC,CutD);
    //get the hists
    GetHists();
    //StyleUp();
    gStyle->SetOptStat(0);
    //load the fitter
    gROOT->ProcessLine(".L ~/clas/scripts/new/quietgausfit.C");
    
    //gROOT->ProcessLine(".L ~/clas/scripts/new/gausfitGBG.C");
    //gROOT->ProcessLine(".L /Users/Bono/clas/scripts/new/BgSubtractedYield.C");
    
    
    
    
    
    //draw all four plots
    TCanvas *c=new TCanvas("c","c",1200,1200);
    c->Divide(2,2);
    c->cd(1);
    tDataB->Draw("mmkpkp >> hA",CutABCD);
    c->cd(2);
    tDataB->Draw("mmkpkppim >> hB",CutABCD);
    c->cd(3);
    tDataB->Draw("mlampim >> hC",CutABCD);
    c->cd(4);
    tDataB->Draw("mcasmMpim >> hD",CutABCD);
    
    //side band
    c->cd(1);
    tDataB->Draw("mmkpkp >> hA_sb",CutABCD_sb,"SAME");
    c->cd(2);
    tDataB->Draw("mmkpkppim >> hB_sb",CutABCD_sb,"SAME");
    c->cd(3);
    tDataB->Draw("mlampim >> hC_sb",CutABCD_sb,"SAME");
    c->cd(4);
    tDataB->Draw("mcasmMpim >> hD_sb",CutABCD_sb,"SAME");
    
    //side band
    c->cd(1);
    tDataB->Draw("mmkpkp >> hA_sb2",CutABCD_sb2,"SAME");
    c->cd(2);
    tDataB->Draw("mmkpkppim >> hB_sb2",CutABCD_sb2,"SAME");
    c->cd(3);
    tDataB->Draw("mlampim >> hC_sb2",CutABCD_sb2,"SAME");
    c->cd(4);
    tDataB->Draw("mcasmMpim >> hD_sb2",CutABCD_sb2,"SAME");
    
    //draw line
    TLine *lXi=new TLine(MASS_Xi,0,MASS_Xi,1000);
    TLine *lLam=new TLine(MASS_Lambda,0,MASS_Lambda,1000);
    lXi->SetLineWidth(4);
    lXi->SetLineColor(kRed);
    lXi->SetLineStyle(4);
    lLam->SetLineWidth(4);
    lLam->SetLineColor(kGreen);
    lLam->SetLineStyle(5);
    c->cd(1);
    lXi->Draw("same");
    c->cd(2);
    lLam->Draw("same");
    c->cd(3);
    lXi->Draw("same");
    c->cd(4);
    lLam->Draw("same");
    c->cd(0);
    
    //print for thesis
    // cA->Print("./pics/massA.png");
    // cB->Print("./pics/massB.png");
    // cC->Print("./pics/massC.png");
    // cD->Print("./pics/massD.png");
    //c->Print("~/Desktop/signal.png");
    

    
    /////////////////////////////////////////////////////////////////
    
    

    
    Double_t t0 = 1;
    Double_t t1 = 1;
    Double_t t2 = 1;
    Double_t t3 = 1;
    Double_t t4 = 1;
    Double_t Yield = 0;
    Double_t Yielderr = 0;
    


    

    

    

 
    //draw the stuff
    TCanvas *cABCD=new TCanvas("cA","cA",1200,1200);
    cABCD->Divide(2,2);
    cABCD->cd(1);
    
    
    ttemp->Draw("mmkpkp >> hAfit",CutC&&CutD);
    gausfit(hAfit,1,1.2,1.45,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
    cABCD->cd(2);
    ttemp->Draw("mmkpkppim >> hBfit",CutC&&CutD);
    gausfit(hBfit,1,1.05,1.2,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
    cABCD->cd(3);
    ttemp->Draw("mlampim >> hCfit",CutA&&CutB);
    
    Double_t MYBACKGROUND =0;
    Double_t MYRMS=0;
    Double_t MYMEAN=0;
    gausfit(hCfit,1,1.27,1.37,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
//    gausfitGBG(hCfit,1,1.27,1.37,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,MYBACKGROUND,Yield,MYRMS,MYMEAN, Yielderr);
    cABCD->cd(4);
    ttemp->Draw("mcasmMpim >> hDfit",CutA&&CutB);
    gausfit(hDfit,1,1.06,1.16,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
   
    
//    //draw line
//    TLine *lXi=new TLine(MASS_Xi,0,MASS_Xi,1000);
//    TLine *lLam=new TLine(MASS_Lambda,0,MASS_Lambda,1000);
//    lXi->SetLineWidth(1);
//    //lXi->SetLineStyle(4);
//    lXi->SetLineColor(kRed);
//    lLam->SetLineWidth(1);
//    //lLam->SetLineStyle(5);
//    lLam->SetLineColor(kGreen);
//    cABCD->cd(1);
//    //lXi->Draw("same");
//    cABCD->cd(2);
//    lLam->Draw("same");
//    cABCD->cd(3);
//    lXi->Draw("same");
//    cABCD->cd(4);
//    lLam->Draw("same");
//  

    
////////////////////////////////////////////
    cABCD->cd(1);
    hA->SetFillColorAlpha(kGreen, 0.25);
    hA->Draw("same");
    cABCD->cd(2);
    hB->SetFillColorAlpha(kGreen, 0.25);
    hB->Draw("same");
    cABCD->cd(3);
    hC->SetFillColorAlpha(kGreen, 0.25);
    hC->Draw("same");
    cABCD->cd(4);
    hD->SetFillColorAlpha(kGreen, 0.25);
    hD->Draw("same");
    c->cd(0);
//    tDataB->Draw("mmkpkp >> hA",CutABCD,"same");
//    cABCD->cd(2);
//    tDataB->Draw("mmkpkppim >> hB",CutABCD,"same");
//    cABCD->cd(3);
//    tDataB->Draw("mlampim >> hC",CutABCD,"same");
//    cABCD->cd(4);
//    tDataB->Draw("mcasmMpim >> hD",CutABCD,"same");

    
    
    //draw line
    TLine *lXi=new TLine(MASS_Xi,0,MASS_Xi,1000);
    TLine *lLam=new TLine(MASS_Lambda,0,MASS_Lambda,1000);
    lXi->SetLineWidth(2);
    lXi->SetLineColor(kBlack);
    lXi->SetLineStyle(2);
    lLam->SetLineWidth(2);
    lLam->SetLineColor(kBlack);
    lLam->SetLineStyle(2);
    cABCD->cd(1);
    lXi->Draw("same");
    cABCD->cd(2);
    lLam->Draw("same");
    cABCD->cd(3);
    lXi->Draw("same");
    cABCD->cd(4);
    lLam->Draw("same");
    cABCD->cd(0);
    
    
    
}

void hyperspherecuts()
{
    //*
	//setup the style
	StyleUp();
	//get the cuts
	TCut CutABCD,CutABCD_sb,CutABCD_sb2;
	GetHyperSphereCut(CutABCD);
	GetHyperSphereSideBand(CutABCD_sb);
	GetHyperSphereSideBand2(CutABCD_sb2);
	//get the hists
	GetHists();

	//draw all four plots
	TCanvas *c=new TCanvas("c","c",1800,1200);
	c->Divide(2,2);
	c->cd(1);
	tDataB->Draw("mmkpkp >> hA",CutABCD);
	c->cd(2);
	tDataB->Draw("mmkpkppim >> hB",CutABCD);
	c->cd(3);
	tDataB->Draw("mlampim >> hC",CutABCD);
	c->cd(4);
	tDataB->Draw("mcasmMpim >> hD",CutABCD);
    
    
	//side band
	c->cd(1);
	tDataB->Draw("mmkpkp >> hA_sb",CutABCD_sb,"SAME");		
	c->cd(2);
	tDataB->Draw("mmkpkppim >> hB_sb",CutABCD_sb,"SAME");
	c->cd(3);
	tDataB->Draw("mlampim >> hC_sb",CutABCD_sb,"SAME");
	c->cd(4);
	tDataB->Draw("mcasmMpim >> hD_sb",CutABCD_sb,"SAME");
	
	//side band
	c->cd(1);
	tDataB->Draw("mmkpkp >> hA_sb2",CutABCD_sb2,"SAME");		
	c->cd(2);
	tDataB->Draw("mmkpkppim >> hB_sb2",CutABCD_sb2,"SAME");
	c->cd(3);
	tDataB->Draw("mlampim >> hC_sb2",CutABCD_sb2,"SAME");
	c->cd(4);
	tDataB->Draw("mcasmMpim >> hD_sb2",CutABCD_sb2,"SAME");

    cout << "number = " << hD->GetEntries() << ", sideband = " << hD_sb->GetEntries() << ", sideband2 = " << hD_sb2->GetEntries() <<endl;
    
	//draw line
	TLine *lXi=new TLine(MASS_Xi,0,MASS_Xi,1000);
	TLine *lLam=new TLine(MASS_Lambda,0,MASS_Lambda,1000);
	lXi->SetLineWidth(4);
	lXi->SetLineColor(kRed);
	lXi->SetLineStyle(4);
	lLam->SetLineWidth(4);
	lLam->SetLineColor(kGreen);
	lLam->SetLineStyle(5);
	c->cd(1);
	lXi->Draw("same");
	c->cd(2);
	lLam->Draw("same");
	c->cd(3);
	lXi->Draw("same");
	c->cd(4);
	lLam->Draw("same");
    c->cd(0);

	//print for thesis
	// cA->Print("./pics/massA.png");
	// cB->Print("./pics/massB.png");
	// cC->Print("./pics/massC.png");
	// cD->Print("./pics/massD.png");
	c->Print("~/Desktop/signal.png");

     }




void spherecuts()
{	
	//setup the style
	StyleUp();
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	
	//get the hists
	GetHists();

	//draw all four plots
	GetSphereCuts(CutA,CutB,CutC,CutD,0,3);
	TCanvas *cA=new TCanvas("cA","cA",1200,800);
	tDataB->Draw("mmkpkp >> hA",CutA);
	TCanvas *cB=new TCanvas("cB","cB",1200,800);
	tDataB->Draw("mmkpkppim >> hB",CutB);
	TCanvas *cC=new TCanvas("cC","cC",1200,800);
	tDataB->Draw("mlampim >> hC",CutC);
	TCanvas *cD=new TCanvas("cD","cD",1200,800);
	tDataB->Draw("mcasmMpim >> hD",CutD);
	
//	//side band
//	GetSphereCuts(CutA,CutB,CutC,CutD,3,6);
//	cA->cd();
//	tDataB->Draw("mmkpkp >> hA_sb",CutA,"SAME");		
//	cB->cd();
//	tDataB->Draw("mmkpkppim >> hB_sb",CutB,"SAME");
//	cC->cd();
//	tDataB->Draw("mlampim >> hC_sb",CutC,"SAME");
//	cD->cd();
//	tDataB->Draw("mcasmMpim >> hD_sb",CutD,"SAME");
//	
//	//side band
//	GetSphereCuts(CutA,CutB,CutC,CutD,6,9);
//	cA->cd();
//	tDataB->Draw("mmkpkp >> hA_sb2",CutA,"SAME");		
//	cB->cd();
//	tDataB->Draw("mmkpkppim >> hB_sb2",CutB,"SAME");
//	cC->cd();
//	tDataB->Draw("mlampim >> hC_sb2",CutC,"SAME");
//	cD->cd();
//	tDataB->Draw("mcasmMpim >> hD_sb2",CutD,"SAME");

	//print for thesis
//	cA->Print("./pics/massA.png");
//	cB->Print("./pics/massB.png");
//	cC->Print("./pics/massC.png");
//	cD->Print("./pics/massD.png");
}



void wrongpion()
{
	TTree *tree=tDataB;
	StyleUp();
	GetHists();
	GetWrongPionHists();
	TCut CutA,CutB,CutC,CutD;
//	TCut piB1 = "mmkpkppim > 1.12 && mmkpkppim < 1.125";
//	TCut piB2 = "mmkpkppim > 1.125 && mmkpkppim < 1.135";
	TCut piC1 =  "mlampim < 1.31";
		
	GetSeperateCuts2(CutA,CutB,CutC,CutD,0.5);
//	TCut cut = CutA&&"mmkpkppim < 1.12";
//	TCut sbcut1 = piB1&&CutA;
//	TCut sbcut2 = piB2&&CutA;

	TCut cut = CutA;
	TCut sbcut1 = piC1&&CutA;	
	
	TCanvas *ctemp=new TCanvas("ctemp","",10,10);
	tree->Draw("mmkpkp >> hA",cut);
	tree->Draw("mmkpkppim >> hB",cut);
	tree->Draw("mlampim >> hC",cut);
	tree->Draw("mcasmMpim >> hD",cut);
	
	tree->Draw("mmkpkp >> hA_sb",sbcut1);
	tree->Draw("mmkpkppim >> hB_sb",sbcut1);
	tree->Draw("mlampim >> hC_sb",sbcut1);
	tree->Draw("mcasmMpim >> hD_sb",sbcut1);
	
	// tree->Draw("mmkpkp >> hA_sb2",sbcut2);
	// tree->Draw("mmkpkppim >> hB_sb2",sbcut2);
	// tree->Draw("mlampim >> hC_sb2",sbcut2);
	// tree->Draw("mcasmMpim >> hD_sb2",sbcut2);
		
	tree->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>> hT",cut);
	tree->Draw("mlamMpim >> hP",cut);
	tree->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>> hT_sb",sbcut1);
	tree->Draw("mlamMpim >> hP_sb",sbcut1);
	// tree->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>> hT_sb2",sbcut2);
	// tree->Draw("mlamMpim >> hP_sb2",sbcut2);

	TCanvas *cpi=new TCanvas("cpi","cpi",1200,800);
	cpi->Divide(2,2);
	cpi->cd(1);
	hA->Draw();
	hA_sb->Draw("SAME");
	hA_sb2->Draw("SAME");
	cpi->cd(2);
	hB->Draw();
	hB_sb->Draw("SAME");
	hB_sb2->Draw("SAME");
	cpi->cd(3);
	hC->Draw();
	hC_sb->Draw("SAME");
	hC_sb2->Draw("SAME");
	cpi->cd(4);
	hD->Draw();
	hD_sb->Draw("SAME");
	hD_sb2->Draw("SAME");
	
	TCanvas *cT=new TCanvas("cT","cT",1200,800);
	cT->Divide(2,1);
	cT->cd(1);
	hT->Draw();
	hT_sb->Draw("same");
	hT_sb2->Draw("same");
	cT->cd(2);
	hP->Draw();
	hP_sb->Draw("same");
	hP_sb2->Draw("same");
}
	
	
	
void unknownsideband()
{
	TTree *tree=tDataB;
	TTree *tree_sb=tDataD;
	StyleUp();
	GetHists();
	GetWrongPionHists();
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts2(CutA,CutB,CutC,CutD,0.5);
	

			
	
	TCanvas *ctemp=new TCanvas("ctemp","",10,10);
	tree->Draw("mmkpkp >> hA",CutA);
	tree->Draw("mmkpkppim >> hB",CutA);
	tree->Draw("mlampim >> hC",CutA);
	tree->Draw("mcasmMpim >> hD",CutA);
	
	tree_sb->Draw("mmkpkp >> hA_sb");
	tree_sb->Draw("mmkpkppim >> hB_sb");
	tree_sb->Draw("mlampim >> hC_sb");
	tree_sb->Draw("mcasmMpim >> hD_sb");
	

	tree->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>>hT",CutA);
	tree->Draw("mlamMpim >> hP",CutA);
	tree_sb->Draw("vtime-(sctpim-sclpim/(betapim*29.99))>> hT_sb");
	tree_sb->Draw("mlamMpim >> hP_sb");


	TCanvas *cpi=new TCanvas("cpi","cpi",1200,800);
	cpi->Divide(2,2);
	cpi->cd(1);
	hA->Draw();
	hA_sb->Draw("SAME");
	hA_sb2->Draw("SAME");
	cpi->cd(2);
	hB->Draw();
	hB_sb->Draw("SAME");
	hB_sb2->Draw("SAME");
	cpi->cd(3);
	hC->Draw();
	hC_sb->Draw("SAME");
	hC_sb2->Draw("SAME");
	cpi->cd(4);
	hD->Draw();
	hD_sb->Draw("SAME");
	hD_sb2->Draw("SAME");
	
	TCanvas *cT=new TCanvas("cT","cT",1200,800);
	cT->Divide(2,1);
	cT->cd(1);
	hT->Draw();
	hT_sb->Draw("same");
	hT_sb2->Draw("same");
	cT->cd(2);
	hP->Draw();
	hP_sb->Draw("same");
	hP_sb2->Draw("same");
}
	
	
	
	
void Mass234()
{
	StyleUp();
	gStyle->SetOptStat(0);
	Get4x7Hists();
	
	TCanvas *ctemp=new TCanvas("ctemp","",10,10);
	tDataM9->Draw("mmkpkp >> hA9");
	tDataM9->Draw("mmkpkppim >> hB9");
	tDataM9->Draw("mlampim >> hC9");
	tDataM9->Draw("mcasmMpim >> hD9");
	
	tDataM6->Draw("mmkpkp >> hA6");
	tDataM6->Draw("mmkpkppim >> hB6");
	tDataM6->Draw("mlampim >> hC6");
	tDataM6->Draw("mcasmMpim >> hD6");
	
	tDataM5->Draw("mmkpkp >> hA5");
	tDataM5->Draw("mmkpkppim >> hB5");
	tDataM5->Draw("mlampim >> hC5");
	tDataM5->Draw("mcasmMpim >> hD5");
	
	tDataM4->Draw("mmkpkp >> hA4");
	tDataM4->Draw("mmkpkppim >> hB4");
	tDataM4->Draw("mlampim >> hC4");
	tDataM4->Draw("mcasmMpim >> hD4");
	
	tDataM3->Draw("mmkpkp >> hA3");
	tDataM3->Draw("mmkpkppim >> hB3");
	tDataM3->Draw("mlampim >> hC3");
	tDataM3->Draw("mcasmMpim >> hD3");
	
	tDataM2->Draw("mmkpkp >> hA2");
	tDataM2->Draw("mmkpkppim >> hB2");
	tDataM2->Draw("mlampim >> hC2");
	tDataM2->Draw("mcasmMpim >> hD2");
	
	tDataM1->Draw("mmkpkp >> hA1");
	tDataM1->Draw("mmkpkppim >> hB1");
	tDataM1->Draw("mlampim >> hC1");
	tDataM1->Draw("mcasmMpim >> hD1");

	hA4->SetFillColor(2);
	hB4->SetFillColor(2);
	hC4->SetFillColor(2);
	hD4->SetFillColor(2);

	hA2->SetFillColor(4);
	hB2->SetFillColor(4);
	hC2->SetFillColor(4);
	hD2->SetFillColor(4);


	TCanvas *cpi=new TCanvas("cpi","cpi",1200,800);
	cpi->Divide(2,2);
	cpi->cd(1);
	//hA9->Draw();
	//hA6->Draw();
	//hA5->Draw("SAME");
	hA4->Draw();
	hA3->Draw("SAME");
	hA2->Draw("SAME");
	//hA1->Draw("SAME");
	cpi->cd(2);
	//hB9->Draw();
	//hB6->Draw();
	//hB5->Draw("SAME");
	hB4->Draw();
	hB3->Draw("SAME");
	hB2->Draw("SAME");
	//hB1->Draw("SAME");
	cpi->cd(3);
	//hC9->Draw();
	//hC6->Draw();
	//hC5->Draw("SAME");
	hC4->Draw();
	hC3->Draw("SAME");
	hC2->Draw("SAME");
	//hC1->Draw("SAME");
	cpi->cd(4);
	//hD9->Draw();
	//hD6->Draw();
	//hD5->Draw("SAME");
	hD4->Draw();
	hD3->Draw("SAME");
	hD2->Draw("SAME");
	//hD1->Draw("SAME");
	
	TCanvas *c=new TCanvas("c","",1,1);
	c->cd(0);
}
	
	




////////////////////////////////////////////////////////////
void FindSigmas()  //originally made, and will use this for thesis (april 2014)
{
	StyleUp();
	gStyle->SetOptStat(0);
	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfitGBG.C");

	Double_t t0 = 1;
	Double_t t1 = 1;
	Double_t t2 = 1;
	Double_t t3 = 1;
	Double_t t4 = 1;
	Double_t Yield = 0;
	Double_t Yielderr = 0;

	const string choice = "Data";
	//cout << "For Data or MC? (type Data or MC)";
	//cin >> choice;
	if (choice.compare("Data") == 0) 
	{		
		TFile *ftemp = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic.root");
		TTree *ttemp = (TTree*)ftemp->Get("v16");
		Double_t fitWidth = 0.015;
		Double_t fitWidthFloat = 0.15;
	}
	else if (choice.compare("MC") == 0)
	{
		TFile *ftemp = TFile::Open("~/clas/rootfiles/LINKS/MC-i7-2kppim_Basic.root");
		//TFile *ftemp = TFile::Open("~/clas/rootfiles/LINKS/MC-i0t0-2kppim.root");
		TTree *ttemp = (TTree*)ftemp->Get("gpp2kppim");
		Double_t fitWidth = 0.0002;
		Double_t fitWidthFloat = 0.01;
	}
	else if (choice.compare("test") == 0)
	{
		TFile *ftemp = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/TimeingTests/MKWay2.root");
		TTree *ttemp = (TTree*)ftemp->Get("work");
		Double_t fitWidth = 0.0002;
		Double_t fitWidthFloat = 0.01;
	}
	
	
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts(CutA,CutB,CutC,CutD);
	
	GetHists();
	
	//draw the stuff
	TCanvas *cABCD=new TCanvas("cA","cA",1800,1200);
	cABCD->Divide(2,2);
	cABCD->cd(1);
	ttemp->Draw("mmkpkp >> hA",CutC&&CutD);
	gausfit(hA,1,1.2,1.45,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(2);
	ttemp->Draw("mmkpkppim >> hB",CutC&&CutD);
	gausfit(hB,1,1.05,1.2,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(3);
	ttemp->Draw("mlampim >> hC",CutA&&CutB);

	Double_t MYBACKGROUND =0;
	Double_t MYRMS=0;
	Double_t MYMEAN=0;
	gausfit(hC,1,1.27,1.37,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	//gausfitGBG(hC,1,1.27,1.37,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,MYBACKGROUND,Yield,MYRMS,MYMEAN, Yielderr);
	cABCD->cd(4);
	ttemp->Draw("mcasmMpim >> hD",CutA&&CutB);
	gausfit(hD,1,1.06,1.16,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	
	
	
	//draw line
	TLine *lXi=new TLine(MASS_Xi,0,MASS_Xi,1000);
	TLine *lLam=new TLine(MASS_Lambda,0,MASS_Lambda,1000);
	lXi->SetLineWidth(1);
	//lXi->SetLineStyle(4);
	lXi->SetLineColor(kRed);
	lLam->SetLineWidth(1);
	//lLam->SetLineStyle(5);
	lLam->SetLineColor(kGreen);
	cABCD->cd(1);
	lXi->Draw("same");
	cABCD->cd(2);
	lLam->Draw("same");
	cABCD->cd(3);
	lXi->Draw("same");
	cABCD->cd(4);
	lLam->Draw("same");
	
	
	
	cABCD->Print("~/Desktop/width.png");
}

void FindSigmas2() //this is upon the request of valery and johann (it just has different cuts)
{	
	StyleUp();
	gStyle->SetOptStat(0);
	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	Double_t fitWidth = 0.015;
	Double_t fitWidthFloat = 0.15;
	Double_t t0 = 1;
	Double_t t1 = 1;
	Double_t t2 = 1;
	Double_t t3 = 0;
	Double_t t4 = 0;
	Double_t Yield = 0;
	Double_t Yielderr = 0;
		
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts(CutA,CutB,CutC,CutD);
	
	GetHists();
	
	//draw the stuff
	TCanvas *cABCD=new TCanvas("cA","cA",1200,800);
	cABCD->Divide(2,2);
	cABCD->cd(1);
	tDataB->Draw("mmkpkp >> hA",CutB);
	gausfit(hA,1,1.2,1.45,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(2);
	tDataB->Draw("mmkpkppim >> hB",CutA);
	gausfit(hB,1,1.05,1.2,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(3);
	tDataB->Draw("mlampim >> hC",CutD);
	gausfit(hC,1,1.27,1.37,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(4);
	tDataB->Draw("mcasmMpim >> hD",CutC);
	gausfit(hD,1,1.06,1.16,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	
	
	
	cABCD->Print("./pics/FindSigmas2.eps");
}




void FindSigmasSphere() //oct 27 2013 after DNP in newport news
{
	
	
	StyleUp();
	gStyle->SetOptStat(1);
	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	Double_t fitWidth = 0.015;
	Double_t fitWidthFloat = 0.15;
	Double_t t0 = 1;
	Double_t t1 = 1;
	Double_t t2 = 1;
	Double_t t3 = 0;
	Double_t t4 = 0;
	Double_t Yield = 0;
	Double_t Yielderr = 0;
	
	
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	GetSphereCuts(CutA,CutB,CutC,CutD,0,3);
	
	GetHists();
	
	//draw the stuff
	TCanvas *cABCD=new TCanvas("cA","cA",1200,800);
	cABCD->Divide(2,2);
	cABCD->cd(1);
	tDataB->Draw("mmkpkp >> hA",CutA);
	gausfit(hA,1,1.2,1.45,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(2);
	tDataB->Draw("mmkpkppim >> hB",CutB);
	gausfit(hB,1,1.05,1.2,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(3);
	tDataB->Draw("mlampim >> hC",CutC);
	gausfit(hC,1,1.27,1.37,t0,t1,t2,t3,t4,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	cABCD->cd(4);
	tDataB->Draw("mcasmMpim >> hD",CutD);
	gausfit(hD,1,1.06,1.16,t0,t1,t2,t3,t4,MASS_Lambda,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	
	
	
	//cABCD->Print("./pics/FindSigmas2.eps");
}




void Show_Xim() //for lei at the clas colaboration meeting in feb 2013
{
	
	
	StyleUp();
	gStyle->SetOptStat(0);
	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	Double_t fitWidth = 0.015;
	Double_t fitWidthFloat = 0.15;
	Double_t t0 = 1;
	Double_t t1 = 1;
	Double_t t2 = 1;
	Double_t t3 = 0;
	Double_t t4 = 0;
	Double_t Yield = 0;
	Double_t Yielderr = 0;
	
	
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts(CutA,CutB,CutC,CutD);
	
	//hist models
	TH1F *hA=new TH1F("hA","",33,1.25,1.45);  // 200/33 = 6 MeV 
	hA->SetMinimum(0);
	hA->SetFillColor(4);
	hA->GetYaxis()->SetTitle("Events/6MeV/c^{2}");
	hA->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
	
	//hist models
	TH1F *hC=new TH1F("hC","",100,1.25,1.45);  // 200/100 = 2 MeV 
	hC->SetMinimum(0);
	hC->SetFillColor(4);
	hC->GetYaxis()->SetTitle("Events/2MeV/c^{2}");
	hC->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	
	
	
	
	//draw the stuff
	TCanvas *cA=new TCanvas("cA","cA",1200,800);
	tDataB->Draw("mmkpkp >> hA",CutC&&CutD);
	gausfit(hA,1,1.26,1.42,1,1,0,0,0,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);

	//draw the stuff
	TCanvas *cC=new TCanvas("cC","cC",1200,800);
	tDataB->Draw("mlampim >> hC",CutA&&CutB);
	gausfit(hC,1,1.26,1.42,1,1,0,0,0,MASS_Xi,fitWidth,fitWidthFloat,3,0,Yield,0,0,Yielderr);
	
	
	cA->Print("./pics/Xim_mmkpkp_kpkppim.eps");
	cC->Print("./pics/Xim_mlampim_kpkppim.eps");
}






void ShowWithRectangular()
{
	

	StyleUp();
	gStyle->SetOptStat(0);
	const string choice;
	cout << "For Data or MC? (type Data or MC)";
	cin >> choice;
	if (choice.compare("Data") == 0) 
	{		
		TFile *ftemp = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic.root");
		TTree *ttemp = (TTree*)ftemp->Get("v05");
		Double_t fitWidth = 0.015;
		Double_t fitWidthFloat = 0.15;
	}
	else if (choice.compare("MC") == 0)
	{
		TFile *ftemp = TFile::Open("~/clas/rootfiles/LINKS/MC-i7-2kppim_Basic.root");
		//TFile *ftemp = TFile::Open("~/clas/rootfiles/LINKS/MC-i0t0-2kppim.root");
		TTree *ttemp = (TTree*)ftemp->Get("gpp2kppim");
		Double_t fitWidth = 0.0002;
		Double_t fitWidthFloat = 0.01;
	}
	
	
	//get the cuts
	TCut CutA,CutB,CutC,CutD;
	GetSeperateCuts(CutA,CutB,CutC,CutD);
	
	GetHists();
	
	//draw the stuff
	TCanvas *cABCD=new TCanvas("cA","cA",1200,800);
	cABCD->Divide(2,2);
	cABCD->cd(1);
	ttemp->Draw("mmkpkp >> hA",CutC&&CutD);

	cABCD->cd(2);
	ttemp->Draw("mmkpkppim >> hB",CutC&&CutD);
	
	cABCD->cd(3);
	ttemp->Draw("mlampim >> hC",CutA&&CutB);

	cABCD->cd(4);
	ttemp->Draw("mcasmMpim >> hD",CutA&&CutB);

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
void GetSeperateCuts2(TCut &CutA,TCut &CutB,TCut &CutC,TCut &CutD, Float_t depth)
{
	
	CutA = Form("sqrt( (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) ) < 1 ",MASS_Xi,MASS_Xi,widthA*depth,widthA*depth);
	CutB = Form("sqrt( (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) ) < 1 ",MASS_Lambda,MASS_Lambda,widthB*depth,widthB*depth);
	CutC = Form("sqrt( (mlampim  - %f)*(mlampim  - %f)/(%f*%f) ) < 1 ",MASS_Xi,MASS_Xi,widthC*depth,widthC*depth);
	CutD = Form("sqrt( (mcasmMpim  - %f)*(mcasmMpim  - %f)/(%f*%f) ) < 1 ",MASS_Lambda,MASS_Lambda,widthD*depth,widthD*depth);		
	
}



void GetSphereCuts(TCut &CutA,TCut &CutB,TCut &CutC,TCut &CutD, Float_t depthlow, Float_t depthhigh)
{
	TCut cond1A,cond2A;
	cond1A = Form("sqrt( (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > %f"
	,MASS_Lambda,MASS_Lambda,sigmaB,sigmaB,MASS_Xi,MASS_Xi,sigmaC,sigmaC,MASS_Lambda,MASS_Lambda,sigmaD,sigmaD,depthlow);
	cond2A = Form("sqrt( (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < %f"
	,MASS_Lambda,MASS_Lambda,sigmaB,sigmaB,MASS_Xi,MASS_Xi,sigmaC,sigmaC,MASS_Lambda,MASS_Lambda,sigmaD,sigmaD,depthhigh);	
	CutA = cond1A&&cond2A;
	
	TCut cond1B,cond2B;
	cond1B = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > %f"
	,MASS_Xi,MASS_Xi,sigmaA,sigmaA,MASS_Xi,MASS_Xi,sigmaC,sigmaC,MASS_Lambda,MASS_Lambda,sigmaD,sigmaD,depthlow);
	cond2B = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < %f"
	,MASS_Xi,MASS_Xi,sigmaA,sigmaA,MASS_Xi,MASS_Xi,sigmaC,sigmaC,MASS_Lambda,MASS_Lambda,sigmaD,sigmaD,depthhigh);	
	CutB = cond1B&&cond2B;
	
	TCut cond1C,cond2C;
	cond1C = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) > %f"
	,MASS_Xi,MASS_Xi,sigmaA,sigmaA,MASS_Lambda,MASS_Lambda,sigmaB,sigmaB,MASS_Lambda,MASS_Lambda,sigmaD,sigmaD,depthlow);
	cond2C = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < %f"
	,MASS_Xi,MASS_Xi,sigmaA,sigmaA,MASS_Lambda,MASS_Lambda,sigmaB,sigmaB,MASS_Lambda,MASS_Lambda,sigmaD,sigmaD,depthhigh);	
	CutC = cond1C&&cond2C;
	
	TCut cond1D,cond2D;
	cond1D = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) ) > %f"
	,MASS_Xi,MASS_Xi,sigmaA,sigmaA,MASS_Lambda,MASS_Lambda,sigmaB,sigmaB,MASS_Xi,MASS_Xi,sigmaC,sigmaC,depthlow);
	cond2D = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) ) < %f"
	,MASS_Xi,MASS_Xi,sigmaA,sigmaA,MASS_Lambda,MASS_Lambda,sigmaB,sigmaB,MASS_Xi,MASS_Xi,sigmaC,sigmaC,depthhigh);
	CutD = cond1D&&cond2D;
	
}


//------------------------
void GetHists()
{	
		//hist models
		TH1F *hCas=new TH1F("hCas","",100,1.25,1.35);  //160   //480
		hCas->SetMinimum(0);
		hCas->SetFillColor(4);
		TH1F *hLam=new TH1F("hLam","",100,1.05,1.15); //160  //480
		hLam->SetMinimum(0);
		hLam->SetFillColor(4);

		//good signal hists
		hA = (TH1F*)hCas->Clone("hA");
		hA->GetYaxis()->SetTitle("Events/1MeV");
		hA->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV)");
		hC = (TH1F*)hCas->Clone("hC");
		hC->GetYaxis()->SetTitle("Events/1MeV");
		hC->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV)");
		hB = (TH1F*)hLam->Clone("hB");
		hB->GetYaxis()->SetTitle("Events/1MeV");
		hB->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV)");
		hD = (TH1F*)hLam->Clone("hD");	
		hD->GetYaxis()->SetTitle("Events/1MeV");
		hD->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV)");
		
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
    
    
    //for fit spectra
    hAfit = (TH1F*)hCas->Clone("hAfit");
    hAfit->GetYaxis()->SetTitle("Events/1MeV");
    hAfit->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV)");
    hCfit = (TH1F*)hCas->Clone("hCfit");
    hCfit->GetYaxis()->SetTitle("Events/1MeV");
    hCfit->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV)");
    hBfit = (TH1F*)hLam->Clone("hBfit");
    hBfit->GetYaxis()->SetTitle("Events/1MeV");
    hBfit->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV)");
    hDfit = (TH1F*)hLam->Clone("hDfit");
    hDfit->GetYaxis()->SetTitle("Events/1MeV");
    hDfit->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV)");
}



void Get4x7Hists()
{	
		//hist models
		TH1F *hCas=new TH1F("hCas","",100,1.25,1.35);  //160   //480
		hCas->SetMinimum(0);
		hCas->SetFillColor(10);
		TH1F *hLam=new TH1F("hLam","",100,1.05,1.15); //160  //480
		hLam->SetMinimum(0);
		hLam->SetFillColor(10);

		//1 sigma hists
		hA1 = (TH1F*)hCas->Clone("hA1");
		hA1->GetYaxis()->SetTitle("Events/1MeV/c^{2}");
		hA1->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");  
		hC1 = (TH1F*)hCas->Clone("hC1");
		hC1->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hC1->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
		hB1 = (TH1F*)hLam->Clone("hB1");
		hB1->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hB1->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
		hD1 = (TH1F*)hLam->Clone("hD1");	
		hD1->GetYaxis()->SetTitle("Events/1MeV/c^{2}");  
		hD1->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
		
		//2 sigma hists
		hA2 = (TH1F*)hA1->Clone("hA2");
		hA2->SetMinimum(0);
		hA2->SetFillColor(25);
		hC2 = (TH1F*)hC1->Clone("hC2");
		hC2->SetMinimum(0);
		hC2->SetFillColor(25);
		hB2 = (TH1F*)hB1->Clone("hB2");
		hB2->SetMinimum(0);
		hB2->SetFillColor(25);
		hD2 = (TH1F*)hD1->Clone("hD2");
		hD2->SetMinimum(0);
		hD2->SetFillColor(25);
	
		//3 sigma hists
		hA3 = (TH1F*)hA1->Clone("hA3");
		hA3->SetMinimum(0);
		hA3->SetFillColor(1);
		hC3 = (TH1F*)hC1->Clone("hC3");
		hC3->SetMinimum(0);
		hC3->SetFillColor(1);
		hB3 = (TH1F*)hB1->Clone("hB3");
		hB3->SetMinimum(0);
		hB3->SetFillColor(1);
		hD3 = (TH1F*)hD1->Clone("hD3");
		hD3->SetMinimum(0);
		hD3->SetFillColor(1);
		
		//4 sigma hists
		hA4 = (TH1F*)hA1->Clone("hA4");
		hA4->SetMinimum(0);
		hA4->SetFillColor(32);
		hC4 = (TH1F*)hC1->Clone("hC4");
		hC4->SetMinimum(0);
		hC4->SetFillColor(32);
		hB4 = (TH1F*)hB1->Clone("hB4");
		hB4->SetMinimum(0);
		hB4->SetFillColor(32);
		hD4 = (TH1F*)hD1->Clone("hD4");
		hD4->SetMinimum(0);
		hD4->SetFillColor(32);
				
		//5 sigma hists
		hA5 = (TH1F*)hA1->Clone("hA5");
		hA5->SetMinimum(0);
		hA5->SetFillColor(38);
		hC5 = (TH1F*)hC1->Clone("hC5");
		hC5->SetMinimum(0);
		hC5->SetFillColor(38);
		hB5 = (TH1F*)hB1->Clone("hB5");
		hB5->SetMinimum(0);
		hB5->SetFillColor(38);
		hD5 = (TH1F*)hD1->Clone("hD5");
		hD5->SetMinimum(0);
		hD5->SetFillColor(38);
		
		//6 sigma hists
		hA6 = (TH1F*)hA1->Clone("hA6");
		hA6->SetMinimum(0);
		hA6->SetFillColor(46);
		hC6 = (TH1F*)hC1->Clone("hC6");
		hC6->SetMinimum(0);
		hC6->SetFillColor(46);
		hB6 = (TH1F*)hB1->Clone("hB6");
		hB6->SetMinimum(0);
		hB6->SetFillColor(46);
		hD6 = (TH1F*)hD1->Clone("hD6");
		hD6->SetMinimum(0);
		hD6->SetFillColor(46);
		
		//9 sigma hists
		hA9 = (TH1F*)hA1->Clone("hA9");
		hA9->SetMinimum(0);
		hA9->SetFillColor(2);
		hC9 = (TH1F*)hC1->Clone("hC9");
		hC9->SetMinimum(0);
		hC9->SetFillColor(2);
		hB9 = (TH1F*)hB1->Clone("hB9");
		hB9->SetMinimum(0);
		hB9->SetFillColor(2);
		hD9 = (TH1F*)hD1->Clone("hD9");
		hD9->SetMinimum(0);
		hD9->SetFillColor(2);
		
}


void GetWrongPionHists()
{	
		//hist models
		TH1F *hTime=new TH1F("hTime","",100,-2,2);
		hTime->SetMinimum(0);
		hTime->SetFillColor(4);
		TH1F *hPro=new TH1F("hPro","",100,0.8,0.95);
		hPro->SetMinimum(0);
		hPro->SetFillColor(4);

		//good signal hists
		hT = (TH1F*)hTime->Clone("hT");
		hT->GetYaxis()->SetTitle("Events");
		hT->GetXaxis()->SetTitle("RF - piTOF (ns)");
		hP = (TH1F*)hPro->Clone("hP");
		hP->GetYaxis()->SetTitle("Events");
		hP->GetXaxis()->SetTitle(" M(#Lambda - #pi^{-}) (GeV/c^{2})");

		//sideband hists
		hT_sb = (TH1F*)hT->Clone("hT_sb");
		hT_sb->SetMinimum(0);
		hT_sb->SetFillColor(2);
		hP_sb = (TH1F*)hP->Clone("hP_sb");
		hP_sb->SetMinimum(0);
		hP_sb->SetFillColor(2);

		//sideband2 hists
		hT_sb2 = (TH1F*)hT->Clone("hT_sb2");
		hT_sb2->SetMinimum(0);
		hT_sb2->SetFillColor(1);
		hP_sb2 = (TH1F*)hP->Clone("hP_sb2");
		hP_sb2->SetMinimum(0);
		hP_sb2->SetFillColor(1);
}






void StyleUp()
{
    
    gStyle->SetLabelSize(0.02);
	gStyle->SetTitleXOffset(0.68);
	gStyle->SetTitleYOffset(0.8);
	gStyle->SetTitleSize(0.07);
	gStyle->SetTitleYSize(0.065);
	gStyle->SetPadTopMargin(0.0005);
    //gStyle->SetPadBottomMargin(0.005);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(1);
    gStyle->SetLabelSize(0.05, "XY");
}



