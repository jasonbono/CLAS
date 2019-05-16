

/*
Name: IntegrateHists.C
Author: Jason Bono
Date: April 20somthing 2013

Purpose: just for cross checking  (step 4b)
What it Does: Makes an ASCII file of each events energy,XiCM,piangles and the calculate R values to read by eye.


Input: ./2kppim-v05-Basic-Mass-Ac.root
Output: ./txt/ASCII.txt

*/



void MakeASCII()
{

	
	int Nk = 50; //# of pion bins used to get the acceptance parameters
	TFile *file = TFile::Open(Form("./NewRootFiles/2kppim-v05-Basic-Mass-Ac-%ibins.root",Nk));
	TTree *tOriginal = (TTree*)file->Get("v05");

	ofstream myfile;
	myfile.open (Form("./txt/ASCII-%ibins.txt",Nk));



	//old branches
	float beam, Xcmtheta;
	float COS_pi_x, COS_pi_y, COS_pi_z;
	float RE0x, RE0y, RE0z, RE1x, RE1y, RE1z,RE2x, RE2y, RE2z;
	float RXi0x, RXi0y, RXi0z, RXi1x, RXi1y, RXi1z,RXi2x, RXi2y, RXi2z;
	float REx, REy, REz;
	float RXix, RXiy, RXiz;
	float eREx, eREy, eREz;
	float eRXix, eRXiy, eRXiz;
	float Rtest;

	tOriginal->SetBranchAddress("beam", &beam);
	tOriginal->SetBranchAddress("Xcmtheta", &Xcmtheta);
	tOriginal->SetBranchAddress("COS_pi_x", &COS_pi_x);
	tOriginal->SetBranchAddress("COS_pi_y", &COS_pi_y);
	tOriginal->SetBranchAddress("COS_pi_z", &COS_pi_z);
	//seperated efficenancy branches
	tOriginal->SetBranchAddress("RE0x", &RE0x);
	tOriginal->SetBranchAddress("RE0y", &RE0y);
	tOriginal->SetBranchAddress("RE0z", &RE0z);
	tOriginal->SetBranchAddress("RE1x", &RE1x);
	tOriginal->SetBranchAddress("RE1y", &RE1y);
	tOriginal->SetBranchAddress("RE1z", &RE1z);
	tOriginal->SetBranchAddress("RE2x", &RE2x);
	tOriginal->SetBranchAddress("RE2y", &RE2y);
	tOriginal->SetBranchAddress("RE2z", &RE2z);
	tOriginal->SetBranchAddress("RXi0x", &RXi0x);
	tOriginal->SetBranchAddress("RXi0y", &RXi0y);
	tOriginal->SetBranchAddress("RXi0z", &RXi0z);
	tOriginal->SetBranchAddress("RXi1x", &RXi1x);
	tOriginal->SetBranchAddress("RXi1y", &RXi1y);
	tOriginal->SetBranchAddress("RXi1z", &RXi1z);
	tOriginal->SetBranchAddress("RXi2x", &RXi2x);
	tOriginal->SetBranchAddress("RXi2y", &RXi2y);
	tOriginal->SetBranchAddress("RXi2z", &RXi2z);
	tOriginal->SetBranchAddress("REx", &REx);
	tOriginal->SetBranchAddress("REy", &REy);
	tOriginal->SetBranchAddress("REz", &REz);
	tOriginal->SetBranchAddress("RXix", &RXix);
	tOriginal->SetBranchAddress("RXiy", &RXiy);
	tOriginal->SetBranchAddress("RXiz", &RXiz);
	
	tOriginal->SetBranchAddress("Rtest", &Rtest);
	
	
	Int_t nentries = (Int_t)tOriginal->GetEntries(); 
	for (int i=0; i<nentries; i++) 
	{
		tOriginal->GetEntry(i);
		
		myfile<<" - - -  Energy = "<<beam<<"  Xcmtheta = "<<Xcmtheta<< "  - - - "<<endl;
		myfile<< "COS_pi_x = "<<COS_pi_x<<"  COS_pi_y = "<< COS_pi_y<<"  COS_pi_z = "<<COS_pi_z<<endl; 
		myfile << "Rtest = " << Rtest << endl;
		myfile<< "RE0x =  " <<  RE0x << "  RE0y =  " <<  RE0y << "  RE0z =  " << RE0z<<endl;
		myfile<< "RE1x =  " <<  RE1x << "  RE1y =  " <<  RE1y << "  RE1z =  " << RE1z<<endl;
		myfile<< "RE2x =  " <<  RE2x << "  RE2y =  " <<  RE2y << "  RE2z =  " << RE2z<<endl;
		myfile<< "RXi0x = " <<  RXi0x << "  RXi0y = " <<  RXi0y << "  RXi0z = " << RXi0z<<endl;
		myfile<< "RXi1x = " <<  RXi1x << "  RXi1y = " <<  RXi1y << "  RXi1z = " << RXi1z<<endl;
		myfile<< "RXi2x = " <<  RXi2x << "  RXi2y = " <<  RXi2y << "  RXi2z = " << RXi2z<<endl;
		myfile<< "REx =   " <<  REx << "  REy =   " <<  REy << "  REz =   " << REz<<endl;
		myfile<< "RXix =  " <<  RXix << "  RXiy =  " <<  RXiy << "  RXiz =  " << RXiz<<endl;
		myfile<<endl;
		
	
	
	
	
	}
}
	
	