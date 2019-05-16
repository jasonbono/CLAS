



g12ana_v15->Draw("sqrt(mm2kpkppim)>>h1",np&&vcut&&beam&&tof1&&tof2&&"np<2&&npip<1&&nkm<1"&&casm&&st);



void g12angles(){
TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");

//-------------------------------------------------------------------------------
  

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





  //----------------------------------------------------------------------------


 TH1F *h2=new TH1F("h2","",100,1.2,1.4) ;
 g12ana_v15->Draw("sqrt(mm2kpkp)>>h2",np&&vcut&&beam&&tof1&&tof2&&"np<2&&npip<1&&nkm<1"&&lamm2&&st);
 g12ana_v15->Draw("sqrt(mm2kpkp)>>h2",newbasic&&lamm);
 h2->Draw("E");
 h2->Rebin(2);
 h2->GetBinWidth(1); // the semi col makes the root NOT return the value!
 h2->GetYaxis()->SetTitle("Event/4MeV/c^{2}");
 h2->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 gStyle->SetOptStat(0);
 // c1->Print("test.eps")

   //note: can also use latex notation by using  h2->GetYaxis()->SetTitle("#Lambda") for example.


   .L ~/clas/macros/g11/fitGAUS.C;
 fitGAUS(h2,1,1.25,1.4,1,1,1,1.32,0.01,3);

 



 //=========================================MMCASCADE===================================================================
///// accualy want binning to be aprox 10 mev so do this=================================================================
TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");

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

 TH1F *h2=new TH1F("h2","",100,1.2,1.4) ;
 newt->Draw("sqrt(mm2kpkp)>>h2",newbasic&&lamm);
 h2->Draw("E");
 h2->Rebin(5);
 h2->GetBinWidth(1); // the semi col makes the root NOT return the value!
 h2->GetYaxis()->SetTitle("Event/10MeV/c^{2}");  //this depends on the get bin width
 h2->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 gStyle->SetOptStat(0);
 //c1->Print("test.eps")


 .L ~/clas/scripts/fit2GAUS.C; // be carefule here too the semi col also dosenot alow the file to be found
 fitGAUS(h2,1,1.2,1.4,1,1,0,1.32,0.01,3); // he programed that if you set a parameter to zero then it will stay zero. so i set the quadratic term to zero to get a linear fit on the backround.

 // now for another plot

//=========================================MMLAMBDA===================================================================

TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");

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

 TH1F *h1=new TH1F("h1","",100,1.05,1.25) ;
 newt->Draw("sqrt(mm2kpkppim)>>h1",newbasic&&lamm);
 h1->Draw("E");
 h1->Rebin(5);
 h1->GetBinWidth(1); // the semi col makes the root NOT return the value!
 h1->GetYaxis()->SetTitle("Event/10MeV/c^{2}");  //this depends on the get bin width
 h1->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 gStyle->SetOptStat(0);
 //c1->Print("~/clas/pics/2011_11_18/whateverfile.eps")


 .L ~/clas/scripts/fit2GAUS.C; // be carefule here too the semi col also dosenot alow the file to be found
 fitGAUS(h1,1,1.05,1.25,1,1,0,1.116,0.01,3);





  }
