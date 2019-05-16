
/* 

Author: Jason Bono

Date: October 18 2012

Purpose: To add a new tree of filtered events to the bos.root files.

Usage:  First edit the file where is says "EDIT HERE" (for data must not only hit the switch but edit two tree names),  the call with the following form:

		
		
		
--->			For Data: root -l BasicTree.C\(\"mypath\"\,\"mytopology\"\,\"v?\"\) 
			
			eg:   root -l BasicTree.C\(\"~/clas/rootfiles/LINKS\"\,\"2kppim\"\,\"v05\"\) 
			OPENS:   ~/clas/rootfiles/LINKS/2kppim-v05.root
			


--->			For Simulation:  root -l BasicTree.C\(\"mypath\"\,\"mytopology\"\,\"i?\"\) 
				
			eg:  root -l BasicTree.C\(\"~/clas/rootfiles/LINKS/sim\"\,\"2kppim\"\,\"i2\"\) 
			OPENS: ~/clas/rootfiles/LINKS/sim/MC_i2_2kppim.root
			
		
		


Update: November 16 2012: changed the cutoff beam energy from 3.3 to 2.8 GeV

*/



void BasicTree(TString path="badpath",TString topology="badtopology", TString version="badversion"){

	//if the arguments were not specified properly than quit root
	if( path=="badpath" || topology=="badpath" || version=="badversion"){
		cout <<"SPECIFY THE PATH,TOPOLOGY,AND ANALYZER VERSION"<<endl;
		gROOT->ProcessLine(".q");
	}
	
	//display the parameters
	cout << "mystring =" << path <<endl;
	cout << "topology =" << topology <<endl;
	cout << "version =" << version <<endl;
	
	
	//==========================================EDIT HERE========================================================
	//*// <-------For Simulation:
	TFile *file = TFile::Open(Form("%s/MC_%s_%s.root",path.Data(),version.Data(),topology.Data()), "UPDATE"); //data converts to a const char *
	TTree *tOriginal = (TTree*)file->Get("gpp2kppim");
	TTree *tBasic = tOriginal->CloneTree(0);
	TString tnameBasic = "gpp2kppim_Basic";
	//*/
	
	/*// <-------For Data:
	TFile *file = TFile::Open(Form("%s/%s-%s.root",path.Data(),topology.Data(),version.Data()), "UPDATE"); //data converts to a const char *
	TTree *tOriginal = (TTree*)file->Get("v05");  //<---edit here
	TTree *tBasic = tOriginal->CloneTree(0);
	TString tnameBasic = "v05_Basic";              //<----edit here
	//*/
	//======================================================================================================


	
	
	
	
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
	
		
		//the  tBasic		
 		bool cut_n = np<2&&npip<1&&nkm<1;
 		bool cut_np = nphoton_nb1<2;
 		bool cut_vcut = abs(vz+90)<30&&sqrt(vx*vx+vy*vy)<7;
 		bool cut_beam = beam>2.8;
 		bool cut_st = abs(stv-scv)<1;
 		bool cut_tof1 = abs(vtime-(sctkp1-sclkp1/(betakp1*29.99)))<0.4;
 		bool cut_tof2 = abs(vtime-(sctkp2-sclkp2/(betakp2*29.99)))<1.1;
 		bool cut_Basic = cut_n&&cut_np&&cut_vcut&&cut_beam&&cut_st&&cut_tof1&&cut_tof2;		
		//cout << cut_n << cut_np << cut_vcut << cut_beam << cut_st << cut_tof1 << cut_tof2 << endl;
		if ( cut_Basic )
		{ 
			tBasic->Fill();
		}
	
	}
	
	//fill the Basic tree
	cout <<"Filling the Basic tree" <<endl;
	tBasic->Write(tnameBasic);
	//tBasic->Print();
	//tBasic->AutoSave();

	//save the changes to the file
	//file->Write();

	//see how much the data was reduced
	Long64_t nentries_Basic = tBasic->GetEntries();
	cout << "The number of entries in tOriginal is " << nentries << endl;
	cout << "The number of entries in tBasic is " << nentries_Basic << endl;
	Float_t nf, nf2, nf3;
	nf = nentries;
	nf3 = nentries_Basic;
	cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;	


	cout << "mystring =" << path <<endl;
	cout << "topology =" << topology <<endl;
	cout << "version =" << version <<endl;
	
	
	//quit root
	gROOT->ProcessLine(".q");
}
