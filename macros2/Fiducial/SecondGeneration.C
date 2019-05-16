//Purpose: To take in the upper and lower phi cuts and to fit to an exponential function


void SecondGeneration()
{
	StyleUp();
	
	const int Np = 15;  //number of momentum bins	
	const int Nt = 15;  //number of theta bins	
	const int Ns = 6;
	
	
	TFile* fInput = new TFile(Form("./hists/FirstGen-%i-%ibins.root",Np,Nt));
	//output
	TFile* fOutput = new TFile(Form("./hists/SecondGen-%i-%ibins.root",Np,Nt),"RECREATE");


	//*//////////////////////////////////////////////// begin pip calculation ////////////////////////////////////////////////////	
	//read in momentum hists, draw them, get bin centers
	//TCanvas *cpcenter_Contracted_pip = new TCanvas("cpcenter_Contracted_pip","cpcenter_Contracted_pip",1000,800);
	//cpcenter_Contracted_pip->Divide(4,4);
	//TCanvas *cpcenter_pip = new TCanvas("cpcenter_pip","cpcenter_pip",1000,800);
	//cpcenter_pip->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter_pip[Np][Nt];
	TH1F *hpcenter_Contracted_pip[Np];
	Float_t pcenter_pip[Np] = {0};
	Float_t prms_pip[Np] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
			//cpcenter_pip->cd(cancount);
			hpcenter_pip[p][t] = (TH1F*)fInput->Get(Form("hpcenter_pip_p%i_t%i",p,t));
			hpcenter_pip[p][t]->Draw();
			cancount += 1;
		}
		
		hpcenter_Contracted_pip[p] = (TH1F*)hpcenter_pip[p][0]->Clone();
		hpcenter_Contracted_pip[p]->SetName(Form("hpContracted_pip_p%i",p));
		hpcenter_Contracted_pip[p]->SetTitle(Form("hpContracted_pip_p%i",p));
		for (int t=1; t<Nt; t++)
		{ 
			hpcenter_Contracted_pip[p]->Add(hpcenter_pip[p][t],1);
		}
		//cpcenter_Contracted_pip->cd(p+1);
		hpcenter_Contracted_pip[p]->Draw();
		pcenter_pip[p] =  hpcenter_Contracted_pip[p]->GetMean();
		prms_pip[p] =  hpcenter_Contracted_pip[p]->GetRMS();
		cout << "pcenter pip = " <<	pcenter_pip[p] <<endl;
	}


	//set up the canvas and the graphs
	TCanvas *c50_pip[Np];
	//TCanvas *cH50_pip[Np];
	TGraphErrors *grL50_pip[Np][Ns];
	TGraphErrors *grH50_pip[Np][Ns];
	TMultiGraph *mg50_pip[Np][Ns];
	//set up the fits
	TF1 *Lfit = new TF1("Lfit","([1]*(1 - 1/((x - [2])*[1]/[0])))", 5, 90);
	TF1 *Hfit = new TF1("Hfit","([1]*(1 - 1/((x - [2])*[1]/[0])))", 5, 90);
	
	TF1 *newLfit = new TF1("Lfit","[0] - [1]/(x - [2])", 5, 90);
	TF1 *newHfit = new TF1("Hfit","[0] - [1]/(x - [2])", 5, 90);
	
	TF1 *Lfit = newLfit;
	TF1 *Hfit = newHfit;
	
	Lfit->SetParLimits(2, -5, 13); //this is the parameter which loccates the asymtote
	Hfit->SetParLimits(2, -5, 13);
	
	Int_t NumParsL = Lfit->GetNumberFreeParameters();
	Int_t NumParsH = Hfit->GetNumberFreeParameters();
	
	
	//Hfit->SetParLimits(0, 25, 120);
	//Lfit->SetParLimits(0, -120, -25);
	//Hfit->SetParLimits(1, 23, 35);
	//Lfit->SetParLimits(1, -35, -23);
	//Lfit->SetParLimits(2, -3, 10); //this is the parameter which loccates the asymtote
	//Hfit->SetParLimits(2, -3, 10);	
	

	Lfit->SetLineColor(1);
	Hfit->SetLineColor(1);
	const int Ni = NumParsL;
	//setup the variables to store fitting parameters... the order is s then p so it can be plotted in tgraph
	Float_t L50_pip_par[Ni][Ns][Np] = {0};
	Float_t eL50_pip_par[Ni][Ns][Np] = {0};
	Float_t H50_pip_par[Ni][Ns][Np] = {0};
	Float_t eH50_pip_par[Ni][Ns][Np] = {0};
	for (int p=0; p<Np; p++)
	{
		//c50_pip[p] = new TCanvas(Form("c50_pip%i",p),Form("c50_pip%i",p),1000,800);
		//c50_pip[p]->Divide(3,2);				
		for (int s=0; s<Ns; s++)
		{
			//get graphs
			grL50_pip[p][s] = (TGraphErrors*)fInput->Get(Form("grL50_pip_p%i-sector%i",p,s+1));
			grL50_pip[p][s]->Fit("Lfit","Rq");				
			grH50_pip[p][s] = (TGraphErrors*)fInput->Get(Form("grH50_pip_p%i-sector%i",p,s+1));
			grH50_pip[p][s]->SetMarkerColor(3);
			grH50_pip[p][s]->Fit("Hfit","Rq");
			//grH50_pip[p][s]->SetTitle("");
			//grH50_pip[p][s]->SetName("");
			grH50_pip[p][s] = ~TGraphErrors();
			grL50_pip[p][s] = ~TGraphErrors();
			
			//put in multigraph, style and draw
			mg50_pip[p][s] = new TMultiGraph();
			mg50_pip[p][s]->Add(grL50_pip[p][s]);
			mg50_pip[p][s]->Add(grH50_pip[p][s]);
			mg50_pip[p][s]->SetName(Form("pip_p%i-sector%i",p,s+1));
			mg50_pip[p][s]->SetTitle(Form("pip_p%i-sector%i",p,s+1));
			mg50_pip[p][s]->Draw("ap");
			//must set axis names after drawn for some reason
			mg50_pip[p][s]->GetXaxis()->SetTitle("#theta");
			mg50_pip[p][s]->GetYaxis()->SetTitle("#delta#phi");
		 	
			//c50_pip[p]->cd(s+1);
			TCanvas *CAN = new TCanvas("CAN","CAN",1000,800);
			mg50_pip[p][s]->Draw("ap");
			mg50_pip[p][s]->Write();
		
			//CAN->Update();
			CAN->Print(Form("./pics/SecondGen/PhiVsTheta_pip-p%i-sec%i.eps",p,s+1));
			
			//store the fitting parameters 
			for (int i=0; i<Ni; i++)
			{
				L50_pip_par[i][s][p] = Lfit->GetParameter(i);
				eL50_pip_par[i][s][p] = Lfit->GetParError(i);	
				H50_pip_par[i][s][p] = Hfit->GetParameter(i);
				eH50_pip_par[i][s][p] = Hfit->GetParError(i);
			}
			
			mg50_pip[p][s] = ~TMultiGraph();
			//Lfit = ~TF1();
			//Rfit = ~TF1();
			
		}
	}

	//// graphs of parameters
	//TCanvas *cL50_pip_par[Ni];
	//TCanvas *cH50_pip_par[Ni];
	TGraphErrors *grL50_pip_par[Ni][Ns];
	TGraphErrors *grH50_pip_par[Ni][Ns];	
	for (int i=0; i<Ni; i++)
	{
	//	cL50_pip_par[i] = new TCanvas(Form("cL50_par%i_pip",i),Form("cL50_par%i_pip",i),1000,800);
	//	cL50_pip_par[i]->Divide(3,2);
	//	cH50_pip_par[i] = new TCanvas(Form("cH50_par%i_pip",i),Form("cH50_par%i_pip",i),1000,800);
	//	cH50_pip_par[i]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			grL50_pip_par[i][s] = new TGraphErrors(Np,pcenter_pip,L50_pip_par[i][s],0,eL50_pip_par[i][s]);
			grL50_pip_par[i][s]->SetMarkerSize(1.5);
			grL50_pip_par[i][s]->SetMarkerColor(2);
			grL50_pip_par[i][s]->SetMarkerStyle(21);
			grL50_pip_par[i][s]->GetXaxis()->SetTitle("pip Momentum");
			grL50_pip_par[i][s]->GetYaxis()->SetTitle("Low Cut (#delta#phi)");
			grL50_pip_par[i][s]->SetName(Form("grL50_pip_par%i-sector%i",i,s+1));
			grL50_pip_par[i][s]->SetTitle(Form("grL50_pip_par%i-sector%i",i,s+1));
	//		cL50_pip_par[i]->cd(s+1);
			grL50_pip_par[i][s]->Draw("AP");
			grL50_pip_par[i][s]->Write();
					
			grH50_pip_par[i][s] = new TGraphErrors(Np,pcenter_pip,H50_pip_par[i][s],0,eH50_pip_par[i][s]);
			grH50_pip_par[i][s]->SetMarkerSize(1.5);
			grH50_pip_par[i][s]->SetMarkerColor(3);
			grH50_pip_par[i][s]->SetMarkerStyle(21);
			grH50_pip_par[i][s]->GetXaxis()->SetTitle("pip Momentum");
			grH50_pip_par[i][s]->GetYaxis()->SetTitle("High Cut (#delta#phi)");
			grH50_pip_par[i][s]->SetName(Form("grH50_pip_par%i-sector%i",i,s+1));
			grH50_pip_par[i][s]->SetTitle(Form("grH50_pip_par%i-sector%i",i,s+1));
	//		cH50_pip_par[i]->cd(s+1);

			grH50_pip_par[i][s]->Draw("AP");
			grH50_pip_par[i][s]->Write();
		}
	}
	////*////
	///////////////////////////////////////////////// finish pip calculation ////////////////////////////////////////////////////

	
	
	
	
	//*///
	///////////////////////////////////////////////// begin pim calculation ////////////////////////////////////////////////////	
	//read in momentum hists, draw them, get bin centers
	//TCanvas *cpcenter_Contracted_pim = new TCanvas("cpcenter_Contracted_pim","cpcenter_Contracted_pim",1000,800);
	//cpcenter_Contracted_pim->Divide(4,4);
	//TCanvas *cpcenter_pim = new TCanvas("cpcenter_pim","cpcenter_pim",1000,800);
	//cpcenter_pim->Divide(Np,Nt);
	int cancount = 1;	
	TH1F *hpcenter_pim[Np][Nt];
	TH1F *hpcenter_Contracted_pim[Np];
	Float_t pcenter_pim[Np] = {0};
	Float_t prms_pim[Np] = {0};
	for (int p=0; p<Np; p++)
	{
		for (int t=0; t<Nt; t++)
		{ 
			//cpcenter_pim->cd(cancount);
			hpcenter_pim[p][t] = (TH1F*)fInput->Get(Form("hpcenter_pim_p%i_t%i",p,t));
			hpcenter_pim[p][t]->Draw();
			cancount += 1;
		}
		
		hpcenter_Contracted_pim[p] = (TH1F*)hpcenter_pim[p][0]->Clone();
		hpcenter_Contracted_pim[p]->SetName(Form("hpContracted_pim_p%i",p));
		hpcenter_Contracted_pim[p]->SetTitle(Form("hpContracted_pim_p%i",p));
		for (int t=1; t<Nt; t++)
		{ 
			hpcenter_Contracted_pim[p]->Add(hpcenter_pim[p][t],1);
		}
		//cpcenter_Contracted_pim->cd(p+1);
		hpcenter_Contracted_pim[p]->Draw();
		pcenter_pim[p] =  hpcenter_Contracted_pim[p]->GetMean();
		prms_pim[p] =  hpcenter_Contracted_pim[p]->GetRMS();
		cout << "pcenter pim = " <<	pcenter_pim[p] <<endl;
	}


	//set up the canvas and the graphs
	TCanvas *c50_pim[Np];
	//TCanvas *cH50_pim[Np];
	TGraphErrors *grL50_pim[Np][Ns];
	TGraphErrors *grH50_pim[Np][Ns];
	TMultiGraph *mg50_pim[Np][Ns];
	//set up the fits
	TF1 *Lfit = new TF1("Lfit","([1]*(1 - 1/((x - [2])*[1]/[0])))", 5, 90);
	TF1 *Hfit = new TF1("Hfit","([1]*(1 - 1/((x - [2])*[1]/[0])))", 5, 90);
	
	
	TF1 *newLfit = new TF1("Lfit","[0] - [1]/(x - [2])", 5, 90);
	TF1 *newHfit = new TF1("Hfit","[0] - [1]/(x - [2])", 5, 90);
	
	TF1 *Lfit = newLfit;
	TF1 *Hfit = newHfit;

	//Lfit->SetParLimits(0, 0, 100);
	//Hfit->SetParLimits(0, 0, 100);
	Lfit->SetParLimits(1, -1000, -15);
	Hfit->SetParLimits(1, 15, 1000);
	Lfit->SetParLimits(2, 4, 23); //this is the parameter which loccates the asymtote
	Hfit->SetParLimits(2, 4, 23);	
	
	Int_t NumParsL = Lfit->GetNumberFreeParameters();
	Int_t NumParsH = Hfit->GetNumberFreeParameters();




	Lfit->SetLineColor(1);
	Hfit->SetLineColor(1);
	const int Ni = NumParsL;
	//setup the variables to store fitting parameters... the order is s then p so it can be plotted in tgraph
	Float_t L50_pim_par[Ni][Ns][Np] = {0};
	Float_t eL50_pim_par[Ni][Ns][Np] = {0};
	Float_t H50_pim_par[Ni][Ns][Np] = {0};
	Float_t eH50_pim_par[Ni][Ns][Np] = {0};
	for (int p=0; p<Np; p++)
	{
		//c50_pim[p] = new TCanvas(Form("c50_pim%i",p),Form("c50_pim%i",p),1000,800);
		//c50_pim[p]->Divide(3,2);				
		for (int s=0; s<Ns; s++)
		{
			//get graphs

			grL50_pim[p][s] = (TGraphErrors*)fInput->Get(Form("grL50_pim_p%i-sector%i",p,s+1));
			grL50_pim[p][s]->Fit("Lfit","Rq");
			grH50_pim[p][s] = (TGraphErrors*)fInput->Get(Form("grH50_pim_p%i-sector%i",p,s+1));
			grH50_pim[p][s]->SetMarkerColor(3);
			grH50_pim[p][s]->Fit("Hfit","Rq");
			

			//grH50_pim[p][s]->SetTitle("");
			//grH50_pim[p][s]->SetName("");
			grH50_pim[p][s] = ~TGraphErrors();
			grL50_pim[p][s] = ~TGraphErrors();
			
			//put in multigraph, style and draw
			mg50_pim[p][s] = new TMultiGraph();
			mg50_pim[p][s]->Add(grH50_pim[p][s]);
			mg50_pim[p][s]->Add(grL50_pim[p][s]);

			mg50_pim[p][s]->SetName(Form("pim_p%i-sector%i",p,s+1));
			mg50_pim[p][s]->SetTitle(Form("pim_p%i-sector%i",p,s+1));
			mg50_pim[p][s]->Draw("ap");
			//must set axis names after drawn for some reason
			mg50_pim[p][s]->GetXaxis()->SetTitle("#theta");
			mg50_pim[p][s]->GetYaxis()->SetTitle("#delta#phi");
		 	
			//c50_pim[p]->cd(s+1);
			TCanvas *CAN = new TCanvas("CAN","CAN",1000,800);
			mg50_pim[p][s]->Draw("ap");
			mg50_pim[p][s]->Write();
		
			//CAN->Update();
			CAN->Print(Form("./pics/SecondGen/PhiVsTheta_pim-p%i-sec%i.eps",p,s+1));
			
			//store the fitting parameters 
			for (int i=0; i<Ni; i++)
			{
				L50_pim_par[i][s][p] = Lfit->GetParameter(i);
				eL50_pim_par[i][s][p] = Lfit->GetParError(i);	
				H50_pim_par[i][s][p] = Hfit->GetParameter(i);
				eH50_pim_par[i][s][p] = Hfit->GetParError(i);
			}
			
			mg50_pim[p][s] = ~TMultiGraph();
			//Lfit = ~TF1();
			//Rfit = ~TF1();
			
		}
	}

	//// graphs of parameters
	//TCanvas *cL50_pim_par[Ni];
	//TCanvas *cH50_pim_par[Ni];
	TGraphErrors *grL50_pim_par[Ni][Ns];
	TGraphErrors *grH50_pim_par[Ni][Ns];	
	for (int i=0; i<Ni; i++)
	{
	//	cL50_pim_par[i] = new TCanvas(Form("cL50_par%i_pim",i),Form("cL50_par%i_pim",i),1000,800);
	//	cL50_pim_par[i]->Divide(3,2);
	//	cH50_pim_par[i] = new TCanvas(Form("cH50_par%i_pim",i),Form("cH50_par%i_pim",i),1000,800);
	//	cH50_pim_par[i]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			grL50_pim_par[i][s] = new TGraphErrors(Np,pcenter_pim,L50_pim_par[i][s],0,eL50_pim_par[i][s]);
			grL50_pim_par[i][s]->SetMarkerSize(1.5);
			grL50_pim_par[i][s]->SetMarkerColor(2);
			grL50_pim_par[i][s]->SetMarkerStyle(21);
			grL50_pim_par[i][s]->GetXaxis()->SetTitle("pim Momentum");
			grL50_pim_par[i][s]->GetYaxis()->SetTitle("Low Cut (#delta#phi)");
			grL50_pim_par[i][s]->SetName(Form("grL50_pim_par%i-sector%i",i,s+1));
			grL50_pim_par[i][s]->SetTitle(Form("grL50_pim_par%i-sector%i",i,s+1));
	//		cL50_pim_par[i]->cd(s+1);
			grL50_pim_par[i][s]->Draw("AP");
			grL50_pim_par[i][s]->Write();
					
			grH50_pim_par[i][s] = new TGraphErrors(Np,pcenter_pim,H50_pim_par[i][s],0,eH50_pim_par[i][s]);
			grH50_pim_par[i][s]->SetMarkerSize(1.5);
			grH50_pim_par[i][s]->SetMarkerColor(3);
			grH50_pim_par[i][s]->SetMarkerStyle(21);
			grH50_pim_par[i][s]->GetXaxis()->SetTitle("pim Momentum");
			grH50_pim_par[i][s]->GetYaxis()->SetTitle("High Cut (#delta#phi)");
			grH50_pim_par[i][s]->SetName(Form("grH50_pim_par%i-sector%i",i,s+1));
			grH50_pim_par[i][s]->SetTitle(Form("grH50_pim_par%i-sector%i",i,s+1));
	//		cH50_pim_par[i]->cd(s+1);

			grH50_pim_par[i][s]->Draw("AP");
			grH50_pim_par[i][s]->Write();
		}
	}
	////*////
	///////////////////////////////////////////////// finish pim calculation ////////////////////////////////////////////////////
	
	

	
	
	
	
	
	
	

	

}





/////////////////////////////////////////////////////////////////////



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
	gStyle->SetOptFit(1);
}


























