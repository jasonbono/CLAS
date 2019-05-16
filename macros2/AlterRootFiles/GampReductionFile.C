
/* 
Author: Jason Bono

Date: Jan 3 2013

Purpose: To reduce the gamp file size by randomly taking out events.

Usage: run the macro shit head

*/


void GampReductionFile()
{

	//==========================================EDIT HERE========================================

	/* //<--------------- FOR SIMULATION ON FARM
	TFile *file = TFile::Open("/w/hallb/clasg12/jbono/sim/DATA/hadded/Reduced/MC_i4_gamp.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree");
	TFile *fileNew = new TFile("/w/hallb/clasg12/jbono/sim/DATA/hadded/Reduced/MC_i4_gamp_100.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "GampTree_100";
	//*/	
	
	/* //<--------------- FOR SIMULATION ON LOCAL
	TFile *file = TFile::Open("~/clas/rootfiles/LINKS/sim/MC_i2_gamp.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree");
	TFile *fileNew = new TFile("~/clas/rootfiles/g12/mc/reduced/MC_i2_gamp_100.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "GampTree_100";
	//*/
	
	//* //<--------------- FOR TEST ON LOCAL
	TFile *file = TFile::Open("~/clas/rootfiles/g12/mc/i4/MC_i4_gamp_100.root");
	TTree *tOriginal = (TTree*)file->Get("GampTree_100");
	TFile *fileNew = new TFile("./PolarizedGamp.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = Form("Polarized__Gamp",Pol1);
	//*/
	
	//===========================================================================================



	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i+= 100)
	{
		if(i % 10000==0) { 
			// do a cout every every 10000 entries
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is " << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		}
		tOriginal->GetEntry(i);
	
	
		take out every 1000 events
		if (i % 100==0)
		{ 
			tNew->Fill();
		}
		else
		{
			cout << "There is an error"<<endl;
			gROOT->ProcessLine(".q");
		{
	
		
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
	
	gROOT->ProcessLine(".q");

}

