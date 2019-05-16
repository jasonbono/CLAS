void TreeArray()
{
	//so the moral of the story is that you can just use fucking equal signs to copy trees.  many a weeks hardship in vain.
	
	TFile *fData = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic.root");
	TTree *tData = (TTree*)fData->Get("v05");
	TFile *fMC = TFile::Open("~/clas/rootfiles/LINKS/MC-i5-2kppim_Basic.root");
	TTree *tMC = (TTree*)fMC->Get("gpp2kppim");
	
	
	
	TTree *tree[2];
	tree[0] = (TTree*)fData->Get("v05");
 	tree[1] = (TTree*)fMC->Get("gpp2kppim");
	
	TTree *crazy[2];	
	crazy[0] = tree[0];
	
	TTree *evenmorecrazy;
	evenmorecrazy = tData;
	evenmorecrazy->Draw("beam");
	

	
	
	
}