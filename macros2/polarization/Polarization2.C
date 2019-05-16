/*
set the number of bins (even number) 
for now only do for the first 5 energy bins (3.3GeV - 4.3GeV)
*/

void Polarization2()
{
	//how many energy bins
	const Int_t NEBins = 11; // this is how many energy bins the Ws were calculated for in GetW.C
	const Int_t LIM = 5; // this specifys how many of the energy bins to use (use all eventualy)
	
	//declare the weighting which came from the output of GetW.C
	const Double_t W[NEBins] = {0.42268, 0.750716, 0.959565, 1.59699, 1.2619, 0, 0, 0, 4.56585, 4.31677, 0};
	const Double_t Werr[NEBins] = {0.07213, 0.117452, 0.146268, 0.267722, 0.242003, 0, 0, 0, 0.882696, 4.92313e+06, 0};
	
	//const Double_t W[NEBins] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	//define how finly to bin in Cosine the pion angle
	int AngleBins = 8;
	
	//define strings
	TString beam[NEBins]; //for cuts
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
	
	TString name[NEBins]; //for naming histos
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
 	TFile* fData = new TFile("v37k_full_newbasic.root");     // DATA histograms
 	TFile* fMC = new TFile("MC_v07_v37k.root");         // MC histograms
 	//TFile* fGen = new TFile("genfile.root");       // GEN histograms 

 	// make aliases for the trees from each file
 	TTree *tData = (TTree*)fMC->Get("v37k");
 	TTree *tMC = (TTree*)fData->Get("v37k_newbasic");
 	//TTree *tGen = (TTree*)fGen->Get("gamptree");

 	// - - - - - -  if the histograms are already stored in the root files, read the same histogram from each file - - - - - - - -
 	//TH1F* hData = (TH1F*)fData->Get("v37k_newbasic")->Clone("data_electron_neg_q2_bin1");
 	//TH1F* hMC = (TH1F*)fMC->Get("v37k")->Clone("mc_electron_neg_q2_bin1");
 	//TH1F* hGen = (TH1F*)fGen->Get("electron_neg_q2_bin1")->Clone("gen_electron_neg_q2_bin1");


 	//if the histograms are not stored in each root file, make them.
 	TCut conf = "kf_prob > 0.50";
 	
	//-----------------------------------------------Data-----------------------------------------------
	TCanvas *cData[LIM];
	TH1F *hDataX[LIM];
 	TH1F *hDataY[LIM];
 	TH1F *hDataZ[LIM];
	TH1F *hDataXtotal = new TH1F("hDataXtotal","hDataXtotal",AngleBins, -1,1);
	TH1F *hDataYtotal = new TH1F("hDataYtotal","hDataYtotal",AngleBins, -1,1);
	TH1F *hDataZtotal = new TH1F("hDataZtotal","hDataZtotal",AngleBins, -1,1);
	for (int i = 0; i < LIM; i++){
		
		cData[i] = new TCanvas(Form("cData%i",i),Form("cData%i",i),1000,500);
 		cData[i]->Divide(3,0);

 		hDataX[i] = new TH1F(Form("hDataX%i",i),name[i],AngleBins, -1,1);
 		hDataY[i] = new TH1F(Form("hDataY%i",i),name[i],AngleBins, -1,1);
 		hDataZ[i] = new TH1F(Form("hDataZ%i",i),name[i],AngleBins, -1,1);
 		
		hDataX[i]->SetMinimum(0);
 		hDataY[i]->SetMinimum(0);
 		hDataZ[i]->SetMinimum(0);
 		hDataX[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 		hDataY[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 		hDataZ[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   
	
		cData[i]->cd(1);
 		tData->Draw(Form("COS_pi_x>>hDataX%i",i),conf&&beam[i],"E");
 		cData[i]->cd(2); 
 		tData->Draw(Form("COS_pi_y>>hDataY%i",i),conf&&beam[i],"E");
 		cData[i]->cd(3); 
 		tData->Draw(Form("COS_pi_z>>hDataZ%i",i),conf&&beam[i],"E");
		
		//add up the histograms
		hDataXtotal->Add(hDataX[i],1);
		hDataYtotal->Add(hDataY[i],1);
		hDataZtotal->Add(hDataZ[i],1);
	}
	/* //check the total histogram
	TCanvas *ctest1=new TCanvas("ctest1","test1",1000,500);
	ctest1->Divide(3,0);
	ctest1->cd(1);
	hDataXtotal->Draw();
	ctest1->cd(2);
	hDataYtotal->Draw();
	ctest1->cd(3);
	hDataZtotal->Draw();
	*/
	
	
		//-----------------------------------------------------MC------------------------------------------------------
		TCanvas *cMC[LIM];
		TH1F *hMCX[LIM];
	 	TH1F *hMCY[LIM];
	 	TH1F *hMCZ[LIM];
		TH1F *hMCXtotal = new TH1F("hMCXtotal","hMCXtotal",AngleBins, -1,1);
		TH1F *hMCYtotal = new TH1F("hMCYtotal","hMCYtotal",AngleBins, -1,1);
		TH1F *hMCZtotal = new TH1F("hMCZtotal","hMCZtotal",AngleBins, -1,1);
		for (int i = 0; i < LIM; i++){

			cMC[i] = new TCanvas(Form("cMC%i",i),Form("cMC%i",i),1000,500);
	 		cMC[i]->Divide(3,0);

	 		hMCX[i] = new TH1F(Form("hMCX%i",i),name[i],AngleBins, -1,1);
	 		hMCY[i] = new TH1F(Form("hMCY%i",i),name[i],AngleBins, -1,1);
	 		hMCZ[i] = new TH1F(Form("hMCZ%i",i),name[i],AngleBins, -1,1);

			hMCX[i]->SetMinimum(0);
	 		hMCY[i]->SetMinimum(0);
	 		hMCZ[i]->SetMinimum(0);
	 		hMCX[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
	 		hMCY[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
	 		hMCZ[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   

			cMC[i]->cd(1);
	 		tMC->Draw(Form("COS_pi_x>>hMCX%i",i),conf&&beam[i],"E");
	 		cMC[i]->cd(2); 
	 		tMC->Draw(Form("COS_pi_y>>hMCY%i",i),conf&&beam[i],"E");
	 		cMC[i]->cd(3); 
	 		tMC->Draw(Form("COS_pi_z>>hMCZ%i",i),conf&&beam[i],"E");

			//add up the histograms
			hMCXtotal->Add(hMCX[i],W[i]);
			hMCYtotal->Add(hMCY[i],W[i]);
			hMCZtotal->Add(hMCZ[i],W[i]);
		}




		//-----------------------------------------------------Gen------------------------------------------------------
		TCanvas *cGen[LIM];
		TH1F *hGenX[LIM];
	 	TH1F *hGenY[LIM];
	 	TH1F *hGenZ[LIM];
		TH1F *hGenXtotal = new TH1F("hGenXtotal","hGenXtotal",AngleBins, -1,1);
		TH1F *hGenYtotal = new TH1F("hGenYtotal","hGenYtotal",AngleBins, -1,1);
		TH1F *hGenZtotal = new TH1F("hGenZtotal","hGenZtotal",AngleBins, -1,1);
		for (int i = 0; i < LIM; i++){

			cGen[i] = new TCanvas(Form("cGen%i",i),Form("cGen%i",i),1000,500);
	 		cGen[i]->Divide(3,0);

	 		hGenX[i] = new TH1F(Form("hGenX%i",i),name[i],AngleBins, -1,1);
	 		hGenY[i] = new TH1F(Form("hGenY%i",i),name[i],AngleBins, -1,1);
	 		hGenZ[i] = new TH1F(Form("hGenZ%i",i),name[i],AngleBins, -1,1);

			hGenX[i]->SetMinimum(0);
	 		hGenY[i]->SetMinimum(0);
	 		hGenZ[i]->SetMinimum(0);
	 		hGenX[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
	 		hGenY[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
	 		hGenZ[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   


			TRandom3 *randGenerator = new TRandom3(time(NULL));
		 	for (int j = 0; j < 50000; j++) 
		 	{
		   		Double_t number = randGenerator->Uniform(-1,1); // generates a number between -1 and 1 
		   		hGenX[i]->Fill(number);	
		   		number = randGenerator->Uniform(-1,1);
		   		hGenY[i]->Fill(number);
		   		number = randGenerator->Uniform(-1,1);
		   		hGenZ[i]->Fill(number);
		 	}

		 
			cGen[i]->cd(1);
			hGenX[i]->Draw("E");
	 		//tGen->Draw(Form("COS_pi_x>>hGenX%i",i),conf&&beam[i],"E");
	 		cGen[i]->cd(2); 
			hGenY[i]->Draw("E");
	 		//tGen->Draw(Form("COS_pi_y>>hGenY%i",i),conf&&beam[i],"E");
	 		cGen[i]->cd(3); 
			hGenZ[i]->Draw("E");
	 		//tGen->Draw(Form("COS_pi_z>>hGenZ%i",i),conf&&beam[i],"E");

			//add up the histograms
			hGenXtotal->Add(hGenX[i],W[i]);
			hGenYtotal->Add(hGenY[i],W[i]);
			hGenZtotal->Add(hGenZ[i],W[i]);
		}



/*

 	//------------------------------------------------Generated-------------------------------------------------
 	TCanvas *c2=new TCanvas("c2","generated",1000,500);
 	c2->Divide(3,0);
 	c2->cd(1);
 	TH1F *hGenX = new TH1F("hGenX","",AngleBins, -1,1);
 	TH1F *hGenY = new TH1F("hGenY","",AngleBins, -1,1);
 	TH1F *hGenZ = new TH1F("hGenZ","",AngleBins, -1,1);
 	hGenX->SetMinimum(0);
 	hGenY->SetMinimum(0);
 	hGenZ->SetMinimum(0);
 	hGenX->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");   
 	hGenY->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");   
 	hGenZ->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");   

 	//fill a flat histogram since we dont have the generated tree
 	TRandom3 *randGenerator = new TRandom3(time(NULL));
 	for (int i = 0; i < 50000; i++) 
 	{
   		Double_t number = randGenerator->Uniform(-1,1); // generates a number between -1 and 1 
   		hGenX->Fill(number);	
   		number = randGenerator->Uniform(-1,1);
   		hGenY->Fill(number);
   		number = randGenerator->Uniform(-1,1);
   		hGenZ->Fill(number);
 	}
 
 	hGenX->Draw("E");
 	//tMC->Draw("COS_pi_x>>hMCX");
 	c2->cd(2); 
 	hGenY->Draw("E");
 	//tMC->Draw("COS_pi_y>>hMCY");
 	c2->cd(3); 
 	hGenZ->Draw("E");
 	//tMC->Draw("COS_pi_z>>hMCZ"); 
*/

 	// ==================================================================================================================

 	//------------------- create a new acceptance histogram---------------------
 	//------------- from a clone of either of the three histograms above---------
 	//---------- the binning should be the same for all histograms above
 	TH1F* accX = (TH1F*)hMCXtotal->Clone("accX");
 	TH1F* accY = (TH1F*)hMCYtotal->Clone("accY");
 	TH1F* accZ = (TH1F*)hMCZtotal->Clone("accZ");

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
		cout << "X: "<<"i = "<< i <<"  Bins = "<< accX->GetNbinsX() <<"  a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
  		Double_t errorX = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or acc = hMC/hGen
    	accX->SetBinError(i, errorX);


		Double_t a = hMCYtotal->GetBinContent(i);
		Double_t b = hGenYtotal->GetBinContent(i);
		Double_t f = a/b;
		cout << " Y:                 a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
  		Double_t errorY = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or acc = hMC/hGen
    	accY->SetBinError(i, errorY);

 	
		Double_t a = hMCZtotal->GetBinContent(i);
		Double_t b = hGenZtotal->GetBinContent(i);
		Double_t f = a/b;
		cout << " Z:                 a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
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
 	TH1F* hMCACX = (TH1F*)hMCXtotal->Clone("MCX");
 	hMCACX->Sumw2();
 	hMCACX->Divide(hMCXtotal, accX);
 	hMCACX->SetMinimum(0);

 	TH1F* hMCACY = (TH1F*)hMCYtotal->Clone("MCY");
 	hMCACY->Sumw2();
 	hMCACY->Divide(hMCYtotal, accY);
 	hMCACY->SetMinimum(0);

 	TH1F* hMCACZ = (TH1F*)hMCZtotal->Clone("MCZ");
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
 
 	TH1F* hDataACX = (TH1F*)hDataXtotal->Clone("DataX");
 	hDataACX->Sumw2();
 	hDataACX->Divide(hDataXtotal, accX);
 	hDataACX->SetMinimum(0);

 	TH1F* hDataACY = (TH1F*)hDataYtotal->Clone("DataY");
 	hDataACY->Sumw2();
 	hDataACY->Divide(hDataYtotal, accY);
 	hDataACY->SetMinimum(0);

 	TH1F* hDataACZ = (TH1F*)hDataZtotal->Clone("DataZ");
 	hDataACZ->Sumw2();
 	hDataACZ->Divide(hDataZtotal, accZ);
 	hDataACZ->SetMinimum(0);

 	TCanvas *cDataAC=new TCanvas("cDataAC","Data Corrected",1000,500);
 	cDataAC->Divide(3,0);
 	cDataAC->cd(1);
 	hDataACX->Draw();
 	cDataAC->cd(2);
 	hDataACY->Draw();
 	cDataAC->cd(3);
 	hDataACZ->Draw();

}