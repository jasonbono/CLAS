/* 

Author: Jason Bono

Date: January 10 2013

Purpose: To write a new file containing the events in the mass hypersphere.

Usage:    > root -l -b 
		  > .L HypersphereFile("somefile.root")

		  which will output somefile_Basic.root

*/

#include "/Users/Bono/clas/myDefinitions/Hypersphere.h" //for local
//#include "/u/home/jbono/myDefinitions/Hypersphere.h" //for farm
void HypersphereFile(TString passed)
{

	int Depth = depth;
	string input(passed);
	string filename = input.substr(0,input.find_last_of("."));
	string extention = input.substr(input.find_last_of("."));
	string tackon(Form("_Mass%i",Depth));
	string output = filename + tackon + extention;
	cout <<"input = "<< input <<"   output = " <<output<<endl;


	//string treename("gpp2kppim");
	string treename("v16");
	TFile *file = TFile::Open(input.c_str());  
	TTree *tOriginal = (TTree*)file->Get(treename.c_str()); 
	TFile *fileNew = new TFile(output.c_str(),"RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = treename.c_str();


	//now list all varibles to use in the filter
	Float_t mmkpkp,mmkpkppim,mlampim,mcasmMpim;
	tOriginal->SetBranchAddress("mmkpkp", &mmkpkp);
	tOriginal->SetBranchAddress("mmkpkppim", &mmkpkppim);
	tOriginal->SetBranchAddress("mlampim", &mlampim);
	tOriginal->SetBranchAddress("mcasmMpim", &mcasmMpim);

	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{

		if(i % 10000==0) 
		{
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is " << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		}
			
		tOriginal->GetEntry(i);
		Bool_t cut = sqrt((mmkpkp-MASS_Xi)*(mmkpkp-MASS_Xi)/(widthA*widthA)+(mmkpkppim-MASS_Lambda)*(mmkpkppim-MASS_Lambda)/(widthB*widthB)+(mlampim-MASS_Xi)*(mlampim-MASS_Xi)/(widthC*widthC)+(mcasmMpim-MASS_Lambda)*(mcasmMpim-MASS_Lambda)/(widthD*widthD)) < 1;
		if ( cut )
		{ 	
			//Fill the new tree with events
			tNew->Fill();
		}
	}
	//Write the New tree
	cout <<"Filling the New tree" <<endl;
	tNew->Write(tNewName);


	//see how much the data was reduced
	Long64_t nentries_New = tNew->GetEntries();
	cout << "The number of entries in the original tree is " << nentries << endl;
	cout << "The number of entries in the new tree is " << nentries_New << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf3 = nentries_New;
	cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;	


	fileNew->Close();
	gROOT->ProcessLine(".q");
}
