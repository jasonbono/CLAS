/*
Author: Jason Bono
Data: Sep 3 2013

Usage: 
> .L FidTreeFile_2kppim	
> FiducialTreeFile(file.root)

This produces three new root files,  Reg,Tight,Loose corresponding to the tightness of the fiducial cuts

typical file to run on is
"/Users/Bono/clas/rootfiles/g12/Reduced/2kppim-v05-Basic-Mass.root"
or 
"/Users/Bono/clas/rootfiles/g12/mc/i8/SendHome/MC-i8-2kppim_Basic_Mass.root" 

*/	
	
void FidTreeFile_2kppim(TString passed)
{

	const int Np = 15;  //number of momentum bins fiducial cuts had
	const int Nt = 15;  //number of theta bins	fiducial cuts had
	const int Ns = 6;  //number of sectors
	const int Ni = 3; //number of parameters in second generation fiducial fit 
	const int Nj = 3; //number of parameters in second generation fiducial fit

	string input(passed);
	string filename = input.substr(0,input.find_last_of("."));
	string extention = input.substr(input.find_last_of("."));
	string tackon("_Fid");
	string output = filename + tackon + extention;
	cout <<"input = "<< input <<"   output = " <<output<<endl;

	string treename("v15");
	TFile *file = TFile::Open(input.c_str());
	TTree *tOriginal = (TTree*)file->Get(treename.c_str()); 
	TFile *fileNew = new TFile(output.c_str(),"RECREATE");
	//Reg
	TTree *tReg = tOriginal->CloneTree(0);
	TString tRegName = Form("%sReg",treename.c_str());
	//Tight
	TTree *tTight = tOriginal->CloneTree(0);
	TString tTightName = Form("%sTight",treename.c_str());
	//Loose
	TTree *tLoose = tOriginal->CloneTree(0);
	TString tLooseName = Form("%sLoose",treename.c_str());
	


	//read in the fitting parameters (dont change name of Pos )
	ifstream infile_Pos(Form("/Users/Bono/clas/macros2/Fiducial/txt/ThirdGen/FitParams_Pos-%i-%ibins.txt",Np,Nt));
	Float_t	ParL_Pos[Ns][Ni][Nj];
	Float_t	ParH_Pos[Ns][Ni][Nj];	
	Float_t parL_Pos[Ns][9] = {0};	
	Float_t parH_Pos[Ns][9] = {0};	
	for (int s=0; s<Ns; s++)
	{
		for (int ii=0; ii<Ni; ii++)
		{	
			for (int j=0; j<Nj; j++)
			{	
				infile_Pos >> ParL_Pos[s][ii][j]; 
				infile_Pos >> ParH_Pos[s][ii][j]; 
				parL_Pos[s][3*ii + j] = ParL_Pos[s][ii][j];
				parH_Pos[s][3*ii + j] = ParH_Pos[s][ii][j];
			}
		}
	}	
	infile_Pos.close();
	
	ifstream infile_Neg(Form("/Users/Bono/clas/macros2/Fiducial/txt/ThirdGen/FitParams_Neg-%i-%ibins.txt",Np,Nt));
	Float_t	ParL_Neg[Ns][Ni][Nj];
	Float_t	ParH_Neg[Ns][Ni][Nj];	
	Float_t parL_Neg[Ns][9] = {0};	
	Float_t parH_Neg[Ns][9] = {0};	
	for (int s=0; s<Ns; s++)
	{
		for (int ii=0; ii<Ni; ii++)
		{	
			for (int j=0; j<Nj; j++)
			{	
				infile_Neg >> ParL_Neg[s][ii][j]; 
				infile_Neg >> ParH_Neg[s][ii][j]; 
				parL_Neg[s][3*ii + j] = ParL_Neg[s][ii][j];
				parH_Neg[s][3*ii + j] = ParH_Neg[s][ii][j];
			}
		}
	}	
	infile_Neg.close();
	

	
	
	//setup to get theta,phi and momentum for all three particles
	//kp1
	Float_t kp1labtheta = -100; //this is actually costheta
	Float_t pkp1 = -100;
	Float_t kp1labphi = -100; //this is in rad/pi from {-1, 1}
	tOriginal->SetBranchAddress("kp1labtheta", &kp1labtheta);
	tOriginal->SetBranchAddress("pkp1", &pkp1);
	tOriginal->SetBranchAddress("kp1labphi", &kp1labphi);
	//kp2
	Float_t kp2labtheta = -100; //this is actually costheta
	Float_t pkp2 = -100;
	Float_t kp2labphi = -100; //this is in rad/pi from {-1, 1}
	tOriginal->SetBranchAddress("kp2labtheta", &kp2labtheta);
	tOriginal->SetBranchAddress("pkp2", &pkp2);
	tOriginal->SetBranchAddress("kp2labphi", &kp2labphi);
	//pim
	Float_t pilabtheta = -100; //this is actually costheta
	Float_t ppim = -100;
	Float_t pilabphi = -100; //this is in rad/pi from {-1, 1}
	tOriginal->SetBranchAddress("pilabtheta", &pilabtheta);
	tOriginal->SetBranchAddress("ppim", &ppim);
	tOriginal->SetBranchAddress("pilabphi", &pilabphi);
	
	
	
	//new branches in Reg file (nominal cuts)
	//kp1
	Float_t kp1phideg = -100;
	Float_t kp1phiclas = -100;
	Float_t kp1phidiff = -100;
	Int_t kp1sector = -100;
	Float_t kp1thetadeg = -100;
	TBranch *kp1phidegbranch = tReg->Branch("kp1phideg", &kp1phideg, "kp1phideg/F");
	TBranch *kp1phiclasbranch = tReg->Branch("kp1phiclas", &kp1phiclas, "kp1phiclas/F");
	TBranch *kp1phidiffbranch = tReg->Branch("kp1phidiff", &kp1phidiff, "kp1phidiff/F");
	TBranch *kp1sectorbranch = tReg->Branch("kp1sector", &kp1sector, "kp1sector/I");
	TBranch *kp1thetadegbranch = tReg->Branch("kp1thetadeg", &kp1thetadeg, "kp1thetadeg/F");
	//kp2
	Float_t kp2phideg = -100;
	Float_t kp2phiclas = -100;
	Float_t kp2phidiff = -100;
	Int_t kp2sector = -100;
	Float_t kp2thetadeg = -100;
	TBranch *kp2phidegbranch = tReg->Branch("kp2phideg", &kp2phideg, "kp2phideg/F");
	TBranch *kp2phiclasbranch = tReg->Branch("kp2phiclas", &kp2phiclas, "kp2phiclas/F");
	TBranch *kp2phidiffbranch = tReg->Branch("kp2phidiff", &kp2phidiff, "kp2phidiff/F");
	TBranch *kp2sectorbranch = tReg->Branch("kp2sector", &kp2sector, "kp2sector/I");
	TBranch *kp2thetadegbranch = tReg->Branch("kp2thetadeg", &kp2thetadeg, "kp2thetadeg/F");	
	//pim
	Float_t pimphideg = -100;
	Float_t pimphiclas = -100;
	Float_t pimphidiff = -100;
	Int_t pimsector = -100;
	Float_t pimthetadeg = -100;
	TBranch *pimphidegbranch = tReg->Branch("pimphideg", &pimphideg, "pimphideg/F");
	TBranch *pimphiclasbranch = tReg->Branch("pimphiclas", &pimphiclas, "pimphiclas/F");
	TBranch *pimphidiffbranch = tReg->Branch("pimphidiff", &pimphidiff, "pimphidiff/F");
	TBranch *pimsectorbranch = tReg->Branch("pimsector", &pimsector, "pimsector/I");
	TBranch *pimthetadegbranch = tReg->Branch("pimthetadeg", &pimthetadeg, "pimthetadeg/F");
	
	
	//new branches in Tight file
	//kp1
	Float_t kp1phideg = -100;
	Float_t kp1phiclas = -100;
	Float_t kp1phidiff = -100;
	Int_t kp1sector = -100;
	Float_t kp1thetadeg = -100;
	TBranch *kp1phidegbranch = tTight->Branch("kp1phideg", &kp1phideg, "kp1phideg/F");
	TBranch *kp1phiclasbranch = tTight->Branch("kp1phiclas", &kp1phiclas, "kp1phiclas/F");
	TBranch *kp1phidiffbranch = tTight->Branch("kp1phidiff", &kp1phidiff, "kp1phidiff/F");
	TBranch *kp1sectorbranch = tTight->Branch("kp1sector", &kp1sector, "kp1sector/I");
	TBranch *kp1thetadegbranch = tTight->Branch("kp1thetadeg", &kp1thetadeg, "kp1thetadeg/F");
	//kp2
	Float_t kp2phideg = -100;
	Float_t kp2phiclas = -100;
	Float_t kp2phidiff = -100;
	Int_t kp2sector = -100;
	Float_t kp2thetadeg = -100;
	TBranch *kp2phidegbranch = tTight->Branch("kp2phideg", &kp2phideg, "kp2phideg/F");
	TBranch *kp2phiclasbranch = tTight->Branch("kp2phiclas", &kp2phiclas, "kp2phiclas/F");
	TBranch *kp2phidiffbranch = tTight->Branch("kp2phidiff", &kp2phidiff, "kp2phidiff/F");
	TBranch *kp2sectorbranch = tTight->Branch("kp2sector", &kp2sector, "kp2sector/I");
	TBranch *kp2thetadegbranch = tTight->Branch("kp2thetadeg", &kp2thetadeg, "kp2thetadeg/F");	
	//pim
	Float_t pimphideg = -100;
	Float_t pimphiclas = -100;
	Float_t pimphidiff = -100;
	Int_t pimsector = -100;
	Float_t pimthetadeg = -100;
	TBranch *pimphidegbranch = tTight->Branch("pimphideg", &pimphideg, "pimphideg/F");
	TBranch *pimphiclasbranch = tTight->Branch("pimphiclas", &pimphiclas, "pimphiclas/F");
	TBranch *pimphidiffbranch = tTight->Branch("pimphidiff", &pimphidiff, "pimphidiff/F");
	TBranch *pimsectorbranch = tTight->Branch("pimsector", &pimsector, "pimsector/I");
	TBranch *pimthetadegbranch = tTight->Branch("pimthetadeg", &pimthetadeg, "pimthetadeg/F");
	
	
	
	
	//new branches in Loose file
	//kp1
	Float_t kp1phideg = -100;
	Float_t kp1phiclas = -100;
	Float_t kp1phidiff = -100;
	Int_t kp1sector = -100;
	Float_t kp1thetadeg = -100;
	TBranch *kp1phidegbranch = tLoose->Branch("kp1phideg", &kp1phideg, "kp1phideg/F");
	TBranch *kp1phiclasbranch = tLoose->Branch("kp1phiclas", &kp1phiclas, "kp1phiclas/F");
	TBranch *kp1phidiffbranch = tLoose->Branch("kp1phidiff", &kp1phidiff, "kp1phidiff/F");
	TBranch *kp1sectorbranch = tLoose->Branch("kp1sector", &kp1sector, "kp1sector/I");
	TBranch *kp1thetadegbranch = tLoose->Branch("kp1thetadeg", &kp1thetadeg, "kp1thetadeg/F");
	//kp2
	Float_t kp2phideg = -100;
	Float_t kp2phiclas = -100;
	Float_t kp2phidiff = -100;
	Int_t kp2sector = -100;
	Float_t kp2thetadeg = -100;
	TBranch *kp2phidegbranch = tLoose->Branch("kp2phideg", &kp2phideg, "kp2phideg/F");
	TBranch *kp2phiclasbranch = tLoose->Branch("kp2phiclas", &kp2phiclas, "kp2phiclas/F");
	TBranch *kp2phidiffbranch = tLoose->Branch("kp2phidiff", &kp2phidiff, "kp2phidiff/F");
	TBranch *kp2sectorbranch = tLoose->Branch("kp2sector", &kp2sector, "kp2sector/I");
	TBranch *kp2thetadegbranch = tLoose->Branch("kp2thetadeg", &kp2thetadeg, "kp2thetadeg/F");	
	//pim
	Float_t pimphideg = -100;
	Float_t pimphiclas = -100;
	Float_t pimphidiff = -100;
	Int_t pimsector = -100;
	Float_t pimthetadeg = -100;
	TBranch *pimphidegbranch = tLoose->Branch("pimphideg", &pimphideg, "pimphideg/F");
	TBranch *pimphiclasbranch = tLoose->Branch("pimphiclas", &pimphiclas, "pimphiclas/F");
	TBranch *pimphidiffbranch = tLoose->Branch("pimphidiff", &pimphidiff, "pimphidiff/F");
	TBranch *pimsectorbranch = tLoose->Branch("pimsector", &pimsector, "pimsector/I");
	TBranch *pimthetadegbranch = tLoose->Branch("pimthetadeg", &pimthetadeg, "pimthetadeg/F");
	



	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{
		tOriginal->GetEntry(i);	

		///////////////////////////kp1///////////////////////
		//get theta in degrees
		kp1thetadeg = (180/3.1415)*acos(kp1labtheta);
		//get phi in deg,clas
		kp1phideg = kp1labphi*180;
		if (kp1phideg < -30)
		{
			kp1phiclas = 360 + kp1phideg;
		}
		else
		{
			kp1phiclas = kp1phideg;
		}
		//get sectors
		if ( (kp1phiclas > -30) && (kp1phiclas < 30 ))
		{
			kp1sector = 1;
		}
		else if ( (kp1phiclas > 30) && (kp1phiclas < 90 ))
		{
			kp1sector = 2;
		}
		else if ( (kp1phiclas > 90) && (kp1phiclas < 150 ))
		{
			kp1sector = 3;
		}
		else if ( (kp1phiclas > 150) && (kp1phiclas < 210 ))
		{
			kp1sector = 4;
		}
		else if ( (kp1phiclas > 210) && (kp1phiclas < 270 ))
		{
			kp1sector = 5;
		}
		else if ( (kp1phiclas > 270) && (kp1phiclas < 330 ))
		{
			kp1sector = 6;
		}
		//get phidiff
		kp1phidiff = (60*(kp1sector - 1)) - kp1phiclas;
		
		//////////////////////////////////kp2///////////////
		//get theta in degrees
		kp2thetadeg = (180/3.1415)*acos(kp2labtheta);
		//get phi in deg,clas
		kp2phideg = kp2labphi*180;
		if (kp2phideg < -30)
		{
			kp2phiclas = 360 + kp2phideg;
		}
		else
		{
			kp2phiclas = kp2phideg;
		}
		//get sectors
		if ( (kp2phiclas > -30) && (kp2phiclas < 30 ))
		{
			kp2sector = 1;
		}
		else if ( (kp2phiclas > 30) && (kp2phiclas < 90 ))
		{
			kp2sector = 2;
		}
		else if ( (kp2phiclas > 90) && (kp2phiclas < 150 ))
		{
			kp2sector = 3;
		}
		else if ( (kp2phiclas > 150) && (kp2phiclas < 210 ))
		{
			kp2sector = 4;
		}
		else if ( (kp2phiclas > 210) && (kp2phiclas < 270 ))
		{
			kp2sector = 5;
		}
		else if ( (kp2phiclas > 270) && (kp2phiclas < 330 ))
		{
			kp2sector = 6;
		}
		//get phidiff
		kp2phidiff = (60*(kp2sector - 1)) - kp2phiclas;
		
		
		//////////////////////////////////pim///////////////
		//get theta in degrees
		pimthetadeg = (180/3.1415)*acos(pilabtheta);
		//get phi in deg,clas
		pimphideg = pilabphi*180; //
		if (pimphideg < -30)
		{
			pimphiclas = 360 + pimphideg;
		}
		else
		{
			pimphiclas = pimphideg;
		}
		//get sectors
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
		//get phidiff
		pimphidiff = (60*(pimsector - 1)) - pimphiclas; 
		
						
		
		
		//set x and y for funciton
		Float_t kp1var[2] = {pkp1,kp1thetadeg};	
		Float_t kp2var[2] = {pkp2,kp2thetadeg};	
		Float_t pimvar[2] = {ppim,pimthetadeg};		
		
		//call function
		//kp1
		float kp1lowReg = 0;
		kp1lowReg = FidFunc (kp1var,parL_Pos[kp1sector - 1]); 
		float kp1highReg = 0;
		kp1highReg = FidFunc (kp1var,parH_Pos[kp1sector - 1]);
		//kp2
		float kp2lowReg = 0;
		kp2lowReg = FidFunc (kp2var,parL_Pos[kp2sector - 1]); 
		float kp2highReg = 0;
		kp2highReg = FidFunc (kp2var,parH_Pos[kp2sector - 1]);
		//pim
		float pimlowReg = 0;
		pimlowReg = FidFunc (pimvar,parL_Neg[pimsector - 1]); 
		float pimhighReg = 0;
		pimhighReg = FidFunc (pimvar,parH_Neg[pimsector - 1]);
		
		
		//Tight
		float kp1lowTight = kp1lowReg + 2;
		float kp1highTight = kp1highReg - 2;
		float kp2lowTight = kp2lowReg + 2;
		float kp2highTight = kp2highReg - 2;
		float pimlowTight = pimlowReg + 2;
		float pimhighTight = pimhighReg - 2;
		
		//Loose
		float kp1lowLoose = kp1lowReg - 2;
		float kp1highLoose = kp1highReg + 2;
		float kp2lowLoose = kp2lowReg - 2;
		float kp2highLoose = kp2highReg + 2;
		float pimlowLoose = pimlowReg - 2;
		float pimhighLoose = pimhighReg + 2;
		
		
		if ( (kp1phidiff > kp1lowReg) && (kp1phidiff < kp1highReg) && (kp2phidiff > kp2lowReg) && (kp2phidiff < kp2highReg)  && (pimphidiff > pimlowReg) && (pimphidiff < pimhighReg) )
		{
			tReg->Fill();
		}
		if ( (kp1phidiff > kp1lowTight) && (kp1phidiff < kp1highTight) && (kp2phidiff > kp2lowTight) && (kp2phidiff < kp2highTight)  && (pimphidiff > pimlowTight) && (pimphidiff < pimhighTight) )
		{
			tTight->Fill();
		}
		if ( (kp1phidiff > kp1lowLoose) && (kp1phidiff < kp1highLoose) && (kp2phidiff > kp2lowLoose) && (kp2phidiff < kp2highLoose)  && (pimphidiff > pimlowLoose) && (pimphidiff < pimhighLoose) )
		{
			tLoose->Fill();
		}
		
		if(i % 10000==0) 
		{ 
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
			cout << "kp1phidiff = " <<kp1phidiff<< "   kp1sector = " <<kp1sector<< "   pkp1 = " <<pkp1<< "   kp1thetadeg = " <<kp1thetadeg<<endl;
			cout << "kp1lowReg = " <<kp1lowReg<< "  kp1highReg = " <<kp1highReg<<endl;
			cout << "kp1lowTight = " <<kp1lowTight<< "  kp1highTight = " <<kp1highTight<<endl;
			cout << "kp1lowLoose = " <<kp1lowLoose<< "  kp1highLoose = " <<kp1highLoose<<endl;
			cout << "kp2phidiff = " <<kp2phidiff<< "   kp2sector = " <<kp2sector<< "   pkp2 = " <<pkp2<< "   kp2thetadeg = " <<kp2thetadeg<<endl;
			cout << "kp2lowReg = " <<kp2lowReg<< "  kp2highReg = " <<kp2highReg<<endl;
			cout << "kp2lowTight = " <<kp2lowTight<< "  kp2highTight = " <<kp2highTight<<endl;
			cout << "kp2lowLoose = " <<kp2lowLoose<< "  kp2highLoose = " <<kp2highLoose<<endl;
			cout << "pimphidiff = " <<pimphidiff<< "   pimsector = " <<pimsector<< "   ppim = " <<ppim<< "   pimthetadeg = " <<pimthetadeg<<endl;
			cout << "pimlowReg = " <<pimlowReg<< "  pimhighReg = " <<pimhighReg<<endl;
			cout << "pimlowTight = " <<pimlowTight<< "  pimhighTight = " <<pimhighTight<<endl;
			cout << "pimlowLoose = " <<pimlowLoose<< "  pimhighLoose = " <<pimhighLoose<<endl<<endl;
		}
	
	}
	tReg->Write(tRegName);
	tTight->Write(tTightName);
	tLoose->Write(tLooseName);	
	gROOT->ProcessLine(".q");
	
	
}	



//////////////////////////////////////////////////
//c style 2d function
Float_t FidFunc(Float_t *x, Float_t *par) 
{
	Float_t xx = x[0]; //momentum
	Float_t yy = x[1]; //theta
	Float_t a = (par[0]*pow(xx,par[1]) + par[2]);
	Float_t b = (par[3]*pow(xx,par[4]) + par[5]);
	Float_t c = (par[6]*pow(xx,par[7]) + par[8]);
 	Float_t f =  a -  b/(yy - c);
	return 	f;
}



Float_t myOLD2dfunc (Float_t *x, Float_t *par) 
{
	Float_t xx = x[0];
	Float_t yy = x[1];
	Float_t a = (par[0]*pow(xx,par[1]) + par[2]);
	Float_t b = (par[3]*pow(xx,par[4]) + par[5]);
	Float_t c = (par[6]*pow(xx,par[7]) + par[8]);
 	Float_t f = ( (b)*(1 - 1/((yy - c)*(b/a))));
	return 	f;
}

