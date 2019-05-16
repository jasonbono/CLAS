/*
Date: May 21 2012.  
Author: Jason Bono.
Purpose: To produce plots showing how the kinematic fitter affected the signal.
it is shown in comparison to the older mcuts and mmcuts
*/



void ShowKinematicFitting2()
{

 //-------------------------------------beautify---------------------
 gStyle->SetTitleXOffset(0.5);
 gStyle->SetTitleYOffset(0.65);
 gStyle->SetTitleSize(0.08);
 gStyle->SetTitleYSize(0.07); 
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
 //-----------------------------------------------------------------


 //------------setup--------------------------------------------
 TFile *dataf = TFile::Open("/Users/Bono/clas/rootfiles/g12/newbasic/v37k_full_newbasic.root");
 TTree *datat = (TTree*)dataf->Get("v37k_newbasic");
 gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS3.C");
 gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS.C");
 TCut conf = "kf_prob > 0.50";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut casm="abs(mlampim-1.321)<0.013";

TCut cas2="abs(sqrt(mm2kpkp) - 1.321)<0.017";
TCut lam2="abs(sqrt(mm2kpkppim)-1.116)<0.01";
TCut lamm2="abs(mcasmMpim-1.116)<0.02"; 

//------------------show the probability distribution-----------------------------
 TCanvas *cConf=new TCanvas("cConf","",1200,800);
 TH1F *hConf=new TH1F("hConf","",100,-0.01,1.01);
 hConf->GetYaxis()->SetTitle("Counts");  
hConf->GetXaxis()->SetTitle("Confidence Level");



 hConf->SetFillColor(2);
 hConf->SetMinimum(1);
 gPad->SetLogy();
 datat->Draw("kf_prob>>hConf");
 //h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 //h0->GetXaxis()->SetTitle("mcut       MM(K^{+}K^{+}) (GeV/c^{2})");

 TH1F *hConfgood=new TH1F("hConfgood","",100,-0.01,1.01);
 hConfgood->SetFillColor(3);
 hConfgood->SetMinimum(1);
 gPad->SetLogy();
 datat->Draw("kf_prob>>hConfgood","kf_prob > 0.5","SAME"); 






 // --------------------missing mass of kpkp-------------------------------------
 TCanvas *c0=new TCanvas("c0","",700,400);
 TH1F *h0=new TH1F("h0","",40,1.1,1.5);
 datat->Draw("sqrt(mm2kpkp)>>h0",lam&&lamm);
 h0->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 fitGAUS3(h0,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);



 TCanvas *c0b=new TCanvas("c0b","",700,400);
 TH1F *h0b=new TH1F("h0b","",40,1.1,1.5);
 datat->Draw("sqrt(mm2kpkp)>>h0b",conf);
 h0b->GetYaxis()->SetTitle("Counts/10MeV/c^{2}");  
 h0b->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");  
 h0b->GetXaxis()->CenterTitle();
 h0b->GetYaxis()->CenterTitle(); 
 //fitGAUS3(h0b,1,1.1,1.5,1,1,0,1.32,0.01,3,0,0,0);
    fitGAUS(h0b,1,1.27,1.38,1,1,0,1.32,0.01,3);


 // --------------------missing mass of kpkppim-------------------------------------
 TCanvas *c1=new TCanvas("c1","",1200,800);
 // TH1F *hlam=new TH1F("hlam","",37, 0.90795,1.3131);
 TH1F *h1=new TH1F("h1","",37,0.90795,1.3131);
 datat->Draw("sqrt(mm2kpkppim)>>h1",cas&&casm);
 // h1->Draw("E");
 h1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h1->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h1,1,0.9,1.3,1,1,0,1.116,0.01,3,0,0,0);



 TCanvas *c1b=new TCanvas("c1b","",1200,800);
 TH1F *h1b=new TH1F("h1b","",37,0.90795,1.3131);
 datat->Draw("sqrt(mm2kpkppim)>>h1b",conf);
 // h1->Draw("E");
 h1b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h1b->GetXaxis()->SetTitle("confidence cut      MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h1b,1,0.9,1.3,1,1,0,1.116,0.01,3,0,0,0);




 //--------------------invarient mass of lambda + pion ------------------------------
 TCanvas *c2=new TCanvas("c2","",1200,800);
 TH1F *h2=new TH1F("h2","",40,1.1,1.5);
 datat->Draw("mlampim>>h2",lam);
 h2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h2->GetXaxis()->SetTitle("mmcut  M(#Xi^{-}#pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h2,1,1.27,1.5,1,1,0,1.32,0.02,3,0.0,0.0,0.0);

 TCanvas *c2b=new TCanvas("c2b","",1200,800);
 TH1F *h2b=new TH1F("h2b","",40,1.1,1.5);
 datat->Draw("mlampim>>h2b",conf);
 h2b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h2b->GetXaxis()->SetTitle("confidence cut     M(#Xi^{-}#pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h2b,1,1.27,1.5,1,1,0,1.32,0.02,3,0.0,0.0,0.0);



 

 //--------------------invarient mass of Xi - pion ------------------------------
 TCanvas *c3=new TCanvas("c3","",1200,800);
 TH1F *h3=new TH1F("h3","", 37, 0.90795,1.3131);
 datat->Draw("mcasmMpim>>h3",cas);
 h3->Draw("E");
 h3->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h3->GetXaxis()->SetTitle("mmcut  M(#Lambda^{0} - #pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h3,1,0.09,1.15,1,1,0,1.116,0.02,3,0.0,0.0,0.0);

 TCanvas *c3b=new TCanvas("c3b","",1200,800);
 TH1F *h3b=new TH1F("h3b","", 37, 0.90795,1.3131);
 datat->Draw("mcasmMpim>>h3b",conf);
 h3b->Draw("E");
 h3b->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 h3b->GetXaxis()->SetTitle("confidence cut   M(#Lambda^{0} - #pi^{-}) (GeV/c^{2})");   
 fitGAUS3(h3b,1,1.0,1.14,1,1,0,1.116,0.02,3,0.0,0.0,0.0);



cConf->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/confidencelevels.eps");

c0->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/mmkpkp_mmcuts_mcuts.eps");
c0b->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/mmkpkp_confcuts.eps");

c1->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/mmkpkppim_mmcuts_mcuts.eps");
c1b->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/mmkpkppim_confcuts.eps");

}