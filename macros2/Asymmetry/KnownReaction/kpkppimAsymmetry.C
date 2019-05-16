/*
Author: Jason Bono
Date: Jun 13 2013
*/



TFile *fData = TFile::Open("/Users/Bono/clas/rootfiles/g12/2kppim/v16/hadded/2kppim-v16_Basic_Mass3.root");
TTree *tData = (TTree*)fData->Get("v16");


const int minstat = 10;
const int Np = 7; //# of phi bins
const float beampol = 0.5;

void kpkppimAsymmetry()
{
	//StyleUp();
	//set up helicity
	TCut negHelBin = "hel == 1";
	TCut posHelBin = "hel == -1";
	
	
	TCut cutp = "pkp1/pkp2 < 10.5";

	
	//set up the pion bins
	TCut PhiBin[Np];
	float Phi[Np] = {0};
	float angle = -TMath::Pi();
	for (int p=0; p < Np; p++)
	{	
		PhiBin[p] = Form("theta > %f && theta < %f",angle,angle + 2.0*TMath::Pi()/Np);
		float low = angle;
		angle = angle + 2.0*TMath::Pi()/Np;
		float high = angle;
		Phi[p] = (low + high)/2.0;
		cout <<"Phi = " <<Phi[p]<<endl;
		TString temp = PhiBin[p];
		cout <<temp<<endl;
	}	
		
	double negN[Np] = {0};
	double posN[Np] = {0};
	double asy[Np] = {0};
	double enegN[Np] = {0};
	double eposN[Np] = {0};
	double easy[Np] = {0};
	vector<double> xx;
	vector<double> yy;
	vector<double> exx;
	vector<double> eyy;
	double x[Np]; //note that the dimention of plotting variables are Np but will endup ploting x pts where x <=Np
	double y[Np]; 
	double ex[Np]; 
	double ey[Np]; 
	double GraphTop;
	TGraphErrors *storegr;
	TLatex *storetex;
	int postot = 0;
	int negtot = 0;	
	float asytot = 0;
	for (int p = 0; p < Np; p++)
	{		
		tData->Draw("theta>>h",PhiBin[p]&&negHelBin&&cutp);
		negN[p] = h->GetEntries();
		negtot += negN[p];
		enegN[p] = sqrt(negN[p]);
				
		tData->Draw("theta>>h",PhiBin[p]&&posHelBin&&cutp);
		posN[p] = h->GetEntries();
		postot += posN[p];
		eposN[p] = sqrt(posN[p]);
				
		asy[p] = (posN[p] - negN[p])/(posN[p] + negN[p]);
		//define some temporary variables to clean up the error calculation
		float tp = posN[p];
		float tep = eposN[p];
		float tn = negN[p];
		float ten = enegN[p];
		float ta = asy[p];
		float tea =  ( 2/( (tp+tn)*(tp+tn) ) ) * sqrt(tn*tn*tep*tep + tp*tp*ten*ten );
		easy[p] = tea;				
	 	//only take acceptable values
		if( (ta != ta)||(tp < minstat)||(tn < minstat) )
		{
			//asy[p] = 0;
			//easy[p] = 0;
			cout << "OMITING A POINT: ";
			cout <<" p="<<p <<" negN = "<<tn << " posN = " << tp << endl;
			cout << " asy = " <<ta<< " +/- " <<tea << endl <<endl;
		}
		else
		{
			asytot += ta;
			xx.push_back(Phi[p]);
			yy.push_back(ta);
			exx.push_back(0);
			eyy.push_back(tea);					
						
			cout <<" p="<<p <<" negN = "<<tn << " posN = " << tp << endl;
			cout << " asy = " <<ta<< " +/- " <<tea << endl <<endl;
		}			
	}
	int npts = xx.size();
	for (int i=0; i < npts; i++)
	{
		x[i] = xx[i]*180/TMath::Pi() + 180;
		y[i] = yy[i]/beampol;
		ex[i] = exx[i];
		ey[i] = eyy[i];
	}		
	xx.clear();
	yy.clear();
	exx.clear();
	eyy.clear();				

	TCanvas *c=new TCanvas("c","c",1200,1000);
	TGraphErrors *mygr = new TGraphErrors(npts,x,y,ex,ey);
	mygr->GetXaxis()->SetLimits(0, 360);
	mygr->SetMinimum(-0.3);
	mygr->SetMaximum(0.3);
	GraphTop = mygr->GetHistogram()->GetMaximum();
	mygr->GetYaxis()->SetTitle(" Asymmetry ");
	mygr->GetXaxis()->SetTitle("phi");
	mygr->SetMarkerStyle(20);
	mygr->SetMarkerSize(3);
	mygr->Draw("AP");
				

	// 
	// TLatex *mytex3=new TLatex(0.0, 0.0,"mytex3");
	// mytex2=new TLatex(-0.9, 0.25*GraphTop,Form("total asymmety = %5.3f ",asytot));
	// mytex2->SetTextSize(0.06); 
	// mytex2->SetTextColor(3);
	// mytex2->Draw("SAME");
				

	TLatex *mytex4=new TLatex(0.0, 0.0,"mytex3");
	mytex4=new TLatex(10, -0.8*GraphTop,Form("n^{+} =%i : n^{-} =%i  ",postot,negtot));
	mytex4->SetTextSize(0.06); 
	mytex4->SetTextColor(15);
	mytex4->Draw("SAME");
	TLine *L1 = new  TLine(0, 0, 360, 0);
	L1->Draw("SAME");
	TLine *L2 = new  TLine(180, -0.3, 180, 0.3);
	L2->Draw("SAME");

}




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