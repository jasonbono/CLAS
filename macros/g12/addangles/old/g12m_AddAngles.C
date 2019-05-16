/* \

jan 14 2012: made this to add the m angle only.  this can be altered to add all angles

November 23 2011: edited this to work on the g12 data.


-------------FROM THE ORIGINAL G11 DATA BELOW-----------------------------
need to change the open file command after the header files to
choose real or simulated events

make sure the root file has "mytree" other wise you will get
"Error: illegal pointer to class object newt 0x0 2853  nxyz_angles.C:138:"


October 2: took helictyREAL.C added x and y angles.


September 7 made some changes to check the results


SEPTEMBER 6. took away the constraint of the lambda mass to conserve 4vector and added the Z component of the pion distribution in preperation for the g12 data. expect zero polarization in this direction for g11 of course. 

AUGUST 28 moved finalsoultion.C to macro directory with the intention of changing the beam energy to "beam" and compairing with the previous
results using "fixbeam2"



jason bono july 27
this code was developed after realizing that the pi and kayon angles are accualy cos(angle). this takes care of that issue by implementing TMath::ACos(). also  this code undoes the pointers in all of the transient variables and makes pointer types for the new branch variables... this may be, the final soultion before simulation.
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
	
void g12m_AddAngles(){
  //TFile *f = TFile::Open("nxyzREAL.root","UPDATE");  
  //TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15_5000.root","UPDATE");     	
  //TTree *addedt = (TTree*)f->Get("g12ana_v15");

  //TFile *f = TFile::Open("~/clas/rootfiles/g12/tests/testv20.root","UPDATE");     	
  //TTree *addedt = (TTree*)f->Get("g12ana_v20");

//  TFile *f = TFile::Open("~/clas/rootfiles/g12/large/g12ana_v16_58090.root","UPDATE");     	
//  TTree *addedt = (TTree*)f->Get("g12ana_v16");

	//TFile *f = TFile::Open("~/clas/rootfiles/g12/g12ana_v15.root","UPDATE");     	
	//TTree *addedt = (TTree*)f->Get("g12ana_v15");

	TFile *f = TFile::Open("~/clas/rootfiles/g11/nmxyzREAL.root","UPDATE");  //for real g11 rootfile 
	TTree *addedt = (TTree*)f->Get("new");  //for real g11 rootfile
	cout << "adding m to real data" <<endl;
	 
	//TFile *f = TFile::Open("~/clas/rootfiles/g11/nmxyzSIM.root","UPDATE"); //for sim g11 rootfile 
	 //TTree *addedt = (TTree*)f->Get("g112kppim"); //for sim g11 rootfile
	//cout << "adding m to sim data" <<endl;


//define momentum 4vectors, lab3vectors, CM3vectors, cascade3vectors, componets and masses
// photon, proton, kaon1, kaon2, cascade, pi-, lambda, ghost

TVector3 UnitVecZ;

TVector3 UnitVecX;
TVector3 UnitVecY;


 TLorentzVector Fb;
 TLorentzVector Fpr;
 TLorentzVector Fk1;
 TLorentzVector Fk2;
 TLorentzVector Fcas;
 TLorentzVector Fpi;
 TLorentzVector Fl;
 TLorentzVector Fghost;

TVector3 Tb;
TVector3 Tpr;
TVector3 Tk1;
TVector3 Tk2;
TVector3 Tcas;
TVector3 Tpi;
TVector3 Tl;
TVector3 Tghost;

TVector3 TbCM;
TVector3 TprCM;
TVector3 Tk1CM;
TVector3 Tk2CM;
TVector3 TcasCM;
TVector3 TpiCM;
TVector3 TlCM;
TVector3 TghostCM;

TVector3 TbCAS;
TVector3 TprCAS;
TVector3 Tk1CAS;
TVector3 Tk2CAS;
TVector3 TcasCAS;
TVector3 TpiCAS;
TVector3 TlCAS;
TVector3 TghostCAS;

Float_t Xb;
Float_t Yb;
Float_t Zb;
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

Float_t Mb=0.0;
Float_t Mpr=0.938272;
Float_t Mk=0.493667;
Float_t Mcas=1.32131;
Float_t Mpi=0.13957;
Float_t Ml=1.115683;

 // normalized momenta
TVector3 nTb;
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
Float_t beam;
Float_t pkp1;
Float_t kp1labtheta;
Float_t kp1labphi;
Float_t pkp2;
Float_t kp2labtheta;
Float_t kp2labphi;
Float_t ppim;
Float_t pilabtheta;
Float_t pilabphi;

addedt->SetBranchAddress("beam", &beam);
addedt->SetBranchAddress("pkp1", &pkp1);
addedt->SetBranchAddress("kp1labtheta", &kp1labtheta);
addedt->SetBranchAddress("kp1labphi", &kp1labphi);
addedt->SetBranchAddress("pkp2", &pkp2);
addedt->SetBranchAddress("kp2labtheta", &kp2labtheta);
addedt->SetBranchAddress("kp2labphi", &kp2labphi);
addedt->SetBranchAddress("ppim", &ppim);
addedt->SetBranchAddress("pilabtheta", &pilabtheta);
addedt->SetBranchAddress("pilabphi", &pilabphi);

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
Float_t PIanglez;
Float_t LAMBangle;
Float_t LAMBanglez;

Float_t PIanglex;
Float_t PIangley;
Float_t LAMBanglex;
Float_t LAMBangley;


	//jb jan 14 2012
	Float_t PIanglem_cm;
	Float_t LAMBanglem_cm;
	Float_t PIanglem_lab; 
	Float_t LAMBanglem_lab;


Float_t Epil;
Float_t Erestcas;
Float_t Eghost;
Float_t ZprCM;
Float_t ZbCM;
Float_t ZpiLAB;
Float_t normdiff;
Float_t EbCM;
Float_t EprCM;




/*
TBranch *PIangleBranch = addedt->Branch("PIangle", &PIangle, "PIangle/F");
TBranch *PIanglezBranch = addedt->Branch("PIanglez", &PIanglez, "PIanglez/F");
TBranch *LAMBangleBranch = addedt->Branch("LAMBangle", &LAMBangle, "LAMBangle/F");
TBranch *LAMBanglezBranch = addedt->Branch("LAMBanglez", &LAMBanglez, "LAMBanglez/F");


TBranch *PIanglexBranch = addedt->Branch("PIanglex", &PIanglex, "PIanglex/F");
TBranch *PIangleyBranch = addedt->Branch("PIangley", &PIangley, "PIangley/F");
TBranch *LAMBanglexBranch = addedt->Branch("LAMBanglex", &LAMBanglex, "LAMBanglex/F");
TBranch *LAMBangleyBranch = addedt->Branch("LAMBangley", &LAMBangley, "LAMBangley/F");


TBranch *EpilBranch = addedt->Branch("Epil", &Epil, "Epil/F");
TBranch *ErestcasBranch = addedt->Branch("Erestcas", &Erestcas, "Erestcas/F");
TBranch *EghostBranch = addedt->Branch("Eghost", &Eghost, "Eghost/F");
TBranch *ZprCMBranch = addedt->Branch("ZprCM", &ZprCM, "ZprCM/F");
TBranch *ZbCMBranch = addedt->Branch("ZbCM", &ZbCM, "ZbCM/F");
TBranch *ZpiLABBranch = addedt->Branch("ZpiLAB", &ZprCM, "ZpiLABCM/F");
TBranch *normdiffBranch = addedt->Branch("normdiff", &normdiff, "normdiff/F");
TBranch *EbCMBranch = addedt->Branch("EbCM", &EbCM, "EbCM/F");
TBranch *EprCMBranch = addedt->Branch("EprCM", &EprCM, "EprCM/F");
*/

	// jb jan 14 2012 making the m branch
	TBranch *PIanglem_cm_Branch = addedt->Branch("PIanglem_cm", &PIanglem_cm, "PIanglem_cm/F");
	TBranch *LAMBanglem_cm_Branch = addedt->Branch("LAMBanglem_cm", &LAMBanglem_cm, "LAMBanglem_cm/F");
	TBranch *PIanglem_lab_Branch = addedt->Branch("PIanglem_lab", &PIanglem_lab, "PIanglem_lab/F");
	TBranch *LAMBanglem_lab_Branch = addedt->Branch("LAMBanglem_lab", &LAMBanglem_lab, "LAMBanglem_lab/F");



Int_t nentries = (Int_t)addedt->GetEntries(); 
for (Int_t i=0; i<nentries; i++) {
addedt->GetEntry(i);


//PHOTON 3&4-vec 
 Xb=0;
 Yb=0;
 Zb=beam; 
 Tb.SetXYZ(Xb,Yb,Zb);
 Fb.SetXYZM(Tb(0),Tb(1),Tb(2),Mb);

//PROTON 3&4-vec
 Xpr=0;
 Ypr=0;
 Zpr=0;
 Tpr.SetXYZ(Xpr,Ypr,Zpr);
 Fpr.SetXYZM(Tpr(0),Tpr(1),Tpr(2),Mpr);

//KAON 3&4-vec
 Xk1=pkp1*sin(TMath::ACos(kp1labtheta))*cos(kp1labphi*TMath::Pi());
 Yk1=pkp1*sin(TMath::ACos(kp1labtheta))*sin(kp1labphi*TMath::Pi());
 Zk1=pkp1*kp1labtheta;

 Tk1.SetXYZ(Xk1,Yk1,Zk1);
 Fk1.SetXYZM(Tk1(0),Tk1(1),Tk1(2),Mk);

Xk2=pkp2*sin(TMath::ACos(kp2labtheta))*cos(kp2labphi*TMath::Pi());
Yk2=pkp2*sin(TMath::ACos(kp2labtheta))*sin(kp2labphi*TMath::Pi());
Zk2=pkp2*kp2labtheta;

Tk2.SetXYZ(Xk2,Yk2,Zk2);
Fk2.SetXYZM(Tk2(0),Tk2(1),Tk2(2),Mk);

//CASCADE 3&4-vec
 Tcas.SetXYZ(Tb(0)+Tpr(0)-Tk1(0)-Tk2(0),Tb(1)+Tpr(1)-Tk1(1)-Tk2(1),Tb(2)+Tpr(2)-Tk1(2)-Tk2(2));
 Fcas.SetXYZM(Tcas(0),Tcas(1),Tcas(2),Mcas);

//PION 3&4-vec
 Xpi=ppim*sin(TMath::ACos(pilabtheta))*cos(pilabphi*TMath::Pi());
 Ypi=ppim*sin(TMath::ACos(pilabtheta))*sin(pilabphi*TMath::Pi());
Zpi=ppim*pilabtheta;
Tpi.SetXYZ(Xpi,Ypi,Zpi);
Fpi.SetXYZM(Tpi(0),Tpi(1),Tpi(2),Mpi);

//LAMBDA 3&4-vec---------SEP6 THIS WAS EDITED TO UNCONSTRAIN THE MASS OF LAMBDA
 Tl.SetXYZ(Tcas(0)-Tpi(0),Tcas(1)-Tpi(1),Tcas(2)-Tpi(2));
 Fl.SetPxPyPzE(Tl(0),Tl(1),Tl(2),Fcas.Energy()-Fpi.Energy());
// Fl.SetXYZM(Tl(0),Tl(1),Tl(2),Ml);

//define ghost particle in lab frame and obtain CM boost vector to get CM
Fghost.SetPxPyPzE(Fb(0)+Fpr(0),Fb(1)+Fpr(1),Fb(2)+Fpr(2),Fb(3)+Fpr(3));// giving funny results
Bcm=-Fghost.BoostVector();
//obtain cascade rest frame boost vector
Bcas=-Fcas.BoostVector();

//boost all needed particles to CM, write to CM3vector. then boost back to lab
 Fb.Boost(Bcm);
 Fpr.Boost(Bcm);
 Fcas.Boost(Bcm);

 TbCM.SetXYZ(Fb(0),Fb(1),Fb(2));
 TprCM.SetXYZ(Fpr(0),Fpr(1),Fpr(2)); 
 TcasCM.SetXYZ(Fcas(0),Fcas(1),Fcas(2));

 //Fb->Boost(-*Bcm);
 //Fpr->Boost(-*Bcm);
 // Fcas->Boost(-*Bcm);
 Fb.SetXYZM(Tb(0),Tb(1),Tb(2),Mb);
 Fpr.SetXYZM(Tpr(0),Tpr(1),Tpr(2),Mpr);
 Fcas.SetXYZM(Tcas(0),Tcas(1),Tcas(2),Mcas);

//boost all needed particles to cascade rest frame, write to cascade 3 vector, then boost back to lab
 Fcas.Boost(Bcas);
 Fpi.Boost(Bcas);
 Fl.Boost(Bcas);
 
 TcasCAS.SetXYZ(Fcas(0),Fcas(1),Fcas(2));
 TpiCAS.SetXYZ(Fpi(0),Fpi(1),Fpi(2));
 TlCAS.SetXYZ(Fl(0),Fl(1),Fl(2));
 
 Fcas.Boost(-Bcas);
 Fpi.Boost(-Bcas);
 Fl.Boost(-Bcas);

// norm to production plane in lab (beamXcas) and CM (protonXcas)--- also define the unit vec along z
LABnorm=Tb.Cross(Tcas);
LABnorm=LABnorm.Unit();
CMnorm=TprCM.Cross(TcasCM);
CMnorm=CMnorm.Unit();

UnitVecZ.SetXYZ(0,0,1);

UnitVecX.SetXYZ(1,0,0);
UnitVecY.SetXYZ(0,1,0);

	//jb jan 14 2012  define the m axis parallel with the momentum of the cascade in the center of mass frame and the lab frame
	TVector3 UnitVecM_cm = TcasCM;
	UnitVecM_cm = UnitVecM_cm.Unit();
	TVector3 UnitVecM_lab = Tcas;
	UnitVecM_lab = UnitVecM_lab.Unit();


//--------------------------the main quantities of main intrest----------------------------------------------------
PIangle=CMnorm.Angle(TpiCAS);
PIanglez=UnitVecZ.Angle(TpiCAS);
LAMBangle=CMnorm.Angle(TlCAS);
LAMBanglez=UnitVecZ.Angle(TlCAS);

PIanglex=UnitVecX.Angle(TpiCAS);
PIangley=UnitVecY.Angle(TpiCAS);
LAMBanglex=UnitVecX.Angle(TlCAS);
LAMBangley=UnitVecY.Angle(TlCAS);

	//jb jan 15 now get the angles of the pion and lambda with the m axix with the m axis calculated in the lab and the cm
	PIanglem_cm = UnitVecM_cm.Angle(TpiCAS);
	LAMBanglem_cm = UnitVecM_cm.Angle(TlCAS);
	PIanglem_lab = UnitVecM_lab.Angle(TpiCAS);
	LAMBanglem_lab = UnitVecM_lab.Angle(TlCAS);

 //-----------------------and some checking below---------------------------


 //again to bypass pointer operatons problem
 //TVector3 tempTcas;
 //tempTcas=Tcas;
//cascade should be in plane so dot with normal should be zero for both
//---------SEP6 edited out below-----
//  LABcasDOTnormLAB=Tcas.Dot(LABnorm);
//   LABcasDOTnormCM=Tcas.Dot(CMnorm);

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

// energy of ghost 
   Fghost.Boost(Bcm);
   Eghost=Fghost.Energy();
    Fghost.Boost(-Bcm);

//getting Z component of proton and electron in CM. just a check to see that they are opposite
//Eghost did this but this is a double check
   ZprCM=TprCM(2);
   ZbCM=TbCM(2);

//getting Z component of pion in lab frame. this might tell us somthing about acceptance
   ZpiLAB=Tpi(2);

//lab norm Dot cm norm should be 1 or -1
   normdiff=LABnorm.Dot(CMnorm);
   
//energy of photon and proton in CM frame
   Fb.Boost(Bcm);
   Fpr.Boost(Bcm);
   EbCM=Fb.Energy();
   EprCM=Fpr.Energy();
   Fb.Boost(-Bcm);
   Fpr.Boost(-Bcm);

/*
   PIangleBranch->Fill();
   PIanglezBranch->Fill();
   LAMBangleBranch->Fill();
   LAMBanglezBranch->Fill();

   PIanglexBranch->Fill();
   PIangleyBranch->Fill();
   LAMBanglexBranch->Fill();
   LAMBangleyBranch->Fill();

   EpilBranch->Fill(); 
   ErestcasBranch->Fill();
   EghostBranch->Fill();
   ZprCMBranch->Fill();
   ZbCMBranch->Fill();
   ZpiLABBranch->Fill();
   normdiffBranch->Fill();
   EbCMBranch->Fill(); 
   EprCMBranch->Fill();
*/

	//jb jan 15
	PIanglem_cm_Branch->Fill();
	LAMBanglem_cm_Branch->Fill();
	PIanglem_lab_Branch->Fill();
	LAMBanglem_lab_Branch->Fill();


 }

addedt->Write("", TObject::kOverwrite);

}
