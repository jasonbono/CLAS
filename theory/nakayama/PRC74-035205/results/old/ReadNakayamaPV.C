// VECTOR
// create ntuple from nakayama's analy_pv results 
// T_lb (beam), theta_K, xsectn, analy_nuc, analy_gam, analy_cas;

{


	gROOT->Reset();
	#include "iostream.h"
	ifstream in;
	in.open("formated_analy_pv.out");
	Float_t x,y,z,j,k,l;
	Int_t nlines = 0;
	TFile *f = new TFile("nakayama_analy_pv.root","RECREATE");
	TH1F *h1 = new TH1F("h1","energy distribution",100,0,6);
	TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","beam:theta_K:xsectn:analy_nuc:analy_gam:analy_cas");

	while (1) 
	{
		in >> x >> y >> z >> j >> k >> l;
		if (!in.good()) break;
		if (nlines < 100) printf("x=%8f, y=%8f, z=%8f, j=%8f, k=%8f, l=%8f",x,y,z,j,k,l);
		h1->Fill(x);
		ntuple->Fill(x,y,z,j,k,l);
		nlines++;
   }
   printf(" found %d pointsn",nlines);
   in.close();
   f->Write();


}








