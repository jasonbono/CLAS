// hist3.C
//
// usage: root -n hist3.C
//
// This macro reads some data files, plots them as histograms and fits them, 
// extracts the mean and sigma, constructs graphs from these parameters.

// constants ////////////////////////////////////////////////////////////////
const Int_t MAX_FILES = 8;

// parameter struct /////////////////////////////////////////////////////////
struct ParStruct {
  // data members
  Float_t mean[MAX_FILES];                    // mean
  Float_t meanErr[MAX_FILES];                 // error in mean
  Float_t sigma[MAX_FILES];                   // sigma
  Float_t sigmaErr[MAX_FILES];                // error in sigma
  Float_t x[MAX_FILES];                       // file number
  // constructor
  ParStruct() {
    // initialize all array elements to 0
    for (int i = 0; i < MAX_FILES; i++) {
      mean[i] = 0.0; 
      meanErr[i] = 0.0;
      sigma[i] = 0.0;
      sigmaErr[i] = 0.0;
      x[i] = 0.0;
    }
  }
};

// level 0 /////////////////////////////////////////////////////////////////
void hist3() {
  // set the style of the entire ROOT system
  gROOT->SetStyle("Plain"); 
  gStyle->SetStatFont(132);
  gStyle->SetOptStat(1110);
  gStyle->SetOptFit(11111111);  
  gStyle->SetOptTitle(0);
  
  // local variables
  TString str;
  TString temp;
  TH1F* h[MAX_FILES];
  ParStruct pars;
  
  // open files for reading
  for (int i = 0; i < MAX_FILES; i++) {
    // setup file name
    str = Form("datafiles/data_%d.dat", i+1);
    
    // init histogram
    temp = Form("h%d", i+1);
    h[i] = new TH1F(temp, temp, 400, -2, 2);
    
    // read the file and store its contents into a histogram
    ReadAndFillHistogram(h[i], str);
  }  
  
  // plot and fit the histograms
  PlotAndFitHistograms(h, pars);    
  
  // plot the parameters as graphs
  GraphParameters(pars);
}

// level 1 //////////////////////////////////////////////////////////////////

// preconditions: str contains the name of the file to be read
// postconditions: opens the file and stores its contents into a new histogram
void ReadAndFillHistogram(TH1F* h, TString str) {
  // open file for reading
  ifstream file(str.Data());
  float number;
  
  // while we can read from the file
  while (file >> number) {
    // if a number was read from the file, fill the histogram with it
    h->Fill(number);
  }
  
  // close the file
  file.close();
}

// preconditions: the histograms have been filled
// postconditions: the histograms are drawn, fitted and mean and sigma extracted
void PlotAndFitHistograms(TH1F** h, ParStruct& pars) {
  // local variables
  TCanvas* can1 = new TCanvas("can1", "canvas", 1000, 700);
  can1->Divide(4, 2);
  
  // setup a function for fitting
  TF1* f1 = new TF1("f1", "gaus(0)+pol1(3)", -2, 2);
  f1->SetParameters(400, 0.0, 0.1, 1, 1);
  
  // statements
  for (Int_t i = 0; i < MAX_FILES; i++) {
    // go to current pad
    can1->cd(i+1);
    gPad->SetMargin(.15, .1, .15, .1);
    
    // setup the histogram style
    SetHistogramStyle(h[i]);
    
    // draw the histogram
    h[i]->Draw();
    
    // fit it
    h[i]->Fit("f1", "ERQ+", "", -1, 1);

    // write a label for the current pad
    TString label = Form("File: %d", i+1);
    WriteLabel(0.2, 0.85, label, 2);

    // update canvas    
    gPad->Update();
    
    // store fit parameters
    pars.mean[i] = f1->GetParameter(1);
    pars.meanErr[i] = f1->GetParError(1);
    pars.sigma[i] = f1->GetParameter(2);
    pars.sigmaErr[i] = f1->GetParError(2);
    
    // store the file numbers as x
    pars.x[i] = i+1;
  }
  
}

// preconditions: the pars structure has been filled
// postconditions: the parameters are plotted
void GraphParameters(const ParStruct & pars) {
  // local variables
  TCanvas* can2 = new TCanvas("can2", "canvas", 1000, 500);
  can2->Divide(2, 1);
  
  // construct graphs with error bars
  TGraphErrors* grMean = new TGraphErrors(MAX_FILES, pars.x, pars.mean, 
    0, pars.meanErr);
  TGraphErrors* grSigma = new TGraphErrors(MAX_FILES, pars.x, pars.sigma,
    0, pars.sigmaErr);
    
  // set the graph styles
  SetGraphStyle(grMean, 2, "Mean #Deltat (ns)");
  SetGraphStyle(grSigma, 4, "Sigma #Deltat (ns)");
    
  // plot the mean
  can2->cd(1);
  // change margins
  gPad->SetMargin(.2, .1, .15, .1);
  // show gridlines
  gPad->SetGrid();
  // change Y axis range
  grMean->GetYaxis()->SetRangeUser(-0.03, 0.03);
  // draw the graph with axis and a polymarker
  grMean->Draw("AP");
  gPad->Update();
  
  // plot the sigma
  can2->cd(2);
  // change margins
  gPad->SetMargin(.2, .1, .15, .1);
  // show gridlines
  gPad->SetGrid();
  // change Y axis range
  grSigma->GetYaxis()->SetRangeUser(0.0, 0.3);
  // draw the graph with axis and a polymarker
  grSigma->Draw("AP");
  gPad->Update();
}

// level 2 //////////////////////////////////////////////////////////////////

// preconditions: the histogram has been filled
// postconditions: the histogram's attributes are set
void SetHistogramStyle(TH1F* h) {
  // rebin histogram
  h->Rebin(2);
  // set x axis attributes
  h->GetXaxis()->SetTitle("#Deltat (ns)");
  h->GetXaxis()->CenterTitle();
  h->GetXaxis()->SetLabelFont(132);
  h->GetXaxis()->SetTitleFont(132);
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
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

// preconditions: all pars are init
// postconditions: the text string drawn at x,y of the specified color, 
//    size 0.06 using the option "same" 
void WriteLabel(Float_t x, Float_t y, TString text, Int_t color) {
  TLatex* tex = new TLatex(x, y, text);
  tex->SetTextFont(132);
  tex->SetNDC(kTRUE);
  tex->SetTextColor(color);
  tex->SetTextSize(0.06);
  tex->Draw("same");
}

// preconditions: the graph has been init and str contains the title of the
//    Y-axis
// postconditions: the graph's axes and markers attributes are set 
void SetGraphStyle(TGraphErrors* gr, Int_t color = 2, TString str) {
  // set x axis attributes
  gr->GetXaxis()->SetTitle("File number");
  gr->GetXaxis()->CenterTitle();
  gr->GetXaxis()->SetLabelFont(132);
  gr->GetXaxis()->SetTitleFont(132);
  gr->GetXaxis()->SetLabelSize(0.06);
  gr->GetXaxis()->SetTitleSize(0.06);
  // set y axis attributes
  gr->GetYaxis()->SetTitle(str.Data());
  gr->GetYaxis()->CenterTitle();
  gr->GetYaxis()->SetLabelFont(132);
  gr->GetYaxis()->SetTitleFont(132);
  gr->GetYaxis()->SetLabelSize(0.06);
  gr->GetYaxis()->SetTitleSize(0.06);
  gr->GetYaxis()->SetTitleOffset(1.5);
  // set marker attributes
  gr->SetMarkerStyle(21);
  gr->SetMarkerSize(1.0);
  gr->SetMarkerColor(color);  
}