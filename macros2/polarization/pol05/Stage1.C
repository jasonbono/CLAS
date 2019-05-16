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
	TFile* fHistos = new TFile("./hists/histsStage1.root","RECREATE");

	

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

	//*//<----------------------------Data------------------------------------------

	//the data histogram
	TH1F *hDataXix[NXiBins][NPiBins];
	TH1F *hDataXiy[NXiBins][NPiBins];
	TH1F *hDataXiz[NXiBins][NPiBins];
	TH1F *hDataEx[NEBins][NPiBins];
	TH1F *hDataEy[NEBins][NPiBins];
	TH1F *hDataEz[NEBins][NPiBins];
	
	
	//loop over E bins
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
			
			
			//Xi binning
			hDataXix[i][j] = (TH1F*)h->Clone(Form("hData-XiBin%i-PixBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-XiBin%i-PixBin%i",i,j),lam&&XiBin[i]&&PixBin[j]);		
			hDataXix[i][j]->Write();	
			hDataXiy[i][j] = (TH1F*)h->Clone(Form("hData-XiBin%i-PiyBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-XiBin%i-PiyBin%i",i,j),lam&&XiBin[i]&&PiyBin[j]);		
			hDataXiy[i][j]->Write();
			hDataXiz[i][j] = (TH1F*)h->Clone(Form("hData-XiBin%i-PizBin%i",i,j));
			tData->Draw(Form("mlampim>>hData-XiBin%i-PizBin%i",i,j),lam&&XiBin[i]&&PizBin[j]);		
			hDataXiz[i][j]->Write();
			
		}
	}

	//*///
	//*//<<---------------------------MC------------------------------------------
	Double_t EventsMC[NXiBins][NPiBins], EventsMCw[NXiBins][NPiBins];
	Double_t FacMC[NXiBins][NPiBins];
	//the MC histogram
	TH1F *hMCXix[NXiBins][NPiBins];
	TH1F *hMCXiy[NXiBins][NPiBins];
	TH1F *hMCXiz[NXiBins][NPiBins];
	TH1F *hMCEx[NEBins][NPiBins];
	TH1F *hMCEy[NEBins][NPiBins];
	TH1F *hMCEz[NEBins][NPiBins];
	//the rank 3 MC histograms
	TH1F *hMCR3x[NXiBins][NPiBins][NEBins];
	TH1F *hMCR3y[NXiBins][NPiBins][NEBins];
	TH1F *hMCR3z[NXiBins][NPiBins][NEBins];
	
	//loop over E bins
	for (int i = 0; i < NEBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			
			//initize the Xi bin histos
			hMCXix[i][j] = (TH1F*)h->Clone(Form("hMC-XiBin%i-PixBin%i",i,j));
			hMCXiy[i][j] = (TH1F*)h->Clone(Form("hMC-XiBin%i-PiyBin%i",i,j));
			hMCXiz[i][j] = (TH1F*)h->Clone(Form("hMC-XiBin%i-PizBin%i",i,j));
			
			
			///*///<-energy binning
			hMCEx[i][j] = (TH1F*)h->Clone(Form("hMC-EBin%i-PixBin%i",i,j));
			tMC->Draw(Form("mlampim>>hMC-EBin%i-PixBin%i",i,j),lam&&EBin[i]&&PixBin[j]);		
			hMCEx[i][j]->Write();	
			hMCEy[i][j] = (TH1F*)h->Clone(Form("hMC-EBin%i-PiyBin%i",i,j));
			tMC->Draw(Form("mlampim>>hMC-EBin%i-PiyBin%i",i,j),lam&&EBin[i]&&PiyBin[j]);		
			hMCEy[i][j]->Write();
			hMCEz[i][j] = (TH1F*)h->Clone(Form("hMC-EBin%i-PizBin%i",i,j));
			tMC->Draw(Form("mlampim>>hMC-EBin%i-PizBin%i",i,j),lam&&EBin[i]&&PizBin[j]);		
			hMCEz[i][j]->Write();
			//*///
			
			
			FacMC[i][j] = 0.0;
			EventsMCw[i][j] = 0.0;
			EventsMC[i][j] = 0.0;
			//*//Xi binning
			for (int k = 0; k < NEBins; k++)
			{
				
				hMCR3x[i][j][k] = (TH1F*)h->Clone(Form("hMC-EBin%i-PixBin%i-XiBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-EBin%i-PixBin%i-XiBin%i",i,j,k),lam&&EBin[i]&&PixBin[j]&&XiBin[k]);
				
				hMCR3y[i][j][k] = (TH1F*)h->Clone(Form("hMC-EBin%i-PiyBin%i-XiBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-EBin%i-PiyBin%i-XiBin%i",i,j,k),lam&&EBin[i]&&PiyBin[j]&&XiBin[k]);
					
				hMCR3z[i][j][k] = (TH1F*)h->Clone(Form("hMC-EBin%i-PizBin%i-XiBin%i",i,j,k));
				tMC->Draw(Form("mlampim>>hMC-EBin%i-PizBin%i-XiBin%i",i,j,k),lam&&EBin[i]&&PizBin[j]&&XiBin[k]);
				
				
				//add the histograms with weights
				hMCXix[i][j]->Add(hMCR3x[i][j][k],W[k]);
				hMCXiy[i][j]->Add(hMCR3y[i][j][k],W[k]);
				hMCXiz[i][j]->Add(hMCR3z[i][j][k],W[k]);
				
				//to count total events in MC
				EventsMC[i][j] = EventsMC[i][j] + hMCR3x[i][j][k]->GetEntries();	
			}

			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			EventsMCw[i][j] = hMCXix[i][j]->GetEntries();
			FacMC[i][j] = EventsMC[i][j]/EventsMCw[i][j] - 1;
			cout<<"i: "<<i<<"  j: "<<j<<"  EventsMC: " <<EventsMC[i][j]<<"  EventsMCw: " <<EventsMCw[i][j]<<"  FacMC: "<<  FacMC[i][j] <<endl;
			hMCXix[i][j]->Add(hMCXix[i][j],FacMC[i][j]);
			hMCXiy[i][j]->Add(hMCXiy[i][j],FacMC[i][j]);
			hMCXiz[i][j]->Add(hMCXiz[i][j],FacMC[i][j]);
			
			hMCXix[i][j]->Write();
			hMCXiy[i][j]->Write();
			hMCXiz[i][j]->Write();
		
		}
	}

	
	//*///
	//*//<<--------------------------Gen------------------------------------------
	Double_t EventsGen[NXiBins][NPiBins], EventsGenw[NXiBins][NPiBins];
	Double_t FacGen[NXiBins][NPiBins];
	
	//the Gen histogram
	TH1F *hGenXix[NXiBins][NPiBins];
	TH1F *hGenXiy[NXiBins][NPiBins];
	TH1F *hGenXiz[NXiBins][NPiBins];
	TH1F *hGenEx[NEBins][NPiBins];
	TH1F *hGenEy[NEBins][NPiBins];
	TH1F *hGenEz[NEBins][NPiBins];
	//the rank 3 MC histograms
	TH1F *hGenR3x[NXiBins][NPiBins][NEBins];
	TH1F *hGenR3y[NXiBins][NPiBins][NEBins];
	TH1F *hGenR3z[NXiBins][NPiBins][NEBins];
	
	
	//loop over Energy bins
	for (int i = 0; i < NEBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			
			//initize the Xi bin histos
			hGenXix[i][j] = (TH1F*)h->Clone(Form("hGen-XiBin%i-PixBin%i",i,j));
			hGenXiy[i][j] = (TH1F*)h->Clone(Form("hGen-XiBin%i-PiyBin%i",i,j));
			hGenXiz[i][j] = (TH1F*)h->Clone(Form("hGen-XiBin%i-PizBin%i",i,j));
			
			//*//<--energy binning
			hGenEx[i][j] = (TH1F*)h->Clone(Form("hGen-EBin%i-PixBin%i",i,j));
			tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PixBin%i",i,j),EBin[i]&&PixBin[j]);		
			hGenEx[i][j]->Write();	
			hGenEy[i][j] = (TH1F*)h->Clone(Form("hGen-EBin%i-PiyBin%i",i,j));
			tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PiyBin%i",i,j),EBin[i]&&PiyBin[j]);		
			hGenEy[i][j]->Write();
			hGenEz[i][j] = (TH1F*)h->Clone(Form("hGen-EBin%i-PizBin%i",i,j));
			tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PizBin%i",i,j),EBin[i]&&PizBin[j]);		
			hGenEz[i][j]->Write();
			//*///
			
			FacGen[i][j] = 0.0;
			EventsGenw[i][j] = 0.0;
			EventsGen[i][j] = 0.0;
			//Xi binning
			for (int k = 0; k < NXiBins; k++)
			{
				
				hGenR3x[i][j][k] = (TH1F*)h->Clone(Form("hGen-EBin%i-PixBin%i-XiBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PixBin%i-XiBin%i",i,j,k),EBin[i]&&PixBin[j]&&XiBin[k]);
				
				hGenR3y[i][j][k] = (TH1F*)h->Clone(Form("hGen-EBin%i-PiyBin%i-XiBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PiyBin%i-XiBin%i",i,j,k),EBin[i]&&PiyBin[j]&&XiBin[k]);
					
				hGenR3z[i][j][k] = (TH1F*)h->Clone(Form("hGen-EBin%i-PizBin%i-XiBin%i",i,j,k));
				tGen->Draw(Form("mmkpkp>>hGen-EBin%i-PizBin%i-XiBin%i",i,j,k),EBin[i]&&PizBin[j]&&XiBin[k]);
				
				
				//add the histograms with weights
				hGenXix[i][j]->Add(hGenR3x[i][j][k],W[k]);
				hGenXiy[i][j]->Add(hGenR3y[i][j][k],W[k]);
				hGenXiz[i][j]->Add(hGenR3z[i][j][k],W[k]);
				
				//to count total events in Gen
				EventsGen[i][j] = EventsGen[i][j] + hGenR3x[i][j][k]->GetEntries();
			
			}

			//normalize so that the weights in the sumation have no effect on the amount of events in the added hists
			EventsGenw[i][j] = hGenXix[i][j]->GetEntries();
			FacGen[i][j] = EventsGen[i][j]/EventsGenw[i][j] - 1;
			cout<<"i: "<<i<<"  j: "<<j<<"  EventsGen: " <<EventsGen[i][j]<<"  EventsGenw: " <<EventsGenw[i][j]<<"  FacGen: "<<  FacGen[i][j] <<endl;
			hGenXix[i][j]->Add(hGenXix[i][j],FacGen[i][j]);
			hGenXiy[i][j]->Add(hGenXiy[i][j],FacGen[i][j]);
			hGenXiz[i][j]->Add(hGenXiz[i][j],FacGen[i][j]);
			
			hGenXix[i][j]->Write();
			hGenXiy[i][j]->Write();
			hGenXiz[i][j]->Write();
		
			
			
		}
	}


	//*///
	gROOT->ProcessLine(".q");

}

