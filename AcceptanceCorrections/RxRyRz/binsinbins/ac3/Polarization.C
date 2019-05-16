/*

Name: .C
Author: Jason Bono
Date: April 24 2013
Purpose: Fifth step.  Reads in the text file and root outputed by CorrectPionDist.C. The txt file is used for all calculations, the root file is just read as a cross check.

Input: ./txt/DataCor.txt & ./hists/PolHists.root   OR  ./txt/SimTestCor.txt & ./hists/SimTest_PolHists.root
Output: ./txt/PolResults.txt  OR ./txt/SimTestPolResults.txt 

*/

// //#include "/Users/Bono/clas/myDefinitions/EXiBins.h" //for the graph titles
// #include "./DataEXiBins.h"  //for the graph titles
// 
// #include "./SimEXiBins.h"
// #include "./Fringe.h"
// #include "./constants.h"
// #include "./Pionbins.h"


//#include "./DataEXiBins.h"
#include "./OneDataBin.h"
//#include "./Fringe.h"
#include "./FringeOneDataBin.h"
#include "./SimEXiBins.h"
#include "./constants.h"
#include "./Pionbins.h"




void Polarization()
{
	StyleUp();
	
	const float alpha = -0.458;
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
	ifstream in(Form("./txt/%sAc%sCorrected-%i_%i_%i_%ibins_%s%s.txt",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nbq,Ncq,Nc,cuts.c_str(),fid.c_str()));
	if(!in)
	{
	    cout << "Cannot open txt file.\n";
		gROOT->ProcessLine(".q");
	}
	//output
	ofstream myfile;
	myfile.open (Form("./txt/%sAc%sCorrected-PolResults-%i_%i_%i_%ibins_%s%s.txt",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nbq,Ncq,Nc,cuts.c_str(),fid.c_str()));
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	// 
	// //interactively choose Data or Simulation
	// cout << "enter choice of what you want to look at (Data, NoPol, PosPol or NegPol):";
	// const string choice;
	// cin >> choice;
	// //second question
	// cout << "enter where you would like to have had the acceptance derived from ( NoPol, PosPol or NegPol):";
	// const string choiceAC;
	// cin >> choiceAC;
	// if ( (choiceAC.compare("NoPol") != 0) && (choiceAC.compare("PosPol") != 0) && (choiceAC.compare("NegPol") != 0) )
	// {
	// 	cout << "incorect of choice of AC. quiting" <<endl;
	// 	gROOT->ProcessLine(".q");
	// }
	// cout << "Fiducial cuts? (type yes or no):";
	// const string fidchoice;
	// cin >> fidchoice;
	// if (fidchoice == "yes")
	// {
	// 	const string fid = "-Fid";
	// }
	// else if (fidchoice == "no")
	// {
	// 	const string fid = "";
	// }
	// else
	// {
	// 	cout << "fidchoice bad"<<endl;
	// 	exit(1);
	// }
	// 		
	// //input
	// //TFile* fPolHistos = new TFile(Form("./hists/%s-Ac%sCorrected-%i_%i_%ibins%s.root",choice.c_str(),choiceAC.c_str(),Nk,Nq,Nc,fid.c_str()));
	// ifstream in(Form("./txt/%s-Ac%sCorrected-%i_%i_%i_%ibins%s.txt",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,Nc,fid.c_str()));
	// if(!in)
	// {
	//     cout << "Cannot open txt file.\n";
	// 	gROOT->ProcessLine(".q");
	// }
	// //output
	// ofstream myfile;
	// myfile.open (Form("./txt/%s-Ac%sCorrected-PolResults-%i_%i_%i_%ibins%s.txt",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,Nc,fid.c_str()));





	
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
			
	TCanvas *cPol[Nd];
	Double_t x[Np] = {0}, y[Np] = {0};
	Double_t ex[Np] = {0}, ey[Np] = {0};
	vector<double> xx;
	vector<double> yy;
	vector<double> exx;
	vector<double> eyy;
	
	vector<double> xxx;
	vector<double> yyy;
	vector<double> exxx;
	vector<double> eyyy;
	
	
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
	for (int d = 0; d < Nd; d++)
	{
		cancount=1;
		cPol[d] = new TCanvas(Form("cPol%s",Axis[d]),Form("cPol%s",Axis[d]),1200,1000);
		cPol[d]->Divide(Nb,Nc);
		for (int c = 0; c < Nc; c++)
		{	
			for (int b = 0; b < Nb; b++)
			{
				for (int p=0; p < Np; p++)
				{						
					if ( (COUNTcor[b][c][d][p] > 100) && (eCOUNTcor[b][c][d][p] > 0) && (BinCenter[b][c][d][p] != 0)  )
					{
						if ((d == 0 && BinCenter[b][c][d][p] < -1) || (d == 2 && (BinCenter[b][c][d][p] < -1 || BinCenter[b][c][d][p] > 1  ))  )
						{
							cout << "Point out of specified range! exiting. "<<endl;
							exit(1);
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
						cout << "OMITING A POINT: Due to low Count" <<endl;
					}
				}
				

							
				
				//Now fill plotting vectors x,y,ex,ey only for the points not boardering on the fringe
				int size = xx.size();
				for (int p=0; p < size; p++)
				{	
					if ( !(  ((d==0)&&(p==0)) || ((d==1)&&(p==0||p==size-1)) || ((d==2)&&(p==0||p==size-1)) ) )
					{
						xxx.push_back(xx[p]);
						yyy.push_back(yy[p]);
						exxx.push_back(exx[p]);
						eyyy.push_back(eyy[p]);
					}
					else
					{
						cout <<"taking out point boardering on fringe"<<endl;
					}
				}
				size = xxx.size();
				for (int p=0; p < size; p++)
				{
					x[p] = xxx[p];
					y[p] = yyy[p];
					ex[p] = exxx[p];
					ey[p] = eyyy[p];
				}
				
				
				
				
				//clear the cpp std::vector(s) for next binn
				xx.clear();
				yy.clear();
				exx.clear();
				eyy.clear(); 
				xxx.clear();
				yyy.clear();
				exxx.clear();
				eyyy.clear();
	
			///*///			
				//set graph and style it
				TGraphErrors *mygr = new TGraphErrors(size,x,y,ex,ey);
				mygr->SetMinimum(0);
				GraphTop[b][c][d] = mygr->GetHistogram()->GetMaximum();
				mygr->GetXaxis()->SetTitle(Form("  cos(#theta_{#pi^{-}}^{%s})  ",Axis[d]));
				mygr->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f :: %1.2f < cos(#theta_{#Xi}^{cm}) < %1.2f  ",EVal[b],EVal[b+1],XVal[b][c],XVal[b][c+1]));
								
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
				cPol[d]->cd(cancount);
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
	for (int d = 0; d < Nd; d++)
	{
		cancount=1;
		for (int c = 0; c < Nc; c++)
		{	
			for (int b = 0; b < Nb; b++)
			{	
				
				PolSum += Polarization[b][c][d];
				myfile << Polarization[b][c][d] << " " << ePolarization[b][c][d] <<endl;
				
				cPol[d]->cd(cancount);
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

	myfile.close();

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

	for (int d = 0; d < Nd; d++)
	{
		cPol[d]->Print(Form("~/Desktop/Pol%s.eps",Axis[d]));
	}


	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				cout<<"ChiSquared = "<<ChiSquared[b][c][d]<<endl;
			}
		}
	}



//*///
//extra thing to display for lei
	TCanvas *cE=new TCanvas("cE","cE",1200,1000);
	cE->Divide(2,2);
	cancount = 1;
	
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			cE->cd(1);
			cancount += 1;
			storegr[b][c][1]->Draw("A*");
			storetex[b][c][1]->Draw("same");
			storegr[b][c][1]->Draw("A*");
			storetex[b][c][1]->Draw("same");
		}
	}
	
///*///





}




///////////////////////////////////////////////////////////////////////////



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
