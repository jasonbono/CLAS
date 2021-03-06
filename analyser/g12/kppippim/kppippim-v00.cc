/*
February 1 2013, Jason Bono:

This came from 2kppim-v05.cc

*/

#include "/u/home/jbono/corrections/May1/g12_ecor.hpp"  //jb 2kppim-v03
#include </u/home/jbono/corrections/May1/g12_pcor.hpp>

#include <cmath>
#include <string>


#include <iostream>
#include <fstream>
#include <plib.h>


using namespace std;

extern "C" 
 {
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

//bitwise drop flags ???
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

extern "C" 
{
 void bnames_(int *);
 int SetVerbose(int);
 extern void photonenergy_(double *b0, int *run, double *b1, double *b2);
}

int StartRun(int);
int ProcessEvent(clasEvent &event,int, int);
int DropList(int DropFlag);
void PrintUsage(char *processName);
int fillNtuples(clasEvent &event);

tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID, threeVec myVert); //jb v13

int npho( clasTAGR_t *TAGR, float tpho, int nb);  //jb npho2

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
 if (CurrentRun != runNo) 
 {
  vertex_brun(runNo);
  CurrentRun = runNo;
 }
 return 0;
}
int DropList(int DropFlag){
 //Mask off banks according to DropFlag ???
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
void PrintUsage(char *processName){
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
void printLabels(){
 int nlab = 0;

 //jb v35k beam_woecor
 cout << ++nlab << "\toldbeam energy{beam_no_ecor}"<<endl;
 cout << ++nlab << "\tmass of (mmpippim_no_ecor) {mmpippim_no_ecor}"<<endl;
 cout << ++nlab << "\tmass of (mmkppippim_no_ecor) {mmkppippim_no_ecor}"<<endl;
 
 cout << ++nlab << "\tmass of (mmpippim_no_pcor) {mmpippim_no_pcor}"<<endl; 
 cout << ++nlab << "\tmass of (mmkppippim_no_pcor) {mmkppippim_no_pcor}"<<endl; 
 cout << ++nlab << "\tmass of (mpippim_no_pcor) {mpippim_no_pcor}"<<endl; 

 cout << ++nlab << "\tmass of (mmpippim_no_eloss) {mmpippim_no_eloss}"<<endl;
 cout << ++nlab << "\tmass of (mmkppippim_no_eloss) {mmkppippim_no_eloss}"<<endl;
 cout << ++nlab << "\tmass of (mpippim_no_eloss) {mpippim_no_eloss}"<<endl; 
 
 cout << ++nlab << "\tmass of (mmpippim_no_corrections) {mmpippim_no_corrections}"<<endl;
 cout << ++nlab << "\tmass of (mmkppippim_no_corrections) {mmkppippim_no_corrections}"<<endl;
 cout << ++nlab << "\tmass of (mpippim_no_corrections) {mpippim_no_corrections}"<<endl; 

 cout << ++nlab << "\tmass of (mmpippim) {mmpippim}"<<endl;
 cout << ++nlab << "\tmass of (mmkppippim) {mmkppippim}"<<endl;
 cout << ++nlab << "\tmass of (mpippim) {mpippim}"<<endl;

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


 cout << ++nlab << "\t{tofbetakp}"<<endl;
 cout << ++nlab << "\t{tofbetapip}"<<endl;
 cout << ++nlab << "\t{tofbetapim}"<<endl;
 cout << ++nlab << "\t{betakp}"<<endl;
 cout << ++nlab << "\t{betapip}"<<endl;
 cout << ++nlab << "\t{betapim}"<<endl;
 cout << ++nlab << "\t{sctkp}"<<endl;
 cout << ++nlab << "\t{sctpip}"<<endl;
 cout << ++nlab << "\t{sctpim}"<<endl;
 cout << ++nlab << "\t{sclkp}"<<endl;
 cout << ++nlab << "\t{sclpip}"<<endl;
 cout << ++nlab << "\t{sclpim}"<<endl;
 cout << ++nlab << "\t{tofmasskp}"<<endl;
 cout << ++nlab << "\t{tofmasspip}"<<endl;
 cout << ++nlab << "\t{tofmasspim}"<<endl;
 cout << ++nlab << "\t{stvkp}"<<endl;
 cout << ++nlab << "\t{stvpip}"<<endl;
 cout << ++nlab << "\t{stvpim}"<<endl;

 cout << ++nlab << "\t{goodSTkp}"<<endl;  //jb v16
 cout << ++nlab << "\t{goodSTpip}"<<endl;  //jb v16
 cout << ++nlab << "\t{goodSTpim}"<<endl;  //jb v16

 cout << ++nlab << "\t{stid_kp}"<<endl;  //jb v17
 cout << ++nlab << "\t{stid_pip}"<<endl;  //jb v17
 cout << ++nlab << "\t{stid_pim}"<<endl;  //jb v17

 // distances
 cout << ++nlab << "\t(distance between K+, pi-){dkppim}"<<endl;
 cout << ++nlab << "\t(distance between pi+, pi-){dpippim}"<<endl;
 cout << ++nlab << "\t(distance between K+, pi+){dkppip}"<<endl;
 cout << ++nlab << "\tbeam energy{beam}"<<endl;
 cout << ++nlab << "\tsqrt(s){w}"<<endl;
  
 //t stuff
 cout << ++nlab << "\tt energy transfer(kp+pip - beam){tkppip}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp+pip+pim - beam){tkppippim}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp+pim - beam){tkppim}"<<endl;
 cout << ++nlab << "\tt energy transfer(pip+pim - beam){tpippim}"<<endl;

 //momentums
 cout << ++nlab << "\tkp momentum{pkp}"<<endl;
 cout << ++nlab << "\tpip momentum{ppip}"<<endl;
 cout << ++nlab << "\tpip momentum{ppim}"<<endl;
 cout << ++nlab << "\tmiss x{missx}"<<endl;
 cout << ++nlab << "\tmiss y{missy}"<<endl;
 cout << ++nlab << "\tmiss z{missz}"<<endl;
 cout << ++nlab << "\tmiss momentum{missp}"<<endl; 
 cout << ++nlab << "\tmiss momentum{misse}"<<endl; 
 //mandalstam varaible t
 //cout << ++nlab << "\tt prime{tp}"<<endl;
 //cout << ++nlab << "\tt prime{tpkp}"<<endl;
 
//constrained masses
 cout << ++nlab << "\tMass(mmk0){mmk0}"<<endl;
 cout << ++nlab << "\tMass(mmkpk0){mmkpk0}"<<endl;

 

 //jb v10
 cout << ++nlab << "\t(Number of photons in 1 timing bunch){nphoton_nb0}"<<endl;
 cout << ++nlab << "\t(Number of photons in 3 timing bunches ){nphoton_nb1}"<<endl;
 cout << ++nlab << "\t(Number of photons in 5 timing bunches){nphoton_nb2}"<<endl;
}

// -----------------------------------------------------------------------------
// --------------------------------- Main program ------------------------------
// ------------------------- To be modified to fit need ------------------------
// -----------------------------------------------------------------------------

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

 for (int i = 1; i < argc; i++)
 {
  argptr = argv[i];
  if (*argptr == '-') 
  {
   argptr++;
   switch (*argptr) 
   {
	
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
	if(OutputUnitNo)
	{
	 cerr << "Output file: " << BOSoutfile << endl;
	 unlink(BOSoutfile);
	 sprintf(out, "OPEN BOSOUTPUT UNIT=9 FILE=\"%s\" WRITE  STATUS=NEW RECL=3600", BOSoutfile);
	 if (!fparm_c(out)) 
	 {
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

 for (int i = 1; i < argc; ++i) 
 {
  argptr = argv[i];
  // process all arguments on command line.
  if (*argptr != '-') 
  {
   // we have a file to process
   clasEvent event(argptr, &bcs_, partbank0, 0);   

   cerr << "initialize:\t" << argptr << endl;
   //     cout << argptr <<endl; //jb v13 puneet wanted me to print this out to see what it does
   Dispatch = isDispatcher(argptr);
   if (event.status()) 
   {
	ret = 1;
	while ((max ? Nevents < max : 1) && ret)
	{
	 // process every event in the file
	 ret = event.read(partbank0);
	 if (ret == DISIO_DATA) 
	 {  
	  
	  Nevents++;
                  
	  if (event.status()) 
	  {
	   if (triggerMask ? (triggerMask & event.trig()) : 1) 
	   {
		int runno = event.run();     
		//int runno = 19660;
		if(setRun)
		{
		 runno = setRun;
		}
		ConfigEvent(runno,0); 
		/* Initialize the TOF geometry.  This is needed regardless of whether you remake the SC reconstruction banks or not.  However, for the regeneration case, this is done in ConfigEvent. */
		StartRun(runno);
		writeFlag = ProcessEvent(event,verbose, IFLAG) ;
		if (BOSoutfile && writeFlag) 
		{
		 if (DropFlag) 
		 {
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
	 else if (ret == DISIO_COMMAND) 
	 {
 	  cerr << "Message from Giant Head: " << getBuffer() << endl;;
     }
	}
	cerr << "\nTotal number of itape records read:\t" << Nevents << endl;
	cerr << "Total number of events processed:\t" << Nproc << endl;
	cerr << "\tTotal number of records written:\t" << Nwrite << endl;
   }
   else 
   {
	cerr << "Unable to open " << argptr << endl;
   }
  }
 }
  
 if (Dispatch) 
 {
  disIO_command("FINISHED");
 }
  
 cerr << "\nTotal number of itape records:\t" << Nevents << endl;

 if (BOSoutfile)
 {
  putBOS(&bcs_,9, "0");
  sprintf(out, "CLOSE BOSOUTPUT UNIT=9");
  fparm_c(out);  
 }
   
 /// Initialization of Momentum Correction Parameters
 
  return (0);
}




// ------------------------------------------------
// ---------------- ProcessEvent ------------------
// ------------ Make all analysis here ------------
// ------------------------------------------------


 int counter = 0;
 int mmcounter = 0;
int ProcessEvent(clasEvent &my_event,int verbose, int IFLAG)
{
 int nReturnValue = 0;

 //set the topology
 if (my_event.N(KPlus)!=1|| my_event.N(PiMinus)==0 || my_event.N(PiPlus)==0 )
 {
  //cout << "event not passing particle filter for the " << counter << " time " <<endl;
  //cout << " Nkp,Npip,Npim = " << my_event.N(KPlus) << ", " <<my_event.N(PiMinus)<< ", " << my_event.N(PiPlus) << endl;
  //counter = counter + 1;
  return (0);
 }



 //----some basic setup-----
 double CASCADE0_MASS = 1.31483;
 double CASCADE_MASS = 1.32131; //mass of Xi-
 double KP_MASS = 0.493667;
 double K0_MASS = 0.497614;
 double PI_MASS = 0.139570; //mass of charged pion
 clasTAGR_t *TAGR = (clasTAGR_t *)getBank(&bcs_,"TAGR"); 
 clasBID_t *TBID  =  (clasBID_t *)getBank(&bcs_,"TBID"); 
 threeVec myVert=my_event.V();; //jb v13 wrong gives error in compiler
 int runno=0;
 int evtno=0;
 double tMin,tMinkp;
 tagr_t *tagr = my_get_photon_tagr(TAGR, TBID, myVert);  //jb v13 calling it
 

 //----target stuff-----
 fourVec target(PROTON_MASS,threeVec(0.0,0.0,0.0));


 //---photon stuff----
 double beamp_no_ecor = -100, beamp = -100.0;
 int eid = 0;
 float tpho; //jb npho
 if(tagr)
 {
  eid = tagr->e_id;
  beamp_no_ecor = tagr->erg;
  tpho=tagr->tpho; //jb npho 
 }
 beamp = beamp_no_ecor;

 fourVec beam, beam_no_ecor; 
 beam_no_ecor.set(beamp_no_ecor,threeVec(0.0,0.0,beamp_no_ecor));
 beam = beam_no_ecor;
 

 //---particle stuff----
 fourVec kp,pip, pim;
 fourVec kp_no_eloss, pip_no_eloss, pim_no_eloss;
 fourVec kp_no_pcor, pip_no_pcor, pim_no_pcor; 
 fourVec kp_no_corrections, pip_no_corrections, pim_no_corrections;

 kp_no_corrections=my_event.cp(KPlus,1).p();
 pip_no_corrections=my_event.cp(PiPlus,1).p();
 pim_no_corrections=my_event.cp(PiMinus,1).p();

 kp_no_eloss = kp_no_corrections;
 pip_no_eloss = pip_no_corrections;
 pim_no_eloss = pim_no_corrections;



//--------------------------------------------------beam energy corections,eloss,kaon switching --------------------------------------------------

 
 runno=my_event.run();
 evtno=my_event.event();
 
 ///eloss and ecor
 if(corr)
 {
  my_event.eLoss("g11a", IFLAG);
  if(datatype)
  {
   beamp = clas::g12::corrected_beam_energy(my_event.run(), beamp_no_ecor);
  }
 }


 //setup the ecor and eloss corrected four vectors
 beam.set(beamp,threeVec(0.0,0.0,beamp));
 kp=my_event.cp(KPlus,1).p();
 pip=my_event.cp(PiPlus,1).p();
 pim=my_event.cp(PiMinus,1).p();
 kp_no_pcor = kp;
 pip_no_pcor = pip;
 pim_no_pcor = pim;


 //do the pcor
 if(corr && datatype) 
 {
  string parms_dir = "/u/home/jbono/corrections/May1";  
  clas::g12::MomentumCorrection pcor(parms_dir);
  
  ///--------------kp,pip,pim------------------
  //kp
  float id_kp = 11; // kaon (geant 3 ID codes)
  float p_kp = kp.r(); // total momentum
  float px_kp = kp.x();
  float py_kp = kp.y();
 
  float pz_kp = sqrt(p_kp*p_kp - px_kp*px_kp - py_kp*py_kp);
  float phi_kp = atan2(py_kp,px_kp);
  float theta_kp = acos(pz_kp/p_kp);

  float new_p_kp = p_kp + pcor.pcor(phi_kp,id_kp);

  float new_px_kp = (new_p_kp / p_kp) * px_kp;
  float new_py_kp = (new_p_kp / p_kp) * py_kp;
  float new_pz_kp = (new_p_kp / p_kp) * pz_kp;

  kp.set( sqrt(KP_MASS*KP_MASS + new_p_kp*new_p_kp), new_px_kp, new_py_kp, new_pz_kp);


  //pip
  float id_pip = 8; // kaon (geant 3 ID codes)
  float p_pip = pip.r(); // total momentum
  float px_pip = pip.x();
  float py_pip = pip.y();

  float pz_pip = sqrt(p_pip*p_pip - px_pip*px_pip - py_pip*py_pip);
  float phi_pip = atan2(py_pip,px_pip);
  float theta_pip = acos(pz_pip/p_pip);

  float new_p_pip = p_pip + pcor.pcor(phi_pip,id_pip);

  float new_px_pip = (new_p_pip / p_pip) * px_pip;
  float new_py_pip = (new_p_pip / p_pip) * py_pip;
  float new_pz_pip = (new_p_pip / p_pip) * pz_pip;

  pip.set( sqrt(KP_MASS*KP_MASS + new_p_pip*new_p_pip), new_px_pip, new_py_pip, new_pz_pip);



  //pim
  float id_pim = 9; // kaon (geant 3 ID codes)
  float p_pim = pim.r(); // total momentum
  float px_pim = pim.x();
  float py_pim = pim.y();

  float pz_pim = sqrt(p_pim*p_pim - px_pim*px_pim - py_pim*py_pim);
  float phi_pim = atan2(py_pim,px_pim);
  float theta_pim = acos(pz_pim/p_pim);

  float new_p_pim = p_pim + pcor.pcor(phi_pim,id_pim);

  float new_px_pim = (new_p_pim / p_pim) * px_pim;
  float new_py_pim = (new_p_pim / p_pim) * py_pim;
  float new_pz_pim = (new_p_pim / p_pim) * pz_pim;

  pim.set( sqrt(PI_CHARGED_MASS*PI_CHARGED_MASS + new_p_pim*new_p_pim), new_px_pim, new_py_pim, new_pz_pim);



  ///--------------kp_no_eloss,pip_no_eloss,pim_no_eloss------------------
  //kp_no_eloss
  float id_kp_no_eloss = 11; // kaon (geant 3 ID codes)
  float p_kp_no_eloss = kp_no_eloss.r(); // total momentum
  float px_kp_no_eloss = kp_no_eloss.x();
  float py_kp_no_eloss = kp_no_eloss.y();
 
  float pz_kp_no_eloss = sqrt(p_kp_no_eloss*p_kp_no_eloss - px_kp_no_eloss*px_kp_no_eloss - py_kp_no_eloss*py_kp_no_eloss);
  float phi_kp_no_eloss = atan2(py_kp_no_eloss,px_kp_no_eloss);
  float theta_kp_no_eloss = acos(pz_kp_no_eloss/p_kp_no_eloss);

  float new_p_kp_no_eloss = p_kp_no_eloss + pcor.pcor(phi_kp_no_eloss,id_kp_no_eloss);

  float new_px_kp_no_eloss = (new_p_kp_no_eloss / p_kp_no_eloss) * px_kp_no_eloss;
  float new_py_kp_no_eloss = (new_p_kp_no_eloss / p_kp_no_eloss) * py_kp_no_eloss;
  float new_pz_kp_no_eloss = (new_p_kp_no_eloss / p_kp_no_eloss) * pz_kp_no_eloss;

  kp_no_eloss.set( sqrt(KP_MASS*KP_MASS + new_p_kp_no_eloss*new_p_kp_no_eloss), new_px_kp_no_eloss, new_py_kp_no_eloss, new_pz_kp_no_eloss);


  //pip_no_eloss
  float id_pip_no_eloss = 8; // kaon (geant 3 ID codes)
  float p_pip_no_eloss = pip_no_eloss.r(); // total momentum
  float px_pip_no_eloss = pip_no_eloss.x();
  float py_pip_no_eloss = pip_no_eloss.y();

  float pz_pip_no_eloss = sqrt(p_pip_no_eloss*p_pip_no_eloss - px_pip_no_eloss*px_pip_no_eloss - py_pip_no_eloss*py_pip_no_eloss);
  float phi_pip_no_eloss = atan2(py_pip_no_eloss,px_pip_no_eloss);
  float theta_pip_no_eloss = acos(pz_pip_no_eloss/p_pip_no_eloss);

  float new_p_pip_no_eloss = p_pip_no_eloss + pcor.pcor(phi_pip_no_eloss,id_pip_no_eloss);

  float new_px_pip_no_eloss = (new_p_pip_no_eloss / p_pip_no_eloss) * px_pip_no_eloss;
  float new_py_pip_no_eloss = (new_p_pip_no_eloss / p_pip_no_eloss) * py_pip_no_eloss;
  float new_pz_pip_no_eloss = (new_p_pip_no_eloss / p_pip_no_eloss) * pz_pip_no_eloss;

  pip_no_eloss.set( sqrt(KP_MASS*KP_MASS + new_p_pip_no_eloss*new_p_pip_no_eloss), new_px_pip_no_eloss, new_py_pip_no_eloss, new_pz_pip_no_eloss);


 
  //pim_no_eloss
  float id_pim_no_eloss = 9; // kaon (geant 3 ID codes)
  float p_pim_no_eloss = pim_no_eloss.r(); // total momentum
  float px_pim_no_eloss = pim_no_eloss.x();
  float py_pim_no_eloss = pim_no_eloss.y();

  float pz_pim_no_eloss = sqrt(p_pim_no_eloss*p_pim_no_eloss - px_pim_no_eloss*px_pim_no_eloss - py_pim_no_eloss*py_pim_no_eloss);
  float phi_pim_no_eloss = atan2(py_pim_no_eloss,px_pim_no_eloss);
  float theta_pim_no_eloss = acos(pz_pim_no_eloss/p_pim_no_eloss);

  float new_p_pim_no_eloss = p_pim_no_eloss + pcor.pcor(phi_pim_no_eloss,id_pim_no_eloss);

  float new_px_pim_no_eloss = (new_p_pim_no_eloss / p_pim_no_eloss) * px_pim_no_eloss;
  float new_py_pim_no_eloss = (new_p_pim_no_eloss / p_pim_no_eloss) * py_pim_no_eloss;
  float new_pz_pim_no_eloss = (new_p_pim_no_eloss / p_pim_no_eloss) * pz_pim_no_eloss;

  pim_no_eloss.set( sqrt(PI_CHARGED_MASS*PI_CHARGED_MASS + new_p_pim_no_eloss*new_p_pim_no_eloss), new_px_pim_no_eloss, new_py_pim_no_eloss, new_pz_pim_no_eloss);


 } //end of pcor



 //setup clas particles
 clasParticle cpkp0, cpkp, cppip, cppim;
 cpkp = my_event.cp(KPlus, 1); 
 cppip = my_event.cp(PiPlus, 1);
 cppim = my_event.cp(PiMinus, 1);
 


 //------------------------------------------------filters------------------------------------------------------
 //check the Vtime first to clean up the data
 float scv=my_event.scVtime();
 float stv=my_event.stVtime();
 float mmkppippim = ~(beam + target - kp - pip - pim); 
 threeVec Vert = my_event.V();

 
 int st=0;
 if(abs(my_event.scVtime()-my_event.stVtime())<=2) st=1; 
 
 int bb=0;
 if(beamp > 2.373) bb=1;
 
 int mm=0;
 if(mmkppippim > 1.2 && mmkppippim < 1.65) mm=1;
 

 if(!mm)
 {
  //cout << "event not passing missing mass filter for " << mmcounter <<" time "<< " mmkppippim = "<< mmkppippim  <<endl; 	
  //mmcounter = mmcounter + 1;
 }
 if(st&&bb&&mm)
 {
  nReturnValue = 1;

  //show the effects of the corrections
  //no ecor
  output << beamp_no_ecor << " "; 
  output << ~(beam_no_ecor + target - pip - pim) << " "; 
  output << ~(beam_no_ecor + target - kp - pip - pim) << " ";

  //no pcor
  output << ~(beam + target - pip_no_pcor - pim_no_pcor) << " "; 
  output << ~(beam + target - kp_no_pcor - pip_no_pcor - pim_no_pcor) << " ";
  output << ~(pip_no_pcor + pim_no_pcor) << " ";
  //no eloss
  output << ~(beam + target - pip_no_eloss - pim_no_eloss) << " ";
  output << ~(beam + target - kp_no_eloss - pip_no_eloss - pim_no_eloss)<< " ";
  output << ~(pip_no_eloss + pim_no_eloss) << " ";
  //no corrections
  output << ~(beam_no_ecor + target - pip_no_corrections - pim_no_corrections) << " "; 
  output << ~(beam_no_ecor + target - kp_no_corrections - pip_no_corrections - pim_no_corrections)<< " ";
  output << ~(pip_no_corrections + pim_no_corrections) << " ";
  //all the corrections
  output << ~(beam + target - pip - pim)<<" ";
  output << ~(beam + target - kp - pip - pim) <<" ";
  output << ~(pip + pim) << " ";
  
//start real stuff	  
  output << runno<< " " <<evtno<< " ";
  output << my_event.scVtime() << " " << my_event.stVtime() << " " << my_event.vtime() << " ";
  output << Vert.x() << " " << Vert.y() << " " << Vert.z() << " ";
  output << my_event.N(KPlus) << " " << my_event.N(PiMinus) << " " << my_event.N(KMinus) << " " << my_event.N(Proton) << " " << my_event.N(PiPlus) << " ";

  /// output<<mppim<<" ";

  //betas,  beta is calculated by ??? while Beta is calculated by ???
  output << cpkp.beta() <<" ";
  output << cppip.beta() <<" ";
  output << cppim.beta() <<" ";
  output << cpkp.Beta() <<" ";
  output << cppip.Beta() <<" ";
  output << cppim.Beta() <<" ";
  //sctime and scpath
  output << cpkp.sc_time() <<" ";
  output << cppip.sc_time() <<" ";
  output << cppim.sc_time() <<" ";
  output << cpkp.scPathLen() <<" ";
  output << cppip.scPathLen() <<" ";
  output << cppim.scPathLen() <<" ";
  //TOF mass
  output << cpkp.mass() <<" ";
  output << cppip.mass() <<" " ;
  output << cppim.mass() <<" ";
  //check st_vtime for different particles
  output << cpkp.stVtime() <<" ";
  output << cppip.stVtime() <<" "; 
  output << cppim.stVtime() <<" ";
  //check st 
  output << cpkp.isSThit() <<" ";  	//jb v16
  output << cppip.isSThit() <<" ";   //jb v16
  output << cppim.isSThit() <<" "; //jb v16	
  output << cpkp.st_id() <<" ";  	//jb v17
  output << cppip.st_id() <<" ";   //jb v17
  output << cppim.st_id() <<" "; //jb v17 
	
  //vertex separations
  double vkppim=-1000, vpippim=-1000, vkppip=-1000;
  vkppim = my_event.vert2Separation(cpkp, cppim);
  vpippim = my_event.vert2Separation(cppip, cppim);
  vkppip = my_event.vert2Separation(cpkp, cppip);
  output << vkppim <<" ";
  output << vpippim <<" ";
  output << vkppip <<" ";
  //beam energy,w
  output << beamp << " "; 
  output << ~(beam+target) << " ";
  
  //t stuff
  output << (kp+pip-beam).lenSq() << " ";
  output<< (kp+pip+pim-beam).lenSq() <<" ";
  output << (kp+pim-beam).lenSq() <<" ";
  output << (pip+pim-beam).lenSq() <<" ";
  
  //momentums
  output << kp.r() <<" ";
  output << pip.r() <<" ";
  output << pim.r() <<" ";
  output << (beam + target - kp - pip - pim).x() << " ";
  output << (beam + target - kp - pip - pim).y() << " ";
  output << (beam + target - kp - pip - pim).z() << " ";
  output << (beam + target - kp - pip - pim).r() << " ";
  //missing energy
  output << (beam + target - kp - pip - pim).t() << " ";
  
  //mandalstam variable t 
  //t transfer to kppippim system
  //tMin = tmin( beamp,0.0, PROTON_MASS, ~(kp + pip + pim), CASCADE0_MASS);
  //output << -((kp + pip + pim - beam).lenSq() - tMin) << " ";
  //t transfer to kp
  //tMinkp  = tmin( beamp, 0.0, PROTON_MASS, KP_MASS, CASCADE_MASS);
  //output << -((kp - beam).lenSq() - tMinkp) << " ";



  //constrain pip pim to be the mass of the k0 and get MM(k0 kp)
  fourVec pipi= pip + pim;
 
  
  double Ek0 = sqrt(K0_MASS*K0_MASS + pipi.r()*pipi.r());
  fourVec k0;
  k0.set(Ek0, threeVec(k0.x(), k0.y(), k0.z()));

  
  //replot the constrained masses 
  output << ~(beam + target - k0) <<" ";
  output << ~(beam + target - kp - k0 ) <<" "; 

 




  //jb v10  the number of photons
  output<<npho(TAGR, tpho, 0)<<" "; 
  output<<npho(TAGR, tpho, 1)<<" "; 
  output<<npho(TAGR, tpho, 2)<<endl; 
 } //jb v35k  this is the filter re-enabled
 return(nReturnValue);
}   // this is the end of processevent


//===================================================jb npho======================================================

int  npho( clasTAGR_t *TAGR, float tpho, int nb)
{                                                                //jb npho func
 int nph=0; //jb npho
 int k;  

 for(k=0;k<TAGR->bank.nrow;k++)
 {  
  if (abs(tpho - TAGR->tagr[k].tpho) < (0.05+2.004*nb)) 
  {                                                             //jb npho  
   nph=nph+1;
  }           
 }
 return(nph);
}
//--------------------------------------------------------------------------------------------------------------
//=====================================jb  my_get_photon_tagr===================================================

//tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID){ 
tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID, threeVec myVert)
{                                                                                 //jb v13
  
 /* This routine only works for time-based tracks! */  
 float best_diff=ST_TAG_COINCIDENCE_WINDOW;
 float tprop=0.0;
 tagr_t *tagr = NULL;
 clasTBTR_t *TBTR=(clasTBTR_t *)getBank(&bcs_,"TBTR");
 float g11targz=-10; //this was for g11
 float g12targz=-90; //jb v11
 int i, j; 
  
 /* Exit from function if missing the requisite banks... */
 if(!TAGR || !TBTR || !TBID) return(NULL);
    
 for (i=0;i<TBID->bank.nrow;i++)
 {
  int trk_ind=TBID->bid[i].track;
  if(trk_ind)
  {     
   //jb v13      tprop=(TBTR->tbtr[trk_ind-1].vert.z - g12targz)/SPEED_OF_LIGHT*1e9;  //jb v11 i think i need to take this out
   tprop=(myVert.z() - g12targz)/SPEED_OF_LIGHT*1e9;  //jb v13
   //cout<<"myVert.z()=" << myVert.z() <<" :  TBTR->tbtr[trk_ind-1].vert.z="<< TBTR->tbtr[trk_ind-1].vert.z<<endl; //jb v13 just a check
   if (TBID->bid[i].st.stat)
   {       
    float mytime=-1000;             //jb v14
    float myenergy=-1000;           //jb v14
  
    for(j=0;j<TAGR->bank.nrow;j++)
    {
     float diff=fabs(TBID->bid[i].st.vtime-(TAGR->tagr[j].tpho+tprop));
     //jb v14     if (diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff
	 //jb v14	&& (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15)){/////////////}    	   
	 //cout <<abs(TAGR->tagr[j].tpho - tagr->tpho)<<endl;
	
	 if (( diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff || (abs(TAGR->tagr[j].tpho - mytime)<0.011&& (TAGR->tagr[j].erg) > myenergy)  )  &&  (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15))
	 {                                                                                //jb v14
      best_diff=diff;
      tagr=&(TAGR->tagr[j]);
	  mytime=tagr->tpho; //jb v14
	  myenergy=tagr->erg; //jb v14
	 }
    } 
   } 
  }
 }
 return(tagr);
}
//--------------------------------------------------------------------------------------------------------------------------------------    






