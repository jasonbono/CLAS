


void beamnorm(){


TFile *f1 = TFile::Open("~/clas/rootfiles/helicity.root");
TTree *realt = (TTree*)f1->Get("mytree");
TFile *f2 = TFile::Open("~/clas/rootfiles/helicitySIM.root");
TTree *simt = (TTree*)f2->Get("mytree");


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



TH1F *h1=new TH1F("h1","real",12,2.5,5.5);
TH1F *h2=new TH1F("h2","sim",12,2.5,5.5);

TCanvas *c0=new TCanvas("c0","",1200,820);
//c0->Divide(2,0);
//c0->cd(1); 
realt->Draw("beam>>h1",mycut);
//c0->cd(2);  
simt->Draw("beam>>h2",mycut,"SAME");
//c0->cd(0);

Double_t factor = h1->Integral("width") / h2->Integral("width");
h2->Scale(factor);
h2->Draw("SAME");
c0->Update();

TH1F *h3=new TH1F("h3","real cos(PIanglez)",50,-1.1,1.1);
TH1F *h4=new TH1F("h4","sim cos(PIanglez)",50,-1.1,1.1);
TCanvas *c1=new TCanvas("c1","",1200,820); 
c1->Divide(2,0);
c1->cd(1);
realt->Draw("cos(PIanglez)>>h3",mycut);
c1->cd(2);
simt->Draw("cos(PIanglez)>>h4",mycut);


Double_t factor2 = h3->Integral("width") / h4->Integral("width");
h4->Scale(factor2);
h4->Draw("SAME");
c1->Update();




}
