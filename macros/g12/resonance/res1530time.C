
/*

jan 9 2012: made this script to show the ~ and MM plots of K+ K+ with the out of time events hist overlayed.



*/


	void res1530time(){
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
//====================================================================

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


	TCut stout="abs(stv-scv)>1.5";
	TCut xtra = "beam>3.6&&sqrt(mm2kpkp)>1.35&&(vx^2+vy^2)<3"&&tof22&&tof12;

	TCut resonate = xtra&&n&&np&&st;
	TCut resonateBUTst = xtra&&n&&np;









	//----------------------------------------------------------------------------------
	//newt->Draw(">>basiclist", newbasic);
	//TEventList *list=(TEventList *)gDirectory->Get("basiclist");
	//newt->SetEventList(list);

	TCanvas *cT=new TCanvas("cT","",1200,800);
	TH1F *hT=new TH1F("hT","",60,-1,5);  
	TH1F *hTin=new TH1F("hTin","",60,-1,5);
	TH1F *hTout=new TH1F("hTout","",60,-1,5);
	newt->Draw("abs(stv - scv)>>hTin",resonate);
	newt->Draw("abs(stv - scv)>>hTout",resonateBUTst&&stout);
	hTin->GetYaxis()->SetTitle("Events/100 ps");  
	hTin->GetXaxis()->SetTitle("abs(stv - scv) (ns)");

	hTin->Draw();
	hTout->SetFillColor(2);
	hTout->SetFillStyle(3004);
	hTout->Draw("same");

	cout << "the number of entries within 1ns: " << hTin->GetEntries() << endl;
	cout << "the integral of the hist within 1ns: " << hTin->Integral() << endl;

	cout << "the number of entries outside of 1.5ns: " << hTout->GetEntries() << endl;
	cout << "the integral of the hist outside of 1.5ns: " << hTout->Integral() << endl;

	//Double_t fac = (hTin->Integral())/(hTout->Integral());
	//cout << "the normalization factor fac=" << fac << endl;
	// so stupid, the fac is wrong!


	// -------------------------------------now to plot the Ξ0  at 1314 mev and get the normalisaation factor---------------------------------------------
	TCanvas *cCas0=new TCanvas("cCas0","1",1200,800);
	 
	TH1F *hCas0inT=new TH1F("hCas0inT","",35,1.15,1.5);
	TH1F *hCas0outT=new TH1F("hCas0outT","",35,1.15,1.5);
	TH1F *hCas0outTnorm=new TH1F("hCas0outTnorm","",35,1.15,1.5);
	TH1F *hCas0sub=new TH1F("hCas0sub","",35,1.15,1.5);
	 
	hCas0inT->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hCas0inT->GetXaxis()->SetTitle("Overlay MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})"); 
	hCas0sub->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hCas0sub->GetXaxis()->SetTitle("Subtracted  MM(K^{+}K^{+}#pi^{-}) (GeV/c^{2})");


	newt->Draw("sqrt(mm2kpkppim)>>hCas0inT", resonate);
    newt->Draw("sqrt(mm2kpkppim)>>hCas0outT", resonateBUTst&&stout);
	hCas0inT->Draw();
	
	
	// getting the background for the norm factor
	Double_t myBackground = 0.0;
	Double_t myYield = 0.0;
	Double_t myDummy = 0.0;
	fitGAUS3(hCas0inT,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground, myYield, myDummy);
	// the normalization factor is calculated
	Double_t fac = myBackground / hCas0outT->GetEntries();
	
	//now normalize the out of time cas0 plot, make it red, and superimpose it
	hCas0outTnorm->Add(hCas0outT, fac);
	hCas0outTnorm->SetFillColor(2);
	hCas0outTnorm->SetFillStyle(3004);
	hCas0outTnorm->Draw("same");
	

	
	//now subtract the backround fit again, and plot on new canvas
	hCas0sub->Add(hCas0inT, 1);
	hCas0sub->Add(hCas0outTnorm, -1);
	TCanvas *cCas0subFit=new TCanvas("cCas0subFit","2",1200,800);
	hCas0sub->Draw();
	Double_t myBackground2 = 0.0;
	Double_t myYield2 = 0.0;
	Double_t myDummy2 = 0.0;
	fitGAUS3(hCas0sub,1,1.15,1.5,1,1,1,1.321,0.02,3, myBackground2, myYield2, myDummy2);
	



	// here is just a check to make sure the normalization factor is calculated properly

	cout << "=========================================================================" << endl;
	cout << "the number of entries out side of 1.5ns: " << hTout->GetEntries() << endl;
	cout << " myBackground: " << myBackground << endl;
	cout << " fac = myBackground/# of entries outside of 1.5 ns  " << fac << endl;
	cout << " the number of entries in the hCas0inT is  " << hCas0inT->GetEntries() << endl;
	cout << " the number of entries in the hCas0outT is  " << hCas0outT->GetEntries() << endl;
	cout << " the number of entries in the hCas0outTnorm is  " << hCas0outTnorm->GetEntries() << endl;
	cout << " the number of entries in the hCas0sub is  " << hCas0sub->GetEntries() << endl;
	cout << "--------------------now the integral method----------------------" << endl;
	cout << " the number of entries in the hCas0inT is (integral)  " << hCas0inT->Integral() << endl;
	cout << " the number of entries in the hCas0outT is (integral)  " << hCas0outT->Integral() << endl;
	cout << " the number of entries in the hCas0outTnorm is (integral) " << hCas0outTnorm->Integral() << endl;
	cout << " the number of entries in the hCas0sub is (integral) " << hCas0sub->Integral() << endl;


	cout << "=========================================================================" << endl;

	// --------------------------------------------now to plot the Ξ-  at various resonances (1530, 1620, 1690, etc)---------------------------------------------
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ the ~ spectrum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TCanvas *cCasm=new TCanvas("cCasm","",1200,800);
	
	TH1F *hCasminT=new TH1F("hCasminT","",60,1.4,2);
	TH1F *hCasmoutT=new TH1F("hCasmoutT","",60,1.4,2);
	TH1F *hCasmoutTnorm=new TH1F("hCasmoutTnorm","",60,1.4,2);
	TH1F *hCasmsub=new TH1F("hCasmsub","",60,1.4,2);
	
	
	hCasminT->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hCasminT->GetXaxis()->SetTitle("Overlay M(#pi^{-}#Xi^{0}) (GeV/c^{2})");
	hCasmsub->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hCasmsub->GetXaxis()->SetTitle("Subtracted  M(#pi^{-}#Xi^{0}) (GeV/c^{2})");

	newt->Draw("mcaspim>>hCasminT", resonate&&cas0);
    newt->Draw("mcaspim>>hCasmoutT", resonateBUTst&&stout&&cas0);	
	
	hCasmoutTnorm->Add(hCasmoutT,fac);
	hCasminT->Draw();
	hCasmoutTnorm->SetFillColor(2);
	hCasmoutTnorm->SetFillStyle(3004);
	hCasmoutTnorm->Draw("same");
	
	//now subtract the backround and plot on new canvas
	hCasmsub->Add(hCasminT,1);
	hCasmsub->Add(hCasmoutTnorm,-1);
	TCanvas *cCasmsub=new TCanvas("cCasmsub","",1200,800);
	hCasmsub->Draw();
	
	
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ the MM spectrum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TCanvas *cCasm2=new TCanvas("cCasm2","",1200,800);
	
	TH1F *hCasminT2=new TH1F("hCasminT2","",60,1.4,2);
	TH1F *hCasmoutT2=new TH1F("hCasmoutT2","",60,1.4,2);
	TH1F *hCasmoutTnorm2=new TH1F("hCasmoutTnorm2","",60,1.4,2);
	TH1F *hCasmsub2=new TH1F("hCasmsub2","",60,1.4,2);
	
	
	hCasminT2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hCasminT2->GetXaxis()->SetTitle("Overlay MM(K^{+}K^{+}) (GeV/c^{2})");
	hCasmsub2->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	hCasmsub2->GetXaxis()->SetTitle("Subtracted MM(K^{+}K^{+}) (GeV/c^{2})");

	newt->Draw("sqrt(mm2kpkp)>>hCasminT2", resonate&&cas0);
    newt->Draw("sqrt(mm2kpkp)>>hCasmoutT2", resonateBUTst&&stout&&cas0);	
	
	hCasmoutTnorm2->Add(hCasmoutT2,fac);
	hCasminT2->Draw();
	hCasmoutTnorm2->SetFillColor(2);
	hCasmoutTnorm2->SetFillStyle(3004);
	hCasmoutTnorm2->Draw("same");
	
	//now subtract the backround and plot on new canvas
	hCasmsub2->Add(hCasminT2,1);
	hCasmsub2->Add(hCasmoutTnorm2,-1);
	TCanvas *cCasmsub2=new TCanvas("cCasmsub2","",1200,800);
	hCasmsub2->Draw();
	
	//print everything
	cT->Print("~/clas/pics/12_jan16/g12talk/restime/time.eps");
	cCas0->Print("~/clas/pics/12_jan16/g12talk/restime/mmkpkppimFitOverlay.eps");
	cCas0subFit->Print("~/clas/pics/12_jan16/g12talk/restime/mmkpkppimFitSubtraction.eps");
	cCasm->Print("~/clas/pics/12_jan16/g12talk/restime/mmkpkppimOverlay.eps");
	cCasmsub->Print("~/clas/pics/12_jan16/g12talk/restime/mmkpkppimSubtraction.eps");
	cCasm2->Print("~/clas/pics/12_jan16/g12talk/restime/mXipimOverlay.eps");
	cCasmsub2->Print("~/clas/pics/12_jan16/g12talk/restime/mXipimSubtraction.eps");
	
	}