/*
 * template.cc   
 * 
 */

#include <iostream>
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
#include <dataIO.h>
#include <itape.h>
#include <vertex.h>
#include <trk.h>
#include <makebanks.h>

	   }

#include <Vec.h>
#include <lorentz.h>
#include <pputil.h>
#include <clasEvent.h>
#include <View.h>


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

static int requestedRawData = 0;
  
  /* ----------- Function prototypes ---------------- */

int printGeneralLabels(char *c);
static void signalINT(int isig);
static void signalSEGV(int isig);
  int StartRun(int runNo);
  int EndRun(int run);
  int ProcessEvent(clasEvent &event,int verbose,int silent);
void installFaultHandlers();
void DropList(int DropFlag);
void pHeader(clasEvent &event);

double beta(const fourVec &p);
double beta(const fourVec &p,double m);
double beta(const threeVec &p,double m);
double deltaBeta(double l,double t);
double chisq(const threeVec &p,double mass,double len,double t);
double gamma(double beta);
double mass(double p,double beta);
extern "C" {
  int bnames_(int *); 
 int trk_remake_swim_banks(int,float,float,float,int,int,int,int);  
  void dc_set_def_();
  void trk_set_def_();
  void dc_xvst_init_(int *);

}

extern particleDataTable PDGtable;


  /* declare the bos common */
BOSbank bcs_;
BOSbank wcs_;
#define LIGHT_SPEED 29.979 // speed of light cm/nsec

int CurrentRun = 0;
int CurrentEvent = 0;
  
void PrintUsage(char *processName)
{
  cerr << processName << " [options] file1 file2 ..." << endl;
  cerr << "\t[-cm#]\t\tSet mini-torus current to #" << endl;
  cerr << "\t[-ct#]\t\tSet torus current to #" << endl;
  cerr << "\t[-L]\t\tPrint labels" << endl;
  cerr << "\t[-v]\t\tverbose mode" << endl;
  cerr << "\t[-ofile]\twrite selected events to file" << endl;
  cerr << "\t[-d]\t\tdebug mode" << endl;
  cerr << "\t[-D#]\t\tSet drop list to #" << endl;
  cerr << "\t[-M#]\t\tProcess only # events" << endl;
  cerr << "\t[-s]\t\tsilent mode" << endl;
  cerr << "\t[-N]\t\tDo not build TDPL bank (unless necessary)" <
  cerr << "\t[-h]\t\tPrint this message" << endl;
  
  
}



// ------------------------------------

main(int argc,char **argv)
{
  FILE *fp = NULL;
  int max = 0;

  int verbose = 0;
  int Silent = 0;

  int writeMode = 0;
  int forceWrite = 0;

  int reBuild = -1;
  int doBuild = 0;
  int rebuildTBID = 0;

  int ret = 1;
  int rejectFlag = 0;
  int NoFault = 0;
  int pEvent;
  
  int Nevents = 0;
  int nfile = 0;
  int Nwrite = 0;
  int nProc = 0;
  time_t time1; 
  float rate; 
  int i;
  char *argptr;
  char *word;
  int Dispatch = 0;
  unsigned int triggerMask = 0;

  int useGPID = 0;
  int useSEB = 0; 
  int partbank = 1;
  char *BOSout = "newFilter.bos";
  int debug = 0;

  // Dispatcher
  char *server = NULL;
  int dispatcherPipelinePrefill = 5;

  int allFlag = 0;
  int dropTDPL = 0;


  // drop sector list

  vector<int> dropSector;

  // itape stuff
  FILE *finput = stdin;

  // bos stuff

  clasOutput coutput;
  int OutputUnitNo = 9;
  extern char *optarg;
  int c; 
  extern int optind;
  int MaxBanks = 1000; 
  char  out[300];

  int DropFlag = 0x0; /*don't drop anything*/

  for (i = 0; i < argc; ++i)
    cerr << argv[i] << " ";
  cerr << endl;

  for (int i = 0; i < argc; ++i)
    cerr << argv[i] << " ";
  cerr << endl;
  while ( (c = getopt(argc,argv, "Ra")) != -1 ) {
    switch (c) {
 
    case 'G':
      useGPID = 1;
      break;

    case 'S':
      useSEB = 1;
      break;

    case 'P':
      partbank = atoi(optarg);
      break;

    case 'F':
      forceWrite = 1;
      break;

    case 'R':
      // write out rejected events
      rejectFlag = 1;
      break;

    case 'L':
      printGeneralLabels(optarg);
      break;
    case 'v':
      verbose = 1;
      break;

    case 'o':
	
      BOSout = optarg;
      break;

    case 'f':
      // do not install fault handlers
      NoFault = 1;
      break;

    case 'd':
      debug = 1;
      break;

    case 'D':
      DropFlag = strtoul(optarg,NULL,0);
      break;

    case 'M':
      max = atoi(optarg);
      break;

    case 't':
      triggerMask = strtoul(optarg,NULL,0);
      break;

    case 's':
      Silent = 1;
      break;

    case 'h':
      PrintUsage(argv[0]);
      exit(0);
      break;

    default:
      cerr << "Unrecognized argument: " << argptr << endl;;
      break;
	  
   
    }

  }

  PDGtable.initialize();


  if (!NoFault)
    installFaultHandlers();

  // Initialize BOS
  bnames_(&MaxBanks);
  initbos();
  configure_banks(stderr,0);

  for (i = 1; i < argc; ++i) {
    argptr = argv[i];
    if (*argptr != '-') {
      clasEvent event(argptr,&bcs_,1,0);
      cerr << "initialize:\t" << argptr << endl;

      Dispatch = isDispatcher(argptr);
      if (event.status()) {
	ret = 1;

	while ((max ? Nevents < max : 1) && ret) {
	  clasHEAD_t *HEAD;	  
	  ret = event.read(1);  // still one event?

	  if (ret == DISIO_DATA) {
	    if (event.type() == 1) {
	      if (HEAD = (clasHEAD_t *)getBank(&bcs_, "HEAD")) {
		int runno=HEAD->head[0].nrun;
		CurrentRun = HEAD->head[0].nrun;
		CurrentEvent =  HEAD->head[0].nevent;
		StartRun(runno); 

		pEvent = ProcessEvent(event,verbose,Silent);
		nProc++;
		if (coutput.status() && (forceWrite ? 1 : (rejectFlag ? !pEvent : pEvent))) {
		  if (DropFlag)
		    DropList(DropFlag);
		  coutput.write(&bcs_);
		  Nwrite++;
		}
	    
	      }
	      event.clean();
	      Nevents++;
	    }
	  
	  }
	  
	
	  else if (ret == DISIO_COMMAND) {
 
	    cerr << "Message from Giant Head: " << getBuffer() << endl;;
      
	  }

	}
	cerr << "\nTotal number of itape records:\t" << Nevents << endl;
	cerr << "\tTotal number of records written:\t" << Nwrite << endl;

      }
      else {
	cerr << "Unable to open " << argptr << endl;
      }

      
    }
  }
  if (Dispatch)
    disIO_command("FINISHED");
  cerr << "\nTotal number of itape records:\t" << Nevents << endl;
  if(coutput.status()) {
    coutput.write(&bcs_,"0");
    coutput.close();
  }
}

int StartRun(int runNo)
{  
  int static CurrentRun = -1;
  if (CurrentRun != runNo) {
    //    dc_xvst_init_(&runNo);
    //    vertex_brun(runNo);
    //  sc_begin_run(runNo);
    //   dc_begin_run(runNo);
    CurrentRun = runNo;

  }
  return 0;
}





int ProcessEvent(clasEvent &event,int verbose,int silent)
{
  int ret = 1; 

  return(ret);
}

int EndRun(int run)
{

	return 0;
}

int GetDispatcherCommand()
{
  int ret;
  int maxSend = 2;
  int OkToSendData = 1;
  int WaitForALLFINISHED = 0;
  int runNo;

  /* wait for command from Dispatcher */

  fd_set rset;
  fd_set wset;
  struct timeval timeout;
  int maxfd = 0;

  FD_ZERO(&rset);
  FD_ZERO(&wset);

  FD_SET(disIO_socket,&rset); if (disIO_socket > maxfd) maxfd = disIO_socket;

  if (OkToSendData && (requestedRawData > 0))
    {
      FD_SET(disIO_socket,&wset); if (disIO_socket > maxfd) maxfd = disIO_socket;
    }

  timeout.tv_sec  = 1;
  timeout.tv_usec = 0;

  if (OkToSendData && (requestedRawData > 0))
    {
      timeout.tv_sec  = 0;
      timeout.tv_usec = 0;
    }

  ret = select(maxfd + 1, &rset, &wset, NULL, &timeout);
  if (ret < 0)
    {
      cerr << "DisFeedDAQ: Error: select() returned " <<  ret << "errno: " << errno << " " << strerror(errno) << endl;
      //	  exitFlag = 1;
      exit(0);
    }    

  /* ok, we got a command. Now parse it */
  static char *msg = NULL;
  static int msglen = 0;
  char *cmd0;
  char *word;
  int maybeUnexpected = 0;

  if (msg)
    free(msg);

  msg = NULL;

  ret = disIO_readRAW_alloc((void **)&msg,&msglen,0);

  if (msg) {

    word = strtok(msg,":");
    cmd0 = word;
    if (word) {
      cerr << "COMMAND: " << cmd0 << endl;

      if (strcmp(word,"NOP") == 0)
	{
	  /* do nothing */
	}
      else if (strcmp(word,"PING") == 0)
	{
	  printf("DisFeedDAQ: Command from Dispatcher: %s\n",word);
	  disIO_command("PING-REPLY");
	}
      else if (strcmp(word,"REQUEST_DATA") == 0)
	{
	  int imore;

	  /* fprintf(stderr,"DisFeedDAQ: Command from Dispatcher: %s\n",word); */

	  word = strtok(NULL,":");

	  if (word)
	    imore = strtoul(word,NULL,0);
	  else
	    imore = 1;

	  /* printf("REQUEST_DATA: more: %d, requested events: %d, sent: %d\n",imore,requestedRawData,isent); */

	  requestedRawData += imore;
	}
      else if (strcmp(word,"MAXSEND") == 0)
	{
	  cerr << "DisFeedDAQ: Command from Dispatcher: " << word << endl;

	  word = strtok(NULL,":");

	  if (word)
	    maxSend = strtoul(word,NULL,0);

	  printf("DisFeedDAQ: New maxSend is %d\n",maxSend);
	}
      else if (strcmp(word,"ALLFINISHED") == 0)
	{
	  if (WaitForALLFINISHED)
	    {
	      cerr << "DisFeedDAQ: Command ALLFINISHED from Dispatcher: " << word << endl;
	      //	    SendBeginTape(runNo);
	      OkToSendData = 1;
	      WaitForALLFINISHED = 0;
	    }
	  else
	    {
	      fprintf(stderr,"DisFeedDAQ: Unexpected command ALLFINISHED from Dispatcher was ignored.\n");
	    }
	}
      else if (strcmp(word,"QUIT") == 0)
	{
	  fprintf(stderr,"DisFeedDAQ: Command QUIT from Dispatcher: %s\n",word);
	  exit(0);
	}
      else if (strcmp(word,"EXIT") == 0)
	{
	  fprintf(stderr,"DisFeedDAQ: Command EXIT from Dispatcher: %s\n",word);
	  exit(0);
	}
      else
	{
	  fprintf(stderr,"DisFeedDAQ: Unexpected command from Dispatcher: [%s] was ignored.\n",msg);
	}
    }
  }
  else {
    cerr << "Received empty message from the Dispatcher" << endl;
  }


      
  return(ret);
}
extern "C" {
int ir_isnan_(float *x)
{
  return(0);
}

int ir_isinf_(float *x)
{
 
  return(0);
}


}

    
void pHeader(clasEvent &event)
{
    int trig = event.trig() & (int) 0xf; 
    cout << event.run() << " " << event.event() << " " << trig << " " ;
 
}

    
void DropList(int DropFlag)
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
 

}

/* Fault handlers */

void installFaultHandlers()
{
  signal(SIGINT,signalINT);  
  signal(SIGSEGV,signalSEGV);
  //  signal(SIGABRT,signalSEGV);
  //  signal(SIGBUS,signalSEGV); 
  //  signal(SIGPIPE,signalPIPE);
  cerr << "Fault handlers installed" << endl;
}

static void signalINT(int isig)
{
  clasEvent e;
  char mess[100];
  static int count = 0;

  cerr << "Run/Event: " << CurrentRun << " " << CurrentEvent << endl;

  count++;
  if (count < 4){
    signal(isig,signalINT);
  } 
  else {
    exit(0);
  }
}
static void signalSEGV(int isig)
{
  clasEvent e;
  static int icount = 0;
  
  cerr << "signalSEGV: Caught signal " << endl;
  cerr << "Run/Event: " << CurrentRun << " " << CurrentEvent << endl;
  exit(1);

}


int printGeneralLabels(char *c)
{
  int ret = 0;
  int print = !strlen(c);
  if (print || (strcmp(c,"TAGR") == 0)) {
    int nlab = 0; 

    cout << "Labels for XXX:" << endl; 
    cout << ++nlab << "\tRun {run}" << endl;
    cout << ++nlab << "\tEvent {evt}" << endl; 
    cout << ++nlab << "\ttrigger {trig}" << endl;
    ret = 1;
  }

  return(ret);
}

// debugging

