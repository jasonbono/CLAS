/* April 11 2012:  jason bono

purpose: this will take an unaltered tree (strait from the analyzer) and will make a seperate root file with the NEWBASIC cut.

use: specify the (oldfile, oldtree, newfile, newtree, filters)

*/

void NewbasicTree(){


	// this 4 line block is for running on lap or desk
	//TFile *oldfile = TFile::Open("/Users/Bono/clas/rootfiles/g12/small/v32k_small.root");
	//TFile *newfile = TFile::Open("/Users/Bono/clas/rootfiles/g12/newbasic/v32k_full_newbasic.root","RECREATE");
	//TTree *oldtree = (TTree*)oldfile->Get("v32k");
	//TTree *newtree = oldtree->CloneTree(0);
	
	//this 4 line block is for running on ifarm
	TFile *oldfile = TFile::Open("/volatile/clas/clasg12/bono/rootfiles/v37k/hadded/v37k_full.root");
	TFile *newfile = TFile::Open("/volatile/clas/clasg12/bono/rootfiles/v37k/hadded/v37k_full_newbasic.root", "RECREATE");
	TTree *oldtree = (TTree*)oldfile->Get("v37k");
	TTree *newtree = oldtree->CloneTree(0);
	
	
	//specify the new names of the new trees;
	TString newtreename = "v37k_newbasic";
	
	//now list all varibles to use in the filter
	Float_t beam, stv, scv;
	Float_t np, npip, nkm;
	Float_t nphoton_nb1;
	Float_t vx, vy, vz;	
	Float_t vtime, sctkp1, sclkp1, betakp1;
	Float_t sctkp2, sclkp2, betakp2;
	
	oldtree->SetBranchAddress("beam", &beam);
	oldtree->SetBranchAddress("stv", &stv);
	oldtree->SetBranchAddress("scv", &scv);			
	oldtree->SetBranchAddress("np", &np);
	oldtree->SetBranchAddress("npip", &npip);
	oldtree->SetBranchAddress("nkm", &nkm);
	oldtree->SetBranchAddress("nphoton_nb1", &nphoton_nb1);
	oldtree->SetBranchAddress("vx", &vx);
	oldtree->SetBranchAddress("vy", &vy);
	oldtree->SetBranchAddress("vz", &vz);
	oldtree->SetBranchAddress("vtime", &vtime);		
	oldtree->SetBranchAddress("sctkp1", &sctkp1);
	oldtree->SetBranchAddress("sclkp1", &sclkp1);	
	oldtree->SetBranchAddress("betakp1", &betakp1);
	oldtree->SetBranchAddress("sctkp2", &sctkp2);
	oldtree->SetBranchAddress("sclkp2", &sclkp2);	
	oldtree->SetBranchAddress("betakp2", &betakp2);
	
	
	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = oldtree->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{
		if(i % 100==0) // do a status cout every every 100 entries
		{
			Float_t ii=i;
			Float_t iii=nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (ii/iii)*100.0 << "% of the job" << endl;
		}
		oldtree->GetEntry(i);
		
		//the  newbasictree		
	 	bool cut_n = np<2&&npip<1&&nkm<1;
	 	bool cut_np = nphoton_nb1<2;
	 	bool cut_vcut = abs(vz+90)<30&&sqrt(vx*vx+vy*vy)<7;
	 	bool cut_beam = beam>3.3;
	 	bool cut_st = abs(stv-scv)<1;
	 	bool cut_tof1 = abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4;
	 	bool cut_tof2 = abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1;
	 	bool cut_newbasic = cut_n&&cut_np&&cut_vcut&&cut_beam&&cut_st&&cut_tof1&&cut_tof2;		
		if ( cut_newbasic )
		{ 
			newtree->Fill();
		}
	}
	
	//the new tree
	newtree->Write(newtreename);
	
	//save the changes to the new file
	newfile->Write();
	

	//see how much the data was reduced
	Long64_t nentries = oldtree->GetEntries();
	Long64_t nentries_res = newtree->GetEntries();
	
	cout << "The number of entries in oldtree is " << nentries << endl;
	cout << "The number of entries in newtree is " << nentries_res << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf2 = nentries_res;
	cout << 100.0*(( nf - nf2 )/(nf))  << " % of entries were taken out of the original tree " << endl;

	//quit root
 	gROOT->ProcessLine(".q");
}


