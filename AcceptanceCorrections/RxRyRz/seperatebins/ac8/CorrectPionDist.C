/*
Name: MakeGraphPol.C
Author: Jason Bono
Date: Jun 12 2013
Purpose: Fourth step. Output the Ac corrected pion distributions as a txt file AND TGraph objects in a root file. 
the txt file

Input: %s-Basic-Mass-Ac%s-%ibins.root
Output: %s-Ac%sCorrected-%ibins.root,  %s-Ac%sCorrected-%ibins.txt
*/

//#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "./DataEXiBins.h"
//#include "./1DataBin.h" 


#include "./SimEXiBins.h"
#include "./Fringe.h"

void CorrectPionDist()
{

	StyleUp();

	//Some important declarations 
	const int Nb = 2,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis		
	//const int Nc = 2;

	const int Np = 12; //number of pion bins
	int Nk = 60; //# of pion bins used to get the acceptance parameters
//	const int Nq = 20; //number of energy and Xi bins for acceptance corrections
	
	const char* BinType[Nb] = {"E","Xi"};
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
	TFile *file = TFile::Open(Form("./NewRootFiles/%sAc%s-%i_%ibins_%s%s.root",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nq,cuts.c_str(),fid.c_str()));
	TTree *tOriginal = (TTree*)file->Get("New");
	//output
	TFile* fPolHistos = new TFile(Form("./hists/%sAc%sCorrected-%i_%i_%ibins_%s%s.root",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nq,Nc,cuts.c_str(),fid.c_str()),"RECREATE");
	ofstream myfile;
	myfile.open (Form("./txt/%sAc%sCorrected-%i_%i_%ibins_%s%s.txt",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nq,Nc,cuts.c_str(),fid.c_str()));

	//old branches
	float beam=0, Xcmtheta=0;
	float COS_pi_x, COS_pi_y, COS_pi_z;
	float REx, REy, REz;
	float RXix, RXiy, RXiz;
	float eREx, eREy, eREz;
	float eRXix, eRXiy, eRXiz;
	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("Xcmtheta", &Xcmtheta);
	tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);	
	//unified efficenancy branches
	tOriginal->SetBranchAddress("REx", &REx);
	tOriginal->SetBranchAddress("REy", &REy);
	tOriginal->SetBranchAddress("REz", &REz);
	tOriginal->SetBranchAddress("RXix", &RXix);
	tOriginal->SetBranchAddress("RXiy", &RXiy);
	tOriginal->SetBranchAddress("RXiz", &RXiz);
	tOriginal->SetBranchAddress("eREx", &eREx);
	tOriginal->SetBranchAddress("eREy", &eREy);
	tOriginal->SetBranchAddress("eREz", &eREz);
	tOriginal->SetBranchAddress("eRXix", &eRXix);
	tOriginal->SetBranchAddress("eRXiy", &eRXiy);
	tOriginal->SetBranchAddress("eRXiz", &eRXiz);
	
	//histograms to plot the results
	TH1D *h=new TH1D("h","",Np,-1.0,1.0);
	TH1D *hPol[Nb][Nc][Nd];
	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				hPol[b][c][d] = (TH1D*)h->Clone(Form("hAc2-%sBin%i-PiAxis%s",BinType[b],c,Axis[d]));
			}
		}
	}

	float X[Nd] = {0};
	float R[Nb][Nd] = {0};
	float eR[Nb][Nd] = {0};
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
	Float_t varX[Nb],varY[Nd];
	/////////////////////////////  . . . . . . . . . . . . . . . .FIRST LOOP. . . . . . . . . . . . . ////////////////////////////////////////////////
	Int_t nentries = (Int_t)tOriginal->GetEntries(); 
	for (int i=0; i<nentries; i++) 
	{
		tOriginal->GetEntry(i);
		
		
		//get the angles
		X[0] = COS_pi_x;
		X[1] = COS_pi_y;
		X[2] = COS_pi_z;
		
		varY[0] = COS_pi_x;
		varY[1] = COS_pi_y;
		varY[2] = COS_pi_z;
		varX[0] = beam;
		varX[1] = Xcmtheta;
		
		//get the R factor
		R[0][0] = REx;
		R[0][1] = REy;
		R[0][2] = REz;
		R[1][0] = RXix;
		R[1][1] = RXiy;
		R[1][2] = RXiz;
		eR[0][0] = eREx;
		eR[0][1] = eREy;
		eR[0][2] = eREz;
		eR[1][0] = eRXix;
		eR[1][1] = eRXiy;
		eR[1][2] = eRXiz;

		//define the binning of the corrected distributions
		bool cut_Angle[Nd][Np];
		float BinAngle = -1;
		for (int p=0; p < Np; p++)
		{
			cut_Angle[0][p] = COS_pi_x > BinAngle && COS_pi_x < BinAngle + 2.0/Np;
			cut_Angle[1][p] = COS_pi_y > BinAngle && COS_pi_y < BinAngle + 2.0/Np;
			cut_Angle[2][p] = COS_pi_z > BinAngle && COS_pi_z < BinAngle + 2.0/Np;
			BinAngle = BinAngle + 2.0/Np;
		}
		//EXiBins in bool form
		bool cut_EXiBin[Nb][Nc];
		for (int c=0; c < Nc; c++)
		{
			cut_EXiBin[0][c] = beam > EVal[c] && beam < EVal[c+1];
			cut_EXiBin[1][c] = Xcmtheta > XVal[c] && Xcmtheta < XVal[c+1];
		}
/*		
		cut_EXiBin[0][0] = beam > EXiParameterA && beam < EXiParameterB;
		cut_EXiBin[0][1] = beam > EXiParameterB && beam < EXiParameterC;
		cut_EXiBin[0][2] = beam > EXiParameterC && beam < EXiParameterD;			
		cut_EXiBin[1][0] = Xcmtheta > EXiParameterE && Xcmtheta < EXiParameterF;
		cut_EXiBin[1][1] = Xcmtheta > EXiParameterF && Xcmtheta < EXiParameterG;
		cut_EXiBin[1][2] = Xcmtheta > EXiParameterG && Xcmtheta < EXiParameterH;
///*///	
		//count everything
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				for (int d = 0; d < Nd; d++)
				{
					for (int p=0; p < Np; p++)
					{
						if (cut_Angle[d][p])  //sort out the pion binning.
						{
							if ( (cut_EXiBin[b][c]) )  //sort out EXi binning.
							{	
								bool fill = NoFringe_smart(varX[b],varY[d],b,d);
								//fill = true;
								if(fill)
								{
									if ( (R[b][d] > 0) && (R[b][d] < 1) ) //only take events with reasonable acceptance
									{					
										//vertical value, also used for horizantal value (bin center)
										COUNTcor[b][c][d][p] += (1/R[b][d]);
										
										//first step for horizontal value and error bars
										Moment1[b][c][d][p] += X[d]/R[b][d];
									
										//first step for vertical error bars 
										SumR[b][c][d][p] += R[b][d];
										SumeR[b][c][d][p] += eR[b][d];
										COUNT[b][c][d][p] += 1;
									
										//the new way to calculate errors
										eCOUNTcor_squared[b][c][d][p] += ( (eR[b][d]/(R[b][d]*R[b][d]))*(eR[b][d]/(R[b][d]*R[b][d])) );
										
										//first step in raue count
										rauecunt[b][c][d][p] += (1/(R[b][d]*eR[b][d]));
										Sum_Recip_eR[b][c][d][p] += (1/eR[b][d]);
										
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
						eCOUNTcor[b][c][d][p] = COUNTcor[b][c][d][p]*sqrt(    (1/COUNT[b][c][d][p])  +   (AvgeR[b][c][d][p]/AvgR[b][c][d][p])*(AvgeR[b][c][d][p]/AvgR[b][c][d][p]) );
						hPol[b][c][d]->SetBinError(p+1,eCOUNTcor[b][c][d][p]);
						eCOUNTcor_new[b][c][d][p] = sqrt(eCOUNTcor_squared[b][c][d][p]); //wrong way
						eCOUNTcor_new[b][c][d][p] = sqrt(COUNTcor[b][c][d][p])*(AvgeR[b][c][d][p]/AvgR[b][c][d][p]*AvgR[b][c][d][p]); //yet another wrong way
						
						
						//eCOUNTcor[b][c][d][p] = eCOUNTcor_new[b][c][d][p];
												
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
		X[0] = COS_pi_x;
		X[1] = COS_pi_y;
		X[2] = COS_pi_z;		
		
		R[0][0] = REx;
		R[0][1] = REy;
		R[0][2] = REz;
		R[1][0] = RXix;
		R[1][1] = RXiy;
		R[1][2] = RXiz;
		eR[0][0] = eREx;
		eR[0][1] = eREy;
		eR[0][2] = eREz;
		eR[1][0] = eRXix;
		eR[1][1] = eRXiy;
		eR[1][2] = eRXiz;				

		//set up the pion binning for the data
		bool cut_Angle[Nd][Np];
		float BinAngle = -1;
		for (int p=0; p < Np; p++)
		{
			cut_Angle[0][p] = COS_pi_x > BinAngle && COS_pi_x < BinAngle + 2.0/Np;
			cut_Angle[1][p] = COS_pi_y > BinAngle && COS_pi_y < BinAngle + 2.0/Np;
			cut_Angle[2][p] = COS_pi_z > BinAngle && COS_pi_z < BinAngle + 2.0/Np;
			BinAngle = BinAngle + 2.0/Np;
		}
		//EXiBins in bool form
		bool cut_EXiBin[Nb][Nc];
		for (int c=0; c < Nc; c++)
		{
			cut_EXiBin[0][c] = beam > EVal[c] && beam < EVal[c+1];
			cut_EXiBin[1][c] = Xcmtheta > XVal[c] && Xcmtheta < XVal[c+1];
		}
		
/*		
		cut_EXiBin[0][0] = beam > EXiParameterA && beam < EXiParameterB;
		cut_EXiBin[0][1] = beam > EXiParameterB && beam < EXiParameterC;
		cut_EXiBin[0][2] = beam > EXiParameterC && beam < EXiParameterD;			
		cut_EXiBin[1][0] = Xcmtheta > EXiParameterE && Xcmtheta < EXiParameterF;
		cut_EXiBin[1][1] = Xcmtheta > EXiParameterF && Xcmtheta < EXiParameterG;
		cut_EXiBin[1][2] = Xcmtheta > EXiParameterG && Xcmtheta < EXiParameterH;
///*///		

		
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				for (int d = 0; d < Nd; d++)
				{
					for (int p=0; p < Np; p++)
					{
						if (cut_Angle[d][p])
						{
							if ( (cut_EXiBin[b][c]) ) 
							{	
								bool fill = NoFringe_smart(varX[b],varY[d],b,d);
								//fill = true;
								if(fill)
								{
									if ( (R[b][d] > 0) && (R[b][d] < 1) ) //only take events with reasonable acceptance
									{					
										//second step for horizontal error bars
										Moment2[b][c][d][p] += (X[d] - BinCenter[b][c][d][p])*(X[d] - BinCenter[b][c][d][p])/R[b][d];	
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

/*
		TGraphErrors GraphPol[Nb][Nc][Nd];
		
		
		float x[Np],y[Np],ex[Np],ey[Np];
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{	
				for (int d = 0; d < Nd; d++)
				{
				
					GraphPol[b][c][d] =  TGraphErrors(Np,BinCenter[b][c][d],COUNTcor[b][c][d],eBinCenter[b][c][d],eCOUNTcor[b][c][d]);
					
				}
			}
		}
		//GraphPol[0][0][0].Draw("A");
		
		
		float x[Np],y[Np],ex[Np],ey[Np];
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{	
				for (int d = 0; d < Nd; d++)
				{
					for (int p=0; p < Np; p++)
					{
				
						x[p] = BinCenter[b][c][d][p];
						y[p] = COUNTcor[b][c][d][p];
						ex[p] = eBinCenter[b][c][d][p];
						ey[p] = eCOUNTcor[b][c][d][p];
					}	
				}
			}
		}
		
		
		TCanvas *cPol=new TCanvas("cPol","cPol",800,600);
		//cPol->Divide(2,2);
		//cPol->cd(1);
		//TGraph *GraphPol2 = new TGraphErrors(Np,x,y,ex,ey);
		float xx[2] = {1,4}, yy[2] = {11,9}, exx[2] = {0} , eyy[2] = {0};
		TGraph *GraphPol2 = new TGraphErrors(2,xx,yy,exx,eyy);

		
		GraphPol2->Draw("A");
	*/
	
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
					gr->Write(Form("gr%s%i-%s",BinType[b],c,Axis[d]));
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








