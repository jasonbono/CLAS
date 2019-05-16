void try(){



 
   TFile *f = TFile::Open("~/clas/rootfiles/std.root");
   TTree *newt = (TTree*)f->Get("mytree");
   gROOT->ProcessLine(".x cuts.C");

   newt->Draw("PIangle",mycut);
	
}
