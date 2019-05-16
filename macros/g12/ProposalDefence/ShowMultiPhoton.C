/*
Date: May 21 2012.  
Author: Jason Bono.
Purpose: To produce plots showing how likely the photon has more than zero partners within 2ns.
*/



void ShowMultiPhoton()
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
 TFile *dataf = TFile::Open("/Users/Bono/clas/rootfiles/g12/large/v34k_full.root");
 TTree *datat = (TTree*)dataf->Get("v34k_original");
 //gPad->SetLiny();
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
 TCut beam="beam>3.6"; 
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;

 TCut conf = "kf_prob > 0.1";
 TCut NoNpBasic=n&&vcut&&beam&&st&&tof1&&tof2&&conf;

 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm





TCanvas *c0=new TCanvas("c0","",1200,800);
TH1F *hPhoton=new TH1F("hPhotonBad","",10,0,5);
TH1F *hPhoton2=new TH1F("hPhotonGood","",10,0,5);
hPhotonGood->SetFillColor(3);
hPhotonBad->SetFillColor(2);

hPhotonGood->GetYaxis()->SetTitle("Counts");  
hPhotonGood->GetXaxis()->SetTitle("Number of photons within 50 ps");

datat->Draw("nphoton_nb0>>hPhotonGood","nphoton_nb0 < 1.5 && nphoton_nb0 > 0.1 " && NoNpBasic);
datat->Draw("nphoton_nb0>>hPhotonBad","nphoton_nb0 > 1.5" && NoNpBasic,"SAME");
hPhoton2->SetFillColor(3);
//datat->Draw("nphoton_nb0>>hPhoton2","","SAME");



TCanvas *c1=new TCanvas("c1","",1200,800);
TH1F *hbeam=new TH1F("hbeam","",100,0,6);
datat->Draw("beam>>hbeam",NoNpBasic);


Float_t ngood = hbeam->GetEntries();
Float_t nbad = hPhotonBad->GetEntries();
Float_t percent =(nbad/ngood);

cout << nbad << "      " <<ngood<<endl;

//cout << "total entries is:  "  <<hbeam->GetEntries() << "  total in the nphoton plot is:  "  << hPhoton->GetEntries() <<endl;


cout << "the percent of events with more than one photon in the beam bucket is:  "  << percent << endl;


c0->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/multiphoton.eps");

}