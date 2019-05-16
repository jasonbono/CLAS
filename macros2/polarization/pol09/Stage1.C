/*

Name: Stage1.C
Author: Jason Bono
Date: October 22 2012
Purpose: To spit out the histograms in bins of Xicmtheta and beamenergy as a "function" of all three PiAngles
This also verifys that the altered beam energy spectrum of the simulation matches the data
Input: Data,MC,Gen files,Winfo.txt, BeamSpectrum.eps
Output: ./hists/histsStage1.root


Usage: 

	1) Choose the string "cuttype" to be defined as lam or hypersphere which chooses the type of cut
	2) Choose block to uncomment (sideband or signal
	3) Set Gamp factor (value should be the factor by which the gamp file being read was earlier randomly reduced)
	4) Choose binning (make sure this matches with GetW.C and all other Stage#.C macros)
	5) Choose the approprate input file name
	then
	.x Stage1.C
	Follow prompts
	

Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events
	If the hypersphere cut routine is used than you should set a nofit in Stage2.C
	If the lam cut routine is used than Stage2.C must implement the gaussian fitter.
	!Read the comment section in GetW.C for more background!

History: January 8 2013: added gampfactor for reduced files.  added hypersphere cut option
jan 24: added check for the beam spectrum, made it so it reads in a text file rather than copy paste.

*/





void Stage1()
{

	//~~~~~~~~~~~~~~~~~~~~~Define Variables for cut type to be used~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char *s = new char[1]; //this is for interactive session
	const string cuttype ("hypersphere"); //<------1-----
	const string lamOption ("lam"); //keep this the same
	const string hyperOption ("hypersphere"); //keep this the same
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
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	
	
	
	//~~~~~~~~~~~~~~~~~~~~~Define Variables for files~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//*//<----------2a
	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v05.root");
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/sim/MC_i3_2kppim_Basic.root");  
	TTree *tData = (TTree*)fData->Get("v05_Basic");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");
	//*///

	/*//<-----------2b
	TFile* fData = new TFile("~/clas/rootfiles/Links/Reduced/2kppim-v05-sb.root"); 
    TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/sim/Reduced/MC_i2_2kppim_sb.root");
	TTree *tData = (TTree*)fData->Get("v05_sb"); 
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_sb");
	//*///
	
	//Generated events
	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/sim/MC_i3_gamp_100.root");
	TTree *tGen = (TTree*)fGen->Get("GampTree_100");
	Float_t gampfactor = 100; //<----3
	
	//New file to store the histograms
	TFile* fHistos = new TFile("./hists/histsStage1.root","RECREATE");
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 



	//~~~~~~~~Choose Binning~~~
	const int NWBins = 28; //<------4a-----
	const int NEBins = 3; //<------4b-----
	const int NXiBins = 3; //<------4c-----
	const int NPiBins = 4; //<------4d-----
	// . . . . . . . . . . . .

	//------Define Varibles For Hyperspherecut---------
	float sigmaA = 0.0113;
	float sigmaB = 0.0107;
	float sigmaC = 0.0031;
	float sigmaD = 0.0030;
	float depth = 3; //<------4e-----

	//theese are fixed
	float widthA = depth*sigmaA;
	float widthB = depth*sigmaB;
	float widthC = depth*sigmaC;
	float widthD = depth*sigmaD;
	float MASS_Xi = 1.321;
	float MASS_Lambda = 1.116;
	// . . . . . . . . . . . . . . . . . . . . . . . . . . .


	
	//-----------The weighting factors <----5-----
	if(NWBins == 28){
		
		ifstream in("./txt/Winfo.txt"); // input
	  	if(!in) {
	    	cout << "Cannot open txt file.\n";
			gROOT->ProcessLine(".q");
	  	}
		float W[NWBins] = {0},Werr[NWBins] = {0};

		for (int k = 0; k < NWBins ; k++) 
		{
	  		in >> W[k] >> Werr[k];
	  		cout << "W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		}
			in.close();	
		
		
		//signal
		//const Double_t W[NWBins] =	{0.0437973, 0.0648952, 0.228951};
		//const Double_t Werr[NWBins] =	{0.00114927, 0.00114925, 0.00496395};		
		//sideband
		//const Double_t W[NEBins] = {0.264398, 0.431034, 0.813187};
		//const Double_t Werr[NEBins] =  {0.0166739, 0.0410624, 0.11915};
		 
	}

	//-------define cuts that define the bins---------
	if(NWBins == 28 && NEBins == 3 && NXiBins == 3 && NPiBins == 4 ){
		
		
		//W bins (weighting factor)
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
		
		
		
		
		
		//energy bins
		TCut EBin[NEBins];
		EBin[0] = "beam > 2.7 && beam < 3.6 ";
		EBin[1] = "beam > 3.6 && beam < 4.5 ";
		EBin[2] = "beam > 4.5 && beam < 5.5 ";	
		
		TString EBinName[NEBins];
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


	//----------------------------------MASS CUTS------------------------------------------ 
	TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
		
	TCut hypersphere = Form("sqrt(  (mmkpkp - %f)*(mmkpkp - %f)/(%f*%f) + (mmkpkppim - %f)*(mmkpkppim - %f)/(%f*%f) + (mlampim - %f)*(mlampim - %f)/(%f*%f) + (mcasmMpim - %f)*(mcasmMpim - %f)/(%f*%f)) < 1"
	,MASS_Xi,MASS_Xi,widthA,widthA,MASS_Lambda,MASS_Lambda,widthB,widthB,MASS_Xi,MASS_Xi,widthC,widthC,MASS_Lambda,MASS_Lambda,widthD,widthD);
	if (cuttype.compare(lamOption) == 0)
	{
		TCut cut=lam;
	}
	else if (cuttype.compare(hyperOption) == 0)
	{
		TCut cut=hypersphere;
	}


	//====================================================================================
	//====================================================================================
	//====================================================================================
	
	//create model for the missing mass histograms (will use as clone)
	TH1F *h=new TH1F("h","",160,1.2,1.68);
	h->GetYaxis()->SetTitle("Events/3MeV/c^{2}");  
	h->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	h->SetMinimum(0);
	
	//and the model for comparing the beam energy spectrum
	TH1F *hBeam=new TH1F("hBeam","",28,2.7,5.5);
	hBeam->GetYaxis()->SetTitle("Events");  
	hBeam->GetXaxis()->SetTitle("Beam Energy (GeV)");
	hBeam->SetMinimum(0);
	
	
	//*//<----------------------------Data------------------------------------------
	cout << "STARTING Data" << endl;
	//the data histogram
	TH1F *hDataEx[NPiBins][NEBins];
	TH1F *hDataEy[NPiBins][NEBins];
	TH1F *hDataEz[NPiBins][NEBins];
	TH1F *hDataXix[NPiBins][NXiBins];
	TH1F *hDataXiy[NPiBins][NXiBins];
	TH1F *hDataXiz[NPiBins][NXiBins];
	//fill for comparing the beam energy spectrum
	TH1F *hBeamData;
	hBeamData = (TH1F*)hBeam->Clone("hBeamData");
	tData->Draw("beam>>hBeamData",cut);

	//loop over pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over energy bins
		for (int j = 0; j < NEBins; j++)
		{
			//energy binning
			hDataEx[i][j] = (TH1F*)h->Clone(Form("hData-PixBin%i-EBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-PixBin%i-EBin%i",i,j),cut&&EBin[j]&&PixBin[i]);
			hDataEx[i][j]->Write();
			hDataEy[i][j] = (TH1F*)h->Clone(Form("hData-PiyBin%i-EBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-PiyBin%i-EBin%i",i,j),cut&&EBin[j]&&PiyBin[i]);
			hDataEy[i][j]->Write();
			hDataEz[i][j] = (TH1F*)h->Clone(Form("hData-PizBin%i-EBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-PizBin%i-EBin%i",i,j),cut&&EBin[j]&&PizBin[i]);
			hDataEz[i][j]->Write();
		}
		
		//loop over Xi bins
		for (int j = 0; j < NXiBins; j++)
		{
			//Xi binning
			hDataXix[i][j] = (TH1F*)h->Clone(Form("hData-PixBin%i-XiBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-PixBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PixBin[i]);		
			hDataXix[i][j]->Write();	
			hDataXiy[i][j] = (TH1F*)h->Clone(Form("hData-PiyBin%i-XiBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-PiyBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PiyBin[i]);		
			hDataXiy[i][j]->Write();
			hDataXiz[i][j] = (TH1F*)h->Clone(Form("hData-PizBin%i-XiBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-PizBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PizBin[i]);		
			hDataXiz[i][j]->Write();	
		}
	}
	cout << "Data FINISHED!" << endl;
	cout <<endl;
	
	
	//*///
	//*//<<---------------------------MC------------------------------------------
	cout << "STARTING MC" << endl;
	
	Double_t EventsMCE[NPiBins][NEBins] = { 0 };
	Double_t EventsMCEw[NPiBins][NEBins] = { 0 };
	Double_t FacMCE[NPiBins][NEBins] = { 0 };
	Double_t EventsMCXi[NPiBins][NXiBins] = { 0 };
	Double_t EventsMCXiw[NPiBins][NXiBins] = { 0 };
	Double_t FacMCXi[NPiBins][NXiBins] = { 0 };
	//the MC histogram
	TH1F *hMCEx[NPiBins][NEBins];
	TH1F *hMCEy[NPiBins][NEBins];
	TH1F *hMCEz[NPiBins][NEBins];
	TH1F *hMCXix[NPiBins][NXiBins];
	TH1F *hMCXiy[NPiBins][NXiBins];
	TH1F *hMCXiz[NPiBins][NXiBins];
	//the rank 3 MC histograms
	TH1F *hMCR3Ex[NPiBins][NEBins][NWBins];
	TH1F *hMCR3Ey[NPiBins][NEBins][NWBins];
	TH1F *hMCR3Ez[NPiBins][NEBins][NWBins];
	TH1F *hMCR3Xix[NPiBins][NXiBins][NWBins];
	TH1F *hMCR3Xiy[NPiBins][NXiBins][NWBins];
	TH1F *hMCR3Xiz[NPiBins][NXiBins][NWBins];
	
	//........histogram for comparing the beam energy spectrum..................
	TH1F *hBeamMC;
	hBeamMC = (TH1F*)hBeam->Clone("hBeamMC");
	tMC->Draw("beam>>hBeamMC",cut);
	TH1F *hBeamGen;
	hBeamGen = (TH1F*)hBeam->Clone("hBeamGen");
	tGen->Draw("beam>>hBeamGen");

	TH1F *hBeamMC_Wtot;	
	hBeamMC_Wtot = (TH1F*)hBeam->Clone("hBeamMC_Wtot");	
	TH1F *hBeamMC_W[NWBins];
	//loop over W bins
	for (int k = 0; k < NWBins; k++)
	{
		hBeamMC_W[k] = (TH1F*)hBeam->Clone(Form("hBeamMC_W%i",k));
		tMC->Draw(Form("beam>>hBeamMC_W%i",k),cut&&WBin[k]);	
		hBeamMC_Wtot->Add(hBeamMC_W[k],W[k]);
	}
	//draw the plots of the beam energy spectrum
	TCanvas *cBeam=new TCanvas("cBeam","cBeam",1200,800);
	cBeam->Divide(2,2);
	cBeam->cd(1);
	hBeamData->Draw();
	cBeam->cd(2);
	hBeamMC->Draw();
	cBeam->cd(3);
	hBeamMC_Wtot->Draw();
	cBeam->cd(4);	
	hBeamGen->Draw();
	cBeam->Print("./pics/BeamSpectrum.eps");
 
	//...........................................................................
	
//*//	
	//loop over pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over energy bins
		for (int j = 0; j < NEBins; j++)
		{
			//initize the E bined histograms
			hMCEx[i][j] = (TH1F*)h->Clone(Form("hMC-PixBin%i-EBin%i",i,j));
			hMCEy[i][j] = (TH1F*)h->Clone(Form("hMC-PiyBin%i-EBin%i",i,j));
			hMCEz[i][j] = (TH1F*)h->Clone(Form("hMC-PizBin%i-EBin%i",i,j));
		
			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{

				//fill the energy rank 3 histograms
				hMCR3Ex[i][j][k] = (TH1F*)h->Clone(Form("hMC-PixBin%i-EBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-PixBin%i-EBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PixBin[i]&&EBin[j]);		
				hMCR3Ey[i][j][k] = (TH1F*)h->Clone(Form("hMC-PiyBin%i-EBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-PiyBin%i-EBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PiyBin[i]&&EBin[j]);
				hMCR3Ez[i][j][k] = (TH1F*)h->Clone(Form("hMC-PizBin%i-EBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-PizBin%i-EBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PizBin[i]&&EBin[j]);

				//contract from rank 3 to rank 2 using weighting factor
				hMCEx[i][j]->Add(hMCR3Ex[i][j][k],W[k]);
				hMCEy[i][j]->Add(hMCR3Ey[i][j][k],W[k]);
				hMCEz[i][j]->Add(hMCR3Ez[i][j][k],W[k]);

				//to count total events in MC
				EventsMCE[i][j] = EventsMCE[i][j] + hMCR3Ex[i][j][k]->GetEntries();
			}
			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			EventsMCEw[i][j] = hMCEx[i][j]->GetEntries();
			FacMCE[i][j] = EventsMCE[i][j]/EventsMCEw[i][j] - 1;
			cout<<"i: "<<i<<"  j: "<<j<<"  EventsMCE: " <<EventsMCE[i][j]<<"  EventsMCEw: " <<EventsMCEw[i][j]<<"  FacMCE: "<<  FacMCE[i][j] <<endl;
			hMCEx[i][j]->Add(hMCEx[i][j],FacMCE[i][j]);
			hMCEy[i][j]->Add(hMCEy[i][j],FacMCE[i][j]);
			hMCEz[i][j]->Add(hMCEz[i][j],FacMCE[i][j]);
		
			//write the E binned histograms
			hMCEx[i][j]->Write();
			hMCEy[i][j]->Write();
			hMCEz[i][j]->Write();
		}

		//loop over Xi bins
		for (int j = 0; j < NXiBins; j++)
		{
			//initize the Xi binned histograms
			hMCXix[i][j] = (TH1F*)h->Clone(Form("hMC-PixBin%i-XiBin%i",i,j));
			hMCXiy[i][j] = (TH1F*)h->Clone(Form("hMC-PiyBin%i-XiBin%i",i,j));
			hMCXiz[i][j] = (TH1F*)h->Clone(Form("hMC-PizBin%i-XiBin%i",i,j));

			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{
				//fill the Xi rank 3 histograms
				hMCR3Xix[i][j][k] = (TH1F*)h->Clone(Form("hMC-PixBin%i-XiBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-PixBin%i-XiBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PixBin[i]&&XiBin[j]);
				hMCR3Xiy[i][j][k] = (TH1F*)h->Clone(Form("hMC-PiyBin%i-XiBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-PiyBin%i-XiBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PiyBin[i]&&XiBin[j]);
				hMCR3Xiz[i][j][k] = (TH1F*)h->Clone(Form("hMC-PizBin%i-XiBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-PizBin%i-XiBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PizBin[i]&&XiBin[j]);
				
				//contract from rank 3 to rank 2 using weighting factor
				hMCXix[i][j]->Add(hMCR3Xix[i][j][k],W[k]);
				hMCXiy[i][j]->Add(hMCR3Xiy[i][j][k],W[k]);
				hMCXiz[i][j]->Add(hMCR3Xiz[i][j][k],W[k]);
				
				//to count total events in MC
				EventsMCXi[i][j] = EventsMCXi[i][j] + hMCR3Xix[i][j][k]->GetEntries();	
			}
			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			EventsMCXiw[i][j] = hMCXix[i][j]->GetEntries();
			FacMCXi[i][j] = EventsMCXi[i][j]/EventsMCXiw[i][j] - 1;
			cout<<"i: "<<i<<"  j: "<<j<<"  EventsMCXi: " <<EventsMCXi[i][j]<<"  EventsMCXiw: " <<EventsMCXiw[i][j]<<"  FacMCXi: "<<  FacMCXi[i][j] <<endl;
			hMCXix[i][j]->Add(hMCXix[i][j],FacMCXi[i][j]);
			hMCXiy[i][j]->Add(hMCXiy[i][j],FacMCXi[i][j]);
			hMCXiz[i][j]->Add(hMCXiz[i][j],FacMCXi[i][j]);
			
			//write the Xi binned histograms
			hMCXix[i][j]->Write();
			hMCXiy[i][j]->Write();
			hMCXiz[i][j]->Write();		
		}
	}
	
	cout << "MC FINISHED!" << endl;
	cout <<endl;
	
	/*///
	/*///<<--------------------------Gen------------------------------------------
	cout << "STARTING Gen" << endl;
	
	Double_t EventsGenE[NPiBins][NEBins] = { 0 };
	Double_t EventsGenEw[NPiBins][NEBins] = { 0 };
	Double_t FacGenE[NPiBins][NEBins] = { 0 };
	Double_t EventsGenXi[NPiBins][NXiBins] = { 0 };
	Double_t EventsGenXiw[NPiBins][NXiBins] = { 0 };
	Double_t FacGenXi[NPiBins][NXiBins] = { 0 };
	
	//the Gen histogram
	TH1F *hGenEx[NPiBins][NEBins];
	TH1F *hGenEy[NPiBins][NEBins];
	TH1F *hGenEz[NPiBins][NEBins];
	TH1F *hGenXix[NPiBins][NXiBins];
	TH1F *hGenXiy[NPiBins][NXiBins];
	TH1F *hGenXiz[NPiBins][NXiBins];
	//the rank 3 MC histograms
	TH1F *hGenR3Ex[NPiBins][NEBins][NWBins];
	TH1F *hGenR3Ey[NPiBins][NEBins][NWBins];
	TH1F *hGenR3Ez[NPiBins][NEBins][NWBins];
	TH1F *hGenR3Xix[NPiBins][NXiBins][NWBins];
	TH1F *hGenR3Xiy[NPiBins][NXiBins][NWBins];
	TH1F *hGenR3Xiz[NPiBins][NXiBins][NWBins];
	
	//loop over Pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over E bins
		for (int j = 0; j < NEBins; j++)
		{
			//initize the E bin histos
			hGenEx[i][j] = (TH1F*)h->Clone(Form("hGen-PixBin%i-EBin%i",i,j));
			hGenEy[i][j] = (TH1F*)h->Clone(Form("hGen-PiyBin%i-EBin%i",i,j));
			hGenEz[i][j] = (TH1F*)h->Clone(Form("hGen-PizBin%i-EBin%i",i,j));
				
			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{
				hGenR3Ex[i][j][k] = (TH1F*)h->Clone(Form("hGen-PixBin%i-EBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-PixBin%i-EBin%i-WBin%i",i,j,k),WBin[k]&&PixBin[i]&&EBin[j]);
				hGenR3Ey[i][j][k] = (TH1F*)h->Clone(Form("hGen-PiyBin%i-EBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-PiyBin%i-EBin%i-WBin%i",i,j,k),WBin[k]&&PiyBin[i]&&EBin[j]);			
				hGenR3Ez[i][j][k] = (TH1F*)h->Clone(Form("hGen-PizBin%i-EBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-PizBin%i-EBin%i-WBin%i",i,j,k),WBin[k]&&PizBin[i]&&EBin[j]);

				//add the histograms with weights
				hGenEx[i][j]->Add(hGenR3Ex[i][j][k],W[k]);
				hGenEy[i][j]->Add(hGenR3Ey[i][j][k],W[k]);
				hGenEz[i][j]->Add(hGenR3Ez[i][j][k],W[k]);

				//to count total events in Gen
				EventsGenE[i][j] = EventsGenE[i][j] + hGenR3Ex[i][j][k]->GetEntries();
			}
			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			//also multiply by the factor by which the gamp files were reduced.
			EventsGenEw[i][j] = hGenEx[i][j]->GetEntries();
			FacGenE[i][j] = EventsGenE[i][j]/EventsGenEw[i][j] - 1;
			cout<<"i: "<<i<<"  j: "<<j<<"  EventsGenE: " <<EventsGenE[i][j]<<"  EventsGenEw: " <<EventsGenEw[i][j]<<"  FacGenE: "<<  FacGenE[i][j] <<endl;
			hGenEx[i][j]->Add(hGenEx[i][j],FacGenE[i][j]*gampfactor);
			hGenEy[i][j]->Add(hGenEy[i][j],FacGenE[i][j]*gampfactor);
			hGenEz[i][j]->Add(hGenEz[i][j],FacGenE[i][j]*gampfactor);
			
			hGenEx[i][j]->Write();
			hGenEy[i][j]->Write();
			hGenEz[i][j]->Write();
		}

		//Xi binning
		for (int j = 0; j < NXiBins; j++)
		{
			//initize the Xi bin histos
			hGenXix[i][j] = (TH1F*)h->Clone(Form("hGen-PixBin%i-XiBin%i",i,j));
			hGenXiy[i][j] = (TH1F*)h->Clone(Form("hGen-PiyBin%i-XiBin%i",i,j));
			hGenXiz[i][j] = (TH1F*)h->Clone(Form("hGen-PizBin%i-XiBin%i",i,j));

			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{	
				hGenR3Xix[i][j][k] = (TH1F*)h->Clone(Form("hGen-PixBin%i-XiBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-PixBin%i-XiBin%i-WBin%i",i,j,k),WBin[k]&&PixBin[i]&&XiBin[j]);
				hGenR3Xiy[i][j][k] = (TH1F*)h->Clone(Form("hGen-PiyBin%i-XiBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-PiyBin%i-XiBin%i-WBin%i",i,j,k),WBin[k]&&PiyBin[i]&&XiBin[j]);			
				hGenR3Xiz[i][j][k] = (TH1F*)h->Clone(Form("hGen-PizBin%i-XiBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-PizBin%i-XiBin%i-WBin%i",i,j,k),WBin[k]&&PizBin[i]&&XiBin[j]);
				
				//add the histograms with weights
				hGenXix[i][j]->Add(hGenR3Xix[i][j][k],W[k]);
				hGenXiy[i][j]->Add(hGenR3Xiy[i][j][k],W[k]);
				hGenXiz[i][j]->Add(hGenR3Xiz[i][j][k],W[k]);
				
				//to count total events in Gen
				EventsGenXi[i][j] = EventsGenXi[i][j] + hGenR3Xix[i][j][k]->GetEntries();			
			}

			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			//also multiply by the factor by which the gamp files were reduced.
			EventsGenXiw[i][j] = hGenXix[i][j]->GetEntries();
			FacGenXi[i][j] = EventsGenXi[i][j]/EventsGenXiw[i][j] - 1;
			cout<<"i: "<<i<<"  j: "<<j<<"  EventsGenXi: " <<EventsGenXi[i][j]<<"  EventsGenXiw: " <<EventsGenXiw[i][j]<<"  FacGenXi: "<<  FacGenXi[i][j] <<endl;
			hGenXix[i][j]->Add(hGenXix[i][j],FacGenXi[i][j]*gampfactor);
			hGenXiy[i][j]->Add(hGenXiy[i][j],FacGenXi[i][j]*gampfactor);
			hGenXiz[i][j]->Add(hGenXiz[i][j],FacGenXi[i][j]*gampfactor);
			
			hGenXix[i][j]->Write();
			hGenXiy[i][j]->Write();
			hGenXiz[i][j]->Write();
		}
	}
	cout << "Gen FINISHED!" << endl;

	//*///
	//gROOT->ProcessLine(".q");

}

