const int MAX_TRACKS = 50;

struct TreeStruct {
  UInt_t evntid;
  Int_t ec;
  Int_t ec_part;
  Float_t ech_x[MAX_TRACKS];
  Float_t ech_y[MAX_TRACKS];
  Float_t ech_z[MAX_TRACKS];  
};

struct ECStruct {
  Int_t eventID;
  Int_t leptonID;  
  Float_t ECx;
  Float_t ECy;
  Float_t ECz;
  Float_t ECconjx;
  Float_t ECconjy;
  Float_t ECconjz;  
};

void compareEC() {
  // local files
  TFile *f = new TFile("tpe_skim_pos_66780.root");
  
  // setup tree
  TTree *tree = (TTree*)f->Get("h10");
    
  // setup struct
  TreeStruct aStruct;
  
  // set branch addresses
  tree->SetBranchAddress("evntid", &aStruct.evntid);
  tree->SetBranchAddress("ec", &aStruct.ec);
  tree->SetBranchAddress("ec_part", &aStruct.ec_part);
  tree->SetBranchAddress("ech_x", aStruct.ech_x);
  tree->SetBranchAddress("ech_y", aStruct.ech_y);
  tree->SetBranchAddress("ech_z", aStruct.ech_z);
  
  // open swim file for reading 
  ifstream str("testec-pos.dat");
  ECStruct ecStruct;
  
  // read the first line
  char line[256];
  
  str.getline(line, 256);
  
  Int_t counter = 0;
  Int_t nEntries = tree->GetEntries();

  // histograms
  TH2F* hX = new TH2F("hx", "hx", 250, -500, 500, 250, -500, 500);
  TH2F* hY = new TH2F("hy", "hy", 250, -500, 500, 250, -500, 500);
  TH2F* hZ = new TH2F("hz", "hz", 500, 0, 1000, 500, 0, 1000);

  TH2F* hXc = new TH2F("hxc", "hxc", 250, -500, 500, 250, -500, 500);
  TH2F* hYc = new TH2F("hyc", "hyc", 250, -500, 500, 250, -500, 500);
  TH2F* hZc = new TH2F("hzc", "hzc", 500, 0, 1000, 500, 0, 1000);

  // loop variables
  Int_t fileCount = 0;
  const Int_t MAXEVENTS = 10000;
  
  while (ReadRecord(str, ecStruct) && fileCount < MAXEVENTS) {
    //cout << ecStruct.eventID << " " << ecStruct.leptonID << " " 
    //  << ecStruct.ECx << " " << ecStruct.ECy << " " << ecStruct.ECz 
    //  << ecStruct.ECconjx << " " << ecStruct.ECconjy << " " << ecStruct.ECconjz 
    //  << endl;
      
    bool Found = false;

    // loop through root tree until the event id is found
    while (!Found && counter < nEntries) {
      tree->GetEntry(counter);
      
      // if the event id is matched, then store info
      if (aStruct.evntid == ecStruct.eventID) {
        Found = true;
        
        //cout << "Found: " << aStruct.evntid << " " << ecStruct.eventID << endl;
        Int_t i = aStruct.ec[ecStruct.leptonID] - 1;
        if (i < 0 || i >= aStruct.ec_part) {
          cout << "Error: invalid ec lepton index " << i << " exiting\n";
        } else {
          //cout << "ech_x: " << aStruct.ech_x[i] << " " << ecStruct.ECx << endl
          //   << "ech_y: " << aStruct.ech_y[i] << " " << ecStruct.ECy << endl
          //   << "ech_z: " << aStruct.ech_z[i] << " " << ecStruct.ECz << endl;
             
          hX->Fill(aStruct.ech_x[i], ecStruct.ECx);   
          hY->Fill(aStruct.ech_y[i], ecStruct.ECy);   
          hZ->Fill(aStruct.ech_z[i], ecStruct.ECz);   

          hXc->Fill(ecStruct.ECx, ecStruct.ECconjx);   
          hYc->Fill(ecStruct.ECy, ecStruct.ECconjy);   
          hZc->Fill(ecStruct.ECz, ecStruct.ECconjz);   
        }        
      }
      
      counter++;
    }
      
      
    fileCount++;
  }
  
  str.close();
  
  
  TCanvas *can = new TCanvas("can", "canvas", 1000, 900);
  can->Divide(3, 2);
  
  can->cd(1);
  gPad->SetMargin(.15, .1, .15, .1);
  gPad->SetGrid();
  myDraw2(hX, "RECSIS EC X (cm)", "Swim EC X (cm)");
  gPad->Update();

  can->cd(2);
  gPad->SetMargin(.15, .1, .15, .1);
  gPad->SetGrid();
  myDraw2(hY, "RECSIS EC Y (cm)", "Swim EC Y (cm)");
  gPad->Update();

  can->cd(3);
  gPad->SetMargin(.15, .1, .15, .1);
  gPad->SetGrid();
  myDraw2(hZ, "RECSIS EC Z (cm)", "Swim EC Z (cm)", 300, 600, 300, 600);
  gPad->Update();
  
  can->cd(4);
  gPad->SetMargin(.15, .1, .15, .1);
  gPad->SetGrid();
  myDraw2(hXc, "Swim EC X (cm)", "Conjugate EC X (cm)");
  gPad->Update();

  can->cd(5);
  gPad->SetMargin(.15, .1, .15, .1);
  gPad->SetGrid();
  myDraw2(hYc, "Swim EC Y (cm)", "Conjugate EC Y (cm)");
  gPad->Update();

  can->cd(6);
  gPad->SetMargin(.15, .1, .15, .1);
  gPad->SetGrid();
  myDraw2(hZc, "Swim EC Z (cm)", "Conjugate EC Z (cm)", 300, 600, 300, 600);
  gPad->Update();


}

// preconditions: the file stream is opened for reading and ec struct has been
//    init
// postconditions: a record from the file is read and its contents are stored
//    in ec struct
bool ReadRecord(ifstream & str, ECStruct & ecStruct) {
  Float_t tempF;
  Int_t tempI;
  bool result = false;
    
  if (str >> tempI >> ecStruct.eventID >> ecStruct.leptonID >> tempI 
    >> tempI >> tempF >> tempF >> tempF >> tempF >> tempF >> tempF 
    >> tempI >> tempI >> tempI >> tempI >> tempI >> ecStruct.ECx >> ecStruct.ECy
    >> ecStruct.ECz >> ecStruct.ECconjx >> ecStruct.ECconjy
    >> ecStruct.ECconjz) {
    result = true;    
  }
  
  return result;
}
