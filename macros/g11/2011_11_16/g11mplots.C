// nov 17 2011

void g11mplots(){
  

  //TFile *freal = TFile::Open("~/clas/rootfiles/g11/new.root");
  TFile *freal = TFile::Open("~/clas/rootfiles/g11/nxyzREAL.root");
  //  TFile *fsim = TFile::Open("~/clas/rootfiles/g11/nxyzSIM.root");

  TTree *newt = (TTree*)freal->Get("mytree");
    gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS.C");
  // gROOT->ProcessLine(".L ~/clas/scripts/fit3GAUS.C");


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






//==============================the g11 cuts================================
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
 TCut mynewB=myksB&&myks2B&&myscB&&mysc2B&&mystB&&mytofB&&myvcutB;
 //---------------------------------------------------------------------------------------

 

//====================================MMCASCADE================================


 //*
 TCanvas *c0=new TCanvas("c0","",700,400);
 TH1F *h0=new TH1F("h0","",30,1.2,1.5);
 newt->Draw("sqrt(mm2kpkp)>>h0",mynewB&&mylambdaB&&mycasmB);

 // h2->Draw("E");
 h0->GetYaxis()->SetTitle("Counts/10MeV/c^{2}");  
 h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 
 h0->GetXaxis()->CenterTitle();
 h0->GetYaxis()->CenterTitle();
  
 fitGAUS(h0,1,1.27,1.38,1,1,0,1.32,0.01,3);
 // c0->Print("~/clas/pics/11_nov11/proposal/g11/g11_mmkpkp.eps");
c0->Print("~/clas/pics/11_nov29/g11_mmkpkp.eps");
 //*/

 //--------------------------------------------------------------------------------------


//=========================================MMLAMBDA=============================================


//*

TCanvas *c1=new TCanvas("c1","",1200,800);
 TH1F *h1=new TH1F("h1","",30,1,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>h1",mynewB&&mycasB&&mycasmB);
 // h1->Draw("E");
  h1->GetYaxis()->SetTitle("Counts/10MeV/c^{2}");  
  h1->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");   
  fitGAUS(h1,1,1.05,1.18,1,1,0,1.117,0.09,3);
  //   c1->Print("~/clas/pics/11_nov11/proposal/g11/g11_mmkpkppim.eps");
c1->Print("~/clas/pics/11_nov29/g11_mmkpkppim.eps");
  //*/

//--------------------------------------------------------------------------------------












 /* SOME OLD BULLSHIT



// plotting mass of labda + pim
 //TCanvas *c0=new TCanvas("c0","mlampim",1000,700);
 //TH1F *h0=new TH1F("h0","m(lam + pim)",200,1.2,1.8);
 //newt->Draw("mlampim>>h0",mynewB);

 
 //  THE BRANCHES DNE FOR THE CALCULATION BELOW!!! NEED "mcasmpim"
 //plotting mass of casm - pim
 // TFloat mcasm=1.322;
TCanvas *c1=new TCanvas("c1","mlampim",1000,700);
 TH1F *h1=new TH1F("h1","m(casm - pim)",200,1.2,1.4);
newt->Draw("mcasmpim>>h1");

 


 // plotting missing mass of kp kp
TCanvas *c2=new TCanvas("c2","mmkpkp",1000,700);
 TH1F *h2=new TH1F("h2","mmkpkp",100,1.2,1.5);
 newt->Draw("sqrt(mm2kpkp)>>h2",mynewB&&mylambdaB&&mycasmB);




 // plotting missing mass of kp kp pim
TCanvas *c3=new TCanvas("c3","mmkpkppim",1000,700);
 TH1F *h3=new TH1F("h3","mmkpkppim",200,1.0,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>h3",mynewB&&mycasB&&mycasmB);






*/




}
