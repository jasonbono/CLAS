
/*
March 1 2012: this was made to check the distributions genererated by the kinematic fitter in the new analyzer
*/


void testKfit(){


TFile *f = TFile::Open("~/clas/rootfiles/g12/large/v24k.root");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/v24k_small.root");
TTree *newt = (TTree*)f->Get("v24k");




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






TCanvas *c0=new TCanvas("c0","",1200,800);
TH1F *h0=new TH1F("h0", "prob", 200,-0.01,1.01);
newt->Draw("kf_prob>>h0",newbasic&&casm&&cas);

TCanvas *c1=new TCanvas("c1","",1200,800);
TH1F *h1=new TH1F("h1", "chi2", 200,-1,10);
newt->Draw("kf_chi2>>h1",newbasic&&casm&&cas);

TCanvas *c2=new TCanvas("c2","",1200,800);
TH1F *h2=new TH1F("h2", "pullbeam", 200,-20,20);
newt->Draw("kf_pull_beam>>h2",newbasic&&casm&&cas);


TCanvas *c3=new TCanvas("c3","",1200,800);
TH1F *h3=new TH1F("h3", "mmkpkppim", 100,0.8,1.5);
newt->Draw("sqrt(mm2kpkppim)>>h3",newbasic&&casm&&cas);







}




