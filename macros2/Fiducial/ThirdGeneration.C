void ThirdGeneration()
{
	StyleUp();
	
	const int Np = 15;  //number of momentum bins	
	const int Nt = 15;  //number of theta bins	
	const int Ns = 6;  //number of sectors
	const int Ni = 3; //number of parameters in second generation fit
	const Int_t Nj = 3;
	//Nj will be the number of parameters in third generation fit

	TFile* fInput = new TFile(Form("./hists/SecondGen-%i-%ibins.root",Np,Nt));
	TFile* fOutput = new TFile(Form("./hists/ThirdGen-%i-%ibins.root",Np,Nt),"RECREATE");
	ofstream myfile_pip;
	myfile_pip.open (Form("./txt/ThirdGen/FitParams_Pos-%i-%ibins.txt",Np,Nt));
	ofstream myfile_pim;
	myfile_pim.open (Form("./txt/ThirdGen/FitParams_Neg-%i-%ibins.txt",Np,Nt));
	TCanvas *CAN = new TCanvas("CAN","CAN",1000,800);



	///////////////////////////////////////////////// begin pip calculation ////////////////////////////////////////////////////
	//TCanvas *cL50_pip_par[Ni];
	//TCanvas *cH50_pip_par[Ni];
	TGraphErrors *grL50_pip_par[Ni][Ns];
	TGraphErrors *grH50_pip_par[Ni][Ns];	
	TF1 *powfit = new TF1("powfit","[0]*pow(x,[1]) + [2]",0.25,4);
	TF1 *myfit;
	TF1 *FitResult_L_pip[Ns][Ni];
	TF1 *FitResult_H_pip[Ns][Ni];
	Float_t ParL_pip[Ns][Ni][6] = {0}; //10 is an upper limit for the number of parameters needed for the fit
	Float_t ParH_pip[Ns][Ni][6] = {0};
	for (int i=0; i<Ni; i++)
	{
		//set fit
		myfit = powfit;
	//	myfit->SetRange(0.25,4);	
	//	cL50_pip_par[i] = new TCanvas(Form("cL50_par%i_pip",i),Form("cL50_par%i_pip",i),1000,800);
	//	cL50_pip_par[i]->Divide(3,2);
	//	cH50_pip_par[i] = new TCanvas(Form("cH50_par%i_pip",i),Form("cH50_par%i_pip",i),1000,800);
	//	cH50_pip_par[i]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			//fit data and store fit for Low	
			grL50_pip_par[i][s] = (TGraphErrors*)fInput->Get(Form("grL50_pip_par%i-sector%i",i,s+1));
			if(i == 0)
			{
				grL50_pip_par[i][s]->SetMaximum(-25);
				grL50_pip_par[i][s]->SetMinimum(-32); 
			}
			if(i == 1)
			{
				grL50_pip_par[i][s]->SetMaximum(10);
				grL50_pip_par[i][s]->SetMinimum(-170);
			}
			if(i == 2)
			{
				grL50_pip_par[2][s]->SetMaximum(10);
				grL50_pip_par[2][s]->SetMinimum(-10);
			}
			grL50_pip_par[i][s]->GetYaxis()->SetTitle(Form("L-par%i-sector%i",i,s+1));
			grL50_pip_par[i][s]->Fit(myfit,"qR");
			FitResult_L_pip[s][i] = myfit;
			for (int j=0; j<Nj; j++)
			{
				ParL_pip[s][i][j] =  FitResult_L_pip[s][i]->GetParameter(j);
			}
			//fit data and store fit for High
			
			if ( (i == 0) && (s == 0) )	myfit->SetRange(0.25, 2); //dont fit some of the bad data points
			else myfit->SetRange(0.25,4);
			grH50_pip_par[i][s] = (TGraphErrors*)fInput->Get(Form("grH50_pip_par%i-sector%i",i,s+1));
			if(i == 0)
			{
				grH50_pip_par[i][s]->SetMaximum(30);
				grH50_pip_par[i][s]->SetMinimum(25); 
			}
			if(i == 1)
			{
				grH50_pip_par[i][s]->SetMaximum(140);
				grH50_pip_par[i][s]->SetMinimum(-10);
			}
			if(i == 2)
			{
				grH50_pip_par[2][s]->SetMaximum(15);
				grH50_pip_par[2][s]->SetMinimum(-7);
			}
			grH50_pip_par[i][s]->GetYaxis()->SetTitle(Form("H-par%i-sector%i",i,s+1));
			grH50_pip_par[i][s]->Fit(myfit,"qR");
			FitResult_H_pip[s][i] = myfit;
			for (int j=0; j<Nj; j++)
			{
				ParH_pip[s][i][j] = FitResult_H_pip[s][i]->GetParameter(j);
			}
			
	//		cL50_pip_par[i]->cd(s+1);
			grL50_pip_par[i][s]->Draw("AP");
			CAN->Print(Form("./pics/ThirdGen/L-ParVsP_pip-par%i-sec%i.eps",i,s+1));
	//		cH50_pip_par[i]->cd(s+1);
			grH50_pip_par[i][s]->Draw("AP");
			CAN->Print(Form("./pics/ThirdGen/H-ParVsP_pip-par%i-sec%i.eps",i,s+1));
			
			grL50_pip_par[i][s]->Write();
			grH50_pip_par[i][s]->Write();			
		}
	}
	
	//write out the fitting parameters
	for (int s=0; s<Ns; s++)
	{
		for (int i=0; i<Ni; i++)
		{	
			for (int j=0; j<Nj; j++)
			{	
				myfile_pip << ParL_pip[s][i][j] <<endl;
				myfile_pip << ParH_pip[s][i][j] <<endl;  
			}
		}
	}
	myfile_pip.close();
	///////////////////////////////////////////////// end pip calculation ////////////////////////////////////////////////////



	//*/////////////////////////////////////////////// begin pim calculation ////////////////////////////////////////////////////
	//TCanvas *cL50_pim_par[Ni];
	//TCanvas *cH50_pim_par[Ni];
	TGraphErrors *grL50_pim_par[Ni][Ns];
	TGraphErrors *grH50_pim_par[Ni][Ns];	
	TF1 *powfit = new TF1("powfit","[0]*pow(x,[1]) + [2]",0.3,4);
	TF1 *myfit;
	TF1 *FitResult_L_pim[Ns][Ni];
	TF1 *FitResult_H_pim[Ns][Ni];
	Float_t ParL_pim[Ns][Ni][6] = {0}; //10 is an upper limit for the number of parameters needed for the fit
	Float_t ParH_pim[Ns][Ni][6] = {0};
	for (int i=0; i<Ni; i++)
	{
		//set fit
		myfit = powfit;
		myfit->SetParLimits(1, -0.0001, 0.0001);	
	//	cL50_pim_par[i] = new TCanvas(Form("cL50_par%i_pim",i),Form("cL50_par%i_pim",i),1000,800);
	//	cL50_pim_par[i]->Divide(3,2);
	//	cH50_pim_par[i] = new TCanvas(Form("cH50_par%i_pim",i),Form("cH50_par%i_pim",i),1000,800);
	//	cH50_pim_par[i]->Divide(3,2);
		for (int s=0; s<Ns; s++)
		{
			//fit data and store fit for Low
			myfit->SetRange(0.4,4);
			grL50_pim_par[i][s] = (TGraphErrors*)fInput->Get(Form("grL50_pim_par%i-sector%i",i,s+1));
			if(i == 0)
			{
				grL50_pim_par[i][s]->SetMaximum(-24);
				grL50_pim_par[i][s]->SetMinimum(-33); 
			}
			if(i == 1)
			{
				grL50_pim_par[i][s]->SetMaximum(10);
				grL50_pim_par[i][s]->SetMinimum(-160);
			}
			if(i == 2)
			{
				grL50_pim_par[2][s]->SetMaximum(20);
				grL50_pim_par[2][s]->SetMinimum(0);
			}
			grL50_pim_par[i][s]->GetYaxis()->SetTitle(Form("L-par%i-sector%i",i,s+1));
			grL50_pim_par[i][s]->Fit(myfit,"qR");
			FitResult_L_pim[s][i] = myfit;
			for (int j=0; j<Nj; j++)
			{
				ParL_pim[s][i][j] =  FitResult_L_pim[s][i]->GetParameter(j);
			}
			//fit data and store fit for High
			myfit->SetRange(0.3,4);
			grH50_pim_par[i][s] = (TGraphErrors*)fInput->Get(Form("grH50_pim_par%i-sector%i",i,s+1));
			if(i == 0)
			{
				grH50_pim_par[i][s]->SetMaximum(30);
				grH50_pim_par[i][s]->SetMinimum(22); 
			}
			if(i == 1)
			{
				grH50_pim_par[i][s]->SetMaximum(140);
				grH50_pim_par[i][s]->SetMinimum(-10);
			}
			if(i == 2)
			{
				grH50_pim_par[2][s]->SetMaximum(30);
				grH50_pim_par[2][s]->SetMinimum(0);
			}
			grH50_pim_par[i][s]->GetYaxis()->SetTitle(Form("H-par%i-sector%i",i,s+1));
			grH50_pim_par[i][s]->Fit(myfit,"qR");
			FitResult_H_pim[s][i] = myfit;
			for (int j=0; j<Nj; j++)
			{
				ParH_pim[s][i][j] = FitResult_H_pim[s][i]->GetParameter(j);
			}
			
	//		cL50_pim_par[i]->cd(s+1);
			grL50_pim_par[i][s]->Draw("AP");
			CAN->Print(Form("./pics/ThirdGen/L-ParVsP_pim-par%i-sec%i.eps",i,s+1));
	//		cH50_pim_par[i]->cd(s+1);
			grH50_pim_par[i][s]->Draw("AP");
			CAN->Print(Form("./pics/ThirdGen/H-ParVsP_pim-par%i-sec%i.eps",i,s+1));
			
			grL50_pim_par[i][s]->Write();
			grH50_pim_par[i][s]->Write();			
		}
	}
	
	//write out the fitting parameters
	for (int s=0; s<Ns; s++)
	{
		for (int i=0; i<Ni; i++)
		{	
			for (int j=0; j<Nj; j++)
			{	
				myfile_pim << ParL_pim[s][i][j] <<endl;
				myfile_pim << ParH_pim[s][i][j] <<endl;  
			}
		}
	}
	myfile_pim.close();
	///*///////////////////////////////////////////////// end pim calculation ////////////////////////////////////////////////////


}

//////////////////////////////////////////////////


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

