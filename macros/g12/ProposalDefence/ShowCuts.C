/*

Date: May 19 2012.  
Author: Jason Bono.
Purpose: To produce plots showing the cuts that were made to clean up the g12 data.


*/

void ShowCuts()
{

 //-------------------------------------beautify---------------------
 gStyle->SetTitleXOffset(0.9);
 gStyle->SetTitleYOffset(2.2);
 gStyle->SetTitleSize(0.045);
 gStyle->SetTitleYSize(0.025); 
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
 TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/large/v34k_full.root");
 TTree *reducedt = (TTree*)f->Get("v34k_reduced");
 TTree *fullt = (TTree*)f->Get("v37k_original");

 

 //-------------------------------cuts----------------------------------------------------------------------------------------------
 //basic cuts
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<30&&sqrt(vx^2+vy^2)<=7";  // relaxed this to allow for weak decays
 TCut beam="beam>3.3"; 
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1";  // relaxed since slower particle has lower time resoultion.
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;
 TCut allbut_st=n&&np&&vcut&&beam&&tof1&&tof2;
 
 //kf cuts
 TCut conf = "kf_prob > 0.10";

 //seperate out the vertex cuts (total defined above as vcut)
 TCut vr="sqrt(vx^2+vy^2)<=7";
 TCut vz="abs(vz+90)<30";
 TCut allbut_vz=n&&np&&vr&&beam&&st&&tof1&&tof2;
 TCut allbut_vr=n&&np&&vz&&beam&&st&&tof1&&tof2;

 //mass cuts
 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
 //--------------------------------------------------------------------------------------------------------------------------------------------






 TCanvas *c2=new TCanvas("c2","",1200,800);
 c2->Divide(2,1);
 c2_2->Divide(1,2);
 c2->cd(1); 


 TH1F *hst=new TH1F("hst","",80,-2,6);
 reducedt->Draw("stv-scv>>hst",allbut_st);
 TH1F *hstC=new TH1F("hstC","",80,-2,6);
 reducedt->Draw("stv-scv>>hstC",newbasic);
 hst->SetFillColor(2);
 hst->Draw();
 hstC->SetFillColor(4);
 hstC->Draw("SAME");
 hst->GetYaxis()->SetTitle("Events/0.1*ns");  
 hst->GetXaxis()->SetTitle("stv-scv (ns)");
 
 
cout << "full:  "  << fullt->GetEntries() << "   basic:  " << basict->GetEntries() <<endl;

}
