void Read_SC_Hists()
{
	
	StyleUp();

	//MC
	TFile* fMC = new TFile("./hists/SCinfo_MC.root");
	TH1F *hMC;
	hMC = (TH1F*)fMC->Get("h2d");
	hMC->SetTitle("MC");
	hMC->SetName("MC");
	hMC->GetXaxis()->SetRange(0,58);
	hMC->GetYaxis()->SetTitle("Sector");
	hMC->GetXaxis()->SetTitle("SC paddle id (MC)");
	
	//Data
	TFile* fData = new TFile("./hists/SCinfo_Data.root");
	TH1F *hData;
	hData = (TH1F*)fData->Get("h2d");
	hData->SetTitle("Data");
	hData->SetName("Data");
	hData->GetXaxis()->SetRange(0,58);
	hData->GetYaxis()->SetTitle("Sector");
	hData->GetXaxis()->SetTitle("SC paddle id (Data)");
	
	
	//normaize the data to the mc
	//Float_t fac = hMC->Integral()/hData->Integral();
	//hData->Scale(fac);
	
	
	TCanvas *cSC = new TCanvas("cSC","cSC",1000,800);
	cSC->Divide(2,1);
	cSC->cd(1);
	hMC->Draw("colz");
	cSC->cd(2);
	hData->Draw("colz");
	
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
	gStyle->SetOptStat(1);
}