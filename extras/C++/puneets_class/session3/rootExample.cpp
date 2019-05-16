// program: ROOT example
// 
// input: none
// output: formatted streams of text
// 
// written by: Puneet Khetarpal
// date: October 30, 2011

// libraries included /////////////////////////////////////////////////////////
#include <iostream>
#include "TLorentzVector.h"
#include "TString.h"
#include "TFile.h"
#include "TH1F.h"
#include "TRandom3.h"
#include "TFloat.h"


using namespace std;

// global constants //////////////////////////////////////////////////////////

const Float_t BEAM_ENERGY = 5.754;                  // beam energy in GeV
const Float_t SIGMA_ENERGY = 0.025;                 // energy resolution

// function prototypes ///////////////////////////////////////////////////////

// function definitions //////////////////////////////////////////////////////

// level 0 ///////////////////////////////////////////////////////////////////

int main() {
  // Example of the TLorentzVector class
  TLorentzVector* electron = new TLorentzVector();
  
  electron->Print();  
  electron->SetPxPyPzE(0, 0, BEAM_ENERGY, BEAM_ENERGY);// electron beam in +z
  electron->Print();
  
  // Example of the TString class
  TString str = "This is an example of a TString class";
  cout << endl << str.Data() << endl << endl;
  TString str2 = Form("electron Energy: %.5f GeV", electron->E());
  cout << endl << str2.Data() << endl << endl;
  
  // Example of TFile class
  TFile* file = new TFile("rootfile.root", "recreate");
  
  // all 'TObjects' created henceforth will be added to the file
  TH1F* h = new TH1F("hist", "a histogram", 400, 5, 7); 
  
  // generate a set of random numbers
  TRandom3* random = new TRandom3; 
  Float_t randNum = 0.0;
  for (Int_t i = 0; i < 1000000; i++) {
    // generate a random number from a Gaussian function centered at
    // BEAM_ENERGY and a resolution of SIGMA_ENERGY
    randNum = random->Gaus(BEAM_ENERGY, SIGMA_ENERGY);
    // fill a histogram with this random number
    h->Fill(randNum);    
  }
    
  // write all TObjects to the TFile 
  file->Write();
  file->Close();   // closes the file and deletes all objects written to it
  
  // delete dynamically allocated variables
  delete electron;
  delete random;
    
  return 0;  
}