

#include "Riostream.h"
void basic() {
    //  Read data from an ascii file and create a root file with an histogram and an ntuple.
    //   see a variant of this macro in basic2.C
    //Author: Rene Brun
    
    
    // read file $ROOTSYS/tutorials/tree/basic.dat
    // this file has 3 columns of float data
    TString dir = gSystem->UnixPathName(__FILE__);
    dir.ReplaceAll("basic.C","");
    dir.ReplaceAll("/./","/");
    ifstream in;
    in.open(Form("%sbasic.dat",dir.Data()));
    
    Float_t x,y,z;
    Int_t nlines = 0;
    TFile *f = new TFile("basic.root","RECREATE");
    TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
    TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");
    
    while (1) {
        in >> x >> y >> z;
        if (!in.good()) break;
        if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
        h1->Fill(x);
        ntuple->Fill(x,y,z);
        nlines++;
    }
    printf(" found %d points\n",nlines);
    
    in.close();
    
    f->Write();
}

/*/void basic()
{
    //   example of macro to read data from an ascii file and
    //   create a root file with an histogram and an ntuple.
    gROOT->Reset();
#include "iostream.h"
    
    ifstream in;
    // we assume a file basic.dat in the current directory
    // this file has 3 columns of float data
    in.open("basic.dat");
    
    Float_t x,y,z,j,k;
    Int_t nlines = 0;
    TFile *f = new TFile("basic.root","RECREATE");
    TH1F *h1 = new TH1F("h1","x distribution",100,-1,6);
    TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z:j:k");
    
    while (1) {
        in >> x >> y >> z >> j >> k;
        if (!in.good()) break;
        if (nlines < 100) printf("x=%8f, y=%8f, z=%8f, j=%8f, k=%8f",x,y,z,j,k);
        h1->Fill(x);
        ntuple->Fill(x,y,z,j,k);
        nlines++;
    }
    printf(" found %d pointsn",nlines);
    
    in.close();
    
    f->Write();
}
*/
