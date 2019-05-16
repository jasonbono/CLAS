/*
Name: Stage2.C
Author: Jason Bono
Date: October 22 2012
Purpose: To take the ouput of Stage1.C & to get yields and output the histograms representing the angular distribution of the pion in the jackson frame


Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events
*/



void Stage2()
{


	char *s = new char[1]; 
	const string simcount ("nofit"); //change this according to how you want the accepted events to be counted
	const string fit ("fit");
	const string nofit ("nofit");
	
		if (simcount.compare(fit) == 0)
		{
			cout << "The fit method: type enter to accept" <<endl;	
			gets(s);
			cout << "fit method accepted" << endl;
			//gROOT->ProcessLine(".q");	
		}
		else if (simcount.compare(nofit) == 0)
		{
			cout << "The no-fit method: Type enter to accept" <<endl;
			gets(s);
			cout << "The no-fit method accepted" << endl;
			//gROOT->ProcessLine(".q");
		}
		else 
		{
			cout << "somthing is wrong, terminating program" <<endl;
			gROOT->ProcessLine(".q");
		}
	
	//binning (keep this consistant with all stages)
	const int NEBins = 3; 
	const int NXiBins = 3; 
	const int NPiBins = 4;
	


	//open the ouput of Stage1.C and new file to write
	TFile* fhS1 = new TFile("./hists/histsStage1.root");
	TFile* fhS2 = new TFile("./hists/histsStage2.root","RECREATE");	


	//declare the hists which will be read in
	//Data
	TH1F *hDataEx[NEBins][NPiBins];
	TH1F *hDataEy[NEBins][NPiBins];
	TH1F *hDataEz[NEBins][NPiBins];
	TH1F *hDataXix[NEBins][NPiBins];
	TH1F *hDataXiy[NEBins][NPiBins];
	TH1F *hDataXiz[NEBins][NPiBins];
	//MC
	TH1F *hMCEx[NEBins][NPiBins];
	TH1F *hMCEy[NEBins][NPiBins];
	TH1F *hMCEz[NEBins][NPiBins];
	TH1F *hMCXix[NEBins][NPiBins];
	TH1F *hMCXiy[NEBins][NPiBins];
	TH1F *hMCXiz[NEBins][NPiBins];
	//Gen
	TH1F *hGenEx[NEBins][NPiBins];
	TH1F *hGenEy[NEBins][NPiBins];
	TH1F *hGenEz[NEBins][NPiBins];
	TH1F *hGenXix[NEBins][NPiBins];
	TH1F *hGenXiy[NEBins][NPiBins];
	TH1F *hGenXiz[NEBins][NPiBins];
	
	//declare the hists which will be written
	//Data
	TH1F *hAngleDataEx[NEBins];
	TH1F *hAngleDataEy[NEBins];
	TH1F *hAngleDataEz[NEBins];
	TH1F *hAngleDataXix[NEBins];
	TH1F *hAngleDataXiy[NEBins];
	TH1F *hAngleDataXiz[NEBins];
	//MC
	TH1F *hAngleMCEx[NEBins];
	TH1F *hAngleMCEy[NEBins];
	TH1F *hAngleMCEz[NEBins];
	TH1F *hAngleMCXix[NEBins];
	TH1F *hAngleMCXiy[NEBins];
	TH1F *hAngleMCXiz[NEBins];
	//Gen
	TH1F *hAngleGenEx[NEBins];
	TH1F *hAngleGenEy[NEBins];
	TH1F *hAngleGenEz[NEBins];
	TH1F *hAngleGenXix[NEBins];
	TH1F *hAngleGenXiy[NEBins];
	TH1F *hAngleGenXiz[NEBins];
	
	
	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	
	//yields for fitter
	//Data
	Double_t YieldDataEx[NEBins][NPiBins], YieldDataEy[NEBins][NPiBins], YieldDataEz[NEBins][NPiBins];
	Int_t  YieldDataExErr[NEBins][NPiBins], YieldDataEyErr[NEBins][NPiBins], YieldDataEzErr[NEBins][NPiBins];
	Double_t YieldDataXix[NXiBins][NPiBins], YieldDataXiy[NXiBins][NPiBins], YieldDataXiz[NXiBins][NPiBins];
	Int_t  YieldDataXixErr[NXiBins][NPiBins], YieldDataXiyErr[NXiBins][NPiBins], YieldDataXizErr[NXiBins][NPiBins];
	//MC
	Double_t YieldMCEx[NEBins][NPiBins], YieldMCEy[NEBins][NPiBins], YieldMCEz[NEBins][NPiBins];
	Int_t  YieldMCExErr[NEBins][NPiBins], YieldMCEyErr[NEBins][NPiBins], YieldMCEzErr[NEBins][NPiBins];
	Double_t YieldMCXix[NXiBins][NPiBins], YieldMCXiy[NXiBins][NPiBins], YieldMCXiz[NXiBins][NPiBins];
	Int_t  YieldMCXixErr[NXiBins][NPiBins], YieldMCXiyErr[NXiBins][NPiBins], YieldMCXizErr[NXiBins][NPiBins];
	//Gen	
	Double_t YieldGenEx[NEBins][NPiBins], YieldGenEy[NEBins][NPiBins], YieldGenEz[NEBins][NPiBins];
	Int_t  YieldGenExErr[NEBins][NPiBins], YieldGenEyErr[NEBins][NPiBins], YieldGenEzErr[NEBins][NPiBins];
	Double_t YieldGenXix[NXiBins][NPiBins], YieldGenXiy[NXiBins][NPiBins], YieldGenXiz[NXiBins][NPiBins];
	Int_t  YieldGenXixErr[NXiBins][NPiBins], YieldGenXiyErr[NXiBins][NPiBins], YieldGenXizErr[NXiBins][NPiBins];
	
	
	//initialize the global fitting parameters to a reasonable setting (they will change for Data and MC)
	Double_t fitLow = 1.2;
	Double_t fitHigh = 1.45;
	Double_t XiMass = 1.321;
	Double_t fitWidth = 0.0055;
	Double_t fitWidthFloat = 0.0005;
	Double_t t0 = 1;
	Double_t t1 = 1;
	Double_t t2 = 1;
	Double_t t3 = 0;
	Double_t t4 = 0;
	
	//setup 3 models yeild histograms
	TH1F *hAngleX = new TH1F("hAngleX","",NPiBins, -1,1);
	hAngleX->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");
	hAngleX->GetYaxis()->SetTitle("Counts");
	hAngleX->SetMinimum(0);
	hAngleX->SetMarkerStyle(21);
	TH1F *hAngleY = (TH1F*)hAngleX->Clone("hAngleY");
	hAngleY->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
	TH1F *hAngleZ = (TH1F*)hAngleX->Clone("hAngleZ");
	hAngleZ->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");



	//========================================================FITTING AND RECORDING===============================================================
	//*//<......data can........
	TCanvas *cDataEx = new TCanvas("cDataEx","cDataEx",1200,800);
	TCanvas *cDataEy = new TCanvas("cDataEy","cDataEy",1200,800);
	TCanvas *cDataEz = new TCanvas("cDataEz","cDataEz",1200,800);
	cDataEx->Divide(NPiBins,NEBins);
	cDataEy->Divide(NPiBins,NEBins);
	cDataEz->Divide(NPiBins,NEBins);
	TCanvas *cDataXix = new TCanvas("cDataXix","cDataXix",1200,800);
	TCanvas *cDataXiy = new TCanvas("cDataXiy","cDataXiy",1200,800);
	TCanvas *cDataXiz = new TCanvas("cDataXiz","cDataXiz",1200,800);
	cDataXix->Divide(NPiBins,NXiBins);
	cDataXiy->Divide(NPiBins,NXiBins);
	cDataXiz->Divide(NPiBins,NXiBins);
	//*///
	
	//*//<......mc can........
	TCanvas *cMCEx = new TCanvas("cMCEx","cMCEx",1200,800);
	TCanvas *cMCEy = new TCanvas("cMCEy","cMCEy",1200,800);
	TCanvas *cMCEz = new TCanvas("cMCEz","cMCEz",1200,800);
	cMCEx->Divide(NPiBins,NEBins);
	cMCEy->Divide(NPiBins,NEBins);
	cMCEz->Divide(NPiBins,NEBins);
	TCanvas *cMCXix = new TCanvas("cMCXix","cMCXix",1200,800);
	TCanvas *cMCXiy = new TCanvas("cMCXiy","cMCXiy",1200,800);
	TCanvas *cMCXiz = new TCanvas("cMCXiz","cMCXiz",1200,800);
	cMCXix->Divide(NPiBins,NXiBins);
	cMCXiy->Divide(NPiBins,NXiBins);
	cMCXiz->Divide(NPiBins,NXiBins);
	//*///
	
	//*//<......gen can........
	TCanvas *cGenEx = new TCanvas("cGenEx","cGenEx",1200,800);
	TCanvas *cGenEy = new TCanvas("cGenEy","cGenEy",1200,800);
	TCanvas *cGenEz = new TCanvas("cGenEz","cGenEz",1200,800);
	cGenEx->Divide(NPiBins,NEBins);
	cGenEy->Divide(NPiBins,NEBins);
	cGenEz->Divide(NPiBins,NEBins);
	TCanvas *cGenXix = new TCanvas("cGenXix","cGenXix",1200,800);
	TCanvas *cGenXiy = new TCanvas("cGenXiy","cGenXiy",1200,800);
	TCanvas *cGenXiz = new TCanvas("cGenXiz","cGenXiz",1200,800);
	cGenXix->Divide(NPiBins,NXiBins);
	cGenXiy->Divide(NPiBins,NXiBins);
	cGenXiz->Divide(NPiBins,NXiBins);
	//*///
	
	//initaize histograms
	//loop over energy bins
	for (int i = 0; i < NEBins; i++)
	{
		hAngleDataEx[i] = (TH1F*)hAngleX->Clone(Form("hAngleData-EBin%i-x",i));
		hAngleDataEy[i] = (TH1F*)hAngleY->Clone(Form("hAngleData-EBin%i-y",i));
		hAngleDataEz[i] = (TH1F*)hAngleZ->Clone(Form("hAngleData-EBin%i-z",i));
		
		hAngleMCEx[i] = (TH1F*)hAngleX->Clone(Form("hAngleMC-EBin%i-x",i));
		hAngleMCEy[i] = (TH1F*)hAngleY->Clone(Form("hAngleMC-EBin%i-y",i));
		hAngleMCEz[i] = (TH1F*)hAngleZ->Clone(Form("hAngleMC-EBin%i-z",i));
		
		hAngleGenEx[i] = (TH1F*)hAngleX->Clone(Form("hAngleGen-EBin%i-x",i));
		hAngleGenEy[i] = (TH1F*)hAngleY->Clone(Form("hAngleGen-EBin%i-y",i));
		hAngleGenEz[i] = (TH1F*)hAngleZ->Clone(Form("hAngleGen-EBin%i-z",i));
	}
	//loop over Xi bins
	for (int i = 0; i < NXiBins; i++)
	{
		hAngleDataXix[i] = (TH1F*)hAngleX->Clone(Form("hAngleData-XiBin%i-x",i));
		hAngleDataXiy[i] = (TH1F*)hAngleY->Clone(Form("hAngleData-XiBin%i-y",i));
		hAngleDataXiz[i] = (TH1F*)hAngleZ->Clone(Form("hAngleData-XiBin%i-z",i));
		
		hAngleMCXix[i] = (TH1F*)hAngleX->Clone(Form("hAngleMC-XiBin%i-x",i));
		hAngleMCXiy[i] = (TH1F*)hAngleY->Clone(Form("hAngleMC-XiBin%i-y",i));
		hAngleMCXiz[i] = (TH1F*)hAngleZ->Clone(Form("hAngleMC-XiBin%i-z",i));
		
		hAngleGenXix[i] = (TH1F*)hAngleX->Clone(Form("hAngleGen-XiBin%i-x",i));
		hAngleGenXiy[i] = (TH1F*)hAngleY->Clone(Form("hAngleGen-XiBin%i-y",i));
		hAngleGenXiz[i] = (TH1F*)hAngleZ->Clone(Form("hAngleGen-XiBin%i-z",i));
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~do everything with binning in Energy~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//loop over energy bins
	for (int i = 0; i < NEBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{

			//----------------------------------------------------------Data-----------------------------------------------------------------------
			t4=0; t3=0; t2=2; t1=1; t0=1; fitLow = 1.2; fitHigh = 1.45; fitWidth = 0.0045; fitWidthFloat = 0.0020;
			//*//<........................................................X.....................................................
			//get the yields
			cDataEx->cd(4*i + j + 1);
			hDataEx[i][j] = (TH1F*)fhS1->Get(Form("hData-EBin%i-PixBin%i",i,j));
			gausfit(hDataEx[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataEx[i][j],0,0,YieldDataExErr[i][j]);		
			//fix the yields in the backward piangle
			if(j == 0){YieldDataEx[i][j] = 20; YieldDataExErr[i][j] = 20;}
			//fill the yields to the histograms
		    hAngleDataEx[i]->SetBinContent(j+1,YieldDataEx[i][j]);
			hAngleDataEx[i]->SetBinError(j+1,YieldDataExErr[i][j]);
		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cDataEy->cd(4*i + j + 1);
			hDataEy[i][j] = (TH1F*)fhS1->Get(Form("hData-EBin%i-PiyBin%i",i,j));
			//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.0028;}
			gausfit(hDataEy[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataEy[i][j],0,0,YieldDataEyErr[i][j]);
			//reset the fitting parameters
			//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.005;}		
			//fill the yields to the histograms
		    hAngleDataEy[i]->SetBinContent(j+1,YieldDataEy[i][j]);
			hAngleDataEy[i]->SetBinError(j+1,YieldDataEyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cDataEz->cd(4*i + j + 1);
			hDataEz[i][j] = (TH1F*)fhS1->Get(Form("hData-EBin%i-PizBin%i",i,j));
			//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.0049;fitWidthFloat = 0.0008;}
			gausfit(hDataEz[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataEz[i][j],0,0,YieldDataEzErr[i][j]);
			//reset the fitting parameters
			//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.006;fitWidthFloat = 0.005;}		
			//fill the yields to the histograms
			//fix the yields in the forward piangle
			if(j == 3){YieldDataEz[i][j] = 20; YieldDataEzErr[i][j] = 20;}
			//fill the yields to the histograms
		    hAngleDataEz[i]->SetBinContent(j+1,YieldDataEz[i][j]);
			hAngleDataEz[i]->SetBinError(j+1,YieldDataEzErr[i][j]);
		  	//*///................................................................................................................................	
			//------------------------------------------------------------------------------------------------------------------------------------
			
			//----------------------------------------------------------MC-----------------------------------------------------------------------
			//set for linear background
			t4=0; t3=0; t2=0; t1=1; t0=1; fitLow = 1.27; fitHigh = 1.394; fitWidth = 0.007; fitWidthFloat = 0.0005;
			//*//<........................................................X.....................................................
			//get the yields
			cMCEx->cd(4*i + j + 1);
			hMCEx[i][j] = (TH1F*)fhS1->Get(Form("hMC-EBin%i-PixBin%i",i,j));
			if (simcount.compare(fit) == 0)
			{
				gausfit(hMCEx[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCEx[i][j],0,0,YieldMCExErr[i][j]);	
				//fix the yields in the backward pi angle
				if(YieldMCEx[i][j] < 10){YieldMCEx[i][j] = 10; YieldMCExErr[i][j] = 10;}
			}
			else if (simcount.compare(nofit) == 0)
			{
				YieldMCEx[i][j] = hMCEx[i][j]->GetEntries();
				YieldMCExErr[i][j] = sqrt(YieldMCEx[i][j]);
				hMCEx[i][j]->Draw();
			}
			//fill the yields/counts to the histograms
			hAngleMCEx[i]->SetBinContent(j+1,YieldMCEx[i][j]);
			hAngleMCEx[i]->SetBinError(j+1,YieldMCExErr[i][j]);

		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cMCEy->cd(4*i + j + 1);
			hMCEy[i][j] = (TH1F*)fhS1->Get(Form("hMC-EBin%i-PiyBin%i",i,j));
			if (simcount.compare(fit) == 0)
			{
				gausfit(hMCEy[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCEy[i][j],0,0,YieldMCEyErr[i][j]);		
				//fix the yields in the medium pi angle
				if(YieldMCEy[i][j] < 10){YieldMCEy[i][j] = 10; YieldMCEyErr[i][j] = 10;}
			}
			else if (simcount.compare(nofit) == 0)
			{
				YieldMCEy[i][j] = hMCEy[i][j]->GetEntries();
				YieldMCEyErr[i][j] = sqrt(YieldMCEy[i][j]);
				hMCEy[i][j]->Draw();
			}
			//fill the yields/counts to the histograms
		    hAngleMCEy[i]->SetBinContent(j+1,YieldMCEy[i][j]);
			hAngleMCEy[i]->SetBinError(j+1,YieldMCEyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cMCEz->cd(4*i + j + 1);
			hMCEz[i][j] = (TH1F*)fhS1->Get(Form("hMC-EBin%i-PizBin%i",i,j));
			if (simcount.compare(fit) == 0)
			{
				if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.0049;fitWidthFloat = 0.0008;}
				gausfit(hMCEz[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCEz[i][j],0,0,YieldMCEzErr[i][j]);		
			}
			else if (simcount.compare(nofit) == 0)
			{
				YieldMCEz[i][j] = hMCEz[i][j]->GetEntries();
				YieldMCEzErr[i][j] = sqrt(YieldMCEz[i][j]);
				hMCEz[i][j]->Draw();
			}
			//fill the yields/counts to the histograms
			//fix the yields in the backward piangle
			if((i==0 && j==3)||(i==2 && j==3)){YieldMCEz[i][j] = 10; YieldMCEzErr[i][j] = 10;}
			else if(i==1 && j==3){YieldMCEz[i][j] = 20; YieldMCEzErr[i][j] = 20;}
			
			
			//fill the yields to the histograms
		    hAngleMCEz[i]->SetBinContent(j+1,YieldMCEz[i][j]);
			hAngleMCEz[i]->SetBinError(j+1,YieldMCEzErr[i][j]);
		  	//*///................................................................................................................................
		
		
		
		
			//----------------------------------------------------------Gen-----------------------------------------------------------------------

			//*//<........................................................X.....................................................
			//get the yields
			cGenEx->cd(4*i + j + 1);
			hGenEx[i][j] = (TH1F*)fhS1->Get(Form("hGen-EBin%i-PixBin%i",i,j));
			//count rather than fit
			YieldGenEx[i][j] = hGenEx[i][j]->GetEntries();
			YieldGenExErr[i][j] = sqrt(YieldGenEx[i][j]);
			hGenEx[i][j]->Draw();		
		    hAngleGenEx[i]->SetBinContent(j+1,YieldGenEx[i][j]);
			hAngleGenEx[i]->SetBinError(j+1,YieldGenExErr[i][j]);
		  	//*///................................................................................................................................
			
		
			//*//<........................................................Y.....................................................
			//get the yields
			cGenEy->cd(4*i + j + 1);
			hGenEy[i][j] = (TH1F*)fhS1->Get(Form("hGen-EBin%i-PiyBin%i",i,j));
			//count rather than fit
			YieldGenEy[i][j] = hGenEy[i][j]->GetEntries();
			YieldGenEyErr[i][j] = sqrt(YieldGenEy[i][j]);
			hGenEy[i][j]->Draw();		
		    hAngleGenEy[i]->SetBinContent(j+1,YieldGenEy[i][j]);
			hAngleGenEy[i]->SetBinError(j+1,YieldGenEyErr[i][j]);
		  	//*///................................................................................................................................
		
		
			//*//<........................................................Z.....................................................
			//get the yields
			cGenEz->cd(4*i + j + 1);
			hGenEz[i][j] = (TH1F*)fhS1->Get(Form("hGen-EBin%i-PizBin%i",i,j));
			//count rather than fit
			YieldGenEz[i][j] = hGenEz[i][j]->GetEntries();
			YieldGenEzErr[i][j] = sqrt(YieldGenEz[i][j]);
			hGenEz[i][j]->Draw();		
		    hAngleGenEz[i]->SetBinContent(j+1,YieldGenEz[i][j]);
			hAngleGenEz[i]->SetBinError(j+1,YieldGenEzErr[i][j]);
		  	//*///................................................................................................................................
		
		
				
		}
		hAngleDataEx[i]->Write();
		hAngleDataEy[i]->Write();
		hAngleDataEz[i]->Write();
		hAngleMCEx[i]->Write();
		hAngleMCEy[i]->Write();
		hAngleMCEz[i]->Write();
		hAngleGenEx[i]->Write();
		hAngleGenEy[i]->Write();
		hAngleGenEz[i]->Write();
	}
	


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~do everything with binning in XiCM Angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//loop over energy bins
	for (int i = 0; i < NXiBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{

			//----------------------------------------------------------Data-----------------------------------------------------------------------
			t4=0; t3=0; t2=2; t1=1; t0=1; fitLow = 1.25; fitHigh = 1.41; fitWidth = 0.0045; fitWidthFloat = 0.0025;
			//*//<........................................................X.....................................................
			//get the yields
			cDataXix->cd(4*i + j + 1);
			hDataXix[i][j] = (TH1F*)fhS1->Get(Form("hData-XiBin%i-PixBin%i",i,j));
			gausfit(hDataXix[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataXix[i][j],0,0,YieldDataXixErr[i][j]);		
			//fix the yields in the backward piangle
			if(j == 0){YieldDataXix[i][j] = 20; YieldDataXixErr[i][j] = 20;}
			//fill the yields to the histograms
		    hAngleDataXix[i]->SetBinContent(j+1,YieldDataXix[i][j]);
			hAngleDataXix[i]->SetBinError(j+1,YieldDataExErr[i][j]);
		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cDataXiy->cd(4*i + j + 1);
			hDataXiy[i][j] = (TH1F*)fhS1->Get(Form("hData-XiBin%i-PiyBin%i",i,j));
			//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.0028;}
			gausfit(hDataXiy[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataXiy[i][j],0,0,YieldDataXiyErr[i][j]);
			//reset the fitting parameters
			//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.005;}		
			//fill the yields to the histograms
		    hAngleDataXiy[i]->SetBinContent(j+1,YieldDataXiy[i][j]);
			hAngleDataXiy[i]->SetBinError(j+1,YieldDataXiyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cDataXiz->cd(4*i + j + 1);
			hDataXiz[i][j] = (TH1F*)fhS1->Get(Form("hData-XiBin%i-PizBin%i",i,j));
			//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.0049;fitWidthFloat = 0.0008;}
			gausfit(hDataXiz[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataXiz[i][j],0,0,YieldDataXizErr[i][j]);
			//reset the fitting parameters
			//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.006;fitWidthFloat = 0.005;}		
			//fill the yields to the histograms
			//fix the yields in the forward piangle
			if(j == 3){YieldDataXiz[i][j] = 20; YieldDataXizErr[i][j] = 20;}
			//fill the yields to the histograms
		    hAngleDataXiz[i]->SetBinContent(j+1,YieldDataXiz[i][j]);
			hAngleDataXiz[i]->SetBinError(j+1,YieldDataXizErr[i][j]);
		  	//*///................................................................................................................................	
			//------------------------------------------------------------------------------------------------------------------------------------
			
			//----------------------------------------------------------MC-----------------------------------------------------------------------
			//set for linear background
			t4=0; t3=0; t2=0; t1=1; t0=1; fitLow = 1.27; fitHigh = 1.394; fitWidth = 0.007; fitWidthFloat = 0.0005;
			//*//<........................................................X.....................................................
			//get the yields
			cMCXix->cd(4*i + j + 1);
			hMCXix[i][j] = (TH1F*)fhS1->Get(Form("hMC-XiBin%i-PixBin%i",i,j));
			if (simcount.compare(fit) == 0)
			{
				gausfit(hMCXix[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCXix[i][j],0,0,YieldMCXixErr[i][j]);		
				//fix the yields in the backward pi angle	
				if(YieldMCXix[i][j] < 10){YieldMCXix[i][j] = 10; YieldMCXixErr[i][j] = 10;}
			}
			else if (simcount.compare(nofit) == 0)
			{
				YieldMCXix[i][j] = hMCXix[i][j]->GetEntries();
				YieldMCXixErr[i][j] = sqrt(YieldMCXix[i][j]);
				hMCXix[i][j]->Draw();
			}
			//fill the yields to the histograms
		    hAngleMCXix[i]->SetBinContent(j+1,YieldMCXix[i][j]);
			hAngleMCXix[i]->SetBinError(j+1,YieldMCXixErr[i][j]);
		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cMCXiy->cd(4*i + j + 1);
			hMCXiy[i][j] = (TH1F*)fhS1->Get(Form("hMC-XiBin%i-PiyBin%i",i,j));
			if (simcount.compare(fit) == 0)
			{
				gausfit(hMCXiy[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCXiy[i][j],0,0,YieldMCXiyErr[i][j]);		
				//fix the yields in the medium pi angle
				if(YieldMCXiy[i][j] < 10){YieldMCXiy[i][j] = 10; YieldMCXiyErr[i][j] = 10;}
			}
			else if (simcount.compare(nofit) == 0)
			{
				YieldMCXiy[i][j] = hMCXiy[i][j]->GetEntries();
				YieldMCXiyErr[i][j] = sqrt(YieldMCXiy[i][j]);
				hMCXiy[i][j]->Draw();
			}
			//fill the yields to the histograms
		    hAngleMCXiy[i]->SetBinContent(j+1,YieldMCXiy[i][j]);
			hAngleMCXiy[i]->SetBinError(j+1,YieldMCXiyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cMCXiz->cd(4*i + j + 1);
			hMCXiz[i][j] = (TH1F*)fhS1->Get(Form("hMC-XiBin%i-PizBin%i",i,j));
			if (simcount.compare(fit) == 0)
			{
				if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.0049;fitWidthFloat = 0.0008;}
				gausfit(hMCXiz[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCXiz[i][j],0,0,YieldMCXizErr[i][j]);		
				//fix the yields in the backward piangle
				if((i==0 && j==3)||(i==2 && j==3)){YieldMCXiz[i][j] = 10; YieldMCXizErr[i][j] = 10;}
				else if(i==1 && j==3){YieldMCXiz[i][j] = 20; YieldMCXizErr[i][j] = 20;}
			}
			else if (simcount.compare(nofit) == 0)
			{
				YieldMCXiz[i][j] = hMCXiz[i][j]->GetEntries();
				YieldMCXizErr[i][j] = sqrt(YieldMCXiz[i][j]);
				hMCXiz[i][j]->Draw();
			}
			//fill the yields to the histograms
		    hAngleMCXiz[i]->SetBinContent(j+1,YieldMCXiz[i][j]);
			hAngleMCXiz[i]->SetBinError(j+1,YieldMCXizErr[i][j]);
		  	//*///................................................................................................................................
		
		
		
		
			//----------------------------------------------------------Gen-----------------------------------------------------------------------

			//*//<........................................................X.....................................................
			//get the yields
			cGenXix->cd(4*i + j + 1);
			hGenXix[i][j] = (TH1F*)fhS1->Get(Form("hGen-XiBin%i-PixBin%i",i,j));
			//count rather than fit
			YieldGenXix[i][j] = hGenXix[i][j]->GetEntries();
			YieldGenXixErr[i][j] = sqrt(YieldGenXix[i][j]);
			hGenXix[i][j]->Draw();		
		    hAngleGenXix[i]->SetBinContent(j+1,YieldGenXix[i][j]);
			hAngleGenXix[i]->SetBinError(j+1,YieldGenXixErr[i][j]);
		  	//*///................................................................................................................................
			
		
			//*//<........................................................Y.....................................................
			//get the yields
			cGenXiy->cd(4*i + j + 1);
			hGenXiy[i][j] = (TH1F*)fhS1->Get(Form("hGen-XiBin%i-PiyBin%i",i,j));
			//count rather than fit
			YieldGenXiy[i][j] = hGenXiy[i][j]->GetEntries();
			YieldGenXiyErr[i][j] = sqrt(YieldGenXiy[i][j]);
			hGenXiy[i][j]->Draw();		
		    hAngleGenXiy[i]->SetBinContent(j+1,YieldGenXiy[i][j]);
			hAngleGenXiy[i]->SetBinError(j+1,YieldGenXiyErr[i][j]);
		  	//*///................................................................................................................................
		
		
			//*//<........................................................Z.....................................................
			//get the yields
			cGenXiz->cd(4*i + j + 1);
			hGenXiz[i][j] = (TH1F*)fhS1->Get(Form("hGen-XiBin%i-PizBin%i",i,j));
			//count rather than fit
			YieldGenXiz[i][j] = hGenXiz[i][j]->GetEntries();
			YieldGenXizErr[i][j] = sqrt(YieldGenXiz[i][j]);
			hGenXiz[i][j]->Draw();		
		    hAngleGenXiz[i]->SetBinContent(j+1,YieldGenXiz[i][j]);
			hAngleGenXiz[i]->SetBinError(j+1,YieldGenXizErr[i][j]);
		  	//*///................................................................................................................................
		
		
				
		}
		hAngleDataXix[i]->Write();
		hAngleDataXiy[i]->Write();
		hAngleDataXiz[i]->Write();
		hAngleMCXix[i]->Write();
		hAngleMCXiy[i]->Write();
		hAngleMCXiz[i]->Write();
		hAngleGenXix[i]->Write();
		hAngleGenXiy[i]->Write();
		hAngleGenXiz[i]->Write();
	}
	
	

	



	//gROOT->ProcessLine(".q");
}	
	
	
	
