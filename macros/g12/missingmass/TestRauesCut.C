

// this was taken from "g12finalmplots.C" to test to see the diffrence
//in the signal to background ratio for my tof cuts and theres.


void TestRauesCut(){
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
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
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
 TCut newbasicbuttof=n&&np&&vcut&&beam&&st; 

 //theese are best defined in this part of the code to prevent discrepenceys when changing cuts in geometry.
TCut allbut_vz=n&&np&&"sqrt(vx^2+vy^2)<7"&&beam&&st&&tof1&&tof2;
TCut allbut_vr=n&&np&&"abs(vz+90)<30"&&beam&&st&&tof1&&tof2;

 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
 //----------------------------------------------------------------------------------


//=============================================================================
//=================================original================================
//=============================================================================



 //====================================MMCASCADE================================


 //*
 TCanvas *c0=new TCanvas("c0","",1200,800);
 TH1F *h0=new TH1F("h0","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>h0",newbasic&&lamm);


 h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 fitGAUS3(h0,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);
 

 //*/

 //--------------------------------------------------------------------------------------


//=========================================MMLAMBDA=============================================


/*

 TCanvas *c1=new TCanvas("c1","",1200,800);

 TH1F *h1=new TH1F("h1","",37,0.90795,1.3131);
 newt->Draw("sqrt(mm2kpkppim)>>h1",newbasic&&casm);

  h1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
  h1->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");   
  fitGAUS3(h1,1,0.9,1.3,1,1,0,1.116,0.01,3,0,0,0);
  
  //*/

//--------------------------------------------------------------------------------------





//=============================================================================
//=================================with mirianas cuts================================
//=============================================================================

//a simple test with TString
/*TString test1 = " beam > 3 ";
TString test2 = " beam";
test2 += " > ";
test2 += " 4 ";
TString test3 = "beam";
TString add =  " > ";
TString add2 =   ;
test3 += add;
test3 += add2;
cout << test2 << endl;
TCanvas *ctest=new TCanvas("ctest","",1200,800);
ctest -> Divide(2,1);
ctest -> cd(1);
newt -> Draw("beam");
ctest -> cd(2);
newt -> Draw("beam", test3);



// a test to compare diffrent calculated values of beta 2 and 3 should be the same
Float_t mpim = 0.13957;
Float_t mkp = 0.49367;
TCanvas *ctest2=new TCanvas("ctest2","",1200,800);
ctest2 -> Divide(4,1);
ctest2 -> cd(1);
newt -> Draw(Form("pkp1/sqrt((pkp1*pkp1) + (%f*%f))" , mpim, mpim ));
ctest2 -> cd(2);
newt -> Draw(Form("pkp1/sqrt((pkp1*pkp1) + (%f*%f))" , mkp, mkp ));
ctest2 -> cd(3);
newt -> Draw("betakp1");
ctest2 -> cd(4);
newt -> Draw("tofbetakp1");
*/




///////////////////////////////

// DEFINE THE NEW CUTS
Float_t mpim = 0.13957;
Float_t mkp = 0.49367;
Float_t mpr = 0.93827;

//-----------------------------------------for relating kaon and pion---------------------------------------------------------------------


// check that my definitions of vertex time is correct. i will simply copy and past theese to make more complext cuts
TString raueVtimedif1 = "abs(vtime - (sctkp1 - sclkp1/((pkp1/sqrt((pkp1*pkp1) + (0.13957 * 0.13957)))*29.99)))";
TString raueVtimedif2 = "abs(vtime - (sctkp2 - sclkp2/((pkp2/sqrt((pkp2*pkp2) + (0.13957 * 0.13957)))*29.99)))";
TString myVtimedif1 = "abs(vtime - (sctkp1-sclkp1/(betakp1*29.99)))";
TString myVtimedif2 = "abs(vtime - (sctkp2-sclkp2/(betakp2*29.99)))";
TString myVtime1diftest = "abs(vtime - (sctkp1 - sclkp1/((pkp1/sqrt((pkp1*pkp1) + (0.49367 * 0.49367)))*29.99)))";
TString myVtime2diftest = "abs(vtime - (sctkp2 - sclkp2/((pkp2/sqrt((pkp2*pkp2) + (0.49367 * 0.49367)))*29.99)))";

//test that myVtime is the same as myVtimetest
TCanvas *ctest3=new TCanvas("ctest3","",1200,800);
ctest3 -> Divide(2,2);
ctest3 -> cd(1);
newt -> Draw(myVtimedif1);
ctest3 -> cd(2);
newt -> Draw(myVtimedif2);
ctest3 -> cd(3);
newt -> Draw(myVtime1diftest);
ctest3 -> cd(4);
newt -> Draw(myVtime2diftest);



// now plot with the new cut for k1 and the old one for k2
TCanvas *ck1=new TCanvas("ck1","",1200,800);
TH1F *hk1=new TH1F("hk1","",40,1.1,1.5);
TString k1better = raueVtimedif1;
k1better += " > ";
k1better += myVtimedif1;
newt -> Draw("sqrt(mm2kpkp) >> hk1",k1better && tof2 && lamm && newbasicbuttof);
hk1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
hk1->GetXaxis()->SetTitle("k1 better than pi MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(hk1,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



// now plot with the new cut for k2 and the old one for k1
TCanvas *ck2=new TCanvas("ck2","",1200,800);
TH1F *hk2=new TH1F("hk2","",40,1.1,1.5);
TString k2better = raueVtimedif2;
k2better += " > ";
k2better += myVtimedif2;
newt -> Draw("sqrt(mm2kpkp) >> hk2",k2better && tof1 && lamm && newbasicbuttof);
hk2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
hk2->GetXaxis()->SetTitle("k2 better than pi MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(hk2,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



// now plot with the new cut for k2 and the old one for k1
TCanvas *ck1k2=new TCanvas("ck1k2","",1200,800);
TH1F *hk1k2=new TH1F("hk1k2","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> hk1k2", k1better && lamm && k2better && newbasicbuttof);
hk1k2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
hk1k2->GetXaxis()->SetTitle("k1 & k2 better than pi MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(hk1k2,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);


TCanvas *call=new TCanvas("call","",1200,800);
TH1F *hall=new TH1F("hall","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> hall", k1better && lamm && k2better && newbasic);
hall->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
hall->GetXaxis()->SetTitle("combo of all 4 cuts MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(hall,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);




TCanvas *cOrig=new TCanvas("cOrig","",1200,800);
TH1F *hOrig=new TH1F("hOrig","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> hOrig", lamm && newbasic );
hOrig->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
hOrig->GetXaxis()->SetTitle("Original MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(hOrig,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



//*/












//-----------------------------------------for relating kaon and proton---------------------------------------------------------------------


// check that my definitions of vertex time is correct. i will simply copy and past theese to make more complext cuts
TString prVtimedif1 = "abs(vtime - (sctkp1 - sclkp1/((pkp1/sqrt((pkp1*pkp1) + (0.93827 * 0.93827)))*29.99)))";
TString prVtimedif2 = "abs(vtime - (sctkp2 - sclkp2/((pkp2/sqrt((pkp2*pkp2) + (0.93827 * 0.93827)))*29.99)))";
TString prmyVtimedif1 = "abs(vtime - (sctkp1-sclkp1/(betakp1*29.99)))";
TString prmyVtimedif2 = "abs(vtime - (sctkp2-sclkp2/(betakp2*29.99)))";
TString prmyVtime1diftest = "abs(vtime - (sctkp1 - sclkp1/((pkp1/sqrt((pkp1*pkp1) + (0.49367 * 0.49367)))*29.99)))";
TString prmyVtime2diftest = "abs(vtime - (sctkp2 - sclkp2/((pkp2/sqrt((pkp2*pkp2) + (0.49367 * 0.49367)))*29.99)))";



// now plot with the new cut for k1 and the old one for k2
TCanvas *prck1=new TCanvas("prck1","",1200,800);
TH1F *prhk1=new TH1F("prhk1","",40,1.1,1.5);
TString prk1better = prVtimedif1;
prk1better += " > ";
prk1better += prmyVtimedif1;
newt -> Draw("sqrt(mm2kpkp) >> prhk1",prk1better && tof2 && lamm && newbasicbuttof);
prhk1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
prhk1->GetXaxis()->SetTitle("k1 better than pr MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(prhk1,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



// now plot with the new cut for k2 and the old one for k1
TCanvas *prck2=new TCanvas("prck2","",1200,800);
TH1F *prhk2=new TH1F("prhk2","",40,1.1,1.5);
TString prk2better = prVtimedif2;
prk2better += " > ";
prk2better += prmyVtimedif2;
newt -> Draw("sqrt(mm2kpkp) >> prhk2",prk2better && tof1 && lamm && newbasicbuttof);
prhk2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
prhk2->GetXaxis()->SetTitle("k2 better than pr MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(prhk2,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



// now plot with the new cut for k2 and the old one for k1
TCanvas *prck1k2=new TCanvas("prck1k2","",1200,800);
TH1F *prhk1k2=new TH1F("prhk1k2","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> prhk1k2", prk1better && lamm && prk2better && newbasicbuttof);
prhk1k2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
prhk1k2->GetXaxis()->SetTitle("k1 & k2 better than pr MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(prhk1k2,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);


TCanvas *prcall=new TCanvas("prcall","",1200,800);
TH1F *prhall=new TH1F("prhall","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> prhall", prk1better && lamm && prk2better && newbasic);
prhall->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
prhall->GetXaxis()->SetTitle("combo of all 4 cuts (for proton and kaon) MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(prhall,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);

TCanvas *prpicall=new TCanvas("prpicall","",1200,800);
TH1F *prpihall=new TH1F("prpihall","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> prpihall", prk1better && lamm && prk2better && newbasic && k1better && newbasic && k2better);
prpihall->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
prpihall->GetXaxis()->SetTitle("combo of 8 cuts (pr pi, k) MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(prpihall,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);




/*


TCanvas *cOrig=new TCanvas("cOrig","",1200,800);
TH1F *hOrig=new TH1F("hOrig","",40,1.1,1.5);
newt -> Draw("sqrt(mm2kpkp) >> hOrig", lamm && newbasic );
hOrig->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
hOrig->GetXaxis()->SetTitle("Original MM(K^{+}K^{+}) (GeV/c^{2})");   
fitGAUS3(hOrig,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



*/





















}