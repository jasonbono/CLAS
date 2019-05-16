/* march 28 2012:  jason bono

purpose: to make new trees of smaller size for g12 root files by passing the original tree through a filter

use: specify the; (file being opened, oldtree, treenames, filters)



*/

void ReducedTree_samefile(){


	// specify the old file and TTree which a subset will be taken from
	//TFile *file = TFile::Open("~/clas/macros/general/AlterRootFiles/test_v32k.root", "UPDATE");
	//TTree *oldtree = (TTree*)file->Get("v32k");
	
	//TFile *file = TFile::Open("~/clas/rootfiles/g12/large/v34k_full.root", "UPDATE");
	//TTree *oldtree = (TTree*)file->Get("v34k");
	
	//TFile *file = TFile::Open("~/clas/rootfiles/g12/large/v37k_00_94.root", "UPDATE");
	//TTree *oldtree = (TTree*)file->Get("v37k");
	
	TFile *file = TFile::Open("/volatile/clas/clasg12/bono/rootfiles/v37k/hadded/v37k_00_94.root", "UPDATE");
	TTree *oldtree = (TTree*)file->Get("v37k");

	//specify the new names of the new trees;
	TString treename1 = "v37k_original";
	TString treename2 = "v37k_reduced";
	TString treename3 = "v37k_newbasic";
	
	
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
	
	

	//list all new trees to be created here and clone them from the old tree.
	TTree *reducedtree = oldtree->CloneTree(0);
	TTree *newbasictree = oldtree->CloneTree(0);

	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = oldtree->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{
		if(i % 100==0) // do a cout every every 100 entries
		{
			Float_t ii=i;
			Float_t iii=nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (i/nentries)*100 << "% of the job" << endl;
		}
		oldtree->GetEntry(i);
		
		//the reduced tree		
		bool cut_b = beam >  2.373;  //this is the threshold for Xi- production
		bool cut_t = abs(stv-scv)<3; // side band will only go out this far at max
		bool cut_reduced = cut_b && cut_t;
		if ( cut_reduced )
		{ 
			reducedtree->Fill();
		}
		
		//the  newbasictree		
	 	bool cut_n = np<2&&npip<1&&nkm<1;
	 	bool cut_np = nphoton_nb1<2;
	 	bool cut_vcut = abs(vz+90)<30&&sqrt(vx*vx+vy*vy)<7;
	 	bool cut_beam = beam>3.3;
	 	bool cut_st = abs(stv-scv)<1;
	 	bool cut_tof1 = abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4;
	 	bool cut_tof2 = abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1;
	 	bool cut_newbasic = cut_n&&cut_np&&cut_vcut&&cut_beam&&cut_st&&cut_tof1&&cut_tof2;		
		//cout << cut_n << cut_np << cut_vcut << cut_beam << cut_st << cut_tof1 << cut_tof2 << endl;
		if ( cut_newbasic )
		{ 
			newbasictree->Fill();
		}
		
	}
	
	//rename the original tree
	oldtree->Write(treename1);
	//rename the reduced tree
	reducedtree->Write(treename2);
	reducedtree->Print();
	reducedtree->AutoSave();
	//rename the newbasic tree
	newbasictree->Write(treename3);
	newbasictree->Print();
	newbasictree->AutoSave();
	
	//save the changes to the file
	file->Write();
	

	//see how much the data was reduced
	Long64_t nentries_reduced = reducedtree->GetEntries();
	Long64_t nentries_newbasic = newbasictree->GetEntries();
	cout << "The number of entries in oldtree is " << nentries << endl;
	cout << "The number of entries in reducedtree is " << nentries_reduced << endl;
	cout << "The number of entries in newbasictree is " << nentries_newbasic << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf2 = nentries_reduced;
	nf3 = nentries_newbasic;
	cout << 100.0*(( nf - nf2 )/(nf))  << " % of entries were taken out of the original tree " << endl;
	cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;	



	//quit root
 	gROOT->ProcessLine(".q");
}








//extra crap



	/*/-------------------------------------------- plot to check ------------------------------------
	TCanvas *c=new TCanvas("c", "", 900, 900);
	c->Divide(2,0);
	c->cd(1);
	oldtree->Draw("beam");
	c->cd(2);
	newtree->Draw("beam");
	*///--------------------------------------------------------------------------------------------
	
	
	
	
	
	



//TCut beam="beam>3.3"
//TCut st="abs(stv-scv)<1";








