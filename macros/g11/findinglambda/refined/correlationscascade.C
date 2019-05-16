/*
jason bono, july 20 2011
made to examine cuts to get good cascade peak.
*/

void correlationscascade(){

TFile *_file0 = TFile::Open("new.root");

TCut cas="abs(sqrt(mm2kpkp)-1.322)<3*0.0077";
TCut lambda="abs(sqrt(mm2kpkppim)-1.1162)<3*0.0088";


/*
//below works for casmassVsc
TH2F *h1=new TH2F("h1","",100,-2,2,100,1.3,1.4);
 new->Draw("sqrt(mm2kpkp):sctkp1-sclkp1/(betakp1*29.99)-scv>>h1",lambda,"CONT");
  h1->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
  h1->GetXaxis()->SetTitle("sctkp1-sclkp1/(betakp1*29.99)-scv");
//*/

/*
//casmassVsc2
TH2F *h2=new TH2F("h2","",100,-1.5,1.5,100,1.3,1.4);
new->Draw("sqrt(mm2kpkp):sctkp2-sclkp2/(betakp2*29.99)-scv>>h2",lambda,"CONT");
h2->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h2->GetXaxis()->SetTitle("sctkp2-sclkp2/(betakp2*29.99)-scv");
//*/

/*
//casmassVks
TH2F *h3=new TH2F("h3","",100,0.65,1.1,100,1.3,1.4);
new->Draw("sqrt(mm2kpkp):mkp1pim>>h3",lambda,"CONT");
h3->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h3->GetXaxis()->SetTitle("mkp1pim");
//*/

/*
//casssVst
 TH2F *h4=new TH2F("h4","",100,-2.5,0.55,100,1.3,1.4);
new->Draw("sqrt(mm2kpkp):scv-stv>>h4",lambda,"CONT");
h4->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h4->GetXaxis()->SetTitle("scv-stv");
//*/

/*
//casmassVvz
TH2F *h5=new TH2F("h5","",100,-33,14,100,1.3,1.4);
new->Draw("sqrt(mm2kpkp):vz>>h5",lambda,"CONT");
h5->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h5->GetXaxis()->SetTitle("vz");
//*/


/*
//casmassVvrad
TH2F *h6=new TH2F("h6","",100,-1,10,100,1.3,1.38);
 new->Draw("sqrt(mm2kpkp):vx^2+vy^2>>h6",lambda,"CONT");
h6->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h6->GetXaxis()->SetTitle("vx^2+vy^2");
//*/

/*
//casmassVks2
TH2F *h7=new TH2F("h7","",100,0.6,1,100,1.3,1.4);
 new->Draw("sqrt(mm2kpkp):mkp2pim>>h7",lambda,"CONT");
h7->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h7->GetXaxis()->SetTitle("mkp2pim");
//*/

/*
//casmassVcasm
TH2F *h8=new TH2F("h8","",100,1.28,1.38,100,1.3,1.38);
new->Draw("sqrt(mm2kpkp):mlampim>>h8",lambda,"CONT");
h8->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h8->GetXaxis()->SetTitle("mlampim");
//*/

/*
//casmassVtofk1
TH2F *h9=new TH2F("h9","",100,0.3,0.7,100,1.3,1.4);
new->Draw("sqrt(mm2kpkp):tofmasskp1>>h9",lambda,"CONT");
h9->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h9->GetXaxis()->SetTitle("tofmasskp1");
//*/

/*
//casmassVtofk2
TH2F *h10=new TH2F("h10","",100,0.3,0.7,100,1.3,1.4);
new->Draw("sqrt(mm2kpkp):tofmasskp2>>h10",lambda,"CONT");
h10->GetYaxis()->SetTitle("sqrt(mm2kpkp)");
h10->GetXaxis()->SetTitle("tofmasskp2");
//*/



 TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5";
 TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1";
 TCut ks="abs(mkp1pim-0.892)<0.08";
 TCut st="abs(scv-stv)<1";
 TCut vcut="abs(vz+10)<21&&(vx^2+vy^2)<8";
 //TCut vout="(vx^2+vy^2)>8";///BAD FOR CASCADE PLOTING!
 TCut ks2="abs(mkp2pim-0.892)<0.08";
 TCut casm="abs(mlampim-1.3224)<3*0.004";
 TCut tof="abs(tofmasskp1-0.494)<0.07&&abs(tofmasskp2-0.494)<0.07";
}
