



void ppippim_fiducial()
{
	StyleUp();
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v01-partial.root");  
	TTree *tdata = (TTree*)fdata->Get("v01");
	
	//derive equi-spaced cuts in momentum
	const int Np = 2;  //number of momentum bins	
	float pnumber = Np;
	float pstep = 0.2;
	float pmin = 0.0;
	float pmax = 2.0;
	float pstep = (pmax - pmin)/pnumber;
	float plowcut[Np];
	float phighcut[Np];
	TCut ppipBin[Np],ppimBin[Np];	
	for (int p=0; p<Np; p++)
	{
		plowcut[p] = pmin + pstep*p;
		phighcut[p] = pmin + pstep*(p+1);
		cout << "plow = " <<plowcut[p]<< "   phigh =" <<phighcut[p]<<endl;
		ppipBin[p] = Form("ppip >= %f && ppip <= %f",plowcut[p],phighcut[p]);
		ppimBin[p] = Form("ppim >= %f && ppim <= %f",plowcut[p],phighcut[p]);
	}

	
	//derive equi-spaced cuts theta
	const int Nt = 2;  //number of theta bins	
	float tnumber = Nt;
	float tstep = 0.2;
	float tmin = 0.4;
	float tmax = 1.0;
	float tstep = (tmax - tmin)/tnumber;
	float tlowcut[Nt];
	float thighcut[Nt];
	TCut tpipBin[Nt],tpimBin[Nt];
	for (int t=0; t<Nt; t++)
	{
		tlowcut[t] = tmin + tstep*t;
		thighcut[t] = tmin + tstep*(t+1);
		cout << "tlow = " <<tlowcut[t]<<  "   thigh =" <<thighcut[t]<<endl;
		tpipBin[t] = Form("piplabtheta >= %f && piplabtheta <= %f",tlowcut[t],thighcut[t]);
		tpimBin[t] = Form("pimlabtheta >= %f && pimlabtheta <= %f",tlowcut[t],thighcut[t]);
	}
	

	//derive phi cuts for sector divisions	
	const int Ns = 6;  //number of sectors in clas
	float snumber = Ns;
	float sstep = 0.2;
	float smin = -1.0;
	float smax = 1.0;
	float sstep = (smax - smin)/snumber;
	float slowcut[Ns];
	float shighcut[Ns];
	float center[Ns];
	float fitwidth[Ns];
	float fithigh[Ns];
	float fitlow[Ns];
	TCut spipBin[Ns],spimBin[Ns];
	TH1F *hpipphi[Np][Nt][Ns];
	TH1F *hpimphi[Np][Nt][Ns];
	for (int s=0; s<Ns; s++)
	{
		slowcut[s] = smin + sstep*(s+0.5);
		shighcut[s] = smin + sstep*(s+1.5);
		center[s] = (slowcut[s] + shighcut[s])/2;
		fitwidth[s] = (shighcut[s] - slowcut[s])/(2*3);
		fithigh[s] = center[s] + fitwidth[s];
		fitlow[s] = center[s] - fitwidth[s];
		cout << "slow = " <<slowcut[s]<<"  center = " << center[s] << "  shigh =" <<shighcut[s]<< "  fitlow = " <<fitlow[s] << "  fithigh = " <<fithigh[s]  <<endl;
		if (s < (Ns - 1) )
		{
			spipBin[s] = Form("piplabphi >= %f && piplabphi <= %f",slowcut[s],shighcut[s]);
			spimBin[s] = Form("pimlabphi >= %f && pimlabphi <= %f",slowcut[s],shighcut[s]);
			for (int p=0; p<Np; p++)
			{
				for (int t=0; t<Nt; t++)
				{
					hpipphi[p][t][s] = new TH1F(Form("hpipphi-p%i-t%i-s%i",p,t,s),"",100,slowcut[s],shighcut[s]);
					hpipphi[p][t][s]->GetXaxis()->SetTitle("#phi (#pi +)");
					
					hpimphi[p][t][s] = new TH1F(Form("hpimphi-p%i-t%i-s%i",p,t,s),"",100,slowcut[s],shighcut[s]);
					hpimphi[p][t][s]->GetXaxis()->SetTitle("#phi (#pi -)");
				}
			}
		}
		else
		{
			spipBin[s] = Form("piplabphi <= %f || piplabphi >= %f",slowcut[0],shighcut[4]);
			spimBin[s] = Form("pimlabphi <= %f || pimlabphi >= %f",slowcut[0],shighcut[4]);
			for (int p=0; p<Np; p++)
			{
				for (int t=0; t<Nt; t++)
				{
					hpipphi[p][t][s] = new TH1F(Form("hpipphi-p%i-t%i-s%i",p,t,s),"",600,-1,1);
					hpipphi[p][t][s]->GetXaxis()->SetTitle("#phi (#pi +)");
					
					hpimphi[p][t][s] = new TH1F(Form("hpimphi-p%i-t%i-s%i",p,t,s),"",600,-1,1);
					hpimphi[p][t][s]->GetXaxis()->SetTitle("#phi (#pi -)");
				}
			}
		}
	}
	

				

	
	
	
	//*///
	TCanvas *cpipphi[Np][Nt];
	//TCanvas *cpimphi[Np][Nt];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			cpipphi[p][t] = new TCanvas(Form("cpipphi-p%i-t%i",p,t),Form("cpipphi-p%i-t%i",p,t),1000,800);
			cpipphi[p][t]->Divide(2,3);
			//cpimphi[p][t] = new TCanvas(Form("cpimphi-p%i-t%i",p,t),Form("cpimphi-p%i-t%i",p,t),1000,800);
			//cpimphi[p][t]->Divide(2,3);
			for (int s=0; s<Ns; s++)
			{
				cpipphi[p][t]->cd(s+1);
				tdata->Draw(Form("piplabphi>>hpipphi-p%i-t%i-s%i",p,t,s),ppipBin[p]&&tpipBin[t]&&spipBin[s]);
				
				//cpimphi[p][t]->cd(s+1);
				//tdata->Draw(Form("pimlabphi>>hpimphi-p%i-t%i-s%i",p,t,s),ppimBin[p]&&tpimBin[t]&&spimBin[s]);
			
			}
		}
	}
	
	
	
	//fitt
	TF1 *fit[Np][Nt][Ns];
	Double_t fitheight[Np][Nt][Ns];
	
	Double_t pc50[Np][Nt][Ns];
	Int_t BinLow50[Np][Nt][Ns];
	Int_t BinHigh50[Np][Nt][Ns];
	Double_t ValLow50[Np][Nt][Ns];
	Double_t ValHigh50[Np][Nt][Ns];
	TLine *LineLow50[Np][Nt][Ns];
	TLine *LineHigh50[Np][Nt][Ns];
	
	Double_t pc80[Np][Nt][Ns];
	Int_t BinLow80[Np][Nt][Ns];
	Int_t BinHigh80[Np][Nt][Ns];
	Double_t ValLow80[Np][Nt][Ns];
	Double_t ValHigh80[Np][Nt][Ns];
	TLine *LineLow80[Np][Nt][Ns];
	TLine *LineHigh80[Np][Nt][Ns];
	
	
		
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				cpipphi[p][t]->cd(s+1);
				fit[p][t][s] = new TF1(Form("fit%i%i%i",p,t,s),"pol0",fitlow[s],fithigh[s]);
				hpipphi[p][t][s]->Fit(fit[p][t][s],"R");
				fitheight[p][t][s] = fit[p][t][s]->GetParameter(0);
				//80% cuts
				pc80[p][t][s] = 0.8*fitheight[p][t][s];
				BinLow80[p][t][s] = hpipphi[p][t][s]->FindFirstBinAbove(pc80[p][t][s],1);
				BinHigh80[p][t][s] = hpipphi[p][t][s]->FindLastBinAbove(pc80[p][t][s],1);
				ValLow80[p][t][s] = hpipphi[p][t][s]->GetBinCenter(BinLow80[p][t][s]);
				ValHigh80[p][t][s] = hpipphi[p][t][s]->GetBinCenter(BinHigh80[p][t][s]);	
				LineLow80[p][t][s] = new TLine(ValLow80[p][t][s],0,ValLow80[p][t][s],pc80[p][t][s]);
				LineHigh80[p][t][s] = new TLine(ValHigh80[p][t][s],0,ValHigh80[p][t][s],pc80[p][t][s]);
				LineLow80[p][t][s]->SetLineColor(2);
				LineHigh80[p][t][s]->SetLineColor(2);
				LineLow80[p][t][s]->Draw();
				LineHigh80[p][t][s]->Draw();
				
				//50% cuts
				pc50[p][t][s] = 0.5*fitheight[p][t][s];
				BinLow50[p][t][s] = hpipphi[p][t][s]->FindFirstBinAbove(pc50[p][t][s],1);
				BinHigh50[p][t][s] = hpipphi[p][t][s]->FindLastBinAbove(pc50[p][t][s],1);
				ValLow50[p][t][s] = hpipphi[p][t][s]->GetBinCenter(BinLow50[p][t][s]);
				ValHigh50[p][t][s] = hpipphi[p][t][s]->GetBinCenter(BinHigh50[p][t][s]);	
				LineLow50[p][t][s] = new TLine(ValLow50[p][t][s],0,ValLow50[p][t][s],pc50[p][t][s]);
				LineHigh50[p][t][s] = new TLine(ValHigh50[p][t][s],0,ValHigh50[p][t][s],pc50[p][t][s]);
				LineLow50[p][t][s]->SetLineColor(3);
				LineHigh50[p][t][s]->SetLineColor(3);
				LineLow50[p][t][s]->Draw();
				LineHigh50[p][t][s]->Draw();
			}
		}
	}
	
	
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				cout << ValLow80[p][t][s] <<"  " << ValHigh80[p][t][s]<<"  " << pc80[p][t][s] <<endl;
			}
		}	
	}
	
	

	
	

	
	
	
	
}

///////////////////////////////////////////////////////////////////////////////

	/*///2d
	TH2F *hpzvpt=new TH2F("hpzvpt","",200,0,0.1,200,-0.1,0.1);
	hpzvpt->GetYaxis()->SetTitle("Pz");
	hpzvpt->GetXaxis()->SetTitle("Pt");
	TH2F *hpzvm=new TH2F("hpzvm","",100,0,0.002,200,-0.1,0.1);
	hpzvm->GetYaxis()->SetTitle("Pz");
	hpzvm->GetXaxis()->SetTitle("mm2");
	TH2F *hptvm=new TH2F("hptvm","",100,0,0.002,200,0,0.1);
	hptvm->GetYaxis()->SetTitle("Pt");
	hptvm->GetXaxis()->SetTitle("mm2");
	
	TCanvas *c2d=new TCanvas("c2d","c2d",1000,800);
	c2d->Divide(2,2);
	c2d->cd(1);
	tdata->Draw("missz : sqrt(missx*missx + missy*missy) >>hpzvpt","","colz");
	c2d->cd(2);
	tdata->Draw("missz : mmppippim*mmppippim >>hpzvm","","colz");
	c2d->cd(3);
	tdata->Draw("sqrt(missx*missx + missy*missy) : mmppippim*mmppippim >>hptvm","","colz");
	c2d->cd(4);
	///*////



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
}







