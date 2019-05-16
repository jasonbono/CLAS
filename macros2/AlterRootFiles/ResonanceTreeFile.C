/* 

Author: Jason Bono

Date: January 31 2013

Purpose: To write a new file containing only the events that passed the sidebands


*/


void ResonanceTreeFile()
{


	TFile *file = TFile::Open("~/clas/rootfiles/g12/2kppim/hadded/2kppim-v05.root"); 
	TTree *tOriginal = (TTree*)file->Get("v05");  //<---edit here
	TFile *fileNew = new TFile("~/clas/rootfiles/g12/Reduced/2kppim-v05-resonance.root","RECREATE"); //<---edit here	
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "v05_resonance";

	


	//now list all varibles to use in the filter
	Float_t beam, stv, scv;
	Float_t np, npip, nkm;
	Float_t nphoton_nb1;
	Float_t vx, vy, vz;	
	Float_t vtime, sctkp1, sclkp1, betakp1;
	Float_t sctkp2, sclkp2, betakp2;

	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("stv", &stv);
	tOriginal->SetBranchAddress("scv", &scv);		
	tOriginal->SetBranchAddress("np", &np);
	tOriginal->SetBranchAddress("npip", &npip);
	tOriginal->SetBranchAddress("nkm", &nkm);
	tOriginal->SetBranchAddress("nphoton_nb1", &nphoton_nb1);
	tOriginal->SetBranchAddress("vx", &vx);
	tOriginal->SetBranchAddress("vy", &vy);
	tOriginal->SetBranchAddress("vz", &vz);
	tOriginal->SetBranchAddress("vtime", &vtime);		
	tOriginal->SetBranchAddress("sctkp1", &sctkp1);
	tOriginal->SetBranchAddress("sclkp1", &sclkp1);	
	tOriginal->SetBranchAddress("betakp1", &betakp1);
	tOriginal->SetBranchAddress("sctkp2", &sctkp2);
	tOriginal->SetBranchAddress("sclkp2", &sclkp2);	
	tOriginal->SetBranchAddress("betakp2", &betakp2);


	//loop over the entries and fill the new tree for those passing the filter
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{

		if(i % 100==0) { 
			// do a cout every every 100 entries
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		}
		tOriginal->GetEntry(i);


		//the resonance tree cuts
		bool cut_tof22 = abs(vtime-(sctkp2-sclkp2/(betakp2*29.99))) < 0.5;
		bool cut_tof12 = abs(vtime-(sctkp1-sclkp1/(betakp1*29.99))) < 0.15;
		bool cut_n = np<2&&npip<1&&nkm<1;
		bool cut_np = nphoton_nb1<2;
		bool cut_st = abs(stv-scv)<1;
		bool cut_bb = beam > 3.6;
		bool cut_vv = (vx**2+vy**2) < 3;
		bool cut_tof11 = abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<0.5;
		bool cut_tof12 = abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.15;
		bool cut_xtra = cut_bb && cut_vv && cut_tof11 && cut_tof12;
		bool cut_resonate = cut_xtra && cut_n && cut_np && cut_st;
		if ( cut_resonate )
		{ 
			tNew->Fill();
		}
	}
	
	//fill the Resonance tree
	cout <<"Filling the Resonance tree" <<endl;
	tNew->Write(tNewName);

	
	//see how much the data was reduced
	Long64_t nentries_Resonance = tNew->GetEntries();
	cout << "The number of entries in tOriginal is " << nentries << endl;
	cout << "The number of entries in tNew is " << nentries_Resonance << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf3 = nentries_Resonance;
	cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;	



	//quit root
	gROOT->ProcessLine(".q");
}

		
		
		
	