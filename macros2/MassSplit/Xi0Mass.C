/*

Author: Jason Bono
Date: Feb 4 2013
Purpose: To measure the mass of the Xi0 through the plotting of:
MM(K0 K+)
MM(Pi+ Pi- K+)



*/





TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/kppippim/v03_Basic2.root");
TTree *tData = (TTree*)fData->Get("v03_Basic");



/*
TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/kppippim/kppippim-v02_Basic.root");
TTree *tData = (TTree*)fData->Get("v02_Basic");
*/



void Xi0Mass()
{
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	StyleUp();
	Double_t K0_MASS = 0.497614;


	TCut cut_mpippim = "abs(mpippim - 0.497614) < 0.01";
	TCut cut = cut_mpippim;
	//TCut cut = "beam > 0";
	
	TCanvas *cMass=new TCanvas("cMass","cMass",1200,800);
	cMass->Divide(2,3);


	//histo model
	TH1F *hMassData=new TH1F("hMass","",1000,0,3);
	hMass->SetMinimum(0);
	hMass->SetMarkerStyle(21);
	hMass->SetFillStyle(3002);
	hMass->SetFillColor(3);
	hMass->GetYaxis()->SetTitle("Events");
	hMass->GetXaxis()->SetTitle("Mass (GeV/c) ");
	//histos used
	hMMkppippim = (TH1F*)hMass->Clone("hMMkppippim");
	hMMkpk0 = (TH1F*)hMass->Clone("hMMkpk0");
	hMMk0 = (TH1F*)hMass->Clone("hMMk0");
	hMpippim = (TH1F*)hMass->Clone("hMpippim");
	hMMpippim = (TH1F*)hMass->Clone("hMMpippim");
	//Xaxis
	hMMkppippim->GetXaxis()->SetTitle("mm(K^{+} #pi^{+} #pi^{-} ) (GeV/c) ");
	hMMkpk0->GetXaxis()->SetTitle("mm(K^{+} K^{0} ) (GeV/c) ");
	hMMk0->GetXaxis()->SetTitle("mm(K^{0} ) (GeV/c) ");
	hMpippim->GetXaxis()->SetTitle("m( #pi^{+} #pi^{-} ) (GeV/c) ");
	hMMpippim->GetXaxis()->SetTitle("mm( #pi^{+} #pi^{-} ) (GeV/c) ");
	//nocor hists
	hMMkppippim_nocor = (TH1F*)hMMkppippim->Clone("hMMkppippim_nocor");
	hMpippim_nocor = (TH1F*)hMpippim->Clone("hMpippim_nocor");
	hMMkppippim_nocor->SetFillColor(4);
	hMpippim_nocor->SetFillColor(4);

	//draw the hists
	cMass->cd(1);
	tData->Draw("mmkppippim>>hMMkppippim",cut);
//	tData->Draw("mmkppippim_no_corrections>>hMMkppippim_no_pcor",cut,"SAME");

	cMass->cd(2);
	tData->Draw("mmkpk0>>hMMkpk0",cut);

	cMass->cd(3);
	tData->Draw("mmk0>>hMMk0",cut);

	cMass->cd(4);
	tData->Draw("mpippim>>hMpippim",cut);
//	tData->Draw("mpippim_no_corrections>>hMpippim_no_pcor",cut,"SAME");

	cMass->cd(5);
	tData->Draw("mmpippim>>hMMpippim",cut);

	//cCompareMassK2Xi->Print("./pics/CompareMassK2Xi_overlay.eps");
	//gROOT->ProcessLine(".q");
}
	
	
//=========================================================	
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
	gStyle->SetOptStat(1);
}

