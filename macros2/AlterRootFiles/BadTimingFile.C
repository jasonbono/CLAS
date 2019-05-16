/*
 
 Made in March, 2017 to show what the bad timing cuts do
 
 Author: Jason Bono
 
 Date: January 31 2013
 
 Purpose: To write a new lighter file
 
 Usage:    > root -l -b
 > .L BasicTreeFile("somefile.root")
 
 which will output somefile_Basic.root
 
 */

#include "/Users/Bono/clas/myDefinitions/BasicParameters.h"  //for local
//#include "/u/home/jbono/myDefinitions/BasicParameters.h"  //for farm

void BadTimingFile(TString passed)
{
    
    
    
    string input(passed);
    string filename = input.substr(0,input.find_last_of("."));
    string extention = input.substr(input.find_last_of("."));
    string tackon("_BadTiming");
    string output = filename + tackon + extention;
    cout <<"input = "<< input <<"   output = " <<output<<endl;
    
    
    //string treename("gpp2kppim");
    string treename("v16");
    //TString tNewName("sim");
    TString tNewName = treename.c_str();
    TFile *file = TFile::Open(input.c_str());
    TTree *tOriginal = (TTree*)file->Get(treename.c_str());
    TFile *fileNew = new TFile(output.c_str(),"RECREATE");
    TTree *tNew = tOriginal->CloneTree(0);
    
    
    //now list all varibles to use in the filter
    Float_t beam, stv, scv;
    Float_t np, npip, nkm;
    Float_t nphoton_nb1;
    Float_t vx, vy, vz;
    Float_t vtime, sctkp1, sclkp1, betakp1;
    Float_t sctkp2, sclkp2, betakp2;
    
    tOriginal->SetBranchAddress("beam", &beam);
    tOriginal->SetBranchAddress("stv", &stv);
    tOriginal->SetBranchAddress("scv", &scv);
    tOriginal->SetBranchAddress("np", &np);
    tOriginal->SetBranchAddress("npip", &npip);
    tOriginal->SetBranchAddress("nkm", &nkm);
    tOriginal->SetBranchAddress("nphoton_nb1", &nphoton_nb1);
    tOriginal->SetBranchAddress("vx", &vx);
    tOriginal->SetBranchAddress("vy", &vy);
    tOriginal->SetBranchAddress("vz", &vz);
    tOriginal->SetBranchAddress("vtime", &vtime);
    tOriginal->SetBranchAddress("sctkp1", &sctkp1);
    tOriginal->SetBranchAddress("sclkp1", &sclkp1);
    tOriginal->SetBranchAddress("betakp1", &betakp1);
    tOriginal->SetBranchAddress("sctkp2", &sctkp2);
    tOriginal->SetBranchAddress("sclkp2", &sclkp2);
    tOriginal->SetBranchAddress("betakp2", &betakp2);
    
    //loop over the entries and fill the new tree for those passing the filter
    Long64_t nentries = tOriginal->GetEntries();
    for (Long64_t i=0; i<nentries; i++)
    {
        
        if(i % 10000==0) {
            // do a cout every every 100 entries
            Float_t tempi = i;
            Float_t tempN = nentries;
            cout <<"nentires is" << nentries << "   i=" << i <<"  have completed  " << (tempi/tempN)*100 << "% of the job" << endl;
        }
        tOriginal->GetEntry(i);
        
        //the  tBasic
        bool cut_n = np < BasicParameterA && npip < BasicParameterB && nkm < BasicParameterC;
        bool cut_np = nphoton_nb1 < BasicParameterD;
        bool cut_vcut = abs(vz + BasicParameterE) < BasicParameterF && sqrt(vx*vx+vy*vy) < BasicParameterG;
        bool cut_beam = beam > BasicParameterH;
        bool cut_st = abs(stv - scv) >= BasicParameterI;
        bool cut_tof1 = abs(vtime - (sctkp1 - sclkp1/(betakp1*29.99))) >= BasicParameterJ;
        bool cut_tof2 = abs(vtime - (sctkp2 - sclkp2/(betakp2*29.99))) >= BasicParameterK;
        bool cut_Basic = cut_st;
        
        if ( cut_Basic )
        {
            tNew->Fill();
        }
    }
    //fill the Basic tree
    cout <<"Filling the Basic tree" <<endl;
    tNew->Write(tNewName);
    //fileNew->Write();
    
    
    //see how much the data was reduced
    Long64_t nentries_Basic = tNew->GetEntries();
    cout << "The number of entries in tOriginal is " << nentries << endl;
    cout << "The number of entries in tNew is " << nentries_Basic << endl;
    Float_t nf, nf2, nf3;
    nf = nentries;
    nf3 = nentries_Basic;
    cout << 100.0*(( nf - nf3 )/(nf))  << " % of entries were taken out of the original tree " << endl;cout << "TEST1" <<endl;
    
    //quit root
    gROOT->ProcessLine(".q");
}
