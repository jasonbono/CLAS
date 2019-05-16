/*
Author: Jason Bono
Date: March 4 2014
*/
 

TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v09/2kppim-v09_Basic_Mass.root");
TTree *tData = (TTree*)fData->Get("v09");

TFile *fMC = TFile::Open("/Users/Bono/clas/rootfiles/LINKS/MC-i9t4-t5-NoPol-2kppim_Basic_Mass.root");
TTree *tMC = (TTree*)fMC->Get("gpp2kppim");


void TestBoost()
{

tMC->Draw("COS_pi_x + COS_lam_x>>h");



















	

}



// 
// 
// void nothing(){
// 	
// 	
// 	
// 	
// 	
// 	//set up the pion bins
// 	TCut PiBin[Np][Nd];
// 	float theta[Np] = {0};
// 	float angle = -1;
// 	for (int p=0; p < Np; p++)
// 	{	
// 		PiBin[p][0] = Form("COS_pi_x > %f && COS_pi_x < %f",angle,angle + 2.0/Np);
// 		PiBin[p][1] = Form("COS_pi_z > %f && COS_pi_z < %f",angle,angle + 2.0/Np);
// 		float low = angle;
// 		angle = angle + 2.0/Np;
// 		float high = angle;
// 		theta[p] = (low + high)/2.0;
// 		cout <<"theta = " <<theta[p]<<endl;
// 		TString temp = PiBin[p][0];
// 		cout <<temp<<endl;
// 		temp = PiBin[p][1];
// 		cout <<temp<<endl;
// 	}	
// 	double negN[Nb][Nc][Nd][Np] = {0};
// 	double posN[Nb][Nc][Nd][Np] = {0};
// 	double asy[Nb][Nc][Nd][Np] = {0};
// 	double enegN[Nb][Nc][Nd][Np] = {0};
// 	double eposN[Nb][Nc][Nd][Np] = {0};
// 	double easy[Nb][Nc][Nd][Np] = {0};
// 	vector<double> xx;
// 	vector<double> yy;
// 	vector<double> exx;
// 	vector<double> eyy;
// 	double x[Np]; //note that the dimention of plotting variables are Np but will endup ploting x pts where x <=Np
// 	double y[Np]; 
// 	double ex[Np]; 
// 	double ey[Np]; 
// 	
// 	
// 	TCanvas *cPol[Nd];
// 	TCanvas *ctemp = new TCanvas("ctemp","",100,100);
// 	double GraphTop[Nb][Nc][Nd] = {0};
// 	TGraphErrors *storegr[Nb][Nc][Nd];
// 	TLatex *storetex[Nb][Nc][Nd];
// 
// 	// stuff that i dont need now
// 	// double p0[Nb][Nc][Nd] = {0},p1[Nb][Nc][Nd] = {0};
// 	// double ep0[Nb][Nc][Nd] = {0},ep1[Nb][Nc][Nd] = {0};
// 	// double Polarization[Nb][Nc][Nd] = {0};
// 	// double ePolarization[Nb][Nc][Nd] = {0};
// 	// double ChiSquared[Nb][Nc][Nd] = {0};	
// 	
// 	
// 	for (int d = 0; d < Nd; d++)
// 	{
// 		int cancount=1;
// 		cPol[d] = new TCanvas(Form("cPol%s",Axis[d]),Form("cPol%s",Axis[d]),1200,1000);
// 		cPol[d]->Divide(Nb,Nc);
// 		for (int b = 0; b < Nb; b++)
// 		{
// 			for (int c = 0; c < Nc; c++)
// 			{
// 				float asytot = 0;
// 				for (int p = 0; p < Np; p++)
// 				{
// 					ctemp->cd();
// 					//tData->Draw("mmkpkppim>>h",EXibin[b][c]&&PiBin[p][d]&&negHelBin);
// 					tN->Draw("mmkpkppim>>h",EXibin[b][c]&&PiBin[p][d]);
// 					//tNgen->Draw("mmkpkppim>>h",EXibin[b][c]&&PiBin[p][d]);
// 					
// 					negN[b][c][d][p] = h->GetEntries();
// 					enegN[b][c][d][p] = sqrt(negN[b][c][d][p]);
// 				
// 					//tData->Draw("mmkpkppim>>h",EXibin[b][c]&&PiBin[p][d]&&posHelBin);
// 					tP->Draw("mmkpkppim>>h",EXibin[b][c]&&PiBin[p][d]);
// 					//tPgen->Draw("mmkpkppim>>h",EXibin[b][c]&&PiBin[p][d]);
// 					posN[b][c][d][p] = h->GetEntries();
// 					eposN[b][c][d][p] = sqrt(posN[b][c][d][p]);
// 				
// 					asy[b][c][d][p] = (posN[b][c][d][p] - negN[b][c][d][p])/(posN[b][c][d][p] + negN[b][c][d][p]);					
// 					//define some temporary variables to clean up the error calculation
// 					float tp = posN[b][c][d][p];
// 					float tep = eposN[b][c][d][p];
// 					float tn = negN[b][c][d][p];
// 					float ten = enegN[b][c][d][p];
// 					float ta = asy[b][c][d][p];
// 					float tea =  ( 2/( (tp+tn)*(tp+tn) ) ) * sqrt(ten*ten*tep*tep + tp*tp*ten*ten );
// 					easy[b][c][d][p] = tea;
// 					
// 					//only take acceptable values
// 					if( (ta != ta)||(tp <= 10)||(tn <= 10) )
// 					{
// 						//asy[b][c][d][p] = 0;
// 						//easy[b][c][d][p] = 0;
// 						cout << "OMITING A POINT: ";
// 						cout << "b = "<<b<<" c = "<<c<<" d="<<d<<" p="<<p <<" negN = "<<tn << " posN = " << tp << endl;
// 						cout << " asy = " <<ta<< " +/- " <<tea << endl <<endl;
// 					}
// 					else
// 					{
// 						asytot += ta;
// 						xx.push_back(theta[p]);
// 						yy.push_back(ta);
// 						exx.push_back(0);
// 						eyy.push_back(tea);					
// 						
// 						cout << "b = "<<b<<" c = "<<c<<" d="<<d<<" p="<<p <<" negN = "<<tn << " posN = " << tp << endl;
// 						cout << " asy = " <<ta<< " +/- " <<tea << endl <<endl;	
// 					}			
// 				}
// 				int npts = xx.size();
// 				for (int i=0; i < npts; i++)
// 				{
// 					x[i] = xx[i];
// 					y[i] = yy[i];
// 					ex[i] = exx[i];
// 					ey[i] = eyy[i];
// 				}		
// 				xx.clear();
// 				yy.clear();
// 				exx.clear();
// 				eyy.clear();
// 				
// 				
// 				
// 				cPol[d]->cd(cancount);
// 				cancount += 1;
// 				TGraphErrors *mygr = new TGraphErrors(npts,x,y,ex,ey);
// 				mygr->GetXaxis()->SetLimits(-1, 1);
// 				mygr->SetMinimum(-1);
// 				mygr->SetMaximum(1);
// 				GraphTop[b][c][d] = mygr->GetHistogram()->GetMaximum();
// 				mygr->GetYaxis()->SetTitle(Form(" Asymmetry ",Axis[d]));
// 				mygr->GetXaxis()->SetTitle(Form(" Cos(#theta_{#pi^{-}}^{%s})  ",Axis[d]));
// 				mygr->SetTitle(Form(" %1.2f < E_{#gamma} < %1.2f :: %1.2f < cos(#theta_{#Xi}^{cm}) < %1.2f  ",EVal[b],EVal[b+1],XVal[b][c],XVal[b][c+1]));
// 				//*///
// 				TF1 *f1 = new TF1("f1",Form("[0] - %f*%f*[1]*x",alpha,beampol),-1,1);
// 				mygr->Fit("f1","EV");
// 				float Xipol = f1->GetParameter(1);
// 				float eXipol = f1->GetParError(1);
// 				float chisqr = f1->GetChisquare();
// 				mygr->Draw("A*");
// 				//storegr[b][c][d] = mygr;
// 				
// 				
// 				TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
// 				mytex=new TLatex(-0.9, 0.7*GraphTop[b][c][d],Form("C%s = %5.3f #pm %5.3f ",Axis[d],Xipol,eXipol));
// 				mytex->SetTextSize(0.06); 
// 				mytex->SetTextColor(4);
// 				mytex->Draw("SAME");
// 				
// 				TLatex *mytex2=new TLatex(0.0, 0.0,"mytex2");
// 				mytex2=new TLatex(-0.9, 0.45*GraphTop[b][c][d],Form("#frac{#sigma^{2}}{ndf} = %5.3f ",chisqr/npts));
// 				mytex2->SetTextSize(0.06); 
// 				mytex2->SetTextColor(1);
// 				mytex2->Draw("SAME");
// 
// 				TLatex *mytex3=new TLatex(0.0, 0.0,"mytex3");
// 				mytex2=new TLatex(-0.9, 0.25*GraphTop[b][c][d],Form("total asymmety = %5.3f ",asytot));
// 				mytex2->SetTextSize(0.06); 
// 				mytex2->SetTextColor(3);
// 				mytex2->Draw("SAME");
// 				
// 				
// 			}	
// 		}
// 	}
// 	
// 	
// 	
// 	
// 	
// }




StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.55);
	gStyle->SetTitleSize(0.07);
	gStyle->SetTitleYSize(0.06); 
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
	gStyle->SetOptFit(0);
}