// hist2.C
//
// usage: root -n hist2.C
//
// This macro constructs two histograms, one using a Gaussian and the other
// with a Gaussian+Constant, and is fit. The parameters from the fit are
// extracted and dumped to standard out.

// level 0 //////////////////////////////////////////////////////////////////
void hist2() {
  // reset root environment
  gROOT->Reset();
  gStyle->Reset();

  // set the style of the entire ROOT system
  gROOT->SetStyle("Plain"); 
  gStyle->SetStatFont(132);
  gStyle->SetOptStat(1110);
  gStyle->SetOptFit(11111111);
  
  // construct a randomly generated 1D histogram
  TH1F* h1 = ConstructHistogram1("h1", 0.938, 0.020);
  
  // draw the histogram with fit
  Draw1(h1);
  
  // construct another randomly generated 1D histogram with background
  TH1F* h2 = ConstructHistogram2("h2", 0.922, 0.0163);
  Draw2(h2);
}

// level 1 //////////////////////////////////////////////////////////////////

// preconditions: mean and sigma are viable floats, with sigma > 0
// postconditions: construct a histogram filled with a randomly generated
//    gaussian centered at mean and sigma
TH1F* ConstructHistogram1(const TString name, 
                          const Float_t mean, 
                          const Float_t sigma) {
  // define a new histogram
  TH1F* h = new TH1F(name, "histogram", 800, 0, 2);
  // create a new random generator object
  TRandom3* random = new TRandom3;
  // set the random generator seed
  random->SetSeed(0);
  // define a variable to store random values
  Float_t randNum = 0.0;

  // generate and fill the histograms  
  for (Int_t i = 0; i < 10000; i++) {
    // generate a random number
    randNum = random->Gaus(mean, sigma);
    // fill the histogram     
    h->Fill(randNum);
  }
  
  // return a pointer to the TH1F object
  return h;
}

// preconditions: mean and sigma are viable floats, with sigma > 0
// postconditions: construct a histogram filled with a randomly generated
//    gaussian centered at mean and sigma
TH1F* ConstructHistogram2(const TString name, 
                          const Float_t mean, 
                          const Float_t sigma) {
  // define a new histogram
  TH1F* h = new TH1F(name, "histogram", 800, 0, 2);
  // create a new random generator object
  TRandom3* random = new TRandom3;
  // set the random generator seed
  random->SetSeed(0);
  // define a variable to store random values
  Float_t randNum = 0.0;
  // create a new function to generate a random number
  TF1* randFn = new TF1("randFn", "gaus(0)+pol0(3)", 0.0, 2.0);
  randFn->SetParameters(1.0, mean, sigma, .1);

  // generate and fill the histograms  
  for (Int_t i = 0; i < 50000; i++) {
    // generate a random number
    randNum = randFn->GetRandom();
    // fill the histogram     
    h->Fill(randNum);
  }
  
  // return a pointer to the TH1F object
  return h;
}

// preconditions: the histogram has been filled
// postconditions: the histogram is fitted and drawn
void Draw1(TH1F* h) {
  // local variables
  TCanvas *can1 = new TCanvas("can1", "canvas", 700, 500);
  gPad->SetMargin(.15, .1, .15, .1);
  
  // set style and attributes of the histogram
  SetHistogramStyle(h);
  h->Draw();
  gPad->Update();
  
  // set up a function to fit the histogram using a predefined function: gaus
  TF1* f1 = new TF1("f1", "gaus", 0.8, 1.2);
  // initialize the parameters of the gaussian to something close to the
  // expected values
  f1->SetParameters(500, 0.93, 0.03);
  // set the limits to parameters
  f1->SetParLimits(1, 0.9, 1);    // par numbers go from 0..N-1
  // you can also fix parameters
  //f1->FixParameter(1, 0.938);
  // fit the function to the histogram
  // E: improved error calculation, R: use range specified,
  // Q: no verbose output from Minuit, +: add to list of functions of hist
  // "same": draw option for the fitted function 
  h->Fit("f1", "ERQ+", "same", 0.85, 1.02);
  // extract the parameters 
  Float_t mean = f1->GetParameter(1);
  Float_t meanErr = f1->GetParError(1);
  Float_t sigma = f1->GetParameter(2);
  Float_t sigmaErr = f1->GetParError(2);
  cout << "Parameters for 1st histogram:\n" 
    << "  mean: " << mean << " mean error: " << meanErr << endl
    << "  sigma: " << sigma << " sigma error: " << sigmaErr << endl;  
}

// preconditions: the histogram has been filled
// postconditions: the histogram is fitted and drawn
void Draw2(TH1F* h) {
  // local variables
  TCanvas *can2 = new TCanvas("can2", "canvas", 700, 500);
  gPad->SetMargin(.15, .1, .15, .1);
  
  // set style and attributes of the histogram
  SetHistogramStyle(h);
  h->Draw();
  gPad->Update();
  
  // set up a function to fit the histogram using predefined functions: 
  // gaus(0) + pol0(3) 
  TF1* f2 = new TF1("f2", "gaus(0)+pol0(3)", 0.8, 1.2);
  // initialize the parameters of the gaussian to something close to the
  // expected values
  f2->SetParameters(h->GetMaximum(), 0.93, 0.03, 50);
  // fit the function to the histogram
  h->Fit("f2", "ERQ+", "same", 0.825, 1.02);
  // extract the parameters 
  Float_t mean = f2->GetParameter(1);
  Float_t meanErr = f2->GetParError(1);
  Float_t sigma = f2->GetParameter(2);
  Float_t sigmaErr = f2->GetParError(2);
  cout << "Parameters for 2nd histogram:\n" 
    << "  mean: " << mean << " mean error: " << meanErr << endl
    << "  sigma: " << sigma << " sigma error: " << sigmaErr << endl;  
}

// level 2 //////////////////////////////////////////////////////////////////

// preconditions: the histogram has been filled
// postconditions: the histogram's attributes are set
void SetHistogramStyle(TH1F* h) {
  // set the title  
  h->SetTitle("");  // I don't want to have a title for the histogram
  // set x axis attributes
  h->GetXaxis()->SetTitle("MM^{2}_{X}(ep #rightarrow eX) (GeV^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetLabelFont(132);
  h->GetXaxis()->SetTitleFont(132);
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetRangeUser(0.8, 1.2);
  // set y axis attributes
  h->GetYaxis()->SetTitle("Counts");
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetLabelFont(132);
  h->GetYaxis()->SetTitleFont(132);
  h->GetYaxis()->SetLabelSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  // set fill color
  h->SetFillColor(2);
}