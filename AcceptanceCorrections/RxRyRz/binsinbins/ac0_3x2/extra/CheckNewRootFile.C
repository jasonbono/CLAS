/*
this makes sure the seperate branches were merged correctedly and correcpond to the unification branches under the approperiate cuts.

its a check of AddAcBranch2Data.

Usage: change b and c and ensure the resultin plots give the same distribution. do this for R and eR


*/

#include "/Users/Bono/clas/myDefinitions/EXiBins.h"


void CheckNewRootFile()
{
	
	const int Nb = 2,Nc = 3,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis		
	const int Np = 10; //number of pion bins
	const int Nk = 50; //# of pion bins used to get the acceptance
	const char* BinType[Nb] = {"E","Xi"};
	const char* BinNumber[Nc] = {"0","1","2"};
	const char* Axis[Nd] = {"x","y","z"};
		
	TFile *file = TFile::Open(Form("./NewRootFiles/2kppim-v05-Basic-Mass-Ac-%ibins.root",Nk));
	TTree *tree = (TTree*)file->Get("v05");
	TFile* sfile = new TFile(Form("./NewRootFiles/SimTest-%ibins.root",Nk));  
	TTree *stree = (TTree*)sfile->Get("SimTest");
	
	const int b = 0;  //bin type
	const int c = 1;  //bin number
	const int d = 2;  //axis
	
	//Data
	TCanvas *cData = new TCanvas("cData","cData",1000,800);
	cData->Divide(2,2);
	cData->cd(1);
	tree->Draw(Form("R%s%s",BinType[b],Axis[d]),EXiBin[b][c]);
	cData->cd(2);
	tree->Draw(Form("R%s%s%s",BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]);
	cData->cd(3);
	tree->Draw(Form("eR%s%s",BinType[b],Axis[d]),EXiBin[b][c]);
	cData->cd(4);
	tree->Draw(Form("eR%s%s%s",BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]);
	
	//Sim
	TCanvas *cSim = new TCanvas("cSim","cSim",1000,800);
	cSim->Divide(2,2);
	cSim->cd(1);
	stree->Draw(Form("R%s%s",BinType[b],Axis[d]),EXiBin[b][c]);
	cSim->cd(2);
	stree->Draw(Form("R%s%s%s",BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]);
	cSim->cd(3);
	stree->Draw(Form("eR%s%s",BinType[b],Axis[d]),EXiBin[b][c]);
	cSim->cd(4);
	stree->Draw(Form("eR%s%s%s",BinType[b],BinNumber[c],Axis[d]),EXiBin[b][c]);
	
	
	
	
}