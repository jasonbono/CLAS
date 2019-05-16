


void surfaceplots(){

  //TFile *_file0 = TFile::Open("../../rootfiles/g12/g12ana_v07_2.root");
TFile *_file0 = TFile::Open("../../rootfiles/g12/g12ana_v07_3.root");


  TCut beam="beam>3.6";
  TCut st="abs(stv-scv)<1";
  TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<2";
  TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<1";
  TCut vcut="abs(vz+90)<21&&(vx^2+vy^2)<8";
  TCut mybasic=beam&&st&&tof1&&tof2&&vcut;
  TCut cas="abs(sqrt(mm2kpkp)-1.32)<0.02";
  TCut lam="abs(sqrt(mm2kpkppim)-1.1162)<0.03";




  //TH1F *h=new TH1F("h", "", 100, 0,3);
  //  g12ana_v07->Draw("sqrt(mm2kpkp)>>h",mybasic);
  //  g12ana_v07->Draw("mm3pi>>h",mybasic);


  //*********************the 3 particle missing masses**********************
TCanvas *c_3p=new  TCanvas("c_3p","",1200,820);
 c_3p->Divide(2,2);

 c_3p->cd(1);
 TH2F *s0=new TH2F("s0","mm3pi:sqrt(mm2kpkppim)",100,0,2,100,0,2.5);
 g12ana_v07_2->Draw("mm3pi:sqrt(mm2kpkppim)>>s0",mybasic,"CONT");

 c_3p->cd(2);
 TH2F *s1=new TH2F("s1","mmkp1pippim:sqrt(mm2kpkppim)",100,0,2,100,0,2.5);
 g12ana_v07_2->Draw("mmkp1pippim:sqrt(mm2kpkppim)>>s1",mybasic,"CONT");

 c_3p->cd(3);
 TH2F *s2=new TH2F("s2","mmkp2pippim:sqrt(mm2kpkppim)",100,0,2,100,0,2.5);
 g12ana_v07_2->Draw("mmkp2pippim:sqrt(mm2kpkppim)>>s2",mybasic,"CONT");


 //************************the 2 particle missing masses**********************
 TCanvas *c_2p=new  TCanvas("c_2p","",1200,820);
 c_2p->Divide(2,2);

 c_2p->cd(1);
 TH2F *s0=new TH2F("s0","2pip:sqrt(mm2kpkp)",100,0.5,2.5,100,0,2.5);
 g12ana_v07_2->Draw("2pip:sqrt(mm2kpkp)>>s0",mybasic,"CONT");

 c_2p->cd(2);
 TH2F *s1=new TH2F("s1","mmkp1pip:sqrt(mm2kpkp)",100,0.5,2.5,100,0,2.5);
 g12ana_v07_2->Draw("mmkp1pip:sqrt(mm2kpkp)>>s1",mybasic,"CONT");

 c_2p->cd(3);
 TH2F *s2=new TH2F("s2","mmkp2pip:sqrt(mm2kpkp)",100,0.5,2.5,100,0,2.5);
 g12ana_v07_2->Draw("mmkp2pip:sqrt(mm2kpkp)>>s2",mybasic,"CONT");

//************************the 1 particle missing masses vs missing mass of kpkppim**************

TCanvas *c_1p=new  TCanvas("c_1p","",1200,820);
 c_1p->Divide(2,2);

 c_1p->cd(1);
 TH2F *s0=new TH2F("s0","mmkp1:sqrt(mm2kpkppim)",100,0,2,100,1.5,3.5);
 g12ana_v07_2->Draw("mmkp1:sqrt(mm2kpkppim)>>s0",mybasic,"CONT");

 c_1p->cd(2);
 TH2F *s1=new TH2F("s1","mmkp2:sqrt(mm2kpkppim)",100,0,2,100,1.5,3.5);
 g12ana_v07_2->Draw("mmkp2:sqrt(mm2kpkppim)>>s1",mybasic,"CONT");

 c_1p->cd(3);
 TH2F *s2=new TH2F("s2","mmpip1:sqrt(mm2kpkppim)",100,0,2,100,1.5,3.5);
 g12ana_v07_2->Draw("mmpip1:sqrt(mm2kpkppim)>>s2",mybasic,"CONT");

 c_1p->cd(4);
 TH2F *s3=new TH2F("s3","mmpip2:sqrt(mm2kpkppim)",100,0,2,100,1.5,3.5);
 g12ana_v07_2->Draw("mmpip2:sqrt(mm2kpkppim)>>s2",mybasic,"CONT");




//************************the 1 particle missing masses vs missing mass of kpkp**************

TCanvas *c_1pb=new  TCanvas("c_1pb","",1200,820);
 c_1pb->Divide(2,2);

 c_1pb->cd(1);
 TH2F *s0=new TH2F("s0","mmkp1:sqrt(mm2kpkp)",100,0,2.5,100,1.5,3.5);
 g12ana_v07_2->Draw("mmkp1:sqrt(mm2kpkppim)>>s0",mybasic,"CONT");

 c_1pb->cd(2);
 TH2F *s1=new TH2F("s1","mmkp2:sqrt(mm2kpkp)",100,0,2.5,100,1.5,3.5);
 g12ana_v07_2->Draw("mmkp2:sqrt(mm2kpkp)>>s1",mybasic,"CONT");

 c_1pb->cd(3);
 TH2F *s2=new TH2F("s2","mmpip1:sqrt(mm2kpkp)",100,0,2.5,100,1.5,3.5);
 g12ana_v07_2->Draw("mmpip1:sqrt(mm2kpkp)>>s2",mybasic,"CONT");

 c_1pb->cd(4);
 TH2F *s3=new TH2F("s3","mmpip2:sqrt(mm2kpkp)",100,0,2.5,100,1.5,3.5);
 g12ana_v07_2->Draw("mmpip2:sqrt(mm2kpkp)>>s2",mybasic,"CONT");



}
