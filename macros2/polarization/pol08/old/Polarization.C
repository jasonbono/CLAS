/*

Name: Polarization.C
Author: Jason Bono
Date: October 22 2012
Purpose: To calculate polarization by plotting the acceptance corrected yeilds as a function of PION-ANGLE in bins of BEAM-ENERGY and XiCM-ANGLE. 

Usage: make sure the W vector is set to correct initalization. 


Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events

*/

void Polarization()
{
	//how many energy bins
	const Int_t NEBins = 3; // this is how many energy bins the Ws were calculated for in GetW.C
	const int AngleBins = 4;
	
	//declare the weighting which came from the output of GetW.C
	if(NEBins == 11){
		const Double_t W[NEBins] = {1.0504, 0.987805, 0.896063, 0.844184, 1.62447, 4.97581, 5.41732, 5.63043, 24.2391, 11.9118, 6.14159};
		const Double_t Werr[NEBins] = {0.842261, 0.127849, 0.679423, 1.83705, 1.24198, 18.8862, 12.7916, 9.38288, 67.3071, 50.4213, 12.9717};
	}
	if(NEBins == 3){
		const Double_t W[NEBins] =	{0.225431, 0.329841, 0.962296};
		const Double_t Werr[NEBins] =	{0.0083008, 0.0127671, 0.0616886};	
	}
	
	

	

	
	//define strings for cuts and for naming
	if(NEBins == 11){
		TString beam[NEBins];
		beam[0] = "beam > 3.3 && beam < 3.5 ";
		beam[1] = "beam > 3.5 && beam < 3.7 ";
		beam[2] = "beam > 3.7 && beam < 3.9 ";
		beam[3] = "beam > 3.9 && beam < 4.1 ";
		beam[4] = "beam > 4.1 && beam < 4.3 ";
		beam[5] = "beam > 4.3 && beam < 4.5 ";
		beam[6] = "beam > 4.5 && beam < 4.7 ";
		beam[7] = "beam > 4.7 && beam < 4.9 ";
		beam[8] = "beam > 4.9 && beam < 5.1 ";
		beam[9] = "beam > 5.1 && beam < 5.3 ";
		beam[10] = "beam > 5.3 && beam < 5.5";
	
		TString name[NEBins];
		name[0] = "3.3  > beam > 3.5";
		name[1] = "3.5  > beam > 3.7";
		name[2] = "3.7  > beam > 3.9";
		name[3] = "3.9  > beam > 4.1";
		name[4] = "4.1  > beam > 4.3";
		name[5] = "4.3  > beam > 4.5";
		name[6] = "4.5  > beam > 4.7";
		name[7] = "4.7  > beam > 4.9";
		name[8] = "4.9  > beam > 5.1";
		name[9] = "5.1  > beam > 5.3";
		name[10] = "5.3  > beam > 5.5";
	}
	if(NEBins == 3){
		TString beam[NEBins];
		beam[0] = "beam > 3.3 && beam < 4.0 ";
		beam[1] = "beam > 4.0 && beam < 4.7 ";
		beam[2] = "beam > 4.7 && beam < 5.4 ";
	
		TString name[NEBins];
		name[0] = "3.3  > beam > 3.65";
		name[1] = "3.65  > beam > 4.0";
		name[2] = "4.0  > beam > 4.35";		
	}	

	
	
	//
	const int NdisplayBins = 5;
	TString binXcm[NdisplayBins];
	binXcm[0] = "Xcmtheta > -1.0 && Xcmtheta < -0.6";
	binXcm[1] = "Xcmtheta > -0.6 && Xcmtheta < -0.2";
	binXcm[2] = "Xcmtheta > -0.2 && Xcmtheta < 0.2";
	binXcm[3] = "Xcmtheta > 0.2 && Xcmtheta < 0.6";
	binXcm[4] = "Xcmtheta > 0.6 && Xcmtheta < 1.0";
	
	TString binXcmTitle[NdisplayBins];
	binXcmTitle[0] = "-1.0 < Xcmtheta < -0.6";
	binXcmTitle[1] = "-0.6 < Xcmtheta < -0.2";
	binXcmTitle[2] = "-0.2 < Xcmtheta < 0.2";
	binXcmTitle[3] = "0.2 < Xcmtheta < 0.6";
	binXcmTitle[4] = "0.6 < Xcmtheta < 1.0";
	
	
	//conf cut
 	TCut conf = "kf_prob > 0.50";

	
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
 	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v01.root");     // DATA histograms
 	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC_i1_2kppim.root");         // MC histograms
 	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/MC_i1_gamp.root");       // GEN histograms 

 	// make aliases for the trees from each file
 	TTree *tData = (TTree*)fData->Get("v01_Basic");
 	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");
 	TTree *tGen = (TTree*)fGen->Get("GampTree");

 	// - - - - - -  if the histograms are already stored in the root files, read the same histogram from each file - - - - - - - -
 	//TH1F* hData = (TH1F*)fData->Get("v37k_newbasic")->Clone("data_electron_neg_q2_bin1");
 	//TH1F* hMC = (TH1F*)fMC->Get("v37k")->Clone("mc_electron_neg_q2_bin1");
 	//TH1F* hGen = (TH1F*)fGen->Get("electron_neg_q2_bin1")->Clone("gen_electron_neg_q2_bin1");


	//setup 3 histogram models to clone.
	TH1F *hAnglesX = new TH1F("hAnglesX","",AngleBins, -1,1);
	hAnglesX->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");
	hAnglesX->GetYaxis()->SetTitle("Counts");
	hAnglesX->SetMinimum(0);
	hAnglesX->SetMarkerStyle(21);
	TH1F *AnglesY = (TH1F*)hAnglesX->Clone("hAnglesY");
	hAnglesY->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
	TH1F *AnglesZ = (TH1F*)hAnglesX->Clone("hAnglesZ");
	hAnglesZ->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");


	//declarations
	Double_t EventsData = 0;
	Double_t EventsMC = 0;
	Double_t EventsMCXw = 0;
	Double_t EventsGen = 0;
	Double_t EventsGenw = 0;
	Double_t FacMC = 0;
	Double_t FacGen = 0;
	//-----------------------------------------------Data-----------------------------------------------
	
	//declareations
	TCanvas *cData[NEBins][NdisplayBins];
	TH1F *hDataX[NEBins][NdisplayBins];
 	TH1F *hDataY[NEBins][NdisplayBins];
 	TH1F *hDataZ[NEBins][NdisplayBins];

	TCanvas *cDataTotal[NdisplayBins];
	TH1F *hDataXtotal[NdisplayBins]; 
	TH1F *hDataYtotal[NdisplayBins]; 
	TH1F *hDataZtotal[NdisplayBins]; 

	//loop over the Xcmtheta bins
	for (int j = 0; j < NdisplayBins; j++)
	{
		hDataXtotal[j] = (TH1F*)hAnglesX->Clone(Form("hDataXtotal_XcmBin_%i",j));
		hDataYtotal[j] = (TH1F*)hAnglesY->Clone(Form("hDataYtotal_XcmBin_%i",j));
		hDataZtotal[j] = (TH1F*)hAnglesZ->Clone(Form("hDataZtotal_XcmBin_%i",j));
	
		for (int i = 0; i < NEBins; i++)
		{
		
			//setup the canvas
			cData[i][j] = new TCanvas(Form("cData%i_%i",i,j),Form("cData%i_%i",i,j),300,100);
 			cData[i][j]->Divide(3,0);
		
			//initiize the histograms
			hDataX[i][j] = (TH1F*)hAnglesX->Clone(Form("hDataX%i_%i",i,j));
			hDataY[i][j] = (TH1F*)hAnglesY->Clone(Form("hDataY%i_%i",i,j));
			hDataZ[i][j] = (TH1F*)hAnglesZ->Clone(Form("hDataZ%i_%i",i,j));
 		
			//fill the histograms
			cData[i][j]->cd(1);
 			tData->Draw(Form("COS_pi_x>>hDataX%i",i),conf&&beam[i]&&binXcm[j],"E");
 			cData[i][j]->cd(2); 
 			tData->Draw(Form("COS_pi_y>>hDataY%i",i),conf&&beam[i]&&binXcm[j],"E");
 			cData[i][j]->cd(3); 
 			tData->Draw(Form("COS_pi_z>>hDataZ%i",i),conf&&beam[i]&&binXcm[j],"E");
		
			//add the histograms
			hDataXtotal[j]->Add(hDataX[i][j],1);
			hDataYtotal[j]->Add(hDataY[i][j],1);
			hDataZtotal[j]->Add(hDataZ[i][j],1);
		}
	
		//draw the added histograms
		cDataTotal[j] = new TCanvas(Form("cDataTotal_%i",j),Form("cDataTotal_%i",j),1000,500);
		cDataTotal[j]->Divide(3,0);
		cDataTotal[j]->cd(1);
		hDataXtotal[j]->SetMinimum(0);	hDataXtotal[j]->Draw("E");
		cDataTotal[j]->cd(2);
		hDataYtotal[j]->SetMinimum(0);	hDataYtotal[j]->Draw("E");
		cDataTotal[j]->cd(3);
		hDataZtotal[j]->SetMinimum(0);	hDataZtotal[j]->Draw("E");
	}
	
	//*
		//-----------------------------------------------------MC------------------------------------------------------
		
		//declarations
		TCanvas *cMC[NEBins];
		TH1F *hMCX[NEBins];
	 	TH1F *hMCY[NEBins];
	 	TH1F *hMCZ[NEBins];
		TH1F *hMCXtotal = (TH1F*)hAnglesX->Clone("hMCXtotal");
		TH1F *hMCYtotal = (TH1F*)hAnglesY->Clone("hMCYtotal");
		TH1F *hMCZtotal = (TH1F*)hAnglesZ->Clone("hMCZtotal");
		for (int i = 0; i < NEBins; i++){

			//setup the canvas
			cMC[i] = new TCanvas(Form("cMC%i",i),Form("cMC%i",i),300,100);
	 		cMC[i]->Divide(3,0);

			//initize the histograms
	 		hMCX[i] = (TH1F*)hAnglesX->Clone(Form("hMCX%i",i));
	 		hMCY[i] = (TH1F*)hAnglesY->Clone(Form("hMCY%i",i));
	 		hMCZ[i] = (TH1F*)hAnglesZ->Clone(Form("hMCZ%i",i));

			//fill the histograms
			cMC[i]->cd(1);
	 		tMC->Draw(Form("COS_pi_x>>hMCX%i",i),conf&&beam[i],"E");
	 		cMC[i]->cd(2); 
	 		tMC->Draw(Form("COS_pi_y>>hMCY%i",i),conf&&beam[i],"E");
	 		cMC[i]->cd(3); 
	 		tMC->Draw(Form("COS_pi_z>>hMCZ%i",i),conf&&beam[i],"E");

			//add the histograms with weights
			hMCXtotal->Add(hMCX[i],W[i]);
			hMCYtotal->Add(hMCY[i],W[i]);
			hMCZtotal->Add(hMCZ[i],W[i]);
			
			//sum the entries up from the indivigual histograms
			EventsMC = EventsMC + hMCX[i]->GetEntries();
			cout << "EventsMC = " << EventsMC <<endl;
			cout <<endl; 
		}
		
		
		//normalize so that the weights in the sumation has no effect on the amount of events in the added hists
		EventsMCw = hMCXtotal->GetEntries();
		FacMC = EventsMC/EventsMCw - 1;
		hMCXtotal->Add(hMCXtotal,FacMC);
		hMCYtotal->Add(hMCYtotal,FacMC);
		hMCZtotal->Add(hMCZtotal,FacMC);
		cout << "----------"<<endl;
		cout << "EventsMC = " << EventsMC << "  EventsMCw = " << EventsMCw << "  FacMC = " << FacMC <<endl;

		//draw the total histograms
		TCanvas *cMCTotal = new TCanvas("cMCTotal","cMCTotal",1000,500);
		cMCTotal->Divide(3,0);
		cMCTotal->cd(1);
		hMCXtotal->SetMinimum(0);	hMCXtotal->Draw("E");
		cMCTotal->cd(2);
		hMCYtotal->SetMinimum(0);	hMCYtotal->Draw("E");
		cMCTotal->cd(3);
		hMCZtotal->SetMinimum(0); 	hMCZtotal->Draw("E");




		//-----------------------------------------------------Gen------------------------------------------------------
		
		//declarations
		TCanvas *cGen[NEBins];	
		TH1F *hGenX[NEBins];
	 	TH1F *hGenY[NEBins];
	 	TH1F *hGenZ[NEBins];
		TH1F *hGenXtotal = (TH1F*)hAnglesX->Clone("hGenXtotal");
		TH1F *hGenYtotal = (TH1F*)hAnglesY->Clone("hGenYtotal");
		TH1F *hGenZtotal = (TH1F*)hAnglesZ->Clone("hGenZtotal");

		for (int i = 0; i < NEBins; i++){
			
			//setup the canvase
			cGen[i] = new TCanvas(Form("cGen%i",i),Form("cGen%i",i),300,100);
	 		cGen[i]->Divide(3,0);
			
			//initize the histograms
	 		hGenX[i] = (TH1F*)hAnglesX->Clone(Form("hGenX%i",i));
	 		hGenY[i] = (TH1F*)hAnglesY->Clone(Form("hGenY%i",i));
	 		hGenZ[i] = (TH1F*)hAnglesZ->Clone(Form("hGenZ%i",i));

		 	//fill the histograms
			cGen[i]->cd(1);
			hGenX[i]->Draw("E");
	 		tGen->Draw(Form("COS_pi_x>>hGenX%i",i),beam[i],"E");
	 		cGen[i]->cd(2);
			hGenY[i]->Draw("E");
	 		tGen->Draw(Form("COS_pi_y>>hGenY%i",i),beam[i],"E");
	 		cGen[i]->cd(3);
			hGenZ[i]->Draw("E");
	 		tGen->Draw(Form("COS_pi_z>>hGenZ%i",i),beam[i],"E");

			//add the histograms	
			hGenXtotal->Add(hGenX[i],W[i]);
			hGenYtotal->Add(hGenY[i],W[i]);
			hGenZtotal->Add(hGenZ[i],W[i]);
			
			//sum the entries up from the indivigual histograms
			EventsGen = EventsGen + hGenX[i]->GetEntries();
			cout << "EventsGen = " << EventsGen <<endl;
			cout <<endl;
		}
		
		
		//normalize so that the weights in the sumation has no effect on the amount of events in the added hists
		EventsGenw = hGenXtotal->GetEntries();
		FacGen = EventsGen/EventsGenw - 1;
		hGenXtotal->Add(hGenXtotal,FacGen);
		hGenYtotal->Add(hGenYtotal,FacGen);
		hGenZtotal->Add(hGenZtotal,FacGen);
		cout << "----------"<<endl;
		cout << "EventsGen = " << EventsGen << "  EventsGenw = " << EventsGenw << "  FacGen = " << FacGen <<endl;

		//draw the total histograms
		TCanvas *cGenTotal = new TCanvas("cGenTotal","cGenTotal",1000,500);
		cGenTotal->Divide(3,0);
		cGenTotal->cd(1);
		hGenXtotal->SetMinimum(0);	hGenXtotal->Draw("E");
		cGenTotal->cd(2);
		hGenYtotal->SetMinimum(0);	hGenYtotal->Draw("E");
		cGenTotal->cd(3);
		hGenZtotal->SetMinimum(0); 	hGenZtotal->Draw("E");


 	// ==================================================================================================================


	//draw the data and mc overlay
	
	TCanvas *cOverlay=new TCanvas("cOverlay","Overlay",1400,800);
	cOverlay->Divide(3,0);
	cOverlay->cd(1);
	hMCXtotal->SetMarkerColor(2);
	hMCXtotal->SetMarkerStyle(20);
	hDataXtotal->Draw("e1p");
	hMCXtotal->Draw("SAMEe1p");
	cOverlay->cd(2);
	hMCYtotal->SetMarkerColor(2);
	hMCYtotal->SetMarkerStyle(20);
	hMCYtotal->Draw("e1p");
	hDataYtotal->Draw("SAMEe1p");
	cOverlay->cd(3);
	hMCZtotal->SetMarkerColor(2);
	hMCZtotal->SetMarkerStyle(20);
	hMCZtotal->Draw("e1p");
	hDataZtotal->Draw("SAMEe1p");
	


 	//------------------- create a new acceptance histogram---------------------
 	//------------- from a clone of either of the three histograms above---------
 	//---------- the binning should be the same for all histograms above
 	TH1F* accX = (TH1F*)hAnglesX->Clone("accX");
 	TH1F* accY = (TH1F*)hAnglesY->Clone("accY");
 	TH1F* accZ = (TH1F*)hAnglesZ->Clone("accZ");

 	//---------------------setup the histogram to calculate---------------------- 
 	//----------errors automatically (helpful for weighted events)----------------
 	accX->Sumw2();
 	accY->Sumw2(); 
 	accZ->Sumw2();

 	// ------------------------------divide MC by gen to obtain acceptance ----------------------------
 	// ------------------------the acceptance for each bin should be < 1. If it isn't, ----------------
	//-------------------------------- then there is an error somewhere. -------------------------------
 	accX->Divide(hMCXtotal, hGenXtotal);
 	accY->Divide(hMCYtotal, hGenYtotal);
 	accZ->Divide(hMCZtotal, hGenZtotal);

 	//---------------------------------You can set the errors-----------------------------------------
 	//-----------------------for each bin of your acceptance explicitly-------------------------------
 	//-------------------------because GEN and MC events are correlated------------------------------
 
	for (Int_t i = 1; i <= accX->GetNbinsX(); i++) 
 	{
 		Double_t a = hMCXtotal->GetBinContent(i);
		Double_t b = hGenXtotal->GetBinContent(i);
		Double_t f = a/b;
		//cout << "X: "<<"i = "<< i <<"  Bins = "<< accX->GetNbinsX() <<"  a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
  		Double_t errorX = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or acc = hMC/hGen
    	accX->SetBinError(i, errorX);


		Double_t a = hMCYtotal->GetBinContent(i);
		Double_t b = hGenYtotal->GetBinContent(i);
		Double_t f = a/b;
		//cout << " Y:                 a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
  		Double_t errorY = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or acc = hMC/hGen
    	accY->SetBinError(i, errorY);

 	
		Double_t a = hMCZtotal->GetBinContent(i);
		Double_t b = hGenZtotal->GetBinContent(i);
		Double_t f = a/b;
		//cout << " Z:                 a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
  		Double_t errorZ = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or acc = hMC/hGen
    	accZ->SetBinError(i, errorZ);

 	}

 	//------------------draw the acceptance correction histograms --------------------
 	TCanvas *cACC=new TCanvas("cACC","ACC",1000,500);
 	cACC->Divide(3,0);
 
 	cACC->cd(1);
 	accX->Draw();
 	cACC->cd(2);
 	accY->Draw();
 	cACC->cd(3);
 	accZ->Draw();

	//-------------- make sure when the acceptance correction is applied to the ---------------------
	//-------------- MC we return the flat distribution of the generated events-----------------------
 	TH1F* hMCACX = (TH1F*)hAnglesX->Clone("MCX");
 	hMCACX->Sumw2();
 	hMCACX->Divide(hMCXtotal, accX);
 	hMCACX->SetMinimum(0);

 	TH1F* hMCACY = (TH1F*)hAnglesY->Clone("MCY");
 	hMCACY->Sumw2();
 	hMCACY->Divide(hMCYtotal, accY);
 	hMCACY->SetMinimum(0);

 	TH1F* hMCACZ = (TH1F*)hAnglesZ->Clone("MCZ");
 	hMCACZ->Sumw2();
 	hMCACZ->Divide(hMCZtotal, accZ);
 	hMCACZ->SetMinimum(0);

 	TCanvas *cMCAC=new TCanvas("cMCAC","MC Corrected",1000,500);
 	cMCAC->Divide(3,0);
 	cMCAC->cd(1);
 	hMCACX->Draw();
 	cMCAC->cd(2);
 	hMCACY->Draw();
 	cMCAC->cd(3);
 	hMCACZ->Draw();


	//-------------- now apply the acceptance correction to Data---------------------
	//-------------- to obtain acceptance corrected histograms-----------------------
 
 	TH1F* hDataACX = (TH1F*)hAnglesX->Clone("DataX");
 	hDataACX->Sumw2();
 	hDataACX->Divide(hDataXtotal, accX);
 	hDataACX->SetMinimum(0);

 	TH1F* hDataACY = (TH1F*)hAnglesY->Clone("DataY");
 	hDataACY->Sumw2();
 	hDataACY->Divide(hDataYtotal, accY);
 	hDataACY->SetMinimum(0);

 	TH1F* hDataACZ = (TH1F*)hAnglesZ->Clone("DataZ");
 	hDataACZ->Sumw2();
 	hDataACZ->Divide(hDataZtotal, accZ);
 	hDataACZ->SetMinimum(0);

 	TCanvas *cDataAC=new TCanvas("cDataAC","Data Corrected",1000,500);
 	cDataAC->Divide(3,0);
 	cDataAC->cd(1);
 	hDataACX->Draw("e1p");
 	cDataAC->cd(2);
 	hDataACY->Draw();
 	cDataAC->cd(3);
 	hDataACZ->Draw();


	//-----------------------------------------calculate polarization------------------------------------
	
	//get the bin number for the limits of integration
	int binlow = hDataACX->GetXaxis()->FindBin(-1);
	int binmid = hDataACX->GetXaxis()->FindBin(0);
	int binhigh = hDataACX->GetXaxis()->FindBin(1);

	
	//calculate pos and neg errors
	Double_t pos,poserrSQ,neg,negerrSQ;
	poserrSQ = 0.0;
	negerrSQ = 0.0;
	for (Int_t i = 1; i <= AngleBins/2; i++) //only half of the bins
	{
		
		neg = neg + hDataACX->GetBinContent(i);
		pos = pos + hDataACX->GetBinContent(i + AngleBins/2 );
		negerrSQ = negerrSQ + (hDataACX->GetBinError(i))*(hDataACX->GetBinError(i));
		poserrSQ = poserrSQ + (hDataACX->GetBinError(i + AngleBins/2))*(hDataACX->GetBinError(i + AngleBins/2 ));
		cout << " i =  " << i << "  neg =  " << neg << "  negerr = " << sqrt(negerrSQ) << " pos = " << pos  << "  poserr = " << sqrt(poserrSQ) <<endl;
		
	}
	//calculate assymetery, polarization and errors
	Double_t negerr = sqrt(negerrSQ);
	Double_t poserr = sqrt(poserrSQ);
	Double_t asym = ( (pos - neg)/(pos + neg) );
	Double_t asymerr = sqrt((poserrSQ + negerrSQ)/((pos + neg)*(pos + neg)))*sqrt(1 + asym*asym);//sqrt((2*pos)/(pos*pos - neg*neg)); 
	Double_t pol = asym*4.385964;
	Double_t polerr = asymerr*4.385964;
	
	
	
	cout <<"------------"<<endl;
	cout << "binlow = " << binlow << "  binmid = " << binmid <<  "  binhigh = " << binhigh <<endl;
	cout << "pos = " << pos << "  poserr = " << poserr << endl;
	cout << "neg = " << neg << "  negerr = " << negerr << endl;
	cout << "asym = " << asym << "  asymerr = " << asymerr <<endl;
	cout << "pol = " << pol << "  polerr = " << polerr <<endl;


	TCanvas *cdummy=new TCanvas("cdummy","",100,50);

//*/
}