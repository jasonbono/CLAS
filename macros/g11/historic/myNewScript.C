void myNewScript() {
  // open root file
  TFile *f = new TFile("myrootfile.root");

  // read cos theta histograms from file
  TH1F *h[10];
  ReadCosThetaHists(f, h);
  ProcessCosThetaHists(h);

}

// level 1 /////////////////////////////////////////////////////////////////////////////////

// preconditions: ROOT file f is opened and ready for reading, h is a TH1F histogram of size 11
// postconditions: Read the cos theta histograms from file and save them in h
void ReadCosThetaHists(TFile *f, TH1F * h[10]) {
  // local variables
  TString name;

  // statements
  for (Int_t i = 0; i < 10; i++) {
    // set up name for the histogram
    name = Form("hrz%d", i+1);
    h[i] = (TH1F*)f->Get(name.Data())->Clone();
  }

  cout << "Finished reading cos theta histograms from file: \n";

  return;
}

// preconditions: h contains cos theta histograms read from the file
// postconditions: process the histograms as needed
void ProcessCosThetaHists(TH1F * h[10]) {
  // local variables
  Int_t nBins = h[0]->GetNbinsX();
  Float_t binValues[10];

  // statements
  cout << "bins: " << nBins << endl;
  // loop over the histogram bins
  for (Int_t j = 1; j <= nBins; j++) {  // NOTE: bin 0: underflow, bin: nBins + 1 is overflow
    // get the content of the bin from the histogram
    binValues[j] = h[0]->GetBinContent(j);

    cout << "j: " << j << " value: " << binValues[j] << endl;   


  }


}
