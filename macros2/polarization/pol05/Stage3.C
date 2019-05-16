/*
Name: Stage3.C
Author: Jason Bono
Date: October 22 2012
Purpose: to take the histograms representing the pion angular distributions for Data, MC & Gen events, a
			and obtain the acceptance corrected pion angular distributions.


Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events
*/



void Stage3()
{


	//binning (keep this consistant with all stages)
	const int NEBins = 3; 
	const int NXiBins = 3; 
	const int NPiBins = 4;

	//open the ouput of Stage2.C and make a new file to write
	TFile* fhS2 = new TFile("./hists/histsStage2.root");
	TFile* fhS3 = new TFile("./hists/histsStage3.root","RECREATE");

	//setup 3 models yeild histograms
	TH1F *hAnglex = new TH1F("hAnglex","",NPiBins, -1,1);
	hAnglex->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");
	hAnglex->GetYaxis()->SetTitle("Counts");
	hAnglex->SetMinimum(0);
	hAnglex->SetMarkerStyle(21);
	TH1F *hAngley = (TH1F*)hAnglex->Clone("hAngley");
	hAngley->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
	TH1F *hAnglez = (TH1F*)hAnglex->Clone("hAnglez");
	hAnglez->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");

	//-------------------read in the histograms from stage 2--------------------------
	//EBins
	TH1F *hAngleDataEx[NEBins];
	TH1F *hAngleDataEy[NEBins];
	TH1F *hAngleDataEz[NEBins];
	TH1F *hAngleMCEx[NEBins];
	TH1F *hAngleMCEy[NEBins];
	TH1F *hAngleMCEz[NEBins];
	TH1F *hAngleGenEx[NEBins];
	TH1F *hAngleGenEy[NEBins];
	TH1F *hAngleGenEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hAngleDataEx[i] = (TH1F*)fhS2->Get(Form("hAngleData-EBin%i-x",i));
		hAngleDataEy[i] = (TH1F*)fhS2->Get(Form("hAngleData-EBin%i-y",i));
		hAngleDataEz[i] = (TH1F*)fhS2->Get(Form("hAngleData-EBin%i-z",i));
		hAngleMCEx[i] = (TH1F*)fhS2->Get(Form("hAngleMC-EBin%i-x",i));
		hAngleMCEy[i] = (TH1F*)fhS2->Get(Form("hAngleMC-EBin%i-y",i));
		hAngleMCEz[i] = (TH1F*)fhS2->Get(Form("hAngleMC-EBin%i-z",i));
		hAngleGenEx[i] = (TH1F*)fhS2->Get(Form("hAngleGen-EBin%i-x",i));
		hAngleGenEy[i] = (TH1F*)fhS2->Get(Form("hAngleGen-EBin%i-y",i));
		hAngleGenEz[i] = (TH1F*)fhS2->Get(Form("hAngleGen-EBin%i-z",i));
	}
	//XiBins
	TH1F *hAngleDataXix[NXiBins];
	TH1F *hAngleDataXiy[NXiBins];
	TH1F *hAngleDataXiz[NXiBins];
	TH1F *hAngleMCXix[NXiBins];
	TH1F *hAngleMCXiy[NXiBins];
	TH1F *hAngleMCXiz[NXiBins];
	TH1F *hAngleGenXix[NXiBins];
	TH1F *hAngleGenXiy[NXiBins];
	TH1F *hAngleGenXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hAngleDataXix[i] = (TH1F*)fhS2->Get(Form("hAngleData-XiBin%i-x",i));
		hAngleDataXiy[i] = (TH1F*)fhS2->Get(Form("hAngleData-XiBin%i-y",i));
		hAngleDataXiz[i] = (TH1F*)fhS2->Get(Form("hAngleData-XiBin%i-z",i));
		hAngleMCXix[i] = (TH1F*)fhS2->Get(Form("hAngleMC-XiBin%i-x",i));
		hAngleMCXiy[i] = (TH1F*)fhS2->Get(Form("hAngleMC-XiBin%i-y",i));
		hAngleMCXiz[i] = (TH1F*)fhS2->Get(Form("hAngleMC-XiBin%i-z",i));
		hAngleGenXix[i] = (TH1F*)fhS2->Get(Form("hAngleGen-XiBin%i-x",i));
		hAngleGenXiy[i] = (TH1F*)fhS2->Get(Form("hAngleGen-XiBin%i-y",i));
		hAngleGenXiz[i] = (TH1F*)fhS2->Get(Form("hAngleGen-XiBin%i-z",i));
	}
//----------------------------------------------------------------------------------	
	
//*	
	//=================create the Ac histograms for EBins======================================= 
	//EBins
	TH1F *hAcEx[NEBins];
	TH1F *hAcEy[NEBins];
	TH1F *hAcEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		//calculate and fill the values
		hAcEx[i] = (TH1F*)hAnglex->Clone(Form("hAc-EBin%i-x",i));
		hAcEy[i] = (TH1F*)hAngley->Clone(Form("hAc-EBin%i-y",i));
		hAcEz[i] = (TH1F*)hAnglez->Clone(Form("hAc-EBin%i-z",i));
		hAcEx[i]->Sumw2();
		hAcEy[i]->Sumw2(); 
		hAcEz[i]->Sumw2();
		hAcEx[i]->Divide(hAngleMCEx[i], hAngleGenEx[i]);
		hAcEy[i]->Divide(hAngleMCEy[i], hAngleGenEy[i]);
		hAcEz[i]->Divide(hAngleMCEz[i], hAngleGenEz[i]);
		
		//calculate and fill the errors
		for (Int_t k = 0; k <= NPiBins; k++) 
	 	{
			//x
	 		Double_t a = hAngleMCEx[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenEx[i]->GetBinContent(k + 1);
			Double_t f = a/b;
	  		Double_t errorX = (1/b)*sqrt(a*(1-f));
	    	hAcEx[i]->SetBinError(k + 1, errorX);
	
			//y
			Double_t a = hAngleMCEy[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenEy[i]->GetBinContent(k + 1);
			Double_t f = a/b;
		  	Double_t errorX = (1/b)*sqrt(a*(1-f));
		    hAcEy[i]->SetBinError(k + 1, errorX);
			
			//z
			Double_t a = hAngleMCEz[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenEz[i]->GetBinContent(k + 1);
			Double_t f = a/b;
			Double_t errorX = (1/b)*sqrt(a*(1-f));
			hAcEz[i]->SetBinError(k + 1, errorX);

	 	}
	}

	//obtain the acceptance corrected histogram for the Data 
	TH1F *hDataAcEx[NEBins];
	TH1F *hDataAcEy[NEBins];
	TH1F *hDataAcEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hDataAcEx[i] = (TH1F*)hAnglex->Clone(Form("hDataAc-EBin%i-x",i));
		hDataAcEy[i] = (TH1F*)hAngley->Clone(Form("hDataAc-EBin%i-y",i));
		hDataAcEz[i] = (TH1F*)hAnglez->Clone(Form("hDataAc-EBin%i-z",i));
		hDataAcEx[i]->Divide(hAngleDataEx[i], hAcEx[i]);
		hDataAcEy[i]->Divide(hAngleDataEy[i], hAcEy[i]);
		hDataAcEz[i]->Divide(hAngleDataEz[i], hAcEz[i]);
	}
	
	
	//obtain the acceptance corrected histogram for the MC (as a cross check) 
	TH1F *hMCAcEx[NEBins];
	TH1F *hMCAcEy[NEBins];
	TH1F *hMCAcEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hMCAcEx[i] = (TH1F*)hAnglex->Clone(Form("hMCAc-EBin%i-x",i));
		hMCAcEy[i] = (TH1F*)hAngley->Clone(Form("hMCAc-EBin%i-x",i));
		hMCAcEz[i] = (TH1F*)hAnglez->Clone(Form("hMCAc-EBin%i-x",i));
		hMCAcEx[i]->Divide(hAngleMCEx[i], hAcEx[i]);
		hMCAcEy[i]->Divide(hAngleMCEy[i], hAcEy[i]);
		hMCAcEz[i]->Divide(hAngleMCEz[i], hAcEz[i]);
	}
	

	//write the histograms to file
	for (int i = 0; i < NEBins; i++)
	{
		hDataAcEx[i]->Write();
		hDataAcEy[i]->Write();
		hDataAcEz[i]->Write();
		hMCAcEx[i]->Write();
		hMCAcEy[i]->Write();
		hMCAcEz[i]->Write();
	}
	
	
	
	
	
	
	//=================create the Ac histograms for XiBins======================================= 
	//XiBins
	TH1F *hAcXix[NXiBins];
	TH1F *hAcXiy[NXiBins];
	TH1F *hAcXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		//calculate and fill the values
		hAcXix[i] = (TH1F*)hAnglex->Clone(Form("hAc-XiBin%i-x",i));
		hAcXiy[i] = (TH1F*)hAngley->Clone(Form("hAc-XiBin%i-y",i));
		hAcXiz[i] = (TH1F*)hAnglez->Clone(Form("hAc-XiBin%i-z",i));
		hAcXix[i]->Sumw2();
		hAcXiy[i]->Sumw2(); 
		hAcXiz[i]->Sumw2();
		hAcXix[i]->Divide(hAngleMCXix[i], hAngleGenXix[i]);
		hAcXiy[i]->Divide(hAngleMCXiy[i], hAngleGenXiy[i]);
		hAcXiz[i]->Divide(hAngleMCXiz[i], hAngleGenXiz[i]);
		
		//calculate and fill the errors
		for (Int_t k = 0; k <= NPiBins; k++) 
	 	{
			//x
	 		Double_t a = hAngleMCXix[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenXix[i]->GetBinContent(k + 1);
			Double_t f = a/b;
	  		Double_t errorX = (1/b)*sqrt(a*(1-f));
	    	hAcXix[i]->SetBinError(k + 1, errorX);
	
			//y
			Double_t a = hAngleMCXiy[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenXiy[i]->GetBinContent(k + 1);
			Double_t f = a/b;
		  	Double_t errorX = (1/b)*sqrt(a*(1-f));
		    hAcXiy[i]->SetBinError(k + 1, errorX);
			
			//z
			Double_t a = hAngleMCXiz[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenXiz[i]->GetBinContent(k + 1);
			Double_t f = a/b;
			Double_t errorX = (1/b)*sqrt(a*(1-f));
			hAcXiz[i]->SetBinError(k + 1, errorX);

	 	}
	}

	//obtain the acceptance corrected histogram for the Data 
	TH1F *hDataAcXix[NXiBins];
	TH1F *hDataAcXiy[NXiBins];
	TH1F *hDataAcXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hDataAcXix[i] = (TH1F*)hAnglex->Clone(Form("hDataAc-XiBin%i-x",i));
		hDataAcXiy[i] = (TH1F*)hAngley->Clone(Form("hDataAc-XiBin%i-y",i));
		hDataAcXiz[i] = (TH1F*)hAnglez->Clone(Form("hDataAc-XiBin%i-z",i));
		hDataAcXix[i]->Divide(hAngleDataXix[i], hAcXix[i]);
		hDataAcXiy[i]->Divide(hAngleDataXiy[i], hAcXiy[i]);
		hDataAcXiz[i]->Divide(hAngleDataXiz[i], hAcXiz[i]);
	}
	
	
	//obtain the acceptance corrected histogram for the MC (as a cross check) 
	TH1F *hMCAcXix[NXiBins];
	TH1F *hMCAcXiy[NXiBins];
	TH1F *hMCAcXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hMCAcXix[i] = (TH1F*)hAnglex->Clone(Form("hMCAc-XiBin%i-x",i));
		hMCAcXiy[i] = (TH1F*)hAngley->Clone(Form("hMCAc-XiBin%i-x",i));
		hMCAcXiz[i] = (TH1F*)hAnglez->Clone(Form("hMCAc-XiBin%i-x",i));
		hMCAcXix[i]->Divide(hAngleMCXix[i], hAcXix[i]);
		hMCAcXiy[i]->Divide(hAngleMCXiy[i], hAcXiy[i]);
		hMCAcXiz[i]->Divide(hAngleMCXiz[i], hAcXiz[i]);
	}
	

	//write the histograms to file
	for (int i = 0; i < NXiBins; i++)
	{
		hDataAcXix[i]->Write();
		hDataAcXiy[i]->Write();
		hDataAcXiz[i]->Write();
		hMCAcXix[i]->Write();
		hMCAcXiy[i]->Write();
		hMCAcXiz[i]->Write();
	}
	
	
	
	
	
	
	
/*
//---------------------------------You can set the errors-----------------------------------------
//-----------------------for each bin of your acceptance explicitly-------------------------------
//-------------------------because GEN and MC events are correlated------------------------------

for (Int_t i = 1; i <= hAcEX->GetNbinsX(); i++) 
{
	Double_t a = hMCXtotal->GetBinContent(i);
	Double_t b = hGenXtotal->GetBinContent(i);
	Double_t f = a/b;
	//cout << "X: "<<"i = "<< i <<"  Bins = "<< hAcEX->GetNbinsX() <<"  a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
	Double_t errorX = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or hAcE = hMC/hGen
	hAcEX->SetBinError(i, errorX);


	Double_t a = hMCYtotal->GetBinContent(i);
	Double_t b = hGenYtotal->GetBinContent(i);
	Double_t f = a/b;
	//cout << " Y:                 a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
	Double_t errorY = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or hAcE = hMC/hGen
	hAcEY->SetBinError(i, errorY);


	Double_t a = hMCZtotal->GetBinContent(i);
	Double_t b = hGenZtotal->GetBinContent(i);
	Double_t f = a/b;
	//cout << " Z:                 a = "<< a <<"  b = "<< b << "  f = " << f <<endl;
	Double_t errorZ = (1/b)*sqrt(a*(1-f));    // From Bevington: f = a/b or hAcE = hMC/hGen
	hAcEZ->SetBinError(i, errorZ);

}




*/	
	
	
}