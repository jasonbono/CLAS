/* make_tw_histos.c */
/* This is a program for filling a set of 48 histograms for a given sector 
   and side of the TOF with times in ns as a function of ADC values.  It 
   operates on raw data generated by a special laser calibration run. 
   Another program will be invoked to fit the distributions in order to derive
   the time-walk correction parameters used in the sc reconstruction code. */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ntypes.h>
#include <bostypes.h>
#include <map_manager.h>
#include <clas_cern.h> 
#include <call.h>
#include <scExtern.h>

#define ADC_PEDESTALS 6
#define T0 0
#define T1 1
#define T2 2
#define LEFT 0
#define RIGHT 1
#define STAND_DEV 2
#define MEAN 1
#define TRUE 1
#define FALSE 0
#define MEMH 50000000
float pawc_[MEMH];

call_const_t call_calib;

int gamecockMode = 0;

/* avoid ambiguity: ALL replaced by sector == 0 */
int init_hbook(char *outfile,int sector,int side, int redo);
int ProcessEvent(int sector,int side,float offset,float lo_cut,float hi_cut);
void PrintUsage(char *processName);

#ifdef VINTAGE_BUILD
void rootopenw(const char* filename) {}
void rootend() {}
void rootbook1(int hid, const char* title, int xbins, double xmin, double xmax) {}
void rootf1(int hid, double x, double value) {}
void count_initialize(int nfiles, char* filelist[]) {}
double get_percent(int ifile, int eventNo) {return 0.;}
int  coupled_paddle_index(int sector, int stripe, int itbtr) {return 0;}
#else
extern  void rootopenw(const char* filename);
extern  void rootend();
extern  void rootbook1(int hid, const char* title, int xbins, double xmin, double xmax);
extern  void rootf1(int hid, double x, double value);
extern  void count_initialize(int nfiles, char* filelist[]);
extern  double get_percent(int ifile, int eventNo);
extern  int  coupled_paddle_index(int sector, int stripe, int itbtr);
#endif

/* --------------------------------------------------- */

int main(int argc,char *argv[]){
  char *dir,callmap[100];
  char *argptr;
  char mess[128];
  char *outfile=NULL;
  char *number;
  FILE *inputfileptr;
  FILE *outputfile;
  clasHEAD_t *header=NULL;
  int side=LEFT;
  float lo_cut = 1.0, hi_cut = 800.0;
  int Nevents=0,i,j,k,errno,runno = -1,max=99999;
  int sector=0,offset=0.,min=1;
  int findRange=0;

  /* copy filename to list */
  double curPercent = 0.;
  char* dataFile[256];
  int nfiles = 0;

  /* Parse command-line arguments */
  if (argc==1) PrintUsage(argv[0]); 
  for (i=1; i<argc; i++) {
    argptr = argv[i];
    if (*argptr == '-') {
      argptr++;
      switch (*argptr) {
      case 'h':
	PrintUsage(argv[0]); 
	break;
      case 'o':
	outfile = ++argptr;
	break;
      case 'n':
	max = atoi(++argptr);
	break;
      case 'm':
	min=atoi(++argptr);
	break;
      case 's':
	sector=atoi(++argptr);
 	break;
      case 'f':
	findRange = 1;
	break;
      case 'r':
	side=RIGHT;
	break;
      case 'l':
	side=LEFT;
	break;
      case 'G':
	gamecockMode = 1;
	break;
      case 't':
 	offset=atof(++argptr); 
	break; 
      case 'c': 
	lo_cut=atof(++argptr);
	break;
      case 'C':
	hi_cut=atof(++argptr);
	break;
      default:
	fprintf(stderr,"Unrecognized argument: [-%s]\n\n",argptr);
	PrintUsage(argv[0]);
	break;
      }
    }
    else   /* it is a data file */

      /*create list of data files, duplicate first entry to find the range */
      if (nfiles < 255) {
	if (!nfiles && findRange) {
	  dataFile[nfiles++] = argv[i]; /* first file in array to find range */
	}
	dataFile[nfiles++] = argv[i];
      }
      else {
	fprintf(stderr, "can't process more than 255 data files\n"); 
	PrintUsage(argv[0]);
      }
  }

  /* Initialize BOS */
  initbos();
  
  /* Loop over the datafiles specified in command-line args. */
  for (i = 0; i < nfiles; i++) {
    sprintf(mess,"OPEN BOSINPUT UNIT=1 FILE=\"%s\" READ", dataFile[i]);
    if (!fparm_c(mess)) {
      fprintf(stderr,"%s: Unable to open file \'%s\': %s\n\n",
	      argv[0], dataFile[i], strerror(errno));
    }
    else {
      printf("Processing %s...\n",argptr);
      while ((max ? Nevents < max : 1) && getBOS(&bcs_,1,"E")) {
	Nevents++;
	if(Nevents==1){
	  
	  /* Get run number from Header bank */
	  header=(clasHEAD_t *)getBank(&bcs_,"HEAD");
	  if (header!=NULL){
         if(runno == -1){
           set_sc_version_constants(header->head[0].nrun);
           /* Initialize the paw system and book histograms */
           init_hbook(outfile,sector,side,0);
         }
	    runno=header->head[0].nrun;
	  }
	  else{
	    printf("No header bank!\n");
	    exit(1);
	  }
	  
	  /* Initialize the SC package */
	  make_SCG_banks(runno);
	  sc_init(runno,TW_CALIB); /* Note that TW_CALIB is a special
				      calibration-only flag for the
				      initialization routine */
	  
	  /* Get laser diode calibration constants */
	  initCL01(runno);
	}
	if(Nevents>min){
	  make_CL01_bank();	  
	  ProcessEvent(sector,side,offset,lo_cut,hi_cut);
	  
	  for(j=0; j <= 6; j++) dropBank(&bcs_, "SC  ", j);
	  for(j=0; j <= 6; j++) dropBank(&bcs_, "SC1 ", j);
	  dropBank(&bcs_,"CL01",0);
	  dropBank(&bcs_,"CALL",0);
	  cleanBanks(&bcs_);
	    
	  if (Nevents%100==0){
	    fprintf(stderr,"%d\r",Nevents);
	    fflush(stderr);
	    }	
	}
      }
    }
    fparm_c("CLOSE BOSINPUT");
    Nevents=0;
  }


  /* Redo it, this time with a good hist range */
  if(findRange){
    init_hbook(outfile,sector,side,1);
    for (i = 0; i < nfiles; i++) {
      sprintf(mess,"OPEN BOSINPUT UNIT=1 FILE=\"%s\" READ", dataFile[i]);
      if (!fparm_c(mess)) {
        fprintf(stderr,"%s: Unable to open file \'%s\': %s\n\n",
  	      argv[0], dataFile[i], strerror(errno));
      }
      else {
        printf("Processing %s...\n",argptr);
        while ((max ? Nevents < max : 1) && getBOS(&bcs_,1,"E")) {
	  Nevents++;
	  if(Nevents==1){
	  
	    /* Get run number from Header bank */
	    header=(clasHEAD_t *)getBank(&bcs_,"HEAD");
	    if (header!=NULL){
	      runno=header->head[0].nrun;
	    }
	    else{
	      printf("No header bank!\n");
	      exit(1);
	    }
	  
	    /* Initialize the SC package */
	    make_SCG_banks(runno);
	    sc_init(runno,TW_CALIB); /* Note that TW_CALIB is a special
				      calibration-only flag for the
				      initialization routine */
	  
	    /* Get laser diode calibration constants */
	    initCL01(runno);
	  }
	  if(Nevents>min){
	    make_CL01_bank();	  
	    ProcessEvent(sector,side,offset,lo_cut,hi_cut);
	  
	    for(j=0; j <= 6; j++) dropBank(&bcs_, "SC  ", j);
	    for(j=0; j <= 6; j++) dropBank(&bcs_, "SC1 ", j);
	    dropBank(&bcs_,"CL01",0);
	    dropBank(&bcs_,"CALL",0);
	    cleanBanks(&bcs_);
	    
	    if (Nevents%100==0){
	      fprintf(stderr,"%d\r",Nevents);
	      fflush(stderr);
	      }	
	    }
        }
      }
      fparm_c("CLOSE BOSINPUT");
      Nevents=0;
    }
  }

  hrout(0,2," ");
  hldir_(" ", " ", 1L, 1L); /* don't remove this line */
  hrend("timw");
}

/*********** END MAIN ******************/

void PrintUsage(char *processName)
{
  fprintf(stderr,"Usage: %s [...options...] file1 [file2] etc....\n\n",processName);
  fprintf(stderr,"  Options:\n");
  fprintf(stderr,"\t-n[#]\t\tProcess only # number of events\n\n");
  fprintf(stderr,"\t-o[filename]\tHistogram output file\n\n");
  fprintf(stderr,"\t-s[sector]\tSector number [default=all]\n\n");
  fprintf(stderr,"\t-t[offset]\tTime offset to get data in range\n\n");
  fprintf(stderr,"\t-f\t\tFind time offset automatically\n\n");
  fprintf(stderr,"\t-l\t\tProduce left histograms\n\n");
  fprintf(stderr,"\t-r\t\tProduce right histograms \n\n");
  fprintf(stderr,"\t-h\t\tPrint this message.\n\n");
  fprintf(stderr,"\t-c\t\tLower cut on laser diode time\n\n");
  fprintf(stderr,"\t-C\t\tUpper cut on laser diode time\n\n");
  exit(0);
}


/* Initialize the paw system and book histograms */


int init_hbook(char *hbookfile,int sector,int side, int redo){
  const float dy = 25.;
  int id,j,k,memh=MEMH;
  char def_out[128];
  char title[128];
  int s0,s1,sec,indx;
  int basid;
  float y0=0., y1=50.;
  float entry[SC_NPADDLES_TOTAL],sum[SC_NPADDLES_TOTAL],ave[SC_NPADDLES_TOTAL];

  s0 = (!sector) ? 1 : sector;
  s1 = (!sector) ? 6 : sector;

  basid = (side==LEFT) ? 100 : 100; //was 100 : 1000!!!
  /* Initialize PAW system */
  if (redo) {
    hrend("timw");
    hunpak(6, entry, " ", 0);
    hunpak(7, sum, " ", 0);
    for (j=0; j<SC_NPADDLES_TOTAL; j++){
      ave[j] = (entry[j]>0.) ? sum[j]/entry[j] : dy;
//fprintf(stderr, "sum, entry, ave = %f, %f, %f \n", sum[j], entry[j], ave[j]);
    }
    hdelet(0);
    printf ("Rebooking histograms...\n");
  }
  else {
    hlimit_(&memh);
    printf("Booking histograms...\n");
  }    

  hbook1(1,"Photo diode time Forward Carriage",2000,0,800,0);
  hbook1(2,"Photo diode time North Carriage"  ,2000,0,800,0);
  hbook1(3,"Photo diode time South Carriage  ",2000,0,800,0);
  hbook1(4,"Photo diode time Space Frame"     ,2000,0,800,0);
  hbook1(5,"ALL DIODES"                       ,2000,0,800,0);
  hbook1(6,"Entries"                          ,SC_NPADDLES,-0.5,(float)SC_NPADDLES - 0.5,0.);
  hbook1(7,"Sum"                              ,SC_NPADDLES,-0.5,(float)SC_NPADDLES - 0.5,0.);
  hbook1(8,"RMS"                              ,SC_NPADDLES,-0.5,(float)SC_NPADDLES - 0.5,0.);

//==================================
//  loop over one or more sectors 
//==================================

  for(sec=s0; sec<=s1; sec++){
    for (id=1;id<=SC_NPADDLES_SEC;id++){
      sprintf(title,"Pulse height vs. time, sec %d id %d %s", sec, id, (side==LEFT)?"LEFT":"RIGHT");
      if (redo) {
	indx = sc_index(sec,id);
	y0 = ave[indx] - dy;
	y1 = ave[indx] + dy;
      }
      hbook2(basid*sec+id, title, 135,0.0,8100,500,y0,y1, 0);
      sprintf(def_out,"tof_tw_sec%d%c.hbook",sec,(side==LEFT)?'l':'r');
    }
  }
    
  /* Open the HBOOK file. */
  if (hbookfile==NULL) hbookfile=&def_out[0];

  hropen(2,"timw",hbookfile,"N",1024,0);  
}





/* Make the SC1 bank and fill the histograms using the data in SC1 */

int ProcessEvent(int sector, int side, float offset, float lo_cut, 
		 float hi_cut)
{
  clasSC1_t *SC1 = NULL;
  clasCL01_t *CL01 =NULL;

  int k, l;
  static int i=0,j=0;
  float t1,t2,t0;
  float time_lr[2],E_l,E_r;
  float ref_time,ref_time1,ref_time2,ref_time3,ref_time4;
  float offset2 = 800.0;
  int s0,s1,sec;
  extern call_const_t call_calib;
  int basid, indx;

  /* sector == 0 : process all sectors */
  s0 = (!sector) ? 1 : sector;
  s1 = (!sector) ? 6 : sector;

  basid = (side==LEFT) ? 100 : 100; //was 100 : 1000!!!
  
  /* Apply the calibration constants to the raw data (SC) and create the 
     SC1 bank */

  /*======== One sector or all sectors ===============*/
  int locFillHistArray[4], locIndex;
  for(sec=s0; sec<=s1; sec++){
    make_SC1_bank(sec);  
    SC1 = getGroup(&bcs_,"SC1 ", sec);
    CL01 = getBank(&bcs_,"CL01");

    if(SC1 && CL01){
      ref_time1 = CL01->cl01[0].fc_diode_t;
      ref_time2 = CL01->cl01[0].nc_diode_t;
      ref_time3 = CL01->cl01[0].sc_diode_t;
      ref_time4 = CL01->cl01[0].sf_diode_t;

      for(l = 0; l < 4; l++)
        locFillHistArray[l] = 0;

      for(k=0;k<SC1->bank.nrow;k++){
        ref_time  = get_diode_time(CL01->cl01[0],SC1->sc1[k].id,sec);
	   if (ref_time>lo_cut&&ref_time<hi_cut){
          //note that the value of the offsets and the t0 in calcing the ref_time (call->t0 caldb const) don't affect the fit result as long as they are consistent for each event within a sc paddle.  
	     time_lr[LEFT]  = offset+offset2-ref_time+SC1->sc1[k].time_l;
	     time_lr[RIGHT] = offset+offset2-ref_time+SC1->sc1[k].time_r;

//fprintf(stderr, "offset, offset2, ref_time, LEFT time is %f, %f, %f, %f \n", offset, offset2, ref_time, time_lr[LEFT]);
	     /* Because we called the initialization routine with a special flag,
	        the 'energies' are really pedestal-subtracted ADC values */
	     E_l=SC1->sc1[k].energy_l; 
	     E_r=SC1->sc1[k].energy_r;   

//fprintf(stderr, "energy l, r = %f, %f \n", E_l, E_r);
          locIndex = get_diode_id(SC1->sc1[k].id,sec) - 2;
          if((locIndex >= 0) && (locIndex < 4)){
            if(locFillHistArray[locIndex] == 0){
              locFillHistArray[locIndex] = 1;
              hf1(locIndex + 1, ref_time, 1);
              hf1(5, ref_time, 1);
            }
	     }
	  
	     indx = sc_index(sec,SC1->sc1[k].id);
	     if(E_l>0&&E_l<8100){ 
	       hf2(basid*sec+SC1->sc1[k].id,E_l,time_lr[side],1.0);
	       if (time_lr[side] > -50.) {
	         hf1(6,indx,1.);
	         hf1(7,indx,time_lr[side]);
	         hf1(8,indx,time_lr[side]*time_lr[side]);
	       }
	     }
	   }
      }
    }
  }
}
