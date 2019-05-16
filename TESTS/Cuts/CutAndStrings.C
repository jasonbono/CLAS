#include "/Users/Bono/clas/myDefinitions/WBins27.h" 
#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"










void CutAndStrings()
{
	
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/sim/MC_i3_2kppim_Basic.root");  
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");




	const int Na = 2,Nb = 2,Nc = 3,Nd = 3;
	TString Cut[Na][Nb][Nc];
	Cut[0][0][0] = Bin[0][0]&&hypersphere;
	Cut[0][0][1] = Bin[0][1]&&hypersphere;			
	Cut[0][0][2] = Bin[0][2]&&hypersphere;
	Cut[0][1][0] = Bin[1][0]&&hypersphere;
	Cut[0][1][1] = Bin[1][1]&&hypersphere;			
	Cut[0][1][2] = Bin[1][2]&&hypersphere;
	Cut[1][0][0] = Bin[0][0];
	Cut[1][0][1] = Bin[0][1];			
	Cut[1][0][2] = Bin[0][2];
	Cut[1][1][0] = Bin[1][0];
	Cut[1][1][1] = Bin[1][1];			
	Cut[1][1][2] = Bin[1][2];
	
	
	TString myString = "beam > 2.8 && beam < 2.9";
	TString myCut = "beam > 2.8 && beam < 2.9";
	TCut S2C = myString;
	TString C2S = myCut; 
	TCut testa = S2C&&myCut;
	TString testb = C2S&&myString;
	
	

	
	tMC->Draw("COS_pi_x",testb);
	//tMC->Draw("COS_pi_x",WBin[11]);
	//tMC->Draw("COS_pi_x",Cut[0][0][1]);
	//tMC->Draw("COS_pi_x",Cut[0][0][1]&&WBin[11]);


}