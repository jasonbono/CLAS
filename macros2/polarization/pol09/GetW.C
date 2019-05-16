/*

Date: Jan 8 2012

Author: Jason Bono

Purpose: To find the normalization factor in order to effectively match the beam energy spectra of the simulation and the data.

Input: Data,MC
Output: ./txt/Winfo.txt

Usage:   (look for the arrows <-------1----  , <-------2---- etc)

		1) Choose hyperesphere or lam cuts (whatever is chosen, choose the same in Stage1.C and if hypersphere is chosen: choose no-fit for stage2.C. see those macros for more details)
		2) Choose Signal or Sideband (also specify the files if they have changed)
		3) Choose number of W bins "NWBins" (this will be distinct from NEBins in the "Stage" macros)
		4) Choose "depth" (for hypersphere only)
		
		5) > .x GetW.C
		6) copy output from terminal window into Stage1.C
		
Notes:		
		the choices above must be matched with the choices in Stage1.C, Stage2.C, Stage3.C, Stage4.C
		for example(s): 
		a) If hyperesphere is choosen then choose hyperesphere in Stage1.C and choose no-fit for stage2.C.
		b) Whatever root files are chosen as input the same should be chosen in Stage1.C
		c) The NWBin value must match for this macro and Stage1.C
		
 
Other Notes: 
		W is simply the Yeild of the Data divided by the Yield of the MC in each energy bin.
		Werr[i] is calculated assuming yieldData and yieldMC are unclorrelated ie the covarience is zero.


*/


void GetW(){


	//open two txt files for writing	
	ofstream myWfile;
	myWfile.open ("./txt/Winfo.txt");

	//~~~~~~~~~~~~~~~~~Define variables for cut type to be used~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char *s = new char[1]; 
	//const string cuttype ("lam"); //<------------1a------
	const string cuttype ("hypersphere"); //<------------1b------
	const string lamOption ("lam");
	const string hyperOption ("hypersphere");
	// checking with interactive statments
	if (cuttype.compare(lamOption) == 0)
	{
		cout << "The lam cut: type enter to accept" <<endl;	
		gets(s);
		cout << "The lam cut accepted" << endl;
	}
	else if (cuttype.compare(hyperOption) == 0)
	{
		cout << "The hypersphere cut: Type enter to accept" <<endl;
		gets(s);
		cout << "The hypersphere cut accepted" << endl;
	}
	else 
	{
		cout << "somthing is wrong, terminating program" <<endl;
		gROOT->ProcessLine(".q");
	}
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CHOOSE SIGNAL OR SIDEBAND~~~~~~~~~~~~~~~~~~~~~~~~~
	//*//<----2a------FOR SIGNAL
	TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/2kppim-v05.root");
	TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/sim/MC_i3_2kppim_Basic.root");
 	TTree *tData = (TTree*)fData->Get("v05_Basic");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");
	//*///
		
	/*//<------2b---FOR SIDEBAND
	TFile* fData = new TFile("~/clas/rootfiles/Links/Reduced/2kppim-v05-sb.root"); 
	TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/sim/Reduced/MC_i2_2kppim_sb.root");
	TTree *tData = (TTree*)fData->Get("v05_sb"); //<------
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_sb");
	//*///
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	
	


	//~~~~~~~~~~~~~~~~~~~~INITALIZE DELCARE LOAD~~~~~~~~~~~~~~~~~~~~~~~
	const Int_t NWBins = 28;	//<----3-----CHOOSE NUMBER OF WEIGHTING BINS
	Double_t YieldData[NWBins], YieldMC[NWBins] ;
	Int_t YieldDataErr[NWBins], YieldMCErr[NWBins];
	Double_t W[NWBins],Werr[NWBins];	
 	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	// . . . . . . . . . . . . . . . . . . . . . . . . .  . . . . . . . . . . 



	//~~~~~~~~~~Define Varibles For Hyperspherecut~~~~~~~~~~~~
	float sigmaA = 0.0113;
	float sigmaB = 0.0107;
	float sigmaC = 0.0031;
	float sigmaD = 0.0030;
	float depth = 3; //<-----------4---------

	//theese are fixed
	float widthA = depth*sigmaA;
	float widthB = depth*sigmaB;
	float widthC = depth*sigmaC;
	float widthD = depth*sigmaD;
	float MASS_Xi = 1.321;
	float MASS_Lambda = 1.116;
	//. . . . . . . . . . . . . . . . . . . . .


	//cuts
	//cuts
	if(NWBins == 28){
		TString WBin[NWBins];
		WBin[0] = "beam > 2.7 && beam < 2.8";
		WBin[1] = "beam > 2.8 && beam < 2.9";
		WBin[2] = "beam > 2.9 && beam < 3.0";
		WBin[3] = "beam > 3.0 && beam < 3.1";
		WBin[4] = "beam > 3.1 && beam < 3.2";
		WBin[5] = "beam > 3.2 && beam < 3.3";
		WBin[6] = "beam > 3.3 && beam < 3.4";
		WBin[7] = "beam > 3.4 && beam < 3.5";
		WBin[8] = "beam > 3.5 && beam < 3.6";
		WBin[9] = "beam > 3.6 && beam < 3.7";
		WBin[10] = "beam > 3.7 && beam < 3.8";
		WBin[11] = "beam > 3.8 && beam < 3.9";
		WBin[12] = "beam > 3.9 && beam < 4.0";
		WBin[13] = "beam > 4.0 && beam < 4.1";
		WBin[14] = "beam > 4.1 && beam < 4.2";
		WBin[15] = "beam > 4.2 && beam < 4.3";
		WBin[16] = "beam > 4.3 && beam < 4.4";
		WBin[17] = "beam > 4.4 && beam < 4.5";
		WBin[18] = "beam > 4.5 && beam < 4.6";
		WBin[19] = "beam > 4.6 && beam < 4.7";
		WBin[20] = "beam > 4.7 && beam < 4.8";
		WBin[21] = "beam > 4.8 && beam < 4.9";
		WBin[22] = "beam > 4.9 && beam < 5.0";
		WBin[23] = "beam > 5.0 && beam < 5.1";
		WBin[24] = "beam > 5.1 && beam < 5.2";
		WBin[25] = "beam > 5.2 && beam < 5.3";
		WBin[26] = "beam > 5.3 && beam < 5.4";
		WBin[27] = "beam > 5.4 && beam < 5.5";
	}
	if(NWBins == 11){
		TString WBin[NWBins];
		WBin[0] = "beam > 2.7 && beam < 3.0";
		WBin[1] = "beam > 3.0 && beam < 3.2";
		WBin[2] = "beam > 3.2 && beam < 3.4";
		WBin[3] = "beam > 3.4 && beam < 3.6";
		WBin[4] = "beam > 3.6 && beam < 3.8";
		WBin[5] = "beam > 3.8 && beam < 4.0";
		WBin[6] = "beam > 4.0 && beam < 4.3";
		WBin[7] = "beam > 4.3 && beam < 4.6";
		WBin[8] = "beam > 4.6 && beam < 4.9";
		WBin[9] = "beam > 4.9 && beam < 5.2";
		WBin[10] = "beam > 5.2 && beam < 5.5";
	}
	if(NWBins == 3){
		TString WBin[NWBins];
		WBin[0] = "beam > 2.7 && beam < 3.6 ";
		WBin[1] = "beam > 3.6 && beam < 4.5 ";
		WBin[2] = "beam > 4.5 && beam < 5.5 ";	
	}

	
	//the mass cut
	
	TString lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";	
	TString hypersphere = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	
	if (cuttype.compare(lamOption) == 0)
	{
		TString cut=lam;
	}
	else if (cuttype.compare(hyperOption) == 0)
	{
		TString cut=hypersphere;	
	}
	TString Cut[NWBins];
	for (int i = 0; i < NWBins ; i++)
 	{
		
		Cut[i] = WBin[i] + "&&" + cut;
		cout << "Cut[i] = " << Cut[i] <<endl;

	}
	
	
	
	//canvases
	TCanvas *c0=new TCanvas("c0","",700,400);
	TCanvas *cData=new TCanvas("cData","cData",1200,800);	
	TCanvas *cMC=new TCanvas("cMC","cMC",1200,800);
	cData->Divide(6,5);
	cMC->Divide(6,5);
	c0->cd();
	
	
	//set up the histograms
	TH1F *h=new TH1F("h","",80,1.2,1.6);
	tData->Draw("mlampim>>h");
	h->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	h->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	TH1F *hData[NWBins], *hMC[NWBins];

	
	//specify the fitting variables
	Double_t fitLow = 1.2;
	Double_t fitHigh = 1.6;
	Double_t XiMass = 1.321;
	Double_t fitWidth = 0.012;
	Double_t fitWidthFloat = 0.007;
	
	Double_t fitmcLow = 1.25;
	Double_t fitmcHigh = 1.4;
	Double_t fitmcWidth = 0.012;
	Double_t fitmcWidthFloat = 0.007;
	
	//-----------------------------------------start the iteration------------------------------------
	int j;
	for (int i = 0; i < NWBins ; i++)
 	{
	
		//Do the fit
		j = i + 1;
		cData->cd(j);
		hData[i] = (TH1F*)h->Clone(Form("hData%i",i));	
		tData->Draw(Form("mlampim>>hData%i",i),Cut[i]);	
		if (cuttype.compare(lamOption) == 0)
		{
				gausfit(hData[i],1,fitLow,fitHigh,1,1,1,1,1,XiMass,fitWidth,fitWidthFloat,3,0,YieldData[i],0,0,YieldDataErr[i]);
		}
		else if (cuttype.compare(hyperOption) == 0)
		{
				YieldData[i] = hData[i]->GetEntries();
				YieldDataErr[i] = sqrt(YieldData[i]);	
		}

		
		
		cMC->cd(j);
		hMC[i] = (TH1F*)h->Clone(Form("hMC%i",i));	
		tMC->Draw(Form("mlampim>>hMC%i",i),Cut[i]);	
		if (cuttype.compare(lamOption) == 0)
		{
				gausfit(hMC[i],1,fitmcLow,fitmcHigh,1,0,0,0,0,XiMass,fitmcWidth,fitmcWidthFloat,3,0,YieldMC[i],0,0,YieldMCErr[i]);
		}
		else if (cuttype.compare(hyperOption) == 0)
		{
				YieldMC[i] = hMC[i]->GetEntries();
				YieldMCErr[i] = sqrt(YieldMC[i]);
		}
	
 	

		//Compute W and Werr 
		W[i] = YieldData[i]/YieldMC[i];
		Werr[i] = W[i]*sqrt((YieldDataErr[i]/YieldData[i])*(YieldDataErr[i]/YieldData[i]) + (YieldMCErr[i]/YieldMC[i])*(YieldMCErr[i]/YieldMC[i]));
	}



	//check again
	for (int i = 0; i < NWBins ; i++) 
	{
		cout << "yield for data is:  " <<YieldData[i] << " +- " << YieldDataErr[i] <<endl;
		cout << "yield for MC is:    " <<YieldMC[i] << " +- " << YieldMCErr[i] <<endl;
		cout << "the weighting factor is:    " <<W[i] << " +- " << Werr[i] <<endl;
		cout << endl;
	}
	
	//output the results to the screen
	for (int i = 0; i < NWBins ; i++) 
	{
		cout <<W[i] << ", ";
	}
	cout << ""<<endl;
	cout << "======================================W above, Werr below ==================================" << endl;
	cout << "" <<endl;
	for (int i = 0; i < NWBins ; i++) 
	{
		cout << Werr[i] << ", ";
		
		//record the W info into the txt file
		if(W[i] > 0 && W[i] < 9000000){  //only for good values
			myWfile << W[i]<< " " <<Werr[i] <<endl;
		} 
		else // if get something like inf or nan then just print zero to the file
		{
			W[i] = 0;
			Werr[i] = 0;
			myWfile << W[i]<< " " <<Werr[i] <<endl;
		}
	}
		myWfile.close();
}