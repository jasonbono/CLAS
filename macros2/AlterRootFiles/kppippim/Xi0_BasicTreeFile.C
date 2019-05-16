/* 

Author: Jason Bono

Date: Feb 13 2013

Purpose: To write a new lighter file containing only the events that passed the sidebands


*/


void Xi0_BasicTreeFile()
{

	
	

	

	//* //<-----------------------------------------
	TFile *file = TFile::Open("/Users/Bono/clas/rootfiles/g12/kppippim/v03.root");  
	TTree *tOriginal = (TTree*)file->Get("v03"); 
	TFile *fileNew = new TFile("/Users/Bono/clas/rootfiles/g12/kppippim/v03_Basic.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "v03_Basic";
	//*/		

	/* //<-----------------------------------------
	TFile *file = TFile::Open("/Users/Bono/clas/rootfiles/g12/kppippim/kppippim-v02.root");  
	TTree *tOriginal = (TTree*)file->Get("v02"); 
	TFile *fileNew = new TFile("/Users/Bono/clas/rootfiles/g12/kppippim/kppippim-v02_Basic.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "v02_Basic";
	//*/
	

	

	//now list all varibles to use in the filter
	Float_t beam, stv, scv;
	Float_t nphoton_nb1;
	Float_t vx, vy, vz;	
	Float_t vtime, sctkp, sclkp, betakp;
	Float_t mpippim;
	Float_t mmkppippim;
	
	
	tOriginal->SetBranchAddress("mpippim", &mpippim);
	tOriginal->SetBranchAddress("mmkppippim", &mmkppippim);
	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("stv", &stv);
	tOriginal->SetBranchAddress("scv", &scv);		
	tOriginal->SetBranchAddress("nphoton_nb1", &nphoton_nb1);
	tOriginal->SetBranchAddress("vx", &vx);
	tOriginal->SetBranchAddress("vy", &vy);
	tOriginal->SetBranchAddress("vz", &vz);
	tOriginal->SetBranchAddress("vtime", &vtime);		
	tOriginal->SetBranchAddress("sctkp", &sctkp);
	tOriginal->SetBranchAddress("sclkp", &sclkp);	
	tOriginal->SetBranchAddress("betakp", &betakp);



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

		//the tBasic
		//the tBasic
		bool cut_np = nphoton_nb1<2;
		bool cut_vcut = abs(vz+90)<30&&sqrt(vx*vx+vy*vy)<7;
		bool cut_beam = beam>2.8;
		bool cut_st = abs(stv-scv)<1;
		bool cut_tof = abs(vtime-(sctkp-sclkp/(betakp*29.99)))<1.1;
		bool cut_mpippim = abs(mpippim - 0.497614)<0.05;
		bool cut_mpippim = mpippim > 0.447614 && mpippim < 0.547614; 
		bool cut_mmkppippim = mmkppippim > 1.0 && mmkppippim < 2.00;
		//cut_mpippim = 1;
		//cut mmkppippim = 1;
		bool cut_Basic = cut_np&&cut_vcut&&cut_beam&&cut_st&&cut_tof&&cut_mpippim&&cut_mmkppippim;

		if ( cut_Basic )
		{ 
			tNew->Fill();
		}

	}
	
	//fill the Basic tree
	cout <<"Filling the Basic tree" <<endl;
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