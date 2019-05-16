#include <fstream>
using namespace std;


AnalyzeTxt()
{
	
	TString DataType = "MC";
	TFile* fHistos = new TFile(Form("./%s_SCinfo.root",DataType),"RECREATE");
	//TFile* fHistos = new TFile("./SCinfo.root","RECREATE");
	ifstream In("text.txt");
	TString txt1, prevtxt;

	const Int_t Ns = 6;
	TH2F *h2d = new TH2F("h2d","",60,0,60,6,1,7);
	TH1F *hSec[Ns];
	for (int s=0; s<Ns; s++)
	{
		hSec[s] = new TH1F(Form("hSec%i",s),"",60,0,60);
	}
	int x;
	int sector;
	int id;
	while(!In.eof()){
		In >> txt1 >> x;
		if(txt1 == "Sector:") {
			sector = x;
			id = 999;
		}
		if(txt1 == "ID:") {
			id = x;
		}
		if(id == 999) continue;
		cout << sector << " " <<  id << endl;
		hSec[sector - 1]->Fill(id);
		h2d->Fill(id,sector,1);
		}
	
	TCanvas *c2d = new TCanvas("c2d","c2d",1000,800);
	h2d->Draw("Colz");
	h2d->Write();
	TCanvas *cSec = new TCanvas("cSec","cSec",1000,800);
	cSec->Divide(2,3);
	for (int s=0; s<Ns; s++)
	{
		cSec->cd(s+1);
		hSec[s]->Draw();
	}

}