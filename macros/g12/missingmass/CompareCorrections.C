/*


Date: April 12 2012:  
Author: Jason Bono
Purpose: To Examine the effects of eloss ecor (and in the future pcor)



*/




void CompareCorrections()
{

	
	//load the fitter
	
	gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS4.C");


	TFile *f = TFile::Open("~/clas/rootfiles/g12/newbasic/v37k_full_newbasic.root");
	TTree *newt = (TTree*)f->Get("v37k_newbasic");

	
	//----------------------------the kf confidence cut---------------------------
	TCut conf = "kf_prob > 0.10";
	//---------------------------------------------------------------------------	
	
	//---------------------------------make it look good-------------------------
	printf("Welcome to the ROOT\n");
	gStyle->SetTitleXOffset(0.85);  //this: Xoff
	gStyle->SetTitleYOffset(0.95);  //this:  Yoff
	gStyle->SetTitleSize(0.06);  //this:    Xsize   
	gStyle->SetTitleYSize(0.06); //this     Ysize
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
	
	
		
	
	//----------------------------create the canvases/histos---------------------------------
	TH1F *histCas[4];
	TH1F *histLam[4];
	TCanvas *can[4];	
	char cname[4];
	char hnameCas[4];
	char hnameLam[4];

	// loop over canvases/histos
	for (int i = 0; i < 4; i++) 
	{
		// setup canvas name
		sprintf(cname, "can_%d", i);
		sprintf(hnameCas,"histCas_%d", i);
		sprintf(hnameLam,"histLam_%d", i);
		
		
		// create a new canvas with appropriate dimensions
		can[i] = new TCanvas(cname, cname, 1600, 1100);
		
		// divide it into subpads as needed
		can[i]->Divide(2, 0);   // columns and rows are integers as needed

		// create the histograms with approprate range and binning
		histCas[i] = new TH1F(hnameCas, "", 15, 1.25, 1.4);
		histLam[i] = new TH1F(hnameLam, "", 15, 1.05, 1.2);
		
		//lable the y axis			
		histCas[i] -> GetYaxis() -> SetTitle("Events/10MeV/c^{2}");
		histLam[i] -> GetYaxis() -> SetTitle("Events/10MeV/c^{2}");


		histCas[i] -> GetXaxis() -> SetTitle(" MM(k^{+} + k^{+})  (GeV/c^{2})");
		histLam[i] -> GetXaxis() -> SetTitle(" MM(k^{+} + k^{+} + #pi^{-})  (GeV (GeV/c^{2})");

	}
	
	
	// the variables passed from the fitter
	Double_t myBackground = 0.0;
	Double_t myYield = 0.0;
	Double_t myRms = 0.0;
	Double_t myMean = 0.0;
	
	
	// the array that i will fill with the results for diffrent fits
	Double_t meanCas[4] = 0;
	Double_t rmsCas[4] = 0;
	Double_t yieldCas[4] = 0;
	Double_t backgroundCas[4] = 0;
	Double_t meanLam[4] = 0;
	Double_t rmsLam[4] = 0;
	Double_t yieldLam[4] = 0;
	Double_t backgroundLam[4] = 0;
	
	
	// spit flavor on the canvas
	TLatex *txtL0=new TLatex(1.3, 400,"eloss&ecor");
	TLatex *txtL1=new TLatex(1.3, 400,"eloss");
	TLatex *txtL2=new TLatex(1.3, 400,"ecor");
	TLatex *txtL3=new TLatex(1.3, 400,"uncorrected");
	
	TLatex *txtR0=new TLatex(1.1, 400,"eloss&ecor");
	TLatex *txtR1=new TLatex(1.1, 400,"eloss");
	TLatex *txtR2=new TLatex(1.1, 400,"ecor");
	TLatex *txtR3=new TLatex(1.1, 400,"uncorrected");
	
			
	
	//=====================================================the mm plots========================================================
	
	//---------------------------with eloss and ecor------------------------------------
	

	can[0]->cd(1);
	newt->Draw("mmkpkp>>histCas_0",conf);
	fitGAUS4(histCas_0,1,1.25,1.4,1,0,0,1.32,0.045,3,myBackground,myYield,myRms,myMean);
	meanCas[0] = myMean;
	rmsCas[0] = myRms;
	yieldCas[0] = myYield; 
	backgroundCas[0] = myBackground;
	txtL0->Draw("SAME");
	
	can[0]->cd(2);
	newt->Draw("mmkpkppim>>histLam_0",conf);
	fitGAUS4(histLam_0,1,1.05,1.2,1,0,0,1.116,0.045,3,myBackground,myYield,myRms,myMean);
	meanLam[0] = myMean;
	rmsLam[0] = myRms;
	yieldLam[0] = myYield; 
	backgroundLam[0] = myBackground;
	txtR0->Draw("SAME");
	
	//-------------------------------with eloss----------------------------------------
	can[1]->cd(1);
	newt->Draw("mmkpkp_woecor>>histCas_1",conf);
	fitGAUS4(histCas_1,1,1.25,1.4,1,0,0,1.32,0.045,3,myBackground,myYield,myRms,myMean);
	meanCas[1] = myMean;
	rmsCas[1] = myRms;
	yieldCas[1] = myYield; 
	backgroundCas[1] = myBackground;
	txtL1->Draw("SAME");

	can[1]->cd(2);
	newt->Draw("mmkpkppim_woecor>>histLam_1",conf);
	fitGAUS4(histLam_1,1,1.05,1.2,1,0,0,1.116,0.045,3,myBackground,myYield,myRms,myMean);
	meanLam[1] = myMean;
	rmsLam[1] = myRms;
	yieldLam[1] = myYield; 
	backgroundLam[1] = myBackground;
	txtR1->Draw("SAME");
	
	//---------------------------------with ecor---------------------------------------
	can[2]->cd(1);
	newt->Draw("mmkpkp_woeloss>>histCas_2",conf);
	fitGAUS4(histCas_2,1,1.25,1.4,1,0,0,1.32,0.045,3,myBackground,myYield,myRms,myMean);
	meanCas[2] = myMean;
	rmsCas[2] = myRms;
	yieldCas[2] = myYield; 
	backgroundCas[2] = myBackground;
	txtL2->Draw("SAME");	
	
	can[2]->cd(2);
	newt->Draw("mmkpkppim_woeloss>>histLam_2",conf);
	fitGAUS4(histLam_2,1,1.05,1.2,1,0,0,1.116,0.045,3,myBackground,myYield,myRms,myMean);
	meanLam[2] = myMean;
	rmsLam[2] = myRms;
	yieldLam[2] = myYield; 
	backgroundLam[2] = myBackground;
	txtR2->Draw("SAME");	
	
	//-------------------------------with nothing--------------------------------------
	can[3]->cd(1);
	newt->Draw("mmkpkp_woecoreloss>>histCas_3",conf);
	fitGAUS4(histCas_3,1,1.25,1.4,1,0,0,1.32,0.045,3,myBackground,myYield,myRms,myMean);
	meanCas[3] = myMean;
	rmsCas[3] = myRms;
	yieldCas[3] = myYield; 
	backgroundCas[3] = myBackground;
	txtL3->Draw("SAME");	
	
	can[3]->cd(2);
	newt->Draw("mmkpkppim_woecoreloss>>histLam_3",conf);
	fitGAUS4(histLam_3,1,1.05,1.2,1,0,0,1.116,0.045,3,myBackground,myYield,myRms,myMean);
	meanLam[3] = myMean;
	rmsLam[3] = myRms;
	yieldLam[3] = myYield; 
	backgroundLam[3] = myBackground;
	txtR3->Draw("SAME");	
	
	//=================================================================================================================
	
	
	//
	cout << "" <<endl;
	cout << "-------------------------------------------LAMBDA----------------------------------------------" <<endl;
	cout << "LAMBDA: eloss & ecor: mean - 1.115683 = " << meanLam[0] - 1.115683 << " : rms =  " << rmsLam[0] << " : yield = " << yieldLam[0] << endl;
	cout << "LAMBDA: eloss       : mean - 1.115683 = " << meanLam[1] - 1.115683 << " : rms =  " << rmsLam[1] << " : yield = " << yieldLam[1] << endl;  
	cout << "LAMBDA: ecor        : mean - 1.115683 = " << meanLam[2] - 1.115683 << " : rms =  " << rmsLam[2] << " : yield = " << yieldLam[2] << endl;
	cout << "LAMBDA: uncorected  : mean - 1.115683 = " << meanLam[1] - 1.115683 << " : rms =  " << rmsLam[1] << " : yield = " << yieldLam[3] << endl;
	
	cout << "" <<endl;
	cout << "-------------------------------------------CASCADE----------------------------------------------" <<endl;
	cout << "CAS: eloss & ecor: mean - 1.32131 = " << meanCas[0] - 1.32131 << " : rms =  " << rmsCas[0] << " : yield = " << yieldCas[0] << endl;
	cout << "CAS: eloss       : mean - 1.32131 = " << meanCas[1] - 1.32131 << " : rms =  " << rmsCas[1] << " : yield = " << yieldCas[1] << endl;  
	cout << "CAS: ecor        : mean - 1.32131 = " << meanCas[2] - 1.32131 << " : rms =  " << rmsCas[2] << " : yield = " << yieldCas[2] << endl;
	cout << "CAS: uncorected  : mean - 1.32131 = " << meanCas[1] - 1.32131 << " : rms =  " << rmsCas[1] << " : yield = " << yieldCas[3] << endl;
	
	
	
	
	
	
	
	
	
	
}