
void testcut(){

 TFile *f1 = TFile::Open("~/clas/rootfiles/helicity.root");
 TTree *realt = (TTree*)f1->Get("mytree");


TCut beam[11];
 for (int i = 0; i < 11; i++) {
   Float_t beamcutVal = 2.79 + .1*i;
   beam[i] = Form("abs(beam-%.2f)<0.05", beamcutVal);
 }




 realt->Draw("beam",beam[3]);




}
