/*
Name: IntegrateHists.C
Author: Jason Bono
Date: April 9 2013
Purpose: To print out the fitting info to text files. Second step in the calculation of the acceptance corrected pion distributions.

Input: *PionHists*.root
Output: *RxRyRz*.txt, *CovMatrixfile*.txt, *AcceptaceHists*.root

Update: ac2 was created to implement aproximately 27x3x2 different acceptance corrections 
*/


#include "./SimEXiBins.h"


void AcceptanceHists()
{

	const int Ne=10; //Ne=#parameters in fit 
	int Nk = 40; //# of pion bins

	

	//interactively choose Simulation type
	cout << "enter choice ( NoPol or PosPol or NegPol):";
	const string cchoice;
	cin >> cchoice;
	if(cchoice == "NoPol") 
	{
		const string choice="";
	}
	else 
	{
		const string choice = "-" + cchoice;
	}
	//second question
	cout << "What kind of cuts? (Basic_Mass3, Basic_Mass1, Basic_Mass6, Basic_BadPion, Basic_UnknownBackground,  ):";
	const string cuts;
	cin >> cuts;	
	cout << "Fiducial cuts? (type yes or no):";
	const string fidchoice;
	cin >> fidchoice;
	if (fidchoice == "yes")
	{
		const string fid = "-Fid";
	}
	else if (fidchoice == "no")
	{
		const string fid = "";
	}
	else
	{
		cout << "fidchoice bad"<<endl;
		exit(1);
	}

	ofstream myParFile,myCovMatrixFile;
	cout <<Form("The hists from %s%s%s will be evaluated",choice.c_str(),cuts.c_str(),fid.c_str()) <<endl;
	TFile* fHistos = new TFile(Form("./hists/PionHists%s-%i_%i_%ibins_%s%s.root",choice.c_str(),Nk,Nbq,Ncq,cuts.c_str(),fid.c_str()));	
	TFile* fAC = new TFile(Form("./hists/AcceptaceHists%s-%i_%i_%ibins_%s%s.root",choice.c_str(),Nk,Nbq,Ncq,cuts.c_str(),fid.c_str()),"RECREATE");
	myParFile.open (Form("./txt/RxRyRz%s-%i_%i_%ibins_%s%s.txt",choice.c_str(),Nk,Nbq,Ncq,cuts.c_str(),fid.c_str()));
	myCovMatrixFile.open (Form("./txt/CovMatrixfile%s-%i_%i_%ibins_%s%s.txt",choice.c_str(),Nk,Nbq,Ncq,cuts.c_str(),fid.c_str()));
	

	StyleUp();
	const int Na = 2,Nd = 3; //a=datatype, b=ebin, c=xibin, d=piaxis
	const char* DataType[Na] = {"MC","Gen"};
	const char* Axis[Nd] = {"x","y","z"};
	
	// Create model for the missing mass histograms (will use as clone)
	TH1D *h=new TH1D("h","",Nk,-1.0,1.0);
	h->GetYaxis()->SetTitle("Acceptance");
	h->GetXaxis()->SetTitle(" Cos(#theta_{#pi^{-}})");
	h->SetMinimum(0);
   	//assign pointers to each histogram in the file.
	TH1D *hPion[Na][Nbq][Ncq][Nd];
	TH1D *hAc[Nbq][Ncq][Nd];

	//TCanvas *cPion[Na][Ncq][Nd];
	int cancount = 1;	
	//get and store the pion distribtuions for MC and Gen.
	for (int a = 0; a < Na; a++)
	{
		for (int cq = 0; cq < Ncq; cq++)
		{
			for (int d = 0; d < Nd; d++)
			{
				//cPion[a][cq][d] = new TCanvas(Form("c%s-xbin%i-%s",DataType[a],cq,Axis[d]),Form("c%s-xbin%i-%s",DataType[a],cq,Axis[d]),800,600);
				//cPion[a][cq][d]->Divide(6,6);
				cancount = 1;
				for (int bq = 0; bq < Nbq; bq++)
				{
					hPion[a][bq][cq][d] = (TH1D*)h->Clone(Form("h%s-ebin%i-xbin%i-PiAxis%s",DataType[a],bq,cq,Axis[d]));
					hPion[a][bq][cq][d] = (TH1D*)fHistos->Get(Form("h%s-ebin%i-xbin%i-PiAxis%s",DataType[a],bq,cq,Axis[d]));
					//cPion[a][cq][d]->cd(cancount);
					hPion[a][bq][cq][d]->Draw();
					//Create a histogram to hold the confidence intervals

					
			
					hPion[a][bq][cq][d]->GetXaxis()->SetTitle(" Cos(#theta^{x}_{#pi^{-}})");
					hPion[a][bq][cq][d]->GetXaxis()->SetTitle(" Cos(#theta^{y}_{#pi^{-}_{y}})");
					hPion[a][bq][cq][d]->GetXaxis()->SetTitle(" Cos(#theta^{z}_{#pi^{-}_{z}})");
					
					cancount = cancount + 1;
				}
			}
		}
	}



	//////////////////////////  now compute the acceptance correction histogram and fit it to a function /////////////////////////////				
	
	//declare needed objected
	double A,B,C,Ac,eAc;
	//gx = new TF1("gx",Form("pol%i",Ne-1),-0.8,1);
	gx = new TF1("gx",Form("pol%i",Ne-1),-0.9,1);
	gy = new TF1("gy",Form("pol%i",Ne-1),-1,1);
	//gz = new TF1("gz",Form("pol%i",Ne-1),-1,0.6);
	gz = new TF1("gz",Form("pol%i",Ne-1),-1,0.7);
	TF1 *fit[Nd];
	fit[0] = gx;
	fit[1] = gy;
	fit[2] = gz;
	//further setup
	//fit[2]->SetRange(0.1,1);

    //gMinuit->SetFCN(fcn);
	float P[Nbq][Ncq][Nd][Ne];
 	float eP[Nbq][Ncq][Nd][Ne];	
	float Chi[Nbq][Ncq][Nd];
	//set stuff up for the error matrix
	float covMatrix[Nbq][Ncq][Nd][Ne][Ne]; //Rank 3 array of rank 2 error matrixes. total rank5
	TVirtualFitter::SetDefaultFitter("Minuit"); 	//set Minuit as default to use gMinuit 

	
	TCanvas *cAc[Ncq][Nd];
	for (int cq = 0; cq < Ncq; cq++)
	{
		for (int d = 0; d < Nd; d++)
		{
			cAc[cq][d] = new TCanvas(Form("cAc%i%s",cq,Axis[d]),Form("cAc%i%s",cq,Axis[d]),1200,1000);
			cAc[cq][d]->Divide(6,6);	
			cancount=1;	
			for (int bq = 0; bq < Nbq; bq++)
			{	
				hAc[bq][cq][d] = (TH1D*)h->Clone(Form("hAc-ebin%i-xbin%i-PiAxis%s",bq,cq,Axis[d]));
				for (int k = 0; k < Nk; k++)
				{
					//compute the acceptance histograms with binomial error
					A = hPion[0][bq][cq][d]->GetBinContent(k + 1);
					B = hPion[1][bq][cq][d]->GetBinContent(k + 1);
					Ac = A/B;
					eAc = (1/B)*sqrt(A*(1-Ac));
					hAc[bq][cq][d]->SetBinContent(k + 1, Ac);
					hAc[bq][cq][d]->SetBinError(k + 1, eAc);
				}
				//style and fit the Ac histograms
				cAc[cq][d]->cd(cancount);
				cancount = cancount + 1;
				hAc[bq][cq][d]->SetMinimum(0);
				hAc[bq][cq][d]->GetXaxis()->SetTitle(Form("Cos(#theta^{%s}_{#pi^{-}})",Axis[d]));
				hAc[bq][cq][d]->Fit(fit[d],"RE"); //R: range, E: Better error calculation
				Chi[bq][cq][d] = fit[d]->GetChisquare();
				
				//Access the fitting parameters and matrix
				TVirtualFitter * myVirtualFitter = TVirtualFitter::GetFitter();  //Set up the virtual fitter for error matrix
				//get all parameters for each fit 
				for (int e = 0; e < Ne; e++)
				{
					P[bq][cq][d][e] = fit[d]->GetParameter(e);
					eP[bq][cq][d][e] = fit[d]->GetParError(e);
					for (int j = 0; j < Ne; j++)
					{
						covMatrix[bq][cq][d][e][j] = myVirtualFitter->GetCovarianceMatrixElement(e,j);
						cout << covMatrix[bq][cq][d][e][j] <<endl;
					}
				}
				
				//Create a histogram to hold the confidence intervals
			   TH1D *hint = new TH1D("hint", "Fitted gaussian with .95 conf.band", 100, -3, 3);
			   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
			   //Now the "hint" histogram has the fitted function values as the 
			   //bin contents and the confidence intervals as bin errors
			   hint->SetStats(kFALSE);
			   hint->SetFillColor(2);
			   hint->Draw("e3 same");
			
			
				//TF1 *testfunc = new TF1("test","0.001",-0.5,0.5);
				//testfunc->Draw("Same");	
				hAc[bq][cq][d]->Write();  	//store the histograms in the new root file ./hists/AcceptaceHists.root
			}

		}
	}
	//now write results out to text file and display on terminal window
	for (int bq = 0; bq < Nbq; bq++)
	{
		for (int cq = 0; cq < Ncq; cq++)
		{
			for (int d = 0; d < Nd; d++)
			{
				cout << "--------- bq = "<<bq<<", cq = "<<cq<<", d = "<<d<<" ------------"<<endl;
				for (int e = 0; e < Ne; e++)
				{
					cout << "P = " << P[bq][cq][d][e] << "  eP = " << eP[bq][cq][d][e] <<"  Chi = " << Chi[bq][cq][d] << endl;
					myParFile<<P[bq][cq][d][e]<<" "<<eP[bq][cq][d][e]<<endl;
					for (int j = 0; j < Ne; j++)
					{
						myCovMatrixFile<< covMatrix[bq][cq][d][e][j] <<endl;					
					}
				}
			}
		}
	}
	myParFile.close();

	//DrawFit(Ne, P[0][0][0], covMatrix[0][0][0]);
	//gROOT->ProcessLine(".q");
}


//////////////////////////////////////////////////////////////////////////////


void DrawFit(const int dim,float FuncPars[dim],float CovMat[dim][dim])
{
		cout << " dim = " <<dim<<endl;
		cout <<"Vec components are: " << FuncPars[0] << " "<< FuncPars[1] << " "<< FuncPars[2] << endl;
		cout <<"some matrix components are: " << CovMat[0][0] << " "<< CovMat[0][1] << endl;
		
		TF1 *basef = new TF1("basef",Form("%f + %f*x + %f*x*x + %f*x*x*x + %f*x*x*x*x",FuncPars[0],FuncPars[1],FuncPars[2],FuncPars[3],FuncPars[4]),-1.0,1.0);
	  	basef->Draw();


		//------------make the function for the error		
		float errorfunc(Float_t x)
		{			
			float result = 0;
			for (int i = 0; i < dim; i++)
			{	
				for (int j = 0; j < dim; j++)
				{
					cout << "CovMat[" <<i<<"]["<<j<<"] = " << CovMat[i][j] << endl;
					result += CovMat[i][j]*pow(x,i)*pow(x,j);
				}
			}
			cout << " final result = " << result <<endl; 
			return result;	
		}
		//---------------------------------------------------
		
		TF1 *errorf = new TF1("errorf","errorfunc(x)",-1,1);
		
		TF1 *highf = new TF1("highf","basef + errorf");
		highf->SetRange(-1,1);

		TF1 *lowf = new TF1("lowf","basef - errorf");
		lowf->SetRange(-1,1);
	
	
		TCanvas *can=new TCanvas("can","",800,600);
		basef->Draw();
		lowf->Draw("SAME");
		highf->Draw("SAME");


}



StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.08);
	gStyle->SetTitleYSize(0.07); 
	gStyle->SetPadTopMargin(0.06);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(1);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit();
}