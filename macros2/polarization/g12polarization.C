/*

Date: May 19 2012.  
Author: Jason Bono.
Purpose: To produce plots showing the simulated events.

*/

void g12polarization()
{

 //-------------------------------------beautify---------------------
 gStyle->SetTitleXOffset(0.5);
 gStyle->SetTitleYOffset(0.55);
 gStyle->SetTitleSize(0.073);
 gStyle->SetTitleYSize(0.09); 
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


 //open the files and create the proper tree pointers
 TFile *simf = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/a1c/v07/MC_v07_v37k.root");
 //TFile *simf = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/v34k_100k.root");
 TFile *dataf = TFile::Open("/Users/Bono/clas/rootfiles/g12/newbasic/v37k_full_newbasic.root");
 TTree *simt = (TTree*)simf->Get("v37k");
 TTree *datat = (TTree*)dataf->Get("v37k_newbasic");
 
 TCut conf = "kf_prob > 0.50";


 TCanvas *c0=new TCanvas("c0","",300,200);
 TH1F *hdatax = new TH1F("datax","",6, -1,1);
 TH1F *hdatay = new TH1F("datay","",6, -1,1);
 TH1F *hdataz = new TH1F("dataz","",6, -1,1);
 hdatax->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 hdatay->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 hdataz->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   

 c0->Divide(3,0);
 c0->cd(1);
 datat->Draw("COS_pi_x>>datax",conf,"E");
 c0->cd(2); 
 datat->Draw("COS_pi_y>>datay",conf,"E");
 c0->cd(3); 
 datat->Draw("COS_pi_z>>dataz",conf,"E");


 TCanvas *c1=new TCanvas("c1","",300,200);
 TH1F *hsimx = new TH1F("hsimx","",6, -1,1);
 TH1F *hsimy = new TH1F("hsimy","",6, -1,1);
 TH1F *hsimz = new TH1F("hsimz","",6, -1,1);
 hsimx->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 hsimy->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 hsimz->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   

 c1->Divide(3,0);
 c1->cd(1);
 simt->Draw("COS_pi_x>>hsimx");
 c1->cd(2); 
 simt->Draw("COS_pi_y>>hsimy");
 c1->cd(3); 
 simt->Draw("COS_pi_z>>hsimz");


 //calculate the overall factor to normize the simulation with
 Float_t fac = (hdatax->GetEntries())/(hsimx->GetEntries());
 cout << "fac = " << fac << endl;


 //calculate the factor to do the acceptance corrections
 //Float_t acceptance = ((hsimx->GetEntries())/6);
 //cout << "acceptance = " << acceptance <<endl;


 //get acceptance correction for each bin
 Float_t acceptancex[6],acceptancey[6],acceptancez[6];
 for (Int_t i=1;i<=6;i++) {
  acceptancex[i] = (hsimx->GetEntries())/(6*hsimx->GetBinContent(i));
  acceptancey[i] = (hsimy->GetEntries())/(6*hsimy->GetBinContent(i));
  acceptancez[i] = (hsimz->GetEntries())/(6*hsimz->GetBinContent(i));

  cout << acceptancex[i] << "  " << acceptancey[i] << "  " << acceptancez[i] <<endl;
 }
 //  - - - - - - - -  - - - - - - - - plot simulation o normaized data- - - - - - - - - - - - - - - - - - - - - - - - - - -  
 TCanvas *c2x=new TCanvas("c2x","",700,700);
 TCanvas *c2y=new TCanvas("c2y","",700,700);
 TCanvas *c2z=new TCanvas("c2z","",700,700);

 TH1F *hsimxN = new TH1F("hsimxN","",6, -1,1);
 TH1F *hsimyN = new TH1F("hsimyN","",6, -1,1);
 TH1F *hsimzN = new TH1F("hsimzN","",6, -1,1);

 hsimxN->GetYaxis()->SetTitle("counts"); 
 hsimyN->GetYaxis()->SetTitle("counts");
 hsimzN->GetYaxis()->SetTitle("counts");
 hsimxN->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 hsimyN->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 hsimzN->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");

 hsimxN->Add(hsimx,fac);
 hsimyN->Add(hsimy,fac);
 hsimzN->Add(hsimz,fac);

 hsimxN->SetMinimum(0);
 hsimyN->SetMinimum(0);
 hsimzN->SetMinimum(0);
 
 hsimxN->SetFillColor(2);
 hsimxN->SetFillStyle(3002);
 hdatax->SetFillColor(3);
 hdatax->SetFillStyle(3002);

 hsimyN->SetFillColor(2);
 hsimyN->SetFillStyle(3002);
 hdatay->SetFillColor(3);
 hdatay->SetFillStyle(3002);

 hsimzN->SetFillColor(2);
 hsimzN->SetFillStyle(3002);
 hdataz->SetFillColor(3);
 hdataz->SetFillStyle(3002);

 hdatax->SetMarkerStyle(20);
 hdatay->SetMarkerStyle(20);
 hdataz->SetMarkerStyle(20);
 
 c2x->cd(); 
 hsimxN->Draw();
 hdatax->Draw("SAMEE1");

 c2y->cd(); 
 hsimyN->Draw();
 hdatay->Draw("SAMEE1");
 
 c2z->cd(); 
 hdataz->Draw("E1");
 hsimzN->Draw("SAME");
 


 //  - - - - - - - -  - - - - - - - - plot acceptance corrected data and simulated events- - - - - - - - - - - - - - - - - - -  
 TCanvas *c2xCorrected=new TCanvas("c2xCorrected","",700,700);
 TCanvas *c2xCorrected=new TCanvas("c2xCorrected","",700,700);
 TCanvas *c2xCorrected=new TCanvas("c2xCorrected","",700,700);

 TH1F *hsimxCor = new TH1F("hsimxCor","",6, -1,1);
 TH1F *hsimyCor = new TH1F("hsimyCor","",6, -1,1);
 TH1F *hsimzCor = new TH1F("hsimzCor","",6, -1,1);

 hsimxCor->GetYaxis()->SetTitle("counts"); 
 hsimyCor->GetYaxis()->SetTitle("counts");
 hsimzCor->GetYaxis()->SetTitle("counts");
 hsimxCor->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 hsimyCor->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 hsimzCor->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");


 //fill simulated
 hsimxCor->Add(hsimx,fac);
 hsimyCor->Add(hsimy,fac);
 hsimzCor->Add(hsimz,fac);
 //style
 hsimxCor->SetMinimum(0);
 hsimyCor->SetMinimum(0);
 hsimzCor->SetMinimum(0);
 
 hsimxCor->SetFillColor(2);
 hsimxCor->SetFillStyle(3002);
 hdataxCor->SetFillColor(3);
 hdataCorx->SetFillStyle(3002);

 hsimyCor->SetFillColor(2);
 hsimyCor->SetFillStyle(3002);
 hdatayCor->SetFillColor(3);
 hdatayCor->SetFillStyle(3002);

 hsimzCor->SetFillColor(2);
 hsimzCor->SetFillStyle(3002);
 hdatazCor->SetFillColor(3);
 hdatazCor->SetFillStyle(3002);

 hdataxCor->SetMarkerStyle(20);
 hdatayCor->SetMarkerStyle(20);
 hdatazCor->SetMarkerStyle(20);
 
 c2xCorrected->cd(); 
 hsimxCor->Draw();
 hdataxCor->Draw("SAMEE1");

 c2xCorrected->cd(); 
 hsimyCor->Draw();
 hdatay->Draw("SAMEE1");
 
 c2xCorrected->cd(); 
 hdatazCor->Draw("E1");
 hsimzCor->Draw("SAME");









//c2->Print("/Users/Bono/clas/macros/g12/ProposalDefence/pics/DataSimOverlay.eps");
//c2xCorrected->Print("~/Desktop/cosx.eps");
//c2xCorrected->Print("~/Desktop/cosy.eps");
//c2xCorrected->Print("~/Desktop/cosz.eps");
}