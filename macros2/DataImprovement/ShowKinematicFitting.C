void ShowKinematicFitting()
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


 //setup
 TFile *fileData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05.root");
 TTree *tData = (TTree*)fileData->Get("v05_Basic");


 TCut lam3="abs(sqrt(mm2kpkppim)-1.116)<0.018";
 TCut lamm3="abs(mcasmMpim-1.116)<0.016"; 

 TCut cas3="abs(sqrt(mm2kpkp) - 1.321)<0.018";
 TCut casm3="abs(mlampim-1.321)<0.014";

 TCut conf = "kf_prob > 0.65";
 TCut cut=conf;
 //TCut cut=cas3&&casm3&&lam3&&lamm3;

 //------------------show the probability and chi squared distribution-----------------------------
 TCanvas *cConf=new TCanvas("cConf","",1200,800);
 cConf->Divide(2,0);
 cConf->cd(1);

 ///conf

 // setup full hist
 TH1F *hConf=new TH1F("hConf","",100,-0.01,1.01);
 hConf->GetYaxis()->SetTitle("Counts");  
 hConf->GetXaxis()->SetTitle("Confidence Level");
 hConf->SetFillColor(2);
 hConf->SetMinimum(1);
 gPad->SetLogy();
 //setup good hist
 TH1F *hConfGood = (TH1F*)hConf->Clone("hConfGood");
 hConfGood->SetFillColor(9);

 //plot
 tData->Draw("kf_prob>>hConf");
 tData->Draw("kf_prob>>hConfGood",cut,"SAME");


 ///chi2
 cConf->cd(2);
 //setup full hist
 TH1F *hChi=new TH1F("hChi","",100,-0.01,7.01);
 hChi->GetYaxis()->SetTitle("Counts");
 hChi->GetXaxis()->SetTitle("#Chi^{2}");
 hChi->SetFillColor(2);
 hChi->SetMinimum(0);
 //setup good hist
 TH1F *hChiGood = (TH1F*)hChi->Clone("hChiGood");
 hChiGood->SetFillColor(9);

 //plot
 tData->Draw("kf_chi2>>hChi");
 tData->Draw("kf_chi2>>hChiGood",cut,"SAME");


 //------------------show the differences-----------------------------
 TCanvas *cDiff=new TCanvas("cDiff","",1200,800);
 cDiff->Divide(2,2);
 cDiff->cd(1);

 ///Diff

 //setup a histogram to clone
 TH1F *hDiff=new TH1F("hDiff","",500,-0.01,0.5);
 hDiff->GetYaxis()->SetTitle("Counts");  
 hDiff->GetXaxis()->SetTitle("p difference (GeV/c)");
 hDiff->SetFillColor(2);
 //hDiff->SetFillStyle(3001);
 hDiff->SetMinimum(0);

 //setup hists for all three particles and beam for all events
 TH1F *hDiff_kp1 = (TH1F*)hDiff->Clone("hDiff_kp1");
 hDiff_kp1->GetXaxis()->SetTitle(" kp1 p difference (GeV/c)");
 TH1F *hDiff_kp2 = (TH1F*)hDiff->Clone("hDiff_kp2");
 hDiff_kp2->GetXaxis()->SetTitle("kp2 p difference (GeV/c)");
 TH1F *hDiff_pim = (TH1F*)hDiff->Clone("hDiff_pim");
 hDiff_pim->GetXaxis()->SetTitle("pim p difference (GeV/c)");
 TH1F *hDiff_beam = (TH1F*)hDiff->Clone("hDiff_beam"); 
 hDiff_beam->GetXaxis()->SetTitle("beam p difference (GeV/c)");
 hDiff_beam->GetXaxis()->Set(300, -0.001, 0.01);


 //setup hists for all three particles and beam for good events
 TH1F *hDiffGood_kp1 = (TH1F*)hDiff_kp1->Clone("hDiffGood_kp1");
 hDiffGood_kp1->SetFillColor(9);
 hDiffGood_kp1->SetFillStyle(1001);
 TH1F *hDiffGood_kp2 = (TH1F*)hDiff_kp2->Clone("hDiffGood_kp2");
 hDiffGood_kp2->SetFillColor(9);
 hDiffGood_kp2->SetFillStyle(1001);
 TH1F *hDiffGood_pim = (TH1F*)hDiff_pim->Clone("hDiffGood_pim");
 hDiffGood_pim->SetFillColor(9);
 hDiffGood_pim->SetFillStyle(1001);
 TH1F *hDiffGood_beam = (TH1F*)hDiff_beam->Clone("hDiffGood_beam"); 
 hDiffGood_beam->SetFillColor(9);
 hDiffGood_beam->SetFillStyle(1001);

 //plot
 tData->Draw("kf_diff_k1>>hDiff_kp1");
 tData->Draw("kf_diff_k1>>hDiffGood_kp1",cut,"SAME");
 cDiff->cd(2);
 tData->Draw("kf_diff_k2>>hDiff_kp2");
 tData->Draw("kf_diff_k2>>hDiffGood_kp2",cut,"SAME");
 cDiff->cd(3);
 tData->Draw("kf_diff_pim>>hDiff_pim");
 tData->Draw("kf_diff_pim>>hDiffGood_pim",cut,"SAME");
 cDiff->cd(4);
 tData->Draw("kf_diff_beam>>hDiff_beam");
 tData->Draw("kf_diff_beam>>hDiffGood_beam",cut,"SAME");



 
 //*//<------------------show the kf mass plots-----------------------------
 TCanvas *cMass_kf=new TCanvas("cMass_kf","",1200,800);
 cMass_kf->Divide(2,2);
 cMass_kf->cd(1);

 //setup hists to clone for masses
 TH1F *hLamda=new TH1F("hLambda_kf","",1000,1.11,1.12);
 hLambda_kf->GetYaxis()->SetTitle("Events/0.001MeV/c^{2}");
 hLambda_kf->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
 hLambda_kf->SetFillColor(2);
 hLambda_kf->SetMinimum(0);

 TH1F *hXi_kf=new TH1F("hXi_kf","",1000,1.315,1.325);
 hXi_kf->GetYaxis()->SetTitle("Events/0.001MeV/c^{2}");  
 hXi_kf->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
 hXi_kf->SetFillColor(2);
 hXi_kf->SetMinimum(0);

 //setup four hists for all events
 TH1F *hLambda_kf_mm = (TH1F*)hLambda_kf->Clone("hLambda_kf_mm");
 TH1F *hLambda_kf_m = (TH1F*)hLambda_kf->Clone("hLambda_kf_m");
 TH1F *hXi_kf_mm = (TH1F*)hXi_kf->Clone("hXi_kf_mm");
 TH1F *hXi_kf_m = (TH1F*)hXi_kf->Clone("hXi_kf_m");
 hLambda_kf_m->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2})");
 hXi_kf_m->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");

 //setup four hists for good events
 TH1F *hLambdaGood_kf_mm = (TH1F*)hLambda_kf_mm->Clone("hLambdaGood_kf_mm");
 hLambdaGood_kf_mm->SetFillColor(9);
 hLambdaGood_kf_mm->SetFillStyle(1001);
 TH1F *hLambdaGood_kf_m = (TH1F*)hLambda_kf_m->Clone("hLambdaGood_kf_m");
 hLambdaGood_kf_m->SetFillColor(9);
 hLambdaGood_kf_m->SetFillStyle(1001);
 TH1F *hXiGood_kf_mm = (TH1F*)hXi_kf_mm->Clone("hXiGood_kf_mm");
 hXiGood_kf_mm->SetFillColor(9);
 hXiGood_kf_mm->SetFillStyle(1001);
 TH1F *hXiGood_kf_m = (TH1F*)hXi_kf_m->Clone("hXiGood_kf_m");
 hXiGood_kf_m->SetFillColor(9);
 hXiGood_kf_m->SetFillStyle(1001);


 //plot
 tData->Draw("kf_mmkpkppim>>hLambda_kf_mm");
 tData->Draw("kf_mmkpkppim>>hLambdaGood_kf_mm",cut,"SAME"); 
 cMass_kf->cd(2);
 tData->Draw("kf_mcasmMpim>>hLambda_kf_m");
 tData->Draw("kf_mcasmMpim>>hLambdaGood_kf_m",cut,"SAME");
 cMass_kf->cd(3);
 tData->Draw("kf_mmkpkp>>hXi_kf_mm");
 tData->Draw("kf_mmkpkp>>hXiGood_kf_mm",cut,"SAME"); 
 cMass_kf->cd(4);
 tData->Draw("kf_mlampim>>hXi_kf_m");
 tData->Draw("kf_mlampim>>hXiGood_kf_m",cut,"SAME");
 //*///

//------------------show the mass plots-----------------------------
 TCanvas *cMass=new TCanvas("cMass","",1200,800);
 cMass->Divide(2,2);
 cMass->cd(1);

 //setup hists to clone for masses
 TH1F *hLamda=new TH1F("hLambda","",80,1.0,1.28);
 hLambda->GetYaxis()->SetTitle("Events/3MeV/c^{2}");
 hLambda->GetXaxis()->SetTitle(" MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2}) test1");
 hLambda->SetFillColor(2);
 hLambda->SetMinimum(0);

 TH1F *hXi=new TH1F("hXi","",80,1.2,1.48);
 hXi->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
 hXi->GetXaxis()->SetTitle(" MM(K^{+}K^{+}) (GeV/c^{2})");
 hXi->SetFillColor(2);
 hXi->SetMinimum(0);

 //setup four hists for all events
 TH1F *hLambda_mm = (TH1F*)hLambda->Clone("hLambda_mm");
 TH1F *hLambda_m = (TH1F*)hLambda->Clone("hLambda_m");
 TH1F *hXi_mm = (TH1F*)hXi->Clone("hXi_mm");
 TH1F *hXi_m = (TH1F*)hXi->Clone("hXi_m");
 hLambda_m->GetXaxis()->SetTitle(" M(#Xi^{-} - #pi^{-}) (GeV/c^{2}) test2");
 hXi_m->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");

 //setup four hists for good events
 TH1F *hLambdaGood_mm = (TH1F*)hLambda_mm->Clone("hLambdaGood_mm");
 hLambdaGood_mm->SetFillColor(9);
 hLambdaGood_mm->SetFillStyle(1001);
 TH1F *hLambdaGood_m = (TH1F*)hLambda_m->Clone("hLambdaGood_m");
 hLambdaGood_m->SetFillColor(9);
 hLambdaGood_m->SetFillStyle(1001);
 TH1F *hXiGood_mm = (TH1F*)hXi_mm->Clone("hXiGood_mm");
 hXiGood_mm->SetFillColor(9);
 hXiGood_mm->SetFillStyle(1001);
 TH1F *hXiGood_m = (TH1F*)hXi_m->Clone("hXiGood_m");
 hXiGood_m->SetFillColor(9);
 hXiGood_m->SetFillStyle(1001);


 //plot
 tData->Draw("mmkpkppim>>hLambda_mm");
 tData->Draw("mmkpkppim>>hLambdaGood_mm",cut,"SAME"); 
 cMass->cd(2);
 tData->Draw("mcasmMpim>>hLambda_m");
 tData->Draw("mcasmMpim>>hLambdaGood_m",cut,"SAME");
 cMass->cd(3);
 tData->Draw("mmkpkp>>hXi_mm");
 tData->Draw("mmkpkp>>hXiGood_mm",cut,"SAME"); 
 cMass->cd(4);
 tData->Draw("mlampim>>hXi_m");
 tData->Draw("mlampim>>hXiGood_m",cut,"SAME");
 
}