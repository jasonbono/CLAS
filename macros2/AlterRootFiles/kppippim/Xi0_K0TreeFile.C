

/* 

Author: Jason Bono

Date: Feb 13 2013

Purpose: To write a new lighter file containing only the events that passed the sidebands


*/


void Xi0_K0TreeFile()
{

	
	

	

	//* //<-----------------------------------------
	TFile *file = TFile::Open("/Users/Bono/clas/rootfiles/g12/kppippim/kppippim-v02.root");  
	TTree *tOriginal = (TTree*)file->Get("v02"); 
	TFile *fileNew = new TFile("/Users/Bono/clas/rootfiles/g12/kppippim/kppippim-v02_K0.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "v02_K0";
	//*/		

	

	//now list all varibles to use in the filter
	Float_t mpippim;
	tOriginal->SetBranchAddress("mpippim", &mpippim);

	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{

		if(i % 10000==0) { 
			// do a cout every every 10000 entries
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		}
		tOriginal->GetEntry(i);

		//filter critera for the new tree
		bool cut_mpippim = abs(mpippim - 0.497614) < 0.01;
		if ( cut_mpippim )
		{ 
			tNew->Fill();
		}
	}
	
	//fill the Basic tree
	cout <<"Filling the K0 tree" <<endl;
	tNew->Write(tNewName);

	
	//see how much the data was reduced
	Long64_t nentries_Basic = tNew->GetEntries();
	cout << "The number of entries in tOriginal is " << nentries << endl;
	cout << "The number of entries in tNew is " << nentries_Basic << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf3 = nentries_Basic;
	cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;	



	//quit root
	gROOT->ProcessLine(".q");
	
}