

void ppippim_fiducial2()
{
	StyleUp();
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v01-partial_Phi.root");  
	TTree *tdata = (TTree*)fdata->Get("v01");
	

	const int Np = 1;  //number of momentum bins	
	const int Nt = 1;  //number of theta bins	
	const int Ns = 6;

	TCut pip_ptcut[Np][Nt];
	pip_ptcut[0][0] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.000000 && piplabtheta < 0.615050 )";
/*
	pip_ptcut[0][1] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.615050 && piplabtheta < 0.813250 )";
	pip_ptcut[0][2] = "(ppip > 0.000000 && ppip < 0.456150 )&&(piplabtheta > 0.813250 && piplabtheta < 1.000000 )";
	pip_ptcut[1][0] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.000000 && piplabtheta < 0.775150 )";
	pip_ptcut[1][1] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.775150 && piplabtheta < 0.903350 )";
	pip_ptcut[1][2] = "(ppip > 0.456150 && ppip < 0.803850 )&&(piplabtheta > 0.903350 && piplabtheta < 1.000000 )";
	pip_ptcut[2][0] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.000000 && piplabtheta < 0.906250 )";
	pip_ptcut[2][1] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.906250 && piplabtheta < 0.961650 )";
	pip_ptcut[2][2] = "(ppip > 0.803850 && ppip < 3.000000 )&&(piplabtheta > 0.961650 && piplabtheta < 1.000000 )";
*/	

	TCut pip_seccut[Ns];
	pip_seccut[0] = "pipsector == 1";
	pip_seccut[1] = "pipsector == 2";
	pip_seccut[2] = "pipsector == 3";
	pip_seccut[3] = "pipsector == 4";
	pip_seccut[4] = "pipsector == 5";
	pip_seccut[5] = "pipsector == 6";
		
	TH1F *hphiclas = new TH1F("hphiclas","",100,-30,330);
	TH1F *hphidifftest = new TH1F("hphidifftest","",100,-30,30);
	tdata->Draw("pipphiclas>>hphiclas",pip_seccut[4]&&pip_ptcut[0][0]);
	
	
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
				hpipphidiff[p][t][s]->GetYaxis()->SetTitle(Form("sector_%i pt-slice_%i%i ",s+1,p,t)); 
				tdata->Draw(Form("pipphidiff>>hpipphidiff-p%i-t%i-s%i",p,t,s),pip_ptcut[p][t]&&pip_seccut[s]);
				fit[p][t][s] = new TF1(Form("fit%i%i%i",p,t,s),"pol0",fitlow,fithigh);
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
				//cout << "Fid_Cut50["<<p<<"]["<<t<<"]["<<s<<"] = \" "<< String_Fid_Cut50[p][t][s] <<" \" ;" <<endl;
			}
		}
	}

	
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
	gStyle->SetOptStat(0);
}
