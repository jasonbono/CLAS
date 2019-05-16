//generate flat






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

void flat()
{
	
	

	
	
	
	
	
	
	
	
	
	
}