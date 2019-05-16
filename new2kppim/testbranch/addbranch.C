/*
june 21 2011, jason bono
to test to see if i can add a branch to the tree "newt" in newer.root
may also serve as a reference for basic commands
*/

//#ifndef __CINT__	
#include <Riostream.h>	
void addbranch(){
       	
TFile *f = new TFile("newer.root","UPDATE");
TTree *newt = (TTree*)f->Get("new");
 Float_t tvar2 =10.0;
//newt->SetBranchAddress("run", &tvar); //im not sure what this is or if i need it
TBranch *tbrBranch = newt->Branch("tvar", &tvar, "tvar/F");
TH1F *a5=new TH1F("a5", "", 100,-1,11);	
Int_t nentries = (Int_t)newt->GetEntries();   //??

for (Int_t i=0; i<nentries; i++) {
newt->GetEntry(i);


tbrBranch->Fill();


  }	

newt->Write("", TObject::kOverwrite);


//just a text to see if macro is working
newt->Draw("tvar");


}
