/*
March 14 2012:
Purpose: to evaluate the induced polarization on the newest calculation of the angular distributions. the macro that was used to add the angles coresponds to the analyzer v28k.


*/




void P()
{

 TFile *freal = TFile::Open("~/clas/rootfiles/g11/xyzReal.root");
 TFile *fsim = TFile::Open("~/clas/rootfiles/g11/xyzSim.root");

 TTree *realt = (TTree*)freal->Get("new");
 TTree *simt = (TTree*)fsim->Get("g112kppim");


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
 //----------------------------------------------------------------------------

 //=============================CUTS===============================================
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
 //------------------------------------------------------------------------------------


 //=====================================angle wrt Y axis==============================
 TCanvas *c0=new TCanvas("c0","",1200,800);
 TH1F *h0=new TH1F("h0","",20,-1,1);
 h0->SetMinimum(0);
 h0->GetYaxis()->SetTitle("Events");  
 h0->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 realt->Draw("mr_COS_pi_y>>h0",mynewB&&mylambdaB&&mycasB&&mycasmB);
 delete c0;

 TCanvas *c1=new TCanvas("c1","",1200,800);
 TH1F *h1=new TH1F("h1","",20,-1,1);
 h1->SetMinimum(0);
 h1->GetYaxis()->SetTitle("Events");  
 h1->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 simt->Draw("mr_COS_pi_y>>h1",mynewB&&mylambdaB&&mycasB&&mycasmB);
 delete c1;

 TCanvas *c2=new TCanvas("c2","",1200,800);
 Float_t dataN=h0->GetEntries();
 Float_t simN=h1->GetEntries();
 cout <<dataN<<"  "<<simN<<endl; 
 //*

 //h0->Scale(1/dataN);
 h1->Scale(dataN/simN);
 h0->Rebin(2);
 h1->Rebin(2);
 
 h0->SetFillColor(5);
 h1->SetFillColor(1);
 h1->SetFillStyle(3004);


 h0->GetYaxis()->SetLabelSize(0.05);  
 h0->GetXaxis()->SetLabelSize(0.05);
 h0->GetXaxis()->CenterTitle();
 h0->GetYaxis()->CenterTitle();


 h0->Draw("E");
 h1->Draw("SAME");
 //*///--------------------------------------------------------------------------------------------------------------------------

 //=====================================angle wrt X axis==============================
 TCanvas *c0b=new TCanvas("c0b","",1200,800);
 TH1F *h0b=new TH1F("h0b","",20,-1,1);
 h0b->SetMinimum(0);
 h0b->GetYaxis()->SetTitle("Events");  
 h0b->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 realt->Draw("mr_COS_pi_x>>h0b",mynewB&&mylambdaB&&mycasB&&mycasmB);
 delete c0b;

 TCanvas *c1b=new TCanvas("c1b","",1200,800);
 TH1F *h1b=new TH1F("h1b","",20,-1,1);
 h1b->SetMinimum(0);
 h1b->GetYaxis()->SetTitle("Events");  
 h1b->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 simt->Draw("mr_COS_pi_x>>h1b",mynewB&&mylambdaB&&mycasB&&mycasmB);
 delete c1b; 

 TCanvas *c2b=new TCanvas("c2b","",1200,800);
 Float_t dataNb=h0b->GetEntries();
 Float_t simNb=h1b->GetEntries();
 cout << dataNb << "  " << simNb << endl; 


 //h0->Scale(1/dataN);
 h1b->Scale(dataNb/simNb);
 h0b->Rebin(2);
 h1b->Rebin(2);
 
 h0b->SetFillColor(5);
 h1b->SetFillColor(1);
 h1b->SetFillStyle(3004);

 h0b->Draw("E");
 h1b->Draw("SAME");

//*///--------------------------------------------------------------------------------------------------------------------------

//=====================================angle wrt Z axis==============================

 TCanvas *c0c=new TCanvas("c0c","",1200,800);
 TH1F *h0c=new TH1F("h0c","",20,-1,1);
 h0c->SetMinimum(0);
 h0c->GetYaxis()->SetTitle("Events");  
 h0c->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   
 realt->Draw("mr_COS_pi_z>>h0c",mynewB&&mylambdaB&&mycasB&&mycasmB);
 delete c0c;

 TCanvas *c1c=new TCanvas("c1c","",1200,800);
 TH1F *h1c=new TH1F("h1c","",20,-1,1);
 h1c->SetMinimum(0);
 h1c->GetYaxis()->SetTitle("Events");  
 h1c->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   
 simt->Draw("mr_COS_pi_z>>h1c",mynewB&&mylambdaB&&mycasB&&mycasmB);
 delete c1c;

 TCanvas *c2c=new TCanvas("c2c","",1200,800);
  Float_t dataNc=h0c->GetEntries();
  Float_t simNc=h1c->GetEntries();
  cout <<dataNc<<"  "<<simNc<<endl; 
//*

  //h0->Scale(1/dataN);
 h1c->Scale(dataNc/simNc);
 h0c->Rebin(2);
 h1c->Rebin(2);
 
 h0c->SetFillColor(5);
 h1c->SetFillColor(1);
 h1c->SetFillStyle(3004);

 h0c->Draw("E");
 h1c->Draw("SAME");




}
