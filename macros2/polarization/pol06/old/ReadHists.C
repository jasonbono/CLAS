


void ReadHists()
{
	
	const int NEBins = 3;
	const int NPiBins = 4;
	TFile* fHists = new TFile("histosEbins.root");
	
	//canvas
	TCanvas *cData[NEBins];
	TCanvas *cMC[NEBins];
	TCanvas *cGen[NEBins];
	TCanvas *cAc[NEBins];
	
	//hists
	TH1F *hDataX[NEBins], *hDataY[NEBins] , *hDataZ[NEBins];
	TH1F *hMCX[NEBins], *hMCY[NEBins], *hMCZ[NEBins];
	TH1F *hGenX[NEBins], *hGenY[NEBins], *hGenZ[NEBins];	
	TH1F *hAcX[NEBins], *hAcY[NEBins], *hAcZ[NEBins]; 

	
	
	
	//model hist to clone
	TH1F *hAngles = new TH1F("hAngles","",NPiBins, -1,1);
	hAngles->SetMinimum(0);


	//loop over energy bins
	for (int i = 0; i < NEBins; i++)
	{
		
		//-------------------Data------------------------------------------
		cData[i] = new TCanvas(Form("cData%i",i),Form("cData%i",i),700,400);
		cData[i]->Divide(3,0);
		
		cData[i]->cd(1);
		hDataX[i] = (TH1F*)fHists->Get(Form("hDataPiX-EBin%i",i));
		hDataX[i]->SetMinimum(-1);
		hDataX[i]->Draw("E");
		
		cData[i]->cd(2);
		hDataY[i] = (TH1F*)fHists->Get(Form("hDataPiY-EBin%i",i));	
		hDataY[i]->SetMinimum(-1);
		hDataY[i]->Draw("E");
				
		cData[i]->cd(3);
		hDataZ[i] = (TH1F*)fHists->Get(Form("hDataPiZ-EBin%i",i));	
		hDataZ[i]->SetMinimum(-1);
		hDataZ[i]->Draw("E");
		
		//-------------------MC------------------------------------------
		cMC[i] = new TCanvas(Form("cMC%i",i),Form("cMC%i",i),700,400);
		cMC[i]->Divide(3,0);
		
		cMC[i]->cd(1);
		hMCX[i] = (TH1F*)fHists->Get(Form("hMCPiX-EBin%i",i));
		hMCX[i]->SetMinimum(-1);
		hMCX[i]->Draw("E");
		
		cMC[i]->cd(2);
		hMCY[i] = (TH1F*)fHists->Get(Form("hMCPiY-EBin%i",i));
		hMCY[i]->SetMinimum(-1);	
		hMCY[i]->Draw("E");
				
		cMC[i]->cd(3);
		hMCZ[i] = (TH1F*)fHists->Get(Form("hMCPiZ-EBin%i",i));
		hMCZ[i]->SetMinimum(-1);	
		hMCZ[i]->Draw("E");
		
		//-------------------Gen------------------------------------------
		cGen[i] = new TCanvas(Form("cGen%i",i),Form("cGen%i",i),700,400);
		cGen[i]->Divide(3,0);
		
		cGen[i]->cd(1);
		hGenX[i] = (TH1F*)fHists->Get(Form("hGenPiX-EBin%i",i));
		hGenX[i]->SetMinimum(-1);
		hGenX[i]->Draw("E");
		
		cGen[i]->cd(2);
		hGenY[i] = (TH1F*)fHists->Get(Form("hGenPiY-EBin%i",i));	
		hGenY[i]->SetMinimum(-1);
		hGenY[i]->Draw("E");
				
		cGen[i]->cd(3);
		hGenZ[i] = (TH1F*)fHists->Get(Form("hGenPiZ-EBin%i",i));
		hGenZ[i]->SetMinimum(-1);	
		hGenZ[i]->Draw("E");

	
	}
		
		
	//============================fill the populations================		

	Double_t nDataX[3][4], nDataY[3][4], nDataZ[3][4];	
	Double_t nMCX[3][4], nMCY[3][4], nMCZ[3][4];
	Double_t nGenX[3][4], nGenY[3][4], nGenZ[3][4];
	
	for (int i = 0; i < NEBins; i++)
	{
		for (int j = 0; j < NPiBins; j++)
		{
			nDataX[i][j] = hDataX[i]->GetBinContent(j+1);
			nDataY[i][j] = hDataY[i]->GetBinContent(j+1);
			nDataZ[i][j] = hDataZ[i]->GetBinContent(j+1);
			
			nMCX[i][j] = hMCX[i]->GetBinContent(j+1);
			nMCY[i][j] = hMCY[i]->GetBinContent(j+1);
			nMCZ[i][j] = hMCZ[i]->GetBinContent(j+1);
			
			nGenX[i][j] = hGenX[i]->GetBinContent(j+1);
			nGenY[i][j] = hGenY[i]->GetBinContent(j+1);
			nGenZ[i][j] = hGenZ[i]->GetBinContent(j+1);
			//cout << "i = " << i << "  j = " << j << "  nDataX[i][j] = " << nDataX[i][j] << endl;					
	
		}
	}
	

	//========================Get Acceptance================		

	Double_t nAcX[3][4], nAcY[3][4], nAcZ[3][4];	
	
	for (int i = 0; i < NEBins; i++)
	{
		for (int j = 0; j < NPiBins; j++)
		{
	
			nAcX[i][j] = nMCX[i][j]/nGenX[i][j];
			nAcY[i][j] = nMCY[i][j]/nGenY[i][j];
			nAcZ[i][j] = nMCZ[i][j]/nGenZ[i][j];
	
		}
	}



	//========================Apply Acceptance Corrections================		

	Double_t nDataAcX[3][4], nDataAcY[3][4], nDataAcZ[3][4];	
	Double_t nMCAcX[3][4], nMCAcY[3][4], nMCAcZ[3][4];
	
	
	for (int i = 0; i < NEBins; i++)
	{
		for (int j = 0; j < NPiBins; j++)
		{
	
			nDataAcX[i][j] = nDataX[i][j]/nAcX[i][j];
			nDataAcY[i][j] = nDataY[i][j]/nAcY[i][j];
			nDataAcZ[i][j] = nDataZ[i][j]/nAcZ[i][j];
			
			//test to see if we get a flat distribution
			nMCAcX[i][j] = nMCX[i][j]/nAcX[i][j];
			nMCAcY[i][j] = nMCY[i][j]/nAcY[i][j];
			nMCAcZ[i][j] = nMCZ[i][j]/nAcZ[i][j];
	
		}
	}


	//====================Fill populations to histograms and plot=====================
	TCanvas *cDataAc[NEBins],*cMCAc[NEBins];

	TH1F *hDataAcX[NEBins], *hDataAcY[NEBins], *hDataAcZ[NEBins]; 
	TH1F *hMCAcX[NEBins], *hMCAcY[NEBins], *hMCAcZ[NEBins]; 


	for (int i = 0; i < NEBins; i++)
	{
	
		cDataAc[i] = new TCanvas(Form("cDataAc%i",i),Form("cDataAc%i",i),1200,800);
		cDataAc[i]->Divide(3,0);
		cMCAc[i] = new TCanvas(Form("cMCAc%i",i),Form("cMCAc%i",i),700,400);
		cMCAc[i]->Divide(3,0);
		
		hDataAcX[i] = (TH1F*)hAngles->Clone(Form("hDataAcX_EBin%i",i));
		hDataAcY[i] = (TH1F*)hAngles->Clone(Form("hDataAcY_EBin%i",i));
		hDataAcZ[i] = (TH1F*)hAngles->Clone(Form("hDataAcZ_EBin%i",i));
		
		hMCAcX[i] = (TH1F*)hAngles->Clone(Form("hMCAcX_EBin%i",i));
		hMCAcY[i] = (TH1F*)hAngles->Clone(Form("hMCAcY_EBin%i",i));
		hMCAcZ[i] = (TH1F*)hAngles->Clone(Form("hMCAcZ_EBin%i",i));
		
		for (int j = 0; j < NPiBins; j++)
		{
			
			
			hDataAcX[i]->SetBinContent(j+1,nDataAcX[i][j]);
			hDataAcY[i]->SetBinContent(j+1,nDataAcY[i][j]);
			hDataAcZ[i]->SetBinContent(j+1,nDataAcZ[i][j]);
		
			hMCAcX[i]->SetBinContent(j+1,nMCAcX[i][j]);
			hMCAcY[i]->SetBinContent(j+1,nMCAcY[i][j]);
			hMCAcZ[i]->SetBinContent(j+1,nMCAcZ[i][j]);
			
			
		}	
	
		
		cDataAc[i]->cd(1);
		hDataAcX[i]->Draw("E");
		cDataAc[i]->cd(2);
		hDataAcY[i]->Draw("E");
		cDataAc[i]->cd(3);
		hDataAcZ[i]->Draw("E");
		
		cMCAc[i]->cd(1);
		hMCAcX[i]->Draw();
		cMCAc[i]->cd(2);
		hMCAcY[i]->Draw();
		cMCAc[i]->cd(3);
		hMCAcZ[i]->Draw();		


	}


}







/*
	
		//------------------------Ac---------------------
		cAc[i] = new TCanvas(Form("cAc%i",i),Form("cAc%i",i),700,400);
		cAc[i]->Divide(3,0);
		
		
		hAcX[i] = (TH1F*)hAngles->Clone(Form("hAcX_EBin%i",i));
		hAcY[i] = (TH1F*)hAngles->Clone(Form("hAcY-EBin%i",i));
		hAcZ[i] = (TH1F*)hAngles->Clone(Form("hAcZ-EBin%i",i));
		
		hAcX[i]->Divide(hMCX[i], hGenX[i]);
	 	hAcY[i]->Divide(hMCY[i], hGenY[i]);
	 	hAcZ[i]->Divide(hMCZ[i], hGenZ[i]);

		cAc[i]->cd(1);
		hAcX[i]->Draw("E");
		cAc[i]->cd(2);
		hAcY[i]->Draw("E");
		cAc[i]->cd(3);
		hAcZ[i]->Draw("E");
//*/
	