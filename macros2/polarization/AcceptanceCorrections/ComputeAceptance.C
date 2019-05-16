#include "/Users/Bono/clas/myDefinitions/AcPi20E3.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"
#include "/Users/Bono/clas/myDefinitions/WBins27.h"

void ComputeAceptance()
{
	
	TCut cut=hypersphere;  	

	//~~~~~~~~~~~~~~~~~~~~~Define Variables for files~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v05.root");
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/sim/MC_i3_2kppim_Basic.root");  
	TTree *tData = (TTree*)fData->Get("v05_Basic");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");

	//Generated events
	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/sim/MC_i3_gamp_100.root");
	TTree *tGen = (TTree*)fGen->Get("GampTree_100");
	Double_t gampfactor = 100; 
	// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	


	//-----------The weighting factors <----5-----
	if(NWBins == 27){
		
		ifstream in("/Users/Bono/clas/myDefinitions/txt/Winfo.txt"); // input
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





	TH1D *h=new TH1D("h","",2000,-1.0,1.0); // 2/2000 = 0.001
	h->GetYaxis()->SetTitle("Events");  
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}}) (GeV/c^{2})");
	h->SetMinimum(0);
	

	

	TH1D *hMCEx[NPiAcBins][NEBins];
	TH1D *hMCEy[NPiAcBins][NEBins];
	TH1D *hMCEz[NPiAcBins][NEBins];
	TH1D *hMCXix[NPiAcBins][NXiBins];
	TH1D *hMCXiy[NPiAcBins][NXiBins];
	TH1D *hMCXiz[NPiAcBins][NXiBins];
	
	TH1D *hGenEx[NPiAcBins][NEBins];
	TH1D *hGenEy[NPiAcBins][NEBins];
	TH1D *hGenEz[NPiAcBins][NEBins];
	TH1D *hGenXix[NPiAcBins][NXiBins];
	TH1D *hGenXiy[NPiAcBins][NXiBins];
	TH1D *hGenXiz[NPiAcBins][NXiBins];




	//open two txt files for writing	
	ofstream myEMCfile,myXiMCfile,myEGenfile,myXiGenfile;
	myEMCfile.open ("./txt/EbinsMC.txt");
	myXiMCfile.open ("./txt/XibinsMC.txt");
	myEGenfile.open ("./txt/EbinsGen.txt");
	myXiGenfile.open ("./txt/XibinsGen.txt");


	
	//loop over energy bins
	for (int j = 0; j < NEBins; j++)
	{
		//loop over pion bins
		for (int i = 0; i < NPiAcBins; i++)
		{
		
			hMCEx[i][j] = (TH1D*)h->Clone(Form("hMC-PixAcBin%i-EBin%i",i,j));
			tMC->Draw(Form("COS_pi_x>>hMC-PixAcBin%i-EBin%i",i,j),cut&&EBin[j]&&PixAcBin[i]);
			cout << hMCEx[i][j]->GetEntries() << "  1" <<endl;

			hMCEy[i][j] = (TH1D*)h->Clone(Form("hMC-PiyAcBin%i-EBin%i",i,j));
			tMC->Draw(Form("COS_pi_y>>hMC-PiyAcBin%i-EBin%i",i,j),cut&&EBin[j]&&PiyAcBin[i]);
			cout << hMCEy[i][j]->GetEntries() <<"  2" <<endl;
			
			hMCEz[i][j] = (TH1D*)h->Clone(Form("hMC-PizAcBin%i-EBin%i",i,j));
			tMC->Draw(Form("COS_pi_z>>hMC-PizAcBin%i-EBin%i",i,j),cut&&EBin[j]&&PizAcBin[i]);
			cout << hMCEz[i][j]->GetEntries() <<"  3" <<endl;
			
			
			myEMCfile<<hMCEx[i][j]->GetEntries()<<" "<<hMCEy[i][j]->GetEntries()<<" "<< hMCEz[i][j]->GetEntries() <<endl; 	
		
		}
	}
		

	//loop over Xi bins
	for (int j = 0; j < NXiBins; j++)
	{
		//loop over pion bins
		for (int i = 0; i < NPiAcBins; i++)
		{
			hMCXix[i][j] = (TH1D*)h->Clone(Form("hMC-PixAcBin%i-XiBin%i",i,j));
			tMC->Draw(Form("COS_pi_x>>hMC-PixAcBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PixAcBin[i]);		
			cout << hMCXix[i][j]->GetEntries()<<"  4" <<endl;
			
			hMCXiy[i][j] = (TH1D*)h->Clone(Form("hMC-PiyAcBin%i-XiBin%i",i,j));
			tMC->Draw(Form("COS_pi_y>>hMC-PiyAcBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PiyAcBin[i]);		
			cout << hMCXiy[i][j]->GetEntries() <<"  5" <<endl;
			
			hMCXiz[i][j] = (TH1D*)h->Clone(Form("hMC-PizAcBin%i-XiBin%i",i,j));
			tMC->Draw(Form("COS_pi_z>>hMC-PizAcBin%i-XiBin%i",i,j),cut&&XiBin[j]&&PizAcBin[i]);		
			cout << hMCXiz[i][j]->GetEntries() <<"  6" <<endl;
				
			
			myXiMCfile<<hMCXix[i][j]->GetEntries()<<" "<<hMCXiy[i][j]->GetEntries()<<" "<< hMCXiz[i][j]->GetEntries() <<endl; 
		}
	}






//////////////////
	//loop over energy bins
	for (int j = 0; j < NEBins; j++)
	{
		//loop over pion bins
		for (int i = 0; i < NPiAcBins; i++)
		{
		
			hGenEx[i][j] = (TH1D*)h->Clone(Form("hGen-PixAcBin%i-EBin%i",i,j));
			tGen->Draw(Form("COS_pi_x>>hGen-PixAcBin%i-EBin%i",i,j),EBin[j]&&PixAcBin[i]);
			cout << hGenEx[i][j]->GetEntries() <<"  7" <<endl;

			hGenEy[i][j] = (TH1D*)h->Clone(Form("hGen-PiyAcBin%i-EBin%i",i,j));
			tGen->Draw(Form("COS_pi_y>>hGen-PiyAcBin%i-EBin%i",i,j),EBin[j]&&PiyAcBin[i]);
			cout << hGenEy[i][j]->GetEntries() <<"  8" <<endl;
			
			hGenEz[i][j] = (TH1D*)h->Clone(Form("hGen-PizAcBin%i-EBin%i",i,j));
			tGen->Draw(Form("COS_pi_z>>hGen-PizAcBin%i-EBin%i",i,j),EBin[j]&&PizAcBin[i]);
			cout << hGenEz[i][j]->GetEntries() <<"  9" <<endl;
			
			
			myEGenfile<<hGenEx[i][j]->GetEntries()*gampfactor<<" "<<hGenEy[i][j]->GetEntries()*gampfactor<<" "<< hGenEz[i][j]->GetEntries()*gampfactor<<endl; 	
		
		}
	}
		
	
	//loop over Xi bins
	for (int j = 0; j < NXiBins; j++)
	{
		//loop over pion bins
		for (int i = 0; i < NPiAcBins; i++)
		{
			//cout << "test1"<<endl;
			hGenXix[i][j] = (TH1D*)h->Clone(Form("hGen-PixAcBin%i-XiBin%i",i,j));
			//cout << "test2"<<endl;
			tGen->Draw(Form("COS_pi_x>>hGen-PixAcBin%i-XiBin%i",i,j),XiBin[j]&&PixAcBin[i]);		
			//cout << "test3"<<endl;
			cout << hGenXix[i][j]->GetEntries() <<"  10" <<endl;
			//cout << "test4"<<endl;
			
			hGenXiy[i][j] = (TH1D*)h->Clone(Form("hGen-PiyAcBin%i-XiBin%i",i,j));
			tGen->Draw(Form("COS_pi_y>>hGen-PiyAcBin%i-XiBin%i",i,j),XiBin[j]&&PiyAcBin[i]);		
			cout << hGenXiy[i][j]->GetEntries() <<"  11" <<endl;
			
			hGenXiz[i][j] = (TH1D*)h->Clone(Form("hGen-PizAcBin%i-XiBin%i",i,j));
			tGen->Draw(Form("COS_pi_z>>hGen-PizAcBin%i-XiBin%i",i,j),XiBin[j]&&PizAcBin[i]);		
			cout << hGenXiz[i][j]->GetEntries() <<"  12" <<endl;
				
			
			myXiGenfile<<hGenXix[i][j]->GetEntries()*gampfactor<<" "<<hGenXiy[i][j]->GetEntries()*gampfactor<<" "<< hGenXiz[i][j]->GetEntries()*gampfactor<<endl; 
		}
	}

}





