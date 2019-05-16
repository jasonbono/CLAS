
/* 
Author: Jason Bono

Date: Jan 3 2013

Purpose: To reduce the gamp file size by randomly taking out events.

Usage: run the macro shit head

*/


void GampReduction()
{

	//==========================================EDIT HERE========================================
	//*// 
	TFile *file = TFile::Open("~/clas/rootfiles/LINKS/sim/MC_i2_gamp.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree");
	TFile *fileNew = new TFile("~/clas/rootfiles/g12/mc/reduced/MC_i2_gamp_1000.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "GampTree_1000";
	//*/
	//===========================================================================================



	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i+= 1000)
	{
		if(i % 10000==0) { 
			// do a cout every every 10000 entries
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is " << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		}
		tOriginal->GetEntry(i);
	
	
		//take out every 1000 events
		//if (i % 1000==0)
		//{ 
			tNew->Fill();
		//}
	
	
		
	}

	//fill the New tree
	cout <<"Filling the New tree" <<endl;
	tNew->Write(tNewName);


	//see how much the data was reduced
	Long64_t nentries_New = tNew->GetEntries();
	cout << "The number of entries in tOriginal is " << nentries << endl;
	cout << "The number of entries in tNew is " << nentries_New << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf3 = nentries_New;
	cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;

	//close the file
	fileNew->Close();

}

