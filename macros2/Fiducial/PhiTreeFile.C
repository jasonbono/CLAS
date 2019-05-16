/*
Author: Jason Bono
Data: Aug 24 2013

Purpose: adds convient branch variables (such as sector) and filters

Usage: 
> .L PhiTree	
> PhiTree(file.root)

root files named somthing like 
/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v03-Partial.root
/Users/Bono/clas/rootfiles/g12/ppippim/full/ppippim-v03.root

*/	
	
void PhiTreeFile(TString passed)
{
	string input(passed);
	string filename = input.substr(0,input.find_last_of("."));
	string extention = input.substr(input.find_last_of("."));
	string tackon("_Phi");
	string output = filename + tackon + extention;
	cout <<"input = "<< input <<"   output = " <<output<<endl;


	string treename("v09");
	TFile *file = TFile::Open(input.c_str());  
	TTree *tOriginal = (TTree*)file->Get(treename.c_str()); 
	TFile *fileNew = new TFile(output.c_str(),"RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = treename.c_str();
	
	
	//prexisting
	//pip
	Float_t piplabphi = -100;
	tOriginal->SetBranchAddress("piplabphi", &piplabphi);
	//pim
	Float_t pimlabphi = -100;
	tOriginal->SetBranchAddress("pimlabphi", &pimlabphi);
	//p
	Float_t plabphi = -100;
	tOriginal->SetBranchAddress("plabphi", &plabphi);
	//universal (for filter)
	Float_t mm2ppippim = -100;
	Float_t missx = -100;
	Float_t missy = -100;
	Float_t stv = -100;
	Float_t scv = -100;	
	tOriginal->SetBranchAddress("mm2ppippim", &mm2ppippim);
	tOriginal->SetBranchAddress("missx", &missx);
	tOriginal->SetBranchAddress("missy", &missy);
	tOriginal->SetBranchAddress("stv", &stv);
	tOriginal->SetBranchAddress("scv", &scv);
		
	
	//new branches
	//pip
	Int_t pipsector;
	Float_t pipphiclas,pipphidiff;
	TBranch *pipsectorbranch = tNew->Branch("pipsector", &pipsector, "pipsector/I");
	TBranch *pipphiclasbranch = tNew->Branch("pipphiclas", &pipphiclas, "pipphiclas/F");
	TBranch *pipphidiffbranch = tNew->Branch("pipphidiff", &pipphidiff, "pipphidiff/F");
	//pim
	Int_t pimsector;
	Float_t pimphiclas,pimphidiff;
	TBranch *pimsectorbranch = tNew->Branch("pimsector", &pimsector, "pimsector/I");
	TBranch *pimphiclasbranch = tNew->Branch("pimphiclas", &pimphiclas, "pimphiclas/F");
	TBranch *pimphidiffbranch = tNew->Branch("pimphidiff", &pimphidiff, "pimphidiff/F");
	//p
	Int_t psector;
	Float_t pphiclas,pphidiff;
	TBranch *psectorbranch = tNew->Branch("psector", &psector, "psector/I");
	TBranch *pphiclasbranch = tNew->Branch("pphiclas", &pphiclas, "pphiclas/F");
	TBranch *pphidiffbranch = tNew->Branch("pphidiff", &pphidiff, "pphidiff/F");
	
	
	//intermediate quantities needed for new branches
	//pip
	Float_t pipphideg = 0;
	Float_t pipphiclas = 0;
	//pim
	Float_t pimphideg = 0;
	Float_t pimphiclas = 0;
	//p
	Float_t pphideg = 0;
	Float_t pphiclas = 0;
	
	
	//begin loop
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{
		tOriginal->GetEntry(i);
		if(i % 10000==0) 
		{ 
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
			cout << "piplabphi = " <<piplabphi << "pimlabphi = " <<pimlabphi << "plabphi = " <<plabphi <<endl;
		}
		
		/////////pip////////////////////////////////
		//phi convention for clas
		pipphideg = piplabphi*180;
		if (pipphideg < -30)
		{
			pipphiclas = 360 + pipphideg;
		}
		else
		{
			pipphiclas = pipphideg;
		}
		//sector
		if ( (pipphiclas > -30) && (pipphiclas < 30 ))
		{
			pipsector = 1;
		}
		else if ( (pipphiclas > 30) && (pipphiclas < 90 ))
		{
			pipsector = 2;
		}
		else if ( (pipphiclas > 90) && (pipphiclas < 150 ))
		{
			pipsector = 3;
		}
		else if ( (pipphiclas > 150) && (pipphiclas < 210 ))
		{
			pipsector = 4;
		}
		else if ( (pipphiclas > 210) && (pipphiclas < 270 ))
		{
			pipsector = 5;
		}
		else if ( (pipphiclas > 270) && (pipphiclas < 330 ))
		{
			pipsector = 6;
		}	
		//diff
		pipphidiff = (60*(pipsector - 1)) - pipphiclas;


		/////////pim////////////////////////////////
		//phi convention for clas
		pimphideg = pimlabphi*180;
		if (pimphideg < -30)
		{
			pimphiclas = 360 + pimphideg;
		}
		else
		{
			pimphiclas = pimphideg;
		}
		//sector
		if ( (pimphiclas > -30) && (pimphiclas < 30 ))
		{
			pimsector = 1;
		}
		else if ( (pimphiclas > 30) && (pimphiclas < 90 ))
		{
			pimsector = 2;
		}
		else if ( (pimphiclas > 90) && (pimphiclas < 150 ))
		{
			pimsector = 3;
		}
		else if ( (pimphiclas > 150) && (pimphiclas < 210 ))
		{
			pimsector = 4;
		}
		else if ( (pimphiclas > 210) && (pimphiclas < 270 ))
		{
			pimsector = 5;
		}
		else if ( (pimphiclas > 270) && (pimphiclas < 330 ))
		{
			pimsector = 6;
		}	
		//diff
		pimphidiff = (60*(pimsector - 1)) - pimphiclas;
		
		
		
		
		/////////p////////////////////////////////
		//phi convention for clas
		pphideg = plabphi*180;
		if (pphideg < -30)
		{
			pphiclas = 360 + pphideg;
		}
		else
		{
			pphiclas = pphideg;
		}
		//sector
		if ( (pphiclas > -30) && (pphiclas < 30 ))
		{
			psector = 1;
		}
		else if ( (pphiclas > 30) && (pphiclas < 90 ))
		{
			psector = 2;
		}
		else if ( (pphiclas > 90) && (pphiclas < 150 ))
		{
			psector = 3;
		}
		else if ( (pphiclas > 150) && (pphiclas < 210 ))
		{
			psector = 4;
		}
		else if ( (pphiclas > 210) && (pphiclas < 270 ))
		{
			psector = 5;
		}
		else if ( (pphiclas > 270) && (pphiclas < 330 ))
		{
			psector = 6;
		}	
		//diff
		pphidiff = (60*(psector - 1)) - pphiclas;
		
		
		
		//setup filter
		int st=0;
	 	if( ((scv - stv) <= 1) && ((scv - stv) >= -1)  ) st=1; 
	 	int pp=0;
	 	if( (missx > -0.1) && (missx < 0.1) && (missy > -0.1) && (missy < 0.1)  ) pp=1;
	 	int mm=0;
	 	if( (mm2ppippim > -0.12) && (mm2ppippim < 0.08) ) mm=1;
		//run the filter
		if(st&&pp&&mm)
		{
			tNew->Fill();
		}

	}
	
	tNew->Write(tNewName);
	
	









	//quit root
	gROOT->ProcessLine(".q");
}	
	
	
	
	
	
	
	
	
	
	
