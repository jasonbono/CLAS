void testhistcut(){

 TFile *f1 = TFile::Open("~/clas/rootfiles/helicity.root");
 TTree *realt = (TTree*)f1->Get("mytree");

 TH1F *h0=new TH1F("h0","",100,0,5);
 TH1F *h1=new TH1F("h1","",100,0,5);

 TCut bcut0="abs(beam-3)<1";
 realt->Draw("beam>>h0",bcut0);

TCanvas *c0=new TCanvas("c0","",500,300);

 h0->Draw("beam");



}
