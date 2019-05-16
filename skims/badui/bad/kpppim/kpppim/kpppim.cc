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

//#include <g12_pcor.hpp>
#include <g12_ecor.hpp>
#include <Vec.h>
#include <lorentz.h>
#include <pputil.h>
#include <clasEvent.h>
#include "res.h"
//#include <g12Anal.h>


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
double twoThreeVecAngle(threeVec, threeVec);
int npho( clasTAGR_t *TAGR, float tpho, int nb);  //jb npho2
tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID, threeVec myVert); //jb v13
void processTrack(clasParticle  &cp);
void processTrack(fourVec p, int ck);
void printTrackLabels(int *nlab, char *id1, char *id2);
void printFourVecLabels(int *nlab, char *id1, char *id2);
void processGeneralHeader(clasEvent &evt);
void printGeneralHeaderLabels(int *nlab);
int hel(clasHEVT_t *HEVT);

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
    int status = 0;
    int OutputUnitNo = 9;
    extern char *optarg;
    int c; 
    extern int optind;
    int MaxBanks = 1000; 
    char  out[300];
    
    int DropFlag = 0x0; /*don't drop anything*/
    
    //for (i = 0; i < argc; ++i)
     //   cerr << argv[i] << " ";
    //cerr << endl;
    
    for (int i = 0; i < argc; ++i)
        cerr << argv[i] << " ";
    cerr << endl;
    while ( (c = getopt(argc,argv, "o:L:")) != -1 ) {
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
                cout<<"FORCE WRITE"<<endl;
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
                status = coutput.open(BOSout, OutputUnitNo);
                
                cout <<"Status:["<<status<<"] " <<"Output file: " << BOSout << endl;
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
                                if (status && pEvent) {
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
    if(status) {
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

int hel(clasHEVT_t *HEVT)
{
        int helicity = 0;
        int readout = HEVT->hevt[0].trgprs;
        if(readout > 0) helicity = 1;
        if(readout < 0) helicity = -1;
        return(helicity);
}

int ProcessEvent(clasEvent &evt,int verbose,int silent)
{
	setRes();
    int ret = 0;
	int ck = 1, ckCM = 1;
    	fourVec kp, p, km, beam, target, X, Y; //X missing meson, Y missing baryon
	fourVec kpLab, pLab, kmLab, beamLab, XLab, YLab; //Lab Frame
	threeVec Cross;
    clasParticle kp_particle, p_particle, km_particle;
	double pmass, kpmass;
	lorentzTransform L;
    //double eBeamLo = 3.5;
    //double eBeamHi = 7.0;
    
	if( (evt.N(KPlus)==1) && (evt.N(Proton)==1) && (evt.N(PiMinus)==1) )
	{
        
		float tpho;
		clasTAGR_t *TAGR = (clasTAGR_t *)getBank(&bcs_,"TAGR");
		clasBID_t *TBID  = (clasBID_t *)getBank(&bcs_,"TBID");
		clasHEVT_t *HEVT = (clasHEVT_t *)getBank(&bcs_,"HEVT");

		if(!TAGR || !TBID || !HEVT) 
		return(NULL);

		threeVec evtVert=evt.V();
		tagr_t *tagr = my_get_photon_tagr(TAGR, TBID, evtVert);  //jb v13 calling it

		double beamp = -1000.0;
		if(tagr)
		{
			//eid = tagr->e_id;
			beamp = tagr->erg;
			//jb v12    wo_beamp = tagr->erg;
			tpho=tagr->tpho; //jb npho
		}
		beam.set(beamp,threeVec(0.0,0.0,beamp));
		
		
		
		kp_particle = evt.cp(KPlus,1);
		p_particle = evt.cp(Proton,1);
		km_particle = evt.cp(KMinus,1);
		
		kp = kp_particle.p();
		p = p_particle.p();
		km = km_particle.p();
		kpLab = kp;
		pLab = p;
		kmLab = km;
		//beam = evt.getBeam(eBeamLo,eBeamHi);
		target = evt.target().get4P();

		pmass = p_particle.mass();
		kpmass = kp_particle.mass();
		
		//Y = beam + target - kp;
		//X = beam + target - p;
		Y = p + km;
		X = kp + km;
		YLab = Y;
		XLab = X;

		beamLab = beam;
		    
		double ebeam = beam.t();
		double mm2pkp = (beam + target - p - kp).lenSq(); //should be mass of km
		double mm2pkpkm = (beam + target - p - kp - km).lenSq(); //should be 0 or mass of pion
		double mm2p = (beam + target - p).lenSq(); //should be mass of X (meson)
		double mm2kp = (beam + target - kp).lenSq(); //should be mass of Y (baryon)
		double t = (beam-kp).lenSq(); //mandelstam variables in vertex IN: photon + target, OUT: X + recoil proton
		double t2 = (beam-X).lenSq();
		double s = (beam+target).lenSq();
		double u = (beam-Y).lenSq();
		double tZ = (beam-kp).lenSq();
		double sZ = (beam+p).lenSq();
		double xk2 = (sZ - pow((pmass - kpmass),2.0)) * (sZ + pow((pmass - kpmass),2.0)) / (4.0 * sZ);
		double Z = 1.0 + (tZ / (2.0 * xk2));
		int Nkm = evt.N(KMinus);
		int Npim = evt.N(PiMinus);
		double pE = p.t(), ppx = p.x(), ppy = p.y(), ppz = p.z();
		double kpE = kp.t(), kppx = kp.x(), kppy = kp.y(), kppz = kp.z();
		double kmpx = km.x(), kmpy = km.y(), kmpz = km.z();
		double kmE = km.t();
		double missp2 = pow(ppx+kppx+kmpx,2.0)+pow(ppy+kppy+kmpy,2.0)+pow(ppz+kppz+kmpz-ebeam,2.0); //missing momentum
		double misspZ2 = pow(ppz+kppz+kmpz-ebeam,2.0);
		double misspT2 = pow(ppx+kppx+kmpx,2.0)+pow(ppy+kppy+kmpy,2.0);
		double invm2kpkm = (kp + km).lenSq(); //invariant mass of X (meson)
		double invm2pkm = (p + km).lenSq(); //invariant mass of Y (baryon)

		ret = ebeam > -1000.0 && fabs(evt.vtime() - evt.stVtime()) < 2.5;
		
		if(ret)
		{
			cout << "PKP "; 
			//.................ANALYSIS IN LAB FRAME.........................................................
			processGeneralHeader(evt);
			cout << tpho << " ";
			cout << hel(HEVT) << " ";

			processTrack(p_particle);
			processTrack(kp_particle);
			processTrack(km_particle);

			cout << mm2pkpkm << " " << mm2pkp << " " << mm2p << " " << mm2kp << " ";
			cout << missp2 << " " << misspZ2 << " " << misspT2 << " "; //Missing Momentums
			cout << invm2kpkm << " " << invm2pkm << " ";
			cout << t << " " << t2 << " " << s << " " << u << " "; //Momentum X-fers
			cout << Nkm << " " << Npim << " ";
			cout << pE << " " << ppx << " " << ppy << " " << ppz << " ";
			cout << kpE << " " << kppx << " " << kppy << " " << kppz << " ";
			cout << kmE << " " << kmpx << " " << kmpy << " " << kmpz << " ";
			cout << tZ << " " << sZ << " " << xk2 << " " << Z << " " << endl;
		}
    	}
	return ret;
}


int printGeneralLabels(char *c)
{
    if ((strcmp(c, "pkp") == 0)) 
	{
		int nlab = 0;
        	cout << "Labels for pK+ (pkp):" << endl;
		
		printGeneralHeaderLabels(&nlab);
		cout << ++nlab <<"\tTphoton {tpho}" << endl;
		cout << ++nlab << "\tBeam Helicity {hel}" <<endl;

		printTrackLabels(&nlab,"PLab","_p");
		printTrackLabels(&nlab,"K+Lab","_kp");
		printTrackLabels(&nlab,"K-Lab","_km");

		cout << ++nlab << "\tMM^2pK+K- {mm2pkpkm}" << endl;
        	cout << ++nlab << "\tMM^2pK+ {mm2pkp}" << endl;
        	cout << ++nlab << "\tMM^2p {mm2p}" << endl;
		cout << ++nlab << "\tMM^2k+ {mm2kp}" << endl;
		cout << ++nlab << "\tMP^2 {missp2}" << endl; //Missing p (off all detected particles)
		cout << ++nlab << "\tMPZ^2 {misspz2}" << endl; //Missing p_z (same as above)
		cout << ++nlab << "\tMPT^2 {misspt2}" << endl; //Missing p_transverse (same as above)
		cout << ++nlab << "\tInvM^2K+K- {invm2kpkm}" << endl;
		cout << ++nlab << "\tInvM^2pK- {invm2pkm}" << endl;
		
		cout << ++nlab << "\ttkp {tkp}" << endl;
		cout << ++nlab << "\ttkpkm {tkpkm}" << endl;
		cout << ++nlab << "\ts {s}" << endl;
		cout << ++nlab << "\tu {u}" << endl;
		
		cout << ++nlab << "\tNK- {Nkm}" << endl;
		cout << ++nlab << "\tNpi- {Npim}" << endl;
		
		cout << ++nlab << "\tPEnergy {p_E_lab}" << endl;
		cout << ++nlab << "\tPpx {p_px_lab}" << endl;
		cout << ++nlab << "\tPpy {p_py_lab}" << endl;
		cout << ++nlab << "\tPpz {p_pz_lab}" << endl;

		cout << ++nlab << "\tK+Energy {kp_E_lab}" << endl;
		cout << ++nlab << "\tK+px {kp_px_lab}" << endl;
		cout << ++nlab << "\tK+py {kp_py_lab}" << endl;
		cout << ++nlab << "\tK+pz {kp_pz_lab}" << endl;

		cout << ++nlab << "\tK-Energy {km_E_lab}" << endl;
		cout << ++nlab << "\tK-px {km_px_lab}" << endl;
		cout << ++nlab << "\tK-py {km_py_lab}" << endl;
		cout << ++nlab << "\tK-pz {km_pz_lab}" << endl;

		cout << ++nlab << "\tt1 {tZ}" << endl;
		cout << ++nlab << "\ts2 {sZ}" << endl;
		cout << ++nlab << "\txk02 {xk2}" << endl;
		cout << ++nlab << "\tZ {Z}" << endl;

    }
    if ((strcmp(c, "DELTA0") == 0)) {
		int nlab = 0;
        cout << "Labels for DELTA0 (delta0):" << endl; 
        cout << ++nlab << "\tMM^2/p1p2pim {mm2p1p2pim}" << endl;
        cout << ++nlab << "\tMass(p1 p2 pim) {mp1p2pim}" << endl;
        cout << ++nlab << "\tMM^2/p1p2 {mm2p1p2}" << endl;
        cout << ++nlab << "\tMass(p1 p2) {mp1p2}" << endl;
        cout << ++nlab << "\tMM^2/p1pim {mm2p1pim}" << endl;
        cout << ++nlab << "\tMass(p1 pim) {mp1pim}" << endl;
        cout << ++nlab << "\tMM^2/p2pim {mm2p2pim}" << endl;
        cout << ++nlab << "\tMass(p2 pim) {mp2pim}" << endl;
        cout << ++nlab << "\tMM^2/p1 {mm2p1}" << endl;
        cout << ++nlab << "\tMM^2/p2 {mm2p2}" << endl;
        cout << ++nlab << "\tMM^2/pim {mm2pim}" << endl;
        cout << ++nlab << "\tMass(nbar pim)const  {mnbarpimconst}" << endl;

        cout << ++nlab << "\tMM^2/p1p2pim {mm2p1p2pimecor}" << endl;
        cout << ++nlab << "\tMM^2/p1p2 {mm2p1p2ecor}" << endl;
        cout << ++nlab << "\tMM^2/p1pim {mm2p1pimecor}" << endl;
        cout << ++nlab << "\tMM^2/p2pim {mm2p2pimecor}" << endl;
        cout << ++nlab << "\tMM^2/p1 {mm2p1ecor}" << endl;
        cout << ++nlab << "\tMM^2/p2 {mm2p2ecor}" << endl;
        cout << ++nlab << "\tMM^2/pim {mm2pimecor}" << endl;
            
        
        cout << ++nlab << "\tE of beam {ebeam}" << endl;
        cout << ++nlab << "\tE of beam {ebeamecor}" << endl;
        cout << ++nlab << "\tx {x}" << endl;
        cout << ++nlab << "\ty {y}" << endl;
        cout << ++nlab << "\tz {z}" << endl;
        cout << ++nlab << "\tvtime {vtime}" << endl;
        cout << ++nlab << "\tstVtime {stvtime}" << endl;
        cout << ++nlab << "\tvtime - stVtime {delvt}" << endl;
        
        printTrackLabels(&nlab,"P1","p1");
        printTrackLabels(&nlab,"P2","p2");
        printTrackLabels(&nlab,"Pi-","pim");

        cout << ++nlab << "\tp missing Nbar {pmnbar}" << endl;
        cout << ++nlab << "\tcos(theta) missing Nbar {ctmnbar}" << endl;
        cout << ++nlab << "\tphi/PI missing Nbar {phimnbar}" << endl;
        cout << ++nlab << "\tp missing Nbar {pmnbar}" << endl;
        cout << ++nlab << "\tcos(theta) missing Nbar {ctmnbar}" << endl;
        cout << ++nlab << "\tphi/PI missing Nbar {phimnbar}" << endl;
        cout << ++nlab << "\tmissing pt {mptconst}" << endl;
        cout << ++nlab << "\tmissing energy {menergyconst}" << endl;
        
        cout << ++nlab << "\tNPhotons 0 {np0}" << endl;
        cout << ++nlab << "\tNPhotons 1 {np1}" << endl;
        cout << ++nlab << "\tNPhotons 2 {np2}" << endl;
        cout << ++nlab << "\tN Kaons {nkaons}" << endl;
        cout << ++nlab << "\tN Pions {npions}" << endl;
        cout << ++nlab << "\tN Photons {ngamma}" << endl;
        
        cout << ++nlab << "\tp of p1 CM {pp1cm}" << endl;
        cout << ++nlab << "\tcos theta p1 CM {ctp1cm}" << endl;
        cout << ++nlab << "\tphi/PI p1 CM {phip1cm}" << endl;
        
        cout << ++nlab << "\tp of p2 CM {pp2cm}" << endl;
        cout << ++nlab << "\tcos theta p2 CM {ctp2cm}" << endl;
        cout << ++nlab << "\tphi/PI p2 CM {phip2cm}" << endl;
        
        cout << ++nlab << "\tp of pim CM {ppimcm}" << endl;
        cout << ++nlab << "\tcos theta pim CM {ctpimcm}" << endl;
        cout << ++nlab << "\tphi/PI pim CM {phipimcm}" << endl;
        
        cout << ++nlab << "\tp of nbar CM {pnbarcm}" << endl;
        cout << ++nlab << "\tcos theta nbar CM {ctnbarcm}" << endl;
        cout << ++nlab << "\tphi/PI nbar CM {phinbarcm}" << endl;
    }
    return(1);
}

void processGeneralHeader(clasEvent &evt) 
{

	pHeader(evt);
	cout << ~(evt.beam().get4P() + evt.target().get4P()) << " ";
	cout << evt.beam().get4P().t() << " ";
	cout << evt.x() << " " << evt.y() << " " << evt.z() << " ";
	cout << evt.N(-1) << " " << evt.N(0) << " " << evt.N(1) << " " << evt.N(Gamma) << " "; //# of photons is here
	cout << evt.vtime() << " " << evt.stVtime() << " " << evt.vtime() - evt.stVtime() << " ";
}

void printGeneralHeaderLabels(int *nlab) 
{
	cout << ++(*nlab) << "\tRun {run}" << endl;
	cout << ++(*nlab) << "\tEvent {evt}" << endl;
	cout << ++(*nlab) << "\ttrigger {trig}" << endl;
	cout << ++(*nlab) << "\tsqrt(s) {wcm}" << endl;
	cout << ++(*nlab) << "\tE of beam {ebeam}" << endl;
	cout << ++(*nlab) << "\tx {x}" << endl;
	cout << ++(*nlab) << "\ty {y}" << endl;
	cout << ++(*nlab) << "\tz {z}" << endl;
	cout << ++(*nlab) << "\t# of q=-1 {nm}" << endl;
	cout << ++(*nlab) << "\t# of q=0 {n0}" << endl;
	cout << ++(*nlab) << "\t# of q=+1 {np}" << endl;
	cout << ++(*nlab) << "\t# of gamma {photons}" << endl; //# of photons
	cout << ++(*nlab) << "\tvtime {vtime}" << endl;
	cout << ++(*nlab) << "\tstVtime {stvtime}" << endl;
	cout << ++(*nlab) << "\tvtime - stVtime {delvt}" << endl;
}

void processTrack(clasParticle &cp) 
{
	int scid = cp.scPaddleId();
	int sect = cp.scPaddleId_sector();
	int q = cp.Q();
	double tof = cp.scTOF();
	double tofexp = cp.scTOFexpected();
	
	fourVec p = cp.p();
	cout << ~p.V() << " " << p.V().cosTheta() << " " << p.V().phi()/M_PI << " " <<  cp.stVtime() << " ";
	cout << cp.mass() << " " << cp.tofLength() <<" "<< cp.beta() << " " << cp.Beta() << " ";
	cout << scid << " " << sect << " " << tof << " " << tofexp << " " << q << " "; //SCID, TOF, TOF expected
	
	if(q > 0) //looking at charged particles anyway
		q = 0;
	else
		q = 1;	
	
	if(res[q][sect-1][scid-1] > 0.0)
		cout << fabs(tof-tofexp) / res[q][sect-1][scid-1] << " ";
	else
		cout << "1000.0 ";
	
	if (cp.isSThit()) {
		cout << " 1 " << cp.SThit().time() << " ";
        
	}
	else {
		cout << " 0 0 ";
	}
	if (cp.isSChit()) {
		cout << " 1 " << cp.SChit().time() << " " << cp.SChit().energy() << " ";
        
	}
	else {
		cout << " 0 0 0 ";
	}
}

void processTrack(fourVec p, int ck) //overloading processTrack to include a different momentum not in the lab frame
{
	if(ck == 1)
	cout << ~p.V() << " " << p.V().cosTheta() << " " << p.V().phi()/M_PI << " ";
	else
	cout << "-1000.0 -1000.0 -1000.0 ";
}

void printTrackLabels(int *nlab, char *id1, char *id2) 
{
	cout << ++(*nlab) << "\tp " << id1 << " {p" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tcos(theta) " << id1 << " {ct" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tphi/PI " << id1 << " {phi" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tstVtime " << id1 << "{stV" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tmass " << id1 << " {m" << id2 << "}" << endl;
    	cout << ++(*nlab) << "\tTOF Length " << id1 << " {toflen" << id2 << "}" << endl;
    	cout << ++(*nlab) << "\tbeta " << id1 << " {b" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tBeta " << id1 << " {B" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tSCID " << id1 << " {scid" << id2 << "}" << endl; //SCID
	cout << ++(*nlab) << "\tSector " << id1 << " {sector" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tTOF " << id1 << " {tof" << id2 << "}" << endl; //TOF
	cout << ++(*nlab) << "\tTOF Expected " << id1 << " {tof_exp" << id2 << "}" << endl; //TOF Expected
	cout << ++(*nlab) << "\tCharge " << id1 << " {q" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tDeviation " << id1 << " {dev" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tis sthit " << id1 << " {isst" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tst time " << id1 << " {stt" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tis schit " << id1 << " {issc" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tsc time " << id1 << " {sct" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tsc energy " << id1 << " {scE" << id2 << "}" << endl;
	
}

void printFourVecLabels(int *nlab, char *id1, char *id2)
{
	cout << ++(*nlab) << "\tp " << id1 << " {p" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tcos(theta) " << id1 << " {ct" << id2 << "}" << endl;
	cout << ++(*nlab) << "\tphi/PI " << id1 << " {phi" << id2 << "}" << endl;
}


double twoThreeVecAngle(threeVec v1, threeVec v2){
    double dot_product = v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
    double magnitude = v1.r() * v2.r();                                      
    return dot_product/magnitude;
}

//*******************jb npho********************************************
int  npho( clasTAGR_t *TAGR, float tpho, int nb){  //jb npho func
    int nph=0; //jb npho
    for(int k=0;k<TAGR->bank.nrow;k++){
        if (abs(tpho - TAGR->tagr[k].tpho) < (0.05+2.004*nb)) {  //jb npho  
            nph=nph+1;
        }
    }
    return(nph);
}


//tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID){ 
tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID, threeVec myVert){  //jb v13
    
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
    
    for (i=0;i<TBID->bank.nrow;i++){
        int trk_ind=TBID->bid[i].track;
        if(trk_ind){     
            //jb v13      tprop=(TBTR->tbtr[trk_ind-1].vert.z - g12targz)/SPEED_OF_LIGHT*1e9;  //jb v11 i think i need to take this out
            tprop=(myVert.z() - g12targz)/LIGHT_SPEED;  //jb v13
            //cout<<"myVert.z()=" << myVert.z() <<" :  TBTR->tbtr[trk_ind-1].vert.z="<< TBTR->tbtr[trk_ind-1].vert.z<<endl; //jb v13 just a check
            if (TBID->bid[i].st.stat){       
                
                float mytime=-1000; //jb v14
                float myenergy=-1000; //jb v14
                
                for(j=0;j<TAGR->bank.nrow;j++){
                    float diff=fabs(TBID->bid[i].st.vtime-(TAGR->tagr[j].tpho+tprop));
                    //jb v14     if (diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff
                    //jb v14	&& (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15)){    	   
                    //cout <<abs(TAGR->tagr[j].tpho - tagr->tpho)<<endl;
                    if (( diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff || (abs(TAGR->tagr[j].tpho - mytime)<0.011&& (TAGR->tagr[j].erg) > myenergy)  )  &&  (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15)){  //jb v14
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




// debugging

