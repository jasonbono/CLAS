/*
Date: May 21 2012.  
Author: Jason Bono.
Purpose: To show the effect of the corrections on the missing mass specturm of kpkppim

Modified: April 22 2014 to display in thesis.
*/



void ShowCorrections()
{

 //-------------------------------------beautify---------------------
 gStyle->SetTitleXOffset(0.5);
 gStyle->SetTitleYOffset(1.3);
 gStyle->SetTitleSize(0.08);
 gStyle->SetTitleYSize(0.035); 
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
 gStyle->SetOptStat(1);
 //gStyle->SetPadRightMargin(0.01);
//gStyle->SetPadLeftMargin(2);
 //-----------------------------------------------------------------



 //------------setup--------------------------------------------
 TFile *fileData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
 TTree *tData = (TTree*)fileData->Get("v15");





 TCanvas *canv=new TCanvas("canv","",1800,1000);
 canv->Divide(2,1);

 //create model for the missing mass histograms
 TH1F *h=new TH1F("h","",125,1.25,1.38);
 h->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
 h->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
 h->SetMinimum(0);
 h->SetFillColor(9);

 h_no_corrections = (TH1F*)h->Clone("hNo");
 h_no_corrections->SetTitle("No Corrections");
 h_all_corrections = (TH1F*)h->Clone("hAll");
 h_all_corrections->SetTitle("All Corrections");

 canv->cd(1);
 tData->Draw("mmkpkp_no_corrections>>hNo");
 canv->cd(2);
 tData->Draw("mmkpkp>>hAll");


}















void OldShowCorrections()
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
 gStyle->SetOptStat(1);
 //-----------------------------------------------------------------



 //------------setup--------------------------------------------
 TFile *fileData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05.root");
 TTree *tData = (TTree*)fileData->Get("v05_Basic");




 TCut conf = "kf_prob > 0.1";
 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; 

 TCut lam3="abs(sqrt(mm2kpkppim)-1.116)<0.018";
 TCut lamm3="abs(mcasmMpim-1.116)<0.016"; 
 TCut cut=lam3&&lamm3;

 TCanvas *canv=new TCanvas("canv","",1200,800);
 canv->Divide(3,2);

 //create model for the missing mass histograms
 TH1F *h=new TH1F("h","",160,1.2,1.68);
 h->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
 h->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
 h->SetMinimum(0);
 h->SetFillColor(9);

 h_no_corrections = (TH1F*)h->Clone("h_no_corrections");
 h_no_pcor = (TH1F*)h->Clone("h_no_pcor");
 h_no_ecor = (TH1F*)h->Clone("h_no_ecor");
 h_no_eloss = (TH1F*)h->Clone("h_no_eloss");
 h_all_corrections = (TH1F*)h->Clone("h_all_corrections");

 canv->cd(1);
 tData->Draw("mmkpkp_no_corrections>>h_no_corrections",cut);
 canv->cd(2);
 tData->Draw("mmkpkp_no_pcor>>h_no_pcor",cut);
 canv->cd(3);
 tData->Draw("mmkpkp_no_ecor>>h_no_ecor",cut);
 canv->cd(4);
 tData->Draw("mmkpkp_no_eloss>>h_no_eloss",cut);
 canv->cd(5);
 tData->Draw("mmkpkp>>h_all_corrections",cut);




 //=====================mmkpkppim===============================
 
 TCut cas3="abs(sqrt(mm2kpkp) - 1.321)<0.018";
 TCut casm3="abs(mlampim-1.321)<0.014";
 TCut cut2=cas3&&casm3;

 TCanvas *canv2=new TCanvas("canv2","",1200,800);
 canv2->Divide(3,2);


 TH1F *h2=new TH1F("h2","",160,1.0,1.48);
 h2->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
 h2->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
 h2->SetMinimum(0);
 h2->SetFillColor(9);

 h2_no_corrections = (TH1F*)h2->Clone("h2_no_corrections");
 h2_no_pcor = (TH1F*)h2->Clone("h2_no_pcor");
 h2_no_ecor = (TH1F*)h2->Clone("h2_no_ecor");
 h2_no_eloss = (TH1F*)h2->Clone("h2_no_eloss");
 h2_all_corrections = (TH1F*)h2->Clone("h2_all_corrections");


 canv2->cd(1);
 tData->Draw("mmkpkppim_no_corrections>>h2_no_corrections",cut2);
 canv2->cd(2);
 tData->Draw("mmkpkppim_no_pcor>>h2_no_pcor",cut2);
 canv2->cd(3);
 tData->Draw("mmkpkppim_no_ecor>>h2_no_ecor",cut2);
 canv2->cd(4);
 tData->Draw("mmkpkppim_no_eloss>>h2_no_eloss",cut2);
 canv2->cd(5);
 tData->Draw("mmkpkppim>>h2_all_corrections",cut2);


//=====================show invarent mass spectrum===========================
 
 //TCut cas3="abs(sqrt(mm2kpkp) - 1.321)<0.01";
 //TCut casm3="abs(mlampim-1.321)<0.01";
 //TCut cut2=cas3&&casm3;

 //TCut lam3="abs(sqrt(mm2kpkppim)-1.116)<0.01";
 //TCut lamm3="abs(mcasmMpim-1.116)<0.01"; 
 //TCut cut=lam3&&lamm3;

 TCanvas *canv3=new TCanvas("canv3","",1200,800);
 canv3->Divide(2,0);


 TH1F *h3=new TH1F("h3","",160,1.0,1.48);
 h3->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
 h3->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
 h3->SetMinimum(0);
 h3->SetFillColor(9);

 TH1F *h4=new TH1F("h4","",160,1.2,1.68);
 h4->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
 h4->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
 h4->SetMinimum(0);
 h4->SetFillColor(9);



 canv3->cd(1);
 tData->Draw("mcasmMpim>>h3",cut2);
 canv3->cd(2);
 tData->Draw("mlampim>>h4",cut);

}