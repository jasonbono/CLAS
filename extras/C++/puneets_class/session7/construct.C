// construct.C
//
// usage: root construct.C
// 
// This macro will construct histograms and store them in a root file

// constants //////////////////////////////////////////////////////////////////
const Int_t NUM_HISTS = 2;                    // number of histograms
const Int_t MAX_EVENTS[NUM_HISTS] 
  = {17834, 50000};                           // max events for each hist
const Int_t MAX_EVENTS_2D = 100000;           // max events for 2d hist
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
  // create a two dimensional histogram
  TH2F* h2d = new TH2F("h2d", "2d histogram", 200, -1, 1, 360, 0, 360);
  
  // fill the histograms
  FillHistograms(h, h2d);
  
  // write to file and close it
  f->Write();
  f->Close();
}

// level 1 ////////////////////////////////////////////////////////////////////


// preconditions: the histograms are initialized
// postconditions: the histograms are filled with randomly generated events
void FillHistograms(TH1F* h[NUM_HISTS], TH2F* h2d) {
  // create a new random generator object
  TRandom3* random = new TRandom3(0);
  // define a variable to store random values
  Float_t randNum = 0.0;
  Float_t randNum2 = 0.0;
  // setup functions
  TF1* f[3];
  f[0] = new TF1("f1", MyFunction1, 0, 360, 3);
  f[0]->SetParameters(6.8, 2.76, 12.);
  f[1] = new TF1("f2", "pol0", 0, 360);
  f[1]->SetParameter(0, 1);
  f[2] = new TF1("f3", MyFunction2, -1, 1, 2);
  f[2]->SetParameters(0.0, 1.0);
  
  // loop through histograms
  for (Int_t i = 0; i < NUM_HISTS; i++) {
    // generate events   
    for (Int_t j = 0; j < MAX_EVENTS[i]; j++)  {
      // generated a random number
      randNum = f[i]->GetRandom();
      // fill the histogram
      h[i]->Fill(randNum);
    }
  }
  
  // generate events for the 2d histogram
  for (Int_t i = 0; i < MAX_EVENTS_2D; i++) {
    randNum = f[0]->GetRandom();   // y axis values
    randNum2 = f[2]->GetRandom();  // x axis values
    h2d->Fill(randNum2, randNum); 
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

// preconditions: none
// postconditions: the value of the function is calculated and returned
Double_t MyFunction2(Double_t* x, Double_t* par) {
  // setup the legendre polynomial function
  Double_t result = par[1] + 0.5*(5.*pow(x[0]-par[0], 3) - 3.*(x[0]-par[0]));
  
  return result;
}
