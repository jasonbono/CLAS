/*
  gamp2part: convert gamp format to CLAS PART Bank
  gp5: added proper detachment for proton and xi

ga6: took out the lambda-proton and lambda-pion vertex detachment and only decatch the Xi-pion: this is because 
the entire vertex time seems to be affected by the lambda-pion and nothing else.  it seems that changing only the Xi-pion has no effect on the timing
distributions but i will leave it in anyway mostly because it should be the right thing to do.

*/

#include <iostream>
#include <unistd.h>

using namespace std;

/*------example PAW Ntuple structure---------------------------*/
extern "C" {

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
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
#include <map_manager.h>
#include <time.h>

using namespace std;

#define MELECTRON .00051

  /* ----------- Function prototypes ---------------- */
void ctrlCHandle(int);
void PrintUsage(char *processName);
  /* declare the bos common */
BOSbank bcs_;
  int nchar(char *,char);
}

#include <kinematics_o.h>
#include <clasPART_o.h>


int maxevents = 0;
clasPART_t *make_pizero_part_bank(int GroupNo, int newpart);
part_t makeBeam(int pid, vector4_t p );
void printgamp(part_t *part);
float beamP(int run);
double Number(double x);
double randm (double low, double high);
void parseTargetPosition(char *str,double& zmin,double& zmax);
void parseTargetXY(char* arg, double& mu_x, double& mu_y,
           double& sigma_x, double& sigma_y);
double gaussian(double xmean,double xwidth);
double expodecay(double tau); //jb

/*#include <matrix.h>
#include <Vec.h>
#include <lorentz.h>*/

/* --------------------------------------------------- */

void PrintUsage(char *processName)
{
  cerr << "Usage: " << processName << " [-M] file1 [file2] etc....\n\n";
  cerr << "  Options:\n\n";
  cerr << "     -M[#]\t\tUse only [#] number of events\n";
  cerr << "     -p[#]\t\tUse this number part bank for output file\n";
  cerr << "     -r[#]\t\tUse [#] for runno (default runno = 1)\n";
  cerr << "     -o<filename>\tUse <filename> for output BOS file\n";
  cerr << "     -t[#]\t\tUse [#] for trigger bit identification (default = 1)\n";
  cerr << "     -T\t\t\tPut Beam particle in TAGR bank (photon use only!)\n";
  cerr << "     -z[#,#]\t\tDistribute vertex-z is given range\n";
  cerr << "     -S[#,#,#,#]\tDistribute vertex-xy according to MU_X,MU_Y,SIGMA_X,SIGMA_Y\n";
  cerr << "     -V\t\t\tUse debugging mode\n";
  cerr << "     -h\t\t\tPrint this message\n\n";
  exit(0);
}



int main(int argc,char **argv)
{
  FILE *fileptr = NULL;
  int i;
  char *argptr, *outfile = NULL;
  int Nevents = 0, Nfile = 0;
  char out[100],mess[100];
  int ret,runno=1;
  ios::sync_with_stdio();
  int partno = 0;
  int verbose = 0;
  int Verbose = 0;
  int debug=0, trigbit=1;
  int makeTAGR=0,offset=0;

  int ElectronRun = 0;
  int CurrentRun = 0;

  clasPART_t *PART = NULL;
  clasHEAD_t *HEAD = NULL;
  clasTAGR_t *TAGR = NULL;

  int num_particles=0,nwrite=0;
  int pid = 0,pcharge = 0;
  float momx=0.0,momy=0.0,momz=0.0,E=0;

  double zmin=0, zmax=0;
  double mu_x(0), mu_y(0), sigma_x(0), sigma_y(0);

  double beamWidth = 0.4;
  long int RDMseed = 0;

  signal(SIGINT,ctrlCHandle);
  signal(SIGHUP,ctrlCHandle);

  char c;
  while ((c = getopt(argc, argv, "M:o:p:r:S:t:TvVz:h")) != -1) {
    switch(c)
      {
      case 'v':
    verbose = 1;
    break;
      case 'V':
    Verbose = 1;
    debug = 1;
    break;
      case 'z':
    parseTargetPosition(optarg, zmin, zmax);
    break;
      case 'r':
    runno = atoi(optarg);
    break;
      case 'M':
    maxevents = atoi(optarg);
    break;
      case 'p':
    partno = atoi(optarg);
    break;
      case 'S':
    parseTargetXY(optarg, mu_x, mu_y, sigma_x, sigma_y);
    break;
      case 'T':
    makeTAGR=1;
    break;
      case 't':
    trigbit = atoi(optarg);
    break;
      case 'o':
    outfile = optarg;
    sprintf(out, "OPEN BOSOUTPUT UNIT=%d FILE=\"%s\" WRITE STATUS=NEW RECL=3600", 7,outfile);
    if (!fparm_c(out)) {
      fprintf(stderr,"%s: Unable to open file \'%s\': %s\n\n",argv[0],out,strerror(errno));
      exit(1);
    }
    break;
      case 'h':
    PrintUsage(argv[0]);
    abort();
      case '?':
        if ((optopt == 'M') ||
        (optopt == 'o') ||
        (optopt == 'p') ||
        (optopt == 'r') ||
        (optopt == 'S') ||
        (optopt == 't') ||
        (optopt == 'z')
        ) {

      cout << "Option -" << optopt << " requires an argument." << endl;
      cout << "See `gamp2part -h' for more." << endl;
    }
        else if (isprint(optopt)) {
          cout << "Unknown option -" << optopt << endl;
      cout << "See `gamp2part -h' for more." << endl;
        }
        else {
          cout << "Unrecognized option character " << optopt << endl;
      cout << "See `gamp2part -h' for more." << endl;
        }
        return 1;
      default:
        abort();
      }
  }

  if (optind == argc) {
    cout << "Please supply one or more gamp files for input." << endl;
    cout << "See `gamp2part -h' for more." << endl;
    return 3;
  }



  if(!RDMseed){
    srand48((long)time(NULL));
  }else{
    srand48(RDMseed);
  }

  /*initialize bos and hbook*/
  initbos();

  for (int iarg = optind; iarg < argc; ++iarg) {
    argptr = argv[iarg];

    if (debug) {
      fprintf (stderr,"Using file: %s\n",argptr);
    }

    fileptr = fopen(argptr,"r");
    if (fileptr) {
      while (!feof(fileptr) && (maxevents ? Nevents < maxevents : 1)) { //Event loop
      offset=0;
      num_particles=0;
      fscanf(fileptr,"%d",&num_particles);

      if (!num_particles) {
        break;
      }

      if (debug) {
        fprintf (stderr,"number of particles: %d\n",num_particles);
      }
      if (debug) {
        fprintf (stderr,"Current value of offset : %d\n",offset);
      }

      HEAD = (clasHEAD_t *)makeBank(&bcs_,"HEAD",0,sizeof(head_t)/sizeof(int),1);
      if (makeTAGR) {
        TAGR = (clasTAGR_t *)makeBank(&bcs_,"TAGR",0,sizeof(tagr_t)/sizeof(int),makeTAGR);
      }
      PART = (clasPART_t *)makeBank(&bcs_,"PART",partno,sizeof(part_t)/sizeof(int),(num_particles-makeTAGR));





      /* First particle is the beam */
      double zvert = randm(zmin, zmax);
      double xvert = gaussian(mu_x, sigma_x);
      double yvert = gaussian(mu_y, sigma_y);
      for (i=0;i<num_particles;i++) { //Particle loop
        fscanf(fileptr,"%d %d %f %f %f %f",&pid,&pcharge,&momx,&momy,&momz,&E);
        if (debug)
		{
        	fprintf(stderr,"pid, charge,mx,my,mz,E: %d %d %f %f %f %f\n",pid,pcharge,momx,momy,momz,E);
        }
        if (i==0) 
		{
          	if (makeTAGR) 
			{
        		TAGR->tagr[0].erg=E;
        		TAGR->tagr[0].stat=15;
        		offset=1;
        		if (debug) 
				{
          			fprintf(stderr,"Offset now %d\n",offset);
        		}
  			} 
			else 
			{
        		PART->part[i].pid = pid;
        		PART->part[i].q = (float)pcharge;
        		PART->part[i].p.space.x = momx;
        		PART->part[i].p.space.y = momy;
        		PART->part[i].p.space.z = momz;
        		PART->part[i].p.t = E;
          	}
        } 
		else 
		{
          	if (debug) 
			{
        		fprintf(stderr,"offset=%d\n",offset);
          	}
          	PART->part[i-offset].pid = pid;
          	PART->part[i-offset].q = (float)pcharge;
          	PART->part[i-offset].p.space.x = momx;
          	PART->part[i-offset].p.space.y = momy;
          	PART->part[i-offset].p.space.z = momz;
          	PART->part[i-offset].p.t = E;
          	PART->part[i-offset].vert.x = xvert;
          	PART->part[i-offset].vert.y = yvert;
          	PART->part[i-offset].vert.z = zvert;
        }
        if (!makeTAGR) 
		{
          	if (!i) 
			{
        		PART->part[i].flags = BEAM_FLAG;
         	} 
			else
			{
        		PART->part[i].flags = 2;
          	}
        }
 		else 
		{
        	if (i > 0) 
			{
        		PART->part[i-offset].flags=2;
          	}
      	}
 	}
	// end loop over particles		
	int pionPosition = -1000;
	double newPionX, newPionY, newPionZ;
	int nkaon = 0;
	int npion = 0;
	int kaonID = 11;
	int pionID = 9;
	int protonID = 14;
	double kp1_px,kp1_py,kp1_pz;
	double kp2_px,kp2_py,kp2_pz;
	double pim_px,pim_py,pim_pz;
	double event_vertx,event_verty,event_vertz;
	
	
	kp2_px = PART->part[3].p.space.x;
	kp2_py = PART->part[3].p.space.y;
	kp2_pz = PART->part[3].p.space.z;
	kp1_px = PART->part[4].p.space.x;
	kp1_py = PART->part[4].p.space.y;
	kp1_pz = PART->part[4].p.space.z;
	
	pim_px = PART->part[2].p.space.x;
	pim_py = PART->part[2].p.space.y;
	pim_pz = PART->part[2].p.space.z;

	event_vertx = PART->part[2].vert.x;//could be any index
	event_verty = PART->part[2].vert.y;
	event_vertz = PART->part[2].vert.z;


	//jb xi information needed for calculation
	double beam = TAGR->tagr[0].erg;
	double xi_mass = 1.32171;
	double lam_mass = 1.115;
	double lightspeed =  29.9792458;
	//xi momentum
	double xi_px = 0 - kp1_px - kp2_px;
	double xi_py = 0 - kp1_py - kp2_py;
	double xi_pz = beam - kp1_pz - kp2_pz;
	//xi momentum
	double lam_px = 0 - kp1_px - kp2_px - pim_px;
	double lam_py = 0 - kp1_py - kp2_py - pim_py;
	double lam_pz = beam - kp1_pz - kp2_pz - pim_pz;
	
	//cout << " xi_pz = " << xi_pz<< "  E = " <<E<<endl;
	//cout <<" runno = " <<runno << " beam = " <<beam <<endl;
	
	//futher xi calculations
	double xi_p = sqrt(xi_px*xi_px + xi_py*xi_py + xi_pz*xi_pz);
	double xi_t = sqrt(xi_mass*xi_mass + xi_p*xi_p);
	double xi_beta = xi_p/xi_t;
	double xi_gamma = 1/sqrt(1 - xi_beta*xi_beta);
	double xi_tau = 0.1639; //in nanno seconds
	double xi_decaytime = expodecay(xi_tau);
	//futher lam calculations
	double lam_p = sqrt(lam_px*xi_px + lam_py*lam_py + lam_pz*lam_pz);
	double lam_t = sqrt(lam_mass*lam_mass + lam_p*lam_p);
	double lam_beta = lam_p/lam_t;
	double lam_gamma = 1/sqrt(1 - lam_beta*lam_beta);
	double lam_tau = 0.2632; //in nanno seconds
	double lam_decaytime = expodecay(lam_tau);
	

	//cout << "GAMMA = " <<xi_gamma << "  xi_decaytime = " <<xi_decaytime<<endl;
	//cout << "z-detachment = " <<lightspeed*xi_gamma*xi_pz*xi_decaytime/xi_t<<endl;
	
	//calculate how far xi flys before it decays
	double xi_flightx = lightspeed*xi_gamma*xi_px*xi_decaytime/xi_t;
	double xi_flighty = lightspeed*xi_gamma*xi_py*xi_decaytime/xi_t;
	double xi_flightz = lightspeed*xi_gamma*xi_pz*xi_decaytime/xi_t;
	//calculate how far lambda flys before it decays
	double lam_flightx = lightspeed*lam_gamma*xi_px*lam_decaytime/lam_t;
	double lam_flighty = lightspeed*lam_gamma*xi_py*lam_decaytime/lam_t;
	double lam_flightz = lightspeed*lam_gamma*xi_pz*lam_decaytime/lam_t;
	//find the new pion1 vertex
	double pi_newvertx = event_vertx + xi_flightx;
	double pi_newverty = event_verty + xi_flighty;
	double pi_newvertz = event_vertz + xi_flightz;
	//find the new proton and pion2 vertex
	double pro_newvertx = pi_newvertx + lam_flightx;
	double pro_newverty = pi_newverty + lam_flighty;
	double pro_newvertz = pi_newvertz + lam_flightz;
		
	//set the new vertex for pion1 which comes from the Xi decay
	PART->part[2].vert.x = pi_newvertx;
	PART->part[2].vert.y = pi_newverty;
	PART->part[2].vert.z = pi_newvertz;
	//set the new vertex for the proton and pion2 which comes from the Lambda decay	 
	//PART->part[1].vert.x = pro_newvertx;
	//PART->part[1].vert.y = pro_newverty;
	//PART->part[1].vert.z = pro_newvertz;
	//PART->part[0].vert.x = pro_newvertx;
	//PART->part[0].vert.y = pro_newverty;
	//PART->part[0].vert.z = pro_newvertz;


    HEAD->head[0].version = 1105;
    HEAD->head[0].nrun = runno;
    HEAD->head[0].nevent = Nevents+1;
    HEAD->head[0].type = 1;
    HEAD->head[0].evtclass = 15;
    HEAD->head[0].trigbits = trigbit;
    HEAD->head[0].time = time(NULL);
    if (outfile && num_particles) {
    	if (makeTAGR) {
          	putBOS(&bcs_, 7, "HEADPARTTAGR");
          	nwrite++;
        } else {
          	putBOS(&bcs_, 7, "HEADPART");
        }
	}
    dropAllBanks(&bcs_,"E");
    cleanBanks(&bcs_);
    Nevents++;
  }
  dropAllBanks(&bcs_,"E");
  cleanBanks(&bcs_);
  Nfile++;
  fclose(fileptr);
}
else {
	fprintf(stderr,"Unable to open file!\n");
}
  }
  sprintf(mess,"CLOSE BOSOUTPUT", argptr);
  fparm_c(mess);
  cerr << "Total # of events processed:\t" << Nevents << endl;
}

void printgamp(part_t *part){
  cout << part->pid << " " << gchrg(part->pid) << " "<< Number(part->p.space.x) << " ";
  cout << Number(part->p.space.y) << " " << Number(part->p.space.z) << " " << Number(part->p.t) << endl;
}

void ctrlCHandle(int x)
{
  signal(SIGINT,ctrlCHandle);
  signal(SIGHUP,ctrlCHandle);
  maxevents = 1;
  fprintf(stderr,"\n\n\t\t\t***  INTERRUPTED!!!  ***\n\n");
}

float beamP(int run)
{
  char *map = "RUN_CONTROL.map";
  char *subsystem = "beam";
  char *item = "energy";
  int length = 1;
  int firsttime;
  float p;
  char x[1000];
  float ret;


      sprintf(x,"%s/Maps/%s",getenv("CLAS_PARMS"),map);
      map_get_float(x  ,subsystem,item,length,&p,run,&firsttime);
      cerr << "BEAM MOMENTUM for Run " << run << " = " << p << " MeV " << endl;
      return(p/1000.0);
}

double Number(double x)
{

  return(isnan(x) ? 1000.0 : x);
}

void parseTargetPosition(char *str,double& zmin,double& zmax)
{
  double z1 = 0,z2 = 0;
  char *word;
  if (nchar(str,',') == 1) {
    /* user has specified a 2-vector */
    word = strtok(str,",");
    z1 = atof(word);
    word = strtok(NULL,",");
    z2  = atof(word);
  }
  else if (nchar(str,',') == 0) {
    z1 = z2 = atof(str);
  }
  else {
    cerr << "error parsing target position:" << str << endl;
  }
  cerr << "Target position set to: " << z1 << " -> " << z2 << endl;
  zmin = z1;
  zmax = z2;
}

void parseTargetXY(char* str, double& mu_x, double& mu_y,
           double& sigma_x, double& sigma_y)
{
  if (nchar(str, ',') != 3) {
    cerr << "When specifying the `-S' option, please supply a string"
     << " in MU_X,MU_Y,SIGMA_X,SIGMA_Y format." << endl;
    cerr << "See `gamp2part -h' for more." << endl;
    abort();
  }

  mu_x    = atof(strtok(str, ","));
  mu_x    = atof(strtok(str, ","));
  sigma_x = atof(strtok(str, ","));
  sigma_y = atof(strtok(str, ","));
}


double randm (double low, double high)
{
  return ((high - low) * drand48 () + low);
}

double gaussian(double xmean,double xwidth)
{
 double r1,r2=9999,g1=1;

 while (r2>g1)
   {
    r1=randm(-3,3);
    g1=exp(-1*(r1*r1)/2)/sqrt(2.*M_PI);
    r2=randm(0,1);
   }
 return(xwidth * r1 + xmean);
}

double expodecay(double tau)//jb: tau is the mean lifetime: tau = (t_halflife)/(ln(2)) 
{
	double x=randm(0,1);
	double t=(-tau)*log(1-x); 
	return (t);
	//transformation func for t goes from a uniform random number 
	//in {0,1} (randm(0,1)) to an exponential decay (1/tau*(exp(-x/tau)))
}




/* end file */
