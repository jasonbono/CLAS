/* 
Author: Jason Bono
Date: Feb 13 2014:
Purpose: To read and plot nakayamas results
*/

using namespace std;

const int nebins = 3;

struct MyStruct
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

void PlotResults()
{
	StyleUp();
	//set up instance of MyStruct
	MyStruct ALine;
	//set up the file to be read
	ifstream myfile;
	myfile.open("./mybono_sp_ps.out");
	//setup vectors for pushback
	vector<double> xi0;
	vector<double> p0;
	vector<double> cx0;
	vector<double> cz0;
	vector<double> xi[nebins];
	vector<double> p[nebins];
	vector<double> cx[nebins];
	vector<double> cz[nebins];
	
	while (ReadALine(myfile, ALine)) 
	{
		float T_lb = ALine.T_lb;
		float Theta_cm = ALine.Theta_cm;
		float P_y = ALine.P_y;
		float C_x = ALine.C_x;
		float C_z = ALine.C_z;
				
		if (T_lb == 3)
		{
			xi[0].push_back(Theta_cm);
			p[0].push_back(P_y);
			cx[0].push_back(C_x);
			cz[0].push_back(C_z);
		}
		const int nxibins = xi[0].size(); //define number of points in graphs
		if (T_lb == 4)
		{
			xi[1].push_back(Theta_cm);
			p[1].push_back(P_y);
			cx[1].push_back(C_x);
			cz[1].push_back(C_z);
		}
		if (T_lb == 5)
		{
			xi[2].push_back(Theta_cm);
			p[2].push_back(P_y);
			cx[2].push_back(C_x);
			cz[2].push_back(C_z);
		}				
	}


	
	TGraph *mygr[nebins][3]; //energy bins and three polarization observables
	TMultiGraph *mymgr[nebins];
	TLegend *myleg[nebins];
	for (int b = 0; b < nebins; b++)
	{
		
		mymgr[b] = new TMultiGraph();
		float x[nxibins] = {0};
		float yx[nxibins] = {0};
		float yy[nxibins] = {0};
		float yz[nxibins] = {0};
		for (int c=0; c < nxibins; c++)
		{
			x[c] = xi[b][c];
			yx[c] = cx[b][c];
			yy[c] = p[b][c];
			yz[c] = cz[b][c];
		}
		mygr[b][0] = new TGraph(nxibins,x,yx);
		mygr[b][1] = new TGraph(nxibins,x,yy);
		mygr[b][2] = new TGraph(nxibins,x,yz);
		
		// mygr[b][0]->SetTitle("test");
		// mygr[b][1]->SetTitle("test");
		// mygr[b][2]->SetTitle("test");
		
		mygr[b][0]->SetMarkerSize(1.5);
		mygr[b][0]->SetMarkerColor(1);
		mygr[b][0]->SetMarkerStyle(22);
		mygr[b][1]->SetMarkerSize(1.5);
		mygr[b][1]->SetMarkerColor(2);
		mygr[b][1]->SetMarkerStyle(21);
		mygr[b][2]->SetMarkerSize(1.5);
		mygr[b][2]->SetMarkerColor(4);
		mygr[b][2]->SetMarkerStyle(20);
		
		myleg[b] = new TLegend(.7, .7, .9, .9); //top right
		myleg[b]->AddEntry(mygr[b][0], "C_{x}", "p");
		myleg[b]->AddEntry(mygr[b][1], "P", "p");
		myleg[b]->AddEntry(mygr[b][2], "C_{z}", "p");

		mymgr[b]->Add(mygr[b][0]);
		mymgr[b]->Add(mygr[b][1]);
		mymgr[b]->Add(mygr[b][2]);
		mymgr[b]->SetTitle(Form("t_{lab} = %i GeV",b+3));
		mymgr[b]->Draw("AP");
		mymgr[b]->SetMinimum(-1);
		mymgr[b]->SetMaximum(1);
		mymgr[b]->GetXaxis()->SetTitle("cos(#theta_{#Xi}^{cm})");
		mymgr[b]->GetYaxis()->SetTitle("Polarization");
		mymgr[b]->Draw("AP");
	}	
	

	TCanvas *can=new TCanvas("can","can", 1200,800);
	can->Divide(3,0);
	for (int b = 0; b < nebins; b++)
	{
		can->cd(b+1);
	 	mymgr[b]->Draw("AP");
		myleg[b]->Draw("Same");
	}	
	
	
}
	


bool ReadALine(ifstream & myfile, MyStruct & ALine)
{
	float tempF;
	int tempI;
	bool result = false;
	//following nakayamas convention
	if (myfile >> ALine.T_lb >> ALine.Theta_cm >> ALine.xsc >> ALine.T_y >> ALine.Sigma >> ALine.P_y >> ALine.Sigma_c >> ALine.C_x >> ALine.C_z ) 
	{
 		result = true;
	}
	return result;
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


