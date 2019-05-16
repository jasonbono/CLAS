
/* Jun 30 will find lab coords of kaon.
pxk1 is the x component of k1 in the lab frame
*/

#include <Riostream.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
	

void labcoords(){
       	
TFile *f = new TFile("newer.root","UPDATE");
TTree *newt = (TTree*)f->Get("new");
Float_t testpxk1;
Float_t pkp1;
TBranch *tbrBranch = newt->Branch("testpxk1", &testpxk1, "testpxk1/F");
//TH1F *a5=new TH1F("a5", "", 100,-1,11);	
Int_t nentries = (Int_t)newt->GetEntries();   //??


newt->SetBranchAddress("pkp1", &pkp1);

for (Int_t i=0; i<nentries; i++) {
newt->GetEntry(i);

//testpxk1=pkp1


tbrBranch->Fill();

  }	

newt->Write("", TObject::kOverwrite);


//just a text to see if macro is working
newt->Draw("tvar")
//newt->Draw("tvar:vy:vz");


}
