

Int_t GetYield(TH1F *his)
{	
	TF1 *fSignal = new TF1("fSignal","gaus",1.29,1.35);
	TF1 *fBackground = new TF1("fBackground","pol4",1.29,1.35);
	TF1 *fSprectrum = new TF1("fSpectrum","gaus + pol4(3)",1.29,1.35);	
	fSpectrum->SetParNames("Strenth","Mean","Sigma","P0","P1","P2","P3","P4");
	fSpectrum->SetParameters(100,1.321,0.003,0,0,0,0,0);
	his->Fit("fSpectrum","","",1.29,1.35);
	Double_t param[8];
	fSpectrum->GetParameters(param);
	fSignal->SetParameters(&param[0]);
	fBackground->SetParameters(&param[3]);
	TH1F *hisSignal = new TH1F(*his);
	hisSignal->Sumw2();
	hisSignal->Add(fBackground,-1);
	his->Draw("e");hisSignal->Draw("SAME");
	fSignal->SetLineColor(1);
	fBackground->SetLineColor(9);
	fSignal->Draw("Same");
    fBackground->Draw("SAME");

	Double_t binw = his->GetBinWidth(1);
	Double_t intSpectrum = fSpectrum->Integral(param[1] - 3*param[2], param[1] + 3*param[2]); //three sigma
    
    
	Int_t YieldSpectrum = intSpectrum/binw;
	Int_t eYieldSpectrum = sqrt(YieldSpectrum);
	cout <<" YieldSpectrum = "<<YieldSpectrum<< " +/- "<< eYieldSpectrum <<endl;
	Double_t intSignal = fSignal->Integral(param[1] - 3*param[2], param[1] + 3*param[2]); //three sigma
	Int_t YieldSignal = intSignal/binw;
	Int_t YieldSignal = intSignal/binw;
	Int_t eYieldSignal = sqrt(YieldSignal);
//	cout <<" YieldSignal = "<<YieldSignal<< " +/- "<< eYieldSignal <<endl;
	return(YieldSignal);
}