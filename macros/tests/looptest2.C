

void looptest2(){
TFile *f1 = TFile::Open("~/clas/rootfiles/helicity.root");  
TTree *realt = (TTree*)f1->Get("mytree");

Int_t j=4;
 TCut c0="beam>3";
 realt->Draw("beam", Form('c%i',j));
}
