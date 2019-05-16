/* july 13 2011. jason bono
this code was written to get pion angles with normal plane and lambda angles with normal plane
normal plane was calculated in CM frame and in lab frame. so a total of four results
*/
#include <Riostream.h>
#include <TMath.h>
#include "TMath.h"
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRotation.h>
#include <TLorentzRotation.h>
#include <assert.h>
gSystem.Load("libPhysics.so");
	
void 4results(){
       	
TFile *f = new TFile("newer.root","UPDATE");
TTree *newt = (TTree*)f->Get("new");

//define momentum 4vectors, lab3vectors, CM3vectors, cascade3vectors, componets and masses
// electron, proton, kaon1, kaon2, cascade, pi-, lambda, ghost
TLorentzVector Fe;
TLorentzVector Fpr;
TLorentzVector Fk1;
TLorentzVector Fk2;
TLorentzVector Fcas;
TLorentzVector Fpi;
TLorentzVector Fl;
 TLorentzVector Fghost;

TVector3 Te;
TVector3 Tpr;
TVector3 Tk1;
TVector3 Tk2;
TVector3 Tcas;
TVector3 Tpi;
TVector3 Tl;
TVector3 Tghost;

TVector3 TeCM;
TVector3 TprCM;
TVector3 Tk1CM;
TVector3 Tk2CM;
TVector3 TcasCM;
TVector3 TpiCM;
TVector3 TlCM;
TVector3 TghostCM;

TVector3 TeCAS;
TVector3 TprCAS;
TVector3 Tk1CAS;
TVector3 Tk2CAS;
TVector3 TcasCAS;
TVector3 TpiCAS;
TVector3 TlCAS;
TVector3 TghostCAS;

Float_t Xe;
Float_t Ye;
Float_t Ze;
Float_t Xpr;
Float_t Ypr;
Float_t Zpr;
Float_t Xk1;
Float_t Yk1;
Float_t Zk1;
Float_t Xk2;
Float_t Yk2;
Float_t Zk2;
Float_t Xcas;
Float_t Ycas;
Float_t Zcas;
Float_t Xpi;
Float_t Ypi;
Float_t Zpi;
Float_t Xl;
Float_t Yl;
Float_t Zl;

Float_t Me=0.0005109;
Float_t Mpr=0.938272;
Float_t Mk=0.493667;
Float_t Mcas=1.32131;
Float_t Mpi=0.13957;
Float_t Ml=1.115683;

 // normalized momenta
TVector3 nTe;
TVector3 nTpr;
TVector3 nTk1;
TVector3 nTk2;
TVector3 nTcas;
TVector3 nTpi;
TVector3 nTl;

//Boost vectors
 TVector3 Bcas;
 TVector3 Bcm;

//Production plane
 TVector3 LABnorm;
 TVector3 CMnorm;

// branch varables
Float_t fixbeam2;
Float_t pkp1;
Float_t kp1labtheta;
Float_t kp1labphi;
Float_t pkp2;
Float_t kp2labtheta;
Float_t kp2labphi;
Float_t ppim;
Float_t pilabtheta;
Float_t pilabphi;
newt->SetBranchAddress("fixbeam2", &fixbeam2);
newt->SetBranchAddress("pkp1", &pkp1);
newt->SetBranchAddress("kp1labtheta", &kp1labtheta);
newt->SetBranchAddress("kp1labphi", &kp1labphi);
newt->SetBranchAddress("pkp2", &pkp2);
newt->SetBranchAddress("kp2labtheta", &kp2labtheta);
newt->SetBranchAddress("kp2labphi", &kp2labphi);
newt->SetBranchAddress("ppim", &ppim);
newt->SetBranchAddress("pilabtheta", &pilabtheta);
newt->SetBranchAddress("pilabphi", &pilabphi);


 /*
adding: 
"PIangle" "LAMBangle" "PIangleLAB" "LAMBangleLAB" --> all 4 quantities of intrest here. 
"LABcasDOTnormLAB" "LABcasDOTnormCM" --> make sure cascade is in production plane in both calculations.
"Epil" "Erestcas" ---> this is total energy of pi and lambda in rest of cascade. and cas rest energy 
"ZprCM" "ZeCM" "Eghost"
"ZpiLAB" -- the z component of pion momentum in the lab frame
"normdiff"-- dot of the normal to produciton plane vectors defined in lab and cm frames
*/
Float_t PIangle;
Float_t PIangleLAB;
Float_t LAMBangle;
Float_t LAMBangleLAB;
Float_t LABcasDOTnormLAB;
Float_t LABcasDOTnormCM;
Float_t Epil;
Float_t Erestcas;
Float_t Eghost;
Float_t ZprCM;
Float_t ZeCM;
Float_t ZpiLAB;
 Float_t normdiff;
TBranch *PIangleBranch = newt->Branch("PIangle", &PIangle, "PIangle/F");
TBranch *PIangleLABBranch = newt->Branch("PIangleLAB", &PIangleLAB, "PIangleLAB/F");
TBranch *LAMBangleBranch = newt->Branch("LAMBangle", &LAMBangle, "LAMBangle/F");
TBranch *LAMBangleLABBranch = newt->Branch("LAMBangleLAB", &LAMBangleLAB, "LAMBangleLAB/F");
TBranch *LABcasDOTnormLABBranch = newt->Branch("LABcasDOTnormLAB", &LABcasDOTnormLAB, "LABcasDOTnormLAB/F");
TBranch *LABcasDOTnormCMBranch = newt->Branch("LABcasDOTnormCM", &LABcasDOTnormCM, "LABcasDOTnormCM/F");
TBranch *EpilBranch = newt->Branch("Epil", &Epil, "Epil/F");
TBranch *ErestcasBranch = newt->Branch("Erestcas", &Erestcas, "Erestcas/F");
TBranch *EghostBranch = newt->Branch("Eghost", &Eghost, "Eghost/F");
TBranch *ZprCMBranch = newt->Branch("ZprCM", &ZprCM, "ZprCM/F");
TBranch *ZeCMBranch = newt->Branch("ZeCM", &ZeCM, "ZeCM/F");
TBranch *ZpiLABBranch = newt->Branch("ZpiLAB", &ZprCM, "ZpiLABCM/F");
TBranch *normdiffBranch = newt->Branch("normdiff", &normdiff, "normdiff/F");

Int_t nentries = (Int_t)newt->GetEntries(); 
for (Int_t i=0; i<nentries; i++) {
newt->GetEntry(i);


//ELECTRON 3&4-vec 
 Xe=0;
 Ye=0;
 Ze=fixbeam2; 
 Te.SetXYZ(Xe,Ye,Ze);
 Fe.SetXYZM(Xe,Ye,Ze,Me);

//PROTON 3&4-vec
 Xpr=0;
 Ypr=0;
 Zpr=0;
 Tpr.SetXYZ(Xpr,Ypr,Zpr);
 Fpr.SetXYZM(Xpr,Ypr,Zpr,Mpr);

//KAON 3&4-vec
Xk1=pkp1*sin(kp1labtheta)*cos(kp1labphi);
Yk1=pkp1*sin(kp1labtheta)*sin(kp1labphi);
Zk1=pkp1*cos(kp1labtheta);

Tk1.SetXYZ(Xk1,Yk1,Zk1);
Fk1.SetXYZM(Xk1,Yk1,Zk1,Mk);

Xk2=pkp2*sin(kp2labtheta)*cos(kp2labphi);
Yk2=pkp2*sin(kp2labtheta)*sin(kp2labphi);
Zk2=pkp2*cos(kp2labtheta);

Tk2.SetXYZ(Xk2,Yk2,Zk2);
Fk2.SetXYZM(Xk2,Yk2,Zk2,Mk);

//CASCADE 3&4-vec
Tcas = Te + Tpr - Tk1 - Tk2;
Fcas = Fe + Fpr - Fk1 - Fk2;
 

//PION 3&4-vec
Xpi=ppim*sin(pilabtheta)*cos(pilabphi);
Ypi=ppim*sin(pilabtheta)*sin(pilabphi);
Zpi=ppim*cos(pilabtheta);
Tpi.SetXYZ(Xpi,Ypi,Zpi);
Fpi.SetXYZM(PIPX,PIPY,PIPZ,Mpi);

//LAMBDA 3&4-vec
 Tl=Tcas-Tpi;
 Fl=Fcas-Fpi;

//define ghost particle in lab frame and obtain CM boost vector to get CM
 Fghost.SetXYZM(Xe,Ye,Ze,Mpr+Me);
 Bcm=-Fghost.BoostVector();

//obtain cascade rest frame boost vector
 Bcas=-Fcas.BoostVector();

//boost all particles to CM, write to CM3vector. then boost back to lab
 Fe.Boost(Bcm);
 Fpr.Boost(Bcm);
 Fk1.Boost(Bcm);
 Fk2.Boost(Bcm);
 Fcas.Boost(Bcm);
 Fpi.Boost(Bcm);
 Fl.Boost(Bcm);
 Fghost.Boost(Bcm);
 
TeCM=(Fe(0),Fe(1),Fe(2));
TprCM=(Fpr(0),Fpr(1),Fpr(2));
Tk1CM=(Fk1(0),Fk1(1),Fk1(2)); 
Tk2CM=(Fk2(0),Fk2(1),Fk2(2)); 
TcasCM=(Fcas(0),Fcas(1),Fcas(2));
TpiCM=(Fpi(0),Fpi(1),Fpi(2));
TlCM=(Fl(0),Fl(1),Fl(2));
TghostCM=(Fghost(0),Fghost(1),Fghost(2));

 Fe.Boost(-Bcm);
 Fpr.Boost(-Bcm);
 Fk1.Boost(-Bcm);
 Fk2.Boost(-Bcm);
 Fcas.Boost(-Bcm);
 Fpi.Boost(-Bcm);
 Fl.Boost(-Bcm);
 Fghost.Boost(-Bcm);

 // boost all particles to cascade rest frame, write to cascade 3 vector, then boost back to lab
 Fe.Boost(Bcas);
 Fpr.Boost(Bcas);
 Fk1.Boost(Bcas);
 Fk2.Boost(Bcas);
 Fcas.Boost(Bcas);
 Fpi.Boost(Bcas);
 Fl.Boost(Bcas);
 Fghost.Boost(Bcas);
 
TeCAS=(Fe(0),Fe(1),Fe(2));
TprCAS=(Fpr(0),Fpr(1),Fpr(2));
Tk1CAS=(Fk1(0),Fk1(1),Fk1(2)); 
Tk2CAS=(Fk2(0),Fk2(1),Fk2(2)); 
TcasCAS=(Fcas(0),Fcas(1),Fcas(2));
TpiCAS=(Fpi(0),Fpi(1),Fpi(2));
TlCAS=(Fl(0),Fl(1),Fl(2));
TghostCAS=(Fghost(0),Fghost(1),Fghost(2));

 Fe.Boost(-Bcas);
 Fpr.Boost(-Bcas);
 Fk1.Boost(-Bcas);
 Fk2.Boost(-Bcas);
 Fcas.Boost(-Bcas);
 Fpi.Boost(-Bcas);
 Fl.Boost(-Bcas);
 Fghost.Boost(-Bcas);


// norm to production plane in lab (electronXcas) and CM (protonXcas)
LABnorm=Te.Cross(Tcas);
LABnorm=LABnorm.Unit();
CMnorm=TprCM.Cross(TcasCM);
CMnorm=LABnorm.Unit();

//--------------------------the 4 quantities of main intrest---------------------
 PIangle=CMnorm.Angle(TpiCAS);
 PIangleLAB=LABnorm.Angle(TpiCAS);
 LAMBangle=CMnorm.Angle(TlCAS);
 LAMBangleLAB=LABnorm.Angle(TlCAS);

 //-----------------------and some checking below---------------------------



//cascade should be in plane so dot with normal should be zero for both
   LABcasDOTnormLAB=Tcas.Dot(LABnorm);
   LABcasDOTnormCM=Tcas.Dot(CMnorm);

 //energy of pion and lambda in the rest frame of the cascade should = mass of cascade
   Fpi.Boost(Bcas);
   Fl.Boost(Bcas);
   Epil=(Fpi.Energy()+Fl.Energy());
   Fpi.Boost(-Bcas);
   Fl.Boost(-Bcas);

// energy of cascade in rest frame should also = mass of cascade
   Fcas.Boost(Bcas); 
   Erestcas=Fcas.Energy();
   Fcas.Boost(-Bcas);

// energy of ghost should be mass of e plus mass of pr in CM frame
   Fghost.Boost(Bcm);
   Eghost=Fghost.Energy();
   Fghost.Boost(-Bcm);

//getting Z component of proton and electron in CM. just a check to see that they are opposite
//Eghost did this but this is a double check
   ZprCM=TprCM(2);
   ZeCM=TeCM(2);

//getting Z component of pion in lab frame. this might tell us somthing about acceptance
   ZpiLAB=Tpi(2);

//lab norm Dot cm norm should be 1 or -1
   normdiff=LABnorm.Dot(CMnorm);




   PIangleBranch->Fill();
PIangleLABBranch->Fill();
LAMBangleBranch->Fill();
LAMBangleLABBranch->Fill();
LABcasDOTnormLABBranch->Fill();
LABcasDOTnormCMBranch->Fill();
EpilBranch->Fill();
ErestcasBranch->Fill();
EghostBranch->Fill();
ZprCMBranch->Fill();
ZeCMBranch->Fill();
ZpiLABBranch->Fill();
normdiffBranch->Fill();

 }

newt->Write("", TObject::kOverwrite);

}
