// gen.C
//
// usage: root -n gen.C
//
// This macro generates some files with 10K events using a 
// Gaussian + Linear Polynomial

// include libraries for random generator (RAND_MAX) ////////////////////////
#include <stdlib.h>

// declare constants ////////////////////////////////////////////////////////
const Int_t MAX_FILES = 8;
const Int_t MAX_EVENTS = 10000;

// level 0 //////////////////////////////////////////////////////////////////
void gen() {
  // set seed for pseudo random number generator
  srand(time(0));
  gRandom->SetSeed(0);
  
  // statements
  for (Int_t i = 0; i < MAX_FILES; i++) {
    // setup file name
    TString fileName = Form("datafiles/data_%d.dat", i+1);
    // open file for writing 
    ofstream str(fileName.Data());
    // init a new function    
    TF1* f = new TF1("f", "gaus(0)+pol1(3)", -2, 2);
    // get random values to store as parameters
    float mean = getRandom(-0.02, 0.02);
    float sigma = getRandom(0.15, 0.2);
    float p0 = getRandom(0.0, 0.1);
    float p1 = getRandom(0.0, 0.01);
    // set parameters for function
    f->SetParameters(1., mean, sigma, p0, p1);
    
    // generate random numbers and write to file
    for (Int_t j = 0; j < MAX_EVENTS; j++) {
      // store random value
      Float_t randvalue = f->GetRandom();
      // write to file
      str << randvalue << endl;
    }
    // cleanup
    delete f;
    str.close();
  }
}

// level 1 //////////////////////////////////////////////////////////////////

// precondition: psuedo-random seed has been set
// postcondition: random number is generated between min and max and returned
float getRandom(float min, float max) {
  return min + (max - min)*rand() / ((float)RAND_MAX);  
}
