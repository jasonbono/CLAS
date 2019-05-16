//lambdaplot.C


void lambdaplot(){

TFile *_file0 = TFile::Open("new.root");
//TH1F *h2=new TH1F("h2","",200,1.0,1.4);
 TH1F *h2=new TH1F("h2","",300,1.0,2.0);

TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5";
TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1";
TCut ks="abs(mkp1pim-0.892)<0.08";
TCut st="abs(scv-stv)<1";
TCut vcut="abs(vz+10)<21&&(vx^2+vy^2)<8";


TCut dd="abs(sqrt(mm2kpkp)-1.32)<0.02";
new->Draw("sqrt(mm2kpkppim)>>h2", sc&&sc2&&dd);
//new->Draw("sqrt(mm2kpkppim)>>h2");
//200 bins and 400 mev so 400/200= 2 mev/bin 



}
