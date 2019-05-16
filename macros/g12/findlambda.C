
void findlambda(){
  

  TFile *_file0 = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");

  TCut Ccas="abs(sqrt(mm2kpkp)-1.322)<0.04";
  TCut Cst="abs((scv-stv))<0.5";
  TCut Csc1="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5"; 
  TCut Csc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<0.5"; 
 



 // TCut casm="abs(mlampim-1.3225)<0.0075"; //cut narrower
 // TCut ks="abs(mkp1pim-0.82)<0.12"; //cut shift and wider
 // TCut ks2="abs(mkp2pim-0.78)<0.09";// shift and made wider
 // TCut mysc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.4"; //made narrower
 // TCut mysc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<0.4"; //made much narrower
 // TCut myst="abs((scv-stv)-0.025)<.325";// made much narrower
 // TCut mytof="abs(tofmasskp1-0.494)<0.054&&abs(tofmasskp2-0.494)<0.054";// made narrower
 // TCut myvcut="abs(vz+9.5)<19.5&&(vx^2+vy^2)<8";
 //  TCut mynew=mycasm&&myks&&myks2&&mysc&&mysc2&&myst&&mytof&&myvcut;

  //=========================lambda ploting====================================
  TH1F *hlamb0=new TH1F("hlamb0","",50,0.0,2.0);
  TH1F *hlamb1=new TH1F("hlamb1","",50,0.0,2.0);
  TH1F *hlamb2=new TH1F("hlamb2","",50,0.0,2.0);
  TH1F *hlamb3=new TH1F("hlamb3","",50,0.0,2.0);
  
  TCanvas *c0=new TCanvas("c0","",1200,820);
  c0->Divide(2,2);
  c0->cd(1);
  g12ana_v07->Draw("sqrt(mm2kpkppim)>>hlamb0");
  c0->cd(2); 
  g12ana_v07->Draw("sqrt(mm2kpkppim)>>hlamb1",Cst);
  c0->cd(3); 
  g12ana_v07->Draw("sqrt(mm2kpkppim)>>hlamb2",Ccas);
  c0->cd(4);
  g12ana_v07->Draw("sqrt(mm2kpkppim)>>hlamb3",Ccas&&Cst&&Csc1&&Csc2);
  //=============================================================



  //=========================cascade ploting====================================
  TH1F *hcas0=new TH1F("hcas0","",50,0.0,2.0);
  TH1F *hcas1=new TH1F("hcas1","",50,0.0,2.0);
  TH1F *hcas2=new TH1F("hcas2","",50,0.0,2.0);
  TH1F *hcas3=new TH1F("hcas3","",50,0.0,2.0);
  
  TCanvas *c1=new TCanvas("c1","",1200,820);
  c1->Divide(2,2);
  c1->cd(1);
  g12ana_v07->Draw("sqrt(mm2kpkp)>>hcas0");
  c1->cd(2); 
  g12ana_v07->Draw("sqrt(mm2kpkp)>>hcas1",Cst&&Csc1&&Csc2);
  c1->cd(3); 
  g12ana_v07->Draw("sqrt(mm2kpkp)>>hcas2",Clamb);
  c1->cd(4);
  g12ana_v07->Draw("sqrt(mm2kpkp)>>hcas3",Clamb&&Cst&&Csc1&&Csc2);
  //=============================================================


  //=========================showing some timing hists===================
  
  TH1F *htime0=new TH1F("htime0","",200,-6.0,6.0);
  TH1F *htime1=new TH1F("htime1","",200,-6.0,6.0);
  TH1F *htime2=new TH1F("htime2","",200,-6.0,6.0);
  TH1F *htime3=new TH1F("htime3","",200,-6.0,6.0);
  TH1F *htime4=new TH1F("htime4","",200,-6.0,6.0);
  TH1F *htime5=new TH1F("htime5","",200,-6.0,6.0);
  
  TCanvas *c2=new TCanvas("c2","",1200,820);
  c2->Divide(3,2);

  c2->cd(1);
  g12ana_v07->Draw("scv - stv>>htime0");
  c2->cd(4);
  g12ana_v07->Draw("scv - stv>>htime1",Cst);

  c2->cd(2);
  g12ana_v07->Draw("(sctkp1-sclkp1/(betakp1*29.99)-scv)>>htime2");
  c2->cd(5);
  g12ana_v07->Draw("(sctkp1-sclkp1/(betakp1*29.99)-scv)>>htime3",Csc1);

  c2->cd(3);
  g12ana_v07->Draw("(sctkp2-sclkp2/(betakp2*29.99)-scv)>>htime4");
  c2->cd(6);
  g12ana_v07->Draw("(sctkp2-sclkp2/(betakp2*29.99)-scv)>>htime5",Csc2);





}
