

void cometest()
{
	
	
	TFile *f = TFile::Open("~/clas/rootfiles/g12/newbasic/v37k_full_newbasic.root");
	TTree *newt = (TTree*)f->Get("v37k_newbasic");
	
	TH1F *hist=new TH1F("hist","",100,2,6);	
	TCanvas *can=new TCanvas("can","",1500,800);

	can->Divide(2,0);
	can->cd(1);
	newt->Draw("beam>>hist");
	hist->Draw("SAME");
	
	can->cd(2);
	TLatex *sum=new TLatex(4, 1000,"eric IS a micro penis");
	//sum->Draw();
	hist->Draw();
	sum->Draw("same");
}