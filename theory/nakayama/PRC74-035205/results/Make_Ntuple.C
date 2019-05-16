{


	gROOT->Reset();
	#include "iostream.h"
	Float_t x,y,z,j,k,l;
	ifstream inKps,inXps,inKpv,inXpv;
//-------------------------K ps-----------------------

	inKps.open("analy_K_ps.out");

	Int_t nlines = 0;
	TFile *fileKps = new TFile("analy_K_ps.root","RECREATE");
	TH1F *histKps = new TH1F("histKps","energy distribution",100,0,6);
	TNtuple *ntupleKps = new TNtuple("ntupleKps","data from ascii file","beam:theta_K:xsectn:analy_nuc:analy_gam:analy_cas");

	while (1) 
	{
		inKps >> x >> y >> z >> j >> k >> l;
		if (!inKps.good()) break;
		if (nlines < 100) printf("x=%8f, y=%8f, z=%8f, j=%8f, k=%8f, l=%8f",x,y,z,j,k,l);
		histKps->Fill(x);
		ntupleKps->Fill(x,y,z,j,k,l);
		nlines++;
   }
   printf(" found %d pointsn",nlines);
   inKps.close();
   fileKps->Write();



//-------------------------X ps-----------------------
	inXps.open("analy_X_ps.out");

	Int_t nlines = 0;
	TFile *fileXps = new TFile("analy_X_ps.root","RECREATE");
	TH1F *histXps = new TH1F("histXps","energy distribution",100,0,6);
	TNtuple *ntupleXps = new TNtuple("ntupleXps","data from ascii file","beam:theta_X:xsectn:analy_nuc:analy_gam:analy_cas");

	while (1) 
	{
		inXps >> x >> y >> z >> j >> k >> l;
		if (!inXps.good()) break;
		if (nlines < 100) printf("x=%8f, y=%8f, z=%8f, j=%8f, k=%8f, l=%8f",x,y,z,j,k,l);
		histXps->Fill(x);
		ntupleXps->Fill(x,y,z,j,k,l);
		nlines++;
   }
   printf(" found %d pointsn",nlines);
   inXps.close();
   fileXps->Write();

//----------------------K pv--------------------------
	inKpv.open("analy_K_pv.out");

	Int_t nlines = 0;
	TFile *fileKpv = new TFile("analy_K_pv.root","RECREATE");
	TH1F *histKpv = new TH1F("histKpv","energy distribution",100,0,6);
	TNtuple *ntupleKpv = new TNtuple("ntupleKpv","data from ascii file","beam:theta_K:xsectn:analy_nuc:analy_gam:analy_cas");

	while (1) 
	{
		inKpv >> x >> y >> z >> j >> k >> l;
		if (!inKpv.good()) break;
		if (nlines < 100) printf("x=%8f, y=%8f, z=%8f, j=%8f, k=%8f, l=%8f",x,y,z,j,k,l);
		histKpv->Fill(x);
		ntupleKpv->Fill(x,y,z,j,k,l);
		nlines++;
   }
   printf(" found %d pointsn",nlines);
   inKpv.close();
   fileKpv->Write();



//--------------------x pv----------------------------
	inXpv.open("analy_X_pv.out");

	Int_t nlines = 0;
	TFile *fileXpv = new TFile("analy_X_pv.root","RECREATE");
	TH1F *histXpv = new TH1F("histXpv","energy distribution",100,0,6);
	TNtuple *ntupleXpv = new TNtuple("ntupleXpv","data from ascii file","beam:theta_X:xsectn:analy_nuc:analy_gam:analy_cas");

	while (1) 
	{
		inXpv >> x >> y >> z >> j >> k >> l;
		if (!inXpv.good()) break;
		if (nlines < 100) printf("x=%8f, y=%8f, z=%8f, j=%8f, k=%8f, l=%8f",x,y,z,j,k,l);
		histXpv->Fill(x);
		ntupleXpv->Fill(x,y,z,j,k,l);
		nlines++;
   }
   printf(" found %d pointsn",nlines);
   inXpv.close();
   fileXpv->Write();




}