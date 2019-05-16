/*
// should be similar to the g11 version

nov 17 2011: g12mplots.C made to be similar to g11mplots.C

cut on m(lambda+pim), then look at both mmkpkppim, and m(cas-pim)
cut on m(cas-pim), then look at mmkpkp and m(lam+pim)


1.32131 = cascade mass
1.11568 = lambda mass

*/
void g12mplots() {

  TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
  TTree *newt = (TTree*)f->Get("g12ana_v15");


  // determine cuts here and paste theese into g12asymmetry.C and g12angles.C
  //------------------------------------------COPY-------------------------------------------------- 
  

  TCut np="nphoton_nb2<6";
 

  TCut beam="beam>3.6";
  TCut st="abs(stv-scv)<1";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
  TCut vcut="abs(vz+90)<21&&(vx^2+vy^2)<8";
  TCut mybasic=beam&&st&&tof1&&tof2&&vcut;

  TCut casm="abs(mlampim-1.32131)<0.05";
  TCut lamm="abs(mcasmMpim - 1.11568) < 0.05";
  TCut cas="abs(sqrt(mm2kpkp)-1.32131)<0.02";
  TCut lam="abs(sqrt(mm2kpkppim)-1.11568)<0.03";

  TCut total=mybasic&&np&&casm&&lamm&&cas&&lam;

  //-------------------------------------------COPY----------------------------------------------

  //test
  //  newt->Draw("PIangle_ANA");

//*
 //===============plotting mass of cascade=(labda + pim)===================================
  TCanvas *c0=new TCanvas("c0","mlampim",1000,700);
  TH1F *h0=new TH1F("h0","m(lam + pim)",200,1.2,1.8);
  newt->Draw("mlampim>>h0",mybasic&&lamm);


  //==============ploting  mass of lambda=(cascade - pim) ==================
 
TCanvas *c1=new TCanvas("c1","mlampim",1000,700);
  TH1F *h1=new TH1F("h1","m(casm - pim)",200,0.5,1.5);
  newt->Draw("mcasmMpim>>h1",mybasic&&casm);


 
 //========================ploting mmmpmp=cascade mass===========================================
  TH1F *h2=new TH1F("h2","mmkpkp",100,1.2,2);
  TCanvas *c2=new TCanvas("c2","",1000,700);
  newt->Draw("sqrt(mm2kpkp)>>h2",mybasic&&np&&lam&&lamm);
  h2->Fit("gaus","fit","",1.30,1.34);
 
 

 //=========================ploting mmkpkppim=lambda mass======================================
  TH1F *h3=new TH1F("h3","mmkpkppim",100,0.5,1.5);
  TCanvas *c3=new TCanvas("c3","",1000,700);
  newt->Draw("sqrt(mm2kpkppim)>>h3",mybasic&&np&&cas&&casm);
  h3->Fit("gaus","fit","",1.08,1.17);

//*/









}
