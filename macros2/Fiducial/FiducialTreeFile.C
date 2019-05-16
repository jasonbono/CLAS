/*
Author: Jason Bono
Data: Sep 3 2013

Usage: 
> .L FiducialTreeFile	
> FiducialTreeFile(file.root)

root files named somthing like 
/Users/Bono/clas/rootfiles/g12/ppippim/partial/ppippim-v03-Partial_Phi.root
*/	
	
void FiducialTreeFile(TString passed)
{

	const int Np = 15;  //number of momentum bins	
	const int Nt = 15;  //number of theta bins	
	const int Ns = 6;  //number of sectors
	const int Ni = 3; //number of parameters in second generation fit
	const int Nj = 3; //number of parameters in second generation fit

	string input(passed);
	string filename = input.substr(0,input.find_last_of("."));
	string extention = input.substr(input.find_last_of("."));

	string tackonNew("_FidAll");
	string outputNew = filename + tackonNew + extention;
	//string tackonReg("_FidReg");
	//string outputReg = filename + tackonReg + extention;
	//string tackonTight("_FidTight");
	//string outputTight = filename + tackonTight + extention;
	//string tackonLoose("_FidLoose");
	//string outputLoose = filename + tackonLoose + extention;
	//cout <<"input = "<< input <<"   outputReg = " <<outputReg <<"   outputTight = " <<outputTight <<"   outputLoose = " <<outputLoose <<endl;

	string treename("v09");
	TFile *file = TFile::Open(input.c_str());  
	TTree *tOriginal = (TTree*)file->Get(treename.c_str()); 
	//the new file with regular fiducial cuts
	TFile *fileNew = new TFile(outputNew.c_str(),"RECREATE");
	//TFile *fileReg = new TFile(outputReg.c_str(),"RECREATE");
	TTree *tReg = tOriginal->CloneTree(0);
	TString tRegName = Form("%sReg",treename.c_str());
	//the new Tight file
	//TFile *fileTight = new TFile(outputTight.c_str(),"RECREATE");
	TTree *tTight = tOriginal->CloneTree(0);
	TString tTightName = Form("%sTight",treename.c_str());
	//the new Loose file
	//TFile *fileLoose = new TFile(outputLoose.c_str(),"RECREATE");
	TTree *tLoose = tOriginal->CloneTree(0);
	TString tLooseName = Form("%sLoose",treename.c_str());


	//set the trees to the files
	//tReg->SetFile(fileReg);
	//tTight->SetFile(fileTight);
	//tLoose->SetFile(fileLoose);


	//read in the fitting parameters
	ifstream infile_Pos(Form("./txt/ThirdGen/FitParams_Pos-%i-%ibins.txt",Np,Nt));
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
				cout << parL_Pos[s][3*ii + j] <<endl;
			}
		}
	}	
	infile_Pos.close();
	ifstream infile_Neg(Form("./txt/ThirdGen/FitParams_Neg-%i-%ibins.txt",Np,Nt));
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
		

	//prexisting
	//pip
	Float_t pipphidiff = -100;
	Int_t pipsector = -100;
	Float_t ppip = -100;
	Float_t piplabtheta = -100;
	tOriginal->SetBranchAddress("pipphidiff", &pipphidiff);
	tOriginal->SetBranchAddress("pipsector", &pipsector);
	tOriginal->SetBranchAddress("ppip", &ppip);
	tOriginal->SetBranchAddress("piplabtheta", &piplabtheta);
	//pim
	Float_t pimphidiff = -100;
	Int_t pimsector = -100;
	Float_t ppim = -100;
	Float_t pimlabtheta = -100;
	tOriginal->SetBranchAddress("pimphidiff", &pimphidiff);
	tOriginal->SetBranchAddress("pimsector", &pimsector);
	tOriginal->SetBranchAddress("ppim", &ppim);
	tOriginal->SetBranchAddress("pimlabtheta", &pimlabtheta);
	//p
	Float_t pphidiff = -100;
	Int_t psector = -100;
	Float_t pp = -100;
	Float_t plabtheta = -100;
	tOriginal->SetBranchAddress("pphidiff", &pphidiff);
	tOriginal->SetBranchAddress("psector", &psector);
	tOriginal->SetBranchAddress("pp", &pp);
	tOriginal->SetBranchAddress("plabtheta", &plabtheta);
	



	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i++)
	{
		tOriginal->GetEntry(i);
		
		//get event by event conditions for pip
		Float_t var_pip[2] = {ppip,piplabtheta};
		float low_pip = 0;
		//cout << var_pip[0] <<"  " <<var_pip[1]<<"  " <<pipsector<<" "<<parL_Pos[pipsector - 1] <<endl;
		low_pip = FidFunc(var_pip,parL_Pos[pipsector - 1]); 
		float high_pip = 0;
		high_pip = FidFunc(var_pip,parH_Pos[pipsector - 1]);
		//get event by event conditions for pim
		Float_t var_pim[2] = {ppim,pimlabtheta};
		float low_pim = 0;
		low_pim = FidFunc(var_pim,parL_Neg[pimsector - 1]); 
		float high_pim = 0;
		high_pim = FidFunc(var_pim,parH_Neg[pimsector - 1]);
		//get event by event conditions for p
		Float_t var_p[2] = {pp,plabtheta};
		float low_p = 0;
		low_p = FidFunc(var_p,parL_Pos[psector - 1]); 
		float high_p = 0;
		high_p = FidFunc(var_p,parH_Pos[psector - 1]);
		//get the tight conditions
		float lowTight_pip, highTight_pip, lowTight_pim, highTight_pim, lowTight_p, highTight_p;
		lowTight_pip = low_pip + 2;
		highTight_pip = high_pip - 2;
		lowTight_pim = low_pim + 2;
		highTight_pim = high_pim - 2;
		lowTight_p = low_p + 2;
		highTight_p = high_p - 2;
		float lowLoose_pip, highLoose_pip, lowLoose_pim, highLoose_pim, lowLoose_p, highLoose_p;
		lowLoose_pip = low_pip - 2;
		highLoose_pip = high_pip + 2;
		lowLoose_pim = low_pim - 2;
		highLoose_pim = high_pim + 2;
		lowLoose_p = low_p - 2;
		highLoose_p = high_p + 2;
		

		
		
		
		if ( (pipphidiff > low_pip) && (pipphidiff < high_pip) && (pimphidiff > low_pim) && (pimphidiff < high_pim) && (pphidiff > low_p) && (pphidiff < high_p) )
		{
			tReg->Fill();
		}
		
		
		if ( (pipphidiff > lowTight_pip) && (pipphidiff < highTight_pip) && (pimphidiff > lowTight_pim) && (pimphidiff < highTight_pim) && (pphidiff > lowTight_p) && (pphidiff < highTight_p) )
		{
			tTight->Fill();
		}
		
		if ( (pipphidiff > lowLoose_pip) && (pipphidiff < highLoose_pip) && (pimphidiff > lowLoose_pim) && (pimphidiff < highLoose_pim) && (pphidiff > lowLoose_p) && (pphidiff < highLoose_p) )
		{
			tLoose->Fill();
		}
		


		if(i % 5000==0) 
		{ 
			Float_t tempi = i;
			Float_t tempN = nentries;
			cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
			cout << "pipphidiff = " <<pipphidiff<< "   pipsector = " <<pipsector<< "   ppip = " <<ppip<< "   piplabtheta = " <<piplabtheta<<endl;
			cout << "low_pip = " <<low_pip<< "  high_pip = " <<high_pip<<endl;
			cout << "lowTight_pip = " <<lowTight_pip<< "  highTight_pip = " <<highTight_pip<<endl;
			cout << "lowLoose_pip = " <<lowLoose_pip<< "  highLoose_pip = " <<highLoose_pip<<endl;
			cout << "pimphidiff = " <<pimphidiff<< "   pimsector = " <<pimsector<< "   ppim = " <<ppim<< "   pimlabtheta = " <<pimlabtheta<<endl;
			cout << "low_pim = " <<low_pim<< "  high_pim = " <<high_pim<<endl;
			cout << "lowTight_pim = " <<lowTight_pim<< "  highTight_pim = " <<highTight_pim<<endl;
			cout << "lowLoose_pim = " <<lowLoose_pim<< "  highLoose_pim = " <<highLoose_pim<<endl;
			cout << "pphidiff = " <<pphidiff<< "   psector = " <<psector<< "   pp = " <<pp<< "   plabtheta = " <<plabtheta<<endl;
			cout << "low_p = " <<low_p<< "  high_p = " <<high_p<<endl;
			cout << "lowTight_p = " <<lowTight_p<< "  highTight_p = " <<highTight_p<<endl;
			cout << "lowLoose_p = " <<lowLoose_p<< "  highLoose_p = " <<highLoose_p<<endl<<endl<<endl;
		}
	
	}
	tReg->Write(tRegName);
	tTight->Write(tTightName);
	tLoose->Write(tLooseName);	
	

	gROOT->ProcessLine(".q");
	
	
}	



///////////////////////////////////////////
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




Float_t OldFidFunc (Float_t *x, Float_t *par) 
{
	Float_t xx = x[0];
	Float_t yy = x[1];
	Float_t a = (par[0]*pow(xx,par[1]) + par[2]);
	Float_t b = (par[3]*pow(xx,par[4]) + par[5]);
	Float_t c = (par[6]*pow(xx,par[7]) + par[8]);
 	Float_t f = ( (b)*(1 - 1/((yy - c)*(b/a))));
	return 	f;
}

