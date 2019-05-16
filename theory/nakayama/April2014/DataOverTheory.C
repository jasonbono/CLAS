/* 
Author: Jason Bono
Date: April 15 2014:
Purpose: To read and plot nakayamas results
*/

#include "./MyResults.h"

using namespace std;

const int nmodels = 3;
const int nobs = 3; //number of observables
const char* Observable[nobs] = {"P","C_{x}","C_{z}"};

struct MyStruct
{
	//following nakayamas convention
	float T_lb;
	float Theta_cm;
	float xsc;
	float Sigma;
	float Sigma_c;
	float T_x;	
	float T_y;
	float T_z;
	float P_x;
	float P_y;
	float P_z;
	float C_x;
	float C_y;
	float C_z;
};

struct MyOldStruct
{
	//following nakayamas convention
	float T_lb;
	float Theta_cm;
	float xsc;
	float T_y;
	float Sigma;
	float P_y;
	float Sigma_c;
	float C_x;
	float C_z;
};

//function prototype
bool ReadALine(ifstream &, MyStruct &);
bool OldReadALine(ifstream &, MyOldStruct &);


void DataOverTheory()
{
	StyleUp();
	//set up instance of MyStruct
	MyOldStruct ALine;
	//MyStruct ALine;
	
	//set up the file to be read
	ifstream myfile[nmodels];
	myfile[0].open("./FebResults/old_mybono_sp_ps.out");
	myfile[1].open("./FebResults/old_mybono_sp_pv.out");	
	myfile[2].open("./FebResults/old_mybono_sp.out");


	// ifstream myfile1,myfile2,myfile3;	
	// myfile1.open("./FebResults/old_mybono_sp_ps.out");
	// myfile2.open("./FebResults/old_mybono_sp_pv.out");	
	// myfile3.open("./FebResults/old_mybono_sp_pv_2011.out");
	
	//setup vectors for pushback
	vector<double> xi0;
	vector<double> p0;
	vector<double> cx0;
	vector<double> cz0;
	vector<double> xi[nmodels];
	vector<double> p[nmodels];
	vector<double> cx[nmodels];
	vector<double> cz[nmodels];

	for (int m = 0; m < nmodels; m++)
	{
		while (OldReadALine(myfile[m], ALine)) 
		{
			float T_lb = ALine.T_lb;
			float Theta_cm = ALine.Theta_cm;
			float P_y = ALine.P_y;
			float C_x = ALine.C_x;
			float C_z = ALine.C_z;				
			if (T_lb == 4)
			{
				xi[m].push_back(Theta_cm);
				p[m].push_back(P_y);
				cx[m].push_back(C_x);
				cz[m].push_back(C_z);
			}
		}
	}
	const int nxibins = xi[0].size(); //define number of points in graphs
	cout << nxibins <<endl;
	

	TGraph *nakGr[nmodels][3]; //three models and three polarization observables
	for (int m = 0; m < nmodels; m++)
	{

		float x[nxibins] = {0};
		float yx[nxibins] = {0};
		float yy[nxibins] = {0};
		float yz[nxibins] = {0};
		for (int c=0; c < nxibins; c++)
		{ 
			x[c] = xi[m][c];
			yx[c] = cx[m][c];
			yy[c] = p[m][c];
			yz[c] = cz[m][c];
			
		}
		nakGr[m][0] = new TGraph(nxibins,x,yx);
		nakGr[m][1] = new TGraph(nxibins,x,yy);
		nakGr[m][2] = new TGraph(nxibins,x,yz);
		
	}
	
	TMultiGraph *nakMgr[nobs];
	TLegend *myleg[nmodels];
	for (int o = 0; o < nobs; o++)
	{
		
		myleg[o] = new TLegend(.65, .7, 0.98, 0.98); //top right
		myleg[o]->AddEntry(nakGr[0][o], "ps (PRC74'06)", "l");
		myleg[o]->AddEntry(nakGr[1][o], "pv (PRC74'06)", "l");
		myleg[o]->AddEntry(nakGr[2][o], "pv (PRC83'11)", "l");
		myleg[o]->SetTextSize(0.04);
		
		nakGr[0][o]->SetMarkerSize(0.1);
		nakGr[0][o]->SetMarkerColor(kRed);
		nakGr[0][o]->SetLineColor(kRed);
		nakGr[0][o]->SetLineStyle(1);
		nakGr[0][o]->SetLineWidth(3);
		nakGr[0][o]->SetMarkerStyle(22);
		nakGr[1][o]->SetMarkerSize(0.1);
		nakGr[1][o]->SetMarkerColor(kBlue);
		nakGr[1][o]->SetLineColor(kBlue);
		nakGr[1][o]->SetLineStyle(6);
		nakGr[1][o]->SetLineWidth(3);
		nakGr[1][o]->SetMarkerStyle(22);
		nakGr[2][o]->SetMarkerSize(0.1);
		nakGr[2][o]->SetMarkerColor(kGreen);
		nakGr[2][o]->SetLineColor(kGreen);
		nakGr[2][o]->SetLineStyle(7);
		nakGr[2][o]->SetLineWidth(3);
		nakGr[2][o]->SetMarkerStyle(22);
		
		nakMgr[o] = new TMultiGraph();
		nakMgr[o]->Add(nakGr[0][o]);
		nakMgr[o]->Add(nakGr[1][o]);
		nakMgr[o]->Add(nakGr[2][o]);
		//nakMgr[o]->SetTitle(Form("t_{lab} = %i GeV",4));
		nakMgr[o]->Draw("ACP");
		nakMgr[o]->SetMinimum(-1);
		nakMgr[o]->SetMaximum(1);
		if (o == 1){
			nakMgr[o]->GetXaxis()->SetTitle("cos(#theta_{#Xi^{-}}^{cm})");
		}
		else{
			
		}

		nakMgr[o]->GetYaxis()->SetTitle(Form("%s",Observable[o]));
		nakMgr[o]->GetYaxis()->CenterTitle();
		nakMgr[o]->Draw("ACP");
	}
	cout <<"test"<<endl;
	//store my results as a plot
	TGraphErrors *mygr[nobs];
	for (int o = 0; o < nobs; o++)
	{
		if(o==0)
		{
			mygr[o] = new TGraphErrors(3,myXimean,myP[1],myeXimean,myeP[1]);
		}
		if(o==1)
		{
			mygr[o] = new TGraphErrors(3,myXimean,myCx[1],myeXimean,myeCx[1]);
		}
		if(o==2)
		{
			mygr[o] = new TGraphErrors(3,myXimean,myCz[1],myeXimean,myeCz[1]);
		}
		myleg[o]->AddEntry(mygr[o], "Data", "p");
		mygr[o]->SetMarkerColor(kBlack);
		mygr[o]->SetMarkerSize(1.5);
		mygr[o]->SetMarkerStyle(20);
		mygr[o]->SetMinimum(-1);
		mygr[o]->SetMaximum(1);
		
		//mygr[o]->GetXaxis()->SetMinimum(-1);
		//mygr[o]->GetXaxis()->SetMaximum(1);
		//nakMgr[o]->Add(mygr[o]);		
	}
		
		
	TPad *nakPad[nobs];	
	TPad *myPad[nobs];
	TCanvas *can=new TCanvas("can","can", 1200,600);
	can->Divide(3,1);
	TMultiGraph *mgs[nobs];
	for (int o = 0; o < nobs; o++)
	{
		can->cd(o+1);
		// myPad[o] = new TPad("myPad","",0,0,1,1);
		// myPad[o]->SetFillColor(kWhite);
		// //myPad[o]->SetGrid();
		// //myPad[o]->Draw();
		// myPad[o]->cd();	
		// mygr[o]->Draw("AP");
		
		// can->cd(o+1);
		// nakPad[o] = new TPad("nakPad","",0,0,1,1);
		// nakPad[o]->SetFillColor(0);
		// nakPad[o]->SetFillStyle(4000);
	   	// nakPad[o]->SetFillColor(0);
	   	// nakPad[o]->SetFrameFillStyle(4000);
		// //nakPad[o]->SetGrid();
		// nakPad[o]->Draw();
		// nakPad[o]->cd();
		
		
		nakMgr[o]->Draw("ACP");
		mygr[o]->Draw("PSAME");
		
			  
		if(o == 1){
			myleg[o]->Draw("same");			
		}
	}	
		TCanvas *cf=new TCanvas("cf","cf", 1,1);
}
	
bool OldReadALine(ifstream & afile, MyOldStruct & ALine)
{
	float tempF;
	int tempI;
	bool result = false;
	//following nakayamas convention
	if (afile >> ALine.T_lb >> ALine.Theta_cm >> ALine.xsc >> ALine.T_y >> ALine.Sigma >> ALine.P_y >> ALine.Sigma_c >> ALine.C_x >> ALine.C_z ) 
	{
 		result = true;
	}
	return result;
}


bool ReadALine(ifstream & afile, MyStruct & ALine)
{
	float tempF;
	int tempI;
	bool result = false;
	//following nakayamas convention
	if (afile >> ALine.T_lb >> ALine.Theta_cm >> ALine.xsc >> ALine.Sigma >> ALine.Sigma_c >> ALine.T_x  >> ALine.T_y >> ALine.T_z >>
 		ALine.P_x >> ALine.P_y >> ALine.P_z >> ALine.C_x >> ALine.C_y >> ALine.C_z ) 
	{
 		result = true;
	}
	return result;
}


StyleUp()
{
	gStyle->SetTitleXOffset(0.4);
	gStyle->SetTitleYOffset(0.2);
	gStyle->SetTitleSize(0.09);
	gStyle->SetTitleYSize(0.13); 
	gStyle->SetPadTopMargin(0);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(100);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);
	gStyle->SetTitleYSize(0.06);
	gStyle->SetTitleYOffset(0.7);
	gStyle->SetTitleXOffset(0.6);
	gStyle->SetPadBottomMargin(0.13);
	gStyle->SetPadRightMargin(0.01);
}


