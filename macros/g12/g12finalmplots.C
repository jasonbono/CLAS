

void g12finalmplots(){
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
//TTree *newt = (TTree*)f->Get("g12ana_v15");
TFile *f = TFile::Open("~/clas/rootfiles/g12/large/g12ana_v16_58090.root");
TTree *newt = (TTree*)f->Get("g12ana_v16");

gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS3.C");


//============= this is from leis_beautify.C which i changed a bit========================
//===============this is the final configuration that he used in his paper========
printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.85);  //this: Xoff
 gStyle->SetTitleYOffset(0.75);  //this:  Yoff
 gStyle->SetTitleSize(0.07);  //this:    Xsize   
 gStyle->SetTitleYSize(0.07); //this     Ysize
 //gStyle->SetLabelFont(72);
 gStyle->SetPadLeftMargin(0.11);   // this: Yaxis 
 gStyle->SetPadBottomMargin(0.15);  // this: Xaxis
 gStyle->SetPadTopMargin(0.02); // was 0.02
 gStyle->SetCanvasBorderMode(1);
 gStyle->SetPadBorderMode(1);
 gStyle->SetFrameBorderMode(0);
 gStyle->SetPadColor(0);
 gStyle->SetCanvasColor(0);
 gStyle->SetFrameFillColor(0);
 gStyle->SetFrameFillStyle(1001);
 gStyle->SetFrameFillStyle(0);
 gStyle->SetFillStyle(0);
 gStyle->SetOptStat(0);
//====================================================================



//=========================cuts version1========================
/* 
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
 TCut ="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
//*///============================================================================


//=========================the most recent cuts as of nov22========================
//need to relax a few cuts here after showing lei my overlay plots.
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<30&&sqrt(vx^2+vy^2)<7";  // relaxed this alot to allow for weak decays
 TCut beam="beam>3.3"; //relaxed this from 3.6
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1";  // this is relaxed because the slower particle has a lower time resoultion.
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;
 
 //theese are best defined in this part of the code to prevent discrepenceys when changing cuts in geometry.
TCut allbut_vz=n&&np&&"sqrt(vx^2+vy^2)<7"&&beam&&st&&tof1&&tof2;
TCut allbut_vr=n&&np&&"abs(vz+90)<30"&&beam&&st&&tof1&&tof2;

 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
 //----------------------------------------------------------------------------------



 //====================================MMCASCADE================================


 //*
 TCanvas *c0=new TCanvas("c0","",1200,800);
 TH1F *h0=new TH1F("h0","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>h0",newbasic&&lamm);

 // h2->Draw("E");
 h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 fitGAUS3(h0,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);




 TCanvas *c0b=new TCanvas("c0b","",1200,800);
 TH1F *h0b=new TH1F("h0b","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>h0b",newbasic&&lam);

 // h2->Draw("E");
 h0b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0b->GetXaxis()->SetTitle("(cut on MMlam) MM(K^{+}K^{+}) (GeV/c^{2})");   
 fitGAUS3(h0b,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);




 // c0->Print("~/clas/pics/11_nov11/proposal/g12/mmkpkp.eps");

 //*/

 //--------------------------------------------------------------------------------------






//=========================================MMLAMBDA=============================================


//*

 TCanvas *c1=new TCanvas("c1","",1200,800);
 // TH1F *hlam=new TH1F("hlam","",37, 0.90795,1.3131);
 TH1F *h1=new TH1F("h1","",37,0.90795,1.3131);
 newt->Draw("sqrt(mm2kpkppim)>>h1",newbasic&&casm);
 // h1->Draw("E");
  h1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
  h1->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");   
  fitGAUS3(h1,1,0.9,1.3,1,1,0,1.116,0.01,3,0,0,0);



 TCanvas *c1b=new TCanvas("c1b","",1200,800);
 TH1F *h1b=new TH1F("h1b","",37,0.90795,1.3131);
 newt->Draw("sqrt(mm2kpkppim)>>h1b",newbasic&&cas);
 // h1->Draw("E");
  h1b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
  h1b->GetXaxis()->SetTitle(" (cut on MMcas) MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");   
  fitGAUS3(h1b,1,0.9,1.3,1,1,0,1.116,0.01,3,0,0,0);



  //   c1->Print("~/clas/pics/11_nov11/proposal/g12/mmkpkppim.eps");

  //*/

//--------------------------------------------------------------------------------------


// below is not being used right now: will need to fix up========================================================================================================================================================================================================================================================================================


//====================================mcascade================================


//*
TCut lam2="abs(sqrt(mm2kpkppim)-1.116)<0.01";

 TCanvas *c2=new TCanvas("c2","",1200,800);
 TH1F *h2=new TH1F("h2","",40,1.1,1.5);
 newt->Draw("mlampim>>h2",newbasic&&lamm);
 h2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h2->GetXaxis()->SetTitle("M(#Xi^{-}#pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h2,1,1.27,1.5,1,1,0,1.32,0.02,3,0.0,0.0,0.0);

 TCanvas *c2b=new TCanvas("c2b","",1200,800);
 TH1F *h2b=new TH1F("h2b","",40,1.1,1.5);
 newt->Draw("mlampim>>h2b",newbasic&&lam);
 h2b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h2b->GetXaxis()->SetTitle(" (cut on (MMlam)) M(#Xi^{-}#pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h2b,1,1.27,1.5,1,1,0,1.32,0.02,3,0.0,0.0,0.0);


 // c2->Print("~/clas/pics/11_nov11/proposal/mlampim.eps");
 //*/
//-----------------------------------------------------------------------


 //==================================mlambda==================================
 //*
TCut cas2="abs(sqrt(mm2kpkp) - 1.321)<0.017";


 TCanvas *c3=new TCanvas("c3","",1200,800);
 TH1F *h3=new TH1F("h3","", 37, 0.90795,1.3131);
 newt->Draw("mcasmMpim>>h3",newbasic&&casm);
 h3->Draw("E");
 h3->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h3->GetXaxis()->SetTitle("M(#Lambda^{0} - #pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h3,1,0.09,1.15,1,1,0,1.116,0.02,3,0.0,0.0,0.0);

 TCanvas *c3b=new TCanvas("c3b","",1200,800);
 TH1F *h3b=new TH1F("h3b","", 37, 0.90795,1.3131);
 newt->Draw("mcasmMpim>>h3b",newbasic&&cas);
 h3b->Draw("E");
 h3b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h3b->GetXaxis()->SetTitle(" (cut on MMcas) M(#Lamda^{0} - #pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h3b,1,0.09,1.15,1,1,0,1.116,0.02,3,0.0,0.0,0.0);



 //c2->Print("~/clas/pics/11_nov11/proposal/mcasmMpim.eps");
 //*///---------------------------------------------------------------------------------





}