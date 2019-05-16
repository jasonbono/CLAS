#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ntypes.h>
#include <bostypes.h>
#include <errno.h>
#include <math.h>
#define VSSTRUCT
#include "simTrees.h"
#undef VSSTRUCT

//void bnames_(int *);
//void initbos(void);
//int configure_banks(FILE *out, int verbose);
//void bankList(BOSbank *bcs, char *list, char *banklist);

void loadBos(int eventNumber,int numParticles,vsGen_t *vsGen){

  //---> Get the HEAD bank
  clasHEAD_t *HEAD = NULL;
  HEAD = makeBank(&bcs_,"HEAD",0,sizeof(head_t)/4,1);

  clasMCTK_t *MCTK = NULL;
  MCTK = makeBank(&bcs_,"MCTK",0,sizeof(mctk_t)/4,numParticles);

  clasMCVX_t *MCVX = NULL;
  MCVX = makeBank(&bcs_,"MCVX",0,sizeof(mcvx_t)/4,numParticles);

  clasTAGR_t *TAGR = NULL;
  TAGR = makeBank(&bcs_,"TAGR",0,sizeof(tagr_t)/4,1);

  //clasPART_t *PART = NULL;
  //PART = makeBank(&bcs_,"PART",1,sizeof(part_t)/4,1);

  HEAD->head[0].version = 1;
  HEAD->head[0].nrun = 1;
  HEAD->head[0].nevent = eventNumber;
  HEAD->head[0].type = -4;
  HEAD->head[0].roc = 0;
  HEAD->head[0].evtclass = 15;
  HEAD->head[0].trigbits = 0;

  //if (eventNumber==1) HEAD->head[0].evtclass = 18 ;

  double pVal,cxVal,cyVal,czVal;
  int i,j,k,chargeVal;
  for(i = 0; i < numParticles; i++) {

    TAGR->tagr[i].stat = 15;
    TAGR->tagr[i].erg = vsGen->eGamma;
    //TAGR->tagr[i].erg = 1.050;
    //TAGR->tagr[i].t_id = 73;
    //TAGR->tagr[i].e_id = 544;

    MCVX->mcvx[i].x = 0.0;
    MCVX->mcvx[i].y = 0.0;
    MCVX->mcvx[i].z = 0.0;
    MCVX->mcvx[i].tof = 0.0;
    MCVX->mcvx[i].flag = 0;

    pVal =  sqrt(pow(vsGen->px[i],2)+pow(vsGen->py[i],2)+pow(vsGen->pz[i],2));
    if (pVal !=0) {
      cxVal = vsGen->px[i]/pVal;
      cyVal = vsGen->py[i]/pVal;
      czVal = vsGen->pz[i]/pVal;
    } else {
      cxVal = 0.0;
      cyVal = 0.0;
      czVal = 0.0;
    }
    MCTK->mctk[i].cx = cxVal;
    MCTK->mctk[i].cy = cyVal;
    MCTK->mctk[i].cz = czVal;
    MCTK->mctk[i].pmom = pVal;
    MCTK->mctk[i].mass = vsGen->m[i];
    MCTK->mctk[i].charge = vsGen->charge[i];
    MCTK->mctk[i].id = vsGen->kf[i];
    MCTK->mctk[i].flag = 1;
    MCTK->mctk[i].beg_vtx = 1;
    MCTK->mctk[i].end_vtx = 0;
    MCTK->mctk[i].parent = vsGen->parent[i];




  }
  putBOS(&bcs_, 2, "C"); 
  dropAllBanks(&bcs_,"C");
  cleanBanks(&bcs_); 

}
