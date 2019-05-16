/* 

Author: Jason Bono

Date: January 9 2013

Purpose: To write a new file containing the out of time side band events.

Usage:

*/


void SidebandFile()
{



	
	//* //<--------------- FOR SIMULATION ON FARM
	TFile *file = TFile::Open("/w/hallb/clasg12/jbono/sim/DATA/hadded/MC_i3_2kppim.root");  
	TTree *tOriginal = (TTree*)file->Get("gpp2kppim"); 
	TFile *fileNew = new TFile("/w/hallb/clasg12/jbono/sim/DATA/hadded/Reduced/MC_i3_2kppim_sb.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "gpp2kppim_sb";
	//*/
	
	

	
	/* //<--------------- FOR SIMULATION ON LOCAL
	TFile *file = TFile::Open("~/clas/rootfiles/LINKS/sim/MC_i2_2kppim.root");  
	TTree *tOriginal = (TTree*)file->Get("gpp2kppim"); 
	TFile *fileNew = new TFile("~/clas/rootfiles/g12/mc/Reduced/MC_i2_2kppim_sb.root","RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "gpp2kppim_sb";
	//*/
	
	
	/* //<--------------- FOR DATA ON LOCAL
	TFile *file = TFile::Open("~/clas/rootfiles/g12/2kppim/hadded/2kppim-v05.root");  //<---edit here
	TTree *tOriginal = (TTree*)file->Get("v05");  //<---edit here
	TFile *fileNew = new TFile("~/clas/rootfiles/g12/Reduced/2kppim-v05-sb.root","RECREATE"); //<---edit here	
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "v05_sb"; //<---edit here
	//*/


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

		if(i % 10000==0) 
		{
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is " << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
		}
			
		tOriginal->GetEntry(i);

		//the  new tree		
	 	//bool cut_n = np<2&&npip<1&&nkm<1;
	 	//bool cut_np = nphoton_nb1<2;
	 	//bool cut_vcut = abs(vz+90)<30&&sqrt(vx*vx+vy*vy)<7;
	 	bool cut_beam = beam>2.8;
	 	bool cut_st = abs(stv-scv)>1;  
	 	bool cut_tof1 = abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))>0.4; //this is what produces the side band
	 	bool cut_tof2 = abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))>1.1; //this is what produces the side band
		bool cut_sb = cut_st||cut_tof1||cut_tof2;
		bool cut = cut_beam&&cut_sb;		
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

	//close the file
	fileNew->Close();

	//quit root
	gROOT->ProcessLine(".q");
}