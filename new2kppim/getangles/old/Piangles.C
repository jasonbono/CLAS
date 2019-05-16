/*
july 5 2011, jason bono
adopted from addbranch.C and from casmomentum.rtf

--- update1  works for when all declaration are in and librarys are called
still using tvar.

--update2 dont yet know how to call leaves, when spesifiying a leave get not defined message 
will look into later. for now make up numbers for vectors.

--- update3 couldent get TMath::Normal2Plane(pbm,pk1,pk2,normal); to work
got function not defined message. replaced with cross product then norm. had to add "ortho"


---- update4 got rest of code working up to the Boost() looks like you can only aply a boost to a 4vector.  defined a 3 component 4vector and bosted that, it worked.



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

	
void Piangles(){
       	
TFile *f = new TFile("newer.root","UPDATE");
TTree *newt = (TTree*)f->Get("new");
 Float_t tvar=10.0;   // just used for test

 
TVector3 pbm;
TVector3 pk1;
TVector3 pk2;
TVector3 px;
TVector3 ppi;

 TVector3 ortho;
TVector3 normal;

Float_t BPX;
Float_t BPY;
Float_t BPZ;
Float_t K1PX;
Float_t K1PY;
Float_t K1PZ;
Float_t K2PX;
Float_t K2PY;
Float_t K2PZ;
Float_t XPX;
Float_t XPY;
Float_t XPZ;



Float_t Mcas=1321.31;
Float_t Ecas;
Float_t Bcas;
TLorentzVector Fcas;
TVector3 Ucas;
TVector3 BVcas;
TVector3 negBVcas;

//TVector3 Rppi;
TLorentzVector Fpi;
Float_t angle;
 

//newt->SetBranchAddress("run", &tvar); //im not sure what this is or if i need it
TBranch *tbrBranch = newt->Branch("tvar", &tvar, "tvar/F");
TH1F *a5=new TH1F("a5", "", 100,-1,11);	
Int_t nentries = (Int_t)newt->GetEntries();   //??

for (Int_t i=0; i<nentries; i++) {
newt->GetEntry(i);




BPX=0.0;
BPY=0.0;	
BPZ=1; //fixbeam2;  NEED TO FIGGURE OUT HOW TO CALL LEAVES
pbm.SetXYZ(BPX,BPY,BPZ);


/*   AGAIN NEED TO CALL LEAVES
K1PX=pkp1*sin(kp1labtheta)*cos(kp1labphi);
K1PY=pkp1*sin(kp1labtheta)*sin(kp1labphi);
K1PZ=pkp1*cos(kp1labtheta);
pk1.SetXYZ(K1PX,K1PY,K1PZ);

K2PX=pkp2*sin(kp2labtheta)*cos(kp2labphi);
K2PY=pkp2*sin(kp2labtheta)*sin(kp2labphi);
K2PZ=pkp2*cos(kp2labtheta);
pk2.SetXYZ(K2PX,K2PY,K2PZ);

PIPX=ppim*sin(pilabtheta)*cos(pilabphi);
PIPY=ppim*sin(pilabtheta)*sin(pilabphi);
PIPZ=ppim*cos(pilabtheta);
ppi.SetXYZ(PIPX,PIPY,PIPZ);

*/

// FOR TESTING -- also see above BPZ
 pk1.SetXYZ(1,1,1);
 pk2.SetXYZ(0,1,0);
 ppi.SetXYZ(7,3,9);

// CASCADE MOMENTUM AND COMPONENTS
px = pbm - pk1 - pk2;
 XPX = px.X();
 XPY = px.Y();
 XPZ = px.Z();

// NORM TO PRODUCTION PLANE
 ortho = pbm.Cross(pk1);
 normal = ortho.Unit();

 //NOW CALCULATE CASCADE QUANTITIES
 Ecas=sqrt(Mcas*Mcas + XPX*XPX + XPY*XPY + XPZ*XPZ);
 Fcas.SetPxPyPzE(XPX,XPY,XPZ,Ecas);
 Bcas = Fcas.Beta();
 Ucas = px.Unit();
 BVcas = Bcas*Ucas;


/* since the Lorentz boost goes from rod frame to rest frame
i need to use the negative beta value so that i go from the rest (lab) frame to 
the rod frame (cascade rest frame)
*/

negBVcas = -BVcas;
Fpi.SetVect(TVector3(1,2,3)); //= ppi;
Fpi.Boost(BVcas);
angle = Fpi.Angle(normal);















tbrBranch->Fill();

  }	

newt->Write("", TObject::kOverwrite);


//just a text to see if macro is working
newt->Draw("tvar:vy:vz");


}
