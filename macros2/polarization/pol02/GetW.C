/*

Werr[i] is calculated assuming yieldData and yieldMC are unclorrelated ie the covarience is zero.

specify the number of energybins

*/


void GetW(){

	//----------------------global variables and initializers-------------------------
	const Int_t NEBins = 11;
	
	Double_t YieldData[NEBins], YieldMC[NEBins] ;
	Int_t YieldDataErr[NEBins], YieldMCErr[NEBins];
	Double_t W[NEBins],Werr[NEBins];	
	//-------------------------------further setup----------------------------------------
 	TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/2kppim-v01.root");
	TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC_i1_2kppim.root");
 	TTree *tData = (TTree*)fData->Get("v01_Basic");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	
 	gROOT->ProcessLine(".L ~/clas/scripts/new/gausfit.C");
 	TCut conf = "kf_prob > 0.50";
 
	//cuts
	if(NEBins == 11){
		TString beam[NEBins];
		beam[0] = "beam > 3.3 && beam < 3.5";
		beam[1] = "beam > 3.5 && beam < 3.7";
		beam[2] = "beam > 3.7 && beam < 3.9";
		beam[3] = "beam > 3.9 && beam < 4.1";
		beam[4] = "beam > 4.1 && beam < 4.3";
		beam[5] = "beam > 4.3 && beam < 4.5";
		beam[6] = "beam > 4.5 && beam < 4.7";
		beam[7] = "beam > 4.7 && beam < 4.9";
		beam[8] = "beam > 4.9 && beam < 5.1";
		beam[9] = "beam > 5.1 && beam < 5.3";
		beam[10] = "beam > 5.3 && beam < 5.5";
	}
	if(NEBins == 3){
		TString beam[NEBins];
		beam[0] = "beam > 3.3 && beam < 3.65";
		beam[1] = "beam > 3.65 && beam < 4.0";
		beam[2] = "beam > 4.0 && beam < 4.35";		
	}

	
	//the lambda cut
	TString lam="abs(sqrt(mm2kpkppim)-1.116)<0.050";
	TString Cut[NEBins];
	for (int i = 0; i < NEBins ; i++)
 	{
		
		Cut[i] = beam[i] + "&&" + lam;
		cout << "Cut[i] = " << Cut[i] <<endl;

	}
	
	
	
	//canvases
	TCanvas *c0=new TCanvas("c0","",700,400);
	TCanvas *cData=new TCanvas("cData","cData",1200,800);	
	TCanvas *cMC=new TCanvas("cMC","cMC",1200,800);
	cData->Divide(4,3);
	cMC->Divide(4,3);
	c0->cd();
	
	
	//set up the histograms
	TH1F *h=new TH1F("h","",40,1.2,1.6);
	tData->Draw("mlampim>>h");
	h->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	h->GetXaxis()->SetTitle(" M(#Lambda + #pi^{-}) (GeV/c^{2})");
	TH1F *hData[NEBins], *hMC[NEBins];

	
	//specify the fitting variables
	Double_t fitLow = 1.25;
	Double_t fitHigh = 1.37;
	Double_t XiMass = 1.321;
	Double_t fitWidth = 0.002;
	Double_t fitWidthFloat = 0.0035;
	
	//-----------------------------------------start the iteration------------------------------------
	int j;
	for (int i = 0; i < NEBins ; i++)
 	{
	
		//Do the fit
		j = i + 1;
		cData->cd(j);
		hData[i] = (TH1F*)h->Clone(Form("hData%i",i));	
		tData->Draw(Form("mlampim>>hData%i",i),Cut[i]);	
		gausfit(hData[i],1,fitLow,fitHigh,1,1,1,XiMass,fitWidth,fitWidthFloat,3,0,YieldData[i],0,0,YieldDataErr[i]);
		
		
		cMC->cd(j);
		hMC[i] = (TH1F*)h->Clone(Form("hMC%i",i));	
		tMC->Draw(Form("mlampim>>hMC%i",i),Cut[i]);	
		gausfit(hMC[i],1,fitLow,fitHigh,1,1,1,XiMass,fitWidth,fitWidthFloat,3,0,YieldMC[i],0,0,YieldMCErr[i]);
 	

		//Compute W and Werr 
		W[i] = YieldData[i]/YieldMC[i];
		Werr[i] = W[i]*sqrt((YieldDataErr[i]/YieldData[i])*(YieldDataErr[i]/YieldData[i]) + (YieldMCErr[i]/YieldMC[i])*(YieldMCErr[i]/YieldMC[i]));
	}


	
	

	//check again
	for (int i = 0; i < NEBins ; i++) 
	{
		cout << "yield for data is:  " <<YieldData[i] << " +- " << YieldDataErr[i] <<endl;
		cout << "yield for MC is:    " <<YieldMC[i] << " +- " << YieldMCErr[i] <<endl;
		cout << "the weighting factor is:    " <<W[i] << " +- " << Werr[i] <<endl;
		cout << endl;
	}
	for (int i = 0; i < NEBins ; i++) 
	{

		cout <<W[i] << ", ";
		//cout << Werr[i] << ", ";
	}
	cout << ""<<endl;
	cout << "======================================W above, Werr below ==================================" << endl;
	cout << "" <<endl;
	for (int i = 0; i < NEBins ; i++) 
	{

		//cout <<W[i] << ", ";
		cout << Werr[i] << ", ";
	}

}