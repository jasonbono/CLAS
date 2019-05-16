


void findcascade(){
  

  TFile *_file0 = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");



  TCut beam="beam>3.639";
  TCut st="abs(stv-scv)<1";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1";
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<1";
  TCut vcut="abs(vz+90)<21&&(vx^2+vy^2)<8";

  TCut mybasic=beam&&st&&tof1&&tof2&&vcut;

  TCut cas="abs(sqrt(mm2kpkp)-1.32)<0.01";
  TCut lam="abs(sqrt(mm2kpkppim)-1.1162)<0.01";

  TCut np="nphoton_nb2<3";  // doesnt do much


  TH1F *h0=new TH1F("h0","",100,1.2,2);
 TH1F *h1=new TH1F("h1","",100,0.5,1.5);

TCanvas *c0=new TCanvas("c0","",800,420);
 c0->Divide(2,1);
 c0->cd(1);
 g12ana_v14->Draw("sqrt(mm2kpkp)>>h0",mybasic&&lam);
  h0->Fit("gaus","fit","",1.30,1.34);
   c0->cd(2);
 g12ana_v14->Draw("sqrt(mm2kpkppim)>>h1",mybasic&&cas);
 h1->Fit("gaus","fit","",1.08,1.17);



 TCanvas *c1=new TCanvas("c1","",800,420);
 c1->Divide(2,1);
 c1->cd(1);
 g12ana_v14->Draw("sqrt(mm2kpkp)>>h0",mybasic&&lam);
 h0->Fit("gaus","fit","",1.30,1.34);
 c1->cd(2);
 g12ana_v14->Draw("sqrt(mm2kpkppim)>>h1",mybasic&&cas);
 h1->Fit("gaus","fit","",1.08,1.17);




}
