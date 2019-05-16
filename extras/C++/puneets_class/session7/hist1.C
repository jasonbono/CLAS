// hist1.C
// 
// usage: root hist1.C
//
// This macro reads histograms for reconstructed and generated events from
// a file, divides the histograms to obtain the acceptance distribution with
// correct errors

// constants /////////////////////////////////////////////////////////////////
const Float_t init = -99999.9;               // some initial constants
const Int_t init_int = -99999;               // some initial constants

// level 0 ///////////////////////////////////////////////////////////////////

void hist1() {
  // open file
  TFile* f = new TFile("hists.root");
  
  // read histograms 
  TH1F* rec = MyRead1DHistogram("h1", f);
  TH1F* gen = MyRead1DHistogram("h2", f);
  
  // compute acceptance
  TH1F* acc = ComputeAcceptance(rec, gen);
  
  // plot histograms
  PlotHistograms(rec, gen, acc);
}

// level 1 ///////////////////////////////////////////////////////////////////

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

// preconditions: rec and gen have been read from the root file
// postconditions: the acceptance for each kinematic bin is computed and
//    returned
TH1F* ComputeAcceptance(TH1F* rec, TH1F* gen) {
  // rebin rec and gen histograms by 30 bins
  rec->Rebin(30);
  gen->Rebin(30);
  
  // clone the generated histogram and store it as acceptance 
  TH1F* acc = (TH1F*)gen->Clone("acc");
  
  // get the total number of bins in the X axis
  Int_t N_BINS = acc->GetXaxis()->GetNbins();
  
  // compute acceptance for each kinematic bin
  for (Int_t i = 1; i <= N_BINS; i++) {
    // obtain the value in rec and gen for each bin
    Double_t recValue = rec->GetBinContent(i);
    Double_t genValue = gen->GetBinContent(i);
    // calculate acceptance
    Double_t accValue = recValue / genValue;
    // compute errors
    Double_t recError = sqrt(recValue);
    Double_t genError = sqrt(genValue);
    
    // compute the error for acceptance
    // sigma_e = (1/N)*sqrt(k*(1-k/N))
    Double_t accError = (1./genValue)*sqrt(recValue*(1. - accValue));
    
    // store acceptance value and errors for acceptance
    acc->SetBinContent(i, accValue);
    acc->SetBinError(i, accError);
    // force errors for rec and gen bins
    rec->SetBinError(i, recError);
    gen->SetBinError(i, genError);
  }
  
  return acc;
}

// preconditions: rec, gen, and acc histograms have been init and filled
// postconditions: the histograms are plotted
void PlotHistograms(TH1F* rec, TH1F* gen, TH1F* acc) {
  // local variables
  TCanvas* can = new TCanvas("can", "canvas", 1000, 500);
  can->Divide(2, 1);
  
  // setup draw styles
  gStyle->SetOptStat(0);       // remove the statistics box
  gStyle->SetErrorX(0);        // set all errors in X coordinate to 0
  
  // setup legend
  TLegend* leg = new TLegend(.4, .8, .9, .9);
  leg->SetFillStyle(0);
  leg->SetTextFont(132);
  leg->SetTextSize(0.06);
  leg->AddEntry(gen, "Generated", "lep");
  leg->AddEntry(rec, "Reconstructed", "lep");
  
  // plot rec and gen histograms
  can->cd(1);
  gPad->SetMargin(.15, .1, .15, .1);
  MyDraw1D(gen, "#phi (deg)", "Counts", 0, 360, 0, 6000, 2, "E1P");
  MyDraw1D(rec, "#phi (deg)", "Counts", 0, 360, 0, init, 4, "E1Psame"); 
  leg->Draw("same");  
  gPad->Update();
  
  // plot acc histogram
  can->cd(2);
  gPad->SetMargin(.15, .1, .15, .1);
  MyDraw1D(acc, "#phi (deg)", "Acceptance", 0, 360, 0, init, 4, "E1P");
  MyText(.2, .85, "Acceptance", 4, "same", 0.06);
  gPad->Update();
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
