/*

Werr[i] is calculated assuming yieldData and yieldMC are unclorrelated ie the covarience is zero.

*/


void GetW(){

	//----------------------global variables and initializers-------------------------
	const Int_t NEBins = 3;
	
	Double_t YieldData[NEBins], YieldMC[NEBins] ;
	Int_t YieldDataErr[NEBins], YieldMCErr[NEBins];
	Double_t W[NEBins],Werr[NEBins];	
	//-------------------------------further setup----------------------------------------
 	TFile *fData = TFile::Open("v37k_full_newbasic.root");
	TFile *fMC = TFile::Open("MC_v07_v37k.root");
 	TTree *tData = (TTree*)fData->Get("v37k_newbasic");
	TTree *tMC = (TTree*)fMC->Get("v37k");
	
 	gROOT->ProcessLine(".L ~/clas/scripts/myfit2GAUS5.C");
 	TCut conf = "kf_prob > 0.50";
 
	//cuts
	if(NEBins == 11){
		TString beam[NEBins];
		beam[0] = "beam > 3.3 && beam < 3.5 ";
		beam[1] = "beam > 3.5 && beam < 3.7 ";
		beam[2] = "beam > 3.7 && beam < 3.9 ";
		beam[3] = "beam > 3.9 && beam < 4.1 ";
		beam[4] = "beam > 4.1 && beam < 4.3 ";
		beam[5] = "beam > 4.3 && beam < 4.5 ";
		beam[6] = "beam > 4.5 && beam < 4.7 ";
		beam[7] = "beam > 4.7 && beam < 4.9 ";
		beam[8] = "beam > 4.9 && beam < 5.1 ";
		beam[9] = "beam > 5.1 && beam < 5.3 ";
		beam[10] = "beam > 5.3 && beam < 5.5";
	}
	if(NEBins == 3){
		TString beam[NEBins];
		beam[0] = "beam > 3.3 && beam < 3.65 ";
		beam[1] = "beam > 3.65 && beam < 4.0 ";
		beam[2] = "beam > 4.0 && beam < 4.35 ";		
	}
	
	
	//canvases
	TCanvas *c0=new TCanvas("c0","",700,400);
	TCanvas *cData=new TCanvas("cData","cData",1000,700);	
	TCanvas *cMC=new TCanvas("cMC","cMC",1000,700);
	cData->Divide(2,2);
	cMC->Divide(2,2);
	c0->cd();
	
	
	//set up the histograms
	TH1F *h=new TH1F("h","",40,1.1,1.5);
	tData->Draw("sqrt(mm2kpkp)>>h",conf);
	h->GetYaxis()->SetTitle("Events/10MeV/c^{2}");  
	h->GetXaxis()->SetTitle("MM(K^{+}K^{+}) (GeV/c^{2})");
	TH1F *hData[NEBins], *hMC[NEBins];


	//-----------------------------------------start the iteration------------------------------------
	int j;
	for (int i = 0; i < NEBins ; i++)
 	{
	
		//Do the fit
		j = i + 1;
		cData->cd(j);
		hData[i] = (TH1F*)h->Clone(Form("hData%i",i));	
		tData->Draw(Form("mmkpkp>>hData%i",i),beam[i]);	
		fitGAUS5(hData[i],1,1.1,1.5,1,1,1,1.321,0.007,3,0,YieldData[i],0,0,YieldDataErr[i]);
		
		
		cMC->cd(j);
		hMC[i] = (TH1F*)h->Clone(Form("hMC%i",i));	
		tMC->Draw(Form("mmkpkp>>hMC%i",i),beam[i]);	
		fitGAUS5(hMC[i],1,1.1,1.5,1,1,1,1.321,0.007,3,0,YieldMC[i],0,0,YieldMCErr[i]);
 	

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
	cout << "======================================W above, Werr below ==================================" << endl;
	for (int i = 0; i < NEBins ; i++) 
	{

		//cout <<W[i] << ", ";
		cout << Werr[i] << ", ";
	}

}