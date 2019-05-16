

void test(){

TFile *f = TFile::Open("~/clas/rootfiles/newer.root");
TTree *newt = (TTree*)f->Get("mytree");

Float_t Piangle;
newt->SetBranchAddress("PIangle", &Piangle);
 Int_t nentries = (Int_t)newt->GetEntries();
cout << "nentries is " << nentries << endl;


TH1F *h1=new TH1F("h1","",20,-1.1,1.1);

for (Int_t i=0; i<nentries;i++) {
newt->GetEvent(i);
h1->Fill(Piangle);

 }
h1->Draw();
 

}







