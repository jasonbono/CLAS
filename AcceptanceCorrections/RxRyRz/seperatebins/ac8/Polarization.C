/*

Name: .C
Author: Jason Bono
Date: April 24 2013
Purpose: Fifth step.  Reads in the text file and root outputed by CorrectPionDist.C. The txt file is used for all calculations, the root file is just read as a cross check.

Input: ./txt/DataCor.txt & ./hists/PolHists.root   OR  ./txt/SimTestCor.txt & ./hists/SimTest_PolHists.root
Output: ./txt/PolResults.txt  OR ./txt/SimTestPolResults.txt 

*/

//#include "/Users/Bono/clas/myDefinitions/EXiBins.h" //for the graph titles
#include "./DataEXiBins.h"  //for the graph titles
//#include "./1DataBin.h" 

#include "./SimEXiBins.h"



void Polarization()
{
	StyleUp();
	const int Nb = 2,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
	const int Np = 12; //number of pion bins
	int Nk = 60; //# of pion bins used to get the acceptance parameters
//	const int Nq = 20; //number of energy and Xi bins for acceptance corrections
	const float alpha = -0.458;	
		
	const char* BinType[Nb] = {"E","Xi"};
	const char* Axis[Nd] = {"x","y","z"};
			
	//interactively choose Data or Simulation
	cout << "enter choice of what you want to look at (Data, NoPol, PosPol or NegPol):";
	const string cchoice;
	cin >> cchoice;
	//second question
	cout << "What kind of cuts? (Basic_Mass3, Basic_BadPion, Basic_UnknownBackground,  ):";
	const string cuts;
	cin >> cuts;
	//third question
	cout << "enter where you would like to have had the acceptance derived from ( NoPol, PosPol or NegPol):";
	const string cchoiceAC;
	cin >> cchoiceAC;
	if ( (cchoiceAC.compare("NoPol") != 0) && (cchoiceAC.compare("PosPol") != 0) && (cchoiceAC.compare("NegPol") != 0) )
	{
		cout << "incorect of choice of AC. quiting" <<endl;
		gROOT->ProcessLine(".q");
	}
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
	//input
	//TFile* fPolHistos = new TFile(Form("./hists/%s-Ac%sCorrected-%i_%i_%ibins%s.root",choice.c_str(),choiceAC.c_str(),Nk,Nq,Nc,fid.c_str()));	

	//output
	ofstream myfile;
	myfile.open (Form("./txt/%sAc%sCorrected-PolResults-%i_%i_%ibins_%s%s.txt",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nq,Nc,cuts.c_str(),fid.c_str()));	
	double BinCenter[Nb][Nc][Nd][Np] = {0}, COUNTcor[Nb][Nc][Nd][Np] = {0}, eBinCenter[Nb][Nc][Nd][Np] = {0}, eCOUNTcor[Nb][Nc][Nd][Np] = {0};
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p < Np; p++)
				{
	  				in >> BinCenter[b][c][d][p] >> COUNTcor[b][c][d][p] >> eBinCenter[b][c][d][p] >> eCOUNTcor[b][c][d][p];
					cout << BinCenter[b][c][d][p] << " " << COUNTcor[b][c][d][p] << " " << eBinCenter[b][c][d][p] << " " << eCOUNTcor[b][c][d][p] <<endl;
	 			}
			}
		}
	}
	in.close();

	TCanvas *cPol[Nb];
	Double_t x[Np] = {0}, y[Np] = {0};
	Double_t ex[Np] = {0}, ey[Np] = {0};
	vector<double> xx;
	vector<double> yy;
	vector<double> exx;
	vector<double> eyy;
	
	TF1 *f1 = new TF1("f1",Form("[0] - [0]*%f*[1]*x",alpha),-1,1);
	Double_t p0[Nb][Nc][Nd] = {0},p1[Nb][Nc][Nd] = {0};
	Double_t ep0[Nb][Nc][Nd] = {0},ep1[Nb][Nc][Nd] = {0};
	Double_t Polarization[Nb][Nc][Nd] = {0};
	Double_t ePolarization[Nb][Nc][Nd] = {0};
	Double_t ChiSquared[Nb][Nc][Nd] = {0};
	Double_t GraphTop[Nb][Nc][Nd] = {0};
	TGraphErrors *storegr[Nb][Nc][Nd];
	TLatex *storetex[Nb][Nc][Nd];
	
	int cancount = 0;
	for (int b = 0; b < Nb; b++)
	{
		cancount=1;
		cPol[b] = new TCanvas(Form("cPol%s",BinType[b]),Form("cPol%s",BinType[b]),1200,1000);
		cPol[b]->Divide(3,Nc);
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p < Np; p++)
				{						
					if (COUNTcor[b][c][d][p] > 100)
					{
						if ((d == 0 && BinCenter[b][c][d][p] < -1) || (d == 2 && (BinCenter[b][c][d][p] < -1 || BinCenter[b][c][d][p] > 1  ))  )
						{
							cout << "Point out of specified range! Omiting. "<<endl;
						}
						else
						{
							xx.push_back(BinCenter[b][c][d][p]);
							yy.push_back(COUNTcor[b][c][d][p]);
							exx.push_back(eBinCenter[b][c][d][p]);
							eyy.push_back(eCOUNTcor[b][c][d][p]);	
							cout <<"xx,yy,exx,eyy = " << xx[p] << " " << yy[p] << " " <<exx[p] << " " << eyy[p] <<endl;	
							//myfile  << x[p] << " " << y[p] << " " <<ex[p] << " " << ey[p] <<endl;
						}	
					}
					else
					{
						cout << "OMITING A POINT" <<endl;
					}
				}
				int size = xx.size();
				cout <<"size of vector = "<< size << endl;
				
				//fill the number to arrays that root can plot
				for(int p=0; p < size; p++)
				{
					x[p] = xx[p];
					y[p] = yy[p];
					ex[p] = exx[p];
					ey[p] = eyy[p];
				}
				//clear the cpp std::vector(s) for next binn
				xx.clear();
				yy.clear();
				exx.clear();
				eyy.clear(); 
	
			///*///			
				//set graph and style it
				TGraphErrors *mygr = new TGraphErrors(size,x,y,ex,ey);
				mygr->SetMinimum(0);
				GraphTop[b][c][d] = mygr->GetHistogram()->GetMaximum();
				mygr->GetXaxis()->SetTitle(Form("  cos(#theta_{#pi^{-}}^{%s})  ",Axis[d]));
				
				
				if (b == 0)
				{
					mygr->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f ",EVal[c],EVal[c+1]));
				/*	
					if(c == 0)
					{
						mygr->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f ",EXiParameterA,EXiParameterB));
						
					}
					if(c == 1)
					{
						mygr->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f ",EXiParameterB,EXiParameterC));
					}
					if(c == 2)
					{
						mygr->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f ",EXiParameterC,EXiParameterD));
					}
				*/
				}
				if (b == 1)
				{
					mygr->SetTitle(Form(" %1.2f < cos(#theta_{#Xi}^{cm}) < %1.2f ",XVal[c],XVal[c+1]));
					/*
						if(c == 0)
						{
							mygr->SetTitle(Form(" %1.2f < #theta_{#Xi}^{CM} < %1.2f ",EXiParameterE,EXiParameterF));
						}
						
						if(c == 1)
						{
							mygr->SetTitle(Form(" %1.2f < #theta_{#Xi}^{CM} < %1.2f ",EXiParameterF,EXiParameterG));
						}
						
						if(c == 2)
						{
							mygr->SetTitle(Form(" %1.2f < #theta_{#Xi}^{CM} < %1.2f ",EXiParameterG,EXiParameterH));
						}
				*/
				}
				//*///
				mygr->Fit("f1","EV");
				p0[b][c][d] = f1->GetParameter(0);
				ep0[b][c][d] = f1->GetParError(0);
				p1[b][c][d] = f1->GetParameter(1);
				ep1[b][c][d] = f1->GetParError(1);
				ChiSquared[b][c][d] = f1->GetChisquare();
				Polarization[b][c][d] = p1[b][c][d];
				ePolarization[b][c][d] = ep1[b][c][d];
				//*///
				
				/*///
				mygr->Fit("pol1");
				TF1 *myfit = mygr->GetFunction("pol1");
				p0[b][c][d] = myfit->GetParameter(0);
				ep0[b][c][d] = myfit->GetParError(0);
				p1[b][c][d] = myfit->GetParameter(1);
				ep1[b][c][d] = myfit->GetParError(1);
				Polarization[b][c][d] = (-1/alpha)*(p1[b][c][d]/p0[b][c][d]);
				ePolarization[b][c][d] = (-1/alpha)*( (ep0[b][c][d])*(p1[b][c][d]/(p0[b][c][d]*p0[b][c][d])) + (ep1[b][c][d]/p0[b][c][d])  ); 
				//*///
				
				cout << "p0 = " << p0[b][c][d] << "  ep0 = " << ep0[b][c][d] <<"  p1 = " << p1[b][c][d] << "  ep1 = " << ep1[b][c][d] <<endl;
				cout << "Polarization = " << Polarization[b][c][d] << "  ePolarization = " << ePolarization[b][c][d] <<endl;
				cout <<endl;
				cPol[b]->cd(cancount);
				mygr->Draw("A*");
				storegr[b][c][d] = mygr;
			
				cancount += 1;	
			///*///
			}			
		}
	}
	
//*///	
	// output the polarization results to a text file, compute the mean and rms of the polarizaiton in all 18 bins, then draw the polarizaiton on each plot 
	
	double PolSum = 0;
	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int b = 0; b < Nb; b++)
	{
		cancount=1;
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{	
				
				PolSum += Polarization[b][c][d];
				myfile << Polarization[b][c][d] << " " << ePolarization[b][c][d] <<endl;
				
				cPol[b]->cd(cancount);
				cout << "Polarization = " << Polarization[b][c][d] << "  ePolarization = " << ePolarization[b][c][d]  <<endl;
				
				if(d == 0)
				{
					mytex=new TLatex(0.3, 0.4*GraphTop[b][c][d],Form("Cx = %5.3f #pm %5.3f ",Polarization[b][c][d],ePolarization[b][c][d]));
				}
				if(d == 1)
				{
					mytex=new TLatex(-0.7, 0.4*GraphTop[b][c][d],Form("P = %5.3f #pm %5.3f ",Polarization[b][c][d],ePolarization[b][c][d]));
				}
				if(d == 2)
				{
					mytex=new TLatex(-0.5, 0.4*GraphTop[b][c][d],Form("Cz = %5.3f #pm %5.3f ",Polarization[b][c][d],ePolarization[b][c][d]));
				}
				mytex->SetTextSize(0.06); 
				mytex->SetTextColor(4);
				mytex->Draw("SAME");
				storetex[b][c][d] =  mytex;
				
				cancount += 1;
			}
		}
	}

	

	double PolAvg = PolSum/(Nb*Nc*Nd);
	double Pol2ndMoment = 0;
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				Pol2ndMoment += (PolAvg - Polarization[b][c][d])*(PolAvg - Polarization[b][c][d]);
				
			}
		}
	}

	double PolRMS = sqrt(Pol2ndMoment)/(Nb*Nc*Nd);
	
	cout << " PolAvg = " << PolAvg <<  "  PolRMS = "<< PolRMS <<endl; 

///*////	


	cPol[0]->Print(Form("~/Desktop/E%i_%i.eps",Nq,Nc));
	cPol[1]->Print(Form("~/Desktop/Xi%i_%i.eps",Nq,Nc));	


	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				//cout<<GraphTop[b][c][d]<<endl;
				cout<<"ChiSquared = "<<ChiSquared[b][c][d]<<endl;
			}
		}
	}



//*///
//extra thing to display for lei
	TCanvas *cE=new TCanvas("cE","cE",1200,1000);
	cE->Divide(2,1);
	cE->cd(1);
	storegr[0][2][0]->Draw("A*");
	storetex[0][2][0]->Draw("same");
	cE->cd(2);
	storegr[0][2][2]->Draw("A*");
	storetex[0][2][2]->Draw("same");
	
	TCanvas *cX=new TCanvas("cX","cX",1200,1000);
	cX->Divide(2,1);
	cX->cd(1);
	storegr[1][2][0]->Draw("A*");
	storetex[1][2][0]->Draw("same");
	cX->cd(2);
	storegr[1][2][2]->Draw("A*");
	storetex[1][2][2]->Draw("same");
	
///*///

	TCanvas *cThesis=new TCanvas("cThesis","cThesis",1200,1000);
	cThesis->Divide(3,2);
	cancount = 1;
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			cThesis->cd(cancount);
			storegr[b][c][1]->Draw("A*");
			storetex[b][c][1]->Draw("same");
			cancount += 1;
		}
	}
	
	cE->cd(1);
	storegr[0][2][0]->Draw("A*");
	storetex[0][2][0]->Draw("same");
	cE->cd(2);
	storegr[0][2][2]->Draw("A*");
	storetex[0][2][2]->Draw("same");





}




///////////////////////////////////////////////////////////////////////////



StyleUp()
{
	gStyle->SetTitleXOffset(0.4);
	gStyle->SetTitleYOffset(0.6);
	gStyle->SetTitleSize(0.07);
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
