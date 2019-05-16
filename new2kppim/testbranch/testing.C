/*
june 21 2011, jason bono
to test to see if i can add a branch to the tree "newt" in newer.root
may also serve as a reference for basic commands

----------june 30 made "testing.c" from old file
*/

//#ifndef __CINT__	
#include <Riostream.h>	
#include <Riostream.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
	

void testing(){
       	
TFile *f = new TFile("newer.root","UPDATE");
TTree *newt = (TTree*)f->Get("new");

    Float_t tvar6; //=10.0;
    TBranch *tbrBranch = newt->Branch("tvar6", &tvar6, "tvar6/F");

TH1F *a5=new TH1F("a5", "", 100,-1,11);	
Int_t nentries = (Int_t)newt->GetEntries();   //??

//tvar5=cos(.785);
/*this works... need to figgure out how to
get tvari assigned to a prexisting leaf
*/




for (Int_t i=0; i<nentries; i++) {
newt->GetEntry(i);

 tvar6=11;
tbrBranch->Fill();


  }	

newt->Write("", TObject::kOverwrite);


//just a text to see if macro is working
       newt->Draw("tvar6");


}
