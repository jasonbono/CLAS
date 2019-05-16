/* 
August This analyzer just adds the mandalstam varable T to any ntuple. was addapted from Addxyz_3 

need to call md (that is the mass of the fourth particle on the mandalstam diagram) the mass of the 
Xi Kp2 system.  for simplicity in calculation i have derived that this is equal to the mass of the
gamma + proton - Kp1 system.  therefore only need to calculate v.M() for v when v is said system.

UPDATE: can just use MMKP1 for this which is already included in my data analyzer.

UPDATE: have also derived that tkp1 is equal to (mmkp1)^2 - mpr^2

UPDATE: the last result seems to be incorrect.
*/
#include <Riostream.h>
#include <TMath.h>
#include "TMath.h"
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
gSystem.Load("libPhysics.so");

void AddT()
{

 	//TFile *f = TFile::Open("/Users/Bono/clas/simulation/g12/XiYield/MC_v07_v37k.root","UPDATE");
	//TFile *f = TFile::Open("/Users/Bono/clas/simulation/g12/XiYield/v37k_full_newbasic.root","UPDATE");
	//TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/mc/a1c/v07/MC_v07_v37k.root","UPDATE");
	TFile *f = TFile::Open("/Users/Bono/clas/rootfiles/g12/large/v37k_00_94.root","UPDATE");
	TTree *addedt = (TTree*)f->Get("v37k");
	gROOT->ProcessLine(".L ~/clas/scripts/mytmin.C");

	//masses
	Float_t mkp=0.493667;
	Float_t mpr=0.938272;
	Float_t mxi=1.32131;
	
	//for the mass of "d" (as in, a,b,c,d)
	//Float_t Md;
	//TLorentzVector Va,Vb,Vc,Vd; //(a=gamma,b=proton,c=Kp1,d=Kp2+Xim)
	
	//calculate theese
	Float_t ekp1;
	//branch varables
 	Float_t beam;
 	Float_t pkp1;
 	Float_t kp1labtheta;
	Float_t mmkp1;
	addedt->SetBranchAddress("beam", &beam);
	addedt->SetBranchAddress("pkp1", &pkp1);
	addedt->SetBranchAddress("kp1labtheta", &kp1labtheta);
	addedt->SetBranchAddress("mmkp1", &mmkp1);
	//new branch
	Float_t tkp1;
	Float_t tminkp1;
	Float_t tpkp1;
	
	TBranch *tkp1Branch = addedt->Branch("tkp1", &tkp1, "tkp1/F");	
	TBranch *tminkp1Branch = addedt->Branch("tminkp1", &tminkp1, "tminkp1/F");	
	TBranch *tpkp1Branch = addedt->Branch("tpkp1", &tpkp1, "tpkp1/F");
	//begin the loop
 	Int_t nentries = (Int_t)addedt->GetEntries(); 
 	for (Int_t i=0; i<nentries; i++) 
 	{
  		addedt->GetEntry(i);
  		//output the progress every 1000 entries
  		if(i % 1000==0)
  		{
   			cout << "progress: " <<  (i*100)/nentries << " %  complete" << endl;
  		}
  		
		//obtain Md
		//va.SetXYZM(0,0,beam,0);
		//vb.SetXYZM(0,0,0,mpr);
		//vc.SetXYZM(x,y,z,mkp);
		
		//calculate Kp1 energy 
		Float_t ekp1 = sqrt(mkp*mkp + pkp1*pkp1);
		// calculate t, tmin, tp for kp1
		tkp1 = mkp*mkp - 2*beam*ekp1 + 2*beam*pkp1*kp1labtheta ;
		tminkp1 = tmin(beam,0.0,mpr,mkp,mmkp1);
		tpkp1 = sqrt((tkp1 - tminkp1)*(tkp1 - tminkp1));
		

		//fill branches 
  		tkp1Branch->Fill();
		tminkp1Branch->Fill();
		tpkp1Branch->Fill();
		if(i % 1000==0)
  		{

			//some diagnostics
			cout << "~~~~~~~~~~~~~~~~SOME DIAGNOSTICS~~~~~~" <<endl;
			cout << "mkp*mkp=" << mkp*mkp << " 2*beam*ekp1=" << 2*beam*ekp1<< " 2*ekp1*pkp1*kp1labtheta=" << 2*ekp1*pkp1*kp1labtheta << " tkp1=" << tkp1 << endl;
			cout << "pkp1=" << pkp1 << " pkp1*pkp1=" << pkp1*pkp1 << " ekp1=" << ekp1 << endl;
			cout <<"======================================" <<endl;
			cout << "tminkp1 = " << tminkp1 <<endl << "tmin = " << tmin(beam,0.0,mpr,mkp,mxi) << endl;
			cout << "beam = " << beam << "  mpr = " << mpr << "  mkp = " << mkp << "  mxi = "  << mxi << endl; 
			cout << "tkp1 = " << tkp1 << "  tminkp1 = " << tminkp1 <<endl;
			cout << "-------------the alternate calculation of t--------------------" <<endl;
			cout << "tkp1_alternatemethod=" << mmkp1*mmkp1 - mpr*mpr <<endl;
			cout << "mmkp1=" << mmkp1 << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			 
			//cout << "sqrt((tkp1 - tminkp1)*(tkp1 - tminkp1)) = "<< sqrt((tkp1 - tminkp1)*(tkp1 - tminkp1)) <<"  tpkp1 = " << tpkp1 <<endl;
		}
  	}
 	addedt->Write("", TObject::kOverwrite);
 	gROOT->ProcessLine(".q");
}
