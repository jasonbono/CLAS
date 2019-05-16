
// December 1 2011:  this was created to look at stv:scv-stv surface plots


void timing(){
  //TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
  TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v16.root");
TTree *newt = (TTree*)f->Get("g12ana_v16");



/*
//============= this is from leis_beautify.C which i changed a bit========================
//===============this is the final configuration that he used in his paper========
 printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.85);  //this: Xoff
 gStyle->SetTitleYOffset(0.95);  //this:  Yoff
 gStyle->SetTitleSize(0.07);  //this:    Xsize   
 gStyle->SetTitleYSize(0.07); //this     Ysize
 //gStyle->SetLabelFont(72);
 gStyle->SetPadLeftMargin(0.19);   // this: Yaxis 
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
*/

//*
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
//*/


 //-------------------------------------------------------------the surface plotting-----------------------------------------------
 

/*
 TH1F *hstv=new TH1F("hstv","",40,-1005,-995);
 TH1F *hdif=new TH1F("hdif","",100,-100,100);


 TCanvas *c0=new TCanvas("c0","",1200,800);
 //newt->Draw("stv>>hstv");
 newt->Draw("stvkp1");
 TCanvas *c1=new TCanvas("c1","",1200,800);
 newt->Draw("scv-stvkp1");
 TCanvas *c2=new TCanvas("c2","",1200,800);
 newt->Draw("stvkp1:scv-stvkp1");

 TCanvas *c3=new TCanvas("c3","",1200,800);
 TH2F *hkp1=new TH2F("hkp1","",75,-15,50,50,-10,40);
 newt->Draw("stvkp1:scv-stvkp1>>hkp1","","CONT");


 TCanvas *c4=new TCanvas("c4","",1200,800);
 TH2F *hkp2=new TH2F("hkp2","",75,-15,50,50,-10,40);
 newt->Draw("stvkp2:scv-stvkp2>>hkp2","","CONT");



 TCanvas *c5=new TCanvas("c5","",1200,800);
 TH2F *hpim=new TH2F("hpim","",75,-15,50,50,-10,40);
 newt->Draw("stvpim:scv-stvpim>>hpim","","CONT");
//*/




	TCanvas *c0=new TCanvas("c0","",1200,800);
	TH2F *S0=new TH2F("S1","",20,-5,5,50,10,35);
	TH2F *S2=new TH2F("S2","",20,-5,5,50,10,35);
	c0->Divide(2,2);
	c0->cd(1);
	newt->Draw("stvkp1:scv-stv");
	c0->cd(2);
//	newt->Draw("stvkp1:scv-stv>>S1");
	newt->Draw("stvkp1");
	c0->cd(3);
	newt->Draw("stvkp1:scv-stv",lam&&cas,"SURF");
	c0->cd(4);
	newt->Draw("stvkp1:scv-stv",lam&&cas);
//	newt->Draw("stvkp1:scv-stv>>S2",lam&&cas);


//TCanvas *c1=new TCanvas("c1","",1200,800);
//c1->Divide(2,2);
//c1->cd(1);
//newt->Draw("stvkp1:scv-stv");
//newt->Draw("stvkp1:scv-stv");
//newt->Draw("stvkp1:scv-stv");


 //	TCanvas *c4=new TCanvas("c4","",1200,800);
 	//TH2F *hkp2=new TH2F("hkp2","",75,-15,50,50,-10,40);
 //	newt->Draw("stvkp2:scv-stv>>S1",lam&&cas);



 //	TCanvas *c5=new TCanvas("c5","",1200,800);
 	//TH2F *hpim=new TH2F("hpim","",75,-15,50,50,-10,40);
 //	newt->Draw("stvpim:scv-stv>>S1",lam&&cas);












}
