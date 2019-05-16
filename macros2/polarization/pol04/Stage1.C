/*

Name: Stage1.C
Author: Jason Bono
Date: October 22 2012
Purpose: To spit out the hists in bins of Xicmtheta and beamenergy as a "function" of all three PiAngles

Usage: 

	1) make sure the W vector is set to correct initalization. 
	2) specify in the output root file if this was binned in beam or Xi angle
	3) uncomment and comment the appropriate blocks according to the binning in data, mc & gamp

Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events

*/


void Stage1()
{
	
	
	//open the files and create the proper tree pointers
	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v01.root");     // DATA histograms
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC_i1_2kppim.root");         // MC histograms
	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/MC_i1_gamp.root");       // GEN histograms 
	// make aliases for the trees from each file
	TTree *tData = (TTree*)fData->Get("v01_Basic");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");
	TTree *tGen = (TTree*)fGen->Get("GampTree");
	
	//create a new file to store the histograms
	TFile* fHistos = new TFile("./hists/histsStage1.root","NEW");

	

	//----------------binning----------------
	const int NEBins = 3; // this is how many energy bins the Ws were calculated for in GetW.C
	const int NXiBins = 3; 
	const int NPiBins = 4;
	
	//-----------The weighting factors---------
	if(NEBins == 3){
		const Double_t W[NEBins] =	{0.225431, 0.329841, 0.962296};
		const Double_t Werr[NEBins] =	{0.0083008, 0.0127671, 0.0616886};	
	}

	//-------define cuts that define the bins---------
	if(NEBins == 3 && NPiBins == 4 ){
		
		//energy bins
		TCut EBin[NEBins];
		EBin[0] = "beam > 3.3 && beam < 4.0 ";
		EBin[1] = "beam > 4.0 && beam < 4.7 ";
		EBin[2] = "beam > 4.7 && beam < 5.4 ";
		
		TString EBinName[NXiBins];
		EBinName[0] = "E-low";
		EBinName[1] = "E-intermediate";
		EBinName[2] = "E-high";
		
	
		//Xicm bins
		TCut XiBin[NXiBins];
		XiBin[0] = "Xcmtheta > -1.0 && Xcmtheta < -0.333";
		XiBin[1] = "Xcmtheta > -0.333 && Xcmtheta < 0.333";
		XiBin[2] = "Xcmtheta > 0.333 && Xcmtheta < 1.0";
		
		TString XiBinName[NXiBins];
		XiBinName[0] = "Xi-backward";
		XiBinName[1] = "Xi-intermediate";
		XiBinName[2] = "Xi-forward";

		//the missing mass cut on lambda
		TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
		
		//pion angle bins
		TCut  PixBin[NPiBins];
		PixBin[0] = "COS_pi_x > -1.0 && COS_pi_x < -0.5";
		PixBin[1] = "COS_pi_x > -0.5 && COS_pi_x < 0.0";
		PixBin[2] = "COS_pi_x > 0.0 && COS_pi_x < 0.5";
		PixBin[3] = "COS_pi_x > 0.5 && COS_pi_x < 1.0";	
		TCut  PiyBin[NPiBins];
		PiyBin[0] = "COS_pi_y > -1.0 && COS_pi_y < -0.5";
		PiyBin[1] = "COS_pi_y > -0.5 && COS_pi_y < 0.0";
		PiyBin[2] = "COS_pi_y > 0.0 && COS_pi_y < 0.5";
		PiyBin[3] = "COS_pi_y > 0.5 && COS_pi_y < 1.0";
		TCut  PizBin[NPiBins];
		PizBin[0] = "COS_pi_z > -1.0 && COS_pi_z < -0.5";
		PizBin[1] = "COS_pi_z > -0.5 && COS_pi_z < 0.0";
		PizBin[2] = "COS_pi_z > 0.0 && COS_pi_z < 0.5";
		PizBin[3] = "COS_pi_z > 0.5 && COS_pi_z < 1.0";
	}
	
	//create model for the missing mass histograms
	TH1F *h=new TH1F("h","",40,1.2,1.6);
	h->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	h->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	h->SetMinimum(0);

	//----------------------------Data------------------------------------------

	//the data histogram
	TH1F *hDataXix[NXiBins][NPiBins];
	TH1F *hDataXiy[NXiBins][NPiBins];
	TH1F *hDataXiz[NXiBins][NPiBins];
	TH1F *hDataEx[NEBins][NPiBins];
	TH1F *hDataEy[NEBins][NPiBins];
	TH1F *hDataEz[NEBins][NPiBins];
	
	
	//loop over Xi bins
	for (int i = 0; i < NEBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			
			//energy binning
			hDataEx[i][j] = (TH1F*)h->Clone(Form("hData-EBin%i-PixBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-EBin%i-PixBin%i",i,j),lam&&EBin[i]&&PixBin[j]);		
			hDataEx[i][j]->Write();	
			hDataEy[i][j] = (TH1F*)h->Clone(Form("hData-EBin%i-PiyBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-EBin%i-PiyBin%i",i,j),lam&&EBin[i]&&PiyBin[j]);		
			hDataEy[i][j]->Write();
			hDataEz[i][j] = (TH1F*)h->Clone(Form("hData-EBin%i-PizBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-EBin%i-PizBin%i",i,j),lam&&EBin[i]&&PizBin[j]);		
			hDataEz[i][j]->Write();
			
		}
	}


	//----------------------------MC------------------------------------------

	//the MC histogram
	TH1F *hMCXix[NXiBins][NPiBins];
	TH1F *hMCXiy[NXiBins][NPiBins];
	TH1F *hMCXiz[NXiBins][NPiBins];
	TH1F *hMCEx[NEBins][NPiBins];
	TH1F *hMCEy[NEBins][NPiBins];
	TH1F *hMCEz[NEBins][NPiBins];
	
	
	//loop over Xi bins
	for (int i = 0; i < NEBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			
			//energy binning
			hMCEx[i][j] = (TH1F*)h->Clone(Form("hMC-EBin%i-PixBin%i",i,j));
			tMC->Draw(Form("mlampim>>hMC-EBin%i-PixBin%i",i,j),lam&&EBin[i]&&PixBin[j]);		
			hMCEx[i][j]->Write();	
			hMCEy[i][j] = (TH1F*)h->Clone(Form("hMC-EBin%i-PiyBin%i",i,j));
			tMC->Draw(Form("mlampim>>hMC-EBin%i-PiyBin%i",i,j),lam&&EBin[i]&&PiyBin[j]);		
			hMCEy[i][j]->Write();
			hMCEz[i][j] = (TH1F*)h->Clone(Form("hMC-EBin%i-PizBin%i",i,j));
			tMC->Draw(Form("mlampim>>hMC-EBin%i-PizBin%i",i,j),lam&&EBin[i]&&PizBin[j]);		
			hMCEz[i][j]->Write();
			
		}
	}

	//----------------------------Gen------------------------------------------

	//the Gen histogram
	TH1F *hGenXix[NXiBins][NPiBins];
	TH1F *hGenXiy[NXiBins][NPiBins];
	TH1F *hGenXiz[NXiBins][NPiBins];
	
	TH1F *hGenEx[NEBins][NPiBins];
	TH1F *hGenEy[NEBins][NPiBins];
	TH1F *hGenEz[NEBins][NPiBins];
	
	
	//loop over Xi bins
	for (int i = 0; i < NEBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			
			//energy binning
			hGenEx[i][j] = (TH1F*)h->Clone(Form("hGen-EBin%i-PixBin%i",i,j));
			tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PixBin%i",i,j),EBin[i]&&PixBin[j]);		
			hGenEx[i][j]->Write();	
			hGenEy[i][j] = (TH1F*)h->Clone(Form("hGen-EBin%i-PiyBin%i",i,j));
			tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PiyBin%i",i,j),EBin[i]&&PiyBin[j]);		
			hGenEy[i][j]->Write();
			hGenEz[i][j] = (TH1F*)h->Clone(Form("hGen-EBin%i-PizBin%i",i,j));
			tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PizBin%i",i,j),EBin[i]&&PizBin[j]);		
			hGenEz[i][j]->Write();
			
		}
	}







	gROOT->ProcessLine(".q");

}

