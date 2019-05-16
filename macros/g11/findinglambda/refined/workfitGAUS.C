// aug 1 2011->>> i edited this file to use the "mynewB" cuts and optimised to run
// fit3GAUS.C.  i used 3.0 as the "factor" because that is what lei did but
// i am not sure if this is the best thing to do.

// to run this type in root:
// .L fit3GAUS.C 
// .x workfitGAUS.C

//----------------------------

// jason bono
// choose lambda or cascade from below then type in root
// .L fitGAUS.C
// .x workfitGAUS.C
// should fit and give yeilds




void workfitGAUS(){

  //TFile *_file0 = TFile::Open("new.root");
TFile *_file0 = TFile::Open("~/clas/rootfiles/g11/nxyzREAL.root");


// .L fitGAUS.C;

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

 TCanvas *c1=new TCanvas("c1","",1200,820);
 c1->Divide(2,0);


 //lambda
//*
c1->cd(1); 
TH1F *h1=new TH1F("h1","mmkpkppim",100,1.0,1.3);
new->Draw("sqrt(mm2kpkppim)>>h1",mynewB&&mycasB);
fitGAUS(h1,1,1.05,1.2,5,1,1,1.1162,0.01,3);
// */


//cascade
//*
 c1->cd(2); 
TH1F *h2=new TH1F("h2","mmkpkp",100,1.2,1.5);
new->Draw("sqrt(mm2kpkp)>>h2",mynewB&&mylambdaB);
 fitGAUS(h2,1,1.25,1.4,1,1,1,1.322,0.01,3);
 // */

   }
