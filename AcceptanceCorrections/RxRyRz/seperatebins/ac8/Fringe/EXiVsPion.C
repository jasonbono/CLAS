#include "../Fringe.h"


void EXiVsPion()
{

	StyleUp();
	TFile* fData = new TFile("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root"); 
	TTree *tData = (TTree*)fData->Get("v05");
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC-i8-NoPol-2kppim_Basic_Mass.root"); 
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	TTree *myTree[2];
	myTree[0] = tData;
	myTree[1] = tMC;

	//a=datatype, b=bintype, d=piaxis
	const int Na = 2,Nb = 2,Nd = 3;
	const char* DataType[Na] = {"Data","MC"};
	const char* BinType[Nb] = {"E","Xi"};
	const char* Axis[Nd] = {"x","y","z"};
	const char* Y[Nb] = {"beam","Xcmtheta"};
	const char* Ytitle[Nb] = {"E #gamma (GeV)", "Cos(#theta^{#Xi^{-}}_{cm})"};
	
	 
	TH2F *hE=new TH2F("hE","",50,2.8,5.5,50,-1,1);
	TH2F *hXi=new TH2F("hXi","",50,-1,1,50,-1,1);
	TH2F *hcopy[Nb];
	hcopy[0] = hE;
	hcopy[1] = hXi;
	TH2F *hCompare[Na][Nb][Nd];
	TH2F *hCompare2[Na][Nb][Nd];
	
	Float_t beam_Data,Xcmtheta_Data,COS_pi_x_Data,COS_pi_y_Data,COS_pi_z_Data;
	myTree[0]->SetBranchAddress("beam", &beam_Data);
	myTree[0]->SetBranchAddress("Xcmtheta", &Xcmtheta_Data);
	myTree[0]->SetBranchAddress("COS_pi_x", &COS_pi_x_Data);
	myTree[0]->SetBranchAddress("COS_pi_y", &COS_pi_y_Data);
	myTree[0]->SetBranchAddress("COS_pi_z", &COS_pi_z_Data);
	
	Float_t beam_MC,Xcmtheta_MC,COS_pi_x_MC,COS_pi_y_MC,COS_pi_z_MC;
	myTree[1]->SetBranchAddress("beam", &beam_MC);
	myTree[1]->SetBranchAddress("Xcmtheta", &Xcmtheta_MC);
	myTree[1]->SetBranchAddress("COS_pi_x", &COS_pi_x_MC);
	myTree[1]->SetBranchAddress("COS_pi_y", &COS_pi_y_MC);
	myTree[1]->SetBranchAddress("COS_pi_z", &COS_pi_z_MC);

	
	Float_t beam[Na],Xcmtheta[Na],COS_pi_x[Na],COS_pi_y[Na],COS_pi_z[Na];
	Float_t varX[Na][Nb],varY[Na][Nd];
	

	//no line
	TLine *noline = new TLine(0,0,0,0);
	//x lines
	TLine *lEx0 = new TLine(2.8,-0.2,3.5,-0.2);	
	TLine *lEx1 = new TLine(3.5,-0.5,5,-0.5);
	TLine *lEx2 = new TLine(5,-0.3,5.5,-0.3);	
	TLine *lXix0 = new TLine(-1,-0.4,0.4,-0.4);
	TLine *lXix1 = new TLine(0.4,-0,0.8,0);	
	TLine *lXix2 = new TLine(0.8,-1,0.8,1);
	//y lines
 	TLine *lXiy0 = new TLine(0.8,-1,0.8,1);
	//z lines
	TLine *lEz0 = new TLine(2.8,0.3,3.3,0.3);
	TLine *lEz1 = new TLine(3.3,0.4,5.5,0.4);
 	TLine *lEz2 = new TLine(0,0,0,0);
	TLine *lXiz0 = new TLine(-1,-0.7,-0.8,-0.7);
	TLine *lXiz1 = new TLine(-0.8,-0.9,-0.6,-0.9);
	TLine *lXiz2 = new TLine(-1,0.5,0,0.5);
	TLine *lXiz3 = new TLine(0,0.2,0.4,0.2);
	TLine *lXiz4 = new TLine(0.4,0,0.8,0);
 	TLine *lXiz5 = new TLine(0.8,-1,0.8,1);
	TLine *lines[Nb][Nd][6];
	for (int b = 0; b < Nb; b++)
	{
		for (int d = 0; d < Nd; d++)
		{
			for (int i = 0; i < 6; i++)
			{
				lines[b][d][i] = noline;
				
			}
		}
	}
	lines[0][0][0] = lEx0;
	lines[0][0][1] = lEx1;
	lines[0][0][2] = lEx2;
	lines[1][0][0] = lXix0;
	lines[1][0][1] = lXix1;
	lines[1][0][2] = lXix2;
	lines[1][1][0] = lXiy0;
	lines[0][2][0] = lEz0;
	lines[0][2][1] = lEz1;
	lines[0][2][2] = lEz2;
	lines[1][2][0] = lXiz0;
	lines[1][2][1] = lXiz1;
	lines[1][2][2] = lXiz2;
	lines[1][2][3] = lXiz3;
	lines[1][2][4] = lXiz4;
	lines[1][2][5] = lXiz5;

/*
	TCanvas *cCompare[Nd];
	for (int d = 0; d < Nd; d++)
	{
		int cancount = 1;
		cCompare[d] = new TCanvas(Form("cCompare_%s",Axis[d]),Form("cCompare_%s",Axis[d]),1200,1000);
		cCompare[d]->Divide(2,2);
		for (int b = 0; b < Nb; b++)
		{
			for (int a = 0; a < Na; a++)
			{
				//hCompare[a][b][d] = hcopy[b];
				hCompare[a][b][d] = (TH2F*)hcopy[b]->Clone();
				//hCompare[a][b][d]->SetTitle(Form("h%i%i%i",a,b,d));
				hCompare[a][b][d]->SetName(Form("h%i%i%i",a,b,d));
				hCompare[a][b][d]->SetTitle(Form("%s",DataType[a]));
				hCompare[a][b][d]->GetYaxis()->SetTitle(Form("Cos(#theta_{%s}^{#pi^{-}})",Axis[d]));
				hCompare[a][b][d]->GetXaxis()->SetTitle(Form("%s",Ytitle[b]));

				cCompare[d]->cd(cancount);
				myTree[a]->Draw(Form("COS_pi_%s:%s >> h%i%i%i",Axis[d],Y[b],a,b,d),"","colz");
				for (int i = 0; i < 6; i++)
				{
						lines[b][d][i]->SetLineWidth(5);
						lines[b][d][i]->SetLineColor(2);						
						lines[b][d][i]->Draw("same");
				}
				cancount += 1;
			}
		}
	}
*/
	
	//after cuts
	TCanvas *cCompare2[Nd];
	for (int d = 0; d < Nd; d++)
	{
		int cancount = 1;
		cCompare2[d] = new TCanvas(Form("cCompare2_%s",Axis[d]),Form("cCompare2_%s",Axis[d]),1200,1000);
		cCompare2[d]->Divide(2,2);
		for (int b = 0; b < Nb; b++)
		{
			for (int a = 0; a < Na; a++)
			{
				//hCompare2[a][b][d] = hcopy[b];
				hCompare2[a][b][d] = (TH2F*)hcopy[b]->Clone();
				//hCompare2[a][b][d]->SetTitle(Form("h%i%i%i",a,b,d));
				hCompare2[a][b][d]->SetName(Form("hCompare2_%i%i%i",a,b,d));
				hCompare2[a][b][d]->SetTitle(Form("%s",DataType[a]));
				hCompare2[a][b][d]->GetYaxis()->SetTitle(Form("Cos(#theta_{%s}^{#pi^{-}})",Axis[d]));
				hCompare2[a][b][d]->GetXaxis()->SetTitle(Form("%s",Ytitle[b]));

				cCompare2[d]->cd(cancount);
				//myTree[a]->Draw(Form("COS_pi_%s:%s >> hCompare2_%i%i%i",Axis[d],Y[b],a,b,d),"","colz");
				//hCompare2[a][b][d]->Clear();
				//hCompare2[a][b][d]->Draw();
				for (int i = 0; i < 6; i++)
				{
						lines[b][d][i]->SetLineWidth(5);
						lines[b][d][i]->SetLineColor(2);						
						lines[b][d][i]->Draw("same");
				}
				cancount += 1;
			}
		}
	}
	
	for (int a = 0; a < Na; a++)
	{
		//loop over the entries and fill the histogram
		Long64_t nentries = myTree[a]->GetEntries();
		for (Long64_t ii=0; ii<nentries; ii++)
		{
			myTree[a]->GetEntry(ii);
			beam[0] = beam_Data;
			Xcmtheta[0] = Xcmtheta_Data;
			COS_pi_x[0] = COS_pi_x_Data;
			COS_pi_y[0] = COS_pi_y_Data;
			COS_pi_z[0] = COS_pi_z_Data;
			beam[1] = beam_MC;
			Xcmtheta[1] = Xcmtheta_MC;
			COS_pi_x[1] = COS_pi_x_MC;
			COS_pi_y[1] = COS_pi_y_MC;
			COS_pi_z[1] = COS_pi_z_MC;
			varX[a][0] = beam[a]; 
			varX[a][1] = Xcmtheta[a];				
			for (int b = 0; b < Nb; b++)
			{
				varY[a][0] = COS_pi_x[a];
				varY[a][1] = COS_pi_y[a];
				varY[a][2] = COS_pi_z[a];
			
		
				for (int d = 0; d < Nd; d++)
				{
					//cout <<a<<" "<<b<<" "<<d<<endl;
					//cout << "varX = "  <<varX[a][b] << " varY = " << varY[a][b][d] <<endl;
					bool fill = NoFringe_smart(varX[a][b],varY[a][d],b,d);
					if(fill)
					{
						hCompare2[a][b][d]->Fill(varX[a][b],varY[a][d]);
					}
				}	
			}
		}
	}
	
	for (int d = 0; d < Nd; d++)
	{
		int cancount = 1;
		for (int b = 0; b < Nb; b++)
		{
			for (int a = 0; a < Na; a++)
			{
				cCompare2[d]->cd(cancount);
				hCompare2[a][b][d]->Draw("colz");
				for (int i = 0; i < 6; i++)
				{
					lines[b][d][i]->SetLineWidth(5);
					lines[b][d][i]->SetLineColor(2);						
					//lines[b][d][i]->Draw("same");
				}
				cancount += 1;
			}
		}
	}
			
		TCanvas *blank = new TCanvas("blank","",1,1);

}





StyleUp()
{
	gStyle->SetTitleXOffset(0.5);
	gStyle->SetTitleYOffset(0.65);
	gStyle->SetTitleSize(0.07);
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
