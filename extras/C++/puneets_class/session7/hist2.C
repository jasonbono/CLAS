// hist2.C
// 
// usage: root -n hist2.C
// 
// This macro plots a two dimensional histogram with different options

// constants /////////////////////////////////////////////////////////////////
const Float_t init = -99999.9;               // some initial constants
const Int_t init_int = -99999;               // some initial constants

// level 0 ///////////////////////////////////////////////////////////////////

void hist2() {
  // set options
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  // open file
  TFile* f = new TFile("hists.root");
  
  // read 2d histogram from the file
  TH2F* h = MyRead2DHistogram("h2d", f);
  
  // plot the 2d histogram using different methods
  Plot2DHistogram(h);
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

// preconditions: the histogram has been read from the root file
// postconditions: the contents of the histogram are plotted using different
//    options
void Plot2DHistogram(TH2F* h) {
  // local variables
  TCanvas* can1 = new TCanvas("can1", "canvas 1", 1000, 600);
  can1->Divide(3, 3);
  TString opt;
  const Int_t NUM = 9;
  TH2F* hClone[NUM];
  TString str;
  Float_t minX = -1.;
  Float_t minY = 0.;
  Float_t maxX = 1.;
  Float_t maxY = 360.0;
  
  // setup lines for cuts
  TLine* ln1 = new TLine(.1, 0, .1, 360.);
  TLine* ln2 = new TLine(-1, 60., 1, 60.0);
  ln1->SetLineWidth(2);
  ln2->SetLineWidth(2);
  ln1->SetLineColor(2);
  ln2->SetLineColor(2);
  
  
  // loop over options
  for (Int_t i = 0; i < NUM; i++) {
    // clone the original histogram
    str = Form("h2d_%d", i+1);
    hClone[i] = (TH2F*)h->Clone(str.Data());
    
    // setup canvas pad
    can1->cd(i+1);
    gPad->SetMargin(.15, .1, .15, .1);
    
    // setup draw options
    switch(i+1) {
      case 1:  // draw with no special options
        opt = " ";
        break;
      case 2:  // colz option
        opt = "COLZ";
        break;
      case 3:  // rebin
        hClone[i]->Rebin2D(10, 10);    
        opt = "COLZ";
        break;
      case 4:  // rebin and surface option
        hClone[i]->Rebin2D(10, 10);
        opt = "SURF2";
        break;
      case 5:  // rebin and surface with contour on top
        hClone[i]->Rebin2D(10, 10);
        opt = "CONT4Z";
        break;
      case 6: // lego options 
        hClone[i]->Rebin2D(10, 10);
        opt = "LEGO2";
        break;
      case 7: // another surface option
        hClone[i]->Rebin2D(10, 10);
        opt = "SURF4";
        break;
      case 8: // box option
        hClone[i]->Rebin2D(10, 10);
        opt = "BOX";
        break;
      case 9: // box option with superimposed histogram
        hClone[i]->Rebin2D(10, 10);
        // apply cuts on this histogram
        minX = -1.;
        maxX = .1;
        minY = 60.0;
        // draw the previous histogram
        hClone[i-1]->Draw("BOX");
        opt = "COLZsame";
        break;
      default: // default option
        opt = "COLZ";
        break;
    }
    
    // draw the histogram
    MyDraw2D(hClone[i], "cos#theta", "#phi (deg)", minX, maxX, minY, maxY, opt.Data());

    // draw lines to show cuts
    if (i == 7) {
      ln1->Draw();
      ln2->Draw();
    }
    
  }
  
}

// level 2 ///////////////////////////////////////////////////////////////////

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