




void DrawFiducialCuts()
{
	StyleUp();
	const int Np = 15;  //number of momentum bins	
	const int Nt = 15;  //number of theta bins	
	const int Ns = 6;  //number of sectors
	const int Ni = 3; //number of parameters in second generation fit
	const int Nj = 3; //number of parameters in second generation fit
	TFile* fdata = new TFile("/Users/Bono/clas/rootfiles/g12/ppippim/full/ppippim-v03_Phi.root");  
	TTree *tdata = (TTree*)fdata->Get("v03");
	//read in the fitting parameters
	ifstream infile_pip(Form("./txt/ThirdGen/FitParams_Pos-%i-%ibins.txt",Np,Nt));
	Float_t	ParL_pip[Ns][Ni][Nj];
	Float_t	ParH_pip[Ns][Ni][Nj];	
	for (int s=0; s<Ns; s++)
	{
		for (int i=0; i<Ni; i++)
		{	
			for (int j=0; j<Nj; j++)
			{	
				infile_pip >> ParL_pip[s][i][j]; 
				infile_pip >> ParH_pip[s][i][j]; 
			}
		}
	}
	infile_pip.close();
	ifstream infile_pim(Form("./txt/ThirdGen/FitParams_Neg-%i-%ibins.txt",Np,Nt));
	Float_t	ParL_pim[Ns][Ni][Nj];
	Float_t	ParH_pim[Ns][Ni][Nj];	
	for (int s=0; s<Ns; s++)
	{
		for (int i=0; i<Ni; i++)
		{	
			for (int j=0; j<Nj; j++)
			{	
				infile_pim >> ParL_pim[s][i][j]; 
				infile_pim >> ParH_pim[s][i][j]; 
			}
		}
	}
	infile_pim.close();
	TCanvas *CAN = new TCanvas("CAN","CAN",1000,800);
	
	
	
	
	
	
	
	///////////////////////////////////////////////// begin pip calculation ////////////////////////////////////////////////////
	TF2 *funL_pip[Ns];
	TF2 *funH_pip[Ns];
	for (int s=0; s<Ns; s++)
	{
		funL_pip[s] = new TF2(Form("PhiLow_pip_sec%i",s+1),FidFunc,0,5,0,90,9); //the last number specifies how many parameters
		funL_pip[s]->SetTitle(Form("PhiLow_pip_sec%i;pip momentum (GeV);pip #theta",s+1));
		funL_pip[s]->SetMaximum(0);
		funL_pip[s]->SetMinimum(-90);
		funL_pip[s]->SetLineColor(0);
		funL_pip[s]->SetLineWidth(5);
		
		funH_pip[s] = new TF2(Form("PhiHigh_pip_sec%i",s+1),FidFunc,0,5,0,90,9); //the last number specifies how many parameters
		funH_pip[s]->SetTitle(Form("PhiHigh_pip_sec%i;pip momentum (GeV);pip #theta",s+1));
		funH_pip[s]->SetMinimum(0);
		funH_pip[s]->SetMaximum(90);
		funH_pip[s]->SetLineColor(2);
		funH_pip[s]->SetLineWidth(5);

		for (int i=0; i<Ni; i++)
		{
			for (int j=0; j<Nj; j++)
			{
				funL_pip[s]->SetParameter(3*i + j,ParL_pip[s][i][j]);
				funH_pip[s]->SetParameter(3*i + j,ParH_pip[s][i][j]);
			}
		}
		funL_pip[s]->Draw("colz"); 
		CAN->Print(Form("./pics/Effects/CutL_pip-sec%i.eps",s+1));
		funH_pip[s]->Draw("colz");
		CAN->Print(Form("./pics/Effects/CutH_pip-sec%i.eps",s+1));
	}
	///////////////////////////////////////////////// end pip calculation ////////////////////////////////////////////////////




	///////////////////////////////////////////////// begin pim calculation ////////////////////////////////////////////////////
	TF2 *funL_pim[Ns];
	TF2 *funH_pim[Ns];
	for (int s=0; s<Ns; s++)
	{
		funL_pim[s] = new TF2(Form("PhiLow_pim_sec%i",s+1),FidFunc,0,5,0,90,9); //the last number specifies how many parameters
		funL_pim[s]->SetTitle(Form("PhiLow_pim_sec%i;pim momentum (GeV);pim #theta",s+1));
		funL_pim[s]->SetMaximum(0);
		funL_pim[s]->SetMinimum(-90);
		funL_pim[s]->SetLineColor(0);
		funL_pim[s]->SetLineWidth(5);
		
		funH_pim[s] = new TF2(Form("PhiHigh_pim_sec%i",s+1),FidFunc,0,5,0,90,9); //the last number specifies how many parameters
		funH_pim[s]->SetTitle(Form("PhiHigh_pim_sec%i;pim momentum (GeV);pim #theta",s+1));
		funH_pim[s]->SetMinimum(0);
		funH_pim[s]->SetMaximum(90);
		funH_pim[s]->SetLineColor(2);
		funH_pim[s]->SetLineWidth(5);

		for (int i=0; i<Ni; i++)
		{
			for (int j=0; j<Nj; j++)
			{
				funL_pim[s]->SetParameter(3*i + j,ParL_pim[s][i][j]);
				funH_pim[s]->SetParameter(3*i + j,ParH_pim[s][i][j]);
			}
		}
		funL_pim[s]->Draw("colz"); 
		CAN->Print(Form("./pics/Effects/CutL_pim-sec%i.eps",s+1));
		funH_pim[s]->Draw("colz");
		CAN->Print(Form("./pics/Effects/CutH_pim-sec%i.eps",s+1));
	}
	///////////////////////////////////////////////// end pim calculation ////////////////////////////////////////////////////












	/*//plot data over 
	//pip
	TCut pip_seccut[Ns];
	pip_seccut[0] = "pipsector == 1";
	pip_seccut[1] = "pipsector == 2";
	pip_seccut[2] = "pipsector == 3";
	pip_seccut[3] = "pipsector == 4";
	pip_seccut[4] = "pipsector == 5";
	pip_seccut[5] = "pipsector == 6";
	for (int s=0; s<Ns; s++)
	{
		//h2d[s] = new TH2F(Form("h2d_Sector%i",s+1),"",100,0,7,100,0,90);
		tdata->Draw(Form(" piplabtheta : ppip : pipphidiff >>h2d_Sector%i",s+1),pip_seccut[s],"colz");
		funL_pip[s]->Draw("same");
		funH_pip[s]->Draw("same");
		CAN->Print(Form("./pics/Effects/DataCutOverlay_pip-sec%i.ps",s+1));
	}
	
	
	
	//pim
	TCut pim_seccut[Ns];
	pim_seccut[0] = "pimsector == 1";
	pim_seccut[1] = "pimsector == 2";
	pim_seccut[2] = "pimsector == 3";
	pim_seccut[3] = "pimsector == 4";
	pim_seccut[4] = "pimsector == 5";
	pim_seccut[5] = "pimsector == 6";
	for (int s=0; s<Ns; s++)
	{
		//h2d[s] = new TH2F(Form("h2d_Sector%i",s+1),"",100,0,7,100,0,90);
		tdata->Draw(Form(" pimlabtheta : ppim : pimphidiff >>h2d_Sector%i",s+1),pim_seccut[s],"colz");
		funL_pim[s]->Draw("same");
		funH_pim[s]->Draw("same");
		CAN->Print(Form("./pics/Effects/DataCutOverlay_pim-sec%i.ps",s+1));
	}	
	///*///

	
}

///////////////////////////////////////////
//c style 2d function
Double_t FidFunc (Double_t *x, Double_t *par) 
{
	Double_t xx = x[0]; //momentum
	Double_t yy = x[1]; //theta
	Double_t a = (par[0]*pow(xx,par[1]) + par[2]);
	Double_t b = (par[3]*pow(xx,par[4]) + par[5]);
	Double_t c = (par[6]*pow(xx,par[7]) + par[8]);
 	Double_t f =  a -  b/(yy - c);
	return 	f;
}


Double_t myOLD2dfunc (Double_t *x, Double_t *par) 
{
	Double_t xx = x[0];
	Double_t yy = x[1];
	Double_t a = (par[0]*pow(xx,par[1]) + par[2]);
	Double_t b = (par[3]*pow(xx,par[4]) + par[5]);
	Double_t c = (par[6]*pow(xx,par[7]) + par[8]);
 	Double_t f = ( (b)*(1 - 1/((yy - c)*(b/a))));
	return 	f;
}


StyleUp()
{
	gStyle->SetTitleXOffset(0.4);
	gStyle->SetTitleYOffset(0.6);
	gStyle->SetTitleSize(0.09);
	gStyle->SetTitleYSize(0.07); 
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
}









