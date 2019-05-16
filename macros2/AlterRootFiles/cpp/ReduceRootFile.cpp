/*
Author: Jason Bono
Date: May 23 2013

Purpose: To take in a root file and produce a new file with only 1% of the events from the original file 


*/


#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>


using namespace std;


int main(int argc, char *argv[]) //use argc & argv to pass the file names through the commandline
//int main()
{

	//file name stuff
	std::string f(argv[1]);
	std::string prefix("reduced100_");
	std::string infile = f;
	std::string outfile = prefix + f;
	TFile *file = TFile::Open(infile.c_str());
	TTree *tOriginal = (TTree*)file->Get("GampTree");
	TFile *fileNew = new TFile(outfile.c_str(),"RECREATE");
	TTree *tNew = tOriginal->CloneTree(0);
	TString tNewName = "GampTree";


	//create a Trandom3 object 
	TRandom3 r3(0);//specifying 0 means a unique seed will be automatically generated using TUUID

	//loop over all entries
	Long64_t nentries = tOriginal->GetEntries();
	for (Long64_t i=0; i<nentries; i += 1 )
	{
		tOriginal->GetEntry(i);
		double RandomNumber = r3.Rndm(); //RandomNumber is a double between 0 and 1 excluding 0
		//take out 99% of the events
		if ((RandomNumber > 0.99) )
		{ 
			tNew->Fill();
		}
	}

	//fill the new tree and close the file
	tNew->Write(tNewName);
	fileNew->Close();



}


