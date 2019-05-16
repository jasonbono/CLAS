
#ifndef __CINT__
#include "TApplication.h"
#include "TPythia6.h"
#include "TFile.h"
#include "TError.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "Riostream.h"
#include <cstdlib>
using namespace std;
#endif

#define FILENAME   "pythia.root"
#define TREENAME   "tree"
#define BRANCHNAME "particles"
#define HISTNAME   "ptSpectra"
#define PDGNUMBER  211

// This function just load the needed libraries if we're executing from
// an interactive session.
void loadLibraries()
{
#ifdef __CINT__
  // Load the Event Generator abstraction library, Pythia 6
  // library, and the Pythia 6 interface library.
  gSystem->Load("libEG");
  //gSystem->Load("$ROOTSYS/../pythia6/libPythia6"); //change to your setup
  gSystem->Load("/Users/Bono/scratch/pythia6/libPythia6"); //change to your setup
  gSystem->Load("libEGPythia6");
#endif
}


// nEvents is how many events we want.
int makeEventSample(Int_t nEvents)
{
  // Load needed libraries
  loadLibraries();


  TPythia6* pythia = new TPythia6;
  float eMax = 5.6;
  float eGamma = 5.0;
  float eFrac = eGamma/eMax;
  pythia->SetPARP(2, 1.0);
  pythia->Initialize("FIXT","gamma","p",eMax);
  pythia->SetPARP(171,eFrac); //Set the beam energy as fraction of eMax

 





  pythia->SetMSEL(2);

  pythia->SetMSTP(13,2);
  pythia->SetMSTP(20,0);
  pythia->SetMSTP(58,4);
  pythia->SetMSTP(92,4);
  pythia->SetMSTP(101,1);
  pythia->SetMSTP(121,1);
  //pythia->SetMSTP(171,0.1); // for variable energy
  //pythia->SetMSTP(172,1); //What is this really for? 

 // pythia->SetPARP(2, 2.54739); //min egamma for pythia
  pythia->SetPARP(18, 0.17);
  pythia->SetPARP(89, 1000);
  pythia->SetPARP(91, 0.40);
  pythia->SetPARP(93, 2.0);
  pythia->SetPARP(99, 0.40);
  pythia->SetPARP(102, 0.5);
  pythia->SetPARP(103, 0.5);
  pythia->SetPARP(104, 0.3);
  pythia->SetPARP(111, 0.0);
  pythia->SetPARP(121, 2.0);
  pythia->SetPARP(161, 3.0);
  pythia->SetPARP(162, 24.6);
  pythia->SetPARP(165, 0.47679);
  pythia->SetPARP(166, 0.67597);

  pythia->SetPARJ(1, 0.029);
  pythia->SetPARJ(2, 0.283);
  pythia->SetPARJ(3, 1.20);
  pythia->SetPARJ(21, 0.40 );
  pythia->SetPARJ(23, 0.03);
  pythia->SetPARJ(41, 1.94);
  pythia->SetPARJ(42, 0.544);
  pythia->SetPARJ(45, 1.05 );

  pythia->SetMSTJ(12, 1);
  pythia->SetMSTJ(45, 4);

  pythia->SetMSTU(112, 4 );
  pythia->SetMSTU(113, 4 );
  pythia->SetMSTU(114, 4 );

  pythia->SetCKIN(1,1.0);  
  pythia->SetCKIN(66,100.0); 



  // Open an output file
  TFile* file = TFile::Open(FILENAME, "RECREATE");

  if (!file || !file->IsOpen()) {
    Error("makeEventSample", "Couldn't open file %s", FILENAME);
    return 1;
  }

  // Make a tree in that file ...
  TTree* tree = new TTree(TREENAME, "Pythia 6 tree");

  // ... and register a the cache of pythia on a branch (It's a
  // TClonesArray of TMCParticle objects. )
  TClonesArray* particles = (TClonesArray*)pythia->GetListOfParticles();
  tree->Branch(BRANCHNAME, &particles);



  // make events
  for (Int_t i = 0; i < nEvents; i++) {
    // Show how far we got every 100'th event.
    if (i % 1 == 0)
      cout << "Event # " << i << endl;

    // Make one event.
    pythia->GenerateEvent();

    // Maybe you want to have another branch with global event
    // information.  In that case, you should process that here.
    // You can also filter out particles here if you want.

    // Now we're ready to fill the tree, and the event is over.
    tree->Fill();
  }



  // Show tree structure
  tree->Print();

  // After the run is over, we may want to do some summary plots:
  TH1D* hist = new TH1D(HISTNAME, "p_{#perp}  spectrum for  #pi^{+}",
			100, 0, 3);
  hist->SetXTitle("p_{#perp}");
  hist->SetYTitle("dN/dp_{#perp}");
  char expression[64];
  sprintf(expression,"sqrt(pow(%s.fPx,2)+pow(%s.fPy,2))>>%s",
		  BRANCHNAME, BRANCHNAME, HISTNAME);
  char selection[64];
  sprintf(selection,"%s.fKF==%d", BRANCHNAME, PDGNUMBER);
  tree->Draw(expression,selection);

  // Normalise to the number of events, and the bin sizes.
  hist->Sumw2();
  hist->Scale(3 / 100. / hist->Integral());
  hist->Fit("expo", "QO+", "", .25, 1.75);
  TF1* func = hist->GetFunction("expo");
  func->SetParNames("A", "- 1 / T");
  // and now we flush and close the file
  file->Write();
  file->Close();

  return 0;

}

// Show the Pt spectra, and start the tree viewer.
int showEventSample()
{
  // Load needed libraries
  loadLibraries();

  // Open the file
  TFile* file = TFile::Open(FILENAME, "READ");
  if (!file || !file->IsOpen()) {
    Error("showEventSample", "Couldn;t open file %s", FILENAME);
    return 1;
  }

  // Get the tree
  TTree* tree = (TTree*)file->Get(TREENAME);
  if (!tree) {
    Error("showEventSample", "couldn't get TTree %s", TREENAME);
    return 2;
  }

  // Start the viewer.
  tree->StartViewer();

  // Get the histogram
  TH1D* hist = (TH1D*)file->Get(HISTNAME);
  if (!hist) {
    Error("showEventSample", "couldn't get TH1D %s", HISTNAME);
    return 4;
  }

  // Draw the histogram in a canvas
  gStyle->SetOptStat(1);
  TCanvas* canvas = new TCanvas("canvas", "canvas");
  canvas->SetLogy();
  hist->Draw("e1");
  TF1* func = hist->GetFunction("expo");

  char expression[64];
  sprintf(expression,"T #approx %5.1f", -1000 / func->GetParameter(1));
  TLatex* latex = new TLatex(1.5, 1e-4, expression);
  latex->SetTextSize(.1);
  latex->SetTextColor(4);
  latex->Draw();

  return 0;
}

void Generate2(Int_t n=100) {
   makeEventSample(n);
   showEventSample();
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication app("app", &argc, argv);

  Int_t n = 100;
  if (argc > 1)
    n = strtol(argv[1], NULL, 0);

  int retVal = 0;
  if (n > 0)
    retVal = makeEventSample(n);
  else {
    retVal = showEventSample();
    app.Run();
  }

  return retVal;
}
#endif

//____________________________________________________________________
//
// EOF
//
