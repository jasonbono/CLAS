/* 



 if v1 v2 and v3 are vector3 of pointer type than
v1=(4,3,1) causes an error.

also if v1 and v2 are initialzed using setXYZ then
v3=v1 + v2 also causes a crash

to preform operations with X Y Z being pointers must do *X=Y.operation(*Z)

july 13 2011. jason bono
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
	
void resultsWpointers3(){
       	
TFile *f = new TFile("newer.root","UPDATE");
TTree *newt = (TTree*)f->Get("new");

//define momentum 4vectors, lab3vectors, CM3vectors, cascade3vectors, componets and masses
// photon, proton, kaon1, kaon2, cascade, pi-, lambda, ghost



 TLorentzVector *Fb=new TLorentzVector();
TLorentzVector *Fpr=new TLorentzVector();
TLorentzVector *Fk1=new TLorentzVector();
TLorentzVector *Fk2=new TLorentzVector();
TLorentzVector *Fcas=new TLorentzVector();
TLorentzVector *Fpi=new TLorentzVector();
TLorentzVector *Fl=new TLorentzVector();
TLorentzVector *Fghost=new TLorentzVector();

TVector3 *Tb=new TVector3();
TVector3 *Tpr=new TVector3();
TVector3 *Tk1=new TVector3();
TVector3 *Tk2=new TVector3();
TVector3 *Tcas=new TVector3();
TVector3 *Tpi=new TVector3();
TVector3 *Tl=new TVector3();
TVector3 *Tghost=new TVector3();

TVector3 *TbCM=new TVector3();
TVector3 *TprCM=new TVector3();
TVector3 *Tk1CM=new TVector3();
TVector3 *Tk2CM=new TVector3();
TVector3 *TcasCM=new TVector3();
TVector3 *TpiCM=new TVector3();
TVector3 *TlCM=new TVector3();
TVector3 *TghostCM=new TVector3();

TVector3 *TbCAS=new TVector3();
TVector3 *TprCAS=new TVector3();
TVector3 *Tk1CAS=new TVector3();
TVector3 *Tk2CAS=new TVector3();
TVector3 *TcasCAS=new TVector3();
TVector3 *TpiCAS=new TVector3();
TVector3 *TlCAS=new TVector3();
TVector3 *TghostCAS=new TVector3();

Float_t *Xb=new Float_t();
Float_t *Yb=new Float_t();
Float_t *Zb=new Float_t();
Float_t *Xpr=new Float_t();
Float_t *Ypr=new Float_t();
Float_t *Zpr=new Float_t();
Float_t *Xk1=new Float_t();
Float_t *Yk1=new Float_t();
Float_t *Zk1=new Float_t();
Float_t *Xk2=new Float_t();
Float_t *Yk2=new Float_t();
Float_t *Zk2=new Float_t();
Float_t *Xcas=new Float_t();
Float_t *Ycas=new Float_t();
Float_t *Zcas=new Float_t();
Float_t *Xpi=new Float_t();
Float_t *Ypi=new Float_t();
Float_t *Zpi=new Float_t();
Float_t *Xl=new Float_t();
Float_t *Yl=new Float_t();
Float_t *Zl=new Float_t();

Float_t Mb=0.0;
Float_t Mpr=0.938272;
Float_t Mk=0.493667;
Float_t Mcas=1.32131;
Float_t Mpi=0.13957;
Float_t Ml=1.115683;

 // normalized momenta
TVector3 *nTb=new TVector3();
TVector3 *nTpr=new TVector3();
TVector3 *nTk1=new TVector3();
TVector3 *nTk2=new TVector3();
TVector3 *nTcas=new TVector3();
TVector3 *nTpi=new TVector3();
TVector3 *nTl=new TVector3();

//Boost vectors
 TVector3 *Bcas=new TVector3();
 TVector3 *Bcm=new TVector3();

//Production plane
 TVector3 *LABnorm=new TVector3();
 TVector3 *CMnorm=new TVector3();

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
"ZprCM" "ZbCM" "Eghost"
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
Float_t ZbCM;
Float_t ZpiLAB;
Float_t normdiff;
Float_t EbCM;
Float_t EprCM;
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
TBranch *ZbCMBranch = newt->Branch("ZbCM", &ZbCM, "ZbCM/F");
TBranch *ZpiLABBranch = newt->Branch("ZpiLAB", &ZprCM, "ZpiLABCM/F");
TBranch *normdiffBranch = newt->Branch("normdiff", &normdiff, "normdiff/F");
TBranch *EbCMBranch = newt->Branch("EbCM", &EbCM, "EbCM/F");
TBranch *EprCMBranch = newt->Branch("EprCM", &EprCM, "EprCM/F");



Int_t nentries = (Int_t)newt->GetEntries(); 
for (Int_t i=0; i<nentries; i++) {
newt->GetEntry(i);


//PHOTON 3&4-vec 
 Xb[0]=0;
 Yb[0]=0;
 Zb[0]=fixbeam2; 
 Tb->SetXYZ(Xb[0],Yb[0],Zb[0]);
 Fb->SetXYZM(Tb(0),Tb(1),Tb(2),Mb);

//PROTON 3&4-vec
 Xpr[0]=0;
 Ypr[0]=0;
 Zpr[0]=0;
 Tpr->SetXYZ(Xpr[0],Ypr[0],Zpr[0]);
 Fpr->SetXYZM(Tpr(0),Tpr(1),Tpr(2),Mpr);

//KAON 3&4-vec
Xk1[0]=pkp1*sin(kp1labtheta)*cos(kp1labphi);
Yk1[0]=pkp1*sin(kp1labtheta)*sin(kp1labphi);
Zk1[0]=pkp1*cos(kp1labtheta);

Tk1->SetXYZ(Xk1[0],Yk1[0],Zk1[0]);
 Fk1->SetXYZM(Tk1(0),Tk1(1),Tk1(2),Mk);

Xk2[0]=pkp2*sin(kp2labtheta)*cos(kp2labphi);
Yk2[0]=pkp2*sin(kp2labtheta)*sin(kp2labphi);
Zk2[0]=pkp2*cos(kp2labtheta);

Tk2->SetXYZ(Xk2[0],Yk2[0],Zk2[0]);
 Fk2->SetXYZM(Tk2(0),Tk2(1),Tk2(2),Mk);

//CASCADE 3&4-vec
 Tcas->SetXYZ(Tb(0)+Tpr(0)-Tk1(0)-Tk2(0),Tb(1)+Tpr(1)-Tk1(1)-Tk2(1),Tb(2)+Tpr(2)-Tk1(2)-Tk2(2));

 Fcas->SetXYZM(Tcas(0),Tcas(1),Tcas(2),Mcas);

//PION 3&4-vec
Xpi[0]=ppim*sin(pilabtheta)*cos(pilabphi);
Ypi[0]=ppim*sin(pilabtheta)*sin(pilabphi);
Zpi[0]=ppim*cos(pilabtheta);
Tpi->SetXYZ(Xpi[0],Ypi[0],Zpi[0]);
 Fpi->SetXYZM(Tpi(0),Tpi(1),Tpi(2),Mpi);

//LAMBDA 3&4-vec
 Tl->SetXYZ(Tcas(0)-Tpi(0),Tcas(1)-Tpi(1),Tcas(2)-Tpi(2));
 Fl->SetXYZM(Tl(0),Tl(1),Tl(2),Ml);

//define ghost particle in lab frame and obtain CM boost vector to get CM
Fghost->SetPxPyPzE(Fb(0)+Fpr(0),Fb(1)+Fpr(1),Fb(2)+Fpr(2),Fb(3)+Fpr(3));// giving funny results
*Bcm=-Fghost->BoostVector();
//obtain cascade rest frame boost vector
*Bcas=-Fcas->BoostVector();

//boost all needed particles to CM, write to CM3vector. then boost back to lab
 Fb->Boost(*Bcm);
 Fpr->Boost(*Bcm);
 Fcas->Boost(*Bcm);

 TbCM->SetXYZ(Fb(0),Fb(1),Fb(2));
 TprCM->SetXYZ(Fpr(0),Fpr(1),Fpr(2)); 
 TcasCM->SetXYZ(Fcas(0),Fcas(1),Fcas(2));

 Fb->SetXYZM(Tb(0),Tb(1),Tb(2),Mb);
 Fpr->SetXYZM(Tpr(0),Tpr(1),Tpr(2),Mpr);
 Fcas->SetXYZM(Tcas(0),Tcas(1),Tcas(2),Mcas);

//boost all needed particles to cascade rest frame, write to cascade 3 vector, then boost back to lab
 Fcas->Boost(*Bcas);
 Fpi->Boost(*Bcas);
 Fl->Boost(*Bcas);
 
 TcasCAS->SetXYZ(Fcas(0),Fcas(1),Fcas(2));
 TpiCAS->SetXYZ(Fpi(0),Fpi(1),Fpi(2));
 TlCAS->SetXYZ(Fl(0),Fl(1),Fl(2));
 
 // Fcas->SetXYZM(Tcas(0),Tcas(1),Tcas(2),Mcas);
 //Fpi->SetXYZM(Tpi(0),Tpi(1),Tpi(2),Mpi);
 //Fl->SetXYZM(Tl(0),Tl(1),Tl(2),Ml);

// norm to production plane in lab (beamXcas) and CM (protonXcas)
*LABnorm=Tb->Cross(*Tcas);
*LABnorm=LABnorm->Unit();
*CMnorm=TprCM->Cross(*TcasCM);
*CMnorm=CMnorm->Unit();

//--------------------------the 4 quantities of main intrest---------------------
 PIangle=CMnorm->Angle(*TpiCAS);
 PIangleLAB=LABnorm->Angle(*TpiCAS);
 LAMBangle=CMnorm->Angle(*TlCAS);
 LAMBangleLAB=LABnorm->Angle(*TlCAS);

 //-----------------------and some checking below---------------------------


 //again to bypass pointer operatons problem
 //TVector3 tempTcas;
 //tempTcas=Tcas;
//cascade should be in plane so dot with normal should be zero for both
   LABcasDOTnormLAB=Tcas->Dot(*LABnorm);
   LABcasDOTnormCM=Tcas->Dot(*CMnorm);

 //energy of pion and lambda in the rest frame of the cascade should = mass of cascade
   // the 4 vecotrs for pion lambda are already boosted to cascade rest frame
   // Fpi->Boost(*Bcas);
   //Fl->Boost(*Bcas);
   Epil=(Fpi->Energy()+Fl->Energy());
   //Fpi->Boost(-*Bcas);
   //Fl->Boost(-*Bcas);

// energy of cascade in rest frame should also = mass of cascade
// the 4 vector for cascade is already at rest from before
//   Fcas->Boost(*Bcas); 
   Erestcas=Fcas->Energy();
   //   Fcas->Boost(-*Bcas);

// energy of ghost, no need to boost back to lab frame
   Fghost->Boost(*Bcm);
   Eghost=Fghost->Energy();
   //Fghost->Boost(-*Bcm);

//getting Z component of proton and electron in CM. just a check to see that they are opposite
//Eghost did this but this is a double check
   ZprCM=TprCM(2);
   ZbCM=TbCM(2);

//getting Z component of pion in lab frame. this might tell us somthing about acceptance
   ZpiLAB=Tpi(2);

//lab norm Dot cm norm should be 1 or -1
   normdiff=LABnorm->Dot(*CMnorm);
   
//energy of photon and proton in CM frame
   Fb->Boost(*Bcm);
   Fpr->Boost(*Bcm);
   EbCM=Fb->Energy();
   EprCM=Fpr->Energy();
   // Fb->Boost(-*Bcm);
   //  Fpr->Boost(-*Bcm);


PIangleBranch->Fill();
PIangleLABBranch->Fill();
LAMBangleBranch->Fill();
LAMBangleLABBranch->Fill();
LABcasDOTnormLABBranch->Fill();
LABcasDOTnormCMBranch->Fill();
 EpilBranch->Fill(); //weird... gives distribution
ErestcasBranch->Fill();
 EghostBranch->Fill();//weird.. gives distribution
 ZprCMBranch->Fill();// weird...gives zero
 ZbCMBranch->Fill();//weird... gives zero
 ZpiLABBranch->Fill();//weird.. gives zero
normdiffBranch->Fill();
 EbCMBranch->Fill(); //weird.. gives constant
 EprCMBranch->Fill();//weird.. gives constant

 }

newt->Write("", TObject::kOverwrite);

}
