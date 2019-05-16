/*
Name: Stage3.C
Author: Jason Bono
Date: October 22 2012
Purpose: to take the histograms representing the pion angular distributions for Data, MC & Gen events, a
			and obtain the acceptance corrected pion angular distributions.
Input: ./hists/histsStage2.root
Output: ./hists/histsStage3.root


Notes: 
	!Read the comment section in GetW.C for more background!

*/
 
#include "/Users/Bono/clas/myDefinitions/Bins222FIXED.h" //kept for NBins definitions, must match Stage1.C

void Stage3()
{

	gStyle->SetErrorX(0.0);



	//open the ouput of Stage2.C and make a new file to write
	TFile* fhS2 = new TFile("./hists/histsStage2.root");
	TFile* fhS3 = new TFile("./hists/histsStage3.root","RECREATE");

	//setup 3 models yeild histograms
	TH1D *hAnglex = new TH1D("hAnglex","",NPiBins, -1,1);
	hAnglex->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");
	hAnglex->GetYaxis()->SetTitle("Counts");
	hAnglex->SetMinimum(0);
	hAnglex->SetMarkerStyle(21);
	TH1D *hAngley = (TH1D*)hAnglex->Clone("hAngley");
	hAngley->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
	TH1D *hAnglez = (TH1D*)hAnglex->Clone("hAnglez");
	hAnglez->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");

	//-------------------read in the histograms from stage 2--------------------------
	//EBins
	TH1D *hAngleDataEx[NEBins];
	TH1D *hAngleDataEy[NEBins];
	TH1D *hAngleDataEz[NEBins];
	TH1D *hAngleMCEx[NEBins];
	TH1D *hAngleMCEy[NEBins];
	TH1D *hAngleMCEz[NEBins];
	TH1D *hAngleGenEx[NEBins];
	TH1D *hAngleGenEy[NEBins];
	TH1D *hAngleGenEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hAngleDataEx[i] = (TH1D*)fhS2->Get(Form("hAngleData-EBin%i-x",i));
		hAngleDataEy[i] = (TH1D*)fhS2->Get(Form("hAngleData-EBin%i-y",i));
		hAngleDataEz[i] = (TH1D*)fhS2->Get(Form("hAngleData-EBin%i-z",i));
		hAngleMCEx[i] = (TH1D*)fhS2->Get(Form("hAngleMC-EBin%i-x",i));
		hAngleMCEy[i] = (TH1D*)fhS2->Get(Form("hAngleMC-EBin%i-y",i));
		hAngleMCEz[i] = (TH1D*)fhS2->Get(Form("hAngleMC-EBin%i-z",i));
		hAngleGenEx[i] = (TH1D*)fhS2->Get(Form("hAngleGen-EBin%i-x",i));
		hAngleGenEy[i] = (TH1D*)fhS2->Get(Form("hAngleGen-EBin%i-y",i));
		hAngleGenEz[i] = (TH1D*)fhS2->Get(Form("hAngleGen-EBin%i-z",i));
	}
	//XiBins
	TH1D *hAngleDataXix[NXiBins];
	TH1D *hAngleDataXiy[NXiBins];
	TH1D *hAngleDataXiz[NXiBins];
	TH1D *hAngleMCXix[NXiBins];
	TH1D *hAngleMCXiy[NXiBins];
	TH1D *hAngleMCXiz[NXiBins];
	TH1D *hAngleGenXix[NXiBins];
	TH1D *hAngleGenXiy[NXiBins];
	TH1D *hAngleGenXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hAngleDataXix[i] = (TH1D*)fhS2->Get(Form("hAngleData-XiBin%i-x",i));
		hAngleDataXiy[i] = (TH1D*)fhS2->Get(Form("hAngleData-XiBin%i-y",i));
		hAngleDataXiz[i] = (TH1D*)fhS2->Get(Form("hAngleData-XiBin%i-z",i));
		hAngleMCXix[i] = (TH1D*)fhS2->Get(Form("hAngleMC-XiBin%i-x",i));
		hAngleMCXiy[i] = (TH1D*)fhS2->Get(Form("hAngleMC-XiBin%i-y",i));
		hAngleMCXiz[i] = (TH1D*)fhS2->Get(Form("hAngleMC-XiBin%i-z",i));
		hAngleGenXix[i] = (TH1D*)fhS2->Get(Form("hAngleGen-XiBin%i-x",i));
		hAngleGenXiy[i] = (TH1D*)fhS2->Get(Form("hAngleGen-XiBin%i-y",i));
		hAngleGenXiz[i] = (TH1D*)fhS2->Get(Form("hAngleGen-XiBin%i-z",i));
	}
	
	//Declare the variables used for error calculations.
	Double_t a = 0.0;
	Double_t b = 0.0;
	Double_t f = 0.0;
	Double_t errorAC = 0.0;
	Double_t errorData = 0.0;
	Double_t errorDataAc = 0.0;
	Double_t A = 0.0;
	Double_t B = 0.0;
//----------------------------------------------------------------------------------	
	
//*	
	//=================create the Ac histograms for EBins======================================= 
	//EBins
	TH1D *hAcEx[NEBins];
	TH1D *hAcEy[NEBins];
	TH1D *hAcEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		//calculate and fill the values
		hAcEx[i] = (TH1D*)hAnglex->Clone(Form("hAc-EBin%i-x",i));
		hAcEy[i] = (TH1D*)hAngley->Clone(Form("hAc-EBin%i-y",i));
		hAcEz[i] = (TH1D*)hAnglez->Clone(Form("hAc-EBin%i-z",i));
		hAcEx[i]->Sumw2();
		hAcEy[i]->Sumw2(); 
		hAcEz[i]->Sumw2();
		hAcEx[i]->Divide(hAngleMCEx[i], hAngleGenEx[i]);
		hAcEy[i]->Divide(hAngleMCEy[i], hAngleGenEy[i]);
		hAcEz[i]->Divide(hAngleMCEz[i], hAngleGenEz[i]);
		
		//calculate and fill the errors
		for (Int_t k = 0; k < NPiBins; k++) //this had a mistake!
	 	{
			//x
	 		a = hAngleMCEx[i]->GetBinContent(k + 1);
			b = hAngleGenEx[i]->GetBinContent(k + 1);
			f = a/b;
	  		errorAC = (1/b)*sqrt(a*(1-f));
			errorAC = errorAC + 0.1*f; //adding the extra 10% uncertainty 
	    	hAcEx[i]->SetBinError(k + 1, errorAC);
			//cout << "x " << errorAC <<endl;
			//cout <<" -------- " <<endl;
			
			//y
	 		a = hAngleMCEy[i]->GetBinContent(k + 1);
			b = hAngleGenEy[i]->GetBinContent(k + 1);
			f = a/b;
	  		errorAC = (1/b)*sqrt(a*(1-f));
			errorAC = errorAC + 0.1*f; //adding the extra 10% uncertainty 
	    	hAcEy[i]->SetBinError(k + 1, errorAC);
			//cout << "y " << errorAC <<endl;
			//cout <<" -------- " <<endl;
			
			//z
	 		a = hAngleMCEz[i]->GetBinContent(k + 1);
			b = hAngleGenEz[i]->GetBinContent(k + 1);
			f = a/b;
	  		errorAC = (1/b)*sqrt(a*(1-f));
			errorAC = errorAC + 0.1*f; //adding the extra 10% uncertainty 
	    	hAcEz[i]->SetBinError(k + 1, errorAC);
			//cout << "z " << errorAC <<endl;
			//cout <<" -------- " <<endl;

	 	}
	}

	//obtain the acceptance corrected histogram for the Data 
	TH1D *hDataAcEx[NEBins];
	TH1D *hDataAcEy[NEBins];
	TH1D *hDataAcEz[NEBins];
	
	for (int i = 0; i < NEBins; i++)
	{
		hDataAcEx[i] = (TH1D*)hAnglex->Clone(Form("hDataAc-EBin%i-x",i));
		hDataAcEy[i] = (TH1D*)hAngley->Clone(Form("hDataAc-EBin%i-y",i));
		hDataAcEz[i] = (TH1D*)hAnglez->Clone(Form("hDataAc-EBin%i-z",i));
		hDataAcEx[i]->Divide(hAngleDataEx[i], hAcEx[i]);
		hDataAcEy[i]->Divide(hAngleDataEy[i], hAcEy[i]);
		hDataAcEz[i]->Divide(hAngleDataEz[i], hAcEz[i]);
		
		// set the error
		for (Int_t k = 0; k < NPiBins; k++) 
		{
			//x
			errorData = hAngleDataEx[i]->GetBinError(k + 1);
			A = hAngleDataEx[i]->GetBinContent(k + 1);
			errorAC = hAcEx[i]->GetBinError(k + 1);
			B = hAcEx[i]->GetBinContent(k + 1);
			errorDataAc = (A/B)*sqrt(( (errorData*errorData)/(A*A)) + ((errorAC*errorAC)/(B*B)) );
			hDataAcEx[i]->SetBinError(k + 1, errorDataAc);
			//cout << " X: " <<" DataAC Value: " << hDataAcEx[i]->GetBinContent(k + 1)<< endl; 
			//cout << " X: " <<"errorData:   "<< errorData <<"  errorAC: "<< errorAC<< "  errorDataAC: " << errorDataAc << endl;
				
			//y
			errorData = hAngleDataEy[i]->GetBinError(k + 1);
			A = hAngleDataEy[i]->GetBinContent(k + 1);
			errorAC = hAcEy[i]->GetBinError(k + 1);
			B = hAcEy[i]->GetBinContent(k + 1);
			errorDataAc = (A/B)*sqrt(( (errorData*errorData)/(A*A)) + ((errorAC*errorAC)/(B*B)) );
			hDataAcEy[i]->SetBinError(k + 1, errorDataAc);
			//cout << " Y: " <<" DataAC Value: " << hDataAcEy[i]->GetBinContent(k + 1)<< endl; 
			//cout << " Y: " <<"errorData:   "<< errorData <<"  errorAC: "<< errorAC<< "  errorDataAC: " << errorDataAc << endl;	
			
			//z
			errorData = hAngleDataEz[i]->GetBinError(k + 1);
			A = hAngleDataEz[i]->GetBinContent(k + 1);
			errorAC = hAcEz[i]->GetBinError(k + 1);
			B = hAcEy[i]->GetBinContent(k + 1);
			errorDataAc = (A/B)*sqrt(( (errorData*errorData)/(A*A)) + ((errorAC*errorAC)/(B*B)) );
			hDataAcEz[i]->SetBinError(k + 1, errorDataAc);
			//cout << " Z: " <<" DataAC Value: " << hDataAcEz[i]->GetBinContent(k + 1)<< endl; 
			//cout << " Z: " <<"errorData:   "<< errorData <<"  errorAC: "<< errorAC<< "  errorDataAC: " << errorDataAc << endl;
		}
	}
	
	
	//obtain the acceptance corrected histogram for the MC as a cross check 
	TH1D *hMCAcEx[NEBins];
	TH1D *hMCAcEy[NEBins];
	TH1D *hMCAcEz[NEBins];
	for (int i = 0; i < NEBins; i++)
	{
		hMCAcEx[i] = (TH1D*)hAnglex->Clone(Form("hMCAc-EBin%i-x",i));
		hMCAcEy[i] = (TH1D*)hAngley->Clone(Form("hMCAc-EBin%i-x",i));
		hMCAcEz[i] = (TH1D*)hAnglez->Clone(Form("hMCAc-EBin%i-x",i));
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
	TH1D *hAcXix[NXiBins];
	TH1D *hAcXiy[NXiBins];
	TH1D *hAcXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		//calculate and fill the values
		hAcXix[i] = (TH1D*)hAnglex->Clone(Form("hAc-XiBin%i-x",i));
		hAcXiy[i] = (TH1D*)hAngley->Clone(Form("hAc-XiBin%i-y",i));
		hAcXiz[i] = (TH1D*)hAnglez->Clone(Form("hAc-XiBin%i-z",i));
		hAcXix[i]->Sumw2();
		hAcXiy[i]->Sumw2(); 
		hAcXiz[i]->Sumw2();
		hAcXix[i]->Divide(hAngleMCXix[i], hAngleGenXix[i]);
		hAcXiy[i]->Divide(hAngleMCXiy[i], hAngleGenXiy[i]);
		hAcXiz[i]->Divide(hAngleMCXiz[i], hAngleGenXiz[i]);
		
		//calculate and fill the errors
		for (Int_t k = 0; k < NPiBins; k++) //this had a mistake!
	 	{
			//x
	 		Double_t a = hAngleMCXix[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenXix[i]->GetBinContent(k + 1);
			Double_t f = a/b;
	  		Double_t errorAc = (1/b)*sqrt(a*(1-f));
			errorAc = errorAc + 0.1*f; //adding the extra 10% uncertainty 
	    	hAcXix[i]->SetBinError(k + 1, errorAc);
			
	
			//y
			Double_t a = hAngleMCXiy[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenXiy[i]->GetBinContent(k + 1);
			Double_t f = a/b;
		  	Double_t errorAc = (1/b)*sqrt(a*(1-f));
			errorY = errorAc + 0.1*f; //adding the extra 10% uncertainty 
		    hAcXiy[i]->SetBinError(k + 1, errorAc);
			
			//z
			Double_t a = hAngleMCXiz[i]->GetBinContent(k + 1);
			Double_t b = hAngleGenXiz[i]->GetBinContent(k + 1);
			Double_t f = a/b;
			Double_t errorAc = (1/b)*sqrt(a*(1-f));
			errorZ = errorAc + 0.1*f; //adding the extra 10% uncertainty 
			hAcXiz[i]->SetBinError(k + 1, errorAc);

	 	}
	}

	//obtain the acceptance corrected histogram for the Data 
	TH1D *hDataAcXix[NXiBins];
	TH1D *hDataAcXiy[NXiBins];
	TH1D *hDataAcXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hDataAcXix[i] = (TH1D*)hAnglex->Clone(Form("hDataAc-XiBin%i-x",i));
		hDataAcXiy[i] = (TH1D*)hAngley->Clone(Form("hDataAc-XiBin%i-y",i));
		hDataAcXiz[i] = (TH1D*)hAnglez->Clone(Form("hDataAc-XiBin%i-z",i));
		hDataAcXix[i]->Divide(hAngleDataXix[i], hAcXix[i]);
		hDataAcXiy[i]->Divide(hAngleDataXiy[i], hAcXiy[i]);
		hDataAcXiz[i]->Divide(hAngleDataXiz[i], hAcXiz[i]);
		
		// set the error
		for (Int_t k = 0; k < NPiBins; k++) 
		{
			//x
			errorData = hAngleDataXix[i]->GetBinError(k + 1);
			A = hAngleDataXix[i]->GetBinContent(k + 1);
			errorAC = hAcXix[i]->GetBinError(k + 1);
			B = hAcXix[i]->GetBinContent(k + 1);
			errorDataAc = (A/B)*sqrt(( (errorData*errorData)/(A*A)) + ((errorAC*errorAC)/(B*B)) );
			hDataAcXix[i]->SetBinError(k + 1, errorDataAc);
			cout << " X: " <<" DataAC Value: " << hDataAcXix[i]->GetBinContent(k + 1)<< endl; 
			cout << " X: " <<"errorData:   "<< errorData <<"  errorAC: "<< errorAC<< "  errorDataAC: " << errorDataAc << endl;
				
			//y
			errorData = hAngleDataXiy[i]->GetBinError(k + 1);
			A = hAngleDataXiy[i]->GetBinContent(k + 1);
			errorAC = hAcXiy[i]->GetBinError(k + 1);
			B = hAcXiy[i]->GetBinContent(k + 1);
			errorDataAc = (A/B)*sqrt(( (errorData*errorData)/(A*A)) + ((errorAC*errorAC)/(B*B)) );
			hDataAcXiy[i]->SetBinError(k + 1, errorDataAc);
			cout << " Y: " <<" DataAC Value: " << hDataAcXiy[i]->GetBinContent(k + 1)<< endl; 
			cout << " Y: " <<"errorData:   "<< errorData <<"  errorAC: "<< errorAC<< "  errorDataAC: " << errorDataAc << endl;	
			
			//z
			errorData = hAngleDataXiz[i]->GetBinError(k + 1);
			A = hAngleDataXiz[i]->GetBinContent(k + 1);
			errorAC = hAcXiz[i]->GetBinError(k + 1);
			B = hAcXiy[i]->GetBinContent(k + 1);
			errorDataAc = (A/B)*sqrt(( (errorData*errorData)/(A*A)) + ((errorAC*errorAC)/(B*B)) );
			hDataAcXiz[i]->SetBinError(k + 1, errorDataAc);
			cout << " Z: " <<" DataAC Value: " << hDataAcXiz[i]->GetBinContent(k + 1)<< endl; 
			cout << " Z: " <<"errorData:   "<< errorData <<"  errorAC: "<< errorAC<< "  errorDataAC: " << errorDataAc << endl;
		}
	}
	
	
	//obtain the acceptance corrected histogram for the MC (as a cross check) 
	TH1D *hMCAcXix[NXiBins];
	TH1D *hMCAcXiy[NXiBins];
	TH1D *hMCAcXiz[NXiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		hMCAcXix[i] = (TH1D*)hAnglex->Clone(Form("hMCAc-XiBin%i-x",i));
		hMCAcXiy[i] = (TH1D*)hAngley->Clone(Form("hMCAc-XiBin%i-x",i));
		hMCAcXiz[i] = (TH1D*)hAnglez->Clone(Form("hMCAc-XiBin%i-x",i));
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
	
	
	

	
}