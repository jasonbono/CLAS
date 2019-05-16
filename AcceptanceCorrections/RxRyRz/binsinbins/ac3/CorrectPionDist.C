/*
Name: CorrectPionDist.C
Author: Jason Bono
Date: Jun 12 2013
Purpose: Fourth step. Output the Ac corrected pion distributions as a txt file AND TGraph objects in a root file. 
the txt file

Input: %s-Basic-Mass-Ac%s-%ibins.root
Output: %s-Ac%sCorrected-%ibins.root,  %s-Ac%sCorrected-%ibins.txt
*/

//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"


//#include "./DataEXiBins.h"
#include "./OneDataBin.h"
//#include "./Fringe.h"
#include "./FringeOneDataBin.h"
#include "./SimEXiBins.h"
#include "./constants.h"
#include "./Pionbins.h"

void CorrectPionDist()
{

	StyleUp();

	const char* Axis[Nd] = {"x","y","z"};
	
	//interactively choose Data or Simulation
	cout << "enter file choice (Data, NoPol,  PosPol or NegPol):";
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
	
	if ( (cchoiceAC.compare("NoPol") != 0) && (cchoiceAC.compare("PosPol") != 0) && (cchoiceAC.compare("NegPol") != 0) )
	{
		cout << "incorect of choice of AC. quiting" <<endl;
		gROOT->ProcessLine(".q");
	}
	
	
	
	//input	
	TFile *file = TFile::Open(Form("./NewRootFiles/%sAc%s-%i_%i_%ibins_%s%s.root",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nbq,Ncq,cuts.c_str(),fid.c_str()));
	TTree *tOriginal = (TTree*)file->Get("New");
	//output
	TFile* fPolHistos = new TFile(Form("./hists/%sAc%sCorrected-%i_%i_%i_%ibins_%s%s.root",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nbq,Ncq,Nc,cuts.c_str(),fid.c_str()),"RECREATE");
	ofstream myfile;
	myfile.open (Form("./txt/%sAc%sCorrected-%i_%i_%i_%ibins_%s%s.txt",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nbq,Ncq,Nc,cuts.c_str(),fid.c_str()));
	
	
	
	
	// //input
	// TFile *file = TFile::Open(Form("./NewRootFiles/%s-Basic-Mass-Ac%s-%i_%i_%ibins%s.root",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,fid.c_str()));
	// TTree *tOriginal = (TTree*)file->Get("New");
	// //output
	// TFile* fPolHistos = new TFile(Form("./hists/%s-Ac%sCorrected-%i_%i_%i_%ibins%s.root",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,Nc,fid.c_str()),"RECREATE");
	// ofstream myfile;
	// myfile.open (Form("./txt/%s-Ac%sCorrected-%i_%i_%i_%ibins%s.txt",choice.c_str(),choiceAC.c_str(),Nk,Nbq,Ncq,Nc,fid.c_str()));

	//old branches
	float beam=0, Xcmtheta=0;
	float COS_pi_x, COS_pi_y, COS_pi_z;
	float Rx, Ry, Rz;
	float eRx, eRy, eRz;
	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("Xcmtheta", &Xcmtheta);
	tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);	
	tOriginal->SetBranchAddress("Rx", &Rx);
	tOriginal->SetBranchAddress("Ry", &Ry);
	tOriginal->SetBranchAddress("Rz", &Rz);
	tOriginal->SetBranchAddress("eRx", &eRx);
	tOriginal->SetBranchAddress("eRy", &eRy);
	tOriginal->SetBranchAddress("eRz", &eRz);

	//histograms to plot the results
	TH1D *h=new TH1D("h","",Np,-1.0,1.0);
	TH1D *hPol[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				hPol[b][c][d] = (TH1D*)h->Clone(Form("hAc2-EBin%i-XBin%i-Axis%s",b,c,Axis[d]));
			}
		}
	}


	float R[Nd] = {0};
	float eR[Nd] = {0};
	float SumR[Nb][Nc][Nd][Np] = {0}, AvgR[Nb][Nc][Nd][Np] = {0};
	float SumeR[Nb][Nc][Nd][Np] = {0}, AvgeR[Nb][Nc][Nd][Np] = {0};
	
	float COUNT[Nb][Nc][Nd][Np] = {0};
	float COUNTcor[Nb][Nc][Nd][Np] = {0};
	float eCOUNTcor[Nb][Nc][Nd][Np] = {0};
	float eCOUNTcor_squared[Nb][Nc][Nd][Np] = {0};
	float eCOUNTcor_new[Nb][Nc][Nd][Np] = {0};
	
	float BinCenter[Nb][Nc][Nd][Np] = {0},  Moment1[Nb][Nc][Nd][Np] = {0};
	float eBinCenter[Nb][Nc][Nd][Np] = {0},  Moment2[Nb][Nc][Nd][Np] = {0};
	
	float rauecunt[Nb][Nc][Nd][Np] = {0};
	float Sum_Recip_eR[Nb][Nc][Nd][Np] = {0};
	//declare varibles to call NoFringe()
	Float_t X,Y;
	Float_t Z[Nd];
	/////////////////////////////  . . . . . . . . . . . . . . . .FIRST LOOP. . . . . . . . . . . . . ////////////////////////////////////////////////
	Int_t nentries = (Int_t)tOriginal->GetEntries(); 
	for (int i=0; i<nentries; i++) 
	{
		tOriginal->GetEntry(i);
		
		//fill the variables
		X = beam;
		Y = Xcmtheta;
		Z[0] = COS_pi_x;
		Z[1] = COS_pi_y;
		Z[2] = COS_pi_z;
		//get the R factor
		R[0] = Rx;
		R[1] = Ry;
		R[2] = Rz;
		eR[0] = eRx;
		eR[1] = eRy;
		eR[2] = eRz;



		//*///pion bins with equal distance in bool form
		bool cut_Angle[Nb][Nc][Nd][Np];
		for (int b=0; b < Nb; b++)
		{
			for (int c=0; c < Nc; c++)
			{
				float BinAngle = -1;
				for (int p=0; p < Np; p++)
				{
					//cout << "low = " << BinAngle << "   high = "<< BinAngle + 2.0/Np <<endl;
					
					cut_Angle[b][c][0][p] = COS_pi_x > BinAngle && COS_pi_x < BinAngle + 2.0/Np;
	 				cut_Angle[b][c][1][p] = COS_pi_y > BinAngle && COS_pi_y < BinAngle + 2.0/Np;
		 			cut_Angle[b][c][2][p] = COS_pi_z > BinAngle && COS_pi_z < BinAngle + 2.0/Np;
		 			BinAngle = BinAngle + 2.0/Np;
					
				}
			}
		}
		//exit(1);
		///*///
		
		

		
		
		/*/////pion bins with equal statistics in bool form
		bool cut_Angle[Nb][Nc][Nd][Np];
		for (int b=0; b < Nb; b++)
		{
			for (int c=0; c < Nc; c++)
			{
				for (int p=0; p < Np; p++)
				{	
					cout << "bcdp" <<b<<c<<0<<p<<endl; 
					cout << "low = " << PiVal[b][c][0][p] << "   high = "<< PiVal[b][c][0][p+1] <<endl;
					cut_Angle[b][c][0][p] = COS_pi_x > PiVal[b][c][0][p]  && COS_pi_x < PiVal[b][c][0][p+1];
					cut_Angle[b][c][1][p] = COS_pi_y > PiVal[b][c][1][p]  && COS_pi_y < PiVal[b][c][1][p+1];
					cut_Angle[b][c][2][p] = COS_pi_z > PiVal[b][c][2][p]  && COS_pi_z < PiVal[b][c][2][p+1];
				}
			}
		}
		exit(1);
		///*////
		
				
		
		//EXiBins with equal statistics in bool form
		bool cut_EBin[Nb];
		bool cut_XiBin[Nb][Nc];
		bool cut_EXiBin[Nb][Nc];
		for (int b=0; b < Nb; b++)
		{
			cut_EBin[b] = beam >= EVal[b] && beam < EVal[b+1];
			for (int c=0; c < Nc; c++)
			{
				cut_XiBin[b][c] = Xcmtheta >= XVal[b][c] && Xcmtheta < XVal[b][c+1];
				cut_EXiBin[b][c] = cut_EBin[b]  && cut_XiBin[b][c];
			}
		}

		//count everything
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				for (int d = 0; d < Nd; d++)
				{
					for (int p=0; p < Np; p++)
					{
						if (cut_Angle[b][c][d][p])  //sort out the pion binning.
						{
							if ( (cut_EXiBin[b][c]) )  //sort out EXi binning.
							{	
								bool fill = NoFringe_6bins(X,Y,Z[d],d);
								//bool fill = true;
								if(fill)
								{
									if ( (R[d] > 0) && (R[d] < 1) ) //only take events with reasonable acceptance
									{					
										//vertical value, also used for horizantal value (bin center)
										COUNTcor[b][c][d][p] += (1/R[d]);
										
										//first step for horizontal value and error bars
										Moment1[b][c][d][p] += Z[d]/R[d];
									
										//first step for vertical error bars 
										SumR[b][c][d][p] += R[d];
										SumeR[b][c][d][p] += eR[d];
										COUNT[b][c][d][p] += 1;
									
										//the new way to calculate errors
										eCOUNTcor_squared[b][c][d][p] += ( (eR[d]/(R[d]*R[d]))*(eR[d]/(R[d]*R[d])) );
										
										//first step in raue count
										rauecunt[b][c][d][p] += (1/(R[d]*eR[d]));
										Sum_Recip_eR[b][c][d][p] += (1/eR[d]);
										
										/*									
										cout << "- - - -  b = "<<b<<", c = "<<c<<", d = "<<d<<", p = "<<p<<" - - - - "<<endl;
										cout << "COUNT = " << COUNT[b][c][d][p] << "   COUNTcor = " << COUNTcor[b][c][d][p] <<endl;
										cout << "Moment1 = " << Moment1[b][c][d][p] <<endl;
										*/
									//	cout <<"good"<<endl;
									}	
									else 
									{
										cout <<"event rejected: Bad Acceptance"<<endl;
									}
								}
								else
								{
									cout <<"event rejected: Fringe Event"<<endl;
								}
							}							
						}		
					}
				}		
			}
		}


	} //finish first loop over events	
	
	//Do first order calculations before second loop
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p < Np; p++)
				{
					
					//filter good bins
					//if ( COUNT[b][c][d][p] > 1 )
					if (COUNTcor[b][c][d][p] > 1 && COUNT[b][c][d][p] > 1)
					{
						//set the vertical value
						hPol[b][c][d]->SetBinContent(p+1,COUNTcor[b][c][d][p]);
	
						//set the vertical error
						AvgR[b][c][d][p] = SumR[b][c][d][p]/COUNT[b][c][d][p];
						AvgeR[b][c][d][p] = SumeR[b][c][d][p]/COUNT[b][c][d][p];
						eCOUNTcor[b][c][d][p] = COUNTcor[b][c][d][p]*sqrt(    (1/COUNT[b][c][d][p])  +   (AvgeR[b][c][d][p]/AvgR[b][c][d][p])*(AvgeR[b][c][d][p]/AvgR[b][c][d][p])    );
						hPol[b][c][d]->SetBinError(p+1,eCOUNTcor[b][c][d][p]);
						eCOUNTcor_new[b][c][d][p] = sqrt(eCOUNTcor_squared[b][c][d][p]);
												
						//find and set the bin center
						BinCenter[b][c][d][p] = Moment1[b][c][d][p]/COUNTcor[b][c][d][p];
						AvgR[b][c][d][p] = SumR[b][c][d][p]/COUNT[b][c][d][p];
						AvgeR[b][c][d][p] = SumeR[b][c][d][p]/COUNT[b][c][d][p];
						
						//compute the raue count
						rauecunt[b][c][d][p] = rauecunt[b][c][d][p]/Sum_Recip_eR[b][c][d][p];
						
					}
					else
					{
						hPol[b][c][d]->SetBinContent(p+1,0);
						AvgR[b][c][d][p] = 0;
						AvgeR[b][c][d][p] = 0;
						eCOUNTcor[b][c][d][p] = 0;
						BinCenter[b][c][d][p] = 0;
						AvgR[b][c][d][p] = 0;
						AvgeR[b][c][d][p] = 0;
						
						cout <<"Prob 3" <<endl;
						cout << "- - - -  b = "<<b<<", c = "<<c<<", d = "<<d<<", p = "<<p<<" - - - - "<<endl;
						cout << "COUNT = " << COUNT[b][c][d][p] << "   COUNTcor = " << COUNTcor[b][c][d][p] << endl;
						cout << "Moment1 = " << Moment1[b][c][d][p] <<endl;
						cout <<endl;
					}					

				}

			}
		}		
	}

	/////////////////////////////  . . . . . . . . . . . . . . . .SECOND LOOP. . . . . . . . . . . . . ////////////////////////////////////////////////
	for (int i=0; i<nentries; i++) 
	{
		tOriginal->GetEntry(i);
				
		//fill the variables
		X = beam;
		Y = Xcmtheta;
		Z[0] = COS_pi_x;
		Z[1] = COS_pi_y;
		Z[2] = COS_pi_z;
		
		//get the R factor
		R[0] = Rx;
		R[1] = Ry;
		R[2] = Rz;
		eR[0] = eRx;
		eR[1] = eRy;
		eR[2] = eRz;
		
		
		//*///pion bins with equal distance in bool form
		bool cut_Angle[Nb][Nc][Nd][Np];
		for (int b=0; b < Nb; b++)
		{
			for (int c=0; c < Nc; c++)
			{
				float BinAngle = -1;
				for (int p=0; p < Np; p++)
				{
					//cout << "low = " << BinAngle << "   high = "<< BinAngle + 2.0/Np <<endl;
					cut_Angle[b][c][0][p] = COS_pi_x > BinAngle && COS_pi_x < BinAngle + 2.0/Np;
	 				cut_Angle[b][c][1][p] = COS_pi_y > BinAngle && COS_pi_y < BinAngle + 2.0/Np;
		 			cut_Angle[b][c][2][p] = COS_pi_z > BinAngle && COS_pi_z < BinAngle + 2.0/Np;
		 			BinAngle = BinAngle + 2.0/Np;	
				}
			}
		}
		//exit(1);
		///*///
		

	
		/*/////pion bins with equal statistics in bool form
		bool cut_Angle[Nb][Nc][Nd][Np];
		for (int b=0; b < Nb; b++)
		{
			for (int c=0; c < Nc; c++)
			{
				for (int p=0; p < Np; p++)
				{	
					cout << "bcdp" <<b<<c<<0<<p<<endl; 
					cout << "low = " << PiVal[b][c][0][p] << "   high = "<< PiVal[b][c][0][p+1] <<endl;
					cut_Angle[b][c][0][p] = COS_pi_x > PiVal[b][c][0][p]  && COS_pi_x < PiVal[b][c][0][p+1];
					cut_Angle[b][c][1][p] = COS_pi_y > PiVal[b][c][1][p]  && COS_pi_y < PiVal[b][c][1][p+1];
					cut_Angle[b][c][2][p] = COS_pi_z > PiVal[b][c][2][p]  && COS_pi_z < PiVal[b][c][2][p+1];
				}
			}
		}
		exit(1);
		///*////
		
		
		
		
		//EXiBins in bool form
		bool cut_EBin[Nb];
		bool cut_XiBin[Nb][Nc];
		bool cut_EXiBin[Nb][Nc];
		for (int b=0; b < Nb; b++)
		{
			cut_EBin[b] = beam >= EVal[b] && beam < EVal[b+1];
			for (int c=0; c < Nc; c++)
			{
				cut_XiBin[b][c] = Xcmtheta >= XVal[b][c] && Xcmtheta < XVal[b][c+1];
				cut_EXiBin[b][c] = cut_EBin[b]  && cut_XiBin[b][c];
			}
		}
				
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				for (int d = 0; d < Nd; d++)
				{
					for (int p=0; p < Np; p++)
					{
						if (cut_Angle[b][c][d][p])
						{
							if ( (cut_EXiBin[b][c]) ) 
							{	
								bool fill = NoFringe_6bins(X,Y,Z[d],d);
								//bool fill = true;
								if(fill)
								{
									if ( (R[d] > 0) && (R[d] < 1) ) //only take events with reasonable acceptance
									{					
										//second step for horizontal error bars
										Moment2[b][c][d][p] += (Z[d] - BinCenter[b][c][d][p])*(Z[d] - BinCenter[b][c][d][p])/R[d];	
									}
								}
							}
						}		
					}
				}		
			}
		}



	} //end of second loop


	//do the second order calculations
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p < Np; p++)
				{
					//filter good bins
					//if ( COUNT[b][c][d][p] > 1 )
					if (COUNTcor[b][c][d][p] > 1 && COUNT[b][c][d][p] > 1)
					{					
						eBinCenter[b][c][d][p] = sqrt(Moment2[b][c][d][p]/COUNTcor[b][c][d][p]);
						eBinCenter[b][c][d][p] = 0;
						cout << "- - - -  b = "<<b<<", c = "<<c<<", d = "<<d<<", p = "<<p<<" - - - - "<<endl;
						cout << "COUNT = " << COUNT[b][c][d][p] << "   COUNTcor = " << COUNTcor[b][c][d][p] << "   eCOUNTcor = " << eCOUNTcor[b][c][d][p]<< "   eCOUNTcor_new = " << eCOUNTcor_new[b][c][d][p]  <<endl;
						cout << "   relerror = " << eCOUNTcor[b][c][d][p]/COUNTcor[b][c][d][p]<< "   relerror = " << eCOUNTcor_new[b][c][d][p]/COUNTcor[b][c][d][p]<< endl;
						cout << "   ratio of errors = " << eCOUNTcor[b][c][d][p]/eCOUNTcor_new[b][c][d][p]<<endl;
						cout << "Moment1 = " << Moment1[b][c][d][p] << "  BinCenter = " << BinCenter[b][c][d][p] << endl;
						cout << "Moment2 = " << Moment2[b][c][d][p] << "  eBinCenter = " << eBinCenter[b][c][d][p] << endl;
						cout <<endl;
					}
					else
					{
						eBinCenter[b][c][d][p] = 0;
						eBinCenter[b][c][d][p] = 0;
					}
				}
				hPol[b][c][d]->SetMinimum(0);
				hPol[b][c][d]->Write();
			}
		}		
	}


	//make the graphs
	Double_t x[Np] = {0}, y[Np] = {0};
	Double_t ex[Np] = {0}, ey[Np] = {0};
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				for (int p=0; p < Np; p++)
				{
					//filter good bins
					//if ( COUNT[b][c][d][p] > 1 )
					if (COUNTcor[b][c][d][p] > 1 && COUNT[b][c][d][p] > 1)
					{					
						x[p] = BinCenter[b][c][d][p];
						y[p] = COUNTcor[b][c][d][p];
						//y[p] = rauecunt[b][c][d][p];
						ex[p] = eBinCenter[b][c][d][p];
						ey[p] = eCOUNTcor[b][c][d][p];
						//ey[p] = eCOUNTcor_new[b][c][d][p];
						//ey[p] = 0;
 					}
					else
					{
						x[p] = 0;
						y[p] = 0;
						ex[p] = 0;
						ey[p] = 0;
					}
					cout << x[p] << " " << y[p] << " " <<ex[p] << " " << ey[p] <<endl;
					myfile  << x[p] << " " << y[p] << " " <<ex[p] << " " << ey[p] <<endl;
				}
				TGraphErrors *gr = new TGraphErrors(Np,x,y,ex,ey);
				gr->SetMinimum(0);
				gr->Write(Form("gr-EBin%i-XBin%i-Axis%s",b,c,Axis[d]));
			}
		}
	}
	
 	gROOT->ProcessLine(".q");
}




//////////////////////////////////////////////////////////////////////////////

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
	gStyle->SetOptStat(1);
	gStyle->SetOptFit();
}








