#include <stdlib.h>
//#include <vector>
//#include <fstream>
//#include <string>
#include <sstream>
#include "TApplication.h"
#include "TPythia6.h"
#include "TFile.h"
#include "TError.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "Riostream.h"
#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include "TMCParticle.h"
#include "TObjArray.h"
#include "TRandom.h"
#include "simTrees.h"
#include "TDatabasePDG.h"




extern "C" {
#include "errno.h"
#include "ntypes.h"
#include "bostypes.h"
  void bnames_(int *);
  void initbos(void);
  int configure_banks(FILE *out, int verbose);
  void bankList(BOSbank *bcs, char *list, char *banklist);
  //void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow);
  void loadBos(int eventNumber,int NumParticles,vsGen_t *vsGen);
  float gpxsecp_(float *, int *);
  float gpxsect_(float *);
}

struct vsDefaults_t {
  char outFileName[80];
  int nToGen,coreRxn,rSeed,pyEdit,printToScreen,phoType;
  double eMin,eMax,tLength,tOffset,vResolution,beamSigma;
};

void printUsage(); // print usage
vsDefaults_t readVsDefaults(); //Read the default settings from vsDefaults.conf
Double_t initEvent(TPythia6 *myPythia, int coreRxn,double eMax,
		   double eGamma,TRandom *testRand,int phoType,
		   TLorentzVector *vPhoton,double *QsqPtr); // initialize event
void setPythiaPars(TPythia6 *myPythia,int phoType); // Set the Pythia parameters
void setBranchesT1(TTree *t1, vsGen_t *vsGen);
void fillXsecHistos(TH1D *h101,TH1D *h102);
TLorentzVector vPho(TRandom *ranGen,TLorentzVector *eScat);
void ytCMlimits(double *yCMlow,double *yCMhigh,double *tCMlow,double *tCMhigh,double *QsqLow,double *QsqHigh);

//Define some cross section histograms
TH1D *h101 = new TH1D("h101","kpk0cas0: xSec vs. Egamma",91,2.95,12.05);
TH1D *h102 = new TH1D("h102","kpkpcasm: xSec vs. Egamma",91,2.95,12.05);

//Define some virtual photon histograms
TH1D *h201 = new TH1D("h201","#nu",160,6.5,10.5);
TH1D *h202 = new TH1D("h202","Q^{2}",350,0.0,0.35);
TH2D *h2000 = new TH2D("h2000","Q^{2} vs #nu",80,6.5,10.5,350,-0.0,0.35);

int main(int argc, char **argv)
{
  //START TEST AREA
  int nmax = 300;
  char  mess[100];
  char  *OutBanks = "HEADMCTKMCVXTAGRPART";
  char  *OutFile = NULL;
  //---> Initialize the BOS banks
  bnames_(&nmax);
  initbos();
  configure_banks(stderr, 0);

  //---> Create the bankList
  bankList(&bcs_, "C=", OutBanks);

  //---> Define the output file: OutFile
  char tmp[100];
  char  out[30];
  //int runNumber = 999;
  //sprintf(tmp, "vsd.%d.bos", runNumber); 
  //fprintf(stdout,"tmp = %s\n",tmp);
  //OutFile = tmp;

  //---> Get the HEAD bank
  //clasHEAD_t *HEAD = NULL;
  //clasHEAD_t *HEAD;
  //HEAD = makeBank(&bcs_,"HEAD",1,sizeof(head_t),2);
  
  //---> Get the MCTK bank
  //clasMCTK_t *MCTK = NULL;
  //MCTK = makeBank(&bcs_,"MCTK",1,sizeof(mctk_t),2);


  //END TEST AREA


  int i;
  char outFileName[80];
  int nToGen,coreRxn,rSeed,pyEdit,printToScreen,phoType;
  double eMin,eMax,tLength,tOffset,vResolution,beamSigma;
  char *argptr; 
  
  vsDefaults_t vsDefaults = readVsDefaults(); //Read the defaults

  //Set the histogram titles
  h101->SetTitle("#gamma p #rightarrow K^{+} K^{0} #Xi^{0}");
  h101->GetYaxis()->SetTitle("#sigma (nanobarns)");
  h101->GetXaxis()->SetTitle("E_{#gamma} (MeV)");
  
  h102->SetTitle("#gamma p #rightarrow K^{+} K^{+} #Xi^{-}");
  h102->GetYaxis()->SetTitle("#sigma (nanobarns)");
  h102->GetXaxis()->SetTitle("E_{#gamma} (MeV)");

  //Set the defaults
  sprintf(outFileName,vsDefaults.outFileName);
  nToGen = vsDefaults.nToGen;
  coreRxn = vsDefaults.coreRxn;
  rSeed = vsDefaults.rSeed;
  pyEdit = vsDefaults.pyEdit;
  eMin = vsDefaults.eMin;
  eMax = vsDefaults.eMax;
  tOffset = vsDefaults.tOffset;
  tLength = vsDefaults.tLength;
  vResolution = vsDefaults.vResolution;
  beamSigma = vsDefaults.beamSigma;
  phoType = vsDefaults.phoType;

  for (i=1; i<argc; i++) {
    argptr = argv[i];
    if (*argptr == '-') {
      argptr++;
      switch (*argptr) { 
      case 'h':
        printUsage();
        break;
      case 'r':
        rSeed = atoi(++argptr);
        break;
      case 'R':
        coreRxn = atoi(++argptr);
        break;
      case 'n':
        nToGen = atoi(++argptr);
        break;
      case 'x':
        pyEdit = atoi(++argptr);
        break;
      case 'p':
        printToScreen = atoi(++argptr);
        break;
      case 'l':
        eMin = atof(++argptr);
        break;
      case 'u':
        eMax = atof(++argptr);
        break;
      case 't':
        tLength = atof(++argptr);
        break;
      case 'O':
        tOffset = atof(++argptr);
        break;
      case 'v':
        vResolution = atof(++argptr);
        break;
      case 'b':
        beamSigma = atof(++argptr);
        break;
      case 'o':
	strcpy(outFileName,++argptr);
        break;
      case 'e':
	phoType =  atoi(++argptr);
        break;
      default:
        fprintf(stderr,"Unrecognized argument: [-%s]\n\n",argptr);
        printUsage();
        break;
      }
    }
  }
  //---> Open the output file (output file can NOT already exist)
  //sprintf(out, "OPEN BOSOUTPUT UNIT=2 FILE=\"%s\" WRITE STATUS=NEW RECL=3600", OutFile);

  //sprintf(tmp, "vsd.%d.bos", runNumber); 
  //fprintf(stdout,"tmp = %s\n",tmp);
   
  sprintf(tmp,outFileName); 
  OutFile = tmp;
  sprintf(out, "OPEN BOSOUTPUT UNIT=2 FILE=\"%s\" WRITE STATUS=NEW RECL=3600", OutFile);
  if (!fparm_c(out)) {
    fprintf(stderr,"%s: Unable to open file \'%s\': %s.  Maybe it already exists?\n\n", argv[0],
            out,strerror(errno));
    exit(1);
  }

  //TFile *fout = new TFile(outFileName,"RECREATE");  //DEFINE OUTPUT ROOT FILE
  double eGamma;


  // Define a tree to store the data
  TTree *t1 = new TTree("t1","generatedEvents");
  vsGen_t vsGen; //vsGen_t defined in simTrees.h
  setBranchesT1(t1, &vsGen); //setBranchesT1 defined in simTrees.h

  TPythia6 *myPythia = new TPythia6();
  TRandom *rand1=new TRandom();

  //Fill some cross section histograms
  fillXsecHistos(h101,h102);

  if (rSeed !=0){ 
    myPythia->SetMRPY(1,rSeed);    //SET RANDOM NUMBER SEED FOR PYTHIA
    myPythia->SetMRPY(2,0);        //TELL PYTHIA TO RESET THE RANDOM NUMBER
    rand1->SetSeed(rSeed);         //SET RANDOM NUMBER SEED FOR TRandom
  }

  double vOffset,zTargetMin,zTargetMax,vSmearX,vSmearY,vSmearZ;
  double vOffsetX,vOffsetY,vOffsetXY,vOffsetPhi;
  int eventTot = 0;
  while (eventTot<nToGen){ //Generate nToGen events
    //FOR REAL PHOTONS: Generate the photon energy uniform over [eMin,eMax]
    eGamma = rand1->Uniform(eMin,eMax);

    //Find the target limits
    zTargetMin = tOffset - tLength/2.0;
    zTargetMax = tOffset + tLength/2.0;

    //Generate the vertex offset due to extended target
    vOffset = rand1->Uniform(zTargetMin,zTargetMax);

    //Generate the vertex offset due to beam spot size
    vOffsetXY = rand1->Gaus(0.0,beamSigma);    
    vOffsetPhi = rand1->Uniform(-TMath::Pi(),TMath::Pi());
    vOffsetX = vOffsetXY*cos(vOffsetPhi);
    vOffsetY = vOffsetXY*sin(vOffsetPhi);

    TLorentzVector vPhoton;
    double Qsq;
    int killEvent = 0;
    vsGen.vsWeight = initEvent(myPythia,coreRxn,eMax,eGamma,rand1,phoType,&vPhoton,&Qsq); //Initialize the reaction
    //vsWeight is the total cross section for pythia determined reactions in micro-barns

    if (coreRxn==0) {
      myPythia->GenerateEvent();
    } else {
      myPythia->Pyexec(); //Decay the particles
      myPythia->ImportParticles(); //Need this call if GenerateEvent method not used
    }

    if (pyEdit == 1) myPythia->Pyedit(2); //Remove decayed particles
    if (printToScreen == 1) myPythia->Pylist(1); //Print the final state to screen

    int numParticles = myPythia->GetNumberOfParticles();
    TObjArray *particles = myPythia->GetListOfParticles();
    TMCParticle *myParticle;
    
    //fout->cd();
    Int_t nGen = 0;
    int vPhoIndex = -1;
    int nVpho = 0;
    int neScat = 0;
    int eScatIndex = -1;
    double chargeVal;
    for(int j = 0; j < numParticles; j++) {
      myParticle = (TMCParticle*)particles->At(j);
      vsGen.kf[nGen] = myParticle->GetKF();
      vsGen.ks[nGen] = myParticle->GetKS();
      vsGen.parent[nGen] = myParticle->GetParent();
      vsGen.E[nGen] = myParticle->GetEnergy();
      vsGen.m[nGen] = myParticle->GetMass();
      vsGen.px[nGen] = myParticle->GetPx();
      vsGen.py[nGen] = myParticle->GetPy();
      vsGen.pz[nGen] = myParticle->GetPz();
      vsGen.vx[nGen] = myParticle->GetVx();
      vsGen.vy[nGen] = myParticle->GetVy();
      vsGen.vz[nGen] = myParticle->GetVz();

      chargeVal = TDatabasePDG::Instance()->GetParticle(vsGen.kf[nGen])->Charge();
      chargeVal = chargeVal/3.0;
      vsGen.charge[nGen] = chargeVal;
      //cout<<"charge = "<<chargeVal<<endl;
      //Reset vertex to cm instead of mm
      vsGen.vx[nGen] = vsGen.vx[nGen]/10.0;
      vsGen.vy[nGen] = vsGen.vy[nGen]/10.0;
      vsGen.vz[nGen] = vsGen.vz[nGen]/10.0;

      //Randomly place vertex along z within target
      vsGen.vz[nGen] = vsGen.vz[nGen] + vOffset;

      //Randomly place the vertex in XY due to sigma of beam profile
      vsGen.vx[nGen] = vsGen.vx[nGen] + vOffsetX;
      vsGen.vy[nGen] = vsGen.vy[nGen] + vOffsetY;

      //Randomly smear vertex due to detector vertex resolution
      vSmearX = rand1->Gaus(0.0,vResolution);
      vSmearY = rand1->Gaus(0.0,vResolution);
      vSmearZ = rand1->Gaus(0.0,vResolution);
      vsGen.vx[nGen] = vsGen.vx[nGen] + vSmearX;
      vsGen.vy[nGen] = vsGen.vy[nGen] + vSmearY;
      vsGen.vz[nGen] = vsGen.vz[nGen] + vSmearZ;

      if (vsGen.kf[nGen] == 22 && vsGen.parent[nGen] == 1 && vsGen.ks[nGen] == 21) {
	nVpho++;
	vPhoIndex = nGen;
      }
      if (vsGen.kf[nGen] == 11 && vsGen.parent[nGen] == 1 && vsGen.ks[nGen] == 21) {
	neScat++;
	eScatIndex = nGen;
      }
      nGen++;
    }

    vsGen.nGen = nGen;
    vsGen.eGamma = eGamma;

    if (coreRxn ==0 && phoType == 1){//Set the virtual photon information
      vPhoton.SetE(vsGen.E[vPhoIndex]);
      vPhoton.SetPx(vsGen.px[vPhoIndex]);
      vPhoton.SetPy(vsGen.py[vPhoIndex]);
      vPhoton.SetPz(vsGen.pz[vPhoIndex]);
      Qsq = -vPhoton.M2();
    }

    if (coreRxn ==0 && phoType ==1) {//Get the scattered electron information
      killEvent = 0;
      TLorentzVector eScat(vsGen.px[eScatIndex],vsGen.py[eScatIndex],
			   vsGen.pz[eScatIndex],vsGen.E[eScatIndex]);
      if (eScat.Theta()*TMath::RadToDeg()<1.0) killEvent = 1;
      if (eScat.Theta()*TMath::RadToDeg()>5.0) killEvent = 1;
      if (vPhoton.E()<7.0 || vPhoton.E()>10.0) killEvent = 1;
    }

    if (phoType==1) {//Set the virtual photon information
      vsGen.eGamma = vPhoton.E();
      vsGen.pXGamma = vPhoton.Px();
      vsGen.pYGamma = vPhoton.Py();
      vsGen.pZGamma = vPhoton.Pz();
      Qsq = -vPhoton.M2();
      vsGen.Qsq = -vPhoton.M2();
      if (killEvent == 0){
	h2000->Fill(vPhoton.E(),Qsq);
	h201->Fill(vPhoton.E());
	h202->Fill(Qsq);
      }

    } else {
      vsGen.eGamma = eGamma;
      vsGen.pXGamma = 0.0;
      vsGen.pYGamma = 0.0;
      vsGen.pZGamma = eGamma;
      Qsq = 0.0;
      vsGen.Qsq = 0.0;
    }

    if (killEvent == 0) {
      t1->Fill(); //Fill the tree
      eventTot++;

      loadBos(eventTot,numParticles,&vsGen); //Load the bos banks
      //---> Write event to file
      //putBOS(&bcs_, 2, "C");
  
      //--> Tidy up 
      //dropAllBanks(&bcs_,"C");
      //cleanBanks(&bcs_);

    } 
      if(eventTot%1000 == 0 && coreRxn == 0) fprintf(stdout,"done %d\n",eventTot);
      if(eventTot%10000 == 0 && coreRxn != 0) fprintf(stdout,"done %d\n",eventTot);
  }
  //Write out some histograms
  //h101->Write();
  //h102->Write();
  //h2000->Write();
  //h201->Write();
  //h202->Write();
  //t1->Write(); //Write out the tree
  //fout->Close(); //Close the file

  //--> Clean up and go home 
  putBOS(&bcs_, 2, "0");
  sprintf(mess,"CLOSE BOSOUTPUT UNIT=2");
  fparm_c(mess);

  return 0;
}
////////////////////////////////////////
Double_t initEvent(TPythia6 *myPythia,int coreRxn,double eMax,
		   double eGamma,TRandom *testRand,int phoType,
		   TLorentzVector *vPhoton,double *QsqPtr){
  static int oneShot = 0;
  double eFrac;
  Double_t vsWeight = 1.0;
  int xBin;
  TLorentzVector e2v4,v4Photon;
  eFrac = eGamma/eMax;

    if (oneShot==0) setPythiaPars(myPythia,phoType); 
  if (coreRxn == 0) { //Pythia defined reactions using real photons
    if (phoType == 0) {
      if (oneShot==0) myPythia->Initialize("FIXT","gamma","p+",eMax);
      myPythia->SetPARP(171,eFrac); //Set the beam energy as fraction of eMax
      //Find gp total cross section and set the weight 
      float xSection;
      float eGamma1;
      eGamma1 = (float)(eGamma);
      xSection = gpxsect_(&eGamma1);
      vsWeight = (double)(xSection);
      vsWeight = vsWeight/1000.0; //Convert to micro-barns
    }
    
    if (phoType == 1 && oneShot == 0) {  //Pythia defined reactions using real virtual photons
      eMax = 11.0;
      eFrac = 1.0;

      double yCMlow=0.0,yCMhigh=0.0,tCMlow=0.0,tCMhigh=0.0,QsqLow = 0.0,QsqHigh = 0.0;
      //Find the pythia limits for scattered electron angle, energy fraction and Qsq
      ytCMlimits(&yCMlow,&yCMhigh,&tCMlow,&tCMhigh,&QsqLow,&QsqHigh);

      //Set the pythia limits for scattered electron angle, energy fraction and Qsq
      myPythia->SetCKIN(69,tCMlow);
      myPythia->SetCKIN(70,tCMhigh);
      myPythia->SetCKIN(61,yCMlow);
      myPythia->SetCKIN(62,yCMhigh);
      myPythia->SetCKIN(65,QsqLow);
      myPythia->SetCKIN(66,QsqHigh);

      //Initialize phythia 
      if (oneShot==0) myPythia->Pyinit("FIXT","gamma/e-","p+",eMax);
    }
  }
  if (coreRxn > 0) { //Predefined reactions
    double mPro = TDatabasePDG::Instance()->GetParticle("proton")->Mass();
    double mTarg = mPro;
    int nParticles = 0;
    int partCode[25];
    double masses[25];
    double masses0[25];
    double uToGeV = 0.931502;
    TLorentzVector target(0.0, 0.0, 0.0, mTarg);
    TLorentzVector proI(0.0, 0.0, 0.0, mPro);
    TLorentzVector beam(0.0, 0.0, eGamma, eGamma);
    TLorentzVector wTmpVec;
    wTmpVec = beam + proI;
    double wTmpVal = wTmpVec.Mag();
    double mMin = wTmpVal - mPro;

    *vPhoton = beam;
    
    if (phoType == 1) {//Reassign beam as virtual photon
      v4Photon = vPho(testRand,&e2v4);
      beam = v4Photon;
      *vPhoton = v4Photon;
    }
    TLorentzVector W = beam + target;

    //cout <<"mTarg, mTarg0 = "<<mTarg<<", "<<mTarg0<<endl;
    TGenPhaseSpace event;

    if (coreRxn == 11) { //p pi+ pi-
      double mTarg0 = 12.0*uToGeV; //C12
      double mTarg1 = 11.009305*uToGeV; //B11
      TLorentzVector target0(0.0, 0.0, 0.0, mTarg0);
      TLorentzVector W0 = beam + target0;
      TGenPhaseSpace event0;
      double Es = 0.016;
      TRandom *randNew=new TRandom();
      double deltaEs = testRand->Gaus(0.0,0.00293);
      Es += deltaEs;
      TLorentzVector beam1(0.0, 0.0, eGamma-Es, eGamma-Es);
      TLorentzVector W1 = beam1 + target;
      masses0[0] = W1.Mag();
      masses0[1] = mTarg1;
      event0.SetDecay(W0,2,masses0); //Initialize the state in genbod
      double testVal = 2.0;
      vsWeight = 0.0;
      while(testVal>vsWeight){//Monte Carlo the event to allow vsWeight=1 
	vsWeight = event0.Generate(); //Get the weight
	testVal = testRand->Uniform(0.0,1.0); //Grab a test value
      }
      //Since output of TGenPhaseSpace has been Monte Carlo'd, set vsWeight=1
      vsWeight = 1.0; 
      TLorentzVector *Wtmp;
      Wtmp = event0.GetDecay(0);
      W = *Wtmp;
      
      //cout<<"masses0 = "<<masses0[0]<<", "<<masses0[1]<<endl;
      //cout<<"mTArg0 = "<<mTarg0<<endl;
      //cout<<"W0.Mag() = "<<W0.Mag()<<endl;
      //cout<<"Wtmp->E() = "<<Wtmp->E()<<endl;
      //cout<<"W.Mag() = "<<W.Mag()<<endl;

      nParticles = 3;
      partCode[0] = 2212; // proton
      partCode[1] = 211;  // pi+
      partCode[2] = -211;  // pi-
    }   

    if (coreRxn == 12) { //p pi+ pi-
      double mTarg0 = 15.994915*uToGeV;; //O16
      double mTarg1 = 15.000109*uToGeV; //N15
      TLorentzVector target0(0.0, 0.0, 0.0, mTarg0);
      TLorentzVector W0 = beam + target0;
      TGenPhaseSpace event0;
      double Es = 0.012;
      double deltaEs = randNew->Gaus(0.0,0.00293);
      Es += deltaEs;
      TLorentzVector beam1(0.0, 0.0, eGamma-Es, eGamma-Es);
      TLorentzVector W1 = beam1 + target;
      masses0[0] = W1.Mag();
      masses0[1] = mTarg1;
      event0.SetDecay(W0,2,masses0); //Initialize the state in genbod
      double testVal = 2.0;
      vsWeight = 0.0;
      while(testVal>vsWeight){//Monte Carlo the event to allow vsWeight=1 
	vsWeight = event0.Generate(); //Get the weight
	testVal = testRand->Uniform(0.0,1.0); //Grab a test value
      }
      //Since output of TGenPhaseSpace has been Monte Carlo'd, set vsWeight=1
      vsWeight = 1.0; 
      TLorentzVector *Wtmp;
      Wtmp = event0.GetDecay(0);
      W = *Wtmp;
      
      //cout<<"masses0 = "<<masses0[0]<<", "<<masses0[1]<<endl;
      //cout<<"mTArg0 = "<<mTarg0<<endl;
      //cout<<"W0.Mag() = "<<W0.Mag()<<endl;
      //cout<<"Wtmp->E() = "<<Wtmp->E()<<endl;
      //cout<<"W.Mag() = "<<W.Mag()<<endl;

      nParticles = 3;
      partCode[0] = 2212; // proton
      partCode[1] = 211;  // pi+
      partCode[2] = -211;  // pi-
    }   

    
    if (coreRxn == 1) { //p pi+ pi-
      nParticles = 3;
      partCode[0] = 2212; // proton
      partCode[1] = 211;  // pi+
      partCode[2] = -211;  // pi-
    }  
    if (coreRxn == 2) { //p pi+ pi- pi0
      nParticles = 4;
      partCode[0] = 2212; // proton
      partCode[1] = 211;  // pi+
      partCode[2] = -211;  // pi-
      partCode[3] = 111;  //pi0
    }  
    if (coreRxn == 3) { //p rho0
      nParticles = 2;
      partCode[0] = 2212; // proton
      partCode[1] = 113;  // rho0
    }  
    if (coreRxn == 4) { //p eta
      nParticles = 2;
      partCode[0] = 2212; // proton
      partCode[1] = 221;  // eta
    }  
    if (coreRxn == 5) { //(Xi0)* K+ K0
      nParticles = 3;
      partCode[0] = 3324; // (Xi0)*
      partCode[1] = 321;  // K+
      partCode[2] = 311;  // K0
    }  
    
    
    //Load up myPythia with dummy energies and angles. Also get the masses
    for (int i=0; i<nParticles; i++) {
      int goMass = 1;
      while (goMass==1) {
	myPythia->Py1ent(i+1,partCode[i],5.0,0.0,0.0);
	masses[i] = myPythia->GetP(i+1,5);//Set the masses

	//cout<<"m, mMin = "<<masses[i]<<", "<<mMin<<endl;
	if (masses[i]<mMin || partCode[i] == 2212) goMass = 0;
      }
    }
    if (phoType == 1) {//Load the scattered electron for virtual photon processes
      myPythia->Py1ent(nParticles+1,11,e2v4.E(),e2v4.Theta(),e2v4.Phi());
    }

    //Phase space generate
    event.SetDecay(W,nParticles,masses); //Initialize the state in genbod
    Double_t testVal = 2.0;
    vsWeight = 0.0;
    while(testVal>vsWeight){//Monte Carlo the event to allow vsWeight=1 
      vsWeight = event.Generate(); //Get the weight
      testVal = testRand->Uniform(0.0,1.0); //Grab a test value
    }
    //Since output of TGenPhaseSpace has been Monte Carlo'd, set vsWeight=1
    vsWeight = 1.0; 

    //Load up the genbod momentum and energies into pythia
    for (int i=0; i<nParticles; i++) {
      TLorentzVector *pTmp;
      pTmp = event.GetDecay(i);
      myPythia->SetP(i+1,1,pTmp->Px());
      myPythia->SetP(i+1,2,pTmp->Py());
      myPythia->SetP(i+1,3,pTmp->Pz());
      myPythia->SetP(i+1,4,pTmp->E());
    }
  }
  if (coreRxn == -1) {//TEST AREA
  }
  oneShot++;
  return vsWeight;
}
////////////////////////////////////////
void fillXsecHistos(TH1D *h101,TH1D *h102) {
  char *fToRead;
  string line;
  stringstream os(line);
  string temp;
  int emptyLine;
  double eVal,xSecVal;


  fToRead = "./kpk0cas0.dat";
  ifstream myfile (fToRead);
  if (myfile.is_open())
    {
      while ( myfile.good() )
        {
          int i = 0;
          getline(myfile,line);
          stringstream os(line);
	  emptyLine = 1;
          while (os >> temp) {
	    emptyLine = 0;
	    if (i==0) eVal = atof(temp.c_str()); 
	    if (i==11) xSecVal = atof(temp.c_str()); 
            i++;
          }
	  if (emptyLine == 0) h101->Fill(eVal,xSecVal);
        }
      myfile.close();
    }
  else cout << "!!!!!!!!!!!Unable to open kpk0cas0.dat!!!!!!!!!!"; 
  
  fToRead = "./kpkpcasm.dat";
  ifstream myfile2 (fToRead);
  if (myfile2.is_open())
    {
      while ( myfile2.good() )
        {
          int i = 0;
          getline(myfile2,line);
          stringstream os(line);
	  emptyLine = 1;
          while (os >> temp) {
	    emptyLine = 0;
	    if (i==0) eVal = atof(temp.c_str()); 
	    if (i==11) xSecVal = atof(temp.c_str()); 
            i++;
          }
	  if (emptyLine == 0) h102->Fill(eVal,xSecVal);
	  //if (emptyLine == 0) cout<<"eVal = "<<eVal<<" xSecVal = "<<xSecVal<<endl;
        }
      myfile2.close();
    }
  else cout << "!!!!!!!!!!!Unable to open kpkpcasm.dat!!!!!!!!!!"; 
}


////////////////////////////////////////
void setPythiaPars(TPythia6 *myPythia,int phoType){
  char *fToRead;
  char parType[80];
  if (phoType == 0) fToRead = "./pythia.dat";
  if (phoType == 1) fToRead = "./pythiaVirtual.dat";
  string line;
  stringstream os(line);
  string temp;
  ifstream myfile (fToRead);
  int varI,varJ,emptyLine,sPrint;
  double varD;
  if (myfile.is_open())
    {
      cout<<"\nPythia parameters from "<<fToRead<<"\n"<<endl;
      while ( myfile.good() )
        {
          int i = 0;
          getline(myfile,line);
          stringstream os(line);
	  emptyLine = 1;
          while (os >> temp) {
	    emptyLine = 0;
	    if (i==0){
	      sprintf(parType,temp.c_str());
	    } else {
	      if (i==1) varI = atoi(temp.c_str()); 
	      if (i==2) varJ = atoi(temp.c_str()); 
	      if (i==2) varD = atof(temp.c_str()); 
	    }
            i++;
          }
	  if (emptyLine==0){ 
	    sPrint = 0;	    
	    if (strcmp(parType,"MSEL") == 0){
	      myPythia->SetMSEL(varI); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"MSUB") == 0){ 
	      myPythia->SetMSUB(varI,varJ); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"MSTP") == 0){ 
	      myPythia->SetMSTP(varI,varJ); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"PARP") == 0){ 
	      myPythia->SetPARP(varI,varD); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"PARJ") == 0){ 
	      myPythia->SetPARJ(varI,varD); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"MSTJ") == 0){ 
	      myPythia->SetMSTJ(varI,varJ); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"MSTU") == 0){ 
	      myPythia->SetMSTU(varI,varJ); 
	      sPrint = 1;
	    }
	    if (strcmp(parType,"CKIN") == 0){ 
	      myPythia->SetCKIN(varI,varD); 
	      sPrint = 1;
	    }
	    if (sPrint == 1) {
	      if (strcmp(parType,"MSEL") == 0) cout<<parType<<"("<<varI<<")"<<endl;
	      if (strcmp(parType,"MSEL") != 0) cout<<parType<<"("<<varI<<","<<varJ<<")"<<endl;
	    }

	    //if (strcmp(parType,"CKIN") == 0) cout<<parType<<", "<<varI<<", "<<varD<<endl;
	  }
        }
      cout<<"\nFinished setting Pythia parameters from "<<fToRead<<"\n"<<endl;
      myfile.close();
    }
  else cout << "!!!!!!!!!!!Unable to open "<<fToRead<<"!!!!!!!!!!"; 
}

////////////////////////////////////////
vsDefaults_t readVsDefaults(){
  vsDefaults_t vsDefaults;
  char *fToRead;
  char parType[80];
  fToRead = "./vsDefaults.conf";
  string line;
  stringstream os(line);
  string temp;
  ifstream myfile (fToRead);
  int varI,emptyLine;
  double varD;
  char varC[80];
  if (myfile.is_open())
    {
      
      //cout<<"\nReading default parameters from vsDefaults.conf\n"<<endl;
      while ( myfile.good() )
        {
          int i = 0;
          getline(myfile,line);
          stringstream os(line);
	  emptyLine = 1;
          while (os >> temp) {
	    emptyLine = 0;
	    if (i==0){
	      sprintf(parType,temp.c_str());
	    } else {
	      if (i==1) varI = atoi(temp.c_str()); 
	      if (i==1) varD = atof(temp.c_str());
	      if (i==1) sprintf(varC,temp.c_str()); 
	    }
            i++;
          }
	  if (emptyLine==0){ 
	    if (strcmp(parType,"outFileName") == 0) sprintf(vsDefaults.outFileName,varC);
	    if (strcmp(parType,"nToGen") == 0) vsDefaults.nToGen = varI;
	    if (strcmp(parType,"coreRxn") == 0) vsDefaults.coreRxn = varI;
	    if (strcmp(parType,"rSeed") == 0) vsDefaults.rSeed = varI;
	    if (strcmp(parType,"pyEdit") == 0) vsDefaults.pyEdit = varI;
	    if (strcmp(parType,"printToScreen") == 0) vsDefaults.printToScreen = varI;
	    if (strcmp(parType,"eMin") == 0) vsDefaults.eMin = varD;
	    if (strcmp(parType,"eMax") == 0) vsDefaults.eMax = varD;
	    if (strcmp(parType,"tLength") == 0) vsDefaults.tLength = varD;
	    if (strcmp(parType,"tOffset") == 0) vsDefaults.tOffset = varD;
	    if (strcmp(parType,"beamSigma") == 0) vsDefaults.beamSigma = varD;
	    if (strcmp(parType,"vResolution") == 0) vsDefaults.vResolution = varD;
	    if (strcmp(parType,"virtualPhoton") == 0) vsDefaults.phoType = varI;
	  }
        }
      //cout<<"\nFinished reading default parameters from vsDefaults.conf\n"<<endl;
      myfile.close();
    }
  else cout << "!!!!!!!!!!!Unable to open vsDefaults.conf!!!!!!!!!!"; 
  return vsDefaults;
}

////////////////////////////////////////
void printUsage(){
  fprintf(stderr,"\nSWITCHES:\n");
  fprintf(stderr,"-h\tPrint this message\n");
  fprintf(stderr,"-n<arg>\tNumber of events to generate\n");
  fprintf(stderr,"-r<arg>\tUser defined random number seed (-r0 = no seeding by user)\n");
  fprintf(stderr,"-R<arg>\tRxn type:\n");
  fprintf(stderr,"\t\t0: background (pythia determined. Parameters in pythia.dat)\n");
  fprintf(stderr,"\t\t1: Omega- K+ K+ K0\n");
  fprintf(stderr,"\t\t2: Xi- K+ K+\n");
  fprintf(stderr,"\t\t3: Xi0 K+ K0\n");
  fprintf(stderr,"\t\t4: Xi-* K+ K+\n");
  fprintf(stderr,"\t\t5: Xi0* K+ K0\n");
  fprintf(stderr,"-x<arg>\tRemove decayed particles if equal to 1\n");
  fprintf(stderr,"-l<arg>\tMinimum incident photon energy to generate in GeV: ONLY USED FOR REAL PHOTONS\n");
  fprintf(stderr,"-u<arg>\tMaximum incident photon energy to generate in GeV: ONLY USED FOR REAL PHOTONS\n");
  fprintf(stderr,"-p<arg>\tPrint to screen if equal to 1\n");
  fprintf(stderr,"-t<arg>\tTarget length in cm\n");
  fprintf(stderr,"-O<arg>\tTarget center in cm\n");
  fprintf(stderr,"-v<arg>\tVertex resolution in cm\n");
  fprintf(stderr,"-b<arg>\tSigma of beam profile in cm\n");
  fprintf(stderr,"-o<arg>\tOutFile name\n");
  fprintf(stderr,"-e<arg>\t0: Real photon. 1: Virtual photon\n");
  
  cout<<""<<endl;
  cout<<"The above switches overide the default setting."<<endl;
  cout<<"The default settings are found in the file vsDefaults.conf"<<endl;
  cout<<"The user should modify the vsDefault.conf file to suit their taste"<<endl;

  cout<<""<<endl;
  vsDefaults_t vsDefaults = readVsDefaults(); //Read the defaults
  cout<<"The current default operation is equivalent to the command:"<<endl;
  cout<<"vsGen" 
      <<" -n"<<vsDefaults.nToGen 
      <<" -r"<<vsDefaults.rSeed 
      <<" -R"<<vsDefaults.coreRxn 
      <<" -x"<<vsDefaults.pyEdit 
      <<" -l"<<vsDefaults.eMin 
      <<" -u"<<vsDefaults.eMax 
      <<" -p"<<vsDefaults.printToScreen 
      <<" -t"<<vsDefaults.tLength 
      <<" -O"<<vsDefaults.tOffset
      <<" -v"<<vsDefaults.vResolution
      <<" -b"<<vsDefaults.beamSigma
      <<" -e"<<vsDefaults.phoType 
      <<" -o"<<vsDefaults.outFileName 
      <<"\n"<<endl;

  exit(0);
}
////////////////////////////////////////
TLorentzVector vPho(TRandom *ranGen,TLorentzVector *eScat){
  double Qsq,QsqMin,QsqMax,e1,e2,p1,p2,e2Min,e2Max,theta2Min,theta2Max;
  double y,yMin,yMax,rFlux,rFluxMax,rFluxTest,mPro,me,theta2,phi2;
  mPro = TDatabasePDG::Instance()->GetParticle("proton")->Mass();
  me = TDatabasePDG::Instance()->GetParticle("e-")->Mass();

  e1 = 11.0;  //HARD CODED INCIDENT ELECTRON ENERGY
  e2Min = 1.0; //HARD CODED e2Min
  e2Max = 4.0; //HARD CODED e2Max
  theta2Min = 1.0*TMath::DegToRad(); //HARD CODED thetaMin
  theta2Max = 5.0*TMath::DegToRad(); //HARD CODED thetaMax

  //Find min and max values of Qsq
  QsqMin = e1*e2Min*pow(theta2Min,2);
  QsqMax = e1*e2Max*pow(theta2Max,2);

  //Find min and max values of y
  yMin = (e1 - e2Max)/e1;
  yMax = (e1 - e2Min)/e1;

  //Find max value of relative flux
  rFluxMax = (1 + pow(1.0-yMin,2))/(yMin*QsqMin);

  //Kludge factor constants
  double c0 = 0.414088;
  double c1 = 0.0697581;
  double d0 = 1.08516;
  double d1 = -1.56566;
  
  //Second iteration
  double c01 = 1.34987;
  double c11 = -0.0414388;

  //Third iteration
  double d01 = 1.02547;
  double d11 = -0.577893;

  //Forth iteration
  double c02 = 1.07501;
  double c12 = -0.00929048;

  double kFac = 1.0,kFac0 = 1.0;
  //Kludge factor (kFac) to align the pythia 
  //determined virtual photon flux with 
  //this version of virtual photon flux
  //kFac0 is evaluated at yMin, QsqMin
  kFac0 = (c0 + c1*e1*yMin)*(d0 + d1*QsqMin);
  kFac0 = kFac0*(c01 + c11*e1*yMin);
  kFac0 = kFac0*(d01 + d11*QsqMin);
  kFac0 = kFac0*(c02 + c12*e1*yMin);

  rFlux = 0.0;
  rFluxTest = 2.0;

  double QsqMax2,QsqMin2;
  while (rFluxTest>rFlux) {//Monte Carlo the relative flux
    y = ranGen->Uniform(yMin,yMax);
    e2 = e1 -e1*y;
    Qsq = ranGen->Uniform(QsqMin,QsqMax);

    //Kludge factor definition
    kFac = (c0 + c1*e1*y)*(d0 + d1*Qsq);
    kFac = kFac*(c01 + c11*e1*y);
    kFac = kFac*(d01 + d11*Qsq);
    kFac = kFac*(c02 + c12*e1*y);

    QsqMax2 = e1*e2*pow(theta2Max,2);
    QsqMin2 = e1*e2*pow(theta2Min,2);
    if (Qsq<=QsqMax2 && Qsq>=QsqMin2) {
      rFlux = kFac*(1 + pow(1.0-y,2))/(y*Qsq);
      rFluxTest = ranGen->Uniform(0.0,kFac0*rFluxMax);
    }
  }
  if (rFlux > rFluxMax) cout<<"BAD rFluxMax value, rFlux = "<<rFlux<<" rFluxMax = "<<rFluxMax<<endl;
  if (rFlux > rFluxMax) cout<<"Qsq = "<<Qsq<<" QsqMax = "<<QsqMax<<endl;


  //Obtain theta2
  theta2 = sqrt(Qsq/(e1*e2));

  //Generate phi2
  phi2 = ranGen->Uniform(-TMath::Pi(),TMath::Pi()); 

  //Get the y value in the CM system
  p1 = sqrt(pow(e1,2) - pow(me,2));
  p2 = sqrt(pow(e2,2) - pow(me,2));
  //TLorentzVector target(0.0, 0.0, 0.0, mPro); 
  TLorentzVector e1vec4(0.0,0.0,p1,e1);
  TLorentzVector e2vec4(p2*sin(theta2)*cos(phi2),p2*sin(theta2)*sin(phi2),p2*cos(theta2),e2);
  TLorentzVector vPho4v = e1vec4 - e2vec4;

  *eScat = e2vec4;
  return vPho4v;
}
////////////////////////////////////////
void ytCMlimits(double *yCMlow,double *yCMhigh,
		 double *tCMlow,double *tCMhigh,
		 double *QsqLow,double *QsqHigh){
  double mPro,me,e1,e2Min,e2Max,theta2Min,theta2Max,p1;
  double e2CMmin,e2CMmax;
  mPro = TDatabasePDG::Instance()->GetParticle("proton")->Mass();
  me = TDatabasePDG::Instance()->GetParticle("e-")->Mass();

  e1 = 11.0;  //HARD CODED INCIDENT ELECTRON ENERGY
  e2Min = 1.0; //HARD CODED e2Min
  e2Max = 4.0; //HARD CODED e2Max
  theta2Min = 1.0*TMath::DegToRad(); //HARD CODED thetaMin
  theta2Max = 5.0*TMath::DegToRad(); //HARD CODED thetaMax

  double QsqMin,QsqMax;
  QsqMin = e1*e2Min*pow(theta2Min,2);
  QsqMax = e1*e2Max*pow(theta2Max,2);

  p1 = sqrt(pow(e1,2) - pow(me,2));
  TLorentzVector target(0.0, 0.0, 0.0, mPro); 
  TLorentzVector e1vec4(0.0,0.0,p1,e1);
  TLorentzVector W = e1vec4 + target;
  TLorentzVector e1vec4CM = e1vec4;
  e1vec4CM.Boost(-W.BoostVector());

  double gamma = W.E()/W.M();
  double beta = W.P()/W.E();
  double tanThetaMinPrime = sin(theta2Min)/(gamma*(cos(theta2Min) - beta));
  double tanThetaMaxPrime = sin(theta2Max)/(gamma*(cos(theta2Max) - beta));

  double thetaMinPrime = TMath::ATan(tanThetaMinPrime);
  double thetaMaxPrime = TMath::ATan(tanThetaMaxPrime);

  e2CMmin = QsqMin/(2.0*e1vec4CM.E()*(1 - cos(thetaMinPrime)));
  e2CMmax = QsqMax/(2.0*e1vec4CM.E()*(1 - cos(thetaMaxPrime)));
  double yCMl = (e1vec4CM.E() - e2CMmax)/e1vec4CM.E();
  double yCMh = (e1vec4CM.E() - e2CMmin)/e1vec4CM.E();

  *yCMlow = yCMl;
  *yCMhigh = yCMh;
  *tCMlow = thetaMinPrime;
  *tCMhigh = thetaMaxPrime;
  *QsqLow = QsqMin;
  *QsqHigh = QsqMax;

}
