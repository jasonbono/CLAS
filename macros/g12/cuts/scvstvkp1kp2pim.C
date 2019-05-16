

//jan 15 2012:  changed the cut conditions.  


//jan 11 2012:  made this to explore the effect messing with indivugual stv-scv particles has on the signal to background:





	void scvstvkp1kp2pim(){
	//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root");
	//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root");
	//TTree *newt = (TTree*)f->Get("g12ana_v15");
	TFile *f = TFile::Open("~/clas/rootfiles/g12/large/reserve/g12ana_v16_58090.root");
	TTree *newt = (TTree*)f->Get("g12ana_v16");

	gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS3.C");
	
	
	
	//============= this is from leis_beautify.C which i changed a bit========================
	//===============this is the final configuration that he used in his paper========
	 printf("Welcome to the ROOT\n");
	 gStyle->SetTitleXOffset(0.85);  //this: Xoff
	 gStyle->SetTitleYOffset(0.95);  //this:  Yoff
	 gStyle->SetTitleSize(0.07);  //this:    Xsize   
	 gStyle->SetTitleYSize(0.07); //this     Ysize
	 //gStyle->SetLabelFont(72);
	 gStyle->SetPadLeftMargin(0.19);   // this: Yaxis 
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
	
	

	
	
	// now to define the cuts charisterisc to this macro
	
	/* the old, slightly wrong cuts
	TCut goodkp1 = "abs(stvkp1 - scv)<1&&stvkp1 != 0";
	TCut goodkp2 = "abs(stvkp2 - scv)<1&&stvkp2 != 0";
	TCut goodpim = "abs(stvpim - scv)<1&&stvpim != 0";
	*/
	//also want to study to what effect stv!=0 has on the cas0 signal
	TCut goodstv = "stv != 0";
	

	// the new cuts which lei asked for	
	TCut goodkp1 = "(abs(stvkp1 - scv)<1 && stvkp1 != 0) || (stvkp1 == 0)";
	TCut goodkp2 = "(abs(stvkp2 - scv)<1 && stvkp2 != 0) || (stvkp2 == 0)";
	TCut goodpim = "(abs(stvpim - scv)<1 && stvpim != 0) || (stvpim == 0)";
	

	
	//===========================================================================================================================================
	// =============plot the Ξ0 from MM(kpkp) which has a pdg mass of (1321.71 ± 0.07) MeV and fit for several diffrent cuts.====================
	//===========================================================================================================================================
	
	// make the canvases
	TCanvas *cOriginal=new TCanvas("cOriginal","",1200,800);
	TCanvas *cstv=new TCanvas("cstv","",1200,800);
	TCanvas *ckp1=new TCanvas("ckp1","",1200,800);
	TCanvas *ckp2=new TCanvas("ckp2","",1200,800);
	TCanvas *cpim=new TCanvas("cpim","",1200,800);
	
	TCanvas *ckp1kp2=new TCanvas("c2kp1kp2","",1200,800);
	TCanvas *ckp1kp2pim=new TCanvas("ckp1kp2pim","",1200,800);
	
	
	// make the histograms
	TH1F *hOriginal=new TH1F("hOriginal","",35,1.15,1.5);
	TH1F *hstv=new TH1F("hstv","",35,1.15,1.5);
	TH1F *hkp1=new TH1F("hkp1","",35,1.15,1.5);
	TH1F *hkp2=new TH1F("hkp2","",35,1.15,1.5);
	TH1F *hpim=new TH1F("hpim","",35,1.15,1.5);
	
	TH1F *hkp1kp2=new TH1F("hkp1kp2","",35,1.15,1.5);
	TH1F *hkp1kp2pim=new TH1F("hkp1kp2pim","",35,1.15,1.5);
	
	
	// give titles to the hist axis
	hOriginal->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hOriginal->GetXaxis()->SetTitle("Original MM(K^{+}K^{+}) (GeV/c^{2})"); 
	hstv->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hstv->GetXaxis()->SetTitle("stv MM(K^{+}K^{+}) (GeV/c^{2})");
	hkp1->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp1->GetXaxis()->SetTitle("kp1 MM(K^{+}K^{+}) (GeV/c^{2})"); 
	hkp2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp2->GetXaxis()->SetTitle("kp2 MM(K^{+}K^{+}) (GeV/c^{2})");
	hpim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hpim->GetXaxis()->SetTitle("pim MM(K^{+}K^{+}) (GeV/c^{2})");
	
	hkp1kp2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp1kp2->GetXaxis()->SetTitle("kp1kp2 MM(K^{+}K^{+}) (GeV/c^{2})");
	hkp1kp2pim->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp1kp2pim->GetXaxis()->SetTitle("kp1kp2pim MM(K^{+}K^{+}) (GeV/c^{2})");
	
	
	

	//fill the hists plot with Ξ0 and fit it 
	newt->Draw("sqrt(mm2kpkp)>>hOriginal", newbasic&&lamm);
	newt->Draw("sqrt(mm2kpkp)>>hstv", newbasic&&lamm&&goodstv);
	newt->Draw("sqrt(mm2kpkp)>>hkp1", newbasic&&lamm&&goodkp1);
	newt->Draw("sqrt(mm2kpkp)>>hkp2", newbasic&&lamm&&goodkp2);
	newt->Draw("sqrt(mm2kpkp)>>hpim", newbasic&&lamm&&goodpim); 
	
	newt->Draw("sqrt(mm2kpkp)>>hkp1kp2", newbasic&&lamm&&goodkp1&&goodkp2);
	newt->Draw("sqrt(mm2kpkp)>>hkp1kp2pim", newbasic&&lamm&&goodkp1&&goodkp2&&goodpim);
	
		
	Double_t myBackground = 0.0;
	Double_t myYield = 0.0;
	Double_t myDummy = 0.0;
			
	
	cOriginal->cd();
	fitGAUS3(hOriginal,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	cstv->cd();
	fitGAUS3(hstv,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	ckp1->cd();
	fitGAUS3(hkp1,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);	
	
	ckp2->cd();
	fitGAUS3(hkp2,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	cpim->cd();
	fitGAUS3(hpim,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	ckp1kp2->cd();
	fitGAUS3(hkp1kp2,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	ckp1kp2pim->cd();
	fitGAUS3(hkp1kp2pim,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);	

	
	
	
	
	
	
//-------------------------------------------------------------------------------------------------	
//====================================end of plotting MMkpkp=======================================
//-------------------------------------------------------------------------------------------------	

	
	
	
	
	
	
	//==============================================================================================================================================
	// =============plot the Ξ0 from MM(kpkppim) which has a pdg mass of (1321.71 ± 0.07) MeV and fit for several diffrent cuts.====================
	//==============================================================================================================================================
	
	
	
	//-------FIRST RE-DEFINE THE CUTS  (taken from res1530sb.C)
	
	//=========================the most recent cuts as of nov22========================
	//need to relax a few cuts here after showing lei my overlay plots.
 	TCut n="np<2&&npip<1&&nkm<1";
 	TCut np="nphoton_nb1<2";
 	TCut vcut="abs(vz+90)<21&&sqrt(vx^2+vy^2)<8";  // relaxed this alot to allow for weak decays
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


 	TCut tof22="abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.5";
 	TCut tof12="abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.15"; // wont include tof1 cuts because it takes out to much signal.


 	TCut cas0="abs(sqrt(mm2kpkppim) - 1.3137)<0.0381";
 	TCut cas0sb="abs(sqrt(mm2kpkppim) - 1.25655)<0.01905  || abs(sqrt(mm2kpkppim) - 1.37085)<0.01905";
	
	
	
	
	
	
	
	
	// make the canvases
	TCanvas *cOriginalB=new TCanvas("cOriginalB","",1200,800);
	TCanvas *cstvB=new TCanvas("cstvB","",1200,800);
	TCanvas *ckp1B=new TCanvas("ckp1B","",1200,800);
	TCanvas *ckp2B=new TCanvas("ckp2B","",1200,800);
	TCanvas *cpimB=new TCanvas("cpimB","",1200,800);
	
	TCanvas *ckp1kp2B=new TCanvas("c2kp1kp2B","",1200,800);
	TCanvas *ckp1kp2pimB=new TCanvas("ckp1kp2pimB","",1200,800);
	
	
	// make the histograms
	TH1F *hOriginalB=new TH1F("hOriginalB","",35,1.15,1.5);
	TH1F *hstvB=new TH1F("hstvB","",35,1.15,1.5);
	TH1F *hkp1B=new TH1F("hkp1B","",35,1.15,1.5);
	TH1F *hkp2B=new TH1F("hkp2B","",35,1.15,1.5);
	TH1F *hpimB=new TH1F("hpimB","",35,1.15,1.5);
	
	TH1F *hkp1kp2B=new TH1F("hkp1kp2B","",35,1.15,1.5);
	TH1F *hkp1kp2pimB=new TH1F("hkp1kp2pimB","",35,1.15,1.5);
	
	
	// give titles to the hist axis
	hOriginalB->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hOriginalB->GetXaxis()->SetTitle("Original MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	hstvB->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hstvB->GetXaxis()->SetTitle("stv MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	hkp1B->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp1B->GetXaxis()->SetTitle("kp1 MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	hkp2B->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp2B->GetXaxis()->SetTitle("kp2 MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	hpimB->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hpimB->GetXaxis()->SetTitle("pim MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	
	hkp1kp2B->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp1kp2B->GetXaxis()->SetTitle("kp1kp2 MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	hkp1kp2pimB->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hkp1kp2pimB->GetXaxis()->SetTitle("kp1kp2pim MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");
	
	
	

	//fill the hists plot with Ξ0 and fit it 
	newt->Draw("sqrt(mm2kpkppim)>>hOriginalB", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12);
	newt->Draw("sqrt(mm2kpkppim)>>hstvB", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&goodstv);
	newt->Draw("sqrt(mm2kpkppim)>>hkp1B", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&goodkp1);
	newt->Draw("sqrt(mm2kpkppim)>>hkp2B", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&goodkp2);
	newt->Draw("sqrt(mm2kpkppim)>>hpimB", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&goodpim); 
	
	newt->Draw("sqrt(mm2kpkppim)>>hkp1kp2B", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&goodkp1&&goodkp2);
	newt->Draw("sqrt(mm2kpkppim)>>hkp1kp2pimB", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12&&goodkp1&&goodkp2&&goodpim);
	
		
		
		//Newt->Draw("sqrt(mm2kpkppim)>>h0", newbasic&&"beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12);
		//fitGAUS3(h0,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
		
		
	Double_t myBackground = 0.0;
	Double_t myYield = 0.0;
	Double_t myDummy = 0.0;
					
	cOriginalB->cd();
	fitGAUS3(hOriginalB,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	cstvB->cd();
	fitGAUS3(hstvB,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	ckp1B->cd();
	fitGAUS3(hkp1B,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);	
	
	ckp2B->cd();
	fitGAUS3(hkp2B,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	cpimB->cd();
	fitGAUS3(hpimB,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	ckp1kp2B->cd();
	fitGAUS3(hkp1kp2B,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	
	ckp1kp2pimB->cd();
	fitGAUS3(hkp1kp2pimB,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);	
	
	
	
	
	// print the canvases 
	cOriginal->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Original.eps");
	cstv->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Stv.eps");
	ckp1->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Kp1.eps");
	ckp2->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Kp2.eps");
	cpim->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Pim.eps");
	ckp1kp2->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Kp1Kp2.eps");
	ckp1kp2pim->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkp_Kp1Kp2Pim.eps");
	
	
	cOriginalB->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Original.eps");
	cstvB->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Stv.eps");
	ckp1B->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Kp1.eps");
	ckp2B->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Kp2.eps");
	cpimB->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Pim.eps");
	ckp1kp2B->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Kp1Kp2.eps");
	ckp1kp2pimB->Print("~/clas/pics/12_jan16/g12talk/timingstudy/MMkpkppim_Kp1Kp2Pim.eps");
	
	
	
	
	
	
	/*
	
	cOriginal->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Original.eps");
	cstv->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Stv.eps");
	ckp1->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp1.eps");
	ckp2->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp2.eps");
	cpim->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Pim.eps");
	ckp1kp2->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp1Kp2.eps");
	ckp1kp2pim->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp1Kp2Pim.eps");
	
	
	cOriginalB->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Original.eps");
	cstvB->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Stv.eps");
	ckp1B->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp1.eps");
	ckp2B->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp2.eps");
	cpimB->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Pim.eps");
	ckp1kp2B->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp1Kp2.eps");
	ckp1kp2pimB->Print("~/clas/pics/12_jan11/timingstudy/MMkpkp_Kp1Kp2Pim.eps");
	
	
	*/
	
	
	
	
	
	
	
	
	
	}