/*
jason bono, july 20 2011
made to examine cuts to get good lambda peak.
*/

void correlationslambda(){

TFile *_file0 = TFile::Open("new.root");

TCut cas="abs(sqrt(mm2kpkp)-1.322)<3*0.0077";
TCut lambda="abs(sqrt(mm2kpkppim)-1.1162)<3*0.0088";


/*
//below works for lambVsc
TH2F *h1=new TH2F("h1","",100,-2,2,100,0.4,1.7);
 new->Draw("sqrt(mm2kpkppim):sctkp1-sclkp1/(betakp1*29.99)-scv>>h1",cas,"CONT");
  h1->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
  h1->GetXaxis()->SetTitle("sctkp1-sclkp1/(betakp1*29.99)-scv");
//*/

/*
//lambmassVsc2
TH2F *h2=new TH2F("h2","",100,-1.5,1.5,100,0.9,1.2);
new->Draw("sqrt(mm2kpkppim):sctkp2-sclkp2/(betakp2*29.99)-scv>>h2",cas,"CONT");
h2->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h2->GetXaxis()->SetTitle("sctkp2-sclkp2/(betakp2*29.99)-scv");
//*/

/*
//lambmassVks
TH2F *h3=new TH2F("h3","",100,0.65,1.1,100,0.85,1.18);
new->Draw("sqrt(mm2kpkppim):mkp1pim>>h3",cas,"CONT");
h3->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h3->GetXaxis()->SetTitle("mkp1pim");
//*/

/*
//lambmassVst
TH2F *h4=new TH2F("h4","",100,-2.5,1,100,0.85,1.18);
new->Draw("sqrt(mm2kpkppim):scv-stv>>h4",cas,"CONT");
h4->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h4->GetXaxis()->SetTitle("scv-stv");
//*/

/*
//lambmassVvz
TH2F *h5=new TH2F("h5","",100,-33,12,100,1,1.18);
new->Draw("sqrt(mm2kpkppim):vz>>h5",cas,"CONT");
h5->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h5->GetXaxis()->SetTitle("vz");
//*/


/*
//lambmassVvrad
TH2F *h6=new TH2F("h6","",100,-1,10,100,1,1.16);
 new->Draw("sqrt(mm2kpkppim):vx^2+vy^2>>h6",cas,"CONT");
h6->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h6->GetXaxis()->SetTitle("vx^2+vy^2");
//*/

/*
//lambmassVks2
TH2F *h7=new TH2F("h7","",100,0.6,1,100,1.06,1.16);
 new->Draw("sqrt(mm2kpkppim):mkp2pim>>h7",cas,"CONT");
h7->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h7->GetXaxis()->SetTitle("mkp2pim");
//*/

/*
//lambmassVcasm
TH2F *h8=new TH2F("h8","",100,1.25,1.4,100,1.06,1.16);
 new->Draw("sqrt(mm2kpkppim):mlampim>>h8",cas,"CONT");
h8->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h8->GetXaxis()->SetTitle("mlampim");
//*/

/*
//lambmassVtofk1
TH2F *h9=new TH2F("h9","",100,0.3,0.7,100,1.09,1.15);
 new->Draw("sqrt(mm2kpkppim):tofmasskp1>>h9",cas,"CONT");
h9->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
h9->GetXaxis()->SetTitle("tofmasskp1");
//*/

/*
//lambmassVtofk2
TH2F *h10=new TH2F("h10","",100,0.3,0.7,100,1.09,1.15);
new->Draw("sqrt(mm2kpkppim):tofmasskp2>>h10",cas,"CONT");
h10->GetYaxis()->SetTitle("sqrt(mm2kpkppim)");
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
