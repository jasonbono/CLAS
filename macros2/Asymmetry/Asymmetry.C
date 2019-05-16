/*
Author: Jason Bono
Date: Jun 13 2013
*/

//#include "./Binning/DataEXiBins_1x1.h"
//#include "./Binning/DataEXiBins_1x3.h"
//#include "./Binning/DataEXiBins_2x2.h";
//#include "./Binning/DataEXiBins_2x3.h"

//#include "./Binning/DataEXiBins_2and2.h"
#include "./Binning/DataEXiBins_3and3.h"


#include "/Users/Bono/clas/myDefinitions/Hypersphere.h" 



const int dofit = 0;
//File *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_Xi3.root");
//TTree *tData = (TTree*)fData->Get("v13");

 TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3.root");
 TTree *tData = (TTree*)fData->Get("v15");
// TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_BadPion.root");
// TTree *tData = (TTree*)fData->Get("v13");
//TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v13/2kppim-v13_Basic_UnknownBackground.root");
//TTree *tData = (TTree*)fData->Get("v13");


//TFile *fDataFid = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v15/hadded/2kppim-v15_Basic_Mass3_Fid.root");
//TTree *tData = (TTree*)fDataFid->Get("v15Loose");
//TTree *tData = (TTree*)fDataFid->Get("v15Reg");
//TTree *tData = (TTree*)fDataFid->Get("v15Tight");

/*
TFile *fP = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i8-PosPol-2kppim_Basic_Mass.root");
TTree *tP = (TTree*)fP->Get("gpp2kppim");
TFile *fN = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i8-NegPol-2kppim_Basic_Mass.root");
TTree *tN = (TTree*)fN->Get("gpp2kppim");
//*/

/*
TFile *fP = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t1-t1-PosPolX-2kppim_Basic_Mass.root");
TTree *tP = (TTree*)fP->Get("gpp2kppim");
TFile *fN = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t1-t1-NegPolX-2kppim_Basic_Mass.root");
TTree *tN = (TTree*)fN->Get("gpp2kppim");
//*/

/*
TFile *fP = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t1-t1-PosPolZ-2kppim_Basic_Mass.root");
TTree *tP = (TTree*)fP->Get("gpp2kppim");
TFile *fN = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t1-t1-NegPolZ-2kppim_Basic_Mass.root");
TTree *tN = (TTree*)fN->Get("gpp2kppim");
//*/

/*///
TFile *fP = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t1-t1-PosPolXZ-2kppim_Basic_Mass.root");
TTree *tP = (TTree*)fP->Get("gpp2kppim");
TFile *fN = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t1-t1-NegPolXZ-2kppim_Basic_Mass.root");
TTree *tN = (TTree*)fN->Get("gpp2kppim");
///*/


//TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/i10/SendHome/MC-i10t2-t2-2kppim_Basic_Mass3.root");
//TTree *tMC = (TTree*)fMC->Get("gpp2kppim");


 // TFile *fPgen = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i8-PosPol-gamproot.root");
 // TTree *tPgen = (TTree*)fPgen->Get("GampTree");
 // TFile *fNgen = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i8-NegPol-gamproot.root");
 // TTree *tNgen = (TTree*)fNgen->Get("GampTree");

//TCanvas * c1 = new TCanvas("c1", "c1", 1000, 1000);
//TCanvas * c2 = new TCanvas("c2", "c2", 1000, 1000);


const int minstat = 10;
const int Np = 8; //# of pion bins
const int Nd = 3;  //# of axies x:d=0,z:d=1
const char* Axis[Nd] = {"x","y","z"};
const float alpha = -0.458;
const float ealpha = 0.012;
const float ePhotonPol = 0.015;

//const float beampol = 0.5;
//const float beampol = 1;
//Double_t PhotonPol[Nb][Nc];




void Asymmetry()
{
	StyleUp();
	gROOT->ProcessLine(".L /Users/Bono/clas/scripts/new/BgSubtractedYield.C");
	TFile* fHistos = new TFile("hists.root","RECREATE");
	
	//output
	//ofstream myfile;
	//myfile.open (Form("./txt/CxCz-3and3bins.txt",cchoice.c_str(),cchoiceAC.c_str(),Nk,Nq,Nc,cuts.c_str(),fid.c_str()));
	
	
	//StyleUp();
	//set up helicity
	TCut negHelBin = "hel == 1";
	TCut posHelBin = "hel == -1";
	
	//set up the pion bins
	TCut PiBin[Np][Nd];
	float theta[Np] = {0};
	float angle = -1;
	for (int p=0; p < Np; p++)
	{
		PiBin[p][0] = Form("COS_pi_x > %f && COS_pi_x < %f",angle,angle + 2.0/Np);
		PiBin[p][1] = Form("COS_pi_y > %f && COS_pi_y < %f",angle,angle + 2.0/Np);
		PiBin[p][2] = Form("COS_pi_z > %f && COS_pi_z < %f",angle,angle + 2.0/Np);
		// PiBin[p][0] = Form("cm_COS_pi_x > %f && cm_COS_pi_x < %f",angle,angle + 2.0/Np);
		// PiBin[p][1] = Form("cm_COS_pi_y > %f && cm_COS_pi_y < %f",angle,angle + 2.0/Np);
		// PiBin[p][2] = Form("cm_COS_pi_z > %f && cm_COS_pi_z < %f",angle,angle + 2.0/Np);
		
		float low = angle;
		angle = angle + 2.0/Np;
		float high = angle;
		theta[p] = (low + high)/2.0;
		cout <<"theta = " <<theta[p]<<endl;
		TString temp = PiBin[p][0];
		cout <<temp<<endl;
		temp = PiBin[p][1];
		cout <<temp<<endl;
	}	
	
	//set up the Xilab angle bins
	TCut Xforward = "Xcmtheta <= -0.8";	
	double negN[Nb][Nc][Nd][Np] = {0};
	double posN[Nb][Nc][Nd][Np] = {0};
	double asy[Nb][Nc][Nd][Np] = {0};
	double enegN[Nb][Nc][Nd][Np] = {0};
	double eposN[Nb][Nc][Nd][Np] = {0};
	double easy[Nb][Nc][Nd][Np] = {0};
	vector<double> xx;
	vector<double> yy;
	vector<double> exx;
	vector<double> eyy;
	double x[Np]; //note that the dimention of plotting variables are Np but will endup ploting x pts where x <=Np
	double y[Np];
	double ex[Np];
	double ey[Np];

	TCanvas *cPol[Nd];
	double GraphTop[Nb][Nc][Nd] = {0};
	TGraphErrors *storegr[Nb][Nc][Nd];
	TLatex *storetex[Nb][Nc][Nd];

	// stuff that i dont need now
	// double p0[Nb][Nc][Nd] = {0},p1[Nb][Nc][Nd] = {0};
	// double ep0[Nb][Nc][Nd] = {0},ep1[Nb][Nc][Nd] = {0};
	// double Polarization[Nb][Nc][Nd] = {0};
	// double ePolarization[Nb][Nc][Nd] = {0};
	// double ChiSquared[Nb][Nc][Nd] = {0};	
	
	TH1F *h=new TH1F("h","",100,1.28,1.36);
	TH1F *his[Nb][Nc][Nd][Np];
	for (int d = 0; d < Nd; d++)
	{
		int cancount=1;
		cPol[d] = new TCanvas(Form("cPol%s",Axis[d]),Form("cPol%s",Axis[d]),1500,900);
		cPol[d]->Divide(Nc,Nb);
		ctemp = new TCanvas("temp","",10,10);
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{
				float asytot = 0;
				float negtot = 0;
				float postot = 0;
				for (int p = 0; p < Np; p++)
				{
					ctemp->cd(0);
					his[b][c][d][p] = (TH1F*)h->Clone(Form("h%i%i%i%in",b,c,d,p));
                    
					
					tData->Draw(Form("mlampim>>h%i%i%i%in",b,c,d,p),EXibin[b][c]&&PiBin[p][d]&&negHelBin);
					//PhotonPol[b][c] = 1;
					//tN->Draw(Form("beam>>h%i%i%i%in",b,c,d,p),EXibin[b][c]&&PiBin[p][d]);
					//tNgen->Draw(Form("beam>>h%i%i%i%in",b,c,d,p),EXibin[b][c]&&PiBin[p][d]);					

					if(dofit == 1){
						if(his[b][c][d][p]->GetEntries() > 100){
							negN[b][c][d][p] = GetYield(his[b][c][d][p]);
						}
						else{
							negN[b][c][d][p] = 0;
						}
					}
					else{
						negN[b][c][d][p] = his[b][c][d][p]->GetEntries();	
					}					
					enegN[b][c][d][p] = sqrt(negN[b][c][d][p]);
					his[b][c][d][p]->Write();	
				
					his[b][c][d][p] = (TH1F*)h->Clone(Form("h%i%i%i%ip",b,c,d,p));

					tData->Draw(Form("mlampim>>h%i%i%i%ip",b,c,d,p),EXibin[b][c]&&PiBin[p][d]&&posHelBin);
					//tP->Draw(Form("beam>>h%i%i%i%ip",b,c,d,p),EXibin[b][c]&&PiBin[p][d]);
					//tPgen->Draw(Form("beam>>h%i%i%i%ip",b,c,d,p),EXibin[b][c]&&PiBin[p][d]);

					if(dofit == 1){
						if(his[b][c][d][p]->GetEntries() > 100){
							posN[b][c][d][p] = GetYield(his[b][c][d][p]);
						}
						else{
							posN[b][c][d][p] = 0;
						}
					}
					else{
						posN[b][c][d][p] = his[b][c][d][p]->GetEntries();	
					}
					eposN[b][c][d][p] = sqrt(posN[b][c][d][p]);
					his[b][c][d][p]->Write();
				
					asy[b][c][d][p] = (posN[b][c][d][p] - negN[b][c][d][p])/(posN[b][c][d][p] + negN[b][c][d][p]);
					//define some temporary variables to clean up the error calculation
					float tp = posN[b][c][d][p];
					float tep = eposN[b][c][d][p];
					float tn = negN[b][c][d][p];
					float ten = enegN[b][c][d][p];
					float ta = asy[b][c][d][p];
					float tea =  ( 2/( (tp+tn)*(tp+tn) ) ) * sqrt(tn*tn*tep*tep + tp*tp*ten*ten );
					easy[b][c][d][p] = tea;
					
					//only take acceptable values
					if( (ta != ta)||(tp < minstat)||(tn < minstat) )
					{
						//asy[b][c][d][p] = 0;
						//easy[b][c][d][p] = 0;
						cout << "OMITING A POINT: ";
						cout << "b = "<<b<<" c = "<<c<<" d="<<d<<" p="<<p <<" negN = "<<tn << " posN = " << tp << endl;
						cout << " asy = " <<ta<< " +/- " <<tea << endl <<endl;
					}
					else if( (d == 1)&&(  (p==0)||(p==Np-1)   ))
					{
						//exit(1);
						//take out boundary y points
					}
					else
					{
						negtot += tn;
						postot += tp;
						asytot += ta;
						xx.push_back(theta[p]);
						yy.push_back(ta);
						exx.push_back(0);
						eyy.push_back(tea);					
						
						cout << "b = "<<b<<" c = "<<c<<" d="<<d<<" p="<<p <<" negN = "<<tn << " posN = " << tp << endl;
						cout << " asy = " <<ta<< " +/- " <<tea << endl <<endl;	
					}			
				}
				int npts = xx.size();
				for (int i=0; i < npts; i++)
				{
					x[i] = xx[i];
					y[i] = yy[i];
					ex[i] = exx[i];
					ey[i] = eyy[i];
				}		
				xx.clear();
				yy.clear();
				exx.clear();
				eyy.clear();
								
				cPol[d]->cd(cancount);
				cancount += 1;
				TGraphErrors *mygr = new TGraphErrors(npts,x,y,ex,ey);
				mygr->GetXaxis()->SetLimits(-1, 1);
				mygr->SetMinimum(-1);
				mygr->SetMaximum(1);
				GraphTop[b][c][d] = mygr->GetHistogram()->GetMaximum();
				mygr->GetYaxis()->SetTitle(Form(" Asymmetry ",Axis[d]));
				mygr->GetXaxis()->SetTitle(Form(" cos#theta_{#pi^{-}}^{%s}  ",Axis[d]));
				mygr->GetXaxis()->SetNdivisions(-4);
                mygr->GetYaxis()->SetNdivisions(-4);
                
                mygr->GetXaxis()->SetLabelSize(0.07);
                mygr->GetYaxis()->SetLabelSize(0.07);
                mygr->GetYaxis()->CenterTitle();
                mygr->GetXaxis()->CenterTitle();
                
                
                
                //mygr->GetXaxis()->SetTextFont(72);
                //mygr->GetXaxis()->SetLabelOffset(0.025);
            
                
                //mygr->SetTitleFont(62);
				if(XVal[0][0] == 1000)
				{
					mygr->SetTitle(Form(" %s GeV",EXibinString[b][c]));
				}
				else
				{
					//->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f  &  %1.2f < cos(#theta_{#Xi}^{cm}) < %1.2f  ",EVal[b],EVal[b+1],XVal[b][c],XVal[b][c+1]));
				}
				
				//*///
				TF1 *f1 = new TF1("f1",Form("[0] - %f*%f*[1]*x",alpha,PhotonPol[b][c]),-1,1);
                //TF1 *f1 = new TF1("f1",Form("-%f*%f*[1]*x",alpha,PhotonPol[b][c]),-1,1);
                
                mygr->Fit("f1","EV");
				float Xipol = f1->GetParameter(1);
				float eXipol = f1->GetParError(1);
				float chisqr = f1->GetChisquare();
				mygr->Draw("A*");
				////*////storegr[b][c][d] = mygr;
				
                
                
												
				TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
                mytex=new TLatex(-0.9, 0.7*GraphTop[b][c][d],Form("C_{%s} = %5.3f #pm %5.3f ",Axis[d],Xipol,eXipol));
				mytex->SetTextSize(0.07);
				mytex->SetTextColor(4);
				mytex->Draw("SAME");
				
				TLatex *mytex2=new TLatex(0.0, 0.0,"mytex2");
				mytex2=new TLatex(-0.9, 0.45*GraphTop[b][c][d],Form("#frac{#sigma^{2}}{ndf} = %5.3f ",chisqr/npts));
				mytex2->SetTextSize(0.07);
				mytex2->SetTextColor(1);
				//mytex2->Draw("SAME");

				TLatex *mytex3=new TLatex(0.0, 0.0,"mytex3");
				mytex3=new TLatex(-0.9, 0.25*GraphTop[b][c][d],Form("tot-asym = %5.3f ",asytot));
				mytex3->SetTextSize(0.07);
				mytex3->SetTextColor(3);
				//mytex3->Draw("SAME");
				
				TLatex *mytex4=new TLatex(0.0, 0.0,"mytex3");
				mytex4=new TLatex(-0.9, 0.1*GraphTop[b][c][d],Form("n- =%5.3f n+ =%5.3f  ",negtot,postot));
				mytex4->SetTextSize(0.07);
				mytex4->SetTextColor(15);
				//mytex4->Draw("SAME");
							


             
               
             
                
			}	
		}
	}
	ctemp->cd(0);
}



StyleUp()
{
	gStyle->SetTitleXOffset(0.75);
	gStyle->SetTitleYOffset(0.8);
	gStyle->SetTitleSize(0.07);
	gStyle->SetTitleYSize(0.07);
	gStyle->SetPadTopMargin(0.12);
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
    gStyle->SetLabelSize(0.045, "XY");
}
