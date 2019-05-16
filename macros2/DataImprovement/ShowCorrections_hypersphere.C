/*
Date: Jan 21 2013.  
Author: Jason Bono.
Purpose: To show the effect of the corrections on the missing mass specturm of kpkppim
*/



void ShowCorrections_hypersphere()
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
 //------Define Global Varibles---------
///edit theese 5 quantities
float sigmaA = 0.0113;
float sigmaB = 0.0107;
float sigmaC = 0.0031;
float sigmaD = 0.0030;
float depth = 1; 

//theese are fixed
float widthA = depth*sigmaA;
float widthB = depth*sigmaB;
float widthC = depth*sigmaC;
float widthD = depth*sigmaD;
float MASS_Xi = 1.321;
float MASS_Lambda = 1.116;


 TFile *fileData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05.root");
 TTree *tData = (TTree*)fileData->Get("v05_Basic");




 TCut CutABCD = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1"
 ,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
 TCut cut=CutABCD;


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


 canv->Print("./pics/ShowCorrections_mmkpkp.eps");

 //=====================mmkpkppim===============================
 

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
 tData->Draw("mmkpkppim_no_corrections>>h2_no_corrections",cut);
 canv2->cd(2);
 tData->Draw("mmkpkppim_no_pcor>>h2_no_pcor",cut);
 canv2->cd(3);
 tData->Draw("mmkpkppim_no_ecor>>h2_no_ecor",cut);
 canv2->cd(4);
 tData->Draw("mmkpkppim_no_eloss>>h2_no_eloss",cut);
 canv2->cd(5);
 tData->Draw("mmkpkppim>>h2_all_corrections",cut);
 
 canv2->Print("./pics/ShowCorrections_mmkpkppim.eps");

//=====================show invarent mass spectrum===========================


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
 tData->Draw("mcasmMpim>>h3",cut);
 canv3->cd(2);
 tData->Draw("mlampim>>h4",cut);




}