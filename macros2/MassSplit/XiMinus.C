

/*
october 1 2013:

requre a proton in the final state
*/


void XiMinus()
{
	TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/2kppim-v05-Basic.root");
	TTree *tData = (TTree*)fData->Get("v05");
	
	TCut proton = "np == 1";
	
	TCanvas *cmm=new TCanvas("cmm","cmm",1000,800);
	cmm->Divide(2,2);
	cmm->cd(1);
	TH1F *hma=new TH1F("hma","hma",300,1,2.5);
	tData->Draw("mmkpkppim>>hma",proton);
	cmm->cd(2);
	TH1F *hmb=new TH1F("hmb","hmb",300,1,2.5);
	tData->Draw("mmkpkppim>>hmb",!proton);
	cmm->cd(3);
	TH1F *hmc=new TH1F("hmc","hmc",300,1,2.5);
	tData->Draw("mmkpkp>>hmc",proton);
	cmm->cd(4);	
	TH1F *hmd=new TH1F("hmd","hmd",300,1,2.5);
	tData->Draw("mmkpkp>>hmd",!proton);
}