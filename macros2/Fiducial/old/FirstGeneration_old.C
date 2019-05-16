

void FirstGeneration_old()
{
	
	
	const int Np = 6;  //number of momentum bins	
	const int Nt = 6;  //number of theta bins	
	const int Ns = 6;

	
	StyleUp();
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v01-partial_Phi.root");  
	TTree *tdata = (TTree*)fdata->Get("v01");	
	//New File of hists
	TFile* fHistos = new TFile(Form("./hists/CutHists-%i-%ibins.root",Np,Nt),"RECREATE");
	

	TCut pip_ptcut[Np][Nt];
	if (Np == 3 && Nt == 3){
		pip_ptcut[0][0] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )";
		pip_ptcut[0][1] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )";
		pip_ptcut[0][2] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )";
		pip_ptcut[1][0] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )";
		pip_ptcut[1][1] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )";
		pip_ptcut[1][2] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )";
		pip_ptcut[2][0] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )";
		pip_ptcut[2][1] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )";
		pip_ptcut[2][2] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )";
	}
	if (Np == 6 && Nt == 6){
		pip_ptcut[0][0] =  " (ppip > 0.000000 && ppip < 0.317250 )&&(piplabtheta > 0.000000 && piplabtheta < 0.437150 ) " ; 
		pip_ptcut[0][1] =  " (ppip > 0.000000 && ppip < 0.317250 )&&(piplabtheta > 0.437150 && piplabtheta < 0.567150 ) " ; 
		pip_ptcut[0][2] =  " (ppip > 0.000000 && ppip < 0.317250 )&&(piplabtheta > 0.567150 && piplabtheta < 0.670650 ) " ; 
		pip_ptcut[0][3] =  " (ppip > 0.000000 && ppip < 0.317250 )&&(piplabtheta > 0.670650 && piplabtheta < 0.769950 ) " ; 
		pip_ptcut[0][4] =  " (ppip > 0.000000 && ppip < 0.317250 )&&(piplabtheta > 0.769950 && piplabtheta < 0.868550 ) " ; 
		pip_ptcut[0][5] =  " (ppip > 0.000000 && ppip < 0.317250 )&&(piplabtheta > 0.868550 && piplabtheta < 1.000000 ) " ; 
		pip_ptcut[1][0] =  " (ppip > 0.317250 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.533050 ) " ; 
		pip_ptcut[1][1] =  " (ppip > 0.317250 && ppip < 0.456150 )&&(piplabtheta > 0.533050 && piplabtheta < 0.667650 ) " ; 
		pip_ptcut[1][2] =  " (ppip > 0.317250 && ppip < 0.456150 )&&(piplabtheta > 0.667650 && piplabtheta < 0.764850 ) " ; 
		pip_ptcut[1][3] =  " (ppip > 0.317250 && ppip < 0.456150 )&&(piplabtheta > 0.764850 && piplabtheta < 0.847850 ) " ; 
		pip_ptcut[1][4] =  " (ppip > 0.317250 && ppip < 0.456150 )&&(piplabtheta > 0.847850 && piplabtheta < 0.922150 ) " ; 
		pip_ptcut[1][5] =  " (ppip > 0.317250 && ppip < 0.456150 )&&(piplabtheta > 0.922150 && piplabtheta < 1.000000 ) " ; 
		pip_ptcut[2][0] =  " (ppip > 0.456150 && ppip < 0.610350 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615450 ) " ; 
		pip_ptcut[2][1] =  " (ppip > 0.456150 && ppip < 0.610350 )&&(piplabtheta > 0.615450 && piplabtheta < 0.738950 ) " ; 
		pip_ptcut[2][2] =  " (ppip > 0.456150 && ppip < 0.610350 )&&(piplabtheta > 0.738950 && piplabtheta < 0.822550 ) " ; 
		pip_ptcut[2][3] =  " (ppip > 0.456150 && ppip < 0.610350 )&&(piplabtheta > 0.822550 && piplabtheta < 0.889550 ) " ; 
		pip_ptcut[2][4] =  " (ppip > 0.456150 && ppip < 0.610350 )&&(piplabtheta > 0.889550 && piplabtheta < 0.941050 ) " ; 
		pip_ptcut[2][5] =  " (ppip > 0.456150 && ppip < 0.610350 )&&(piplabtheta > 0.941050 && piplabtheta < 1.000000 ) " ; 
		pip_ptcut[3][0] =  " (ppip > 0.610350 && ppip < 0.803550 )&&(piplabtheta > 0.000000 && piplabtheta < 0.711350 ) " ; 
		pip_ptcut[3][1] =  " (ppip > 0.610350 && ppip < 0.803550 )&&(piplabtheta > 0.711350 && piplabtheta < 0.806050 ) " ; 
		pip_ptcut[3][2] =  " (ppip > 0.610350 && ppip < 0.803550 )&&(piplabtheta > 0.806050 && piplabtheta < 0.868350 ) " ; 
		pip_ptcut[3][3] =  " (ppip > 0.610350 && ppip < 0.803550 )&&(piplabtheta > 0.868350 && piplabtheta < 0.915550 ) " ; 
		pip_ptcut[3][4] =  " (ppip > 0.610350 && ppip < 0.803550 )&&(piplabtheta > 0.915550 && piplabtheta < 0.954950 ) " ; 
		pip_ptcut[3][5] =  " (ppip > 0.610350 && ppip < 0.803550 )&&(piplabtheta > 0.954950 && piplabtheta < 1.000000 ) " ; 
		pip_ptcut[4][0] =  " (ppip > 0.803550 && ppip < 1.106250 )&&(piplabtheta > 0.000000 && piplabtheta < 0.807450 ) " ; 
		pip_ptcut[4][1] =  " (ppip > 0.803550 && ppip < 1.106250 )&&(piplabtheta > 0.807450 && piplabtheta < 0.870550 ) " ; 
		pip_ptcut[4][2] =  " (ppip > 0.803550 && ppip < 1.106250 )&&(piplabtheta > 0.870550 && piplabtheta < 0.910450 ) " ; 
		pip_ptcut[4][3] =  " (ppip > 0.803550 && ppip < 1.106250 )&&(piplabtheta > 0.910450 && piplabtheta < 0.942150 ) " ; 
		pip_ptcut[4][4] =  " (ppip > 0.803550 && ppip < 1.106250 )&&(piplabtheta > 0.942150 && piplabtheta < 0.968150 ) " ; 
		pip_ptcut[4][5] =  " (ppip > 0.803550 && ppip < 1.106250 )&&(piplabtheta > 0.968150 && piplabtheta < 1.000000 ) " ; 
		pip_ptcut[5][0] =  " (ppip > 1.106250 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.899650 ) " ; 
		pip_ptcut[5][1] =  " (ppip > 1.106250 && ppip < 3.000000 )&&(piplabtheta > 0.899650 && piplabtheta < 0.935850 ) " ; 
		pip_ptcut[5][2] =  " (ppip > 1.106250 && ppip < 3.000000 )&&(piplabtheta > 0.935850 && piplabtheta < 0.956850 ) " ; 
		pip_ptcut[5][3] =  " (ppip > 1.106250 && ppip < 3.000000 )&&(piplabtheta > 0.956850 && piplabtheta < 0.971150 ) " ; 
		pip_ptcut[5][4] =  " (ppip > 1.106250 && ppip < 3.000000 )&&(piplabtheta > 0.971150 && piplabtheta < 0.982150 ) " ; 
		pip_ptcut[5][5] =  " (ppip > 1.106250 && ppip < 3.000000 )&&(piplabtheta > 0.982150 && piplabtheta < 1.000000 ) " ;
	}
	
	

	TCut pip_seccut[Ns];
	pip_seccut[0] = "pipsector == 1";
	pip_seccut[1] = "pipsector == 2";
	pip_seccut[2] = "pipsector == 3";
	pip_seccut[3] = "pipsector == 4";
	pip_seccut[4] = "pipsector == 5";
	pip_seccut[5] = "pipsector == 6";
		
	//get bin centers for momentum	
	TCanvas *cpbincenter = new TCanvas("cpbincenter","cpbincenter",1000,800);
	cpbincenter->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter[Np][Nt];
	Double_t pcenter[Np][Nt] = {0};
	Double_t prms[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
			cpbincenter->cd(cancount);
			hpcenter[p][t] = new TH1F(Form("hpcenter%i_%i",p,t),"",200,0,4);
			tdata->Draw(Form("ppip>>hpcenter%i_%i",p,t),pip_ptcut[p][t]);
			hpcenter[p][t]->GetXaxis()->SetTitle("pip momentum (GeV)");
			hpcenter[p][t]->Write();
			pcenter[p][t] =  hpcenter[p][t]->GetMean();
			prms[p][t] =  hpcenter[p][t]->GetRMS();
			cout <<"momentum center and rms = " << pcenter[p][t] << "  and  "<< prms[p][t] <<endl;
			cancount += 1;
		}
	}
	
	
	//get bin centers for theta	
	TCanvas *ctbincenter = new TCanvas("ctbincenter","ctbincenter",1000,800);
	ctbincenter->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *htcenter[Np][Nt];
	Double_t tcenter[Np][Nt] = {0};
	Double_t trms[Np][Nt] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
			ctbincenter->cd(cancount);
			htcenter[p][t] = new TH1F(Form("htcenter%i_%i",p,t),"",200,0,180);
			tdata->Draw(Form("(180/3.141592)*acos(plabtheta)>>htcenter%i_%i",p,t),pip_ptcut[p][t]);
			htcenter[p][t]->GetXaxis()->SetTitle("pip #theta (deg)");
			htcenter[p][t]->Write();
			tcenter[p][t] =  htcenter[p][t]->GetMean();
			trms[p][t] =  htcenter[p][t]->GetRMS();
			cout <<"theta center and rms = " << tcenter[p][t] << "  and  "<< trms[p][t] <<endl;
			cancount += 1;
		}
	}


	
	
	TCanvas *cpipphi[Np][Nt];
	TH1F *hpipphidiff[Np][Nt][Ns];
	
	
	//fitt
	Double_t fitlow  = -15;	
	Double_t fithigh = 15;
	Double_t center = 0;
	TF1 *fit[Np][Nt][Ns];
	Double_t fitheight[Np][Nt][Ns] = {0};
	
	Double_t pc50[Np][Nt][Ns] = {0};
	Int_t BinLow50[Np][Nt][Ns] = {0};
	Int_t BinHigh50[Np][Nt][Ns] = {0};
	Double_t ValLow50[Np][Nt][Ns] = {0};
	Double_t ValHigh50[Np][Nt][Ns] = {0};
	
	Double_t clasValLow50[Np][Nt][Ns] = {0};
	Double_t clasValHigh50[Np][Nt][Ns] = {0};
	
	TLine *LineLow50[Np][Nt][Ns] = {0};
	TLine *LineHigh50[Np][Nt][Ns] = {0};
	
	Double_t pc80[Np][Nt][Ns] = {0};
	Int_t BinLow80[Np][Nt][Ns] = {0};
	Int_t BinHigh80[Np][Nt][Ns] = {0};
	Double_t ValLow80[Np][Nt][Ns] = {0};
	Double_t ValHigh80[Np][Nt][Ns] = {0};
	TLine *LineLow80[Np][Nt][Ns];
	TLine *LineHigh80[Np][Nt][Ns];
	
	TCut Fid_Cut50[Np][Nt][Ns];
	TString String_Fid_Cut50[Np][Nt][Ns];


	TCut Cut50[Np][Nt][Ns];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{
			cpipphi[p][t] = new TCanvas(Form("cpipphi-p%i-t%i",p,t),Form("cpipphi-p%i-t%i",p,t),1000,800);
			cpipphi[p][t]->Divide(2,3);
			for (int s=0; s<Ns; s++)
			{
				cout <<"test 0"<<endl;
				cpipphi[p][t]->cd(s+1);
				hpipphidiff[p][t][s] = new TH1F(Form("hpipphidiff-p%i-t%i-s%i",p,t,s),"",100,-30,30);
				hpipphidiff[p][t][s]->GetXaxis()->SetTitle("#phi (#pi +)");
				hpipphidiff[p][t][s]->GetYaxis()->SetTitle(Form("sector_%i pt-slice_%i_%i ",s+1,p,t)); 
				tdata->Draw(Form("pipphidiff>>hpipphidiff-p%i-t%i-s%i",p,t,s),pip_ptcut[p][t]&&pip_seccut[s]);
				fit[p][t][s] = new TF1(Form("fit%i_%i_%i",p,t,s),"pol0",fitlow,fithigh);
				hpipphidiff[p][t][s]->Fit(fit[p][t][s],"R");
				fitheight[p][t][s] = fit[p][t][s]->GetParameter(0);
				cout <<"test 1"<<endl;
				//80% cuts
				pc80[p][t][s] = 0.8*fitheight[p][t][s];
				BinLow80[p][t][s] = hpipphidiff[p][t][s]->FindFirstBinAbove(pc80[p][t][s],1);
				BinHigh80[p][t][s] = hpipphidiff[p][t][s]->FindLastBinAbove(pc80[p][t][s],1);
				ValLow80[p][t][s] = hpipphidiff[p][t][s]->GetBinCenter(BinLow80[p][t][s]);
				ValHigh80[p][t][s] = hpipphidiff[p][t][s]->GetBinCenter(BinHigh80[p][t][s]);	
				LineLow80[p][t][s] = new TLine(ValLow80[p][t][s],0,ValLow80[p][t][s],pc80[p][t][s]);
				LineHigh80[p][t][s] = new TLine(ValHigh80[p][t][s],0,ValHigh80[p][t][s],pc80[p][t][s]);
				LineLow80[p][t][s]->SetLineColor(2);
				LineHigh80[p][t][s]->SetLineColor(2);
				LineLow80[p][t][s]->Draw();
				LineHigh80[p][t][s]->Draw();

				//50% cuts
				pc50[p][t][s] = 0.5*fitheight[p][t][s];
				BinLow50[p][t][s] = hpipphidiff[p][t][s]->FindFirstBinAbove(pc50[p][t][s],1);
				BinHigh50[p][t][s] = hpipphidiff[p][t][s]->FindLastBinAbove(pc50[p][t][s],1);
				ValLow50[p][t][s] = hpipphidiff[p][t][s]->GetBinCenter(BinLow50[p][t][s]);
				ValHigh50[p][t][s] = hpipphidiff[p][t][s]->GetBinCenter(BinHigh50[p][t][s]);	
				LineLow50[p][t][s] = new TLine(ValLow50[p][t][s],0,ValLow50[p][t][s],pc50[p][t][s]);
				LineHigh50[p][t][s] = new TLine(ValHigh50[p][t][s],0,ValHigh50[p][t][s],pc50[p][t][s]);
				LineLow50[p][t][s]->SetLineColor(3);
				LineHigh50[p][t][s]->SetLineColor(3);
				LineLow50[p][t][s]->Draw();
				LineHigh50[p][t][s]->Draw();
				
				//clasValLow50[p][t][s] = ValLow50[p][t][s] + (60*s);
				//clasValHigh50[p][t][s] = ValHigh50[p][t][s] + (60*s);
				Cut50[p][t][s] = Form("pipphidiff > %f && pipphidiff < %f",ValLow50[p][t][s],ValHigh50[p][t][s]);
				
				Fid_Cut50[p][t][s] = Cut50[p][t][s] && pip_ptcut[p][t] && pip_seccut[s];
				String_Fid_Cut50[p][t][s] = Fid_Cut50[p][t][s];
				//cout << "cut = " << String_Fid_Cut50[p][t][s] << endl;
			}
		}
	}
	
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Np; t++)
		{
			for (int s=0; s<Ns; s++)
			{
				cout << "Fid_Cut50["<<p<<"]["<<t<<"]["<<s<<"] = \" "<< String_Fid_Cut50[p][t][s] <<" \" ;" <<endl;
			}
		}
	}

	
	//get the high and low cut values in a form thats plotable
	Double_t H50[Ns][Np][Nt] = {0};
	Double_t L50[Ns][Np][Nt] = {0};
	Float_t ThetaCenter[Nt][Np];
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Np; t++)
		{
			ThetaCenter[t][p] = tcenter[p][t];
			for (int s=0; s<Ns; s++)
			{
				H50[s][p][t] = ValHigh50[p][t][s];
				L50[s][p][t] = ValLow50[p][t][s];
			}
		}
	}
	
	
	//1d hists of lower cut and theta in sclices of p
	TCanvas *cL50[Np];
	TGraphErrors *grL50[Np][Ns];
	TCanvas *cH50[Np];
	TGraphErrors *grH50[Np][Ns];
	for (int p=0; p<Np; p++)
	{
		cL50[p] = new TCanvas(Form("cL50%i",t),Form("cL50%i",t),1000,800);
		cL50[p]->Divide(3,2);
		cH50[p] = new TCanvas(Form("cH50%i",t),Form("cH50%i",t),1000,800);
		cH50[p]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			grL50[p][s] = new TGraphErrors(Nt,tcenter[p],L50[s][p],0,0);
			grL50[p][s]->SetMarkerSize(1.5);
			grL50[p][s]->SetMarkerColor(2);
			grL50[p][s]->SetMarkerStyle(22);
			grL50[p][s]->GetXaxis()->SetTitle("cos(#theta)");
			grL50[p][s]->GetYaxis()->SetTitle("Low Cut (#delta#phi)");
			grL50[p][s]->SetName(Form("grL50_p%i-sector%i",p,s+1));
			cL50[p]->cd(s+1);
			grL50[p][s]->Draw("AP");
			grL50[p][s]->Write();

			
			
			grH50[p][s] = new TGraphErrors(Nt,tcenter[p],H50[s][p],0,0);
			grH50[p][s]->SetMarkerSize(1.5);
			grH50[p][s]->SetMarkerColor(2);
			grH50[p][s]->SetMarkerStyle(22);
			grH50[p][s]->GetXaxis()->SetTitle("cos(#theta)");
			grH50[p][s]->GetYaxis()->SetTitle("High Cut (#delta#phi)");
			grH50[p][s]->SetName(Form("grH50_p%i-sector%i",p,s+1));
			cH50[p]->cd(s+1);
			grH50[p][s]->Draw("AP");
			grH50[p][s]->Write();

			
		}
	}
	

	/*2d hists of lower cut
	TCanvas *cL50 = new TCanvas("cL50","cL50",1000,800);
	cL50->Divide(3,2);
	TH2F *hL50[Ns];
	for (int s=0; s<Ns; s++)
	{
		hL50[s] = new TH2F(Form("hL50%i",s),"",100,0,3,100,0,1);
		for (int p=0; p<Np; p++)
		{
			for (int t=0; t<Np; t++)
			{
					hL50[s]->Fill(pcenter[p][t], tcenter[p][t],L50[s][p][t]);
					
			}
		}
		cL50->cd(s+1);
		hL50[s]->Write();
		hL50[s]->Draw("colz");
	}
	*/

	/*
	//1d hists of lower cut and p
	TCanvas *cL50p[Nt];
	TH1F *hL50p[Nt][Ns];
	for (int t=0; t<Nt; t++)
	{
		cL50p[t] = new TCanvas(Form("cL50p%i",t),Form("cL50p%i",t),1000,800);
		cL50p[t]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			hL50p[t][s] = new TH1F(Form("hL50p%i_%i",t,s),"",600,0,3);
			for (int p=0; p<Np; p++)
			{
				hL50p[t][s]->Fill(pcenter[p][t], L50[s][p][t]);
			}
			cL50p[t]->cd(s+1);
			hL50p[t][s]->Draw();
			hL50p[t][s]->Write();
		}
	}

	//1d hists of higher cut and p
	TCanvas *cH50p[Nt];
	TH1F *hH50p[Nt][Ns];
	for (int t=0; t<Np; t++)
	{
		cH50p[t] = new TCanvas(Form("cH50p%i",t),Form("cH50p%i",t),1000,800);
		cH50p[t]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			hH50p[t][s] = new TH1F(Form("hH50p%i_%i",t,s),"",600,0,3);
			for (int p=0; p<Np; p++)
			{
				hH50p[t][s]->Fill(pcenter[p][t], H50[s][p][t]);
			}
			cH50p[t]->cd(s+1);
			hH50p[t][s]->Draw();
			hH50p[t][s]->Write();
		}
	}
	
	
	
	//1d hists of lower cut and theta
	TCanvas *cL50t[Np];
	TH1F *hL50t[Np][Ns];
	for (int p=0; p<Np; p++)
	{
		cL50t[p] = new TCanvas(Form("cL50t%i",t),Form("cL50t%i",t),1000,800);
		cL50t[p]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			hL50t[p][s] = new TH1F(Form("hL50t%i_%i",p,s),"",300,0,1);
			for (int t=0; t<Nt; t++)
			{
				hL50t[p][s]->Fill(tcenter[p][t], L50[s][p][t]);
			}
			cL50t[p]->cd(s+1);
			hL50t[p][s]->Draw();
			hL50t[p][s]->Write();
		}
	}


	//1d hists of uper cut and theta
	TCanvas *cH50t[Np];
	TH1F *hH50t[Np][Ns];
	for (int p=0; p<Np; p++)
	{
		cH50t[p] = new TCanvas(Form("cH50t%i",t),Form("cH50t%i",t),1000,800);
		cH50t[p]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			hH50t[p][s] = new TH1F(Form("hH50t%i_%i",p,s),"",300,0,1);
			for (int t=0; t<Nt; t++)
			{
				hH50t[p][s]->Fill(tcenter[p][t], H50[s][p][t]);
			}
			cH50t[p]->cd(s+1);
			hH50t[p][s]->Draw();
			hH50t[p][s]->Write();
		}
	}
	
	*/
	

//	exit(1);

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
