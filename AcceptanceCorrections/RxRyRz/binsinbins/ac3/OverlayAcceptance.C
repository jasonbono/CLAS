


void OverlayAcceptance()
{
	
	const int Na = 2,Nb = 2,Nd = 3; //a=datatype, b=bintype, c=binnumber, d=piaxis
	const char* DataType[Na] = {"MC","Gen"};
	const char* BinType[Nb] = {"E","Xi"};
	const char* Axis[Nd] = {"x","y","z"};
	
	const int Ne=10; //Ne=#parameters in fit
	int Nk = 40; //# of pion bins
	const int Nq = 10; //number of energy and Xi bins for acceptance corrections
	
	TFile* fACNoPol = new TFile(Form("./hists/AcceptaceHists-NoPol-%i_%ibins.root",Nk,Nq));
	TFile* fACPosPol = new TFile(Form("./hists/AcceptaceHists-PosPol-%i_%ibins.root",Nk,Nq));
	
	
	TH1D *hAcNoPol[Nb][Nq][Nd];
	TH1D *hAcPosPol[Nb][Nq][Nd];
	

	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			for (int d = 0; d < Nd; d++)
			{	
				hAcNoPol[b][q][d] = (TH1D*)fACNoPol->Get(Form("hAc-%sBin%i-PiAxis%s",BinType[b],q,Axis[d]));
				hAcPosPol[b][q][d] = (TH1D*)fACPosPol->Get(Form("hAc-%sBin%i-PiAxis%s",BinType[b],q,Axis[d]));
				hAcNoPol[b][q][d]->SetLineColor(1);
			}
		}
	}
	
	
	
	TCanvas *can[Nb][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int d = 0; d < Nd; d++)
		{	
			can[b][d]=new TCanvas(Form("c%i%i",b,d),"",1000,800);
			can[b][d]->Divide(4,3);
			for (int q = 0; q < Nq; q++)
			{
				can[b][d]->cd(q+1);
				hAcPosPol[b][q][d]->Draw();
				hAcNoPol[b][q][d]->Draw("same");
			

			}
		}
	}
	
}