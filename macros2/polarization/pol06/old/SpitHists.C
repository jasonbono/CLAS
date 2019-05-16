/*

Name: SpitHists.C
Author: Jason Bono
Date: October 22 2012
Purpose: To calculate polarization by plotting the acceptance corrected yeilds as a function of PION-ANGLE in bins of BEAM-ENERGY and XiCM-ANGLE. 

Usage: 

	1) make sure the W vector is set to correct initalization. 
	2) specify in the output root file if this was binned in beam or Xi angle
	3) uncomment and comment the appropriate blocks according to the binning in data, mc & gamp

Notes: The input from GetW.C is needed as an input for the W vector which normaized the beam energy spectrum for Xi->lambda + pim events

*/


void SpitHists()
{
	
	//----------------binning----------------
	const int NEBins = 3; // this is how many energy bins the Ws were calculated for in GetW.C
	const int NXiBins = 3; 
	const int NPiBins = 4;
	
	//-----------The weighting factors---------
	if(NEBins == 11){
		const Double_t W[NEBins] = {1.0504, 0.987805, 0.896063, 0.844184, 1.62447, 4.97581, 5.41732, 5.63043, 24.2391, 11.9118, 6.14159};
		const Double_t Werr[NEBins] = {0.842261, 0.127849, 0.679423, 1.83705, 1.24198, 18.8862, 12.7916, 9.38288, 67.3071, 50.4213, 12.9717};
	}
	if(NEBins == 3){
		const Double_t W[NEBins] =	{0.225431, 0.329841, 0.962296};
		const Double_t Werr[NEBins] =	{0.0083008, 0.0127671, 0.0616886};	
	}
	
	
	//open the files and create the proper tree pointers
 	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v01.root");     // DATA histograms
 	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC_i1_2kppim.root");         // MC histograms
 	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/MC_i1_gamp.root");       // GEN histograms 

 	// make aliases for the trees from each file
 	TTree *tData = (TTree*)fData->Get("v01_Basic");
 	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");
 	TTree *tGen = (TTree*)fGen->Get("GampTree");

	//create a new file to store the histogram of the acceptance corrected distributions
	TFile* fHistos = new TFile("histosEbins.root","NEW");
	//TFile* fHistos = new TFile("histosXibins.root","NEW");

	//-------define cuts that define the bins---------
	//energy bins
	TCut beamBin[NEBins];
	beamBin[0] = "beam > 3.3 && beam < 4.0 ";
	beamBin[1] = "beam > 4.0 && beam < 4.7 ";
	beamBin[2] = "beam > 4.7 && beam < 5.4 ";
	
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = "Xcmtheta > -1.0 && Xcmtheta < -0.333";
	XiBin[1] = "Xcmtheta > -0.333 && Xcmtheta < 0.333";
	XiBin[2] = "Xcmtheta > 0.333 && Xcmtheta < 1.0";
		
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
	
	//the missing mass cut on lambda
	TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
	
	//TCut casm="abs(mlampim-1.321)<0.013";
 	//TCut lam="abs(sqrt(mm2kpkppim)-1.116)<0.033";
 	//TCut lamm="abs(mcasmMpim - 1.116)<0.01";
 	//TCut cas="abs(sqrt(mm2kpkp) - 1.321)<0.048";
 	//TCut lamm2="abs(mcasmMpim-1.116)<0.02";

	//create model for the histograms
	TH1F *h=new TH1F("h","",40,1.2,1.6);
	//tData->Draw("mlampim>>h",lam);
	h->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	h->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	TH1F *hData[NEBins], *hMC[NEBins];

	//load the fitter
	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
	
	//specify the global fitting parameters
	Double_t fitLow = 1.2;
	Double_t fitHigh = 1.45;
	Double_t XiMass = 1.321;
	XiMass = 1.32;
	Double_t fitWidth = 0.006;
	Double_t fitWidthFloat = 0.01;
	Double_t t0 = 1;
	Double_t t1 = 1;
	Double_t t2 = 1;
	Double_t t3 = 0;
	Double_t t4 = 0;
///* 
	//---------------------------------------------------data-----------------------------------
	//to obtain the yeilds for the data in energy bins instead of Xi bins just change the cuts to beamBin for x,y,z
	//uncomment and comment the appropriate blocks
	
	
	//yields for Data fitting to fill
	Double_t YieldDataX[NXiBins][NPiBins], YieldDataY[NXiBins][NPiBins], YieldDataZ[NXiBins][NPiBins];
	Int_t  YieldDataXErr[NXiBins][NPiBins], YieldDataYErr[NXiBins][NPiBins], YieldDataZErr[NXiBins][NPiBins]; 
	
	//the data canvas	
	TCanvas *cData[NXiBins][NPiBins];
	
	//the data histogram
	TH1F *hDataX[NXiBins][NPiBins];
	TH1F *hDataY[NXiBins][NPiBins];
	TH1F *hDataZ[NXiBins][NPiBins];

	//loop over Xi bins
	for (int i = 0; i < NXiBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			cData[i][j] = new TCanvas(Form("cData%i%i",i,j),"cData",1200,800);
			cData[i][j]->Divide(3,0);
			
			cData[i][j] = new TCanvas(Form("cData%i%i",i,j),"cData",1200,800);
			cData[i][j]->Divide(3,0);


/*  //XiBin block
			//x direction	
			cData[i][j]->cd(1);	
			hDataX[i][j] = (TH1F*)h->Clone(Form("hData-XiBin%i-PixBin%i",i,j));	
			tData->Draw(Form("mlampim>>hData-XiBin%i-PixBin%i",i,j),lam&&XiBin[i]&&PixBin[j]);
			gausfit(hDataX[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataX[i][j],0,0,YieldDataXErr[i][j]);
		
			//y direction	
			cData[i][j]->cd(2);	
			hDataY[i][j] = (TH1F*)h->Clone(Form("hData-YiBin%i-PiyBin%i",i,j));	
			tData->Draw(Form("mlampim>>hData-YiBin%i-PiyBin%i",i,j),lam&&XiBin[i]&&PiyBin[j]);
			gausfit(hDataY[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataY[i][j],0,0,YieldDataYErr[i][j]);
			
			//z direction	
			cData[i][j]->cd(3);	
			hDataZ[i][j] = (TH1F*)h->Clone(Form("hData-ZiBin%i-PizBin%i",i,j));	
			tData->Draw(Form("mlampim>>hData-ZiBin%i-PizBin%i",i,j),lam&&XiBin[i]&&PizBin[j]);
			gausfit(hDataZ[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataZ[i][j],0,0,YieldDataZErr[i][j]);
*/			

  //beamBin block
			//x direction	
			cData[i][j]->cd(1);	
			hDataX[i][j] = (TH1F*)h->Clone(Form("hData-XiBin%i-PixBin%i",i,j));	
			tData->Draw(Form("mlampim>>hData-XiBin%i-PixBin%i",i,j),lam&&beamBin[i]&&PixBin[j]);
			gausfit(hDataX[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataX[i][j],0,0,YieldDataXErr[i][j]);
		
			//y direction	
			cData[i][j]->cd(2);	
			hDataY[i][j] = (TH1F*)h->Clone(Form("hData-YiBin%i-PiyBin%i",i,j));	
			tData->Draw(Form("mlampim>>hData-YiBin%i-PiyBin%i",i,j),lam&&beamBin[i]&&PiyBin[j]);
			gausfit(hDataY[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataY[i][j],0,0,YieldDataYErr[i][j]);
			
			//z direction	
			cData[i][j]->cd(3);	
			hDataZ[i][j] = (TH1F*)h->Clone(Form("hData-ZiBin%i-PizBin%i",i,j));	
			tData->Draw(Form("mlampim>>hData-ZiBin%i-PizBin%i",i,j),lam&&beamBin[i]&&PizBin[j]);
			gausfit(hDataZ[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldDataZ[i][j],0,0,YieldDataZErr[i][j]);
//*/

		}
	}


//*/

//*
	//--------------------------------------------------MC-----------------------------------
	//to change to bining in energy,  comment out everything below the third for loop and uncomment the energybin block
	
	// for normalizing after w
	Double_t EventsMC = 0;
	Double_t EventsMCw = 0;
	Double_t FacMC = 0;

	
	//yields for MC fitting to fill 
	Double_t YieldMCX[NXiBins][NPiBins], YieldMCY[NXiBins][NPiBins], YieldMCZ[NXiBins][NPiBins];
	Int_t  YieldMCXErr[NXiBins][NPiBins], YieldMCYErr[NXiBins][NPiBins], YieldMCZErr[NXiBins][NPiBins]; 
	
	//the MC canvas	and 
	TCanvas *cMC[NXiBins][NPiBins];
	
	//the MC histogram
	TH1F *hMCX[NXiBins][NPiBins];
	TH1F *hMCY[NXiBins][NPiBins];
	TH1F *hMCZ[NXiBins][NPiBins];
	
	//the rank 3 canvas
	TCanvas *cMCR3[NXiBins][NPiBins][NEBins];

	//the rank 3 MC histograms
	TH1F *hMCXR3[NXiBins][NPiBins][NEBins];
	TH1F *hMCYR3[NXiBins][NPiBins][NEBins];
	TH1F *hMCZR3[NXiBins][NPiBins][NEBins];	
	
	//loop over Xi bins
	for (int i = 0; i < NXiBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			//initiize the histograms
			hMCX[i][j] = (TH1F*)h->Clone(Form("hMCX-XiBin%i-PixBin%i",i,j));	
			hMCY[i][j] = (TH1F*)h->Clone(Form("hMCY-XiBin%i-PiyBin%i",i,j));	
			hMCZ[i][j] = (TH1F*)h->Clone(Form("hMCZ-XiBin%i-PizBin%i",i,j));	
			
				
		
			///* //ENERGYBIN BLOCK
			
			cMC[i][j] = new TCanvas(Form("cMC%i%i",i,j),"cMC",1200,800);
			cMC[i][j]->Divide(3,0);
			//x direction	
			cMC[i][j]->cd(1);	
			tMC->Draw(Form("mlampim>>hMCX-XiBin%i-PixBin%i",i,j),lam&&beamBin[i]&&PixBin[j]);
			gausfit(hMCX[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCX[i][j],0,0,YieldMCXErr[i][j]);

			//y direction	
			cMC[i][j]->cd(2);	
			tMC->Draw(Form("mlampim>>hMCY-XiBin%i-PiyBin%i",i,j),lam&&beamBin[i]&&PiyBin[j]);
			gausfit(hMCY[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCY[i][j],0,0,YieldMCYErr[i][j]);

			//z direction	
			cMC[i][j]->cd(3);	
			tMC->Draw(Form("mlampim>>hMCZ-XiBin%i-PizBin%i",i,j),lam&&beamBin[i]&&PizBin[j]);
			gausfit(hMCZ[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCZ[i][j],0,0,YieldMCZErr[i][j]);		
		
	
		
		/*  //XiBIN BLOCK
			//loop over energy bins
			for (int k = 0; k < NEBins; k++)
			{
				cMCR3[i][j][k] = new TCanvas(Form("cMC%i%i%i",i,j,k),"cMC",1200,800);
				cMCR3[i][j][k]->Divide(3,0);
				
				//x direction (rank 3)	
				cMCR3[i][j][k]->cd(1);
				hMCXR3[i][j][k] = (TH1F*)h->Clone(Form("hMCX-XiBin%i-PixBin%i-beamBin%i",i,j,k));	
				tMC->Draw(Form("mlampim>>hMCX-XiBin%i-PixBin%i-beamBin%i",i,j,k),lam&&XiBin[i]&&PixBin[j]&&beamBin[k]);
				
				//y direction (rank 3)	
				cMCR3[i][j][k]->cd(2);
				hMCYR3[i][j][k] = (TH1F*)h->Clone(Form("hMCY-XiBin%i-PiyBin%i-beamBin%i",i,j,k));	
				tMC->Draw(Form("mlampim>>hMCY-XiBin%i-PiyBin%i-beamBin%i",i,j,k),lam&&XiBin[i]&&PiyBin[j]&&beamBin[k]);
				
				//z direction (rank 3)	
				cMCR3[i][j][k]->cd(3);
				hMCZR3[i][j][k] = (TH1F*)h->Clone(Form("hMCZ-XiBin%i-PizBin%i-beamBin%i",i,j,k));	
				tMC->Draw(Form("mlampim>>hMCZ-XiBin%i-PizBin%i-beamBin%i",i,j,k),lam&&XiBin[i]&&PizBin[j]&&beamBin[k]);
		
				//contract the rank 3 tensor with the W vector to form a rank 2 tensor
				hMCX[i][j]->Add(hMCXR3[i][j][k],W[k]);
				hMCY[i][j]->Add(hMCYR3[i][j][k],W[k]);
				hMCZ[i][j]->Add(hMCZR3[i][j][k],W[k]);
				
				//to count total events in MC
				EventsMC = EventsMC + hMCXR3[i][j][k]->GetEntries();
			}
			
			//normalize so that the weights in the sumation has no effect on the amount of events in the added hists
			EventsMCw = hMCX[i][j]->GetEntries();
			FacMC[i][j] = EventsMC[i][j]/EventsMCw[i][j] - 1;
			hMCX[i][j]->Add(hMCX[i][j],FacMC);
			hMCY[i][j]->Add(hMCY[i][j],FacMC);
			hMCZ[i][j]->Add(hMCZ[i][j],FacMC);
			
			
			// fit the contracted tensors
			cMC[i][j] = new TCanvas(Form("cMC%i%i",i,j),"cMC",1200,800);
			cMC[i][j]->Divide(3,0);
			cMC[i][j]->cd(1);
			gausfit(hMCX[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCX[i][j],0,0,YieldMCXErr[i][j]);
			cMC[i][j]->cd(2);
			gausfit(hMCY[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCY[i][j],0,0,YieldMCYErr[i][j]);
			cMC[i][j]->cd(3);
			gausfit(hMCZ[i][j],1,fitLow,fitHigh,t0,t1,t2,t3,t4,XiMass,fitWidth,fitWidthFloat,3,0,YieldMCZ[i][j],0,0,YieldMCZErr[i][j]);

//*/			
			
		
		}
	}
//*/
//*
	//--------------------------------------------------GEN-----------------------------------
	//to change to bining in energy,  comment out everything below the third for loop and uncomment the energybin block
	
	//yields for Gen fitting to fill 
	Double_t YieldGenX[NXiBins][NPiBins], YieldGenY[NXiBins][NPiBins], YieldGenZ[NXiBins][NPiBins];
	Int_t  YieldGenXErr[NXiBins][NPiBins], YieldGenYErr[NXiBins][NPiBins], YieldGenZErr[NXiBins][NPiBins]; 
	
	//the Gen canvas	and 
	TCanvas *cGen[NXiBins][NPiBins];
	
	
	//the Gen histogram
	TH1F *hGenX[NXiBins][NPiBins];
	TH1F *hGenY[NXiBins][NPiBins];
	TH1F *hGenZ[NXiBins][NPiBins];
	
	//the rank 3 canvas
	TCanvas *cGenR3[NXiBins][NPiBins][NEBins];

	//the rank 3 Gen histograms
	TH1F *hGenXR3[NXiBins][NPiBins][NEBins];
	TH1F *hGenYR3[NXiBins][NPiBins][NEBins];
	TH1F *hGenZR3[NXiBins][NPiBins][NEBins];	
	
	//loop over Xi bins
	for (int i = 0; i < NXiBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			//initiize the histograms
			hGenX[i][j] = (TH1F*)h->Clone(Form("hGenX-XiBin%i-PixBin%i",i,j));	
			hGenY[i][j] = (TH1F*)h->Clone(Form("hGenY-XiBin%i-PiyBin%i",i,j));	
			hGenZ[i][j] = (TH1F*)h->Clone(Form("hGenZ-XiBin%i-PizBin%i",i,j));	
		
			//* //energybin block
			cGen[i][j] = new TCanvas(Form("cGen%i%i",i,j),"cGen",1200,800);
			cGen[i][j]->Divide(3,0);
			
			//x direction	
			cGen[i][j]->cd(1);	
			tGen->Draw(Form("mmkpkp>>hGenX-XiBin%i-PixBin%i",i,j),beamBin[i]&&PixBin[j]);

			//y direction	
			cGen[i][j]->cd(2);	
			tGen->Draw(Form("mmkpkp>>hGenY-XiBin%i-PiyBin%i",i,j),beamBin[i]&&PiyBin[j]);
			

			//z direction	
			cGen[i][j]->cd(3);	
			tGen->Draw(Form("mmkpkp>>hGenZ-XiBin%i-PizBin%i",i,j),beamBin[i]&&PizBin[j]);
				
		
		
		/* //Xibin block
		
			//loop over energy bins
			for (int k = 0; k < NEBins; k++)
			{
				cGenR3[i][j][k] = new TCanvas(Form("cGen%i%i%i",i,j,k),"cGen",1200,800);
				cGenR3[i][j][k]->Divide(3,0);
				
				//x direction (rank 3)	
				cGenR3[i][j][k]->cd(1);
				hGenXR3[i][j][k] = (TH1F*)h->Clone(Form("hGenXR3-XiBin%i-PixBin%i-beamBin%i",i,j,k));	
				tGen->Draw(Form("mmkpkp>>hGenXR3-XiBin%i-PixBin%i-beamBin%i",i,j,k),XiBin[i]&&PixBin[j]&&beamBin[k]);
				
				//x direction (rank 3)	
				cGenR3[i][j][k]->cd(2);
				hGenYR3[i][j][k] = (TH1F*)h->Clone(Form("hGenYR3-XiBin%i-PiyBin%i-beamBin%i",i,j,k));	
				tGen->Draw(Form("mmkpkp>>hGenYR3-XiBin%i-PiyBin%i-beamBin%i",i,j,k),XiBin[i]&&PiyBin[j]&&beamBin[k]);
				
				//z direction (rank 3)	
				cGenR3[i][j][k]->cd(3);
				hGenZR3[i][j][k] = (TH1F*)h->Clone(Form("hGenZR3-XiBin%i-PizBin%i-beamBin%i",i,j,k));	
				tGen->Draw(Form("mmkpkp>>hGenZR3-XiBin%i-PizBin%i-beamBin%i",i,j,k),XiBin[i]&&PizBin[j]&&beamBin[k]);
		
				//contract the rank 3 tensor with the W vector to form a rank 2 tensor
				hGenX[i][j]->Add(hGenXR3[i][j][k],W[k]);
				hGenY[i][j]->Add(hGenYR3[i][j][k],W[k]);
				hGenZ[i][j]->Add(hGenZR3[i][j][k],W[k]);
		
			}
		//*/
			//count the entries in the generated distributsions
			YieldGenX[i][j] = hGenX[i][j]->GetEntries();
			YieldGenY[i][j] = hGenY[i][j]->GetEntries();
			YieldGenZ[i][j] = hGenZ[i][j]->GetEntries();

		
		
			cout << "YieldDataX[i][j] = " << YieldDataX[i][j] << "  YieldDataX[i][j] = " << YieldDataY[i][j] << "  YieldDataZ[i][j] = "<< YieldDataZ[i][j] <<endl;
			cout << "YieldMCX[i][j] = " << YieldMCX[i][j] << "  YieldMCX[i][j] = " << YieldMCY[i][j] << "  YieldMCZ[i][j] = "<< YieldMCZ[i][j] <<endl;
			cout << "YieldGenX[i][j] = " << YieldGenX[i][j] << "  YieldGenX[i][j] = " << YieldGenY[i][j] << "  YieldGenZ[i][j] = "<< YieldGenZ[i][j] <<endl;	
		}
	}

///*/



//----------------------------write the yeilds to a histograms-------------------------------


	TH1F *hDataPiX[NXiBins];
	TH1F *hDataPiY[NXiBins];
	TH1F *hDataPiZ[NXiBins];
	
	TH1F *hMCPiX[NXiBins];
	TH1F *hMCPiY[NXiBins];
	TH1F *hMCPiZ[NXiBins];
	
	TH1F *hGenPiX[NXiBins];
	TH1F *hGenPiY[NXiBins];
	TH1F *hGenPiZ[NXiBins];
	
	//loop over the Xi (or energy) Bins
	for (int i = 0; i < NXiBins; i++)
	{	
		//Setup the Hists
		hDataPiX[i] = new TH1F(Form("hDataPiX-EBin%i",i),"",NPiBins,-1.0,1.0);
		hDataPiX[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
		hDataPiX[i]->GetYaxis()->SetTitle("Counts");

		hDataPiY[i] = (TH1F*)hDataPiX[i]->Clone(Form("hDataPiY-EBin%i",i));
		hDataPiZ[i] = (TH1F*)hDataPiX[i]->Clone(Form("hDataPiZ-EBin%i",i));

		hMCPiX[i] = (TH1F*)hDataPiX[i]->Clone(Form("hMCPiX-EBin%i",i));
		hMCPiY[i] = (TH1F*)hDataPiX[i]->Clone(Form("hMCPiY-EBin%i",i));
		hMCPiZ[i] = (TH1F*)hDataPiX[i]->Clone(Form("hMCPiZ-EBin%i",i));

		hGenPiX[i] = (TH1F*)hDataPiX[i]->Clone(Form("hGenPiX-EBin%i",i));
		hGenPiY[i] = (TH1F*)hDataPiX[i]->Clone(Form("hGenPiY-EBin%i",i));
		hGenPiZ[i] = (TH1F*)hDataPiX[i]->Clone(Form("hGenPiZ-EBin%i",i));
	
		//loop over the pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			//Fill the Hists
			hDataPiX[i]->SetBinContent(j+1,YieldDataX[i][j]);
			hDataPiY[i]->SetBinContent(j+1,YieldDataY[i][j]);
			hDataPiZ[i]->SetBinContent(j+1,YieldDataZ[i][j]);

			hMCPiX[i]->SetBinContent(j+1,YieldMCX[i][j]);
			hMCPiY[i]->SetBinContent(j+1,YieldMCY[i][j]);
			hMCPiZ[i]->SetBinContent(j+1,YieldMCZ[i][j]);
			
			hGenPiX[i]->SetBinContent(j+1,YieldGenX[i][j]);
			hGenPiY[i]->SetBinContent(j+1,YieldGenY[i][j]);
			hGenPiZ[i]->SetBinContent(j+1,YieldGenZ[i][j]);
		}
	
		//Save the Hists
		hDataPiX[i]->Write();
		hDataPiY[i]->Write();
		hDataPiZ[i]->Write();
			
		hMCPiX[i]->Write();
		hMCPiY[i]->Write();
		hMCPiZ[i]->Write();
					
		hGenPiX[i]->Write();
		hGenPiY[i]->Write();
		hGenPiZ[i]->Write();	
	
	
	}


/*
//---------------------------------------Get & Apply Acceptance Corrections------------------------------------------
	Double_t ACX[NXiBins][NPiBins],ACY[NXiBins][NPiBins],ACZ[NXiBins][NPiBins];
	Double_t YieldDataACX[NXiBins][NPiBins], YieldDataACY[NXiBins][NPiBins], YieldDataACZ[NXiBins][NPiBins];
	//loop over Xi bins
	for (int i = 0; i < NXiBins; i++)
	{
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
			//get acceptance corrections
			ACX[i][j] = YieldMCX[i][j]/YieldGenX[i][j];
			ACY[i][j] = YieldMCY[i][j]/YieldGenY[i][j];
			ACZ[i][j] = YieldMCZ[i][j]/YieldGenZ[i][j];
			//correct the data
			YieldDataACX[i][j] = YieldDataX[i][j]/ACX[i][j];
			YieldDataACY[i][j] = YieldDataY[i][j]/ACY[i][j];
			YieldDataACZ[i][j] = YieldDataZ[i][j]/ACZ[i][j];

		}
	}

/* //-------------------------------Write acceptance corrected yeilds to histogram-----------------------

	//the data canvas	
	TCanvas *cDataAC[NXiBins];
	//the acceptance corrected data histogram
	TH1F *hDataACX[NXiBins];
	TH1F *hDataACY[NXiBins];
	TH1F *hDataACZ[NXiBins];
/*  
	Double_t YieldFakeACX[NXiBins][NPiBins],YieldFakeACY[NXiBins][NPiBins],YieldFakeACZ[NXiBins][NPiBins];
	for (int i = 0; i < NXiBins; i++)
	{
		for (int j = 0; j < NPiBins; j++)
		{
			YieldFakeACX[i][j] = 1 + j*j + 10*i;
			YieldFakeACY[i][j] = 8 - j*j + 10*i;
			YieldFakeACZ[i][j] = 50 + 3*j - i*i;
		}
	}
*/
	//loop over Xi bins
/*
	for (int i = 0; i < NXiBins; i++)
	{
		//setup the canvas
		cDataAC[i] = new TCanvas(Form("cDataAC-XiBin%i",i),"cDataAC",1200,800);
		cDataAC[i]->Divide(3,0);
	
		hDataACX[i] = new TH1F(Form("hDataACX-XiBin%i",i),"",4,-1.0,1.0);
		hDataACX[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{x})");
		hDataACX[i]->GetYaxis()->SetTitle("Counts");
		
		hDataACY[i] = new TH1F(Form("hDataACY-XiBin%i",i),"",4,-1.0,1.0);
		hDataACY[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{y})");
		hDataACY[i]->GetYaxis()->SetTitle("Counts");

		hDataACZ[i] = new TH1F(Form("hDataACZ-XiBin%i",i),"",4,-1.0,1.0);
		hDataACZ[i]->GetXaxis()->SetTitle("cos(#theta^{#pi^{-}}_{z})");
		hDataACZ[i]->GetYaxis()->SetTitle("Counts");
	
	
		//loop over pion bins
		for (int j = 0; j < NPiBins; j++)
		{
				
			hDataACX[i]->SetBinContent(j+1,YieldDataACX[i][j]);
			hDataACY[i]->SetBinContent(j+1,YieldDataACY[i][j]);
			hDataACZ[i]->SetBinContent(j+1,YieldDataACZ[i][j]);
		
		
		}
		
		cDataAC[i]->cd(1);
		hDataACX[i]->Draw("E");
		hDataACX[i]->Write();
			
		cDataAC[i]->cd(2);
		hDataACY[i]->Draw("E");
		hDataACY[i]->Write();
			
		cDataAC[i]->cd(3);
		hDataACZ[i]->Draw("E");
		hDataACZ[i]->Write();
			
	}

	

//*/

		
}






	
	
