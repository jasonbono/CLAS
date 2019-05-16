/*

nov 23 2011: took this from mcas1690. it is just an improvment on cuts to get a clean cascade peak in the mmkpkppim spectrum



nov 22 2011:  this macro cuts on the cas0 in the mmkpkppim spectrum to search for resonances of casm at 1690 or 1620. cas(1530) is already well known.

note that the ground state of casm and cas0 are at 1321 and 1314 respetively so it should NOT be possible for the ground state of casm(1321)->cas0(1314)+pim(139) 


 So looking primaraly for: 
 casm(1690)->cas0(1314)+pim(139)


 */


void resonanceMMkpkppim(){
TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");
gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS.C");



//============= this is from leis_beautify.C which i changed a bit========================
printf("Welcome to the ROOT\n");
gStyle->SetTitleXOffset(0.9);
gStyle->SetTitleYOffset(1.3);
gStyle->SetTitleSize(0.045);
 //gStyle->SetLabelFont(72);
 //gStyle->SetPadLeftMargin(0.2);
 //gStyle->SetPadBottomMargin(0.2);
 gStyle->SetPadTopMargin(0.02);
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
 TCut vcut="abs(vz+90)<21&&sqrt(vx^2+vy^2)<8";  // relaxed this alot to allow for weak decays
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





 TCut tof22="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.5";
 TCut tof12="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.15"; // wont include tof1 cuts because it takes out to much signal.

 //----------------------------------------------------------------------------------
 //newt->Draw(">>basiclist", newbasic);
 //TEventList *list=(TEventList *)gDirectory->Get("basiclist");
 //newt->SetEventList(list);
  





 TCanvas *c0=new TCanvas("c0","",1200,800);
 TH1F *h0=new TH1F("h0","",35,1.15,1.5);
 h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");  


 newt->Draw("sqrt(mm2kpkppim)>>h0", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12);


 fitGAUS(h0,1,1.15,1.5,1,1,1,1.321,0.02,3);

c0->Print("~/clas/pics/11_nov11/proposal/g12/resonanceMMkpkppim.eps");



}
