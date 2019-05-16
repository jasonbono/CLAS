



#include "/Users/Bono/clas/myDefinitions/WBins.h" 
#include "/Users/Bono/clas/myDefinitions/EXiBins.h"


void QuickCorrection()
{
	
	
	//Some important declarations 
	const int Nb = 2,Nc = 3,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis		
	const int Np = 10; //number of pion bins
	const int Nk = 50; //# of pion bins used to get the acceptance
	const float alpha = -0.458;	
	const char* BinType[Nb] = {"E","Xi"};
	const char* BinNumber[Nc] = {"0","1","2"};
	const char* Axis[Nd] = {"x","y","z"};
	

	//interactively choose Data or Simulation
	cout << "enter choice (Data, NoPol, or PosPol):";
	const string choice;
	cin >> choice;
	if (choice.compare("Data") == 0)
	{
	  	cout <<"The data will be evaluated" <<endl;	
		TFile *file = TFile::Open(Form("./NewRootFiles/2kppim-v05-Basic-Mass-Ac-%ibins.root",Nk));
		TTree *tOriginal = (TTree*)file->Get("v05");
		TFile* fPolHistos = new TFile(Form("./hists/QuickPolHists-%ibins.root",Nk),"RECREATE");
		ofstream myfile;
		myfile.open (Form("./txt/QuickDataCor-%ibins.txt",Nk));
		
		bool AddWithWeight = 0; //do not use the W factors
	}
	else if (choice.compare("NoPol") == 0) 
	{
		cout <<"The NoPol simulation will be evaluated" <<endl;		
		TFile* file = new TFile(Form("./NewRootFiles/SimTest-NoPol-%ibins.root",Nk));
		TTree *tOriginal = (TTree*)file->Get("SimTest");
		TFile* fPolHistos = new TFile(Form("./hists/QuickSimTest-NoPol-PolHists-%ibins.root",Nk),"RECREATE");
		ofstream myfile;
		myfile.open (Form("./txt/QuickSimTestCor-NoPol-%ibins.txt",Nk));
		
		bool AddWithWeight = 1; //use the W factors when evaluating the simulation
	}
	else if (choice.compare("PosPol") == 0) 
	{
		cout <<"The PosPol simulation will be evaluated" <<endl;		
		TFile* file = new TFile(Form("./NewRootFiles/SimTest-PosPol-%ibins.root",Nk));  
		TTree *tOriginal = (TTree*)file->Get("SimTest");
		TFile* fPolHistos = new TFile(Form("./hists/QuickSimTest-PosPol-PolHists-%ibins.root",Nk),"RECREATE");
		ofstream myfile;
		myfile.open (Form("./txt/QuickSimTestCor-PosPol-%ibins.txt",Nk));	
		
		bool AddWithWeight = 1; //use the W factors when evaluating the simulation
	}
	
	else
	{ 
		cout << "choice error, quiting! " <<endl;
		gROOT->ProcessLine(".q");
	}
	AddWithWeight = 0;



	//-----------The Weighting Factors---------
	if (AddWithWeight){
		if(NWBins == 27){
			ifstream in(Form("/Users/Bono/clas/myDefinitions/txt/Winfo-i5-%s.txt",choice.c_str())); // input
	  		if(!in) {
	    		cout << "Cannot open txt file.\n";
				gROOT->ProcessLine(".q");
	  		}
			double W[NWBins] = {0},eW[NWBins] = {0};

			for (int z = 0; z < NWBins ; z++) 
			{
	  			in >> W[z] >> eW[z];
	  			cout << "W[z], eW[z] = " << W[z] << ", " << eW[z] << "\n";
			}
				in.close();		
			}
		}



	//histograms to plot the results
	TH1D *h=new TH1D("h","",Np,-1,1);
	TH1D *hPol[Nb][Nc][Nd];
	TH1D *hPolW[Nb][Nc][Nd][NWBins];
	

	
				
	//hPion[a][b][c][d]->Add(hPionW[a][b][c][d][z],W[z]);


	for (int b = 0; b < Nb; b++)
	{
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{
				if (AddWithWeight)
				{
					for (int z = 0; z < NWBins ; z++) 
					{
						hPolW[b][c][d][z] = (TH1D*)h->Clone(Form("h-%sBin%s-PiAxis%s-W%i",BinType[b],BinNumber[c],Axis[d],z));
						tOriginal->Draw(Form("COS_pi_%s >>h-%sBin%s-PiAxis%s-W%i",Axis[d],BinType[b],BinNumber[c],Axis[d],z),Form("1/R%s%s",BinType[b],Axis[d])*(EXiBin[b][c]&&WBin[z]));
						hPolW[b][c][d][z]->SetMinimum(0);	
					}
				}
				hPol[b][c][d] = (TH1D*)h->Clone(Form("h-%sBin%s-PiAxis%s",BinType[b],BinNumber[c],Axis[d]));
				hPol[b][c][d]->SetMinimum(0);
				if (d == 0) 
				{
					hPol[b][c][d]->SetAxisRange(-0.4,1,"X"); //X means to scale the x-axis rather than the y-axis
				}
				if (d == 2) 
				{
					hPol[b][c][d]->SetAxisRange(-0.6,0.2,"X");  //this give the beginning of the last bin, not the end of the plot
				}
			}
		}
	}


	//fill and draw the histograms
	TCanvas *cPol[Nb];
	int cancount = 0;
	for (int b = 0; b < Nb; b++)
	{
		cancount=1;
		cPol[b] = new TCanvas(Form("cPol%s",BinType[b]),Form("cPol%s",BinType[b]),1200,1000);
		cPol[b]->Divide(3,3);
		for (int c = 0; c < Nc; c++)
		{	
			for (int d = 0; d < Nd; d++)
			{
				if (AddWithWeight)
				{
					for (int z = 0; z < NWBins ; z++) 
					{
						hPol[b][c][d]->Add(hPolW[b][c][d][z],W[z]);				
					}
					cPol[b]->cd(cancount);
					cancount += 1;
					hPol[b][c][d]->Draw();
				}
				else if (!AddWithWeight)		
				{
					cPol[b]->cd(cancount);
					cancount += 1;
					tOriginal->Draw(Form("COS_pi_%s >>h-%sBin%s-PiAxis%s",Axis[d],BinType[b],BinNumber[c],Axis[d]),Form("1/R%s%s",BinType[b],Axis[d])*EXiBin[b][c]);
				}
				hPol[b][c][d]->SetMinimum(0);
			}
		}
	}
	
	
	//Fit the histograms, calculate polarization and put lables on
	TF1 *f1 = new TF1("f1",Form("[0] - [0]*%f*[1]*x",alpha),-1,1);
	Double_t p0[Nb][Nc][Nd],p1[Nb][Nc][Nd];
	Double_t ep0[Nb][Nc][Nd],ep1[Nb][Nc][Nd];
	Double_t Polarization[Nb][Nc][Nd];
	Double_t ePolarization[Nb][Nc][Nd];
	TLatex *mytex=new TLatex(0.0, 0.0,"mytex");
	for (int b = 0; b < Nb; b++)
	{
		cancount=1;
		for (int c = 0; c < Nc; c++)
		{
			for (int d = 0; d < Nd; d++)
			{	
				cPol[b]->cd(cancount);
				cancount += 1;
				//*///
				hPol[b][c][d]->Fit("f1");
				p0[b][c][d] = f1->GetParameter(0);
				ep0[b][c][d] = f1->GetParError(0);
				p1[b][c][d] = f1->GetParameter(1);
				ep1[b][c][d] = f1->GetParError(1);
				Polarization[b][c][d] = p1[b][c][d];
				ePolarization[b][c][d] = ep1[b][c][d];
				//*///
				/*///
				hPol[b][c][d]->Fit("pol1");
				TF1 *myfit = hPol[b][c][d]->GetFunction("pol1");
				p0[b][c][d] = myfit->GetParameter(0);
				ep0[b][c][d] = myfit->GetParError(0);
				p1[b][c][d] = myfit->GetParameter(1);
				ep1[b][c][d] = myfit->GetParError(1);
				Polarization[b][c][d] = (-1/alpha)*(p1[b][c][d]/p0[b][c][d]);
				ePolarization[b][c][d] = (-1/alpha)*( (ep0[b][c][d])*(p1[b][c][d]/(p0[b][c][d]*p0[b][c][d])) + (ep1[b][c][d]/p0[b][c][d])  ); 
				//*///
				cout << "p0 = " << p0[b][c][d] << "  ep0 = " << ep0[b][c][d] <<"  p1 = " << p1[b][c][d] << "  ep1 = " << ep1[b][c][d] <<endl;
				cout << "Polarization = " << Polarization[b][c][d] << "  ePolarization = " << ePolarization[b][c][d] <<endl;
				mytex=new TLatex(-0.4, 0,Form("P = %5.3f #pm %5.3f ",Polarization[b][c][d],ePolarization[b][c][d]));
				mytex->Draw("SAME");
	
			}
		}
	}
	
	
	
	
	if (AddWithWeight)
	{
		
		//just to check
		TCanvas *cBeam = new TCanvas("cBeam","cBeam",800,600);
		cBeam->Divide(2,0);
		cBeam->cd(1);
		TH1D *hb=new TH1D("hb","",27,2.8,5.5);
		TH1D *hBeamW[NWBins];
		TH1D *hBeam;
		hBeam = (TH1D*)hb->Clone(Form("hBeam"));
		hBeam->SetMinimum(0);
		for (int z = 0; z < NWBins ; z++) 
		{	
			hBeamW[z] = (TH1D*)hb->Clone(Form("hBeam-W%i",z));
			tOriginal->Draw(Form("beam>>hBeam-W%i",z),WBin[z]);
			hBeamW[z]->SetMinimum(0);
			hBeam->Add(hBeamW[z],W[z]);	
		}
	

		hBeam->Draw();
		
		cBeam->cd(2);
		TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
		TTree *tData = (TTree*)fData->Get("v05");
		
		TH1D *hBeamData=new TH1D("hBeamData","",27,2.8,5.5);
		tData->Draw("beam>>hBeamData");
		
		
	}
	
	
	
	
		
	
	
	
	
	
	
}