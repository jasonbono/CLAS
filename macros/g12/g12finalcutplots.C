
void g12finalcutplots(){
   TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
   // TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
TTree *newt = (TTree*)f->Get("g12ana_v15");
gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS.C");


//============= this is from leis_beautify.C which i changed a bit========================
printf("Welcome to the ROOT\n");
 gStyle->SetTitleXOffset(0.9);
 gStyle->SetTitleYOffset(2.2);
 gStyle->SetTitleSize(0.045);
 gStyle->SetTitleYSize(0.025); //jb
 //gStyle->SetLabelFont(72);
 //gStyle->SetPadLeftMargin(0.2);
 //gStyle->SetPadBottomMargin(0.2);
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
//====================================================================


//=========================version 1 of cuts========================
/*
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<24&&(vx^2+vy^2)<20";
 TCut beam="beam>3.6"; 
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.4";
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;
 
 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
*/
 //----------------------------------------------------------------------------------



//=========================the most recent cuts as of nov22========================
//need to relax a few cuts here after showing lei my overlay plots.
 TCut n="np<2&&npip<1&&nkm<1";
 TCut np="nphoton_nb1<2";
 TCut vcut="abs(vz+90)<30&&sqrt(vx^2+vy^2)<=7";  // relaxed this alot to allow for weak decays
 TCut beam="beam>3.3"; //relaxed this from 3.6
 TCut st="abs(stv-scv)<1";
 TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";
 TCut tof2="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1";  // this is relaxed because the slower particle has a lower time resoultion.
 TCut newbasic=n&&np&&vcut&&beam&&st&&tof1&&tof2;
 
 //theese are best defined in this part of the code to prevent discrepenceys when changing cuts in geometry.
 TCut vr="sqrt(vx^2+vy^2)<=7";
 TCut vz="abs(vz+90)<30";
 TCut allbut_vz=n&&np&&vr&&beam&&st&&tof1&&tof2;
 TCut allbut_vr=n&&np&&vz&&beam&&st&&tof1&&tof2;




 TCut casm="abs(mlampim-1.321)<0.013";
 TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 TCut lamm2="abs(mcasmMpim-1.116)<0.02"; //lei used this cut rather than lamm
 //----------------------------------------------------------------------------------





 

 //===============all 4 of the mass plots are stored====================
 //    DONT COMMENT THEESE OUT IF YOU WANT TO LOOK AT HOW THE CUTS AFFECT THE MM SPECTRUMS
 
 TH1F *hmmkpkp=new TH1F("hmmkpkp","",40,1.1,1.5);
 // TH1F *hmmkpkppim=new TH1F("hmmkpkppim","",40,0.9,1.3);
 TH1F *hmmkpkppim=new TH1F("hmmkpkppim","",37,0.90795,1.3131);

 // now to copy the hists.
 TH1F *hmmkpkp_vr = (TH1F*)hmmkpkp->Clone("hmmkpkp_vr");
 TH1F *hmmkpkp_st = (TH1F*)hmmkpkp->Clone("hmmkpkp_st");
 TH1F *hmmkpkp_beam = (TH1F*)hmmkpkp->Clone("hmmkpkp_beam");
 TH1F *hmmkpkp_tof1 = (TH1F*)hmmkpkp->Clone("hmmkpkp_tof1");
 TH1F *hmmkpkp_tof2 = (TH1F*)hmmkpkp->Clone("hmmkpkp_tof2");

 TH1F *hmmkpkppim_vr = (TH1F*)hmmkpkppim->Clone("hmmkpkppim_vr");
 TH1F *hmmkpkppim_st = (TH1F*)hmmkpkppim->Clone("hmmkpkppim_st");
 TH1F *hmmkpkppim_beam = (TH1F*)hmmkpkppim->Clone("hmmkpkppim_beam");
 TH1F *hmmkpkppim_tof1 = (TH1F*)hmmkpkppim->Clone("hmmkpkppim_tof1");
 TH1F *hmmkpkppim_tof2 = (TH1F*)hmmkpkppim->Clone("hmmkpkppim_tof2");



 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp",newbasic&&lamm);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim",newbasic&&casm);

 //-----------------------------------------------------------------------------------------



 //----------------------------------------------------------------------



 //==============vcut========================================================

//--------the vz portion.... does nothing and wont include.----------

/*
 TCanvas *c0=new TCanvas("c0","",600,400);
 TH1F *hvz=new TH1F("hvz","",300,-150,-40);
 newt->Draw("vz>>hvz",allbut_vz);
 TH1F *hvzC=new TH1F("hvzC","",300,-150,-40);
 newt->Draw("vz>>hvzC",newbasic);
 hvz->Draw();
 hvzC->SetFillColor(2);
 hvzC->Draw("SAME");


 //h0->GetYaxis()->SetTitle("Event/10MeV/c^{2}");  
 //h0->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");   
 */
//----------------------vz cut does nothing---------------------


//--------------------the vr portion-----------------------
//*


 TCanvas *c1=new TCanvas("c1","",1200,800);
 c1->Divide(2,1);
 c1_2->Divide(1,2);
 c1->cd(1); 
 
 TH1F *hvr=new TH1F("hvr","",50,0,50);
 newt->Draw("sqrt(vx^2+vy^2)>>hvr",allbut_vr);
 TH1F *hvrC=new TH1F("hvrC","",50,0,50);
 newt->Draw("sqrt(vx^2+vy^2)>>hvrC",newbasic);
 hvr->SetFillColor(2);
 hvr->Draw();
 hvrC->SetFillColor(4);
 hvrC->Draw("SAME");
 //hvr->GetYaxis()->SetTitle("Events/cm");  
 hvr->GetXaxis()->SetTitle("vr (cm)"); 


 c1_2->cd(1);
 //TH1F *hmmkpkp_vr=new TH1F("hmmkpkp_vr","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_vr",allbut_vr&&!vr&&lamm);
 hmmkpkp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkp->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 
 hmmkpkp_vr->SetFillColor(2);
 hmmkpkp->SetFillColor(4);
 hmmkpkp->Draw(); 
 hmmkpkp_vr->Draw("SAME");



 c1_2->cd(2); 
 //TH1F *hmmkpkppim_vr=new TH1F("hmmkpkppim_vr","",40,0.9,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_vr",allbut_vr&&!vr&&casm);
 hmmkpkppim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkppim->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 hmmkpkppim_vr->SetFillColor(2);
 hmmkpkppim->SetFillColor(4);
 hmmkpkppim->Draw(); 
 hmmkpkppim_vr->Draw("SAME");


 c1->Print("~/clas/pics/11_nov11/proposal/g12/vr.eps");


 //*///------------------------------------------------------------------------------



 //=========================st============================
 // TCut st="abs(stv-scv)<1";

 /*

 TCut allbut_st=n&&np&&vcut&&beam&&tof1&&tof2;
 

 TCanvas *c2=new TCanvas("c2","",1200,800);
 c2->Divide(2,1);
 c2_2->Divide(1,2);
 c2->cd(1); 


 TH1F *hst=new TH1F("hst","",80,-2,6);
 newt->Draw("stv-scv>>hst",allbut_st);
 TH1F *hstC=new TH1F("hstC","",80,-2,6);
 newt->Draw("stv-scv>>hstC",newbasic);
 hst->SetFillColor(2);
 hst->Draw();
 hstC->SetFillColor(4);
 hstC->Draw("SAME");
 hst->GetYaxis()->SetTitle("Events/0.1*ns");  
 hst->GetXaxis()->SetTitle("stv-scv (ns)"); 
 


 c2_2->cd(1); // TCanvas *c2_MMcas=new TCanvas("c2_MMcas","",600,400);
 // TH1F *hmmkpkp_st=new TH1F("hmmkpkp_st","",40,1.1,1.5);
 //newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_st",allbut_st&&lamm);
 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_st",allbut_st&&!st&&lamm);
 hmmkpkp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkp->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 
 hmmkpkp_st->SetFillColor(2);
 hmmkpkp->SetFillColor(4);
 hmmkpkp->Draw(); 
 hmmkpkp_st->Draw("SAME");
 


 c2_2->cd(2); // TCanvas *c2_MMlam=new TCanvas("c2_MMlam","",600,400);
 // TH1F *hmmkpkppim_st=new TH1F("hmmkpkppim_st","",40,0.9,1.3);
 //newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_st",allbut_st&&casm);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_st",allbut_st&&!st&&lamm);
 hmmkpkppim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkppim->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 hmmkpkppim->SetFillColor(4);
 hmmkpkppim->Draw();
 hmmkpkppim_st->SetFillColor(2);
 hmmkpkppim_st->Draw("same"); 




c2->Print("~/clas/pics/11_nov11/proposal/g12/st.eps");


//*///-----------------------------------------------------------



 //=========================beam============================


 /*

 TCut allbut_beam=n&&np&&vcut&&st&&tof1&&tof2;
 
 TCanvas *c3=new TCanvas("c3","",1200,800);
 c3->Divide(2,1);
 c3_2->Divide(1,2);
 c3->cd(1); 

 TH1F *hbeam=new TH1F("hbeam","",120,0,6);
 newt->Draw("beam>>hbeam",allbut_beam);
 TH1F *hbeamC=new TH1F("hbeamC","",120,0,6);
 newt->Draw("beam>>hbeamC",newbasic);
 hbeam->SetFillColor(2);
 hbeam->Draw();
 hbeamC->SetFillColor(4);
 hbeamC->Draw("SAME");
 hbeam->GetYaxis()->SetTitle("Events/50MeV");  
 hbeam->GetXaxis()->SetTitle("E#gamma (GeV)"); 
 
 
 c3_2->cd(1);// TCanvas *c3_MMcas=new TCanvas("c3_MMcas","",600,400);
 // TH1F *hmmkpkp_beam=new TH1F("hmmkpkp_beam","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_beam",allbut_beam&&!beam&&lamm);
 hmmkpkp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkp->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 
 hmmkpkp_beam->SetFillColor(2);
 hmmkpkp->SetFillColor(4);
 hmmkpkp->Draw(); 
 hmmkpkp_beam->Draw("SAME");




 c3_2->cd(2);// TCanvas *c3_MMlam=new TCanvas("c3_MMlam","",600,400);
 //TH1F *hmmkpkppim_beam=new TH1F("hmmkpkppim_beam","",40,0.9,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_beam",allbut_beam&&!beam&&casm);
 hmmkpkppim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkppim->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 hmmkpkppim_beam->SetFillColor(2);
 hmmkpkppim->SetFillColor(4);
 hmmkpkppim->Draw(); 
 hmmkpkppim_beam->Draw("SAME");

c3->Print("~/clas/pics/11_nov11/proposal/g12/beam.eps");

//*///-----------------------------------------------------------



 //=========================tof1============================
// TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";

/*

 TCut allbut_tof1=n&&np&&vcut&&st&&beam&&tof2;
 
 TCanvas *c4a=new TCanvas("c4a","",1200,800);
 c4a->Divide(2,1);
 c4a_2->Divide(1,2);
 c4a->cd(1); 

 TH1F *htof1=new TH1F("htof1","",200,0,2.5);
 newt->Draw("(vtime-(sctkp1-sclkp1/(betakp1*29.99)))>>htof1",allbut_tof1);
 TH1F *htof1C=new TH1F("htof1C","",200,0,2.5);
 newt->Draw("(vtime-(sctkp1-sclkp1/(betakp1*29.99)))>>htof1C",newbasic);
 htof1->SetFillColor(2);
 htof1->Draw();
 htof1C->SetFillColor(4);
 htof1C->Draw("SAME");
 htof1->GetYaxis()->SetTitle("Events/0.0125*ns");  
 htof1->GetXaxis()->SetTitle("(t^{RF}_{vertex}-t^{TOF}_{vertex} ) (ns)"); 
 
 
 c4a_2->cd(1); // TCanvas *c4a_MMcas=new TCanvas("c4a_MMcas","",600,400);
 // TH1F *hmmkpkp_tof1=new TH1F("hmmkpkp_tof1","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_tof1",allbut_tof1&&!tof1&&lamm);
 hmmkpkp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkp->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 
 hmmkpkp_tof1->SetFillColor(2);
 hmmkpkp->SetFillColor(4);
 hmmkpkp->Draw(); 
 hmmkpkp_tof1->Draw("SAME");

 c4a_2->cd(2); // TCanvas *c4a_MMlam=new TCanvas("c4a_MMlam","",600,400);
 //TH1F *hmmkpkppim_tof1=new TH1F("hmmkpkppim_tof1","",40,0.9,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_tof1",allbut_tof1&&!tof1&&casm);
 hmmkpkppim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkppim->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 hmmkpkppim_tof1->SetFillColor(2);
 hmmkpkppim->SetFillColor(4);
 hmmkpkppim->Draw(); 
 hmmkpkppim_tof1->Draw("SAME");


c4a->Print("~/clas/pics/11_nov11/proposal/g12/tof1.eps");


//*///-----------------------------------------------------------




//=========================tof2============================
// TCut tof1="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4";

/*

 TCut allbut_tof2=n&&np&&vcut&&st&&beam&&tof1;
 
 TCanvas *c4b=new TCanvas("c4b","",1200,800);
 c4b->Divide(2,1);
 c4b_2->Divide(1,2);
 c4b->cd(1); 


 TH1F *htof2=new TH1F("htof2","",200,0,2.5);
 newt->Draw("(vtime-(sctkp2-sclkp2/(betakp2*29.99)))>>htof2",allbut_tof2);
 TH1F *htof2C=new TH1F("htof2C","",200,0,2.5);
 newt->Draw("(vtime-(sctkp2-sclkp2/(betakp2*29.99)))>>htof2C",newbasic);
 htof2->SetFillColor(2);
 htof2->Draw();
 htof2C->SetFillColor(4);
 htof2C->Draw("SAME");
 htof2->GetYaxis()->SetTitle("Events/0.0125*ns");  
 htof2->GetXaxis()->SetTitle("(t^{RF}_{vertex}-t^{TOF}_{vertex} ) (ns)"); 
 

 c4b_2->cd(1);// TCanvas *c4b_MMcas=new TCanvas("c4b_MMcas","",600,400);
 // TH1F *hmmkpkp_tof2=new TH1F("hmmkpkp_tof2","",40,1.1,1.5);
 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_tof2",allbut_tof2&&!tof2&&lamm);
 hmmkpkp->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkp->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 
 hmmkpkp_tof2->SetFillColor(2);
 hmmkpkp->SetFillColor(4);
 hmmkpkp->Draw(); 
 hmmkpkp_tof2->Draw("SAME");

 c4b_2->cd(2);// TCanvas *c4b_MMlam=new TCanvas("c4b_MMlam","",600,400);
 // TH1F *hmmkpkppim_tof2=new TH1F("hmmkpkppim_tof2","",40,0.9,1.3);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_tof2",allbut_tof2&&!tof2&&casm);
 hmmkpkppim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkppim->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
 hmmkpkppim_tof2->SetFillColor(2);
 hmmkpkppim->SetFillColor(4);
 hmmkpkppim->Draw(); 
 hmmkpkppim_tof2->Draw("SAME");


c4b->Print("~/clas/pics/11_nov11/proposal/g12/tof2.eps");

//*///-----------------------------------------------------------



 //============================cas=======================================

/*
 TCanvas *c5=new TCanvas("c5","",600,400);
 TH1F *hcas=new TH1F("hcas","",100,1,2);
 newt->Draw("sqrt(mm2kpkp)>>hcas",newbasic);
 TH1F *hcasC=new TH1F("hcasC","",100,1,2);
 newt->Draw("sqrt(mm2kpkp)>>hcasC",newbasic&&cas);
 hcas->SetFillColor(2);
 hcas->Draw();
 hcasC->SetFillColor(4);
 hcasC->Draw("SAME");
 hcas->GetYaxis()->SetTitle("Event/10MeV/c^{2}");  
 hcas->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})"); 




 //TCanvas *c5_MMlam=new TCanvas("c5_MMlam","",600,400);
 //TH1F *hmmkpkppim_cas=new TH1F("hmmkpkppim_cas","",60,0.9,1.5);
 //newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_cas",allbut_tof2&&casm);
 //hmmkpkppim_tof2->SetFillColor(2);
 //hmmkpkppim_tof2->Draw(); 
 //hmmkpkppim->SetFillColor(4);
 //hmmkpkppim->Draw("SAME");
 //hmmkpkppim_tof2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 //hmmkpkppim_tof2->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 



 //*///------------------------------------------------------------------------



//============================lam=======================================

/*
 TCanvas *c6=new TCanvas("c6","",600,400);
 TH1F *hlam=new TH1F("hlam","",100,1,2);
 newt->Draw("sqrt(mm2kpkppim)>>hlam",newbasic);
 TH1F *hlamC=new TH1F("hlamC","",100,1,2);
 newt->Draw("sqrt(mm2kpkppim)>>hlamC",newbasic&&lam);
 hlam->SetFillColor(2);
 hlam->Draw();
 hlamC->SetFillColor(4);
 hlamC->Draw("SAME");


 hlam->GetYaxis()->SetTitle("Event/10MeV/c^{2}");  
 hlam->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 


 //*///------------------------------------------------------------------------



 //============================casm=======================================
//TCut casm="abs(mlampim-1.321)<0.013";
/*
 TCanvas *c7=new TCanvas("c7","",600,400);
 TH1F *hcasm=new TH1F("hcasm","",100,1.25,1.75);
 newt->Draw("mlampim>>hcasm",newbasic);
 TH1F *hcasmC=new TH1F("hcasmC","",100,1.25,1.75);
 newt->Draw("mlampim>>hcasmC",newbasic&&casm);
 hcasm->SetFillColor(2);
 hcasm->Draw();
 hcasmC->SetFillColor(4);
 hcasmC->Draw("SAME");
 hcasm->GetYaxis()->SetTitle("Event/5MeV/c^{2}");  
 hcasm->GetXaxis()->SetTitle("M(#Lambda^{0}#pi^{-}) (GeV/c^{2})"); 


 TCanvas *c7_MMlam=new TCanvas("c7_MMlam","",600,400);
 TH1F *hmmkpkppim_casm=new TH1F("hmmkpkppim_casm","",60,0.9,1.5);
 newt->Draw("sqrt(mm2kpkppim)>>hmmkpkppim_casm",newbasic);
 hmmkpkppim_casm->SetFillColor(2);
 hmmkpkppim_casm->Draw(); 
 hmmkpkppim->SetFillColor(4);
 hmmkpkppim->Draw("SAME");
 hmmkpkppim_casm->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkppim_casm->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 


 c7->Print("~/clas/pics/11_nov11/proposal/casm.eps");
 c7_MMlam->Print("~/clas/pics/11_nov11/proposal/casm_lam.eps");

 //*///------------------------------------------------------------------------




 //============================lamm=======================================
 //TCut lamm="abs(mcasmMpim - 1.116)<0.01";
/*

 TCanvas *c8=new TCanvas("c8","",600,400);
 TH1F *hlamm=new TH1F("hlamm","",100,0.9,1.2);
 newt->Draw("mcasmMpim>>hlamm",newbasic);
 TH1F *hlammC=new TH1F("hlammC","",100,0.9,1.2);
 newt->Draw("mcasmMpim>>hlammC",newbasic&&lamm);
 hlamm->SetFillColor(2);
 hlamm->Draw();
 hlammC->SetFillColor(4);
 hlammC->Draw("SAME");
 hlamm->GetYaxis()->SetTitle("Event/3MeV/c^{2}");  
 hlamm->GetXaxis()->SetTitle("M(#Xi^{-} - #pi^{-}) (GeV/c^{2})"); 



 TCanvas *c8_MMcas=new TCanvas("c8_MMcas","",600,400);
 TH1F *hmmkpkp_lamm=new TH1F("hmmkpkp_lamm","",60,1.1,1.7);
 newt->Draw("sqrt(mm2kpkp)>>hmmkpkp_lamm",newbasic);
 hmmkpkp_lamm->SetFillColor(2);
 hmmkpkp_lamm->Draw(); 
 hmmkpkp->SetFillColor(4);
 hmmkpkp->Draw("SAME");
 hmmkpkp_lamm->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
 hmmkpkp_lamm->GetXaxis()->SetTitle("MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 


 // c8->Print("~/clas/pics/11_nov11/proposal/casm.eps");
 // c8_MMcas->Print("~/clas/pics/11_nov11/proposal/lamm_cas.eps");


 //*///------------------------------------------------------------------------














}
