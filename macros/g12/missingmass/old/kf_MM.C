/*
this was made first to show the ~(kf_lambda + kf_pim) spectrum
*/

void kf_MM()
{
 TFile *f = TFile::Open("~/clas/rootfiles/g12/v29k_mediumER.root");
 TTree *newt = (TTree*)f->Get("v29k");

 //TFile *f = TFile::Open("~/clas/rootfiles/g12/v30k_tiny.root");
 //TTree *newt = (TTree*)f->Get("v30k");

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


 //=============================kf cuts================================
 
 TCut conf = "kf_prob > 0.60";

 TCut kfcasm="abs(kf_mlampim-1.321)<0.013";
 TCut kflam="abs(kf_mmkpkppim-1.116)<0.033";
 TCut kflamm="abs(kf_mcasmMpim - 1.116)<0.01";
 TCut kfcas="abs(kf_mmkpkp - 1.321)<0.048";


 //-------------------------------------------------------------------




 /*//====================================== kf plots1  =================================== 
 TCanvas *c0=new TCanvas("c0","kf plots, conf & basic cuts",1200,800);
 c0->Divide(2,2);

 c0->cd(1);
 TH1F *h00=new TH1F("h00","kf_mlampim",70,1.0,1.7);
 newt -> Draw("kf_mlampim>>h00",newbasic&&conf);
 
 c0->cd(2);
 TH1F *h01=new TH1F("h01","kf_mcasmMpim",100,-1.5,1.5);
 newt -> Draw("kf_mcasmMpim>>h01",newbasic&&conf);

 c0->cd(3); 
 TH1F *h02=new TH1F("h02","kf_mmkpkp",70,1.0,1.7);
 newt -> Draw("kf_mmkpkp>>h02",newbasic&&conf); 
 
 c0->cd(4);
 TH1F *h03=new TH1F("h03","kf_mmkpkppim",100,1.0,1.2);
 newt -> Draw("kf_mmkpkppim>>h03",newbasic&&conf);



//====================================== kf plots2  =================================== 
 TCanvas *c1=new TCanvas("c1","kf plots, mass & basic cuts",1200,800);
 c1->Divide(2,2);

 c1->cd(1);
 TH1F *h10=new TH1F("h10","kf_mlampim",70,1.0,1.7);
 newt -> Draw("kf_mlampim>>h10",newbasic&&lam&&cas);
 
 c1->cd(2);
 TH1F *h11=new TH1F("h11","kf_mcasmMpim",100,-1.5,1.5);
 newt -> Draw("kf_mcasmMpim>>h11",newbasic&&lam&&cas);

 c1->cd(3); 
 TH1F *h12=new TH1F("h12","kf_mmkpkp",70,1.0,1.7);
 newt -> Draw("kf_mmkpkp>>h12",newbasic&&lamm&&casm); 
 
 c1->cd(4);
 TH1F *h13=new TH1F("h13","kf_mmkpkppim",100,1.0,1.2);
 newt -> Draw("kf_mmkpkppim>>h13",newbasic&&lamm&&casm);
*/



//====================================== kf plots3  =================================== 
 TCanvas *c2=new TCanvas("c2","kf plots, conf & mass & basic cuts",1200,800);
 c2->Divide(2,2);

 c2->cd(1);
 TH1F *h20=new TH1F("h20","kf_mlampim",100,1.1,1.4);
 newt -> Draw("kf_mlampim>>h20",newbasic&&lam&&cas&&conf);
 
 c2->cd(2);
 TH1F *h21=new TH1F("h21","kf_mcasmMpim",100,-1.5,1.5);
 newt -> Draw("kf_mcasmMpim>>h21",newbasic&&lam&&cas&&conf);

 c2->cd(3); 
 TH1F *h22=new TH1F("h22","kf_mmkpkp",50,1.2,1.4);
 newt -> Draw("kf_mmkpkp>>h22",newbasic&&lamm&&casm&&conf); 
 
 c2->cd(4);
 TH1F *h23=new TH1F("h23","kf_mmkpkppim",100,1.0,1.2);
 newt -> Draw("kf_mmkpkppim>>h23",newbasic&&lamm&&casm&&conf);








/*//====================================== regular  plots1  =================================== 
 TCanvas *c3=new TCanvas("c3","regular plots, conf & basic cuts",1200,800);
 c3->Divide(2,2);

 c3->cd(1);
 TH1F *h30=new TH1F("h30","kf_mlampim",70,1.0,1.7);
 newt -> Draw("mlampim>>h30",newbasic&&conf);
 
 c3->cd(2);
 TH1F *h31=new TH1F("h31","kf_mcasmMpim",100,-1.5,1.5);
 newt -> Draw("mcasmMpim>>h31",newbasic&&conf);

 c3->cd(3); 
 TH1F *h32=new TH1F("h32","kf_mmkpkp",70,1.0,1.7);
 newt -> Draw("mmkpkp>>h32",newbasic&&conf); 
 
 c3->cd(4);
 TH1F *h33=new TH1F("h33","kf_mmkpkppim",100,1.0,1.2);
 newt -> Draw("sqrt(mm2kpkppim)>>h33",newbasic&&conf);



*/
/*
//====================================== regular  plots2  =================================== 
 TCanvas *c4=new TCanvas("c4","regular plots, mass & basic cuts",1200,800);
 c4->Divide(2,2);

 c4->cd(1);
 TH1F *h40=new TH1F("h40","mlampim",100,1.1,1.4);
 newt -> Draw("mlampim>>h40",newbasic&&lam&&cas);

 c4->cd(2);
 TH1F *h41=new TH1F("h41","mcasmMpim",100,-1.5,1.5);
 newt -> Draw("mcasmMpim>>h41",newbasic&&lam&&cas);

 c4->cd(3); 
 TH1F *h42=new TH1F("h42","mmkpkp",70,1.0,1.7);
 newt -> Draw("mmkpkp>>h42",newbasic&&lamm&&casm); 

 c4->cd(4);
 TH1F *h43=new TH1F("h43","mmkpkppim",100,1.0,1.2);
 newt -> Draw("sqrt(mm2kpkppim)>>h43",newbasic&&lamm&&casm);


/*

//====================================== regular  plots3  =================================== 
 TCanvas *c5=new TCanvas("c5","regular plots, conf & mass & basic cuts",1200,800);
 c5->Divide(2,2);

 c5->cd(1);
 TH1F *h50=new TH1F("h50","kf_mlampim",100,1.1,1.4);
 newt -> Draw("mlampim>>h50",newbasic&&lam&&cas&&conf);

 c5->cd(2);
 TH1F *h51=new TH1F("h51","kf_mcasmMpim",100,-1.5,1.5);
 newt -> Draw("mcasmMpim>>h51",newbasic&&lam&&cas&&conf);

 c5->cd(3); 
 TH1F *h52=new TH1F("h52","kf_mmkpkp",70,1.0,1.7);
 newt -> Draw("mmkpkp>>h52",newbasic&&lamm&&casm&&conf); 

 c5->cd(4);
 TH1F *h53=new TH1F("h53","kf_mmkpkppim",100,1.0,1.2);
 newt -> Draw("sqrt(mm2kpkppim)>>h53",newbasic&&lamm&&casm&&conf);

*/


/*

//=====================================extra kf plot

 TCanvas *c8=new TCanvas("c8","kf plots, conf & kfmass & basic cuts",1200,800);
 c8->Divide(2,2);

 c8->cd(1);
 TH1F *h80=new TH1F("h80","kf_mlampim",100,1.1,1.4);
 newt -> Draw("kf_mlampim>>h80",newbasic&&kflam&&kfcas&&conf);

 c8->cd(2);
 TH1F *h81=new TH1F("h81","kf_mcasmMpim",100,-1.5,1.5);
 newt -> Draw("kf_mcasmMpim>>h81",newbasic&&kflam&&kfcas&&conf);

 c8->cd(3); 
 TH1F *h82=new TH1F("h82","kf_mmkpkp",70,1.0,1.7);
 newt -> Draw("kf_mmkpkp>>h82",newbasic&&lamm&&casm&&conf); 

 c8->cd(4);
 TH1F *h83=new TH1F("h83","kf_mmkpkppim",100,1.0,1.2);
 newt -> Draw("kf_mmkpkppim>>h83",newbasic&&lamm&&casm&&conf);

*/



}