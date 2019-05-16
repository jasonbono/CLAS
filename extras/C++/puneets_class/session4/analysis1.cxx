// program: analysis - version 1.0
//
// usage: analysis1 -h -i [input file] -o [output file] -M [max events]
// 
// input:
//    -h               - option to see program usage
//    -i [input file]  - the name of the input root file name (required)
//    -o [output file] - the name of the output root file name
//    -M [max events]  - max num of events to process
// output:
//    the output root file containing events and histogram that
//    have passed the cuts
//
// written by: Puneet Khetarpal
// 
// date: November 12, 2011
//////////////////////////////////////////////////////////////////////////////

// libraries included ////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"

#include "unistd.h"   // a C library that implements getopt()

using namespace std;

// global constants and definitions //////////////////////////////////////////

// function prototypes ///////////////////////////////////////////////////////
// level 1 
bool ParseInput(int,                         // argc
                char* [],                    // argv
                TString &,                   // input file name
                TString &,                   // output file name
                Long64_t &);                 // max events 
// level 2
void PrintUsage();

// function definitions //////////////////////////////////////////////////////

// level 0 ///////////////////////////////////////////////////////////////////

int main(int argc,          // argc: argument count
         char* argv[]) {    // argv: argument vector
  // local variables
  TString inputFileName;                    // input root file name
  TString outputFileName = "output.root";   // output root file name
  Long64_t maxEvents = -1;                  // max num of events to process
  
  // parse input parameters
  if (!ParseInput(argc, argv, inputFileName, outputFileName, maxEvents))
    exit(0);
  
  // open the input file to check if it exists or if it is valid ROOT file
  TFile* inputFile = new TFile(inputFileName.Data());
  
  // if the file is not a valid ROOT file
  // the status of the file is set to a zombie
  if (inputFile->IsZombie())
    exit(0);
    
  // if it is a valid root file, then search for a ROOT tree object
  TTree* aTree = (TTree*)inputFile->Get("h10");
  
  Long64_t entries = aTree->GetEntries();  
  cout << "Total number of entries: " << entries << endl;
  
  // consolidate max number of events to process
  if (maxEvents > entries || maxEvents == -1) 
    maxEvents = entries;
  
  // associated tree variables
  Int_t nBytes = 0;                       // total bytes read from tree
  UInt_t evntid = 0;                      // event id (unsigned integer)
  Float_t p[20];                          // 3-momentum of tracks 
  
  // print list of leaves
  aTree->GetListOfLeaves()->Print();
  
  // associate the tree branches with local variable addresses
  aTree->SetBranchAddress("evntid", &evntid);
  aTree->SetBranchAddress("p", p);
  
  // loop through the events 
  for (Long64_t trigIndex = 0; trigIndex < maxEvents; trigIndex++) {
    // get the entry for event index
    nBytes += aTree->GetEntry(trigIndex);
    
    // output info to screen
    cout << evntid << " " << p[0] << endl;
    
    // This is the heart of your code -- your analysis of events goes here!
    // You can fill your histograms, make cuts, select/reject events
    // and fill any new trees you have defined.
    // At every instance of the function "GetEntry" call, the 
    // pointers to the branches in the tree are reset to appropriate
    // addresses in the ROOT file for the event at 'trigIndex'. 
  }
  
  // cleanup
  delete aTree;
  inputFile->Close();
  
  return 0;
}

// level 1 ///////////////////////////////////////////////////////////////////

// preconditions: none
// postconditions: the input parameters are parsed and stored as needed
bool ParseInput(int argc, char* argv[], TString &inputFileName,
  TString &outputFileName, Long64_t &maxEvents) {
  // local variables
  bool result = false;
  bool inputOption = false;      // test for required input file option
  int numArgs = argc - 1;        // argv[0]: path of executable
  char opt = ' ';                // variable to store options

  // check to see if there is at least one argument to the program
  if (numArgs < 1) {
    cout << "Error: Insufficient arguments to program call - " << numArgs
      << endl << endl;
    PrintUsage();
    return result;
  }
  
  // getopt() takes in the number of command line arguments (argc)
  // an array of strings to those arguments (argv), and a string
  // of options to expect at command line. It returns the first
  // option as a character. The next call to this function with
  // same arguments returns the next option. 
  //
  // getopt() also sets some global variables, viz.:
  //   optarg - a pointer to the current option argument, if it exists
  //   optind - the index of the next argv pointer to process
  //   optopt - the last known option

  extern char* optarg;       // extern keyword declare a variable/function
  extern int optind, optopt; // its name is visible from other files
 
  // Options that require an argument after them, a ':' must be
  // specified in the options string. If you specify a ':' at the 
  // beginning of the options string, then getopt() will return
  // a ':' if it can't find a required argument to an option. If
  // you don't specify a ':' at the beginning of the list, then
  // a '?' is returned. A '?' is also returned when an unrecognized
  // option is specified.
  // 
  // When getopt() has finished parsing through all the options, 
  // it returns -1:
  // 
  // NOTE: here the compiler automatically typecasts opt as an 
  // integer when evaluating this expression  
  
  while ((opt = getopt(argc, argv, ":i:o:M:h?")) != -1) {
    switch(opt) {
      case 'i':  // check for input file
        inputFileName = optarg;
        inputOption = true;    // store whether input file option given
        break;  
      case 'o':  // check for output file
        outputFileName = optarg;
        break;
      case 'M':  // check for maximum number of events to process
        maxEvents = atol(optarg);
        // check whether max events > 0
        if (maxEvents < 1) {
          cout << "Error: invalid max number of events specified - " 
            << optarg << endl;
          PrintUsage();
          return result;
        }
        break;
      case ':':  // if a required argument is missing
        cout << "-" << char(optopt) << " without an argument\n";
      case 'h':  // fall through for ':' and 'h' is intentional
      case '?':  // -h or any other option must show usage 
        PrintUsage();
        return result;
        break;
      default:   // you won't actually get here, but for completeness...
        break;
    }
  }

  // if input root file option is not specified then issue error
  if (!inputOption) {
    cout << "Error: Input root file name required as input\n" << endl;
    PrintUsage();
    return result;
  }

  // if we have come this far then set result to true
  result = true;
  
  // print the result of the parsing
  cout << "The input file name is: " << inputFileName.Data() << endl
       << "The output file name is: " << outputFileName.Data() << endl
       << "The max number of events to process is: " << maxEvents << endl;
  
  return result;
}

// level 2 ///////////////////////////////////////////////////////////////////

// preconditions: none
// postconditions: the usage is printed
void PrintUsage() {
  cout << "usage: analysis1 -h -i [input file] -o [output file] "
       << "-M [max events]" << endl << endl
       << "    -h                   show program usage and exit\n"
       << "    -i [input file]      name of the input root file name "
       << "(required)\n"
       << "    -o [output file]     name of the output root file name\n"
       << "                         (default: output.root)\n"
       << "    -M [max events]      max num of events to process\n"
       << endl;
  
  return;
}