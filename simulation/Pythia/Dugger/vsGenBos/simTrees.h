#if !defined VSBRANCHES
typedef struct {
  int nGen;
  double eGamma;
  double pXGamma;
  double pYGamma;
  double pZGamma;
  double Qsq;
  double vsWeight;
  int kf[200];
  int ks[200];
  int parent[200];
  double E[200];
  double m[200];
  double px[200];
  double py[200];
  double pz[200];
  double vx[200];
  double vy[200];
  double vz[200];
  double charge[200];
} vsGen_t;

typedef struct {
  int nEvent;
  double eGamma;
  double pXGamma;
  double pYGamma;
  double pZGamma;
  double Qsq;
  double vsWeight;
  int kf[200];
  int vsGenIndex[200];
  double E[200];
  double m[200];
  double px[200];
  double py[200];
  double pz[200];
  double vx[200];
  double vy[200];
  double vz[200];
  double charge[200];
} event_t;

#endif

#if !defined VSSTRUCT
void setBranchesT1(TTree *t1, vsGen_t *vsGen){
  t1->Branch("vsGen.nGen",&vsGen->nGen,"nGen/I");
  t1->Branch("vsGen.eGamma",&vsGen->eGamma,"eGamma/D");
  t1->Branch("vsGen.pXGamma",&vsGen->pXGamma,"pXGamma/D");
  t1->Branch("vsGen.pYGamma",&vsGen->pYGamma,"pYGamma/D");
  t1->Branch("vsGen.pZGamma",&vsGen->pZGamma,"pZGamma/D");
  t1->Branch("vsGen.Qsq",&vsGen->Qsq,"Qsq/D");
  t1->Branch("vsGen.vsWeight",&vsGen->vsWeight,"vsWeight/D");
  t1->Branch("vsGen.kf",vsGen->kf,"kf[nGen]/I");
  t1->Branch("vsGen.ks",vsGen->ks,"ks[nGen]/I");
  t1->Branch("vsGen.parent",vsGen->parent,"parent[nGen]/I");
  t1->Branch("vsGen.E",vsGen->E,"E[nGen]/D");
  t1->Branch("vsGen.m",vsGen->m,"m[nGen]/D");
  t1->Branch("vsGen.px",vsGen->px,"px[nGen]/D");
  t1->Branch("vsGen.py",vsGen->py,"py[nGen]/D");
  t1->Branch("vsGen.pz",vsGen->pz,"pz[nGen]/D");
  t1->Branch("vsGen.vx",vsGen->vx,"vx[nGen]/D");
  t1->Branch("vsGen.vy",vsGen->vy,"vy[nGen]/D");
  t1->Branch("vsGen.vz",vsGen->vz,"vz[nGen]/D");
  t1->Branch("vsGen.charge",vsGen->charge,"charge[nGen]/D");
}

void getBranchesT1(TTree *t1,vsGen_t *vsGen){

  t1->SetBranchAddress("vsGen.nGen",&vsGen->nGen);
  t1->SetBranchAddress("vsGen.eGamma",&vsGen->eGamma);
  t1->SetBranchAddress("vsGen.pXGamma",&vsGen->pXGamma);
  t1->SetBranchAddress("vsGen.pYGamma",&vsGen->pYGamma);
  t1->SetBranchAddress("vsGen.pZGamma",&vsGen->pZGamma);
  t1->SetBranchAddress("vsGen.Qsq",&vsGen->Qsq);
  t1->SetBranchAddress("vsGen.vsWeight",&vsGen->vsWeight);
  t1->SetBranchAddress("vsGen.kf",vsGen->kf);
  t1->SetBranchAddress("vsGen.ks",vsGen->ks);
  t1->SetBranchAddress("vsGen.parent",vsGen->parent);
  t1->SetBranchAddress("vsGen.E",vsGen->E);
  t1->SetBranchAddress("vsGen.m",vsGen->m);
  t1->SetBranchAddress("vsGen.px",vsGen->px);
  t1->SetBranchAddress("vsGen.py",vsGen->py);
  t1->SetBranchAddress("vsGen.pz",vsGen->pz);
  t1->SetBranchAddress("vsGen.vx",vsGen->vx);
  t1->SetBranchAddress("vsGen.vy",vsGen->vy);
  t1->SetBranchAddress("vsGen.vz",vsGen->vz);
  t1->SetBranchAddress("vsGen.charge",vsGen->charge);
}

void setBranchesT2(TTree *t2, vsGen_t *vsGen, event_t *event){
  t2->Branch("vsGen.nGen",&vsGen->nGen,"nGen/I");
  t2->Branch("vsGen.eGamma",&vsGen->eGamma,"eGamma/D");
  t2->Branch("vsGen.pXGamma",&vsGen->pXGamma,"pXGamma/D");
  t2->Branch("vsGen.pYGamma",&vsGen->pYGamma,"pYGamma/D");
  t2->Branch("vsGen.pZGamma",&vsGen->pZGamma,"pZGamma/D");
  t2->Branch("vsGen.Qsq",&vsGen->Qsq,"Qsq/D");
  t2->Branch("vsGen.vsWeight",&vsGen->vsWeight,"vsWeight/D");
  t2->Branch("vsGen.kf",vsGen->kf,"kf[nGen]/I");
  t2->Branch("vsGen.ks",vsGen->ks,"ks[nGen]/I");
  t2->Branch("vsGen.parent",vsGen->parent,"parent[nGen]/I");
  t2->Branch("vsGen.E",vsGen->E,"E[nGen]/D");
  t2->Branch("vsGen.m",vsGen->m,"m[nGen]/D");
  t2->Branch("vsGen.px",vsGen->px,"px[nGen]/D");
  t2->Branch("vsGen.py",vsGen->py,"py[nGen]/D");
  t2->Branch("vsGen.pz",vsGen->pz,"pz[nGen]/D");
  t2->Branch("vsGen.vx",vsGen->vx,"vx[nGen]/D");
  t2->Branch("vsGen.vy",vsGen->vy,"vy[nGen]/D");
  t2->Branch("vsGen.vz",vsGen->vz,"vz[nGen]/D");
  t2->Branch("vsGen.charge",vsGen->charge,"charge[nGen]/D");

  t2->Branch("event.nEvent",&event->nEvent,"nEvent/I");
  t2->Branch("event.eGamma",&event->eGamma,"eGamma/D");
  t2->Branch("event.pXGamma",&event->pXGamma,"pXGamma/D");
  t2->Branch("event.pYGamma",&event->pYGamma,"pYGamma/D");
  t2->Branch("event.pZGamma",&event->pZGamma,"pZGamma/D");
  t2->Branch("event.Qsq",&event->Qsq,"Qsq/D");
  t2->Branch("event.vsWeight",&event->vsWeight,"vsWeight/D");
  t2->Branch("event.kf",event->kf,"kf[nEvent]/I");
  t2->Branch("event.vsGenIndex",event->vsGenIndex,"vsGenIndex[nEvent]/I");
  t2->Branch("event.E",event->E,"E[nEvent]/D");
  t2->Branch("event.m",event->m,"m[nEvent]/D");
  t2->Branch("event.px",event->px,"px[nEvent]/D");
  t2->Branch("event.py",event->py,"py[nEvent]/D");
  t2->Branch("event.pz",event->pz,"pz[nEvent]/D");
  t2->Branch("event.vx",event->vx,"vx[nEvent]/D");
  t2->Branch("event.vy",event->vy,"vy[nEvent]/D");
  t2->Branch("event.vz",event->vz,"vz[nEvent]/D");
  t2->Branch("event.charge",event->charge,"charge[nEvent]/D");
}

void getBranchesT2(TTree *t2, vsGen_t *vsGen, event_t *event){
  t2->SetBranchAddress("vsGen.nGen",&vsGen->nGen);
  t2->SetBranchAddress("vsGen.eGamma",&vsGen->eGamma);
  t2->SetBranchAddress("vsGen.pXGamma",&vsGen->pXGamma);
  t2->SetBranchAddress("vsGen.pYGamma",&vsGen->pYGamma);
  t2->SetBranchAddress("vsGen.pZGamma",&vsGen->pZGamma);
  t2->SetBranchAddress("vsGen.Qsq",&vsGen->Qsq);
  t2->SetBranchAddress("vsGen.vsWeight",&vsGen->vsWeight);
  t2->SetBranchAddress("vsGen.kf",vsGen->kf);
  t2->SetBranchAddress("vsGen.ks",vsGen->ks);
  t2->SetBranchAddress("vsGen.parent",vsGen->parent);
  t2->SetBranchAddress("vsGen.E",vsGen->E);
  t2->SetBranchAddress("vsGen.m",vsGen->m);
  t2->SetBranchAddress("vsGen.px",vsGen->px);
  t2->SetBranchAddress("vsGen.py",vsGen->py);
  t2->SetBranchAddress("vsGen.pz",vsGen->pz);
  t2->SetBranchAddress("vsGen.vx",vsGen->vx);
  t2->SetBranchAddress("vsGen.vy",vsGen->vy);
  t2->SetBranchAddress("vsGen.vz",vsGen->vz);
  t2->SetBranchAddress("vsGen.charge",vsGen->charge);

  t2->SetBranchAddress("event.nEvent",&event->nEvent);
  t2->SetBranchAddress("event.eGamma",&event->eGamma);
  t2->SetBranchAddress("event.pXGamma",&event->pXGamma);
  t2->SetBranchAddress("event.pYGamma",&event->pYGamma);
  t2->SetBranchAddress("event.pZGamma",&event->pZGamma);
  t2->SetBranchAddress("event.Qsq",&event->Qsq);
  t2->SetBranchAddress("event.vsWeight",&event->vsWeight);
  t2->SetBranchAddress("event.kf",event->kf);
  t2->SetBranchAddress("event.vsGenIndex",event->vsGenIndex);
  t2->SetBranchAddress("event.E",event->E);
  t2->SetBranchAddress("event.m",event->m);
  t2->SetBranchAddress("event.px",event->px);
  t2->SetBranchAddress("event.py",event->py);
  t2->SetBranchAddress("event.pz",event->pz);
  t2->SetBranchAddress("event.vx",event->vx);
  t2->SetBranchAddress("event.vy",event->vy);
  t2->SetBranchAddress("event.vz",event->vz);
  t2->SetBranchAddress("event.charge",event->charge);
}
#endif
