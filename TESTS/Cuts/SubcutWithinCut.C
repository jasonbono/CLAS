#include "/Users/Bono/clas/myDefinitions/WBins.h" 
#include "/Users/Bono/clas/myDefinitions/EXiBins.h"
#include "/Users/Bono/clas/myDefinitions/Hypersphere.h"










void SubcutWithinCut()
{
	
	TFile* fMC = new TFile("~/clas/rootfiles/LINKS/sim/MC_i3_2kppim_Basic.root");  
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim_Basic");




	

	TCut myCut = "beam > 2.8 && beam < 3.5";
	TCut mySubcut = "beam > 2.9 && beam < 3.0";
	TCut myTotal = myCut && mySubcut;


	
	//tMC->Draw("COS_pi_x",myTotal&&myCut&&mySubcut&&hypersphere);
	tMC->Draw("COS_pi_x",EXiBin[0][1]&&WBin[13]&&hypersphere);

}