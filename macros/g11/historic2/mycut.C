// jason bono, july 29 2011. 
// this was made after i fixed the bug in "finalsoultion.C" and the distributions looked right.
// this was made to help increase the signal to backround.


void mycut(){

TFile *_file0 = TFile::Open("new.root");
TH1F *h0=new TH1F("h0","",200,0.5,2.0);
TH1F *h1=new TH1F("h1","",200,0.5,2.0);
TH1F *h2=new TH1F("h2","",200,1.0,1.3);
 TH1F *h3=new TH1F("h3","",200,1.2,1.5);
TH1F *h4=new TH1F("h4","",200,1.0,1.3);
TH1F *h5=new TH1F("h5","",200,1.2,1.5);

/*
 //-----------the old------------------

 TCut cas="abs(sqrt(mm2kpkp)-1.322)<3*0.0077";
 TCut lambda="abs(sqrt(mm2kpkppim)-1.1162)<3*0.0088";

 TCut casm="abs(mlampim-1.3224)<3*0.004";
 TCut ks="abs(mkp1pim-0.892)<0.08";
 TCut ks2="abs(mkp2pim-0.892)<0.08";
 TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5";
 TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1";
 TCut st="abs(scv-stv)<1";
 TCut tof="abs(tofmasskp1-0.494)<0.07&&abs(tofmasskp2-0.494)<0.07";
 TCut vcut="abs(vz+10)<21&&(vx^2+vy^2)<8";
 TCut old=casm&&ks&&ks2&&sc&&sc2&&st&&tof&&vcut;

 TCanvas *c1=new TCanvas("c1","",1200,820);
 c1->Divide(2,0);
 c1->cd(1); 
 new->Draw("sqrt(mm2kpkppim)>>h0",old);
 c1->cd(2); 
 new->Draw("sqrt(mm2kpkp)>>h1",old);
*/





 //-----------the new------------------

 TCut mycas="abs(sqrt(mm2kpkp)-1.322)<0.04";
 TCut mylambda="abs(sqrt(mm2kpkppim)-1.1162)<0.035";

 TCut mycasm="abs(mlampim-1.3225)<0.0075"; //cut narrower
 TCut myks="abs(mkp1pim-0.82)<0.12"; //cut shift and wider
 TCut myks2="abs(mkp2pim-0.78)<0.09";// shift and made wider
 TCut mysc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.4"; //made narrower
 TCut mysc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<0.4"; //made much narrower
 TCut myst="abs((scv-stv)-0.025)<.325";// made much narrower
 TCut mytof="abs(tofmasskp1-0.494)<0.054&&abs(tofmasskp2-0.494)<0.054";// made narrower
 TCut myvcut="abs(vz+9.5)<19.5&&(vx^2+vy^2)<8";
 TCut mynew=mycasm&&myks&&myks2&&mysc&&mysc2&&myst&&mytof&&myvcut;

 TCanvas *c2=new TCanvas("c2","",1200,820);
 c2->Divide(2,0);
 c2->cd(1); 
 new->Draw("sqrt(mm2kpkppim)>>h2",mynew&&mycas,"E");
 c2->cd(2); 
 new->Draw("sqrt(mm2kpkp)>>h3",mynew&&mylambda,"E");



//-----------the newB------------------

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

 TCanvas *c3=new TCanvas("c3","",1200,820);
 c3->Divide(2,0);
 c3->cd(1); 
 new->Draw("sqrt(mm2kpkppim)>>h4",mynewB&&mycasB,"E");
 c3->cd(2); 
 new->Draw("sqrt(mm2kpkp)>>h5",mynewB&&mylambdaB,"E");



}


