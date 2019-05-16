// hist1.C
// 
// usage: root hist1.C
// 
// This macro reads histograms from a file and manipulates them

// constants //////////////////////////////////////////////////////////////////
const Int_t NUM_HISTS = 2;                   // total histograms to read
const Float_t init = -99999.9;               // some initial constants
const Int_t init_int = -99999;               // some initial constants

// level 0 ////////////////////////////////////////////////////////////////////

void hist1() {
  // set style options
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  // open root file for reading
  TFile* f = new TFile("hists.root");
  // init histograms
  TH1F* h[NUM_HISTS];
  
  // read histograms from file
  ReadHistograms(h, f);

  // normalize and plot histograms
  Normalize(h);

}

// level 1 ////////////////////////////////////////////////////////////////////

// preconditions: the file is opened for reading and histograms have been 
//    declared
// postconditions: the histograms and read from file and returned
void ReadHistograms(TH1F* h[NUM_HISTS], TFile* f) {
  // setup local variables
  TString name;                          // name of histogram in file
  
  // loop through histogram array
  for (Int_t i = 0; i < NUM_HISTS; i++) {
    // setup histogram name
    name = Form("h%d", i+1);
    // read histogram from file
    h[i] = MyRead1DHistogram(name, f);
  }  
}

// preconditions: the histograms have been read from file
// postconditions: the histograms and normalized and plotted in two ways
void Normalize(TH1F* h[NUM_HISTS]) {
  // local variables
  TH1F* h1[NUM_HISTS];                     // first set of clones
  TH1F* h2[NUM_HISTS];                     // second set of clones
  TH1F* h3[NUM_HISTS];                     // third set of clones
  TCanvas* normCan = new TCanvas("normcan", "normalized canvas", 1000, 800);
  normCan->Divide(2, 2);
  Int_t count = 1;
  TString str;

  // clone and rebin the histograms
  for (Int_t i = 0; i < NUM_HISTS; i++) {
    // clone the first set
    str = Form("h1_%d", i+1);
    h1[i] = (TH1F*)h[i]->Clone(str.Data());
    h1[i]->Rebin(30);
    // clone the second set
    str = Form("h2_%d", i+1);
    h2[i] = (TH1F*)h[i]->Clone(str.Data());
    h2[i]->Rebin(30);
    // clone the third set
    str = Form("h3_%d", i+1);
    h3[i] = (TH1F*)h[i]->Clone(str.Data());
    h3[i]->Rebin(30);
    // set automatic error calculation for each bin point
    h3[i]->Sumw2();
  }

  // plot histograms without modifications  
  MyPlot(h, normCan, count, "", "same");
  
  // plot the first set of cloned histograms
  MyPlot(h1, normCan, count, "E1P", "E1Psame");

  // normalize the original histogram
  Double_t factor = h2[1]->GetEntries() / h2[0]->GetEntries();
  h2[0]->Scale(factor);
  MyPlot(h2, normCan, count, "", "E1Psame");
  
  // normalize distributions so that the integral under the curve is 1
  // the 'width' option: sum of bin contents multiplied by the bin width in x
  Double_t factor1 = 1./h3[0]->Integral("width");
  Double_t factor2 = 1./h3[1]->Integral("width");
  h3[0]->Scale(factor1);
  h3[1]->Scale(factor2);
  MyPlot(h3, normCan, count, "E1P", "E1Psame");
  
}

// level 2 ////////////////////////////////////////////////////////////////////

// precondition:
// postconditions:
void MyPlot(TH1F* myH[NUM_HISTS], TCanvas* can, Int_t & count, 
  const char* opt1, const char* opt2) {
  // setup pad
  can->cd(count);
  gPad->SetMargin(.15, .1, .15, .1);

  // draw the histograms
  MyDraw1D(myH[1], "#phi (deg)", "Counts", 0, 360, 0, init, 2, opt1);
  MyDraw1D(myH[0], "#phi (deg)", "Counts", 0, 360, 0, init, 4, opt2);

  // show the entries for each histogram on the pad
  Int_t numEntries = myH[1]->GetEntries();
  TString str = Form("h1: %d", numEntries);
  MyText(0.2, 0.85, str.Data(), 2, "same");

  numEntries = myH[0]->GetEntries();
  str = Form("h2: %d", numEntries);
  MyText(0.2, 0.8, str.Data(), 4, "same");

  // update the canvas
  gPad->Update();  

  // increment counter 
  count++;
}


// preconditions: str is the name of the histogram to be read, and file f is
//    opened for reading
// postconditions: 1D histogram with name str is read from file f and returned
TH1F* MyRead1DHistogram(TString str, TFile* f) {
  // set global file directory pointer to point to top dir in f
  f->cd();
  // extract and clone the TObject with name str and typecast it as a TH1F*
  TH1F* h = (TH1F*)gDirectory->Get(str.Data())->Clone();
  // return the pointer to the 1D histogram
  return h;  
}

// level 3 ////////////////////////////////////////////////////////////////////

// precondition: h is specified and is a one d histogram, a canvas has been
//     initialized.
// postcondition: the histogram h is plotted with xtitle, ytitle, xlo, xhi,
//     ylo, and fillcolor if specified. Otherwise default values will be used
void MyDraw1D(TH1F *h, char *xtitle = NULL, char *ytitle = NULL,
Float_t xlo = init, Float_t xhi = init, Float_t ylo = init, Float_t yhi = init,
Int_t lineColor = init_int, char *opt = NULL) {
  // set font attributes
  h->SetLabelFont(132, "xyz");
  h->SetTitleFont(132, "xyz");
 
  // set axis title and label sizes
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetLabelSize(0.06);

  // specify x and y axis titles if specified
  if (xtitle != NULL) {
    h->GetXaxis()->SetTitle(xtitle);
    h->GetXaxis()->CenterTitle();
  }
  if (ytitle != NULL) {
    h->GetYaxis()->SetTitle(ytitle);
    h->GetYaxis()->SetTitleOffset(1.2);
    h->GetYaxis()->CenterTitle();
  }
  // specify the range of display for the x axis
  if ((xlo != init) && (xhi != init))
    h->GetXaxis()->SetRangeUser(xlo, xhi);
  // specify the range of display for the y axis
  if (ylo != init)
    h->SetMinimum(ylo);
  if (yhi != init)
    h->SetMaximum(yhi);
  // specify fill color for the histogram
  if (lineColor != init_int) h->SetLineColor(lineColor);
  
  // set line width
  h->SetLineWidth(2);

  // check if the options contain marker option
  if (opt != NULL) {
    TString option = opt;
    if (option.Contains("P", TString::kIgnoreCase)) {
      h->SetMarkerStyle(21);
      h->SetMarkerSize(0.75);
      if (lineColor != init_int) {
        h->SetMarkerColor(lineColor);
        h->SetLineColor(1);
      }
    }
  }

  // plot the damn histogram
  if (opt != NULL)
    h->Draw(opt);
  else
    h->Draw();

  return;
}

// precondition: x and y are coodinates in the NDC coordinate system, text,
//    color and options are all viable
// postcondition: the text is plotted at NDC coords x,y with the given color
//    and drawing option opt.
void MyText(Float_t x, Float_t y, char *text, Int_t color, char *opt = "",
      Float_t size = 0.05) {
 TLatex *tex = new TLatex(x, y, text);
 tex->SetTextFont(132);
 tex->SetNDC(kTRUE);
 tex->SetTextColor(color);
 tex->SetTextSize(size);
 tex->Draw(opt);
}
