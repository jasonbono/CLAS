void Read_DC_Hists()
{
	gStyle->SetOptStat(0);
	const Int_t Ns = 6;
	TFile* fMC = new TFile("./hists/pdu_10.root");
	TH2F *hOccMC[Ns];
	TH2F *hChangeMC[Ns];
	TFile* fData = new TFile("./hists/pdu_56363.root");
	TH2F *hOccData[Ns];
	TH2F *hChangeData[Ns];
	


	TCanvas *cOcc[Ns];
	for (int s=0; s<Ns; s++)
	{
		hOccMC[s] = (TH2F*)fMC->Get(Form("h2%i0",s+1));
		hOccData[s] = (TH2F*)fData->Get(Form("h2%i0",s+1));
		hOccMC[s]->GetYaxis()->SetTitle("Layer Number");	
		hOccData[s]->GetYaxis()->SetTitle("Layer Number");	
		hOccMC[s]->GetXaxis()->SetTitle("Wire Number (MC)");
		hOccData[s]->GetXaxis()->SetTitle("Wire Number (Data)");
		
		Float_t fac = hOccMC[s]->Integral()/hOccData[s]->Integral(); //to normalize the histograms
		hOccData[s]->Scale(fac);
		
		cOcc[s] = new TCanvas(Form("cOcc%i",s),Form("Sector-%i",s+1),1200,800);
		cOcc[s]->Divide(2,1);
		cOcc[s]->cd(1);
		hOccMC[s]->Draw("colz");
		cOcc[s]->cd(2);
		hOccData[s]->Draw("colz");
		
		


	}





	TCanvas *cChange[Ns];
	for (int s=0; s<Ns; s++)
	{
		hChangeMC[s] = (TH2F*)fMC->Get(Form("h3%i0",s+1));
		hChangeData[s] = (TH2F*)fData->Get(Form("h3%i0",s+1));
		hChangeMC[s]->GetYaxis()->SetTitle("Layer Number");	
		hChangeData[s]->GetYaxis()->SetTitle("Layer Number");	
		hChangeMC[s]->GetXaxis()->SetTitle("Wire Number (MC)");
		hChangeData[s]->GetXaxis()->SetTitle("Wire Number (Data)");
		
		Float_t fac = hChangeMC[s]->Integral()/hChangeData[s]->Integral(); //to normalize the histograms
		hChangeData[s]->Scale(fac);
		
		cChange[s] = new TCanvas(Form("cChange%i",s),Form("Sector-%i",s+1),1200,800);
		cChange[s]->Divide(2,1);
		cChange[s]->cd(1);
		hChangeMC[s]->Draw("colz");
		cChange[s]->cd(2);
		hChangeData[s]->Draw("colz");
		

	}








	
}