/*  jason bono, august 2 2011.

made to show results of "finalsoultion.C" while at jlab

*/

void display(){

  //TFile *f = TFile::Open("~/clas/rootfiles/newer.root");
TFile *f = TFile::Open("~/clas/rootfiles/beam.root");
//TFile *f = TFile::Open("~/clas/rootfiles/std.root");
//TFile *f = TFile::Open("~/clas/rootfiles/dbg.root");
TTree *newt = (TTree*)f->Get("mytree");


TH1F *h1=new TH1F("h1","pionangle",200,0,6);
TH1F *h2=new TH1F("h2","EpilCUT",200,0,6);
TH1F *h3=new TH1F("h3","Erestcas",200,0,6);

 
TCut mycasB="abs(sqrt(mm2kpkp)-1.322)<0.03";
TCut mylambdaB="abs(sqrt(mm2kpkppim)-1.1162)<0.03";

 TCut mycasmB="abs(mlampim-1.320)<0.03"; //cut narrower, shift wider
 TCut myksB="abs(mkp1pim-0.835)<0.165"; //cut shift and wider, shift wider
 TCut myks2B="abs(mkp2pim-0.758)<0.115";// shift and made wider, shift wider
 TCut myscB="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5"; //made narrower, wider
 TCut mysc2B="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<0.5"; //made much narrower, wider
 TCut mystB="abs((scv-stv)-0.0)<0.5";// made much narrower, totaly changed-- fixed error
 TCut mytofB="abs(tofmasskp1-0.5)<0.15&&abs(tofmasskp2-0.5)<0.15";//made narrower, fixed
 TCut myvcutB="abs(vz+9.0)<21&&(vx^2+vy^2)<9";//??,fixed
 TCut mynewB=mycasmB&&myksB&&myks2B&&myscB&&mysc2B&&mystB&&mytofB&&myvcutB;
 TCut mycut=mynewB&&mycasB&&mylambdaB;

 //TCanvas *c1=new TCanvas("c1","",1200,820);
 //c1->Divide(2,0);
 //c1->cd(1);
 //new->Draw("PIangle",mycut);
 //c1->cd(2);
newt->Draw("cos(PIangle)",mycut);


}
