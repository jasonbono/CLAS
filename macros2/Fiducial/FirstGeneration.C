

void FirstGeneration()
{
	
	StyleUp();
	
	const int Np = 15;  //number of momentum bins	
	const int Nt = 15;  //number of theta bins	
	const int Ns = 6;
	
	
	//input
	TFile* fInput = new TFile(Form("./hists/Phi-%i-%ibins.root",Np,Nt));
	//output
	TFile* fOutput = new TFile(Form("./hists/FirstGen-%i-%ibins.root",Np,Nt),"RECREATE");
	TCanvas *CAN = new TCanvas("CAN","CAN",1000,800);
	
	
	///////////////////////////////////////////////// begin pip calculation ////////////////////////////////////////////////////
	
	//read in momentum hists, draw them, get bin centers
	//TCanvas *cpcenter_pip = new TCanvas("cpcenter_pip","cpcenter_pip",1000,800);
	//cpcenter_pip->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter_pip[Np][Nt];
	Double_t pcenter_pip[Np][Nt] = {0};
	Double_t prms_pip[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
	//		cpcenter_pip->cd(cancount);
			hpcenter_pip[p][t] = (TH1F*)fInput->Get(Form("hpcenter_pip_p%i_t%i",p,t));
	//		hpcenter_pip[p][t]->Draw();
			cancount += 1;
			pcenter_pip[p][t] =  hpcenter_pip[p][t]->GetMean();
			prms_pip[p][t] =  hpcenter_pip[p][t]->GetRMS();
			
			cout << " pcenter = " <<pcenter_pip[p][t]<<endl;
			
			//pass along once again to next root file
			hpcenter_pip[p][t]->Write();
		}
	}	
	cout <<endl;
	//read in theta hists, draw them, get bin centers
	//TCanvas *ctcenter_pip = new TCanvas("ctcenter_pip","ctcenter_pip",1000,800);
	//ctcenter_pip->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *htcenter_pip[Np][Nt];
	Double_t tcenter_pip[Np][Nt] = {0};
	Double_t trms_pip[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
	//		ctcenter_pip->cd(cancount);
			htcenter_pip[p][t] = (TH1F*)fInput->Get(Form("htcenter_pip_p%i_t%i",p,t));
	//		htcenter_pip[p][t]->Draw();
			cancount += 1;
			tcenter_pip[p][t] =  htcenter_pip[p][t]->GetMean();
			trms_pip[p][t] =  htcenter_pip[p][t]->GetRMS();
			cout << " tcenter pip = " <<tcenter_pip[p][t]<<endl;
			
			//pass along once again to next root file
			htcenter_pip[p][t]->Write();
		}
	}	
	//read in phi hists
	TH1F *hphidiff_pip[Np][Nt][Ns];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				hphidiff_pip[p][t][s] = (TH1F*)fInput->Get(Form("hphidiff_pip_p%i_t%i_s%i",p,t,s));
				hphidiff_pip[p][t][s]->GetYaxis()->SetTitle(Form("Sector%i_p%i_t%i",s+1,p,t));			
			}
		}
	}	
	//declarations for fitting
	Double_t fitlow  = -12;	
	Double_t fithigh = 12;
	Double_t center = 0;
	TF1 *fit_pip[Np][Nt][Ns];
	Double_t fitheight_pip[Np][Nt][Ns] = {0};
	Double_t pc50_pip[Np][Nt][Ns] = {0};
	Int_t BinLow50_pip[Np][Nt][Ns] = {0};
	Int_t BinHigh50_pip[Np][Nt][Ns] = {0};
	Double_t ValLow50_pip[Np][Nt][Ns] = {0};
	Double_t ValHigh50_pip[Np][Nt][Ns] = {0};
	TLine *LineLow50_pip[Np][Nt][Ns] = {0};
	TLine *LineHigh50_pip[Np][Nt][Ns] = {0};
	//fit error 
	Double_t efitheight_pip[Np][Nt][Ns] = {0};
	//upper bounds
	Double_t eu_pc50_pip[Np][Nt][Ns] = {0};
	Int_t eu_BinLow50_pip[Np][Nt][Ns] = {0};
	Int_t eu_BinHigh50_pip[Np][Nt][Ns] = {0};
	Double_t eu_ValLow50_pip[Np][Nt][Ns] = {0};
	Double_t eu_ValHigh50_pip[Np][Nt][Ns] = {0};
	TLine *eu_LineLow50_pip[Np][Nt][Ns] = {0};
	TLine *eu_LineHigh50_pip[Np][Nt][Ns] = {0};
	//lower bounds
	Double_t el_pc50_pip[Np][Nt][Ns] = {0};
	Int_t el_BinLow50_pip[Np][Nt][Ns] = {0};
	Int_t el_BinHigh50_pip[Np][Nt][Ns] = {0};
	Double_t el_ValLow50_pip[Np][Nt][Ns] = {0};
	Double_t el_ValHigh50_pip[Np][Nt][Ns] = {0};
	TLine *el_LineLow50_pip[Np][Nt][Ns] = {0};
	TLine *el_LineHigh50_pip[Np][Nt][Ns] = {0};
	//final error
	Double_t eValLow50_pip[Np][Nt][Ns] = {0};
	Double_t eValHigh50_pip[Np][Nt][Ns] = {0};
	//canvas
	TCanvas *cphi_pip[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
	//		cphi_pip[p][t] = new TCanvas(Form("cphi_pip_p%i_t%i",p,t),Form("cphi_pip_p%i_t%i",p,t),1000,800);
	//		cphi_pip[p][t]->Divide(2,3);
			for (int s=0; s<Ns; s++)
			{
	//			cphi_pip[p][t]->cd(s+1);
				fit_pip[p][t][s] = new TF1(Form("fit_pip_p%i_t%i_s%i",p,t,s),"pol0",fitlow,fithigh);
				hphidiff_pip[p][t][s]->Fit(fit_pip[p][t][s],"Rq");
				fitheight_pip[p][t][s] = fit_pip[p][t][s]->GetParameter(0);
				efitheight_pip[p][t][s] = fit_pip[p][t][s]->GetParError(0);
				hphidiff_pip[p][t][s]->Draw();
					
				//50% cuts
				Float_t cutheight = 0.5;
				pc50_pip[p][t][s] = cutheight*fitheight_pip[p][t][s];
				BinLow50_pip[p][t][s] = hphidiff_pip[p][t][s]->FindFirstBinAbove(pc50_pip[p][t][s],1);
				BinHigh50_pip[p][t][s] = hphidiff_pip[p][t][s]->FindLastBinAbove(pc50_pip[p][t][s],1);
				ValLow50_pip[p][t][s] = hphidiff_pip[p][t][s]->GetBinCenter(BinLow50_pip[p][t][s]);
				ValHigh50_pip[p][t][s] = hphidiff_pip[p][t][s]->GetBinCenter(BinHigh50_pip[p][t][s]);	
				LineLow50_pip[p][t][s] = new TLine(ValLow50_pip[p][t][s],0,ValLow50_pip[p][t][s],pc50_pip[p][t][s]);
				LineHigh50_pip[p][t][s] = new TLine(ValHigh50_pip[p][t][s],0,ValHigh50_pip[p][t][s],pc50_pip[p][t][s]);
				LineLow50_pip[p][t][s]->SetLineColor(3);
				LineHigh50_pip[p][t][s]->SetLineColor(3);
				LineLow50_pip[p][t][s]->Draw();
				LineHigh50_pip[p][t][s]->Draw();
				//compute the error (eu stands for upper limit, el stands for lower limit)
				eu_pc50_pip[p][t][s] = cutheight*(fitheight_pip[p][t][s] + efitheight_pip[p][t][s]);
				el_pc50_pip[p][t][s] = cutheight*(fitheight_pip[p][t][s] - efitheight_pip[p][t][s]);
				eu_BinLow50_pip[p][t][s] = hphidiff_pip[p][t][s]->FindFirstBinAbove(eu_pc50_pip[p][t][s],1) + 1; //takes care of two sources of error: fit height & bin width
				el_BinLow50_pip[p][t][s] = hphidiff_pip[p][t][s]->FindFirstBinAbove(el_pc50_pip[p][t][s],1) - 1;
				eu_BinHigh50_pip[p][t][s] = hphidiff_pip[p][t][s]->FindLastBinAbove(eu_pc50_pip[p][t][s],1) + 1;
				el_BinHigh50_pip[p][t][s] = hphidiff_pip[p][t][s]->FindLastBinAbove(el_pc50_pip[p][t][s],1) - 1;
				eu_ValLow50_pip[p][t][s] = hphidiff_pip[p][t][s]->GetBinCenter(eu_BinLow50_pip[p][t][s]);
				el_ValLow50_pip[p][t][s] = hphidiff_pip[p][t][s]->GetBinCenter(el_BinLow50_pip[p][t][s]);
				eu_ValHigh50_pip[p][t][s] = hphidiff_pip[p][t][s]->GetBinCenter(eu_BinHigh50_pip[p][t][s]);
				el_ValHigh50_pip[p][t][s] = hphidiff_pip[p][t][s]->GetBinCenter(el_BinHigh50_pip[p][t][s]);	
				//plot the error
				eu_LineLow50_pip[p][t][s] = new TLine(eu_ValLow50_pip[p][t][s],0,eu_ValLow50_pip[p][t][s],eu_pc50_pip[p][t][s]);
				eu_LineHigh50_pip[p][t][s] = new TLine(eu_ValHigh50_pip[p][t][s],0,eu_ValHigh50_pip[p][t][s],eu_pc50_pip[p][t][s]);
				eu_LineLow50_pip[p][t][s]->SetLineColor(2);
				eu_LineHigh50_pip[p][t][s]->SetLineColor(2);
				eu_LineLow50_pip[p][t][s]->Draw();
				eu_LineHigh50_pip[p][t][s]->Draw();
				el_LineLow50_pip[p][t][s] = new TLine(el_ValLow50_pip[p][t][s],0,el_ValLow50_pip[p][t][s],el_pc50_pip[p][t][s]);
				el_LineHigh50_pip[p][t][s] = new TLine(el_ValHigh50_pip[p][t][s],0,el_ValHigh50_pip[p][t][s],el_pc50_pip[p][t][s]);
				el_LineLow50_pip[p][t][s]->SetLineColor(2);
				el_LineHigh50_pip[p][t][s]->SetLineColor(2);
				el_LineLow50_pip[p][t][s]->Draw();
				el_LineHigh50_pip[p][t][s]->Draw();				
				
				//CAN->update();
				CAN->Print(Form("./pics/FirstGen/PhiFit_pip-p%i-t%i-sec%i.eps",p,t,s+1));
				//store error as a symentrical value about for graphing (alternatively could just choose eu or el depending according to what deviates most from the true value)
				eValLow50_pip[p][t][s] = (eu_ValLow50_pip[p][t][s] - el_ValLow50_pip[p][t][s])/2;
				eValHigh50_pip[p][t][s] = (eu_ValHigh50_pip[p][t][s] - el_ValHigh50_pip[p][t][s])/2;
			}
		}
	}

	//get the high and low cut values in a form thats plotable
	Double_t H50_pip[Ns][Np][Nt] = {0};
	Double_t L50_pip[Ns][Np][Nt] = {0};
	Double_t eH50_pip[Ns][Np][Nt] = {0};
	Double_t eL50_pip[Ns][Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Np; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				H50_pip[s][p][t] = ValHigh50_pip[p][t][s];
				L50_pip[s][p][t] = ValLow50_pip[p][t][s];
				eH50_pip[s][p][t] = eValHigh50_pip[p][t][s];
				eL50_pip[s][p][t] = eValLow50_pip[p][t][s];
			}
		}
	}	
	//1d graphs of cuts and theta in sclices of p
	TCanvas *cL50_pip[Np];
	TGraphErrors *grL50_pip[Np][Ns];
	TCanvas *cH50_pip[Np];
	TGraphErrors *grH50_pip[Np][Ns];
	for (int p=0; p<Np; p++)
	{
	//	cL50_pip[p] = new TCanvas(Form("cL50_pip_p%i",p),Form("cL50_pip_p%i",p),1000,800);
	//	cL50_pip[p]->Divide(3,2);
	//	cH50_pip[p] = new TCanvas(Form("cH50_pip_p%i",p),Form("cH50_pip_p%i",p),1000,800);
	//	cH50_pip[p]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			grL50_pip[p][s] = new TGraphErrors(Nt,tcenter_pip[p],L50_pip[s][p],0,eL50_pip[s][p]);
			grL50_pip[p][s]->SetMarkerSize(1.2);
			grL50_pip[p][s]->SetMarkerColor(2);
			grL50_pip[p][s]->SetMarkerStyle(8);
			grL50_pip[p][s]->GetXaxis()->SetTitle("#theta");
			grL50_pip[p][s]->GetYaxis()->SetTitle("Low Cut (#delta#phi)");
			grL50_pip[p][s]->SetName(Form("grL50_pip_p%i-sector%i",p,s+1));
			grL50_pip[p][s]->SetTitle(Form("grL50_pip_p%i-sector%i",p,s+1));
	//		cL50_pip[p]->cd(s+1);
			grL50_pip[p][s]->Draw("AP");
			grL50_pip[p][s]->Write();
		
			grH50_pip[p][s] = new TGraphErrors(Nt,tcenter_pip[p],H50_pip[s][p],0,eH50_pip[s][p]);
			grH50_pip[p][s]->SetMarkerSize(1.2);
			grH50_pip[p][s]->SetMarkerColor(3);
			grH50_pip[p][s]->SetMarkerStyle(8);
			grH50_pip[p][s]->GetXaxis()->SetTitle("#theta");
			grH50_pip[p][s]->GetYaxis()->SetTitle("High Cut (#delta#phi)");
			grH50_pip[p][s]->SetName(Form("grH50_pip_p%i-sector%i",p,s+1));
			grH50_pip[p][s]->SetTitle(Form("grH50_pip_p%i-sector%i",p,s+1));
	//		cH50_pip[p]->cd(s+1);
			grH50_pip[p][s]->Draw("AP");
			grH50_pip[p][s]->Write();		
		}
	}
	cout << "tcenters pip = " <<tcenter_pip[0][0] << ",  " <<tcenter_pip[0][1] <<",  " << tcenter_pip[0][2] <<endl;
	///////////////////////////////////////////////// end pip calculation ////////////////////////////////////////////////////









	///////////////////////////////////////////////// begin pim calculation ////////////////////////////////////////////////////
	
	//read in momentum hists, draw them, get bin centers
	//TCanvas *cpcenter_pim = new TCanvas("cpcenter_pim","cpcenter_pim",1000,800);
	//cpcenter_pim->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter_pim[Np][Nt];
	Double_t pcenter_pim[Np][Nt] = {0};
	Double_t prms_pim[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
	//		cpcenter_pim->cd(cancount);
			hpcenter_pim[p][t] = (TH1F*)fInput->Get(Form("hpcenter_pim_p%i_t%i",p,t));
	//		hpcenter_pim[p][t]->Draw();
			cancount += 1;
			pcenter_pim[p][t] =  hpcenter_pim[p][t]->GetMean();
			prms_pim[p][t] =  hpcenter_pim[p][t]->GetRMS();
			
			cout << " pcenter = " <<pcenter_pim[p][t]<<endl;
			
			//pass along once again to next root file
			hpcenter_pim[p][t]->Write();
		}
	}	
	cout <<endl;
	//read in theta hists, draw them, get bin centers
	//TCanvas *ctcenter_pim = new TCanvas("ctcenter_pim","ctcenter_pim",1000,800);
	//ctcenter_pim->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *htcenter_pim[Np][Nt];
	Double_t tcenter_pim[Np][Nt] = {0};
	Double_t trms_pim[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
	//		ctcenter_pim->cd(cancount);
			htcenter_pim[p][t] = (TH1F*)fInput->Get(Form("htcenter_pim_p%i_t%i",p,t));
	//		htcenter_pim[p][t]->Draw();
			cancount += 1;
			tcenter_pim[p][t] =  htcenter_pim[p][t]->GetMean();
			trms_pim[p][t] =  htcenter_pim[p][t]->GetRMS();
			cout << " tcenter pim = " <<tcenter_pim[p][t]<<endl;
			
			//pass along once again to next root file
			htcenter_pim[p][t]->Write();
		}
	}	
	//read in phi hists
	TH1F *hphidiff_pim[Np][Nt][Ns];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				hphidiff_pim[p][t][s] = (TH1F*)fInput->Get(Form("hphidiff_pim_p%i_t%i_s%i",p,t,s));
				hphidiff_pim[p][t][s]->GetYaxis()->SetTitle(Form("Sector%i_p%i_t%i",s+1,p,t));			
			}
		}
	}	
	//declarations for fitting
	Double_t fitlow  = -12;	
	Double_t fithigh = 12;
	Double_t center = 0;
	TF1 *fit_pim[Np][Nt][Ns];
	Double_t fitheight_pim[Np][Nt][Ns] = {0};
	Double_t pc50_pim[Np][Nt][Ns] = {0};
	Int_t BinLow50_pim[Np][Nt][Ns] = {0};
	Int_t BinHigh50_pim[Np][Nt][Ns] = {0};
	Double_t ValLow50_pim[Np][Nt][Ns] = {0};
	Double_t ValHigh50_pim[Np][Nt][Ns] = {0};
	TLine *LineLow50_pim[Np][Nt][Ns] = {0};
	TLine *LineHigh50_pim[Np][Nt][Ns] = {0};
	//fit error 
	Double_t efitheight_pim[Np][Nt][Ns] = {0};
	//upper bounds
	Double_t eu_pc50_pim[Np][Nt][Ns] = {0};
	Int_t eu_BinLow50_pim[Np][Nt][Ns] = {0};
	Int_t eu_BinHigh50_pim[Np][Nt][Ns] = {0};
	Double_t eu_ValLow50_pim[Np][Nt][Ns] = {0};
	Double_t eu_ValHigh50_pim[Np][Nt][Ns] = {0};
	TLine *eu_LineLow50_pim[Np][Nt][Ns] = {0};
	TLine *eu_LineHigh50_pim[Np][Nt][Ns] = {0};
	//lower bounds
	Double_t el_pc50_pim[Np][Nt][Ns] = {0};
	Int_t el_BinLow50_pim[Np][Nt][Ns] = {0};
	Int_t el_BinHigh50_pim[Np][Nt][Ns] = {0};
	Double_t el_ValLow50_pim[Np][Nt][Ns] = {0};
	Double_t el_ValHigh50_pim[Np][Nt][Ns] = {0};
	TLine *el_LineLow50_pim[Np][Nt][Ns] = {0};
	TLine *el_LineHigh50_pim[Np][Nt][Ns] = {0};
	//final error
	Double_t eValLow50_pim[Np][Nt][Ns] = {0};
	Double_t eValHigh50_pim[Np][Nt][Ns] = {0};
	//canvas
	TCanvas *cphi_pim[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
	//		cphi_pim[p][t] = new TCanvas(Form("cphi_pim_p%i_t%i",p,t),Form("cphi_pim_p%i_t%i",p,t),1000,800);
	//		cphi_pim[p][t]->Divide(2,3);
			for (int s=0; s<Ns; s++)
			{
	//			cphi_pim[p][t]->cd(s+1);
				fit_pim[p][t][s] = new TF1(Form("fit_pim_p%i_t%i_s%i",p,t,s),"pol0",fitlow,fithigh);
				hphidiff_pim[p][t][s]->Fit(fit_pim[p][t][s],"Rq");
				fitheight_pim[p][t][s] = fit_pim[p][t][s]->GetParameter(0);
				efitheight_pim[p][t][s] = fit_pim[p][t][s]->GetParError(0);
				hphidiff_pim[p][t][s]->Draw();
					
				//50% cuts
				Float_t cutheight = 0.5;
				pc50_pim[p][t][s] = cutheight*fitheight_pim[p][t][s];
				BinLow50_pim[p][t][s] = hphidiff_pim[p][t][s]->FindFirstBinAbove(pc50_pim[p][t][s],1);
				BinHigh50_pim[p][t][s] = hphidiff_pim[p][t][s]->FindLastBinAbove(pc50_pim[p][t][s],1);
				ValLow50_pim[p][t][s] = hphidiff_pim[p][t][s]->GetBinCenter(BinLow50_pim[p][t][s]);
				ValHigh50_pim[p][t][s] = hphidiff_pim[p][t][s]->GetBinCenter(BinHigh50_pim[p][t][s]);	
				LineLow50_pim[p][t][s] = new TLine(ValLow50_pim[p][t][s],0,ValLow50_pim[p][t][s],pc50_pim[p][t][s]);
				LineHigh50_pim[p][t][s] = new TLine(ValHigh50_pim[p][t][s],0,ValHigh50_pim[p][t][s],pc50_pim[p][t][s]);
				LineLow50_pim[p][t][s]->SetLineColor(3);
				LineHigh50_pim[p][t][s]->SetLineColor(3);
				LineLow50_pim[p][t][s]->Draw();
				LineHigh50_pim[p][t][s]->Draw();
				//compute the error (eu stands for upper limit, el stands for lower limit)
				eu_pc50_pim[p][t][s] = cutheight*(fitheight_pim[p][t][s] + efitheight_pim[p][t][s]);
				el_pc50_pim[p][t][s] = cutheight*(fitheight_pim[p][t][s] - efitheight_pim[p][t][s]);
				eu_BinLow50_pim[p][t][s] = hphidiff_pim[p][t][s]->FindFirstBinAbove(eu_pc50_pim[p][t][s],1) + 1; //takes care of two sources of error: fit height & bin width
				el_BinLow50_pim[p][t][s] = hphidiff_pim[p][t][s]->FindFirstBinAbove(el_pc50_pim[p][t][s],1) - 1;
				eu_BinHigh50_pim[p][t][s] = hphidiff_pim[p][t][s]->FindLastBinAbove(eu_pc50_pim[p][t][s],1) + 1;
				el_BinHigh50_pim[p][t][s] = hphidiff_pim[p][t][s]->FindLastBinAbove(el_pc50_pim[p][t][s],1) - 1;
				eu_ValLow50_pim[p][t][s] = hphidiff_pim[p][t][s]->GetBinCenter(eu_BinLow50_pim[p][t][s]);
				el_ValLow50_pim[p][t][s] = hphidiff_pim[p][t][s]->GetBinCenter(el_BinLow50_pim[p][t][s]);
				eu_ValHigh50_pim[p][t][s] = hphidiff_pim[p][t][s]->GetBinCenter(eu_BinHigh50_pim[p][t][s]);
				el_ValHigh50_pim[p][t][s] = hphidiff_pim[p][t][s]->GetBinCenter(el_BinHigh50_pim[p][t][s]);	
				//plot the error
				eu_LineLow50_pim[p][t][s] = new TLine(eu_ValLow50_pim[p][t][s],0,eu_ValLow50_pim[p][t][s],eu_pc50_pim[p][t][s]);
				eu_LineHigh50_pim[p][t][s] = new TLine(eu_ValHigh50_pim[p][t][s],0,eu_ValHigh50_pim[p][t][s],eu_pc50_pim[p][t][s]);
				eu_LineLow50_pim[p][t][s]->SetLineColor(2);
				eu_LineHigh50_pim[p][t][s]->SetLineColor(2);
				eu_LineLow50_pim[p][t][s]->Draw();
				eu_LineHigh50_pim[p][t][s]->Draw();
				el_LineLow50_pim[p][t][s] = new TLine(el_ValLow50_pim[p][t][s],0,el_ValLow50_pim[p][t][s],el_pc50_pim[p][t][s]);
				el_LineHigh50_pim[p][t][s] = new TLine(el_ValHigh50_pim[p][t][s],0,el_ValHigh50_pim[p][t][s],el_pc50_pim[p][t][s]);
				el_LineLow50_pim[p][t][s]->SetLineColor(2);
				el_LineHigh50_pim[p][t][s]->SetLineColor(2);
				el_LineLow50_pim[p][t][s]->Draw();
				el_LineHigh50_pim[p][t][s]->Draw();				
				
				//CAN->update();
				CAN->Print(Form("./pics/FirstGen/PhiFit_pim-p%i-t%i-sec%i.eps",p,t,s+1));
				//store error as a symentrical value about for graphing (alternatively could just choose eu or el depending according to what deviates most from the true value)
				eValLow50_pim[p][t][s] = (eu_ValLow50_pim[p][t][s] - el_ValLow50_pim[p][t][s])/2;
				eValHigh50_pim[p][t][s] = (eu_ValHigh50_pim[p][t][s] - el_ValHigh50_pim[p][t][s])/2;
			}
		}
	}

	//get the high and low cut values in a form thats plotable
	Double_t H50_pim[Ns][Np][Nt] = {0};
	Double_t L50_pim[Ns][Np][Nt] = {0};
	Double_t eH50_pim[Ns][Np][Nt] = {0};
	Double_t eL50_pim[Ns][Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Np; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				H50_pim[s][p][t] = ValHigh50_pim[p][t][s];
				L50_pim[s][p][t] = ValLow50_pim[p][t][s];
				eH50_pim[s][p][t] = eValHigh50_pim[p][t][s];
				eL50_pim[s][p][t] = eValLow50_pim[p][t][s];
			}
		}
	}	
	//1d graphs of cuts and theta in sclices of p
	TCanvas *cL50_pim[Np];
	TGraphErrors *grL50_pim[Np][Ns];
	TCanvas *cH50_pim[Np];
	TGraphErrors *grH50_pim[Np][Ns];
	for (int p=0; p<Np; p++)
	{
	//	cL50_pim[p] = new TCanvas(Form("cL50_pim_p%i",p),Form("cL50_pim_p%i",p),1000,800);
	//	cL50_pim[p]->Divide(3,2);
	//	cH50_pim[p] = new TCanvas(Form("cH50_pim_p%i",p),Form("cH50_pim_p%i",p),1000,800);
	//	cH50_pim[p]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			grL50_pim[p][s] = new TGraphErrors(Nt,tcenter_pim[p],L50_pim[s][p],0,eL50_pim[s][p]);
			grL50_pim[p][s]->SetMarkerSize(1.2);
			grL50_pim[p][s]->SetMarkerColor(2);
			grL50_pim[p][s]->SetMarkerStyle(8);
			grL50_pim[p][s]->GetXaxis()->SetTitle("#theta");
			grL50_pim[p][s]->GetYaxis()->SetTitle("Low Cut (#delta#phi)");
			grL50_pim[p][s]->SetName(Form("grL50_pim_p%i-sector%i",p,s+1));
			grL50_pim[p][s]->SetTitle(Form("grL50_pim_p%i-sector%i",p,s+1));
	//		cL50_pim[p]->cd(s+1);
			grL50_pim[p][s]->Draw("AP");
			grL50_pim[p][s]->Write();
		
			grH50_pim[p][s] = new TGraphErrors(Nt,tcenter_pim[p],H50_pim[s][p],0,eH50_pim[s][p]);
			grH50_pim[p][s]->SetMarkerSize(1.2);
			grH50_pim[p][s]->SetMarkerColor(3);
			grH50_pim[p][s]->SetMarkerStyle(8);
			grH50_pim[p][s]->GetXaxis()->SetTitle("#theta");
			grH50_pim[p][s]->GetYaxis()->SetTitle("High Cut (#delta#phi)");
			grH50_pim[p][s]->SetName(Form("grH50_pim_p%i-sector%i",p,s+1));
			grH50_pim[p][s]->SetTitle(Form("grH50_pim_p%i-sector%i",p,s+1));
	//		cH50_pim[p]->cd(s+1);
			grH50_pim[p][s]->Draw("AP");
			grH50_pim[p][s]->Write();		
		}
	}
	cout << "tcenters pim = " <<tcenter_pim[0][0] << ",  " <<tcenter_pim[0][1] <<",  " << tcenter_pim[0][2] <<endl;
	///////////////////////////////////////////////// end pim calculation ////////////////////////////////////////////////////













}

////////////////////////////////////////////////////////////////////////


StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.08);
	gStyle->SetTitleYSize(0.07); 
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(1);
}
