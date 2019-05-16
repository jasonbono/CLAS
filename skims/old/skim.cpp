// this is the other skim
//OCT 4, i picked this up from johann he directed me to the g12 skim in
//https://jlabsvn.jlab.org/svnroot/clas/trunk/analysis/view
//

// to find editing my me look for //JB\\


/**
 * skim.cpp
 **/

#include <csignal>
#include <iostream>
#include <string>
#include <unistd.h>

extern "C" {
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

using namespace std;

/**
 * the bos common
 **/
BOSbank bcs_;
BOSbank wcs_;

int CurrentRun = 0;
int CurrentEvent = 0;

bool IsInTopology(clasEvent &event, string topology) {
    int n = event.N();
    int np = event.N(Proton);
    int npip = event.N(PiPlus);
    int npim = event.N(PiMinus);
    int nkp = event.N(KPlus);
    int nkm = event.N(KMinus);
    /*int npi0 = event.N(Pi0);
    int neta = event.N(Eta);
    int ngamma = event.N(Gamma);
    int nneut = event.N(Neutron);
    int npbar = event.N(AntiProton);
    int nem = event.N(Electron);
    int nep = event.N(Positron);*/
    if(topology == "kpkppim_excl" && n >= 3 && nkp >= 2 && npim >= 1) {
       return true;  
    }  
    else {
      return false;
    }
}

/**
 * Fault handlers
 **/
static void signalINT(int isig) {
    cerr << "Run/Event: " << CurrentRun
        << " " << CurrentEvent
        << endl;
    exit(0);
}
static void signalSEGV(int isig) {
    cerr << "signalSEGV: Caught signal " << endl;
    cerr << "Run/Event: " << CurrentRun
        << " " << CurrentEvent
        << endl;
    exit(0);
}
void installFaultHandlers() {
    signal(SIGINT,signalINT);
    signal(SIGSEGV,signalSEGV);
}

void printUsage(char *processName) {
    cerr << processName << " [options] -o output-file input-files ..." << endl;
    cerr << "\t[-m#]\t\tprocess only # events" << endl;
    cerr << "\t[-v]\t\tverbose mode" << endl;
    cerr << "\t[-q]\t\tquiet (batch) mode" << endl;
    cerr << "\t[-o]<string>\toutput file (default: out.bos)\n";
    cerr << "\t[-t]<string>\twhere <string> is one of:\n";
    cerr << "\t\tppippim_excl    proton pi+ pi- exclusive (default)\n";
    cerr << "\t\tkpk_incl        K+ Kaon inclusive\n";
    cerr << "\t\tppippimkl_excl  proton pi+ pi- missing(K_long) exclusive\n";
    cerr << "\t\tppik_excl       proton pion kaon exclusive\n";
    cerr << "\t\tkkpp            K+ K+ proton proton\n";
    cerr << "\t[-h]\t\tprint this message" << endl;
}

int StartRun(int runNo) {
    int static CurrentRun = -1;
    if(CurrentRun != runNo) {
        CurrentRun = runNo;
    }
    return 0;
}

int main(int argc,char** argv) {
    /**
     * argument handler
     **/
    char *argptr;
    int max = 0;
    bool quiet = false;
    bool verbose = false;
    clasOutput coutput;
    string topology = "ppippim";

    for(int i=1; i<argc; ++i) {
        argptr = argv[i];
        if(*argptr == '-') {
            argptr++;
            switch(*argptr) {
case 'm': max = atoi(++argptr); break;
case 'q': quiet = true; break;
case 'v': verbose = true; break;
case 'o':
    if (*(++argptr)) {
        unlink(argptr);
        int status = coutput.open(argptr, 9);
        cerr << "output file: " << argptr << endl;
    }
    break;
case 't': topology = string(++argptr); break;
case 'h': printUsage(argv[0]); exit(0); break;
                default:
                    cerr << "unrecognized argument: " << argptr << endl;
                    break;
            }
        }
    }

    if(topology == "kpkppim_excl") {
        clog << "K+ K+ Pi- Events.\n"
            << "Cuts:\n"

    } else if(topology == "kpk_incl") {
        clog << "K+ Kaon Inclusive Events.\n";
    } else if(topology == "ppippimkl_excl") {
        clog << "Proton Pi+ Pi- Missing(K_long) Exclusive Events.\n"
            << "\tCut around missing mass squared\n"
            << "\toff proton pi+ pi- = 0.248 +/- 0.02\n";
    } else if(topology == "ppik_excl") {
        clog << "Proton Kaon Pion Exclusive Events.\n"
            << "Cuts:\n"
            << "\tmissing mass squared        < 0.2\n"
            << "\tmissing momentum z          < 0.5\n"
            << "\tmissing momentum transverse < 0.15\n";
    }
    installFaultHandlers();

    /// Initialize BOS
    int MaxBanks = 1000;
    bnames_(&MaxBanks);
    initbos();
    configure_banks(stderr,0);

    clasHEAD_t *HEAD;

    size_t nFiles = 0;
    size_t nEvents = 0;
    size_t nProc = 0;

    for(int i=1; i<argc; ++i) {
        argptr = argv[i];
        if(*argptr != '-') {
            cerr << "reading bos file: " << argptr << endl;
            if(!quiet) clog << "events: processed / total / files\n";
            clasEvent event(argptr, &bcs_, 1, 0);
            ++nFiles;
            if(event.status()) {
                while((max ? nEvents < max : 1) && event.read(1)) {
                    if(event.type() == 1) {
if(HEAD = (clasHEAD_t*) getBank(&bcs_, "HEAD")) {
    CurrentRun   = HEAD->head[0].nrun;
    CurrentEvent = HEAD->head[0].nevent;
    StartRun(HEAD->head[0].nrun);
    try {
        if(IsInTopology(event, topology)) {
            coutput.write(&bcs_);
            ++nProc;
        }
    } catch(exception &e) {
        cerr << "exception caught: " << e.what() << endl;
    }
}
                    }
                    event.clean();
                    if(!(++nEvents % 1000) && !quiet) {
                        clog << nProc
                            << '\t' << nEvents
                            << '\t' << nFiles
                            << '\r';
                    }
                }
                if(!quiet) {
                    clog << nProc
                        << '\t' << nEvents
                        << '\t' << nFiles
                        << endl;
                }
            } else {
                cerr << "unable to open " << argptr << endl;
            }
        }
    }
    if(!quiet) {
        clog << nProc
            << '\t' << nEvents
            << '\t' << nFiles
            << endl;
    }
    coutput.write(&bcs_, "0");
    coutput.close();
    if(!quiet) clog << coutput.name() << " closed" << endl;
    return 0;
}
