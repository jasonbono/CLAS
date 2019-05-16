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
	6) Choose if the bins are of variable width by "var" or "fixed"
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



#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"
#include "/Users/Bono/clas/myDefinitions/WBins27.h" 
#include "/Users/Bono/clas/myDefinitions/Bins336.h"

void Stage1()
{

	//~~~~~~~~~~~~~~~~~~~~~Define Variables for cut type to be used~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char *s = new char[1]; //this is for interactive session
	const string cuttype ("hypersphere"); //<------1-----
	const string lamOption ("lam"); //dont change this
	const string hyperOption ("hypersphere"); //dont change this
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
		cout << "somthing is wrong with your cut type, terminating program" <<endl;
		gROOT->ProcessLine(".q");
	}
	
	
	
	const string varOption ("var"); //dont change this
	const string fixedOption ("fixed");	
	if (bintype.compare(varOption) == 0)
	{
		cout << "The varible bin width option: type enter to accept" <<endl;	
		gets(s);
		cout << "variable bin width accepted" << endl;
	}
	else if (bintype.compare(fixedOption) == 0)
	{
		cout << "The fixed bin with option: Type enter to accept" <<endl;
		gets(s);
		cout << "fixed bin width accepted" << endl;
	}
	else 
	{
		cout << "somthing is wrong with your choice of bin type, terminating program" <<endl;
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
	Double_t gampfactor = 100; //<----3
	
	//New file to store the histograms
	TFile* fHistos = new TFile("./hists/histsStage1.root","RECREATE");
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 






/*	
	//-----------The weighting factors <----5-----
	if(NWBins == 27){
		
		ifstream in("./txt/Winfo.txt"); // input
	  	if(!in) {
	    	cout << "Cannot open txt file.\n";
			gROOT->ProcessLine(".q");
	  	}
		double W[NWBins] = {0},Werr[NWBins] = {0};

		for (int k = 0; k < NWBins ; k++) 
		{
	  		in >> W[k] >> Werr[k];
	  		cout << "W[k], Werr[k] = " << W[k] << ", " << Werr[k] << "\n";
		}
			in.close();		
	}

*/
	
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
	TH1D *h=new TH1D("h","",2000,-1.0,1.0); // 2/2000 = 0.001
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}}) (GeV/c^{2})");
	h->SetMinimum(0);
	
	//and the model for comparing the beam energy spectrum
	TH1D *hBeam=new TH1D("hBeam","",27,2.8,5.5);
	hBeam->GetYaxis()->SetTitle("Events");  
	hBeam->GetXaxis()->SetTitle("Beam Energy (GeV)");
	hBeam->SetMinimum(0);
	
	
	//*//<----------------------------Data------------------------------------------
	cout << "STARTING Data" << endl;
	//the data histogram
	TH1D *hDataEx[NPiBins][NEBins];
	TH1D *hDataEy[NPiBins][NEBins];
	TH1D *hDataEz[NPiBins][NEBins];
	TH1D *hDataXix[NPiBins][NXiBins];
	TH1D *hDataXiy[NPiBins][NXiBins];
	TH1D *hDataXiz[NPiBins][NXiBins];
	//fill for comparing the beam energy spectrum
	TH1D *hBeamData;
	hBeamData = (TH1D*)hBeam->Clone("hBeamData");
	tData->Draw("beam>>hBeamData",cut);

	//loop over pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over energy bins
		for (int j = 0; j < NEBins; j++)
		{
			//energy binning
			hDataEx[i][j] = (TH1D*)h->Clone(Form("hData-PixBin%i-EBin%i",i,j));
			tData->Draw(Form("COS_pi_x>>hData-PixBin%i-EBin%i",i,j),cut&&EBin[j]&&PixBin[i]);
			hDataEx[i][j]->Write();
			hDataEy[i][j] = (TH1D*)h->Clone(Form("hData-PiyBin%i-EBin%i",i,j));
			tData->Draw(Form("COS_pi_y>>hData-PiyBin%i-EBin%i",i,j),cut&&EBin[j]&&PiyBin[i]);
			hDataEy[i][j]->Write();
			hDataEz[i][j] = (TH1D*)h->Clone(Form("hData-PizBin%i-EBin%i",i,j));
			tData->Draw(Form("COS_pi_z>>hData-PizBin%i-EBin%i",i,j),cut&&EBin[j]&&PizBin[i]);
			hDataEz[i][j]->Write();
		}
		
		//loop over Xi bins
		for (int j = 0; j < NXiBins; j++)
		{
			//Xi binning
			hDataXix[i][j] = (TH1D*)h->Clone(Form("hData-PixBin%i-XiBin%i",i,j));
			tData->Draw(Form("COS_pi_x>>hData-PixBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PixBin[i]);		
			hDataXix[i][j]->Write();	
			hDataXiy[i][j] = (TH1D*)h->Clone(Form("hData-PiyBin%i-XiBin%i",i,j));
			tData->Draw(Form("COS_pi_y>>hData-PiyBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PiyBin[i]);		
			hDataXiy[i][j]->Write();
			hDataXiz[i][j] = (TH1D*)h->Clone(Form("hData-PizBin%i-XiBin%i",i,j));
			tData->Draw(Form("COS_pi_z>>hData-PizBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PizBin[i]);		
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
	TH1D *hMCEx[NPiBins][NEBins];
	TH1D *hMCEy[NPiBins][NEBins];
	TH1D *hMCEz[NPiBins][NEBins];
	TH1D *hMCXix[NPiBins][NXiBins];
	TH1D *hMCXiy[NPiBins][NXiBins];
	TH1D *hMCXiz[NPiBins][NXiBins];
	//the rank 3 MC histograms
	TH1D *hMCR3Ex[NPiBins][NEBins][NWBins];
	TH1D *hMCR3Ey[NPiBins][NEBins][NWBins];
	TH1D *hMCR3Ez[NPiBins][NEBins][NWBins];
	TH1D *hMCR3Xix[NPiBins][NXiBins][NWBins];
	TH1D *hMCR3Xiy[NPiBins][NXiBins][NWBins];
	TH1D *hMCR3Xiz[NPiBins][NXiBins][NWBins];
	
	//........histogram for comparing the beam energy spectrum..................
	TH1D *hBeamMC;
	hBeamMC = (TH1D*)hBeam->Clone("hBeamMC");
	tMC->Draw("beam>>hBeamMC",cut);
	TH1D *hBeamGen;
	hBeamGen = (TH1D*)hBeam->Clone("hBeamGen");
	tGen->Draw("beam>>hBeamGen");

	TH1D *hBeamMC_Wtot;	
	hBeamMC_Wtot = (TH1D*)hBeam->Clone("hBeamMC_Wtot");	
	TH1D *hBeamMC_W[NWBins];
	//loop over W bins
	for (int k = 0; k < NWBins; k++)
	{
		hBeamMC_W[k] = (TH1D*)hBeam->Clone(Form("hBeamMC_W%i",k));
		tMC->Draw(Form("beam>>hBeamMC_W%i",k),cut&&WBin[k]);	
		hBeamMC_Wtot->Add(hBeamMC_W[k],W[k]);
		hBeamMC_Wtot->SetMinimum(0);
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
			hMCEx[i][j] = (TH1D*)h->Clone(Form("hMC-PixBin%i-EBin%i",i,j));
			hMCEy[i][j] = (TH1D*)h->Clone(Form("hMC-PiyBin%i-EBin%i",i,j));
			hMCEz[i][j] = (TH1D*)h->Clone(Form("hMC-PizBin%i-EBin%i",i,j));
		
			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{

				//fill the energy rank 3 histograms
				hMCR3Ex[i][j][k] = (TH1D*)h->Clone(Form("hMC-PixBin%i-EBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("COS_pi_x>>hMC-PixBin%i-EBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PixBin[i]&&EBin[j]);		
				hMCR3Ey[i][j][k] = (TH1D*)h->Clone(Form("hMC-PiyBin%i-EBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("COS_pi_y>>hMC-PiyBin%i-EBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PiyBin[i]&&EBin[j]);
				hMCR3Ez[i][j][k] = (TH1D*)h->Clone(Form("hMC-PizBin%i-EBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("COS_pi_z>>hMC-PizBin%i-EBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PizBin[i]&&EBin[j]);

				//contract from rank 3 to rank 2 using weighting factor
				hMCEx[i][j]->Add(hMCR3Ex[i][j][k],W[k]);
				hMCEy[i][j]->Add(hMCR3Ey[i][j][k],W[k]);
				hMCEz[i][j]->Add(hMCR3Ez[i][j][k],W[k]);

				//# before weighting
				EventsMCE[i][j] = EventsMCE[i][j] + hMCR3Ex[i][j][k]->GetEntries();  
			}
			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			//# after weighting
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
			hMCXix[i][j] = (TH1D*)h->Clone(Form("hMC-PixBin%i-XiBin%i",i,j));
			hMCXiy[i][j] = (TH1D*)h->Clone(Form("hMC-PiyBin%i-XiBin%i",i,j));
			hMCXiz[i][j] = (TH1D*)h->Clone(Form("hMC-PizBin%i-XiBin%i",i,j));

			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{
				//fill the Xi rank 3 histograms
				hMCR3Xix[i][j][k] = (TH1D*)h->Clone(Form("hMC-PixBin%i-XiBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("COS_pi_x>>hMC-PixBin%i-XiBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PixBin[i]&&XiBin[j]);
				hMCR3Xiy[i][j][k] = (TH1D*)h->Clone(Form("hMC-PiyBin%i-XiBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("COS_pi_y>>hMC-PiyBin%i-XiBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PiyBin[i]&&XiBin[j]);
				hMCR3Xiz[i][j][k] = (TH1D*)h->Clone(Form("hMC-PizBin%i-XiBin%i-WBin%i",i,j,k));
				tMC->Draw(Form("COS_pi_z>>hMC-PizBin%i-XiBin%i-WBin%i",i,j,k),cut&&WBin[k]&&PizBin[i]&&XiBin[j]);
				
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
	TH1D *hGenEx[NPiBins][NEBins];
	TH1D *hGenEy[NPiBins][NEBins];
	TH1D *hGenEz[NPiBins][NEBins];
	TH1D *hGenXix[NPiBins][NXiBins];
	TH1D *hGenXiy[NPiBins][NXiBins];
	TH1D *hGenXiz[NPiBins][NXiBins];
	//the rank 3 MC histograms
	TH1D *hGenR3Ex[NPiBins][NEBins][NWBins];
	TH1D *hGenR3Ey[NPiBins][NEBins][NWBins];
	TH1D *hGenR3Ez[NPiBins][NEBins][NWBins];
	TH1D *hGenR3Xix[NPiBins][NXiBins][NWBins];
	TH1D *hGenR3Xiy[NPiBins][NXiBins][NWBins];
	TH1D *hGenR3Xiz[NPiBins][NXiBins][NWBins];
	
	//loop over Pion bins
	for (int i = 0; i < NPiBins; i++)
	{
		//loop over E bins
		for (int j = 0; j < NEBins; j++)
		{
			//initize the E bin histos
			hGenEx[i][j] = (TH1D*)h->Clone(Form("hGen-PixBin%i-EBin%i",i,j));
			hGenEy[i][j] = (TH1D*)h->Clone(Form("hGen-PiyBin%i-EBin%i",i,j));
			hGenEz[i][j] = (TH1D*)h->Clone(Form("hGen-PizBin%i-EBin%i",i,j));
				
			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{
				hGenR3Ex[i][j][k] = (TH1D*)h->Clone(Form("hGen-PixBin%i-EBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("COS_pi_x>>hGen-PixBin%i-EBin%i-WBin%i",i,j,k),WBin[k]&&PixBin[i]&&EBin[j]);
				hGenR3Ey[i][j][k] = (TH1D*)h->Clone(Form("hGen-PiyBin%i-EBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("COS_pi_y>>hGen-PiyBin%i-EBin%i-WBin%i",i,j,k),WBin[k]&&PiyBin[i]&&EBin[j]);			
				hGenR3Ez[i][j][k] = (TH1D*)h->Clone(Form("hGen-PizBin%i-EBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("COS_pi_z>>hGen-PizBin%i-EBin%i-WBin%i",i,j,k),WBin[k]&&PizBin[i]&&EBin[j]);

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
			hGenXix[i][j] = (TH1D*)h->Clone(Form("hGen-PixBin%i-XiBin%i",i,j));
			hGenXiy[i][j] = (TH1D*)h->Clone(Form("hGen-PiyBin%i-XiBin%i",i,j));
			hGenXiz[i][j] = (TH1D*)h->Clone(Form("hGen-PizBin%i-XiBin%i",i,j));

			//loop over W bins
			for (int k = 0; k < NWBins; k++)
			{	
				hGenR3Xix[i][j][k] = (TH1D*)h->Clone(Form("hGen-PixBin%i-XiBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("COS_pi_x>>hGen-PixBin%i-XiBin%i-WBin%i",i,j,k),WBin[k]&&PixBin[i]&&XiBin[j]);
				hGenR3Xiy[i][j][k] = (TH1D*)h->Clone(Form("hGen-PiyBin%i-XiBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("COS_pi_y>>hGen-PiyBin%i-XiBin%i-WBin%i",i,j,k),WBin[k]&&PiyBin[i]&&XiBin[j]);			
				hGenR3Xiz[i][j][k] = (TH1D*)h->Clone(Form("hGen-PizBin%i-XiBin%i-WBin%i",i,j,k));
				tGen->Draw(Form("COS_pi_z>>hGen-PizBin%i-XiBin%i-WBin%i",i,j,k),WBin[k]&&PizBin[i]&&XiBin[j]);
				
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