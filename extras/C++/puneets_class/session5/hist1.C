// hist1.C
//
// usage: root -n hist1.C
//
// This macro generates a 1D histogram and plots it using different options
// 

// level0 ///////////////////////////////////////////////////////////////////
void hist1() {
  // reset root environment
  gROOT->Reset();
  gStyle->Reset();
    
  // construct a randomly generated 1D histogram
  TH1F* h1 = ConstructHistogram1("h1", 0.0, 0.239);
  
  // set the style of the entire ROOT system
  gROOT->SetStyle("Plain");    // others: "Default", "Bold", "Video"
  // change the fonts for the statistics box
  gStyle->SetStatFont(132); // change font to something nice for all hists
  gStyle->SetOptStat(1110); // show number of events, mean, and RMS only
  
  // Change the axes, labels, titles, fonts, styles
  Draw1(h1);

  gStyle->SetOptTitle(0);   // hide the title

  // Manipulating canvas, pads, playing with draw options
  Draw2(h1);    
}

// level 1 //////////////////////////////////////////////////////////////////

// preconditions: mean and sigma are viable floats, with sigma > 0
// postconditions: construct a histogram filled with a randomly generated
//    gaussian centered at mean and sigma
TH1F* ConstructHistogram1(const TString name, 
                          const Float_t mean, 
                          const Float_t sigma) {
  // define a new histogram
  TH1F* h = new TH1F(name, "histogram", 800, -2, 2);
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

// preconditions: the histogram has been filled
// postconditions: the histogram is plotted on a canvas with modified
//   attributes
void Draw1(TH1F* h) {
  // setup canvas
  TCanvas* can2 = new TCanvas("can2", "canvas", 700, 500);

  //------------- draw the histogram ---------------------//
  h->Draw();
  // updates the pad with the modified histogram
  gPad->Update();
  // the following command will suspend execution until 
  // CTRL or C is typed in the pad, or double click from the mouse.
  // In the meantime you can interact with the pad and its contents
  gPad->WaitPrimitive();  
  
  //---------- change the histogram title ----------------//
  h->SetTitle("My histogram");  

  // to remove the title, either set the string to "", or 
  // issue the following command 
  //gStyle->SetOptTitle(0);   // beware: this command only hides the title 
  //h->SetTitle("");          // this command actually sets the title to NULL  

  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();
      
  //----------- change the axes title --------------------//
  
  // change the axes title in many different ways
  // 1st method: directly invoke the SetXTitle() or SetYTitle() or SetZTitle()
  // Note: you can use Latex style for the text
  //       need to use {} and #alpha instead of \alpha for latex symbols 
  h->SetXTitle("#Deltat_{#pi}");

  h->Draw();  
  gPad->Update();
  gPad->WaitPrimitive();
  
  // 2nd method: get access to the TAxis object and then modify that object
  // you can get access to the axis via the GetXaxis() or GetYaxis() or
  // GetZaxis() functions. This returns a TAxis* object, which can be
  // modified
  TAxis* xAxis = h->GetXaxis();  
  xAxis->SetTitle("#Deltat_{#pi} (ns)"); 
  
  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();
  
  // 3rd method: stacking commands (I prefer this method)
  h->GetYaxis()->SetTitle("Counts/0.005 ns");
  
  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();
  
  //--------------- center the titles -------------------------//
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  
  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();
  
  //--------------- change axes label and title sizes ----------//
  cout << "Default label size for X axis is: " 
       << h->GetXaxis()->GetLabelSize() << endl 
       << "Default title size of X axis is: " 
       << h->GetXaxis()->GetTitleSize() << endl
       << "Default label size for Y axis is: " 
       << h->GetYaxis()->GetLabelSize() << endl 
       << "Default title size of Y axis is: " 
       << h->GetYaxis()->GetTitleSize() << endl;
  // for the x-axis
  h->GetXaxis()->SetLabelSize(0.08);   // change tick labels
  h->GetXaxis()->SetTitleSize(0.08);   // change title size 
  // for the y-axis
  h->GetYaxis()->SetLabelSize(0.08);   // change tick labels
  h->GetYaxis()->SetTitleSize(0.08);   // change title size 

  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();

  //------------- set pad margin offset ----------------------//
  gPad->SetMargin(.2, .1, .2, .1);    // left right bottom top, default: .1  

  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();

  //------------- change the axes fonts ----------------------//
  h->GetXaxis()->SetLabelFont(132);
  h->GetXaxis()->SetTitleFont(132);
  h->GetYaxis()->SetLabelFont(132);
  h->GetYaxis()->SetTitleFont(132);

  h->Draw();
  gPad->Update();
  gPad->WaitPrimitive();
}

// preconditions: the histogram's axes fonts, and styles have been set 
// postcondition: the canvas, pads and draw options are explored
void Draw2(TH1F* h) {
  // setup a new canvas with many pads
  TCanvas* can3 = new TCanvas("can3", "canvas", 1000, 700);
  can3->Divide(3, 3);   // divide into 3x3 sub pads
   
  // setup some local variables
  const Int_t NUM_HISTS = 9;      // store the num of hists to make
  TString str;                    // variable to store hist names
  TH1F* myHist[NUM_HISTS];        // 1-d histogram array of size NUM_HISTS
  TString opt = "";               // variable to store draw options
  
  // setup and draw cloned histograms with different options
  for (Int_t i = 0; i < NUM_HISTS; i++) {
    // setup a name for this histogram
    str = Form("myhist_%d", i+1);
    // clone the original histogram and give it a new name
    // the Clone() returns TObject*, so need to cast it to TH1F*
    myHist[i] = (TH1F*)h->Clone(str.Data());
    
    // set the gPad pointer to point to current pad in can3
    can3->cd(i+1);   // pad numbers go from 1..N
    // setup pad margins
    gPad->SetMargin(.2, .1, .2, .1);
    
    // setup attributes for current histogram
    switch(i) {
      case 0:   // change fill color 
        myHist[i]->SetFillColor(4);
        break;
      case 1:   // change line color
        myHist[i]->SetLineColor(2);
        break;
      case 2:   // draw it as a bar chart
        opt = "B";
        myHist[i]->SetFillColor(8);
        break;
      case 3:  // draw it as scatter plot with error bars
        opt = "E1P";
        break;
      case 4:  // change the polymarker to filled square
        myHist[i]->SetMarkerStyle(21);
        myHist[i]->SetMarkerSize(0.75);
        myHist[i]->SetMarkerColor(2);
        opt = "E1P";
        break;
      case 5:  // rebin the histogram and use a triangle for marker
        myHist[i]->Rebin(5);
        myHist[i]->GetYaxis()->SetTitle("Counts/0.025 ns");
        myHist[i]->SetMarkerStyle(22);
        myHist[i]->SetMarkerSize(0.75);
        myHist[i]->SetMarkerColor(4);
        opt = "E1P";        
        break;
      case 6:  // rebin and draw as a smooth dashed curve 
        myHist[i]->Rebin(2);
        myHist[i]->GetYaxis()->SetTitle("Counts/0.01 ns");
        myHist[i]->SetLineStyle(2);
        opt = "C";
        break;
      case 7: // rebin and draw for a specific range in x
        myHist[i]->Rebin(2);
        myHist[i]->GetYaxis()->SetTitle("Counts/0.01 ns");
        myHist[i]->GetXaxis()->SetRangeUser(-1, 1);
        opt = "";
        break;
      case 8: // rebin and draw for a specific range in x to show cuts
        myHist[i]->Rebin(2);
        myHist[i]->GetYaxis()->SetTitle("Counts/0.01 ns");
        myHist[i]->SetFillColor(9);
        myHist[i]->GetXaxis()->SetRangeUser(-.35, .35);
        myHist[i-1]->Draw();   // plot the previous histogram
        opt = "same";          // opt to draw this histogram on same pad
        break;
      default:
        opt = "";
        break; 
    }
    
    // draw the histogram
    myHist[i]->Draw(opt.Data());
    // update pad
    gPad->Update();
  } 
}