
void PassTTree()
{
	cout<< "trying to pass"<<endl;


	TTree *mytree = new TTree;
	pass(mytree);
	
	//mytree->Draw("beam");
	cout <<"but only this many after passing:  " <<mytree->GetEntries() <<endl;
}



void pass(TTree *mytree)
{
	TFile *afile = TFile::Open("~/clas/rootfiles/LINKS/2kppim-v05-Basic-Mass.root");
	TTree *mytree = (TTree*)afile->Get("v05");
	cout << "there are this many events in the branch im trying to pass:  " << mytree->GetEntries()<<endl;
}