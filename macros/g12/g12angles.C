

//nov 17 2011:  should be similar to the g11 version

void g12angles(){

 TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");

 TTree *newt = (TTree*)f->Get("g12ana_v15");



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
 TCut mynewB=myksB&&myks2B&&myscB&&mysc2B&&mystB&&mytofB&&myvcutB;




 TCanvas *c0=new TCanvas("c0","data cos(PIangle)",1000,700);
 TH1F *h0=new TH1F("h0","data cos(PIangle)",50,-1.1,1.1);
 newt->Draw("cos(PIangle)>>h0",mynewB&&mylambdaB&&mycasB&&mycasmB);



