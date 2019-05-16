// construct.C
//
// usage: root construct.C
// 
// This macro will construct histograms and store them in a root file

// constants //////////////////////////////////////////////////////////////////
const Int_t NUM_HISTS = 2;                    // number of histograms
const Int_t MAX_EVENTS[NUM_HISTS] 
  = {17834, 50000};                           // max events for each hist
const Float_t D2R = Pi() / 180.;              // conversion from deg to radians

// level 0 ////////////////////////////////////////////////////////////////////

void construct() {
  // initialize root file
  TFile* f = new TFile("hists.root", "recreate");
  
  // initialize histograms
  TH1F* h[NUM_HISTS];                        // histogram array with 5 elements
  TString name;                              // variable for hist name
  TString desc;                              // variable for hist description
  // loop through elements of histogram
  for (Int_t i = 0; i < NUM_HISTS; i++) {
    // setup name and description of histogram
    name = Form("h%d", i+1);
    desc = Form("histogram %d", i+1);
    // initialize histograms
    h[i] = new TH1F(name, desc, 360, 0, 360);
  }
  
  // fill the histograms
  FillHistograms(h);
  
  // write to file and close it
  f->Write();
  f->Close();
}

// level 1 ////////////////////////////////////////////////////////////////////


// preconditions: the histograms are initialized
// postconditions: the histograms are filled with randomly generated events
void FillHistograms(TH1F* h[NUM_HISTS]) {
  // create a new random generator object
  TRandom3* random = new TRandom3(0);
  // define a variable to store random values
  Float_t randNum = 0.0;
  // setup functions
  TF1* f1 = new TF1("f1", MyFunction1, 0, 360, 3);
  f1->SetParameters(6.8, 2.76, 12.);
  
  // loop through histograms
  for (Int_t i = 0; i < NUM_HISTS; i++) {
    // generate events   
    for (Int_t j = 0; j < MAX_EVENTS[i]; j++)  {
      // generated a random number
      randNum = f1->GetRandom();
      // fill the histogram
      h[i]->Fill(randNum);
    }
  }
    
}

// preconditions: none
// postconditions: the value of the function is calculated and returned
Double_t MyFunction1(Double_t* x, Double_t* par) {
  // local variables
  Double_t xRadians = x[0] * D2R;
  Double_t result = par[0]*sin(xRadians-par[1]) + par[2];
  
  return result;  
}
