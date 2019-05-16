



void ReadHist()
{
	
	TFile* fHistos = new TFile("./SCinfo_MC.root");
	TH1F *h;
	h = (TH1F*)fHistos->Get("h2d");
	h->Draw("colz");
	
}