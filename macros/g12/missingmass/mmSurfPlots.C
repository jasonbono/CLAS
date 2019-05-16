
/*

created on feb 7 2012:  jason bono.  

this macro is an adaptation of g12finalmplots.C from the macros/g12 directory. really the only similarity are the cuts ie the
definition of "newbasic" 
this was made at the request of brian raue and puneet. they wanted to see the surface plots of

mmkpkppim:mmkpkp



*/


void mmSurfPlots(){
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
//TTree *newt = (TTree*)f->Get("g12ana_v15");
TFile *f = TFile::Open("~/clas/rootfiles/g12/large/g12ana_v16_58090.root");
TTree *newt = (TTree*)f->Get("g12ana_v16");




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



 //====================================THE PLOTS================================

TCanvas *c0=new TCanvas("c0","",1200,800);
c0->Divide(2,0);
c0->cd(1);
TH2F *s0=new TH2F("s0", "Lambda:Xi", 40, 1.1, 1.5, 40, 0.90, 1.3);

s0->SetLabelFont(120, "xyz");
s0->SetTitleFont(132, "xyz");
s0->SetLabelSize(0.02, "xyz");
s0->SetTitleSize(0.04, "xyz");
s0->GetXaxis()->SetTitle("mmkpkp");
s0->GetXaxis()->CenterTitle();
s0->GetYaxis()->SetTitle("mmkpkppim");
s0->GetYaxis()->CenterTitle();



newt->Draw("sqrt(mm2kpkppim):sqrt(mm2kpkp)>>s0",newbasic);

s0->Draw("cont");
c0->cd(2);
s0->Draw("surf2");


//newt->Draw("beam");


}

