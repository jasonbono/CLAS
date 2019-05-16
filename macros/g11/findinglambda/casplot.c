// to find the cascade peak and show on jun 29 2011 at first g12 meeting

void casplot(){

  TFile *_file0 = TFile::Open("new.root");
  TH1F *h2=new TH1F("h2","",300,1.0,2.0);
  
//some cuts
  TCut sc="abs(sctkp1-sclkp1/(betakp1*29.99)-scv)<0.5";
  TCut sc2="abs(sctkp2-sclkp2/(betakp2*29.99)-scv)<1";
  TCut st="abs(scv-stv)<1";
  //NOW TO CUT ON LAMBDA
  TCut ll="abs(sqrt(mm2kpkppim)-1.12)<0.02";

  new->Draw("sqrt(mm2kpkp)>>h2",sc&&sc2&&st&&ll);

  //this has 300 bins over 1000 Mev so 1000/300= 3.333 mev/bin
}
