void teststuff(){


TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");


 TCanvas *c=new TCanvas("c","",1200,800);
 c->Divide(2,1);
 c->cd(1);
 TH1F *h2=new TH1F("h2","",60,1.1,1.7);
 newt->Draw("sqrt(mm2kpkp)>>h2");
 //c->cd(2);
c_2->Divide(1,2);
 c_2->cd(1);
 newt->Draw("beam");
c_2->cd(2);
 newt->Draw("run");




}
