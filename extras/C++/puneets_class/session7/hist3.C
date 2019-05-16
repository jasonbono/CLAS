// hist3.C
// 
// usage: root -n 'hist3.C("filename", minX, maxX)'
// 
// inputs: 
//    filename: name of the root file that contains the 2D histogram 'h2d'
//    minX: minimum X value to start projection
//    maxX: maximum X value to stop projection
// 
// This macro will take a 2D histogram and create projections 

// constants //////////////////////////////////////////////////////////////////
const Float_t init = -99999.9;               // some initial constants
const Int_t init_int = -99999;               // some initial constants

// level 0 ////////////////////////////////////////////////////////////////////

void hist3(const char* file, Float_t minX, Float_t maxX) {
  // dump inputs to stdout
  cout << "file name: " << file << endl 
       << "min X: " << minX << endl 
       << "max X: " << maxX << endl;
  
  // open root file
  TFile* f = new TFile(file);
  
  // setup style
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  // read 2d histogram
  TH2F* h = MyRead2DHistogram("h2d", f);
  h->Rebin2D(5, 5);

  // find the bin corresponding to the min and max values in X for the hist
  Int_t minBin = h->GetXaxis()->FindBin(minX);
  Int_t maxBin = h->GetXaxis()->FindBin(maxX); 

  // obtain its projection on the Y axis from minX to maxX
  TH1F* proj = (TH1F*)h->ProjectionY("proj", minBin, maxBin);

  // setup lines to draw
  TLine* ln1 = new TLine(minX, 0, minX, 360);
  TLine* ln2 = new TLine(maxX, 0, maxX, 360);
  ln1->SetLineColor(2);
  ln2->SetLineColor(2);
  ln1->SetLineWidth(2);
  ln2->SetLineWidth(2);

  // plot the histogram along with its projection
  TCanvas* can = new TCanvas("can", "canvas", 1000, 500);
  can->Divide(2, 1);
  
  // plot the 2d histogram
  can->cd(1);
  gPad->SetMargin(.15, .1, .15, .1);
  MyDraw2D(h, "cos#theta", "#phi (deg)");
  ln1->Draw();
  ln2->Draw();
  gPad->Update();
  
  // plot the projection
  can->cd(2);
  gPad->SetMargin(.15, .1, .15, .1);
  MyDraw1D(proj, "#phi (deg)", "counts", init, init, 0, init);  
  gPad->Update();

}

// level 1 ////////////////////////////////////////////////////////////////////

// preconditions: str is the name of the histogram to be read, and file f is
//    opened for reading
// postconditions: 2D histogram with name str is read from file f and returned
TH2F* MyRead2DHistogram(TString str, TFile* f) {
  // set global file directory pointer to point to top dir in f
  f->cd();
  // extract and clone the TObject with name str and typecast it as a TH1F*
  TH2F* h = (TH2F*)gDirectory->Get(str.Data())->Clone();
  // return the pointer to the 1D histogram
  return h;  
}

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

// precondition: h is specified and a 2d histogram, a canvas has been
//     initialized
// postcondition: the histogram h is plotted with xtitle, ytitle, xlo, xhi,
//     ylo, and yhi if specified. Otherwsie default values will be used.
void MyDraw2D(TH2F *h, char *xtitle = NULL, char *ytitle = NULL, 
  Float_t xlo = init, Float_t xhi = init, Float_t ylo = init, 
  Float_t yhi = init, char *opt = NULL) {
    
	h->SetLabelFont(132, "xyz");
	h->SetTitleFont(132, "xyz");
	h->SetLabelSize(0.06, "xyz");
	h->SetTitleSize(0.06, "xyz");
  // specify x and y axis titles if specified
  if (xtitle != NULL) {
    h->GetXaxis()->SetTitle(xtitle);
		h->GetXaxis()->CenterTitle();
  }
  if (ytitle != NULL) {
    h->GetYaxis()->SetTitle(ytitle);
    //h->GetYaxis()->SetTitleOffset(1.5);
    h->GetYaxis()->CenterTitle();
  }
  // specify the range of display for the x axis
  if ((xlo != init) && (xhi != init))
    h->GetXaxis()->SetRangeUser(xlo, xhi);
  if ((ylo != init) && (yhi != init))
    h->GetYaxis()->SetRangeUser(ylo, yhi);
  // draw the damn histogram
  if (opt != NULL)
    h->Draw(opt);
  else
    h->Draw("COLZ");

  return;
}