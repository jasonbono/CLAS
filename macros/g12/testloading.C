void teststuff(){


TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");

 gROOT->ProcessLine(".L ~/clas/scripts/myfit2gaus.C");



TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
 TCut beam="beam>3.6"; 
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;
 
 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lam







 TH1F *h2=new TH1F("h2","",60,1.1,1.7);
 newt->Draw("sqrt(mm2kpkp)>>h2",newbasic&&lamm);
 h2->Draw("E");
 // h2->Rebin(5);
 // h2->GetBinWidth(1); // the semi col makes the root NOT return the value!
 h2->GetYaxis()->SetTitle("Event/10MeV/c^{2}");  //this depends on the get bin width
 h2->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 // gStyle->SetOptStat(0);
 //c1->Print("test.eps")



 fitGAUS(h2,1,1.1,1.7,1,1,0,1.32,0.01,3); 






}
