/*
Name: Stage2.C
Author: Jason Bono
Date: October 22 2012
Purpose: To take the ouput of Stage1.C & to get yields and output the histograms representing the angular distribution of the pion in the jackson frame
Input: ./hists/histsStage1.root
Output: ./hists/histsStage2.root

Usage: change the methods for fitting or no fitting by editing the two strings "datacount" & "simcount"
	
	if the histograms were obtained from Stage1.C using the hypersphere cut than choose NO FIT!
	if they were obtained using simpler cuts that introduce a larger background fitting choose FIT!
	the fit is needed for an accurate yeild with background subtraction with background is present or complex

Notes: 
	!Read the comment section in GetW.C for more background!

History: 
Jan 8 2013 the option for nofit for the data was added

*/


#include "/Users/Bono/clas/myDefinitions/Bins222FIXED.h" //kept for NBins definitions, must match Stage1.C



void Stage2()
{


	char *s = new char[1]; //this is for interactive session
	const string datacount ("nofit"); //<------change this according to how you want the data to be counted
	const string simcount ("nofit"); //<------change this according to how you want the accepted events to be counted
	
	const string fit ("fit"); //keep theese the same
	const string nofit ("nofit");


	// checking with interactive statments
	if (datacount.compare(fit) == 0)
	{
		cout << "The fit method for data: type enter to accept" <<endl;	
		gets(s);
		cout << "Fit method for data accepted" << endl;
		gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	}
	else if (datacount.compare(nofit) == 0)
	{
		cout << "The no-fit method for data: Type enter to accept" <<endl;
		gets(s);
		cout << "The no-fit method for data accepted" << endl;
	}
	else 
	{
		cout << "somthing is wrong, terminating program" <<endl;
		gROOT->ProcessLine(".q");
	}
	
	if (simcount.compare(fit) == 0)
	{
		cout << "The fit method for simulation: type enter to accept" <<endl;	
		gets(s);
		cout << "Fit method for simulation accepted" << endl;
		//gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	}
	else if (simcount.compare(nofit) == 0)
	{
		cout << "The no-fit method for simulation: Type enter to accept" <<endl;
		gets(s);
		cout << "The no-fit method for simulation accepted" << endl;
	}
	else 
	{
		cout << "somthing is wrong, terminating program" <<endl;
		gROOT->ProcessLine(".q");
	}


	
	//open the ouput of Stage1.C and new file to write
	TFile* fhS1 = new TFile("./hists/histsStage1.root");
	TFile* fhS2 = new TFile("./hists/histsStage2.root","RECREATE");	

	//declare the hists which will be read in
	//Data
	TH1D *hDataEx[NPiBins][NEBins];
	TH1D *hDataEy[NPiBins][NEBins];
	TH1D *hDataEz[NPiBins][NEBins];
	TH1D *hDataXix[NPiBins][NXiBins];
	TH1D *hDataXiy[NPiBins][NXiBins];
	TH1D *hDataXiz[NPiBins][NXiBins];
	//MC
	TH1D *hMCEx[NPiBins][NEBins];
	TH1D *hMCEy[NPiBins][NEBins];
	TH1D *hMCEz[NPiBins][NEBins];
	TH1D *hMCXix[NPiBins][NXiBins];
	TH1D *hMCXiy[NPiBins][NXiBins];
	TH1D *hMCXiz[NPiBins][NXiBins];
	//Gen
	TH1D *hGenEx[NPiBins][NEBins];
	TH1D *hGenEy[NPiBins][NEBins];
	TH1D *hGenEz[NPiBins][NEBins];
	TH1D *hGenXix[NPiBins][NXiBins];
	TH1D *hGenXiy[NPiBins][NXiBins];
	TH1D *hGenXiz[NPiBins][NXiBins];
	
	//declare the hists which will be written
	//Data
	TH1D *hAngleDataEx[NEBins];
	TH1D *hAngleDataEy[NEBins];
	TH1D *hAngleDataEz[NEBins];
	TH1D *hAngleDataXix[NXiBins];
	TH1D *hAngleDataXiy[NXiBins];
	TH1D *hAngleDataXiz[NXiBins];
	//MC
	TH1D *hAngleMCEx[NEBins];
	TH1D *hAngleMCEy[NEBins];
	TH1D *hAngleMCEz[NEBins];
	TH1D *hAngleMCXix[NXiBins];
	TH1D *hAngleMCXiy[NXiBins];
	TH1D *hAngleMCXiz[NXiBins];
	//Gen
	TH1D *hAngleGenEx[NEBins];
	TH1D *hAngleGenEy[NEBins];
	TH1D *hAngleGenEz[NEBins];
	TH1D *hAngleGenXix[NXiBins];
	TH1D *hAngleGenXiy[NXiBins];
	TH1D *hAngleGenXiz[NXiBins];
	
	
	//yields for fitter
	//Data
	Double_t YieldDataEx[NPiBins][NEBins], YieldDataEy[NPiBins][NEBins], YieldDataEz[NPiBins][NEBins];
	Double_t  YieldDataExErr[NPiBins][NEBins], YieldDataEyErr[NPiBins][NEBins], YieldDataEzErr[NPiBins][NEBins];
	Double_t YieldDataXix[NPiBins][NXiBins], YieldDataXiy[NPiBins][NXiBins], YieldDataXiz[NPiBins][NXiBins];
	Double_t  YieldDataXixErr[NPiBins][NXiBins], YieldDataXiyErr[NPiBins][NXiBins], YieldDataXizErr[NPiBins][NXiBins];
	//MC
	Double_t YieldMCEx[NPiBins][NEBins], YieldMCEy[NPiBins][NEBins], YieldMCEz[NPiBins][NEBins];
	Double_t  YieldMCExErr[NPiBins][NEBins], YieldMCEyErr[NPiBins][NEBins], YieldMCEzErr[NPiBins][NEBins];
	Double_t YieldMCXix[NPiBins][NXiBins], YieldMCXiy[NPiBins][NXiBins], YieldMCXiz[NPiBins][NXiBins];
	Double_t  YieldMCXixErr[NPiBins][NXiBins], YieldMCXiyErr[NPiBins][NXiBins], YieldMCXizErr[NPiBins][NXiBins];
	//Gen	
	Double_t YieldGenEx[NPiBins][NEBins], YieldGenEy[NPiBins][NEBins], YieldGenEz[NPiBins][NEBins];
	Double_t  YieldGenExErr[NPiBins][NEBins], YieldGenEyErr[NPiBins][NEBins], YieldGenEzErr[NPiBins][NEBins];
	Double_t YieldGenXix[NPiBins][NXiBins], YieldGenXiy[NPiBins][NXiBins], YieldGenXiz[NPiBins][NXiBins];
	Double_t  YieldGenXixErr[NPiBins][NXiBins], YieldGenXiyErr[NPiBins][NXiBins], YieldGenXizErr[NPiBins][NXiBins];
	
	
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
	TH1D *hAngleX = new TH1D("hAngleX","",NPiBins, -1,1);
	hAngleX->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");
	hAngleX->GetYaxis()->SetTitle("Counts");
	hAngleX->SetMinimum(0);
	hAngleX->SetMarkerStyle(21);
	TH1D *hAngleY = (TH1D*)hAngleX->Clone("hAngleY");
	hAngleY->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
	TH1D *hAngleZ = (TH1D*)hAngleX->Clone("hAngleZ");
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
	for (int j = 0; j < NEBins; j++)
	{
		hAngleDataEx[j] = (TH1D*)hAngleX->Clone(Form("hAngleData-EBin%i-x",j));
		hAngleDataEy[j] = (TH1D*)hAngleY->Clone(Form("hAngleData-EBin%i-y",j));
		hAngleDataEz[j] = (TH1D*)hAngleZ->Clone(Form("hAngleData-EBin%i-z",j));
		
		hAngleMCEx[j] = (TH1D*)hAngleX->Clone(Form("hAngleMC-EBin%i-x",j));
		hAngleMCEy[j] = (TH1D*)hAngleY->Clone(Form("hAngleMC-EBin%i-y",j));
		hAngleMCEz[j] = (TH1D*)hAngleZ->Clone(Form("hAngleMC-EBin%i-z",j));
		
		hAngleGenEx[j] = (TH1D*)hAngleX->Clone(Form("hAngleGen-EBin%i-x",j));
		hAngleGenEy[j] = (TH1D*)hAngleY->Clone(Form("hAngleGen-EBin%i-y",j));
		hAngleGenEz[j] = (TH1D*)hAngleZ->Clone(Form("hAngleGen-EBin%i-z",j));
	}
	//loop over Xi bins
	for (int j = 0; j < NXiBins; j++)
	{
		hAngleDataXix[j] = (TH1D*)hAngleX->Clone(Form("hAngleData-XiBin%i-x",j));
		hAngleDataXiy[j] = (TH1D*)hAngleY->Clone(Form("hAngleData-XiBin%i-y",j));
		hAngleDataXiz[j] = (TH1D*)hAngleZ->Clone(Form("hAngleData-XiBin%i-z",j));
		
		hAngleMCXix[j] = (TH1D*)hAngleX->Clone(Form("hAngleMC-XiBin%i-x",j));
		hAngleMCXiy[j] = (TH1D*)hAngleY->Clone(Form("hAngleMC-XiBin%i-y",j));
		hAngleMCXiz[j] = (TH1D*)hAngleZ->Clone(Form("hAngleMC-XiBin%i-z",j));
		
		hAngleGenXix[j] = (TH1D*)hAngleX->Clone(Form("hAngleGen-XiBin%i-x",j));
		hAngleGenXiy[j] = (TH1D*)hAngleY->Clone(Form("hAngleGen-XiBin%i-y",j));
		hAngleGenXiz[j] = (TH1D*)hAngleZ->Clone(Form("hAngleGen-XiBin%i-z",j));
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~do everything with binning in Energy~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//loop over Pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over energy bins
		for (int j = 0; j < NEBins; j++)
		{

			//----------------------------------------------------------Data-----------------------------------------------------------------------
			cout << "STARTING Energy Data!  i,j = " << i <<","<< j << endl;
			
			t4=1; t3=1; t2=1; t1=1; t0=1; fitLow = 1.2; fitHigh = 1.45; fitWidth = 0.0045; fitWidthFloat = 0.0020;
			//*//<........................................................X.....................................................
			//get the yields
			cout << " above canvase " <<endl;
			cDataEx->cd(i + 4*j + 1);
			cout << " below canvase " <<endl;
			hDataEx[i][j] = (TH1D*)fhS1->Get(Form("hData-PixBin%i-EBin%i",i,j));
			cout << " below hdataex " <<endl;
			if (datacount.compare(fit) == 0)
			{
				gausfit(hDataEx[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataEx[i][j],0,0,YieldDataExErr[i][j]);		
				//fix the yields in the backward piangle
				if(j == 0){YieldDataEx[i][j] = 20; YieldDataExErr[i][j] = 20;}
			}
			else if (datacount.compare(nofit) == 0)
			{
				cout << " in else if " <<endl;
				YieldDataEx[i][j] = hDataEx[i][j]->GetEntries();
				YieldDataExErr[i][j] = sqrt(YieldDataEx[i][j]);
				hDataEx[i][j]->Draw();
				cout << " end of else if " <<endl;
			}
			//fill the yields to the histograms

		    hAngleDataEx[j]->SetBinContent(i + 1,YieldDataEx[i][j]);
			hAngleDataEx[j]->SetBinError(i + 1,YieldDataExErr[i][j]);


		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cDataEy->cd(i + 4*j + 1);
			hDataEy[i][j] = (TH1D*)fhS1->Get(Form("hData-PiyBin%i-EBin%i",i,j));
			if (datacount.compare(fit) == 0)
			{
				//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.0028;}
				gausfit(hDataEy[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataEy[i][j],0,0,YieldDataEyErr[i][j]);
				//reset the fitting parameters
				//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.005;}		
			}	
			else if (datacount.compare(nofit) == 0)
			{
				YieldDataEy[i][j] = hDataEy[i][j]->GetEntries();
				YieldDataEyErr[i][j] = sqrt(YieldDataEy[i][j]);
				hDataEy[i][j]->Draw();
			}
			//fill the yields to the histograms
		    hAngleDataEy[j]->SetBinContent(i + 1,YieldDataEy[i][j]);
			hAngleDataEy[j]->SetBinError(i + 1,YieldDataEyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cDataEz->cd(i + 4*j + 1);
			hDataEz[i][j] = (TH1D*)fhS1->Get(Form("hData-PizBin%i-EBin%i",i,j));
			if (datacount.compare(fit) == 0)
			{
				//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.0049;fitWidthFloat = 0.0008;}
				gausfit(hDataEz[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataEz[i][j],0,0,YieldDataEzErr[i][j]);
				//reset the fitting parameters
				//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.006;fitWidthFloat = 0.005;}		
				//fill the yields to the histograms
				//fix the yields in the forward piangle
				if(j == 3){YieldDataEz[i][j] = 20; YieldDataEzErr[i][j] = 20;}
		    }
			else if (datacount.compare(nofit) == 0)
			{
				YieldDataEz[i][j] = hDataEz[i][j]->GetEntries();
				YieldDataEzErr[i][j] = sqrt(YieldDataEz[i][j]);
				hDataEz[i][j]->Draw();
			}
			//fill the yields to the histograms
			hAngleDataEz[j]->SetBinContent(i + 1,YieldDataEz[i][j]);
			hAngleDataEz[j]->SetBinError(i + 1,YieldDataEzErr[i][j]);

		  	//*///................................................................................................................................	
			//------------------------------------------------------------------------------------------------------------------------------------
			
			//----------------------------------------------------------MC-----------------------------------------------------------------------
			cout << "STARTING Energy MC!" << endl;
			//set for linear background
			t4=0; t3=0; t2=0; t1=1; t0=1; fitLow = 1.27; fitHigh = 1.394; fitWidth = 0.007; fitWidthFloat = 0.0005;
			//*//<........................................................X.....................................................
			//get the yields
			cMCEx->cd(i + 4*j + 1);
			hMCEx[i][j] = (TH1D*)fhS1->Get(Form("hMC-PixBin%i-EBin%i",i,j));
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
			hAngleMCEx[j]->SetBinContent(i + 1,YieldMCEx[i][j]);
			hAngleMCEx[j]->SetBinError(i + 1,YieldMCExErr[i][j]);

		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cMCEy->cd(i + 4*j + 1);
			hMCEy[i][j] = (TH1D*)fhS1->Get(Form("hMC-PiyBin%i-EBin%i",i,j));
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
		    hAngleMCEy[j]->SetBinContent(i + 1,YieldMCEy[i][j]);
			hAngleMCEy[j]->SetBinError(i + 1,YieldMCEyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cMCEz->cd(i + 4*j + 1);
			hMCEz[i][j] = (TH1D*)fhS1->Get(Form("hMC-PizBin%i-EBin%i",i,j));
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
			
			//fill the yields to the histograms
		    hAngleMCEz[j]->SetBinContent(i + 1,YieldMCEz[i][j]);
			hAngleMCEz[j]->SetBinError(i + 1,YieldMCEzErr[i][j]);
		  	//*///................................................................................................................................
		
		
		
		
			//----------------------------------------------------------Gen-----------------------------------------------------------------------
			cout << "STARTING Energy Gen!" << endl;
			//*//<........................................................X.....................................................
			//get the yields
			cGenEx->cd(i + 4*j + 1);
			hGenEx[i][j] = (TH1D*)fhS1->Get(Form("hGen-PixBin%i-EBin%i",i,j));
			//count rather than fit. generated events should never need to be fitted.
			YieldGenEx[i][j] = hGenEx[i][j]->GetEntries();
			YieldGenExErr[i][j] = sqrt(YieldGenEx[i][j]);
			hGenEx[i][j]->Draw();		
		    hAngleGenEx[j]->SetBinContent(i + 1,YieldGenEx[i][j]);
			hAngleGenEx[j]->SetBinError(i + 1,YieldGenExErr[i][j]);
		  	//*///................................................................................................................................
			
		
			//*//<........................................................Y.....................................................
			//get the yields
			cGenEy->cd(i + 4*j + 1);
			hGenEy[i][j] = (TH1D*)fhS1->Get(Form("hGen-PiyBin%i-EBin%i",i,j));
			//count rather than fit. generated events should never need to be fitted.
			YieldGenEy[i][j] = hGenEy[i][j]->GetEntries();
			YieldGenEyErr[i][j] = sqrt(YieldGenEy[i][j]);
			hGenEy[i][j]->Draw();		
		    hAngleGenEy[j]->SetBinContent(i + 1,YieldGenEy[i][j]);
			hAngleGenEy[j]->SetBinError(i + 1,YieldGenEyErr[i][j]);
		  	//*///................................................................................................................................
		
		
			//*//<........................................................Z.....................................................
			//get the yields
			cGenEz->cd(i + 4*j + 1);
			hGenEz[i][j] = (TH1D*)fhS1->Get(Form("hGen-PizBin%i-EBin%i",i,j));
			//count rather than fit. generated events should never need to be fitted.
			YieldGenEz[i][j] = hGenEz[i][j]->GetEntries();
			YieldGenEzErr[i][j] = sqrt(YieldGenEz[i][j]);
			hGenEz[i][j]->Draw();		
		    hAngleGenEz[j]->SetBinContent(i + 1,YieldGenEz[i][j]);
			hAngleGenEz[j]->SetBinError(i + 1,YieldGenEzErr[i][j]);
		  	//*///................................................................................................................................
		
		
				
		}
	}
	
	//loop over E bins
	for (int j = 0; j < NEBins; j++)
	{
		hAngleDataEx[j]->Write();
		hAngleDataEy[j]->Write();
		hAngleDataEz[j]->Write();
		hAngleMCEx[j]->Write();
		hAngleMCEy[j]->Write();
		hAngleMCEz[j]->Write();
		hAngleGenEx[j]->Write();
		hAngleGenEy[j]->Write();
		hAngleGenEz[j]->Write();
	}
	


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~do everything with binning in XiCM Angle~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//loop over pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over Xi bins
		for (int j = 0; j < NXiBins; j++)
		{

			//----------------------------------------------------------Data-----------------------------------------------------------------------
			cout << "STARTING Xi Data!" << endl;
			t4=0; t3=0; t2=2; t1=1; t0=1; fitLow = 1.25; fitHigh = 1.41; fitWidth = 0.0045; fitWidthFloat = 0.0025;
			//*//<........................................................X.....................................................
			//get the yields
			cDataXix->cd(i + 4*j + 1);
			hDataXix[i][j] = (TH1D*)fhS1->Get(Form("hData-PixBin%i-XiBin%i",i,j));
			
			if (datacount.compare(fit) == 0)
			{	
				gausfit(hDataXix[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataXix[i][j],0,0,YieldDataXixErr[i][j]);		
				//fix the yields in the backward piangle
				if(j == 0){YieldDataXix[i][j] = 20; YieldDataXixErr[i][j] = 20;}
			}
			else if (datacount.compare(nofit) == 0)
			{
				YieldDataXix[i][j] = hDataXix[i][j]->GetEntries();
				YieldDataXixErr[i][j] = sqrt(YieldDataXix[i][j]);
				hDataXix[i][j]->Draw();
			}
			//fill the yields to the histograms
		    hAngleDataXix[j]->SetBinContent(i + 1,YieldDataXix[i][j]);
			hAngleDataXix[j]->SetBinError(i + 1,YieldDataExErr[i][j]);
		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cDataXiy->cd(i + 4*j + 1);
			hDataXiy[i][j] = (TH1D*)fhS1->Get(Form("hData-PiyBin%i-XiBin%i",i,j));
			
			if (datacount.compare(fit) == 0)
			{
				//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.0028;}
				gausfit(hDataXiy[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataXiy[i][j],0,0,YieldDataXiyErr[i][j]);
				//reset the fitting parameters
				//if((i == 1 && j == 2)||(i == 2 && j == 1 )){fitWidthFloat = 0.005;}		
			}
			else if (datacount.compare(nofit) == 0)
			{
				YieldDataXiy[i][j] = hDataXiy[i][j]->GetEntries();
				YieldDataXiyErr[i][j] = sqrt(YieldDataXiy[i][j]);
				hDataXiy[i][j]->Draw();
			}
			//fill the yields to the histograms
		    hAngleDataXiy[j]->SetBinContent(i + 1,YieldDataXiy[i][j]);
			hAngleDataXiy[j]->SetBinError(i + 1,YieldDataXiyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cDataXiz->cd(i + 4*j + 1);
			hDataXiz[i][j] = (TH1D*)fhS1->Get(Form("hData-PizBin%i-XiBin%i",i,j));
			
			if (datacount.compare(fit) == 0)
			{	
				//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.0049;fitWidthFloat = 0.0008;}
				gausfit(hDataXiz[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataXiz[i][j],0,0,YieldDataXizErr[i][j]);
				//reset the fitting parameters
				//if((i == 1 && j == 2)||(i == 2 && j == 0 )){Double_t fitWidth = 0.006;fitWidthFloat = 0.005;}		
				//fill the yields to the histograms
				//fix the yields in the forward piangle
				if(j == 3){YieldDataXiz[i][j] = 20; YieldDataXizErr[i][j] = 20;}
			}
			else if (datacount.compare(nofit) == 0)
			{
				YieldDataXiz[i][j] = hDataXiz[i][j]->GetEntries();
				YieldDataXizErr[i][j] = sqrt(YieldDataXiz[i][j]);
				hDataXiz[i][j]->Draw();
			}
			
			//fill the yields to the histograms
		    hAngleDataXiz[j]->SetBinContent(i + 1,YieldDataXiz[i][j]);
			hAngleDataXiz[j]->SetBinError(i + 1,YieldDataXizErr[i][j]);
		  	//*///................................................................................................................................	
			//------------------------------------------------------------------------------------------------------------------------------------
			
			//----------------------------------------------------------MC-----------------------------------------------------------------------
			cout << "STARTING Xi MC!" << endl;
			//set for linear background
			t4=0; t3=0; t2=0; t1=1; t0=1; fitLow = 1.27; fitHigh = 1.394; fitWidth = 0.007; fitWidthFloat = 0.0005;
			//*//<........................................................X.....................................................
			//get the yields
			cMCXix->cd(i + 4*j + 1);
			hMCXix[i][j] = (TH1D*)fhS1->Get(Form("hMC-PixBin%i-XiBin%i",i,j));
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
		    hAngleMCXix[j]->SetBinContent(i + 1,YieldMCXix[i][j]);
			hAngleMCXix[j]->SetBinError(i + 1,YieldMCXixErr[i][j]);
		  	//*///................................................................................................................................
			
			//*//<........................................................Y.....................................................
			//get the yields
			cMCXiy->cd(i + 4*j + 1);
			hMCXiy[i][j] = (TH1D*)fhS1->Get(Form("hMC-PiyBin%i-XiBin%i",i,j));
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
		    hAngleMCXiy[j]->SetBinContent(i + 1,YieldMCXiy[i][j]);
			hAngleMCXiy[j]->SetBinError(i + 1,YieldMCXiyErr[i][j]);
		  	//*///................................................................................................................................
		
			//*//<........................................................Z.....................................................
			//get the yields
			cMCXiz->cd(i + 4*j + 1);
			hMCXiz[i][j] = (TH1D*)fhS1->Get(Form("hMC-PizBin%i-XiBin%i",i,j));
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
		    hAngleMCXiz[j]->SetBinContent(i + 1,YieldMCXiz[i][j]);
			hAngleMCXiz[j]->SetBinError(i + 1,YieldMCXizErr[i][j]);
		  	//*///................................................................................................................................
		
		
		
		
			//----------------------------------------------------------Gen-----------------------------------------------------------------------
			cout << "STARTING Xi Gen!" << endl;
			//*//<........................................................X.....................................................
			//get the yields
			cGenXix->cd(i + 4*j + 1);
			hGenXix[i][j] = (TH1D*)fhS1->Get(Form("hGen-PixBin%i-XiBin%i",i,j));
			//count rather than fit. generated events should never need to be fitted. 
			YieldGenXix[i][j] = hGenXix[i][j]->GetEntries();
			YieldGenXixErr[i][j] = sqrt(YieldGenXix[i][j]);
			hGenXix[i][j]->Draw();		
		    hAngleGenXix[j]->SetBinContent(i + 1,YieldGenXix[i][j]);
			hAngleGenXix[j]->SetBinError(i + 1,YieldGenXixErr[i][j]);
		  	//*///................................................................................................................................
			
		
			//*//<........................................................Y.....................................................
			//get the yields
			cGenXiy->cd(i + 4*j + 1);
			hGenXiy[i][j] = (TH1D*)fhS1->Get(Form("hGen-PiyBin%i-XiBin%i",i,j));
			//count rather than fit. generated events should never need to be fitted.
			YieldGenXiy[i][j] = hGenXiy[i][j]->GetEntries();
			YieldGenXiyErr[i][j] = sqrt(YieldGenXiy[i][j]);
			hGenXiy[i][j]->Draw();		
		    hAngleGenXiy[j]->SetBinContent(i + 1,YieldGenXiy[i][j]);
			hAngleGenXiy[j]->SetBinError(i + 1,YieldGenXiyErr[i][j]);
		  	//*///................................................................................................................................
		
		
			//*//<........................................................Z.....................................................
			//get the yields
			cGenXiz->cd(i + 4*j + 1);
			hGenXiz[i][j] = (TH1D*)fhS1->Get(Form("hGen-PizBin%i-XiBin%i",i,j));
			//count rather than fit. generated events should never need to be fitted.
			YieldGenXiz[i][j] = hGenXiz[i][j]->GetEntries();
			YieldGenXizErr[i][j] = sqrt(YieldGenXiz[i][j]);
			hGenXiz[i][j]->Draw();		
		    hAngleGenXiz[j]->SetBinContent(i + 1,YieldGenXiz[i][j]);
			hAngleGenXiz[j]->SetBinError(i + 1,YieldGenXizErr[i][j]);
		  	//*///................................................................................................................................
		
			
		}
	}
	//loop over Xi bins
	for (int j = 0; j < NXiBins; j++)
	{
		hAngleDataXix[j]->Write();
		hAngleDataXiy[j]->Write();
		hAngleDataXiz[j]->Write();
		hAngleMCXix[j]->Write();
		hAngleMCXiy[j]->Write();
		hAngleMCXiz[j]->Write();
		hAngleGenXix[j]->Write();
		hAngleGenXiy[j]->Write();
		hAngleGenXiz[j]->Write();
	}
	
	
	/*/read the bin centers and rms values, output to txt file
	Double_t xPionBinMean[NPiBins],yPionBinMean[NPiBins],zPionBinMean[NPiBins];
	Double_t xPionBinRMS[NPiBins],yPionBinRMS[NPiBins],zPionBinRMS[NPiBins];
	TH1D *hPionBins[NPiBins];
	for (int i = 0; i < NPiBins; i++){
		
		cout <<	hPionBin[i]->GetMean() << endl;
		cout <<	hPionBin[i]->GetRMS() << endl;
		cout << endl;
	}
	
	
	*/
	
	
	
	//gROOT->ProcessLine(".q");
}	
	
	
	
