




#include "/Users/Bono/clas/myDefinitions/EXiBins.h"


void EXiAcceptance()
{
	const int Na = 3; //Data Type (0=Data,1=MC,2=Gen)
	const int Nb = 2; //number of bins types (e and xi)
	const int Nc = 3; //number of EXiBins
	const int Ns = 30; //nuber of bins in acceptance corrections (s for slices)
	const char* DataType[Na] = {"Data","MC","Gen"};
	const char* BinType[Nb] = {"E","Xi"};
	const char* Quantities[Nb] = {"beam","Xcmtheta"};
	float factor[Na] = {1,1,100}; //100 for the gamp reduction factor
	
	Double_t emin = 2.8;
    Double_t emax = 5.5;
    Double_t estep = (emax - emin)/Ns;
	Double_t ximin = -1;
	Double_t ximax = 1;
	Double_t xistep = (ximax - ximin)/Ns;
	
	TCut exibin[2][Ns];
	for (int s=0;s<Ns;s++)
	{
		exibin[0][s] = Form("beam >= 2.8 + %f && beam <= 2.8 + %f",s*estep,(s+1)*estep);
		//cout << Form("beam >= 2.8 + %f && beam <= 2.8 + %f",s*estep,(s+1)*estep) <<endl;
		
		exibin[1][s] = Form("Xcmtheta >= -1 + %f && Xcmtheta <= -1 + %f",s*xistep,(s+1)*xistep);
		//cout << Form("Xcmtheta >= -1 + %f && Xcmtheta <= -1 + %f",s*xistep,(s+1)*xistep) <<endl;
	}
	
	
	//all three input trees
	TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
	TTree *tData = (TTree*)fData->Get("v05");
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/MC-i5-2kppim_Basic_Mass.root");  
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	TFile* fGen = new TFile("~/clas/rootfiles/LINKS/MC-i5-gamproot-100.root");
	TTree *tGen = (TTree*)fGen->Get("GampTree");
	const TTree* TreeType[Na];
	TreeType[0] = tData;
	TreeType[1] = tMC;
	TreeType[2] = tGen;

	
	
	//model for beam spectrum and xi spectrum
	TH1F *he=new TH1F("he","",Ns,2.8,5.5); 
	he->GetYaxis()->SetTitle("Events");  
	he->GetXaxis()->SetTitle("E#gamma (GeV) ");
	he->SetMinimum(0);
	TH1F *hxi=new TH1F("hxi","",Ns,-1.0,1.0); 
	hxi->GetYaxis()->SetTitle("Events");  
	hxi->GetXaxis()->SetTitle(" Cos(#theta_{#Xi^{-}})");
	hxi->SetMinimum(0);
	TH1F *hmodel[Nb];
	hmodel[0] = (TH1F*)he->Clone("hE");
	hmodel[1] = (TH1F*)hxi->Clone("hXi");
	
	

	//fill the e and xi dists for Data, MC, Gen
	TH1F *hDist[Na][Nb][Nc];
	for (int a = 0; a < Na; a++)
	{
		for (int b = 0; b < Nb; b++)
		{
			for (int c = 0; c < Nc; c++)
			{					
				hDist[a][b][c] = (TH1F*)hmodel[b]->Clone(Form("h%s-%s%i",DataType[a],BinType[b],c));
				TreeType[a]->Draw(Form("%s >> h%s-%s%i ",Quantities[b],DataType[a],BinType[b],c),EXiBin[b][c]);
			}
		}
	}
	
			
	TH1F *hAC[Nb][Nc];
	TH1F *hCor[Nb][Nc];
	TH1F *hCorTotal[Nb];
	TH1F *hDataTotal[Nb];
	float Mean[Nb][Nc];
	TCanvas *cAC=new TCanvas("cAC","cAC",800,600);
	TCanvas *cCor=new TCanvas("cCor","cCor",800,600);
	TCanvas *cData=new TCanvas("cData","Data",800,600);

	cAC->Divide(3,3);
	cCor->Divide(3,3);
	cData->Divide(3,3);
	int cancount=0;
	for (int b = 0; b < Nb; b++)
	{
		hCorTotal[b] = (TH1F*)hmodel[b]->Clone(Form("hCorTotal-%s",BinType[b]));
		hDataTotal[b] = (TH1F*)hmodel[b]->Clone(Form("hDataTotal-%s",BinType[b]));
		for (int c = 0; c < Nc; c++)
		{
			cancount+=1;
			hAC[b][c] = (TH1F*)hmodel[b]->Clone(Form("hAC-%s%i",BinType[b],c));
			hCor[b][c] = (TH1F*)hmodel[b]->Clone(Form("hCor-%s%i",BinType[b],c));
			hAC[b][c]->Divide(hDist[1][b][c],hDist[2][b][c]);
			hCor[b][c]->Divide(hDist[0][b][c],hAC[b][c]);		
			Mean[b][c] = hCor[b][c]->GetMean();
			cout << "for bin " << BinType[b] <<c<<"  Mean = " <<Mean[b][c] <<endl;
			cAC->cd(cancount);
			hAC[b][c]->Draw();
			cCor->cd(cancount);
			hCor[b][c]->Draw();		
			cData->cd(cancount);
			hDist[0][b][c]->Draw();			
			hCorTotal[b]->Add(hCor[b][c]);
			hDataTotal[b]->Add(hDist[0][b][c]);
		}
	}	
	
	TCanvas *cCorTotal=new TCanvas("cCorTotal","cCorTotal",800,600);
	cCorTotal->Divide(2,1);
	cCorTotal->cd(1);
	hCorTotal[0]->Draw();
	cCorTotal->cd(2);
	hCorTotal[1]->Draw();

	TCanvas *cDataTotal=new TCanvas("cDataTotal","cDataTotal",800,600);
	cDataTotal->Divide(2,1);
	cDataTotal->cd(1);
	hDataTotal[0]->Draw();
	cDataTotal->cd(2);
	hDataTotal[1]->Draw();
	
	
	//*/
	
	//now find the rms in the bins
	
	
	

}