/*

OCT 23 2011.  took this strait from g11 ana and took out the ps beam corrections.  i FINALLY got the lable files to match.  also added all the angles
 for ps removal see //jb. for angle addtion see //jb v06

so the number of branches at this point should be 117 - 4ps + 8angles = 121 branches which is what im seeing in the lable and the view file out puts

*/

#include <iostream>
#include <fstream>
#include <plib.h>

extern "C" {
  
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <ntypes.h>
#include <bostypes.h>
#include <clas_cern.h>
#include <particleType.h>
#include <kinematics.h>
#include <pdgutil.h>
#include <pid.h>
#include <scalers.h>
#include <utility.h>
#include <printBOS.h>
#include <ec.h>
#include <PartUtil.h>
#include <dataIO.h>
#include <itape.h>
#include <vertex.h>
#include <sc.h>

}

// You must change this to have the correct header file for ROOT
#include <Vec.h>
#include <lorentz.h>
#include <pputil.h>
#include <clasEvent.h>


/*bitwise drop flags*/
#define DROP_RAW BIT(0)
#define DROP_DC0 BIT(1)
#define DROP_DC1 BIT(2)
#define DROP_HBLA BIT(3)
#define DROP_TBLA BIT(4)
#define DROP_HBTB BIT(5)
#define DROP_SC BIT(6)
#define DROP_EC BIT(7)
#define DROP_HBID BIT(8)
#define DROP_CL01 BIT(9)
#define DROP_SEB BIT(10)
#define DROP_TBID BIT(11)
#define DROP_HDPL BIT(12)
#define DROP_LAC BIT(13)
#define DROP_CC BIT(14)
#define DROP_ST BIT(15)
#define DROP_DHCL BIT(16)
#define DROP_TAGR BIT(17)
#define CC_BANKS "CCRCCC01"
#define SEB_BANKS "HEVTEVNTDCPBSCPBCCPBUNUSEVHBTRKSSTPBTGPBLCPB"
#define TAGGER_BANKS "TAGRTAGIPSO "
#define SC_BANKS "SC1 SCR SCRC"
#define EC_BANKS "EC01ECHBECPIECPCECPBEC  EC1 "
#define ST_BANKS "ST1 STR "
#define REGION1_BANKS "RGLK"

#define BUFSIZE 200000

extern "C" {
void bnames_(int *);
int SetVerbose(int);
extern void photonenergy_(double *b0, int *run, double *b1, double *b2);
}

int StartRun(int);
int ProcessEvent(clasEvent &event,int, int);
int DropList(int DropFlag);
void PrintUsage(char *processName);
int fillNtuples(clasEvent &event);
tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID);

int CurrentRun = 0;
int setRun = 0;
int CurrentEvent = 0;
int partbank0 = 1;
int partbank = 1;
int datatype=1;
int corr=0;

ofstream output;





int StartRun(int runNo)
{  
  int static CurrentRun = -1;
  if (CurrentRun != runNo) {
     vertex_brun(runNo);
     CurrentRun = runNo;
  }
  return 0;
}


int DropList(int DropFlag)
{
  /* Mask off banks according to DropFlag*/

  if (DropFlag & DROP_RAW) bankList(&bcs_, "E-", "R");  
  if (DropFlag & DROP_DC0) bankList(&bcs_, "E-", "DC0 ");
  if (DropFlag & DROP_DC1) bankList(&bcs_, "E-", "DC1 ");
  if (DropFlag & DROP_HBLA) bankList(&bcs_, "E-", "HBLA");
  if (DropFlag & DROP_TBLA) bankList(&bcs_, "E-", "TBLA");
  if (DropFlag & DROP_HBTB) bankList(&bcs_, "E-", "HBTB");
  if (DropFlag & DROP_SC) bankList(&bcs_, "E-", SC_BANKS);
  if (DropFlag & DROP_EC) bankList(&bcs_, "E-", EC_BANKS);
  if (DropFlag & DROP_HBID) bankList(&bcs_, "E-", "HBID");
  if (DropFlag & DROP_CL01) bankList(&bcs_, "E-", "CL01");
  if (DropFlag & DROP_SEB) bankList(&bcs_, "E-", SEB_BANKS);
  if (DropFlag & DROP_TBID) bankList(&bcs_, "E-", "TBIDPARTTBERTBTR");
  if (DropFlag & DROP_HDPL) bankList(&bcs_, "E-", "HDPL");
  if (DropFlag & DROP_LAC) bankList(&bcs_, "E-", "EC1R");
  if (DropFlag & DROP_CC) bankList(&bcs_, "E-", CC_BANKS);
  if (DropFlag & DROP_ST) bankList(&bcs_, "E-", ST_BANKS);
  if (DropFlag & DROP_DHCL) bankList(&bcs_, "E-", "DHCL");
  if (DropFlag & DROP_TAGR) bankList(&bcs_, "E-", TAGGER_BANKS);
 
  return(0);
}


void PrintUsage(char *processName)
{
  cerr << processName << " <options> <filename>\n";
  cerr << "\toptions are:\n";
  cerr << "\t-t#\ttrigger mask.\n";
  cerr << "\t-D#\tDrop flag.\n";
  cerr << "\t-o<filename>\tBOS output file.\n";
  cerr << "\t-M#\tprocess maximum # of events.\n";
  cerr << "\t-R#\tset run number (mc only)\n";
  cerr << "\t-a<filename>\tascii output file for making Ntuples(default output.view).\n";
  cerr << "\t-X#\tdata type(x=1, real data; x=0, mc data\n";
  cerr << "\t-C#\tperform eloss and momentum correction(C=1, perform correction; C=0, no correction\n";
  cerr << "\t-F#\tIFLAG valued for eloss package(default 1)\n";
  cerr << "\t\tIFLAG=0 - empty target. For IFLAG=0 no energy losses in target.\n";
  cerr << "\t\tIFLAG=1 - LH2 target\n";
  cerr << "\t\tIFLAG=2 - LD2 target\n";
  cerr << "\t\tIFLAG=3 - L3He target\n";
  cerr << "\t-i\tquiet mode (no counter).\n";
  cerr << "\t-h\tprint the above" << endl;
}

void printLabels()
{

  int nlab = 0;

 cout << ++nlab << "\trun number{run}"<<endl;
 cout << ++nlab << "\tevt number{evt}"<<endl;
 cout << ++nlab << "\tsc Vtime{scv}"<<endl;
 cout << ++nlab << "\tst Vtime{stv}"<<endl;
 cout << ++nlab << "\tvtim should be same as sc Vtime{vtime}"<<endl;
 cout << ++nlab << "\tmvrt x{vx}"<<endl;
 cout << ++nlab << "\tmvrt y{vy}"<<endl;
 cout << ++nlab << "\tmvrt z{vz}"<<endl;
 cout << ++nlab << "\tnumber of K+{nkp}"<<endl;
 cout << ++nlab << "\tnumber of pi-{npim}"<<endl;
 cout << ++nlab << "\tnumber of K-{nkm}"<<endl;
 cout << ++nlab << "\tnumber of proton{np}"<<endl;
 cout << ++nlab << "\tnumber of pi+{npip}"<<endl;
 cout << ++nlab << "\t{kfit probability, confidence level}{cl}"<<endl;
 cout << ++nlab << "\t{kfit chisq}{chi2}"<<endl;
 cout << ++nlab << "\t{kfit beam}{bfit}"<<endl;
 cout << ++nlab << "\t{kfit mm}{fitmmkkpim}"<<endl;
 cout << ++nlab << "\t{kfit mmkpkp}{fitmmkpkp}"<<endl;
 cout << ++nlab << "\t{kfit mmkp1}{fitmmkp1}"<<endl;
 cout << ++nlab << "\t{kfit mmkp2}{fitmmkp2}"<<endl;
 cout << ++nlab << "\t{kfit mmpim}{fitmmpim}"<<endl;
 cout << ++nlab << "\t{kfit m(kp1+pim)}{fitmkp1pim}"<<endl;
 cout << ++nlab << "\t{kfit m(kp2+pim)}{fitmkp2pim}"<<endl;
 cout << ++nlab << "\t(mass of proton pi-){mppim}"<<endl;
 cout << ++nlab << "\t{tofbetakp1}"<<endl;
 cout << ++nlab << "\t{tofbetakp2}"<<endl;
 cout << ++nlab << "\t{tofbetapim}"<<endl;
 cout << ++nlab << "\t{betakp1}"<<endl;
 cout << ++nlab << "\t{betakp2}"<<endl;
 cout << ++nlab << "\t{betapim}"<<endl;
 cout << ++nlab << "\t{sctkp1}"<<endl;
 cout << ++nlab << "\t{sctkp2}"<<endl;
 cout << ++nlab << "\t{sctpim}"<<endl;
 cout << ++nlab << "\t{sclkp1}"<<endl;
 cout << ++nlab << "\t{sclkp2}"<<endl;
 cout << ++nlab << "\t{sclpim}"<<endl;
 cout << ++nlab << "\t{tofmasskp1}"<<endl;
 cout << ++nlab << "\t{tofmasskp2}"<<endl;
 cout << ++nlab << "\t{tofmasspim}"<<endl;
 cout << ++nlab << "\t{stvkp1}"<<endl;
 cout << ++nlab << "\t{stvkp2}"<<endl;
 cout << ++nlab << "\t{stvpim}"<<endl;
 cout << ++nlab << "\t(distance between K+1, pi-){dkp1pim}"<<endl;
 cout << ++nlab << "\t(distance between K+2, pi-){dkp2pim}"<<endl;
 cout << ++nlab << "\t(distance between K+1, K+2){dkpkp}"<<endl;
 cout << ++nlab << "\tbeam energy{beam}"<<endl;
 //JB\\cout << ++nlab << "\tbeam energy from ps tagger correction{psbeam}"<<endl;
 cout << ++nlab << "\tsqrt(s){w}"<<endl;
 
 cout << ++nlab << "\tt energy transfer(kp1+kp2 - beam){tkpkp}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp1+kp2+pim - beam){tkpkppim}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp1+pim - beam){tkp1pim}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp2+pim - beam){tkp2pim}"<<endl;
  cout << ++nlab << "\tmissing mass square of (K+K+) {mm2kpkp}"<<endl;
  //JB\\  cout << ++nlab << "\tmissing mass square of using ps beam (K+K+) {psmm2kpkp}"<<endl;
  cout << ++nlab << "\tmissing mass square of (kp1){mm2kp1}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp2){mm2kp2}"<<endl;
  cout << ++nlab << "\tmissing mass square of (kp1+pim){mm2kp1pim}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp2+pim){mm2kp2pim}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp+kp+pim){mm2kpkppim}"<<endl;
 //JB\\ cout << ++nlab << "\tmissing mass square of (kp+kp+pim)using ps beam{psmm2kpkppim}"<<endl;

 //invariant masses
 cout << ++nlab << "\tmass of (k+ k+) {mkpkp}"<<endl;
 cout << ++nlab << "\tmass of (k+1 pi-) {mkp1pim}"<<endl;
 cout << ++nlab << "\tmass of (k+2 pi-) {mkp2pim}"<<endl;

 //missing masses
  cout << ++nlab << "\tmass of (mmkp1){mmkp1}"<<endl;
  cout << ++nlab << "\tmass of (mmkp2) {mmkp2}"<<endl;
  cout << ++nlab << "\tmass of (mmkpkp) {mmkpkp}"<<endl;

     //momentums
  cout << ++nlab << "\tkp1 momentum{pkp1}"<<endl;
  cout << ++nlab << "\tkp2 momentum{pkp2}"<<endl;
  cout << ++nlab << "\tkp2 momentum{ppim}"<<endl;
  cout << ++nlab << "\tmiss x{missx}"<<endl;
  cout << ++nlab << "\tmiss y{missy}"<<endl;
  cout << ++nlab << "\tmiss z{missz}"<<endl;
  cout << ++nlab << "\tmiss momentum{missp}"<<endl; 
  cout << ++nlab << "\tmiss momentum{misse}"<<endl; 

 
    cout << ++nlab << "\tt prime{tp}"<<endl;
   //constrained masses
     cout << ++nlab << "\tMass(Cascade, K+1){mcaskp1}"<<endl;
    cout << ++nlab << "\tMass(Cascade, K+2){mcaskp2}"<<endl;
    cout << ++nlab << "\tMass(Cascade, pim){mcaspim}"<<endl;
    cout << ++nlab << "\tMass(lambda, pim){mlampim}"<<endl;
    //JB\\  cout << ++nlab << "\tMass(Cascade, pim) ps method{mpscaspim}"<<endl;
    cout << ++nlab << "\tMass(Cascade, pim) fix beam method{mfixcaspim}"<<endl;
    cout << ++nlab << "\tbeam energy fix beam method{fixbeam}"<<endl;

    cout << ++nlab << "\tMass(Cascadem, kp1){mcasmkp1}"<<endl;
    cout << ++nlab << "\tMass(Cascadem, kp2){mcasmkp2}"<<endl;
    cout << ++nlab << "\tMass(Cascadem, kp1)using fixbeam{mfixcasmkp1}"<<endl;
    cout << ++nlab << "\tMass(Cascadem, kp2)usign fixbeam{mfixcasmkp2}"<<endl;
     cout << ++nlab << "\tbeam energy fix beam method{fixbeam2}"<<endl;
    //replace k+ with pi+ and get the masses
    cout << ++nlab << "\tMissing Mass(3pi){mm3pi}"<<endl;
    cout << ++nlab << "\tMissing Mass(K+1, pip, pim){mmkp1pippim}"<<endl;
    cout << ++nlab << "\tMissing Mass(K+2, pip, pim){mmkp2pippim}"<<endl;
    cout << ++nlab << "\tMass(K+1, pip, pim){mkp1pippim}"<<endl;
    cout << ++nlab << "\tMass(K+2, pip, pim){mkp2pippim}"<<endl;
    cout << ++nlab << "\tMass(pip1, pim){mpip1pim}"<<endl;
    cout << ++nlab << "\tMass(pip2, pim){mpip2pim}"<<endl;
    cout << ++nlab << "\tMass(pip1, pip2, pim){m3pi}"<<endl;
   //lab angles
  cout << ++nlab << "\t(K+) lab angle{kp1labtheta}"<<endl;
  cout << ++nlab << "\t (K+) lab angle{kp1labphi}"<<endl;
cout << ++nlab << "\t(K+2) lab angle{kp2labtheta}"<<endl;
  cout << ++nlab << "\t (K+2) lab angle{kp2labphi}"<<endl;
   cout << ++nlab << "\t(pi) lab angle{pilabtheta}"<<endl;
  cout << ++nlab << "\t(pi) lab angle{pilabphi}"<<endl;
   cout << ++nlab << "\t(X) lab angle{Xlabtheta}"<<endl;
  cout << ++nlab << "\t(X) lab angle{Xlabphi}"<<endl;
 
  //cm angles
  cout << ++nlab << "\t(K+) cm angle{kp1cmtheta}"<<endl;
  cout << ++nlab << "\t (K+) cm angle{kp1cmphi}"<<endl;
 cout << ++nlab << "\t(K+2) cm angle{kp2cmtheta}"<<endl;
  cout << ++nlab << "\t (K+2) cm angle{kp2cmphi}"<<endl;
  cout << ++nlab << "\t(pi) cm angle{picmtheta}"<<endl;
  cout << ++nlab << "\t(pi) cm angle{picmphi}"<<endl;
  cout << ++nlab << "\t(X) cm angle{Xcmtheta}"<<endl;
  cout << ++nlab << "\t(X) cm angle{Xcmphi}"<<endl;
  //Y1 rest frame angles
  cout << ++nlab << "\t(Kp2) (kp2+xm) rest angle{kp2htheta}"<<endl;
  cout << ++nlab << "\t(Kp2)(kp2+xm) rest angle{kp2hphi}"<<endl;
  //Y2 rest frame angles
  cout << ++nlab << "\t(Kp1) (kp1+xm) rest angle{kp1htheta}"<<endl;
  cout << ++nlab << "\t(Kp1) (kp1+xm) rest angle{kp1hphi}"<<endl;
 //X rest frame angles
  cout << ++nlab << "\t(pi) Xi rest angle{pihtheta}"<<endl;
  cout << ++nlab << "\t(pi) Xi rest angle{pihphi}"<<endl;


//jb v06
  cout << ++nlab << "\t(pi) pi norm angle{PIangle_ANA}"<<endl; 
  cout << ++nlab << "\t(pi) pi x angle{PIanglex_ANA}"<<endl;
  cout << ++nlab << "\t(pi) pi y angle{PIangley_ANA}"<<endl;
  cout << ++nlab << "\t(pi) pi z angle{PIanglez_ANA}"<<endl;
  cout << ++nlab << "\t(pi) li norm angle{LAMBangle_ANA}"<<endl;
  cout << ++nlab << "\t(pi) l x angle{LAMBanglex_ANA}"<<endl;
  cout << ++nlab << "\t(pi) l y angle{LAMBangley_ANA}"<<endl;
  cout << ++nlab << "\t(pi) l z angle{LAMBanglez_ANA}"<<endl;

 
  }



// ------------------------------------------------
// ------------------ Main program ----------------
// ---------- To be modified to fit need ----------
// ------------------------------------------------

int main(int argc,char **argv)
{

  int max = 0;
  int verbose = 0;
  int ret = 1;
  int Nevents = 0;
  int Nproc = 0;
  int Nwrite = 0;
  char *argptr;
  int Dispatch = 0;
  unsigned int triggerMask = 0;
  int writeFlag = 0;
  int IFLAG=1;

  
  // bos stuff
  char *BOSoutfile = NULL;
  char *asciioutfile = "output.view";
  int OutputUnitNo = 9;
  int MaxBanks = 1000; 
  char  out[300];
  char Elist[5 * MaxBanks];

  int DropFlag = 0x0;

  for (int i = 1; i < argc; i++) {
    argptr = argv[i];
    if (*argptr == '-') {
      argptr++;
      switch (*argptr) {
	
      case 't':
	triggerMask = strtoul(++argptr,NULL,0);
	break;
      case 'X':
	datatype = atoi(++argptr);
	break;
      case 'C':
	corr = atoi(++argptr);
	break;
      case 'a':
	
	if(*(++argptr))
	  asciioutfile = argptr;
	break;
      case 'F':
	IFLAG = atoi(++argptr);
	break;

      case 'D':
	DropFlag = strtoul(++argptr,NULL,0);
	break;

      case 'v':
	verbose = 1;
	break;
      
      case 'o':
	if(*(++argptr))
	  BOSoutfile = argptr;
	if(OutputUnitNo){
	  cerr << "Output file: " << BOSoutfile << endl;
	  unlink(BOSoutfile);
	  sprintf(out, "OPEN BOSOUTPUT UNIT=9 FILE=\"%s\" WRITE  STATUS=NEW RECL=3600", BOSoutfile);
	  if (!fparm_c(out)) {
	    cerr << argv[0] << ": Unable to open file: " << out << " " <<  strerror(errno) << endl;	 
	    exit(1);
	  }
	}
	break;

      case 'M':
	max = atoi(++argptr);
	break;
      case 'R':
	setRun = atoi(++argptr);
	break;
          
          
      case 'h':
	PrintUsage(argv[0]);
	exit(0);
	break;

      case 'p':
	partbank0 = atoi(++argptr);
	break;

      case 'L':
	printLabels();
	exit(0);
	break;

      default:
	cerr << "Unrecognized argument: " << argptr << endl;;
	break;
      }
    }
  }
  cerr << " output ascii file is :" << asciioutfile <<endl;
  output.open(asciioutfile, ios::out);

  cerr << "Parsing bank: " << partbank0 << endl;

  // Initialize BOS
  bnames_(&MaxBanks);
  initbos();
  configure_banks(stderr,0);

  for (int i = 1; i < argc; ++i) {
    argptr = argv[i];
    // process all arguments on command line.
    if (*argptr != '-') {
      // we have a file to process
      clasEvent event(argptr, &bcs_, partbank0, 0);
      
      cerr << "initialize:\t" << argptr << endl;
      
      Dispatch = isDispatcher(argptr);
      if (event.status()) {
	ret = 1;
	while ((max ? Nevents < max : 1) && ret) {
	  // process every event in the file
	  ret = event.read(partbank0);
	  if (ret == DISIO_DATA) {
	    
	    Nevents++;
                  
	    if (event.status()) {
	      if (triggerMask ? (triggerMask & event.trig()) : 1) {
		int runno = event.run();     
		//int runno = 19660;
		if(setRun){
		  runno = setRun;
		}
		ConfigEvent(runno,0); 
		/* Initialize the TOF geometry.  This is needed regardless of whether you remake the SC reconstruction banks or not.  However, for the regeneration case, this is done in ConfigEvent. */
		StartRun(runno);
		writeFlag = ProcessEvent(event,verbose, IFLAG) ;
		if (BOSoutfile && writeFlag) {
		  if (DropFlag) {
		    DropList(DropFlag);
		  }
		  putBOS(&bcs_,9,"E");
		  Nwrite++;
		}
		dropAllBanks(&bcs_,"E");
		cleanBanks(&bcs_);
		Nproc++;
	      }
	    }
	  }
	  else if (ret == DISIO_COMMAND) {
 	    cerr << "Message from Giant Head: " << getBuffer() << endl;;
      	  }
	  
	}
	cerr << "\nTotal number of itape records read:\t" << Nevents << endl;
	cerr << "Total number of events processed:\t" << Nproc << endl;
	cerr << "\tTotal number of records written:\t" << Nwrite << endl;
      }
      else {
	cerr << "Unable to open " << argptr << endl;
      }
    }
  }
  
  if (Dispatch) {
    disIO_command("FINISHED");
  }
  
  cerr << "\nTotal number of itape records:\t" << Nevents << endl;

  if (BOSoutfile) {
    putBOS(&bcs_,9, "0");
    sprintf(out, "CLOSE BOSOUTPUT UNIT=9");
    fparm_c(out);  
  }
   

  return (0);
}


// ------------------------------------------------
// ---------------- ProcessEvent ------------------
// ------------ Make all analysis here ------------
// ------------------------------------------------

int ProcessEvent(clasEvent &my_event,int verbose, int IFLAG)
{
  int nReturnValue = 0;
  //static int nCount = 0;
  
  if (my_event.N(KPlus)!=2 || my_event.N(PiMinus)!=1 ){
    return (0);
  }
  
  
  // if there Pi+ pi+ K- in Part banks, get four vectors of these particles
  // and set beam and target four vectors

  fourVec kp1,kp2, kp0, pim;
  fourVec pip1, pip2;
  fourVec beam,psbeam,fixbeam,target(PROTON_MASS,threeVec(0.0,0.0,0.0));
  double beamp = -100.0, psbeamp = -100.0, mmbeamp = -100.0, fixbeamp = -100.0;
  double newbeam1 = -100.0;
  double newbeam2 = -100.0;
  double CASCADE0_MASS = 1.31483;
  double CASCADE_MASS = 1.32131;
  clasTAGR_t *TAGR = (clasTAGR_t *)getBank(&bcs_,"TAGR"); 
  clasBID_t *TBID  =  (clasBID_t *)getBank(&bcs_,"TBID"); 
  int runno=0;
  int evtno=0;
  double tMin;
  tagr_t *tagr = my_get_photon_tagr(TAGR, TBID);
  int eid = 0;
   if(tagr){
     eid = tagr->e_id;
     beamp = tagr->erg;
   }
    

 runno=my_event.run();
 evtno=my_event.event();
  if(corr){
  //do eloss and mommentum correction
    my_event.eLoss("g11a", IFLAG);
    if(datatype) {
      //my_event.momentumCorrection();
      psbeamp=my_event.lgTAGRcorrection(beamp, eid);
      if(runno>44109){
	photonenergy_(&beamp,&runno,&newbeam1,&newbeam2);
	psbeamp = newbeam1*0.99824;
	mmbeamp = newbeam2*0.99944;
      }
      else if(runno>43489){
	photonenergy_(&beamp,&runno,&newbeam1,&newbeam2);
	psbeamp = newbeam1*1.0006;
	mmbeamp = newbeam2*1.0018;
      }
    }
    else {
      psbeamp=beamp;
      mmbeamp=beamp;
    }
    my_event.Pcor(); 
  }
  beam.set(mmbeamp,threeVec(0.0,0.0,mmbeamp));
  psbeam.set(psbeamp,threeVec(0.0,0.0,psbeamp));
  kp1=my_event.cp(KPlus,1).p();
  kp2=my_event.cp(KPlus,2).p();
  pim=my_event.cp(PiMinus,1).p();
 
 //Now check with kinematic fitting
  clasKineFit fit;
  clasParticle l[3]; 
  std::list<clasParticle> cpIn; 
  std::list<clasParticle> cpOut;
  std::list<clasParticle>::iterator pin; 
  std::list<clasParticle>::iterator pout;
  std::vector<double> pulls;
  std::vector<double>::iterator pit;
  int x[10];
  
  l[0] = my_event.cp(KPlus,1);
  l[1] = my_event.cp(KPlus,2);
  l[2] = my_event.cp(PiMinus,1);

  fit = mwKfit(mmbeamp,l,3,CASCADE0_MASS,x,0.0);
  float cl=fit.prob();  
  cpIn = fit.cpIn();
  cpOut = fit.cpOut();
  pin = cpIn.begin();
  pout = cpOut.begin();
  fourVec kp1Out;
  fourVec kp2Out;
  fourVec kp0Out;
  fourVec pimOut;
  float beampOut=fit.beamEnergy();
  fourVec beamOut;
  beamOut.set(beampOut,threeVec(0.0,0.0,beampOut));

  int ict = 0;

  while (pout != cpOut.end()) {
    switch (ict) {
    case 0:
      kp1Out = pout->p();
      break;
    case 1:
      kp2Out = pout->p();
      break;
    case 2:
      pimOut =  pout->p();
      break;

      
    }
    ict++;
    pout++;
  }
   if(kp1Out.r()<kp2Out.r()){
    kp0Out = kp1Out;
    kp1Out = kp2Out;
    kp2Out = kp0Out;
  }

  //end of kinematic fitting
  //if kp1 is slower, reverse the order 

  if(kp1.r()<kp2.r()){
    kp0 = kp1;
    kp1 = kp2;
    kp2 = kp0;
  }
  //check the Vtime first to clean up the data
  float scv=my_event.scVtime();
  float stv=my_event.stVtime();
  threeVec Vert = my_event.V();

  int targZ=0, targXY=0, st=0;
  if(abs(Vert.z()+10)<=20) targZ=1;
  if((Vert.x()*Vert.x()+Vert.y()*Vert.y())<=4) targXY=1;
  if(abs(my_event.scVtime()-my_event.stVtime())<=3) st=1;

  float mm2kpkp=(beam + target - kp2 - kp1).lenSq();
  if(st){
  nReturnValue = 1;
  output<<runno<<" "<<evtno<<" ";
  output<<my_event.scVtime()<<" "<<my_event.stVtime()<<" "<<my_event.vtime()<<" ";
  output<<Vert.x()<<" "<<Vert.y()<<" "<<Vert.z()<<" ";
  output<<my_event.N(KPlus)<<" "<<my_event.N(PiMinus)<<" "<<my_event.N(KMinus)<<" "<<my_event.N(Proton)<<" "<<my_event.N(PiPlus)<<" ";
  output << fit.prob() << " "<<fit.chisq()<<" ";
  output<<fit.beamEnergy()<<" "<<~(beamOut+target-kp1Out-kp2Out-pimOut)<<" ";
  output<<~(beamOut+target-kp1Out-kp2Out)<<" ";
  output<<~(beamOut+target-kp1Out)<<" "<<~(beamOut+target-kp2Out)<<" "<<~(beamOut+target-pimOut)<<" "<<~(pimOut+kp1Out)<<" "<<~(pimOut+kp2Out)<<" ";
  double mppim = -10;
  fourVec proton;
  if(my_event.N(Proton)){
    proton = my_event.cp(Proton,1).p();
    mppim = ~(proton + pim);
  }
  output<<mppim<<" ";

  clasParticle cpkp1, cpkp2, cppim;
  if(kp1.r()>kp2.r()){
    
    //also check the beta's
    output<<my_event.cp(KPlus, 1).beta()<<" ";
    output<<my_event.cp(KPlus, 2).beta()<<" ";
    output<<my_event.cp(PiMinus, 1).beta()<<" ";
    output<<my_event.cp(KPlus, 1).Beta()<<" ";
    output<<my_event.cp(KPlus, 2).Beta()<<" ";
    output<<my_event.cp(PiMinus, 1).Beta()<<" ";
  //also check the sctime and scpath
  output<<my_event.cp(KPlus, 1).sc_time()<<" ";
  output<<my_event.cp(KPlus, 2).sc_time()<<" ";
  output<<my_event.cp(PiMinus, 1).sc_time()<<" ";
  output<<my_event.cp(KPlus, 1).scPathLen()<<" ";
  output<<my_event.cp(KPlus, 2).scPathLen()<<" ";
  output<<my_event.cp(PiMinus, 1).scPathLen()<<" ";
    //check the TOF mass
    output<<my_event.cp(KPlus, 1).mass()<<" ";
    output<<my_event.cp(KPlus, 2).mass()<<" " ;
    output<<my_event.cp(PiMinus, 1).mass()<<" ";
      //check st_vtime for different particles
    output<<my_event.cp(KPlus, 1).stVtime()<<" ";
    output<<my_event.cp(KPlus, 2).stVtime()<<" "; 
    output<<my_event.cp(PiMinus, 1).stVtime()<<" ";
    cpkp1 = my_event.cp(KPlus, 1);
    cpkp2 = my_event.cp(KPlus, 2);
  }

  else {
  //also check the beta's
    output<<my_event.cp(KPlus, 2).beta()<<" ";
    output<<my_event.cp(KPlus, 1).beta()<<" ";
    //check the TOF mass
    output<<my_event.cp(KPlus, 2).mass()<<" ";
    output<<my_event.cp(KPlus, 1).mass()<<" " ;
      //check st_vtime for different particles
    output<<my_event.cp(KPlus, 2).stVtime()<<" ";
    output<<my_event.cp(KPlus, 1).stVtime()<<" "; 
    cpkp1 = my_event.cp(KPlus, 2);
    cpkp2 = my_event.cp(KPlus, 1);
   
  }
  cppim = my_event.cp(PiMinus, 1);
  double vkp1pim=-1000, vkp2pim=-1000, vkpkp=-1000;
  
 
  vkp1pim = my_event.vert2Separation(cpkp1, cppim);
  vkp2pim = my_event.vert2Separation(cpkp2, cppim);
  vkpkp = my_event.vert2Separation(cpkp1, cpkp2);
    
  
    //check the vertex separation
  output<<vkp1pim<<" "<<vkp2pim<<" "<<vkpkp<<" ";

//now plot the masses
//jb  output<<mmbeamp<<" "<<psbeamp<<" "<<~(beam+target)<<" "<<(kp1+kp2-beam).lenSq()<<" ";
  output<<mmbeamp<<" "<<~(beam+target)<<" "<<(kp1+kp2-beam).lenSq()<<" ";    //jb
  output<<(kp1+kp2+pim-beam).lenSq()<<" ";
  output<<(kp1+pim-beam).lenSq()<<" "<<(kp2+pim-beam).lenSq()<<" ";
  output << (beam + target - kp1 - kp2).lenSq() << " ";
//jb  output << (psbeam + target - kp1 - kp2).lenSq() << " ";
  output << (beam + target - kp1).lenSq() << " ";
  output << (beam + target - kp2).lenSq() << " ";  
  output << (beam + target - kp1-pim).lenSq() << " ";
  output << (beam + target - kp2-pim).lenSq() << " ";  
  output << (beam + target - kp1 - kp2-pim).lenSq() << " ";  
//jb output << (psbeam + target - kp1 - kp2-pim).lenSq() << " ";
   
  //invariant masses
  output << ~(kp2 + kp1) << " "<<~(kp1+pim)<<" "<<~(kp2+pim)<<" ";

  //missing masses
  output << ~(beam+target-kp1) << " ";
  output << ~(beam+target-kp2) << " "<<~(beam+target-kp1-kp2)<<" ";
  //check the momentums
  output <<kp1.r()<<" "<<kp2.r()<<" "<<pim.r()<<" ";
  output << (beam + target - kp1 - kp2 - pim).x() << " ";
  output << (beam + target - kp1 - kp2 - pim).y() << " ";
  output << (beam + target - kp1 - kp2 - pim).z() << " ";
  output << (beam + target - kp1 - kp2 - pim).r() << " ";
  //check the missing energy
  output << (beam + target - kp1 - kp2 - pim).t() << " ";
  

 
    //get the t transfer from proton
  tMin = tmin(beamp,0.0,PROTON_MASS,~(kp1 + kp2 + pim),CASCADE0_MASS);
  output << -((kp1 + kp2 + pim - beam).lenSq() - tMin) << " ";
   
  //constrain cascade and replot the k+ cascade masses
  fourVec miss=beam + target - kp1 - kp2 - pim;
  fourVec kkpi = kp1 + kp2 + pim;
  fourVec miss2=beam + target - kp1 - kp2;
  fourVec kk = kp1 + kp2;
  fixbeamp = (CASCADE0_MASS*CASCADE0_MASS - kkpi.lenSq()  - PROTON_MASS*PROTON_MASS + 2*PROTON_MASS*kkpi.t())/(2*(PROTON_MASS+kkpi.z()-kkpi.t()));
  fixbeam.set(fixbeamp,threeVec(0.0,0.0,fixbeamp));
  double fixbeamp2 = (CASCADE_MASS*CASCADE_MASS - kk.lenSq()  - PROTON_MASS*PROTON_MASS + 2*PROTON_MASS*kk.t())/(2*(PROTON_MASS+kk.z()-kk.t()));
  fourVec fixbeam2;
  fixbeam2.set(fixbeamp2,threeVec(0.0,0.0,fixbeamp2));
  fourVec psmiss=psbeam + target - kp1 - kp2 - pim;
  double Ecascade = sqrt(CASCADE0_MASS*CASCADE0_MASS + miss.r()*miss.r());
  double psEcascade = sqrt(CASCADE0_MASS*CASCADE0_MASS + psmiss.r()*psmiss.r());
  double Elambda = sqrt(LAMBDA_MASS*LAMBDA_MASS + miss.r()*miss.r());
  fourVec cascade, lambda, pscascade;
  double Ecascadem = sqrt(CASCADE_MASS*CASCADE_MASS + miss2.r()*miss2.r());
  fourVec cascadem;
  cascade.set(Ecascade, threeVec(miss.x(), miss.y(), miss.z()));
  cascadem.set(Ecascadem, threeVec(miss2.x(), miss2.y(), miss2.z()));
  pscascade.set(psEcascade, threeVec(psmiss.x(), psmiss.y(), psmiss.z()));
  lambda.set(Elambda, threeVec(miss.x(), miss.y(), miss.z()));
  //replot the constrained masses
  //jb  output<<~(cascade + kp1) <<" "<<~(cascade + kp2)<<" "<<~(cascade + pim)<<" "<<~(lambda+pim)<<" "<<~(pscascade + pim)<<" "<<~(fixbeam+target-kp1-kp2)<<" "<<fixbeamp<<" ";
  output<<~(cascade + kp1) <<" "<<~(cascade + kp2)<<" "<<~(cascade + pim)<<" "<<~(lambda+pim)<<" "<<~(fixbeam+target-kp1-kp2)<<" "<<fixbeamp<<" ";  //jb
  output<<~(cascadem + kp1) <<" "<<~(cascadem + kp2)<<" "<<~(fixbeam2+target-kp1)<<" "<<~(fixbeam2+target-kp2)<<" "<<fixbeamp2<<" ";
    //replace k+ with pi+ and replot the k+ related masses
  double Epip1 = sqrt(PI_CHARGED_MASS*PI_CHARGED_MASS+kp1.r()*kp1.r());
  pip1.set(Epip1, threeVec(kp1.x(), kp1.y(), kp1.z()));
  double Epip2 = sqrt(PI_CHARGED_MASS*PI_CHARGED_MASS+kp2.r()*kp2.r());
  pip2.set(Epip2, threeVec(kp2.x(), kp2.y(), kp2.z()));
  output<<~(beam+target-pip1-pip2-pim) << " " << ~(beam+target-kp1-pip2-pim) <<" "<<~(beam+target-pip1-kp2-pim)<<" "<<~(kp1+pip2+pim)<<" "<<~(kp2+pip1+pim)<<" "<<~(pip1+pim)<<" "<<~(pip2+pim)<<" "<<~(pip1+pip2+pim)<<" ";
//get the meson system 4-vector
  fourVec X;
  X=beam+target-kp1-kp2;
  fourVec kp1_1, kp1_2;
  fourVec kp2_1, kp2_2;
  fourVec cascadem_1, cascadem_2;
  fourVec fixbeam2_1, fixbeam2_2;
  fourVec Y1, Y2;
  kp1_1=kp1;
  kp1_2=kp1;
  kp2_1=kp2;
  kp2_2=kp2;
  cascadem_1=cascadem;
  cascadem_2=cascadem;
  fixbeam2_1=fixbeam2;
  fixbeam2_2=fixbeam2;
  Y1=cascadem+kp2;
  Y2=cascadem+kp1;
  //Now get the angles
  //first print out angles in the lab
  // print angle of K+1 and K+2 in lab
  
  output << kp1.cosTheta() << " " << kp1.phi()/M_PI << " ";
  output << kp2.cosTheta() << " " << kp2.phi()/M_PI << " ";
  output << pim.cosTheta() << " " << pim.phi()/M_PI << " ";
  output << X.cosTheta() << " " << X.phi()/M_PI << " ";
  lorentzTransform L, L1, L2;
  // Define a Lorentz Transformation to the CM
  L.set(beam + target);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
  kp1_1 *=L;
  kp1_2 *=L;
  kp2_1 *=L;
  kp2_1 *=L;
  cascadem_1 *=L;
  cascadem_2 *=L;
  Y1 *=L;
  Y2 *=L;
  fixbeam2_1 *=L;
  fixbeam2_2 *=L;

  //align beam along Z-axis
  L.set(beam.phi(),beam.theta(),0.0);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
  output << kp1.cosTheta() << " " << kp1.phi()/M_PI << " ";
  output << kp2.cosTheta() << " " << kp2.phi()/M_PI << " ";
  output << pim.cosTheta() << " " << pim.phi()/M_PI << " ";
  output << X.cosTheta() << " " << X.phi()/M_PI << " ";

//jb v06 for adding PIangleANA
          fourVec pim_1;
	  lorentzTransform L9;  
	  L9.set(X);
	  pim_1.set(pim.t(),pim.V());
	  pim_1 *=L9;
  //jb v06 adding all angles for pi and lambda
	  fourVec lambda_1;
	  lambda_1.set(lambda.t(),lambda.V());
	  lambda_1 *=L9;
  //jb v06 defining the lab coords
	  threeVec xlab;
	  threeVec ylab;
	  threeVec zlab;
	  xlab.set(1.0,0.0,0.0);
	  ylab.set(0.0,1.0,0.0);
	  zlab.set(0.0,0.0,1.0);

  //for cascadem-Lambda events, assume Kp1 is on the meson vertex
  L1.set(fixbeam2_1.phi(), fixbeam2_1.theta(),0.0); 
  kp1_1 *=L1;
  kp2_1 *=L1;
  fixbeam2_1 *=L1;
  Y1 *=L1;
  threeVec Cross1;
  Cross1 = fixbeam2_1/kp1_1;
  //move this to align with the the y-axis
  L1.set(Cross1.phi(),Cross1.theta()-M_PI/2.0,-M_PI/2.0);
  kp1_1 *=L1;
  kp2_1 *=L1;
  Y1 *=L1;
 // Now rotate to the helicity frame of X so the z axis is along the X momentum  
  L1.set(Y1.phi(),Y1.theta(),0.0);
  kp1_1 *=L1;
  kp2_1 *=L1;
  Y1 *=L1;

  // Now Boost to Y1 rest frame - since y-axis (above) is normal - will not change direction of y
  
  L1.set(Y1);
  kp1_1 *=L1;
  kp2_1 *=L1;
  output<<kp2_1.cosTheta()<<" "<<kp2_1.phi()/M_PI<<" ";


  //for cascadem-Lambda events, assume Kp2 is on the meson vertex
  L2.set(fixbeam2_2.phi(), fixbeam2_2.theta(),0.0); 
  kp1_2 *=L2;
  kp2_2 *=L2;
  fixbeam2_2 *=L2;
  Y2 *=L2;
  threeVec Cross2;
  Cross2 = fixbeam2_2/kp2_2;
  //move this to align with the the y-axis
  L2.set(Cross2.phi(),Cross2.theta()-M_PI/2.0,-M_PI/2.0);
  kp1_2 *=L2;
  kp2_2 *=L2;
  Y2 *=L2;
 // Now rotate to the helicity frame of Y2 so the z axis is along the X momentum  
  L2.set(Y2.phi(),Y2.theta(),0.0);
  kp1_2 *=L2;
  kp2_2 *=L2;
  Y2 *=L2;

  // Now Boost to Y2 rest frame - since y-axis (above) is normal - will not change direction of y
  
  L2.set(Y2);
  kp1_2 *=L2;
  kp2_2 *=L2;
  output<<kp1_2.cosTheta()<<" "<<kp1_2.phi()/M_PI<<" ";




  threeVec Cross;
  Cross = beam/X;
  //move this to align with the the y-axis
  L.set(Cross.phi(),Cross.theta()-M_PI/2.0,-M_PI/2.0);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
 // Now rotate to the helicity frame of X so the z axis is along the X momentum 
  L.set(X.phi(),X.theta(),0.0);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  pim *= L;
  X *=L;

  // Now Boost to X rest frame - since y-axis (above) is normal - will not change direction of y
  
  L.set(X);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
//now we are in the X (cascade*) helicity rest frame , output the 2-body decay angles of Pi- in X rest frame
  
  double alpha, beta;
  double ctpim = -10, phipim = -10;

  alpha=pim.phi();
  beta=pim.theta();
  ctpim = pim.cosTheta();
  phipim = pim.phi()/M_PI;
  if(fabs(ctpim)>0&&fabs(phipim)>0){
    //jb v06    output<<ctpim<<" "<<phipim<<endl;
    output<<ctpim<<" "<<phipim<<" ";   //jb v06
  }
  else{
    //jb   output<<" -10 "<<" "<<" -10 "<<endl;
    output<<" -10 "<<" "<<" -10 "<<" ";   //jb v06
  }

//jb v06
//jb the previous boosts did not act on theese quantities
//jb pim_1 is in the X rest frame with z aligned with beam, and cross is in cm with z aligned with beam	  
  output<<cos((Cross.theta() - (pim_1.V()).theta()))<<" ";
  output<<cos(xlab.theta() - (pim_1.V()).theta())<<" ";
  output<<cos(ylab.theta() - (pim_1.V()).theta())<<" ";
  output<<cos(zlab.theta() - (pim_1.V()).theta())<<" ";
  output<<cos(Cross.theta() - (lambda_1.V()).theta())<<" ";
  output<<cos(xlab.theta() - (lambda_1.V()).theta())<<" ";
  output<<cos(ylab.theta() - (lambda_1.V()).theta())<<" ";
  output<<cos(zlab.theta() - (lambda_1.V()).theta())<<endl; 
/*   my old foolish calculation
  output<<(Cross - pim_1.V()).cosTheta()<<" ";
  output<<(xlab - pim_1.V()).cosTheta()<<" ";
  output<<(ylab - pim_1.V()).cosTheta()<<" ";
  output<<(zlab - pim_1.V()).cosTheta()<<" ";
  output<<(Cross - lambda_1.V()).cosTheta()<<" ";
  output<<(xlab - lambda_1.V()).cosTheta()<<" ";
  output<<(ylab - lambda_1.V()).cosTheta()<<" ";
  output<<(zlab - lambda_1.V()).cosTheta()<<endl;
*/

  }
  return(nReturnValue);
}




tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID){
  /* This routine only works for time-based tracks! */  
  float best_diff=ST_TAG_COINCIDENCE_WINDOW;
  float tprop=0.0;
  tagr_t *tagr = NULL;
  clasTBTR_t *TBTR=(clasTBTR_t *)getBank(&bcs_,"TBTR");
  float g11targz=-10;
  int i, j;      
    
  /* Exit from function if missing the requisite banks... */
  if(!TAGR || !TBTR || !TBID) return(NULL);
    
  for (i=0;i<TBID->bank.nrow;i++){
    int trk_ind=TBID->bid[i].track;
    if(trk_ind){     
      tprop=(TBTR->tbtr[trk_ind-1].vert.z - g11targz)/SPEED_OF_LIGHT*1e9;
    	if (TBID->bid[i].st.stat){       
    	  for(j=0;j<TAGR->bank.nrow;j++){
    	    float diff=fabs(TBID->bid[i].st.vtime-(TAGR->tagr[j].tpho+tprop));
    	    if (diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff
    		&& (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15)){
    	      best_diff=diff;
    	      tagr=&(TAGR->tagr[j]);
    	    }
    	  }       
    	} 
    }



  }
  return(tagr);
}
    
















