


const int Ns = 6;
TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
TTree *tData = (TTree*)fData->Get("v05");
TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i8-2kppim_Basic_Mass.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");

TFile *fDataFid = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass-Fid.root");
TTree *tDataFid = (TTree*)fDataFid->Get("v05Loose");
TFile *fMCFid = TFile::Open("~/clas/rootfiles/LINKS/MC-i8-2kppim_Basic_Mass_Fid.root");
TTree *tMCFid = (TTree*)fMCFid->Get("gpp2kppimLoose");


TTree *mytData = tDataFid;
TTree *mytMC = tMCFid;
//TTree *mytData = tData;
//TTree *mytMC = tMC;

void PhiDeviation()
{	
	StyleUp();
	PimDev();
	Kp1Dev();
	Kp2Dev();
	


}

PimDev()
{

	TCut pim_seccut[Ns];
	pim_seccut[0] = "pimsector == 1";
	pim_seccut[1] = "pimsector == 2";
	pim_seccut[2] = "pimsector == 3";
	pim_seccut[3] = "pimsector == 4";
	pim_seccut[4] = "pimsector == 5";
	pim_seccut[5] = "pimsector == 6";

	
	gStyle->SetOptStat(1);



	TCanvas *cphi_pim;
	cphi_pim = new TCanvas("cphi_pim_","cphi_pim",1000,800);
	cphi_pim->Divide(2,3);

	
	TH1F *hDataphidiff_pim[Ns];
	TH1F *hMCphidiff_pim[Ns];

	
	float temp1 = mytData->GetEntries();
	float temp2 = mytMC->GetEntries();
	float normfac = temp1/temp2;



	Float_t Data_pim[Ns] = {0};
	Float_t MC_pim[Ns] = {0};
	Float_t TotalAbsDev_pim[Ns] = {0};
	Float_t TotalDev_pim[Ns] = {0};
	Float_t Moment_pim[Ns] = {0};
	Float_t StanDev_pim[Ns] = {0};
	Float_t AbsDev_pim[Ns] = {0};
	Float_t AvgDev_pim[Ns] = {0};
	Float_t counter[Ns] = {0};
	for (int s=0; s<Ns; s++)
	{
		cphi_pim->cd(s+1);
		hDataphidiff_pim[s] = new TH1F(Form("hDataphidiff_pim_s%i",s),"",60,-30,30);
		hDataphidiff_pim[s]->GetXaxis()->SetTitle("#phi (#pi -)");
		hDataphidiff_pim[s]->GetYaxis()->SetTitle(Form("sector_%i",s+1));
		mytData->Draw(Form("pimphidiff>>hDataphidiff_pim_s%i",s),pim_seccut[s]);
		
		hMCphidiff_pim[s] = new TH1F(Form("hMCphidiff_pim_s%i",s),"",60,-30,30);
		hMCphidiff_pim[s]->GetXaxis()->SetTitle("#phi (#pi -)");
		hMCphidiff_pim[s]->GetYaxis()->SetTitle(Form("sector_%i",s+1)); 
		mytMC->Draw(Form("pimphidiff>>hMCphidiff_pim_s%i",s),pim_seccut[s]);
		hMCphidiff_pim[s]->SetLineColor(2);

		hMCphidiff_pim[s]->Add(hMCphidiff_pim[s], normfac - 1);
		hDataphidiff_pim[s]->Draw("E");
		hMCphidiff_pim[s]->Draw("SAME");
		
		
		for (int b=0; b<60; b++)
		{
			if ( (hDataphidiff_pim[s]->GetBinContent(b) != 0) || (hMCphidiff_pim[s]->GetBinContent(b) !=0 ) ) //only NOT satisfied when mc AND data hists are zero in that bin
			{
				counter[s] += 1;
				Data_pim[s] = hDataphidiff_pim[s]->GetBinContent(b);
				MC_pim[s] = hMCphidiff_pim[s]->GetBinContent(b);
				TotalAbsDev_pim[s] += TMath::Abs(Data_pim[s] - MC_pim[s]);
				TotalDev_pim[s] += (Data_pim[s] - MC_pim[s]);
				Moment_pim[s] += (Data_pim[s] - MC_pim[s])*(Data_pim[s] - MC_pim[s]);

				cout << " for bin " <<b <<" bin content for Data is " <<	Data_pim[s] <<endl;
				cout << " for bin " <<b <<" bin content for MC is " << MC_pim[s] <<endl;
				cout << " for bin " <<b <<" bin difference is " << TotalAbsDev_pim[s] <<endl<<endl;
			}
		}
	}

	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int s=0; s<Ns; s++)
	{
		StanDev_pim[s] = sqrt( (1/(counter[s] - 1))*Moment_pim[s] );
		AbsDev_pim[s] = TotalAbsDev_pim[s]/counter[s];
		AvgDev_pim[s] = TotalDev_pim[s]/counter[s];
		cout << "total devation for sector " << s+1 <<" = " << TotalAbsDev_pim[s] << "  and number of bins was  " << counter[s] <<endl;
		cout << "absolute devation for sector " << s+1 <<" = " << AbsDev_pim[s]  <<endl;
		cout << "average devation for sector " << s+1 <<" = " << AvgDev_pim[s]  <<endl;
		cout << "standard devation for sector " << s+1 <<" = " << StanDev_pim[s] <<endl<<endl;
		
		
		mytex=new TLatex(-20, 30,Form("Abs Dev = %5.3f^{#circ} ",AbsDev_pim[s] ));
		cphi_pim->cd(s+1);
		mytex->SetTextSize(0.09); 
		mytex->SetTextColor(4);
		mytex->Draw("SAME");
		
		mytex2=new TLatex(-20, 25,Form("Avg Dev = %5.3f^{#circ} ",AvgDev_pim[s] ));
		mytex2->SetTextSize(0.09); 
		mytex2->SetTextColor(3);
		mytex2->Draw("SAME");
	}

	cphi_pim->Print("~/Desktop/PhiDev_Loose_pim.png");

}


Kp1Dev()
{

	TCut kp1_seccut[Ns];
	kp1_seccut[0] = "kp1sector == 1";
	kp1_seccut[1] = "kp1sector == 2";
	kp1_seccut[2] = "kp1sector == 3";
	kp1_seccut[3] = "kp1sector == 4";
	kp1_seccut[4] = "kp1sector == 5";
	kp1_seccut[5] = "kp1sector == 6";

	
	gStyle->SetOptStat(1);



	TCanvas *cphi_kp1;
	cphi_kp1 = new TCanvas("cphi_kp1_","cphi_kp1",1000,800);
	cphi_kp1->Divide(2,3);

	
	TH1F *hDataphidiff_kp1[Ns];
	TH1F *hMCphidiff_kp1[Ns];

	
	float temp1 = mytData->GetEntries();
	float temp2 = mytMC->GetEntries();
	float normfac = temp1/temp2;



	Float_t Data_kp1[Ns] = {0};
	Float_t MC_kp1[Ns] = {0};
	Float_t TotalAbsDev_kp1[Ns] = {0};
	Float_t TotalDev_kp1[Ns] = {0};
	Float_t Moment_kp1[Ns] = {0};
	Float_t StanDev_kp1[Ns] = {0};
	Float_t AbsDev_kp1[Ns] = {0};
	Float_t AvgDev_kp1[Ns] = {0};
	Float_t counter[Ns] = {0};
	for (int s=0; s<Ns; s++)
	{
		cphi_kp1->cd(s+1);
		hDataphidiff_kp1[s] = new TH1F(Form("hDataphidiff_kp1_s%i",s),"",60,-30,30);
		hDataphidiff_kp1[s]->GetXaxis()->SetTitle("#phi (k^{+}_{fast})");
		hDataphidiff_kp1[s]->GetYaxis()->SetTitle(Form("sector_%i",s+1));
		mytData->Draw(Form("kp1phidiff>>hDataphidiff_kp1_s%i",s),kp1_seccut[s]);
		
		hMCphidiff_kp1[s] = new TH1F(Form("hMCphidiff_kp1_s%i",s),"",60,-30,30);
		hMCphidiff_kp1[s]->GetXaxis()->SetTitle("#phi (k^{+}_{fast})");
		hMCphidiff_kp1[s]->GetYaxis()->SetTitle(Form("sector_%i",s+1)); 
		mytMC->Draw(Form("kp1phidiff>>hMCphidiff_kp1_s%i",s),kp1_seccut[s]);
		hMCphidiff_kp1[s]->SetLineColor(2);

		hMCphidiff_kp1[s]->Add(hMCphidiff_kp1[s], normfac - 1);
		hDataphidiff_kp1[s]->Draw("E");
		hMCphidiff_kp1[s]->Draw("SAME");
		
		
		for (int b=0; b<60; b++)
		{
			if ( (hDataphidiff_kp1[s]->GetBinContent(b) != 0) || (hMCphidiff_kp1[s]->GetBinContent(b) !=0 ) ) //only NOT satisfied when mc AND data hists are zero in that bin
			{
				counter[s] += 1;
				Data_kp1[s] = hDataphidiff_kp1[s]->GetBinContent(b);
				MC_kp1[s] = hMCphidiff_kp1[s]->GetBinContent(b);
				TotalAbsDev_kp1[s] += TMath::Abs(Data_kp1[s] - MC_kp1[s]);
				TotalDev_kp1[s] += (Data_kp1[s] - MC_kp1[s]);
				Moment_kp1[s] += (Data_kp1[s] - MC_kp1[s])*(Data_kp1[s] - MC_kp1[s]);

				cout << " for bin " <<b <<" bin content for Data is " <<	Data_kp1[s] <<endl;
				cout << " for bin " <<b <<" bin content for MC is " << MC_kp1[s] <<endl;
				cout << " for bin " <<b <<" bin difference is " << TotalAbsDev_kp1[s] <<endl<<endl;
			}
		}
	}

	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int s=0; s<Ns; s++)
	{
		StanDev_kp1[s] = sqrt( (1/(counter[s] - 1))*Moment_kp1[s] );
		AbsDev_kp1[s] = TotalAbsDev_kp1[s]/counter[s];
		AvgDev_kp1[s] = TotalDev_kp1[s]/counter[s];
		cout << "total devation for sector " << s+1 <<" = " << TotalAbsDev_kp1[s] << "  and number of bins was  " << counter[s] <<endl;
		cout << "absolute devation for sector " << s+1 <<" = " << AbsDev_kp1[s]  <<endl;
		cout << "average devation for sector " << s+1 <<" = " << AvgDev_kp1[s]  <<endl;
		cout << "standard devation for sector " << s+1 <<" = " << StanDev_kp1[s] <<endl<<endl;
		
		
		mytex=new TLatex(-20, 23,Form("Abs Dev = %5.3f^{#circ} ",AbsDev_kp1[s] ));
		cphi_kp1->cd(s+1);
		mytex->SetTextSize(0.09); 
		mytex->SetTextColor(4);
		mytex->Draw("SAME");
		
		mytex2=new TLatex(-20, 18,Form("Avg Dev = %5.3f^{#circ} ",AvgDev_kp1[s] ));
		mytex2->SetTextSize(0.09); 
		mytex2->SetTextColor(3);
		mytex2->Draw("SAME");
	}

	cphi_kp1->Print("~/Desktop/PhiDev_Loose_kp1.png");

}



Kp2Dev()
{

	TCut kp2_seccut[Ns];
	kp2_seccut[0] = "kp2sector == 1";
	kp2_seccut[1] = "kp2sector == 2";
	kp2_seccut[2] = "kp2sector == 3";
	kp2_seccut[3] = "kp2sector == 4";
	kp2_seccut[4] = "kp2sector == 5";
	kp2_seccut[5] = "kp2sector == 6";

	
	gStyle->SetOptStat(1);



	TCanvas *cphi_kp2;
	cphi_kp2 = new TCanvas("cphi_kp2_","cphi_kp2",1000,800);
	cphi_kp2->Divide(2,3);

	
	TH1F *hDataphidiff_kp2[Ns];
	TH1F *hMCphidiff_kp2[Ns];

	
	float temp1 = mytData->GetEntries();
	float temp2 = mytMC->GetEntries();
	float normfac = temp1/temp2;



	Float_t Data_kp2[Ns] = {0};
	Float_t MC_kp2[Ns] = {0};
	Float_t TotalAbsDev_kp2[Ns] = {0};
	Float_t TotalDev_kp2[Ns] = {0};
	Float_t Moment_kp2[Ns] = {0};
	Float_t StanDev_kp2[Ns] = {0};
	Float_t AbsDev_kp2[Ns] = {0};
	Float_t AvgDev_kp2[Ns] = {0};
	Float_t counter[Ns] = {0};
	for (int s=0; s<Ns; s++)
	{
		cphi_kp2->cd(s+1);
		hDataphidiff_kp2[s] = new TH1F(Form("hDataphidiff_kp2_s%i",s),"",60,-30,30);
		hDataphidiff_kp2[s]->GetXaxis()->SetTitle("#phi (k^{+}_{slow})");
		hDataphidiff_kp2[s]->GetYaxis()->SetTitle(Form("sector_%i",s+1));
		mytData->Draw(Form("kp2phidiff>>hDataphidiff_kp2_s%i",s),kp2_seccut[s]);
		
		hMCphidiff_kp2[s] = new TH1F(Form("hMCphidiff_kp2_s%i",s),"",60,-30,30);
		hMCphidiff_kp2[s]->GetXaxis()->SetTitle("#phi (k^{+}_{slow})");
		hMCphidiff_kp2[s]->GetYaxis()->SetTitle(Form("sector_%i",s+1)); 
		mytMC->Draw(Form("kp2phidiff>>hMCphidiff_kp2_s%i",s),kp2_seccut[s]);
		hMCphidiff_kp2[s]->SetLineColor(2);

		hMCphidiff_kp2[s]->Add(hMCphidiff_kp2[s], normfac - 1);
		hDataphidiff_kp2[s]->Draw("E");
		hMCphidiff_kp2[s]->Draw("SAME");
		
		
		for (int b=0; b<60; b++)
		{
			if ( (hDataphidiff_kp2[s]->GetBinContent(b) != 0) || (hMCphidiff_kp2[s]->GetBinContent(b) !=0 ) ) //only NOT satisfied when mc AND data hists are zero in that bin
			{
				counter[s] += 1;
				Data_kp2[s] = hDataphidiff_kp2[s]->GetBinContent(b);
				MC_kp2[s] = hMCphidiff_kp2[s]->GetBinContent(b);
				TotalAbsDev_kp2[s] += TMath::Abs(Data_kp2[s] - MC_kp2[s]);
				TotalDev_kp2[s] += (Data_kp2[s] - MC_kp2[s]);
				Moment_kp2[s] += (Data_kp2[s] - MC_kp2[s])*(Data_kp2[s] - MC_kp2[s]);

				cout << " for bin " <<b <<" bin content for Data is " <<	Data_kp2[s] <<endl;
				cout << " for bin " <<b <<" bin content for MC is " << MC_kp2[s] <<endl;
				cout << " for bin " <<b <<" bin difference is " << TotalAbsDev_kp2[s] <<endl<<endl;
			}
		}
	}

	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int s=0; s<Ns; s++)
	{
		StanDev_kp2[s] = sqrt( (1/(counter[s] - 1))*Moment_kp2[s] );
		AbsDev_kp2[s] = TotalAbsDev_kp2[s]/counter[s];
		AvgDev_kp2[s] = TotalDev_kp2[s]/counter[s];
		cout << "total devation for sector " << s+1 <<" = " << TotalAbsDev_kp2[s] << "  and number of bins was  " << counter[s] <<endl;
		cout << "absolute devation for sector " << s+1 <<" = " << AbsDev_kp2[s]  <<endl;
		cout << "average devation for sector " << s+1 <<" = " << AvgDev_kp2[s]  <<endl;
		cout << "standard devation for sector " << s+1 <<" = " << StanDev_kp2[s] <<endl<<endl;
		
		
		mytex=new TLatex(-20, 23,Form("Abs Dev = %5.3f^{#circ} ",AbsDev_kp2[s] ));
		cphi_kp2->cd(s+1);
		mytex->SetTextSize(0.09); 
		mytex->SetTextColor(4);
		mytex->Draw("SAME");
		
		mytex2=new TLatex(-20, 18,Form("Avg Dev = %5.3f^{#circ} ",AvgDev_kp2[s] ));
		mytex2->SetTextSize(0.09); 
		mytex2->SetTextColor(3);
		mytex2->Draw("SAME");
	}

	cphi_kp2->Print("~/Desktop/PhiDev_Loose_kp2.png");

}



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
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
}