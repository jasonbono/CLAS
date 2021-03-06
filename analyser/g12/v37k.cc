/*
April 10 v37k: added the combos for mmkpkp and mmkpkppim for nocorrecton,ecor,eloss and both.

skiped v36k becaused it dident work :/

april 1 v35k: 
1) changed the names of the polarization angles from COSth to COS as to correspond to the Addxyz_2.C macro
2) called the new energy e_cor developed by mike kunkle and johann: then renamed the beamp to be this new corrected energy.  i made some new varible showing the values with out
this new correction with the suffix "woE".  once i implement the pcor, the variables without both energy and momentum corrections will be called by the suffix "_woEP"
this is similar to the varibles without eloss correctons which are named witht he prefix "wo_"
3) put back the st filter
4) added in the bb filter for beam energy
5) the g11 kinematic fitting was removed

//the filters are working and all seems to be good



the energy correction clearly had an effect after examining the rootfile. as documented in my log book


march 26 v34k: got the extra kf working for the cascade0 spectrum. now i have both header files combined into a single headder.


march 21 v33k:  added the one constraint kinematic fitting for the kp kp pi (cascade0) to try to clean up the spectrum in search for the missing resonance.
THIS NEVER WORKED



march 20 v32k: made the fit so that it works for two kinematic constraints.

march 19 v31k:  the extra methods added in the last section are incorrect and were taken out once again. it seems that everything with the kinematic fitter 
makes sence other than the kf_casmMpim spectrum.  lei and i showed that the kf_mmkpkp = kf_mlampim which is what we see in the data exactly for any confidence cut over 10%
for the non lambda events ie confidence = 0% the spectrums are very close but not exact. 

change summary: 
1) took out the extra method of calculating invarient mass
2) fixed the kinematic fitting tests
3) added kf2 to constrain on cascade.
4) added mmkpkppim for convience when writing macros. (find this next to mmkpkp) 


March 18 v30k:  put together some tests to see why the kinematic fitting is not improving the spectrum.  also added diffrent methods of calculating the invarient mass in the kinfit

-found that the masses of the lambda and proton are in the headder file correctly so they do not need to be declared in this code.
-right now it is possible that the source of the error was from the fact that i used kf_lamda and kf_cascadem in the invarent masses, 
i may have to use lambda and cascade instead.




March 15 v29k:  moved the kinematic fitting just above the added polarization angles and added the invarient masses from the kinematic fitter: ~(lambda + pi)  and ~(cascade - pion).
i needed to add the four vectors for kf_lambda and kf_cascade to do this


MARCH 9 2012: "v28k":: cleaned up  format further.


MARCH 7 2012: "v27k" ::: added more kinematic fitting varibles (ie missing mass variables)


MARCH 7 2012: "v26k" ::: 
the angles from the previous version v25k agreed witht those obtained from the macro "Addxyz.C" for the pion. in this macro i added in the angle for the 
lambdaPDG and deleeted most of the old work assocated with past attempts to compute the angles. also started cleaning up the format of this analyze


--------------------------------------------------------------------------------------------------------------
MARCH 1 2012: "v25k":  the kinematic fitting from the previous version seems to be working properly so now i will focus on correcting the way the angles are computed.
i have just made the macro "Addxyz.C" which computes the angles in a way i am more cirtan of.  the instructions i have out lined just below.

1) start in lab system with the beam aligned with the z axis.
2) compute the kpkp four vector in the lab frame which is simply just k1+k2
2) compute the cascadePDG four vector by the momentum of (beam + proton - k1 - k2) and the PDG mass.
3) obtain the boost vector so that this cascadePDG is in a rest frame
4) boost the beam, the pion, and the kpkp vector to the cascade (and lambda if want to examine this particle) 
... side note:  can use both lambda and lambdaPDG where lambda is from missing p and e and lambdaPDG is missing p and the PDG mass. defineing a third lambda is possible which is simply the
cascade - pion system however this would be reduntant.  from the analysis in Addxyz.C the lambdaPDG is what came out closest to back to back witht he pion in the Xi resframe
5) using the boosted vectors define  (z' = beam momentum) , (y' = beam.cross.kpkp), (x' = z'.cross.y') where theese have all been normalized
6) by whatever means find the cosine of the angles between the pion (still in the XiPDG restframe) and each of the three primed coordinates.
7)  if wanted find the similar angles of the lambdaPDG... STILL HAVE TO VERIFY WHICH LAMBDA TO USE 


FEB 28 2012:  v24k:  look for "v24k":  attempting to add cosine of the angles for 2 inplane (z and x) and the one out of plane (y).
here the naming convention has changed as to conform with bradford for easy compairison.  will call the varieables COSth_pi_x, COSth_pi_y, COSth_pi_z,
and when i compute them from a macro for compairison i will just call them "mcro_COSth_pi_x" etc. since i will eventualy only use the analyzer and not seperate
macros to add my branch variables.  i have outlined in my book how to compute the angles.

in this version i have not deleeted the old ways of computing the angles but i will in subsequent versions once i have confirmed that theese are the correct
angles


--------------------------------------------------------------------------------------------------------------
FEB 27 2012:  v23k: look for "v23k"
here i filled the kf_4vecs, theese will be used to calculate missing mass in later versions. i also added as branch variables chi2 and prob and  put the kfit calculations closer to the top of the code rather than at the bottem.
also it should be noted that i skiped version 22. this is because that version never compiled but i was working on an issue which
is outlined in the fillowing exerpt from that code:

 "Jan 3 2012 v22:  changed the way the angles are computed.  i realized that the energy in the fourvector is important when boosting in order to preserve the direction of momentum. what happens is if the wrong energy is chosen then when boosting the 
momentum component ORGHOGONAL to the boost is left unchanged while the momentum component PARALLEL with the boost is lorentz contracted the incorect amount.  the way that i had done it in g12nxyz_angles.C is:
cascade:  p from missing momentum of targ,beam,kp1,kp2  and energy from nominal mass (along of couse with p which was just described)
lambda:  p from missing momentum of targ,beam,kp1,kp2,pim  and energy= cascade(energy) - pim(energy)
pim: p measured  energy from nominal mass
kp1 & kp2:  p measured and energy from nominal mass
i will set theese four vectors and obtain the angles from them. calling the new vectors   particlename_new "

THIS should be looked into shortly.



--------------------------------------------------------------------------------------------------------------
Feb 27 2012:  added the beginning of kinematic fit.  this will be the last cc file with k in the name,  v22 will be skiped because i never 
got it to compile right so the next version of this code will be v23.


December 30 2011 v21: found one thing wrong:  i have been using X as the cascade however this does not use the constrained mass and therefore is not correct in the CM frame.  insdead use cascadem. will change the tests accordingly
-> this showed that the energy of the pion and the lambda in the rest frame of the cascadem was NOT the mass of the cascade so there must be a problem.  however the rest frame of the cascade looks ok. will have to exploer def of pim_1 and lambda_1

December 30 2011 v20:  added even more tests to find what is wrong with the angles. look for "jb v20"
at this point it has been proven that vec.r() is indeed the pythagorean distance sqrt [vec.x()^2 vec.y()^2 vec.z()^2]  
where vec is either a 3vec or a 4vec.  for a 4 vec with (a,b,c,d) vec.x()=b ie it is the x component of the momentum. this is what was expected.
more is to be determined however in the theese next few checks  



December 29 2011 v19: changed the way angles are computed HERE LOOK FOR "jb v18" as i made a mistake and called all the edits the wrong thing. 


December 29 2011 v18:  trying to find angles bug and cleaning up the format.  added a few tests search for //jb v18



December 19 2011 v17: fixed the spelling bug for the isSThit() member function branch varible and
 added a branch varible for the paddle that was hit for the startcounter timing.
it is in the TBID bank called and the member function is called st_id. it is an integer from 1 to 100.
not sure if it will work but want to try myevent.cp(KPlus,1).st_id()


December 15 2011 v16: added in myevent.cp(KPlus,1).isSThit() as a branch variable to see which 
tracks had good start counter hits.  i havent looked at it yet but i think it is good hit==1 and bad hit==0


nov 17 v15: added (cascadem - pim) invarient mass

nov 10 v14: now to write somthing that selects the higher energy photon.

Nov 10 v13: clas event my_event.V() gets the vertex info from the MVRT. MVRT stands for multiple vertex and it averages all of the vertexes in TBTR. used this to
changed the prototype etc etc of my_get_photon_tagr look for //jb v13

i think i fixed the issue of myvert.



nov 10: v12: i still have not finished what i specified below for the v11 version.  for this one however i would like to fix my wo missing masses to verify that the eloss does somthing
and also check out the angles that i added because the spectrum looked wrong for v10, probably an error in the def of lambda_1 and pim_1

------------->>>> dont see anything wrong with the way the angles are computed.


nov 9:  v11:  changes needed are below  look for //jb v11... may not do all changes in v11 may need to make several v11_x versions to complete

in my_get_photon_tagr:
*DONE:take out g11targz=-10 and put in g12targz=-90
*change TBTR->tbtr[trk_ind-1].vert.z to somthing MVRT.z somthing.  basicly using MVRT bank rather than TBTR bank.
*write somthing to choose the higher energy for multiple photons

elsewere:
*DONE:take out mmbeam stuff! the beam energy should not have corrections, eloss applies to the particles going through the detector so need to fix the test to see if eloss is doing somthing.
*DONE FOR ONE (search edit_1): take out any filters, theese will be if statements.  want to analyze all events.



nov 9:  v10:  added the nphotons as branch variables and fixed the angles.  there are some problems with this analyzer

SKIP TO V10 FOR HIGER VERSIONS!!!

Nov 8: v07_3_npho:  adding npho function to count the number of photons in the beam bunch and neighboring and next neighboring bunches.
search for //jb npho. in this version the results are just prited to the screen with cout.  

Nov 7: v07_3  i added missing mass for pip + pim systems.  added the lambda and cascade missing mass that would bypass energy corrections the "wo" variables

Nov 2: v07_2  i added a bunch of leaves so that we could look at the 2d histograms. search for //jbv07_2 for the changes

October 23 2011 v07  took out the kinematic fiting and the momentum correction.  took out 10 branches for kinematic fiting so there should be 121-10=111
see lines with //jb v07


OCT 23 2011. v06  took this strait from g11 ana and took out the ps beam corrections.  i FINALLY got the lable files to match.  also added all the angles
 for ps removal see //jb. for angle addtion see //jb v06

so the number of branches at this point should be 117 - 4ps + 8angles = 121 branches which is what im seeing in the lable and the view file out puts

*/


#include "my_kinfit2.hpp"
#include "g12_ecor.hpp"  //jb v35k



#include <iostream>
#include <fstream>
#include <plib.h>

extern "C" 
 {
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

 #include <scalers.h>
 #include <utility.h>
 #include <printBOS.h>
 #include <ec.h>
 #include <PartUtil.h>
 #include <dataIO.h>
 #include <itape.h>
 #include <vertex.h>
 #include <sc.h>
 }

// You must change this to have the correct header file for ROOT
#include <Vec.h>
#include <lorentz.h>
#include <pputil.h>
#include <clasEvent.h>

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

extern "C" 
{
 void bnames_(int *);
 int SetVerbose(int);
 extern void photonenergy_(double *b0, int *run, double *b1, double *b2);
}

int StartRun(int);
int ProcessEvent(clasEvent &event,int, int);
int DropList(int DropFlag);
void PrintUsage(char *processName);
int fillNtuples(clasEvent &event);

tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID, threeVec myVert); //jb v13
//jb v13 tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID);
int npho( clasTAGR_t *TAGR, float tpho, int nb);  //jb npho2

int CurrentRun = 0;
int setRun = 0;
int CurrentEvent = 0;
int partbank0 = 1;
int partbank = 1;
int datatype=1;
int corr=0;

ofstream output;

int StartRun(int runNo)
{  
 int static CurrentRun = -1;
 if (CurrentRun != runNo) 
 {
  vertex_brun(runNo);
  CurrentRun = runNo;
 }
 return 0;
}


int DropList(int DropFlag)
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
 
 return(0);
}


void PrintUsage(char *processName)
{
 cerr << processName << " <options> <filename>\n";
 cerr << "\toptions are:\n";
 cerr << "\t-t#\ttrigger mask.\n";
 cerr << "\t-D#\tDrop flag.\n";
 cerr << "\t-o<filename>\tBOS output file.\n";
 cerr << "\t-M#\tprocess maximum # of events.\n";
 cerr << "\t-R#\tset run number (mc only)\n";
 cerr << "\t-a<filename>\tascii output file for making Ntuples(default output.view).\n";
 cerr << "\t-X#\tdata type(x=1, real data; x=0, mc data\n";
 cerr << "\t-C#\tperform eloss and momentum correction(C=1, perform correction; C=0, no correction\n";
 cerr << "\t-F#\tIFLAG valued for eloss package(default 1)\n";
 cerr << "\t\tIFLAG=0 - empty target. For IFLAG=0 no energy losses in target.\n";
 cerr << "\t\tIFLAG=1 - LH2 target\n";
 cerr << "\t\tIFLAG=2 - LD2 target\n";
 cerr << "\t\tIFLAG=3 - L3He target\n";
 cerr << "\t-i\tquiet mode (no counter).\n";
 cerr << "\t-h\tprint the above" << endl;
}

void printLabels()
{
 int nlab = 0;

 // some tests of the ecor
 cout << ++nlab << "\toldbeam energy{beam_woecor}"<<endl;
 cout << ++nlab << "\tmass of (mmkpkp_woecor) {mmkpkp_woecor}"<<endl;
 cout << ++nlab << "\tmass of (mmkpkppim_woecor) {mmkpkppim_woecor}"<<endl;

 cout << ++nlab << "\tmass of (mmkpkp_woeloss) {mmkpkp_woeloss}"<<endl;
 cout << ++nlab << "\tmass of (mmkpkppim_woeloss) {mmkpkppim_woeloss}"<<endl;

 cout << ++nlab << "\tmass of (mmkpkp_woecoreloss) {mmkpkp_woecoreloss}"<<endl;
 cout << ++nlab << "\tmass of (mmkpkppim_woecoreloss) {mmkpkppim_woecoreloss}"<<endl;

 cout << ++nlab << "\trun number{run}"<<endl;
 cout << ++nlab << "\tevt number{evt}"<<endl;
 cout << ++nlab << "\tsc Vtime{scv}"<<endl;
 cout << ++nlab << "\tst Vtime{stv}"<<endl;
 cout << ++nlab << "\tvtim should be same as sc Vtime{vtime}"<<endl;
 cout << ++nlab << "\tmvrt x{vx}"<<endl;
 cout << ++nlab << "\tmvrt y{vy}"<<endl;
 cout << ++nlab << "\tmvrt z{vz}"<<endl;
 cout << ++nlab << "\tnumber of K+{nkp}"<<endl;
 cout << ++nlab << "\tnumber of pi-{npim}"<<endl;
 cout << ++nlab << "\tnumber of K-{nkm}"<<endl;
 cout << ++nlab << "\tnumber of proton{np}"<<endl;
 cout << ++nlab << "\tnumber of pi+{npip}"<<endl;
 //jb v07 cout << ++nlab << "\t{kfit probability, confidence level}{cl}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit chisq}{chi2}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit beam}{bfit}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit mm}{fitmmkkpim}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit }{fitmmkpkp}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit mmkp1}{fitmmkp1}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit mmkp2}{fitmmkp2}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit mmpim}{fitmmpim}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit m(kp1+pim)}{fitmkp1pim}"<<endl;
 //jb v07  cout << ++nlab << "\t{kfit m(kp2+pim)}{fitmkp2pim}"<<endl;
 cout << ++nlab << "\t(mass of proton pi-){mppim}"<<endl;
 cout << ++nlab << "\t{tofbetakp1}"<<endl;
 cout << ++nlab << "\t{tofbetakp2}"<<endl;
 cout << ++nlab << "\t{tofbetapim}"<<endl;
 cout << ++nlab << "\t{betakp1}"<<endl;
 cout << ++nlab << "\t{betakp2}"<<endl;
 cout << ++nlab << "\t{betapim}"<<endl;
 cout << ++nlab << "\t{sctkp1}"<<endl;
 cout << ++nlab << "\t{sctkp2}"<<endl;
 cout << ++nlab << "\t{sctpim}"<<endl;
 cout << ++nlab << "\t{sclkp1}"<<endl;
 cout << ++nlab << "\t{sclkp2}"<<endl;
 cout << ++nlab << "\t{sclpim}"<<endl;
 cout << ++nlab << "\t{tofmasskp1}"<<endl;
 cout << ++nlab << "\t{tofmasskp2}"<<endl;
 cout << ++nlab << "\t{tofmasspim}"<<endl;
 cout << ++nlab << "\t{stvkp1}"<<endl;
 cout << ++nlab << "\t{stvkp2}"<<endl;
 cout << ++nlab << "\t{stvpim}"<<endl;

 cout << ++nlab << "\t{goodSTkp1}"<<endl;  //jb v16
 cout << ++nlab << "\t{goodSTkp2}"<<endl;  //jb v16
 cout << ++nlab << "\t{goodSTpim}"<<endl;  //jb v16

 cout << ++nlab << "\t{stid_kp1}"<<endl;  //jb v17
 cout << ++nlab << "\t{stid_kp2}"<<endl;  //jb v17
 cout << ++nlab << "\t{stid_pim}"<<endl;  //jb v17


 // distances
 cout << ++nlab << "\t(distance between K+1, pi-){dkp1pim}"<<endl;
 cout << ++nlab << "\t(distance between K+2, pi-){dkp2pim}"<<endl;
 cout << ++nlab << "\t(distance between K+1, K+2){dkpkp}"<<endl;
 cout << ++nlab << "\tbeam energy{beam}"<<endl;
 //JB\\cout << ++nlab << "\tbeam energy from ps tagger correction{psbeam}"<<endl;
 cout << ++nlab << "\tsqrt(s){w}"<<endl;
 
 cout << ++nlab << "\tt energy transfer(kp1+kp2 - beam){tkpkp}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp1+kp2+pim - beam){tkpkppim}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp1+pim - beam){tkp1pim}"<<endl;
 cout << ++nlab << "\tt energy transfer(kp2+pim - beam){tkp2pim}"<<endl;
 cout << ++nlab << "\tmissing mass square of (K+K+) {mm2kpkp}"<<endl;
 //JB\\  cout << ++nlab << "\tmissing mass square of using ps beam (K+K+) {psmm2kpkp}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp1){mm2kp1}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp2){mm2kp2}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp1+pim){mm2kp1pim}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp2+pim){mm2kp2pim}"<<endl;
 cout << ++nlab << "\tmissing mass square of (kp+kp+pim){mm2kpkppim}"<<endl;
 //jbv07_3 the cascade and lambda missing mass square without beam energy corrections 
 //cout << ++nlab << "\tmissing mass square without eloss corrections of (kp1+kp2){wo_mm2kpkp}"<<endl;
 //cout << ++nlab << "\tmissing mass square without eloss corrections of (kp1+kp2+pim){wo_mm2kpkppim}"<<endl;

 //JB\\ cout << ++nlab << "\tmissing mass square of (kp+kp+pim)using ps beam{psmm2kpkppim}"<<endl;

 //invariant masses
 cout << ++nlab << "\tmass of (k+ k+) {mkpkp}"<<endl;
 cout << ++nlab << "\tmass of (k+1 pi-) {mkp1pim}"<<endl;
 cout << ++nlab << "\tmass of (k+2 pi-) {mkp2pim}"<<endl;

 //missing masses
 cout << ++nlab << "\tmass of (mmkp1){mmkp1}"<<endl;
 cout << ++nlab << "\tmass of (mmkp2) {mmkp2}"<<endl;
 cout << ++nlab << "\tmass of (mmkpkp) {mmkpkp}"<<endl;
 cout << ++nlab << "\tmass of (mmkpkppim) {mmkpkppim}"<<endl;

 //momentums
 cout << ++nlab << "\tkp1 momentum{pkp1}"<<endl;
 cout << ++nlab << "\tkp2 momentum{pkp2}"<<endl;
 cout << ++nlab << "\tkp2 momentum{ppim}"<<endl;
 cout << ++nlab << "\tmiss x{missx}"<<endl;
 cout << ++nlab << "\tmiss y{missy}"<<endl;
 cout << ++nlab << "\tmiss z{missz}"<<endl;
 cout << ++nlab << "\tmiss momentum{missp}"<<endl; 
 cout << ++nlab << "\tmiss momentum{misse}"<<endl; 

 cout << ++nlab << "\tt prime{tp}"<<endl;
 //constrained masses
 cout << ++nlab << "\tMass(Cascade, K+1){mcaskp1}"<<endl;
 cout << ++nlab << "\tMass(Cascade, K+2){mcaskp2}"<<endl;
 cout << ++nlab << "\tMass(Cascade, pim){mcaspim}"<<endl;
 cout << ++nlab << "\tMass(lambda, pim){mlampim}"<<endl;
 //JB\\  cout << ++nlab << "\tMass(Cascade, pim) ps method{mpscaspim}"<<endl;
 cout << ++nlab << "\tMass(Cascade, pim) fix beam method{mfixcaspim}"<<endl;
 cout << ++nlab << "\tbeam energy fix beam method{fixbeam}"<<endl;

 cout << ++nlab << "\tMass(Cascadem, kp1){mcasmkp1}"<<endl;
 cout << ++nlab << "\tMass(Cascadem, kp2){mcasmkp2}"<<endl;
 cout << ++nlab << "\tMass(Cascadem - pim){mcasmMpim}"<<endl;  //jb v15
 cout << ++nlab << "\tMass(Cascadem, kp1)using fixbeam{mfixcasmkp1}"<<endl;
 cout << ++nlab << "\tMass(Cascadem, kp2)usign fixbeam{mfixcasmkp2}"<<endl;
 cout << ++nlab << "\tbeam energy fix beam method{fixbeam2}"<<endl;
   
 //replace k+ with pi+ and get the masses
 cout << ++nlab << "\tMissing Mass(3pi){mm3pi}"<<endl;
 cout << ++nlab << "\tMissing Mass(K+1, pip, pim){mmkp1pippim}"<<endl;
 cout << ++nlab << "\tMissing Mass(K+2, pip, pim){mmkp2pippim}"<<endl; 
  
 //jbv07_2 leaves for 2 particle for k+ replaced with pi+
 cout << ++nlab << "\tMissing Mass(2pip){2pip}"<<endl;
 cout << ++nlab << "\tMissing Mass(K+1, pip){mmkp1pip}"<<endl;
 cout << ++nlab << "\tMissing Mass(K+2, pip){mmkp2pip}"<<endl;
 //jbv07_2 leaves for 1 particle for k+ replaced with pi+  
 cout << ++nlab << "\tMissing Mass(K+1){mmkp1}"<<endl;
 cout << ++nlab << "\tMissing Mass(K+2){mmkp2}"<<endl;
 cout << ++nlab << "\tMissing Mass(pip1){mmpip1}"<<endl;
 cout << ++nlab << "\tMissing Mass(pip2){mmpip2}"<<endl;

 cout << ++nlab << "\tMass(K+1, pip, pim){mkp1pippim}"<<endl;
 cout << ++nlab << "\tMass(K+2, pip, pim){mkp2pippim}"<<endl;
 cout << ++nlab << "\tMass(pip1, pim){mpip1pim}"<<endl;
 cout << ++nlab << "\tMass(pip2, pim){mpip2pim}"<<endl;
 cout << ++nlab << "\tMass(pip1, pip2, pim){m3pi}"<<endl;

 //jbv07_3 the missing mass of pip + pim system
 cout << ++nlab << "\tMissing Mass(pip1 + pim){mmpip1pim}"<<endl;
 cout << ++nlab << "\tMissing Mass(pip2 + pim){mmpip2pim}"<<endl;


 // kf
 cout << ++nlab << "\t(kfit){kf_prob}"<<endl;
 cout << ++nlab << "\t(kfit){kf_chi2}"<<endl;
 cout << ++nlab << "\t(kfit){kf_pull_beam}"<<endl;
 cout << ++nlab << "\t(kfit){kf_mmkpkppim}"<<endl;  //v27k
 cout << ++nlab << "\t(kfit){kf_mmkpkp}"<<endl;     //v27k
 cout << ++nlab << "\t(kfit)(lambda + pim){kf_mlampim}"<<endl;  //jb v29k
 cout << ++nlab << "\t(kfit)(Cascadem - pim){kf_mcasmMpim}"<<endl;  //jb v29k

 cout << ++nlab << "\t(kfit tests){kf_diff_beam}"<<endl;  //jb v30k
 cout << ++nlab << "\t(kfit tests){kf_diff_k1}"<<endl; //jb v30k
 cout << ++nlab << "\t(kfit tests){kf_diff_k2}"<<endl; //jb v30k
 cout << ++nlab << "\t(kfit tests){kf_diff_pim}"<<endl; //jb v30k


 // kf2
 cout << ++nlab << "\t(kfit2){kf2_prob}"<<endl;
 cout << ++nlab << "\t(kfit2){kf2_chi2}"<<endl;
 cout << ++nlab << "\t(kfit2){kf2_pull_beam}"<<endl;
 cout << ++nlab << "\t(kfit2){kf2_mmkpkppim}"<<endl;
 cout << ++nlab << "\t(kfit2){kf2_mmkpkp}"<<endl;  
 cout << ++nlab << "\t(kfit2)(cascade0 + pim){kf2_mcas0pim}"<<endl;
 
 cout << ++nlab << "\t(kfit2 tests){kf2_diff_beam}"<<endl;
 cout << ++nlab << "\t(kfit2 tests){kf2_diff_k1}"<<endl;
 cout << ++nlab << "\t(kfit2 tests){kf2_diff_k2}"<<endl; 
 cout << ++nlab << "\t(kfit2 tests){kf2_diff_pim}"<<endl; 


 //jb v24k the polarization angles
 cout << ++nlab << "\t(pi) pion angle x{COS_pi_x}"<<endl; 
 cout << ++nlab << "\t(pi) pion angle y{COS_pi_y}"<<endl; 
 cout << ++nlab << "\t(pi) pion angle z{COS_pi_z}"<<endl;
 cout << ++nlab << "\t(pi) lambda angle x{COS_lam_x}"<<endl; 
 cout << ++nlab << "\t(pi) lambda angle y{COS_lam_y}"<<endl; 
 cout << ++nlab << "\t(pi) lambda angle z{COS_lam_z}"<<endl;


 //lab angles
 cout << ++nlab << "\t(K+) lab angle{kp1labtheta}"<<endl;
 cout << ++nlab << "\t (K+) lab angle{kp1labphi}"<<endl;
 cout << ++nlab << "\t(K+2) lab angle{kp2labtheta}"<<endl;
 cout << ++nlab << "\t (K+2) lab angle{kp2labphi}"<<endl;
 cout << ++nlab << "\t(pi) lab angle{pilabtheta}"<<endl;
 cout << ++nlab << "\t(pi) lab angle{pilabphi}"<<endl;
 cout << ++nlab << "\t(X) lab angle{Xlabtheta}"<<endl;
 cout << ++nlab << "\t(X) lab angle{Xlabphi}"<<endl;
 
 //cm angles
 cout << ++nlab << "\t(K+) cm angle{kp1cmtheta}"<<endl;
 cout << ++nlab << "\t (K+) cm angle{kp1cmphi}"<<endl;
 cout << ++nlab << "\t(K+2) cm angle{kp2cmtheta}"<<endl;
 cout << ++nlab << "\t (K+2) cm angle{kp2cmphi}"<<endl;
 cout << ++nlab << "\t(pi) cm angle{picmtheta}"<<endl;
 cout << ++nlab << "\t(pi) cm angle{picmphi}"<<endl;
 cout << ++nlab << "\t(X) cm angle{Xcmtheta}"<<endl;
 cout << ++nlab << "\t(X) cm angle{Xcmphi}"<<endl;
 //Y1 rest frame angles
 cout << ++nlab << "\t(Kp2) (kp2+xm) rest angle{kp2htheta}"<<endl;
 cout << ++nlab << "\t(Kp2)(kp2+xm) rest angle{kp2hphi}"<<endl;
 //Y2 rest frame angles
 cout << ++nlab << "\t(Kp1) (kp1+xm) rest angle{kp1htheta}"<<endl;
 cout << ++nlab << "\t(Kp1) (kp1+xm) rest angle{kp1hphi}"<<endl;
 //X rest frame angles
 cout << ++nlab << "\t(pi) Xi rest angle{pihtheta}"<<endl;
 cout << ++nlab << "\t(pi) Xi rest angle{pihphi}"<<endl;

 //jb v10
 cout << ++nlab << "\t(Number of photons in 1 timing bunch){nphoton_nb0}"<<endl;
 cout << ++nlab << "\t(Number of photons in 3 timing bunches ){nphoton_nb1}"<<endl;
 cout << ++nlab << "\t(Number of photons in 5 timing bunches){nphoton_nb2}"<<endl;



}


// ------------------------------------------------
// ------------------ Main program ----------------
// ---------- To be modified to fit need ----------
// ------------------------------------------------

int main(int argc,char **argv)
{

 int max = 0;
 int verbose = 0;
 int ret = 1;
 int Nevents = 0;
 int Nproc = 0;
 int Nwrite = 0;
 char *argptr;
 int Dispatch = 0;
 unsigned int triggerMask = 0;
 int writeFlag = 0;
 int IFLAG=1;
 
 // bos stuff
 char *BOSoutfile = NULL;
 char *asciioutfile = "output.view";
 int OutputUnitNo = 9;
 int MaxBanks = 1000; 
 char  out[300];
 char Elist[5 * MaxBanks];

 int DropFlag = 0x0;

 for (int i = 1; i < argc; i++)
 {
  argptr = argv[i];
  if (*argptr == '-') 
  {
   argptr++;
   switch (*argptr) 
   {
	
    case 't':
    triggerMask = strtoul(++argptr,NULL,0);
    break;
    case 'X':
	datatype = atoi(++argptr);
	break;
    case 'C':
	corr = atoi(++argptr);
	break;
    case 'a':
	
	if(*(++argptr))
	asciioutfile = argptr;
	break;
    case 'F':
	IFLAG = atoi(++argptr);
	break;

    case 'D':
	DropFlag = strtoul(++argptr,NULL,0);
	break;

    case 'v':
	verbose = 1;
	break;
      
    case 'o':
	if(*(++argptr))
	BOSoutfile = argptr;
	if(OutputUnitNo)
	{
	 cerr << "Output file: " << BOSoutfile << endl;
	 unlink(BOSoutfile);
	 sprintf(out, "OPEN BOSOUTPUT UNIT=9 FILE=\"%s\" WRITE  STATUS=NEW RECL=3600", BOSoutfile);
	 if (!fparm_c(out)) 
	 {
	  cerr << argv[0] << ": Unable to open file: " << out << " " <<  strerror(errno) << endl;	 
	  exit(1);
	 }
	}
	break;

    case 'M':
	max = atoi(++argptr);
	break;
    case 'R':
	setRun = atoi(++argptr);
	break;
          
          
    case 'h':
	PrintUsage(argv[0]);
	exit(0);
	break;

    case 'p':
	partbank0 = atoi(++argptr);
	break;

    case 'L':
	printLabels();
	exit(0);
	break;

    default:
	cerr << "Unrecognized argument: " << argptr << endl;;
	break;
   }
  }
 }
 cerr << " output ascii file is :" << asciioutfile <<endl;
 output.open(asciioutfile, ios::out);

 cerr << "Parsing bank: " << partbank0 << endl;

 // Initialize BOS
 bnames_(&MaxBanks);
 initbos();
 configure_banks(stderr,0);

 for (int i = 1; i < argc; ++i) 
 {
  argptr = argv[i];
  // process all arguments on command line.
  if (*argptr != '-') 
  {
   // we have a file to process
   clasEvent event(argptr, &bcs_, partbank0, 0);
      
   // this is in the wrong place threeVec myVert=event.V();   //jb v13 *************************************     

   cerr << "initialize:\t" << argptr << endl;
   //     cout << argptr <<endl; //jb v13 puneet wanted me to print this out to see what it does
   Dispatch = isDispatcher(argptr);
   if (event.status()) 
   {
	ret = 1;
	while ((max ? Nevents < max : 1) && ret)
	{
	 // process every event in the file
	 ret = event.read(partbank0);
	 if (ret == DISIO_DATA) 
	 {  
	  
	  Nevents++;
                  
	  if (event.status()) 
	  {
	   if (triggerMask ? (triggerMask & event.trig()) : 1) 
	   {
		int runno = event.run();     
		//int runno = 19660;
		if(setRun)
		{
		 runno = setRun;
		}
		ConfigEvent(runno,0); 
		/* Initialize the TOF geometry.  This is needed regardless of whether you remake the SC reconstruction banks or not.  However, for the regeneration case, this is done in ConfigEvent. */
		StartRun(runno);
		writeFlag = ProcessEvent(event,verbose, IFLAG) ;
		if (BOSoutfile && writeFlag) 
		{
		 if (DropFlag) 
		 {
		  DropList(DropFlag);
		 }
		 putBOS(&bcs_,9,"E");
		 Nwrite++;
		}
		dropAllBanks(&bcs_,"E");
		cleanBanks(&bcs_);
		Nproc++;
	   }
	  }
	 }
	 else if (ret == DISIO_COMMAND) 
	 {
 	  cerr << "Message from Giant Head: " << getBuffer() << endl;;
     }
	}
	cerr << "\nTotal number of itape records read:\t" << Nevents << endl;
	cerr << "Total number of events processed:\t" << Nproc << endl;
	cerr << "\tTotal number of records written:\t" << Nwrite << endl;
   }
   else 
   {
	cerr << "Unable to open " << argptr << endl;
   }
  }
 }
  
 if (Dispatch) 
 {
  disIO_command("FINISHED");
 }
  
 cerr << "\nTotal number of itape records:\t" << Nevents << endl;

 if (BOSoutfile)
 {
  putBOS(&bcs_,9, "0");
  sprintf(out, "CLOSE BOSOUTPUT UNIT=9");
  fparm_c(out);  
 }
   

  return (0);
}


// ------------------------------------------------
// ---------------- ProcessEvent ------------------
// ------------ Make all analysis here ------------
// ------------------------------------------------

int ProcessEvent(clasEvent &my_event,int verbose, int IFLAG)
{
 int nReturnValue = 0;
 //static int nCount = 0;
 
 if (my_event.N(KPlus)!=2 || my_event.N(PiMinus)!=1 )
 {
  return (0);
 }
  
  
 // if there Pi+ pi+ K- in Part banks, get four vectors of these particles
 // and set beam and target four vectors
 
 
 fourVec kp1,kp2, kp0, pim;
 fourVec pip1, pip2;
 fourVec beam,psbeam,fixbeam,target(PROTON_MASS,threeVec(0.0,0.0,0.0));
 double beamp_woecor = -100, beamp = -100.0, psbeamp = -100.0, mmbeamp = -100.0, fixbeamp = -100.0;
 double newbeam1 = -100.0;
 double newbeam2 = -100.0;
 double CASCADE0_MASS = 1.31483;
 double CASCADE_MASS = 1.32131;
 clasTAGR_t *TAGR = (clasTAGR_t *)getBank(&bcs_,"TAGR"); 
 clasBID_t *TBID  =  (clasBID_t *)getBank(&bcs_,"TBID"); 
 threeVec myVert=my_event.V();; //jb v13 wrong gives error in compiler
 //threeVec myVert;
 int runno=0;
 int evtno=0;
 double tMin;
 //jb v13  tagr_t *tagr = my_get_photon_tagr(TAGR, TBID, myVert); 
 tagr_t *tagr = my_get_photon_tagr(TAGR, TBID, myVert);  //jb v13 calling it
 


 int eid = 0;

 float tpho; //jb npho

 //jb v12  fourVec wo_beam;  //jbv07_3  made for showing missing mass without beam energy corrections.
 //jb v12  double wo_beamp = -100.0;   //jbv07_3  made for showing missing mass without beam energy corrections.

 fourVec kp1_woeloss, kp2_woeloss, pim_woeloss;  //jb v12 made this for showing missing mass spectrum without eloss corrections.
 kp1_woeloss=my_event.cp(KPlus,1).p();
 kp2_woeloss=my_event.cp(KPlus,2).p();
 pim_woeloss=my_event.cp(PiMinus,1).p();
 //jb v12: these 3 above were filled BEFORE my_event.eLoss("g11a", IFLAG)

 if(tagr)
 {
  eid = tagr->e_id;
  beamp_woecor = tagr->erg;
  //jb v12    wo_beamp = tagr->erg;
  tpho=tagr->tpho; //jb npho 
 }
  

 //--------------------------------------------------------v35k the energy correcton-------------------------------------------------------
 beamp = corrected_beam_energy(my_event.run(), beamp_woecor);
 //make a 4vec from the beam_woecor for later checking
 fourVec beam_woecor; 
 beam_woecor.set(beamp_woecor,threeVec(0.0,0.0,beamp_woecor));
 //---------------------------------------------------------------------------------------------------------------------------------------

 runno=my_event.run();
 evtno=my_event.event();
 if(corr)
 {
  //do eloss and mommentum correction
  my_event.eLoss("g11a", IFLAG);
  if(datatype) 
  {
   //my_event.momentumCorrection();
   psbeamp=my_event.lgTAGRcorrection(beamp, eid);
   if(runno>44109)
   {                                     //\\ this if gets done for all g12  runs check to see if this is right.
	photonenergy_(&beamp,&runno,&newbeam1,&newbeam2);
	psbeamp = newbeam1*0.99824;
	mmbeamp = newbeam2*0.99944;
   }
   else if(runno>43489)
   {
	photonenergy_(&beamp,&runno,&newbeam1,&newbeam2);
	psbeamp = newbeam1*1.0006;
	mmbeamp = newbeam2*1.0018;
   }
  }
  else 
  {
   psbeamp=beamp;
   mmbeamp=beamp;
  }
 }
 //jb v11  beam.set(mmbeamp,threeVec(0.0,0.0,mmbeamp));
 beam.set(beamp,threeVec(0.0,0.0,beamp));  //jb v11  took out the mmbeam crap.
 //jb v12  wo_beam.set(wo_beamp,threeVec(0.0,0.0,wo_beamp)); //jbv07_3  made for showing missing mass without beam energy corrections.
 psbeam.set(psbeamp,threeVec(0.0,0.0,psbeamp));
 kp1=my_event.cp(KPlus,1).p();
 kp2=my_event.cp(KPlus,2).p();
 pim=my_event.cp(PiMinus,1).p();


 //if kp1 is slower, reverse the order 
 if(kp1.r()<kp2.r())
 {
 kp0 = kp1;
 kp1 = kp2;
 kp2 = kp0;
 }
 //check the Vtime first to clean up the data
 float scv=my_event.scVtime();
 float stv=my_event.stVtime();
 threeVec Vert = my_event.V();

 int targZ=0, targXY=0, st=0;
 if(abs(Vert.z()+10)<=20) targZ=1;   //\\ lei abandoned this cut 
 if((Vert.x()*Vert.x()+Vert.y()*Vert.y())<=4) targXY=1;  //\\ this too
 if(abs(my_event.scVtime()-my_event.stVtime())<=3) st=1; //\\ this cut should be relaxed then the data should be looked at to determine where to place cuts
 //jb v35k adding the beam energy filter: this is the energy needed for production of k+ k+ Xi- from gamma and proton
 int bb=0;
 if(beamp > 2.373) bb=1;


 float mm2kpkp=(beam + target - kp2 - kp1).lenSq();
 //jb v11 edit_1   search for edit_1 to find the other bracket (just above return(nReturnValue)) this is taken off to relax the cut:  if(st){
 if(st&&bb)  //jb v35k putting the filter back
 {
  nReturnValue = 1;

  output << beamp_woecor << " "; //jb v35k beam_woecor
  output << ~(beam_woecor + target - kp1 - kp2) << " " << ~(beam_woecor + target-kp1-kp2 - pim) <<" "; //jb v35k mm_woecor
  output << ~(beam + target - kp1_woeloss - kp2_woeloss) << " " << ~(beam + target-kp1_woeloss-kp2_woeloss - pim_woeloss)<<" "; //jb v37k mm_woeloss
  output << ~(beam_woecor + target - kp1_woeloss - kp2_woeloss) << " " <<~(beam_woecor + target-kp1_woeloss-kp2_woeloss - pim_woeloss)<<" "; //jb v35k mm_woecoreloss
	
  
  output<<runno<<" "<<evtno<<" ";
  output<<my_event.scVtime()<<" "<<my_event.stVtime()<<" "<<my_event.vtime()<<" ";
  output<<Vert.x()<<" "<<Vert.y()<<" "<<Vert.z()<<" ";
  output<<my_event.N(KPlus)<<" "<<my_event.N(PiMinus)<<" "<<my_event.N(KMinus)<<" "<<my_event.N(Proton)<<" "<<my_event.N(PiPlus)<<" ";
  //jb v07  output << fit.prob() << " "<<fit.chisq()<<" ";
  //jb v07 output<<fit.beamEnergy()<<" "<<~(beamOut+target-kp1Out-kp2Out-pimOut)<<" ";
  //jb v07 output<<~(beamOut+target-kp1Out-kp2Out)<<" ";
  //jb v07 output<<~(beamOut+target-kp1Out)<<" "<<~(beamOut+target-kp2Out)<<" "<<~(beamOut+target-pimOut)<<" "<<~(pimOut+kp1Out)<<" "<<~(pimOut+kp2Out)<<" ";
  double mppim = -10;
  fourVec proton;
  if(my_event.N(Proton))
  {
   proton = my_event.cp(Proton,1).p();
   mppim = ~(proton + pim);
  }
  output<<mppim<<" ";

  clasParticle cpkp1, cpkp2, cppim;
  if(kp1.r()>kp2.r())
  {
   //also check the beta's
   output<<my_event.cp(KPlus, 1).beta()<<" ";
   output<<my_event.cp(KPlus, 2).beta()<<" ";
   output<<my_event.cp(PiMinus, 1).beta()<<" ";
   output<<my_event.cp(KPlus, 1).Beta()<<" ";
   output<<my_event.cp(KPlus, 2).Beta()<<" ";
   output<<my_event.cp(PiMinus, 1).Beta()<<" ";
   //also check the sctime and scpath
   output<<my_event.cp(KPlus, 1).sc_time()<<" ";
   output<<my_event.cp(KPlus, 2).sc_time()<<" ";
   output<<my_event.cp(PiMinus, 1).sc_time()<<" ";
   output<<my_event.cp(KPlus, 1).scPathLen()<<" ";
   output<<my_event.cp(KPlus, 2).scPathLen()<<" ";
   output<<my_event.cp(PiMinus, 1).scPathLen()<<" ";
   //check the TOF mass
   output<<my_event.cp(KPlus, 1).mass()<<" ";
   output<<my_event.cp(KPlus, 2).mass()<<" " ;
   output<<my_event.cp(PiMinus, 1).mass()<<" ";
   //check st_vtime for different particles
   output<<my_event.cp(KPlus, 1).stVtime()<<" ";
   output<<my_event.cp(KPlus, 2).stVtime()<<" "; 
   output<<my_event.cp(PiMinus, 1).stVtime()<<" ";

   output<<my_event.cp(KPlus, 1).isSThit()<<" ";  	//jb v16
   output<<my_event.cp(KPlus, 2).isSThit()<<" ";   //jb v16
   output<<my_event.cp(PiMinus, 1).isSThit()<<" "; //jb v16
	
   output<<my_event.cp(KPlus, 1).st_id()<<" ";  	//jb v17
   output<<my_event.cp(KPlus, 2).st_id()<<" ";   //jb v17
   output<<my_event.cp(PiMinus, 1).st_id()<<" "; //jb v17 
	
   cpkp1 = my_event.cp(KPlus, 1);
   cpkp2 = my_event.cp(KPlus, 2);
  }

  else 
  {
   //also check the beta's
   output<<my_event.cp(KPlus, 2).beta()<<" ";
   output<<my_event.cp(KPlus, 1).beta()<<" ";
   //check the TOF mass
   output<<my_event.cp(KPlus, 2).mass()<<" ";
   output<<my_event.cp(KPlus, 1).mass()<<" " ;
   //check st_vtime for different particles
   output<<my_event.cp(KPlus, 2).stVtime()<<" ";
   output<<my_event.cp(KPlus, 1).stVtime()<<" "; 
   cpkp1 = my_event.cp(KPlus, 2);
   cpkp2 = my_event.cp(KPlus, 1);
  }
   
  cppim = my_event.cp(PiMinus, 1);

  double vkp1pim=-1000, vkp2pim=-1000, vkpkp=-1000;
   
  vkp1pim = my_event.vert2Separation(cpkp1, cppim);
  vkp2pim = my_event.vert2Separation(cpkp2, cppim);
  vkpkp = my_event.vert2Separation(cpkp1, cpkp2);
    
  
  //check the vertex separation
  output<<vkp1pim<<" "<<vkp2pim<<" "<<vkpkp<<" ";

  //now plot the masses
  //jb  output<<mmbeamp<<" "<<psbeamp<<" "<<~(beam+target)<<" "<<(kp1+kp2-beam).lenSq()<<" ";

  //jb v11  output<<mmbeamp<<" "<<~(beam+target)<<" "<<(kp1+kp2-beam).lenSq()<<" ";    //jb
  output<<beamp<<" "<<~(beam+target)<<" "<<(kp1+kp2-beam).lenSq()<<" ";   //jb v11 replaced above line with this because i needed to take out mmbeamp 

  output<<(kp1+kp2+pim-beam).lenSq()<<" ";
  output<<(kp1+pim-beam).lenSq()<<" "<<(kp2+pim-beam).lenSq()<<" ";
  output << (beam + target - kp1 - kp2).lenSq() << " ";
  //jb  output << (psbeam + target - kp1 - kp2).lenSq() << " ";
  output << (beam + target - kp1).lenSq() << " ";
  output << (beam + target - kp2).lenSq() << " ";  
  output << (beam + target - kp1-pim).lenSq() << " ";
  output << (beam + target - kp2-pim).lenSq() << " ";  
  output << (beam + target - kp1 - kp2-pim).lenSq() << " ";  
  //jb output << (psbeam + target - kp1 - kp2-pim).lenSq() << " ";
  //output << (beam + target - kp1_woeloss - kp2_woeloss).lenSq() << " ";   //jbv07_3
  //output << (beam + target - kp1_woeloss - kp2_woeloss - pim_woeloss).lenSq() << " ";  //jbv07_3 

  //invariant masses
  output << ~(kp2 + kp1) << " "<<~(kp1+pim)<<" "<<~(kp2+pim)<<" ";

  //missing masses
  output << ~(beam+target-kp1) << " ";
  output << ~(beam+target-kp2) << " "<<~(beam+target-kp1-kp2)<<" " << ~(beam + target - kp1 - kp2 - pim) << "";
  //check the momentums
  output <<kp1.r()<<" "<<kp2.r()<<" "<<pim.r()<<" ";
  output << (beam + target - kp1 - kp2 - pim).x() << " ";
  output << (beam + target - kp1 - kp2 - pim).y() << " ";
  output << (beam + target - kp1 - kp2 - pim).z() << " ";
  output << (beam + target - kp1 - kp2 - pim).r() << " ";
  //check the missing energy
  output << (beam + target - kp1 - kp2 - pim).t() << " ";
  

 
  //get the t transfer from proton
  tMin = tmin(beamp,0.0,PROTON_MASS,~(kp1 + kp2 + pim),CASCADE0_MASS);
  output << -((kp1 + kp2 + pim - beam).lenSq() - tMin) << " ";
   
  //constrain cascade and replot the k+ cascade masses
  fourVec miss=beam + target - kp1 - kp2 - pim;
  fourVec kkpi = kp1 + kp2 + pim;
  fourVec miss2=beam + target - kp1 - kp2;
  fourVec kk = kp1 + kp2;
  fixbeamp = (CASCADE0_MASS*CASCADE0_MASS - kkpi.lenSq()  - PROTON_MASS*PROTON_MASS + 2*PROTON_MASS*kkpi.t())/(2*(PROTON_MASS+kkpi.z()-kkpi.t()));
  fixbeam.set(fixbeamp,threeVec(0.0,0.0,fixbeamp));
  double fixbeamp2 = (CASCADE_MASS*CASCADE_MASS - kk.lenSq()  - PROTON_MASS*PROTON_MASS + 2*PROTON_MASS*kk.t())/(2*(PROTON_MASS+kk.z()-kk.t()));
  fourVec fixbeam2;
  fixbeam2.set(fixbeamp2,threeVec(0.0,0.0,fixbeamp2));
  fourVec psmiss=psbeam + target - kp1 - kp2 - pim;
  double Ecascade = sqrt(CASCADE0_MASS*CASCADE0_MASS + miss.r()*miss.r());
  double psEcascade = sqrt(CASCADE0_MASS*CASCADE0_MASS + psmiss.r()*psmiss.r());
  double Elambda = sqrt(LAMBDA_MASS*LAMBDA_MASS + miss.r()*miss.r());
  fourVec cascade, lambda, pscascade;
  double Ecascadem = sqrt(CASCADE_MASS*CASCADE_MASS + miss2.r()*miss2.r());
  fourVec cascadem;
  cascade.set(Ecascade, threeVec(miss.x(), miss.y(), miss.z()));
  cascadem.set(Ecascadem, threeVec(miss2.x(), miss2.y(), miss2.z()));
  pscascade.set(psEcascade, threeVec(psmiss.x(), psmiss.y(), psmiss.z()));
  lambda.set(Elambda, threeVec(miss.x(), miss.y(), miss.z()));
  //replot the constrained masses
  //jb  output<<~(cascade + kp1) <<" "<<~(cascade + kp2)<<" "<<~(cascade + pim)<<" "<<~(lambda+pim)<<" "<<~(pscascade + pim)<<" "<<~(fixbeam+target-kp1-kp2)<<" "<<fixbeamp<<" ";
  output<<~(cascade + kp1) <<" "<<~(cascade + kp2)<<" "<<~(cascade + pim)<<" "<<~(lambda+pim)<<" "<<~(fixbeam+target-kp1-kp2)<<" "<<fixbeamp<<" ";  //jb
  output<<~(cascadem + kp1) <<" "<<~(cascadem + kp2)<<" "<<~(cascadem - pim)<<" "<<~(fixbeam2+target-kp1)<<" "<<~(fixbeam2+target-kp2)<<" "<<fixbeamp2<<" ";  //jb v15 added the casm - pim output
  //replace k+ with pi+ and replot the k+ related masses
  double Epip1 = sqrt(PI_CHARGED_MASS*PI_CHARGED_MASS+kp1.r()*kp1.r());
  pip1.set(Epip1, threeVec(kp1.x(), kp1.y(), kp1.z()));
  double Epip2 = sqrt(PI_CHARGED_MASS*PI_CHARGED_MASS+kp2.r()*kp2.r());
  pip2.set(Epip2, threeVec(kp2.x(), kp2.y(), kp2.z()));
  //jbv07_2  output<<~(beam+target-pip1-pip2-pim) << " " << ~(beam+target-kp1-pip2-pim) <<" "<<~(beam+target-pip1-kp2-pim)<<" "<<~(kp1+pip2+pim)<<" "<<~(kp2+pip1+pim)<<" "<<~(pip1+pim)<<" "<<~(pip2+pim)<<" "<<~(pip1+pip2+pim)<<" ";

  //jbv07_2
  output<< ~(beam+target-pip1-pip2-pim) << " " << ~(beam+target-kp1-pip2-pim) <<" " << ~(beam+target-pip1-kp2-pim) << " " << ~(beam+target-pip1-pip2) << " " << ~(beam+target-kp1-pip2) << " " << ~(beam+target-kp2-pip1) << " " << ~(beam+target-kp1) << " " << ~(beam+target-kp2) << " " << ~(beam+target-pip1) << " " << ~(beam+target-pip2) << " " << ~(kp1+pip2+pim) << " " << ~(kp2+pip1+pim)<< " " << ~(pip1+pim) << " " << ~(pip2+pim) << " " << ~(pip1+pip2+pim) << " " ;

  output<< ~(beam+target-pip1-pim) << " " << ~(beam+target-pip2-pim) << " ";  //jbv07_3

  //get the meson system 4-vector
  fourVec X;
  X=beam+target-kp1-kp2;
  fourVec kp1_1, kp1_2;
  fourVec kp2_1, kp2_2;
  fourVec cascadem_1, cascadem_2;
  fourVec fixbeam2_1, fixbeam2_2;
  fourVec Y1, Y2;
  kp1_1=kp1;
  kp1_2=kp1;
  kp2_1=kp2;
  kp2_2=kp2;
  cascadem_1=cascadem;
  cascadem_2=cascadem;
  fixbeam2_1=fixbeam2;
  fixbeam2_2=fixbeam2;
  Y1=cascadem+kp2;
  Y2=cascadem+kp1;


  // jb v18 
  fourVec pim_1, lambda_1, X_1;
  pim_1=pim;
  lambda_1=lambda;
  X_1=X;
  //jb v20
  fourVec cascadem_my;
  cascadem_my = cascadem;





  //=======================================================g12 kinematic fitting======================================================

  //-----------------------------------------------------------------KF---------------------------------------------------------------
  vector<clasParticle> cp_kpkppim;
  cp_kpkppim.push_back(cpkp1);
  cp_kpkppim.push_back(cpkp2);
  cp_kpkppim.push_back(cppim);
  kinfit_output_t kfit_kpkppim = my_kinematic_fit(beam, PROTON_MASS, cp_kpkppim, LAMBDA_MASS, CASCADE_MASS, "g12", Vert);

  //fill parameters with new fitted values
  fourVec kf_kp1 = kfit_kpkppim.parts[0];
  fourVec kf_kp2 = kfit_kpkppim.parts[1];
  fourVec kf_pim = kfit_kpkppim.parts[2];
  fourVec kf_beam = kfit_kpkppim.beam;

  //--------- make the pdg lambda and cascade---------------------------------
  //the missing 4-momentums
  fourVec kf_miss = kf_beam + target - kf_kp1 - kf_kp2 - kf_pim;
  fourVec kf_miss2 = kf_beam + target - kf_kp1 - kf_kp2;
  //the pdg energy
  double kf_Elambda = sqrt(LAMBDA_MASS*LAMBDA_MASS + kf_miss.r()*kf_miss.r());
  double kf_Ecascadem = sqrt(CASCADE_MASS*CASCADE_MASS + kf_miss2.r()*kf_miss2.r());
  // fill the lambda and cascade
  fourVec kf_lambda, kf_cascadem;
  kf_lambda.set(kf_Elambda, threeVec(kf_miss.x(), kf_miss.y(), kf_miss.z()));
  kf_cascadem.set(kf_Ecascadem, threeVec(kf_miss2.x(), kf_miss2.y(), kf_miss2.z()));
  //-----------------------------------------------------------------------------


  // prob, chi2 and pulls
  double kf_prob = kfit_kpkppim.prob;
  double kf_chi2 = kfit_kpkppim.chi2;
  double kf_pull_beam = kfit_kpkppim.pull_beam;
 
  //some output variables 
  output<<kf_prob<<" ";
  output<<kf_chi2<<" ";
  output<<kf_pull_beam<<" ";

  output << ~(target + kf_beam - kf_kp1 - kf_kp2 - kf_pim) << " ";
  output << ~(target + kf_beam - kf_kp1 - kf_kp2) << " ";
  output << ~(kf_lambda + kf_pim) << " ";
  output << ~(kf_cascadem - kf_pim) << " ";

  //now to check the effects of the kinfit
  output << (beam - kf_beam).r() <<" ";
  output << (kp1 - kf_kp1).r() <<" ";
  output << (kp2 - kf_kp2).r() <<" ";
  output << (pim - kf_pim).r() <<" ";
  


  //-----------------------------------------------------------------KF2---------------------------------------------------------------
  vector<clasParticle> cp2_kpkppim;
  cp2_kpkppim.push_back(cpkp1);
  cp2_kpkppim.push_back(cpkp2);
  cp2_kpkppim.push_back(cppim);
  kinfit_output_t kfit2_kpkppim = kinematic_fit(beam, PROTON_MASS, cp2_kpkppim, CASCADE0_MASS, "g12", Vert);

  //fill parameters with new fitted values
  fourVec kf2_kp1 = kfit2_kpkppim.parts[0];
  fourVec kf2_kp2 = kfit2_kpkppim.parts[1];
  fourVec kf2_pim = kfit2_kpkppim.parts[2];
  fourVec kf2_beam = kfit2_kpkppim.beam;

  //--------- make the pdg lambda and cascade---------------------------------
  //the missing 4-momentums
  fourVec kf2_miss = kf2_beam + target - kf2_kp1 - kf2_kp2 - kf2_pim;
  //the pdg energy
  double kf2_Ecascade0 = sqrt(CASCADE0_MASS*CASCADE0_MASS + kf2_miss.r()*kf2_miss.r());
  // fill the lambda and cascade
  fourVec kf2_cascade0;
  kf2_cascade0.set(kf2_Ecascade0, threeVec(kf2_miss.x(), kf2_miss.y(), kf2_miss.z()));
  //-----------------------------------------------------------------------------


  // prob, chi2 and pulls
  double kf2_prob = kfit2_kpkppim.prob;
  double kf2_chi2 = kfit2_kpkppim.chi2;
  double kf2_pull_beam = kfit2_kpkppim.pull_beam;

  //some output variables 
  output<<kf2_prob<<" ";
  output<<kf2_chi2<<" ";
  output<<kf2_pull_beam<<" ";

  output << ~(target + kf2_beam - kf2_kp1 - kf2_kp2 - kf2_pim) << " ";
  output << ~(target + kf2_beam - kf2_kp1 - kf2_kp2) << " ";
  output << ~(kf2_cascade0 + kf2_pim) << " ";


  //now to check the effects of the kinfit
  output << (beam - kf2_beam).r() <<" ";
  output << (kp1 - kf2_kp1).r() <<" ";
  output << (kp2 - kf2_kp2).r() <<" ";
  output << (pim - kf2_pim).r() <<" ";



  //=========================================================COMPUTING THE ANGLES===================================================================
  //----------------------------------------------------------jb v24k & jb v25k -----------------------------------------
  // going to use theese quantities for obtaining the pion angles WRT the axies of interest
 
  // first get quantities in the lab frame  
  fourVec KP1, KP2, PIM, BEAM, PRO, CAS, LAM, KPKP, TARG; 
  KP1 = kp1;
  KP2 = kp2;
  KPKP = kp1 + kp2; 
  PIM = pim;
  BEAM = beam;
  CAS = cascadem;  //this is the pdg kind
  LAM = lambda;   // this is the pdg kind
  TARG = target;

  //BOOST TO Xi FRAME
  lorentzTransform LCAS;
  LCAS.set(CAS); 
  KPKP *= LCAS;
  PIM *= LCAS;
  BEAM *= LCAS;
  CAS *= LCAS;
  LAM *= LCAS;

  //check that we are in the correct refrence frame:
  //  cout << "the total energy of the cascade should be its mass in this ref-frame: CAS.t() = " << CAS.t() << endl;

  

  // fill the needed (unit) three vectors
  threeVec T_PIM_unit, T_KPKP_unit, T_BEAM_unit, T_LAM_unit;
  T_BEAM_unit.set(BEAM.x()/BEAM.r(), BEAM.y()/BEAM.r(), BEAM.z()/BEAM.r());  
  T_KPKP_unit.set(KPKP.x()/KPKP.r(), KPKP.y()/KPKP.r(), KPKP.z()/KPKP.r() );
  T_PIM_unit.set(PIM.x()/PIM.r(), PIM.y()/PIM.r(), PIM.z()/PIM.r() );
  T_LAM_unit.set(LAM.x()/LAM.r(), LAM.y()/LAM.r(), LAM.z()/LAM.r() );
  
  // (z' = beam momentum) , (y' = beam.cross.kpkp), (x' = z'.cross.y') 
  
  threeVec xx,yy,zz;  //unit coordinate vectors
  zz.set(T_BEAM_unit.x(), T_BEAM_unit.y(), T_BEAM_unit.z());
  threeVec yyy = zz/T_KPKP_unit;
  yy.set(yyy.x()/yyy.r(), yyy.y()/yyy.r(), yyy.z()/yyy.r());
  xx = zz/yy;  //THIS SHOULD BE THE OTHER WAY AROUND FOR A RIGHT HANDED SYSTEM!!!!!!!!!!!!!!!!!!!!!!!

  //cout << "T_LAM_unit.r() =" << T_LAM_unit.r() << endl;
  //cout << "T_BEAM_unit.r()=" << T_BEAM_unit.r() << "  T_KPKP_unit.r()=" << T_KPKP_unit.r() << "  T_PIM_unit.r()=" << T_PIM_unit.r() << endl;
  //cout << "check normality: " << " xx.r()=" << xx.r() << "  yy.r()=" << yy.r() << "  zz.r()=" << zz.r() <<endl;
  //cout << "check orthogonalality:  (xx/yy).r()=" << (xx/yy).r() <<endl;
  //cout << "check orthogonalality:  (xx/zz).r()=" << (xx/zz).r() <<endl;
  //cout << "check orthogonalality:  (yy/zz).r()=" << (yy/zz).r() <<endl;
  //good so have an orthonormal coordinate system and normalized momenta of the particles
 
  //compute the angles of the pion
  double COSth_pi_x, COSth_pi_y, COSth_pi_z;
  COSth_pi_x = T_PIM_unit.x() * xx.x() + T_PIM_unit.y() * xx.y() + T_PIM_unit.z() * xx.z();
  COSth_pi_y = T_PIM_unit.x() * yy.x() + T_PIM_unit.y() * yy.y() + T_PIM_unit.z() * yy.z();
  COSth_pi_z = T_PIM_unit.x() * zz.x() + T_PIM_unit.y() * zz.y() + T_PIM_unit.z() * zz.z();

  //now compute the angles of the lambda
  double COSth_lam_x, COSth_lam_y, COSth_lam_z;
  COSth_lam_x = T_LAM_unit.x() * xx.x() + T_LAM_unit.y() * xx.y() + T_LAM_unit.z() * xx.z();
  COSth_lam_y = T_LAM_unit.x() * yy.x() + T_LAM_unit.y() * yy.y() + T_LAM_unit.z() * yy.z();
  COSth_lam_z = T_LAM_unit.x() * zz.x() + T_LAM_unit.y() * zz.y() + T_LAM_unit.z() * zz.z();


  // out put the angles
  output << COSth_pi_x << " " << COSth_pi_y << " " << COSth_pi_z << " ";
  output << COSth_lam_x << " " << COSth_lam_y << " " << COSth_lam_z << " ";

  //==========================================================================================================================================





  //Now get the angles
  //first print out angles in the lab
  // print angle of K+1 and K+2 in lab
  // LAB FRAME------------------------------------------------------------
  output << kp1.cosTheta() << " " << kp1.phi()/M_PI << " ";
  output << kp2.cosTheta() << " " << kp2.phi()/M_PI << " ";
  output << pim.cosTheta() << " " << pim.phi()/M_PI << " "; 
  output << X.cosTheta() << " " << X.phi()/M_PI << " ";
  lorentzTransform L, L1, L2;
  

  // Define a Lorentz Transformation to the CM-----------------------------
  L.set(beam + target);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
  kp1_1 *=L;
  kp1_2 *=L;
  kp2_1 *=L;
  kp2_1 *=L;
  cascadem_1 *=L;
  cascadem_2 *=L;
  Y1 *=L;
  Y2 *=L;
  fixbeam2_1 *=L;
  fixbeam2_2 *=L;


  //jb v18
  pim_1 *= L;
  lambda_1 *= L;
  X_1 *= L;
  cascadem_my *=L;  //jb v21

  //align beam along Z-axis-------------------------------------------------
  L.set(beam.phi(),beam.theta(),0.0);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
  output << kp1.cosTheta() << " " << kp1.phi()/M_PI << " ";
  output << kp2.cosTheta() << " " << kp2.phi()/M_PI << " ";
  output << pim.cosTheta() << " " << pim.phi()/M_PI << " ";
  output << X.cosTheta() << " " << X.phi()/M_PI << " ";

  //for cascadem-Lambda events, assume Kp1 is on the meson vertex
  L1.set(fixbeam2_1.phi(), fixbeam2_1.theta(),0.0); 
  kp1_1 *=L1;
  kp2_1 *=L1;
  fixbeam2_1 *=L1;
  Y1 *=L1;
  threeVec Cross1;
  Cross1 = fixbeam2_1/kp1_1;
  //move this to align with the the y-axis
  L1.set(Cross1.phi(),Cross1.theta()-M_PI/2.0,-M_PI/2.0);
  kp1_1 *=L1;
  kp2_1 *=L1;
  Y1 *=L1;
  // Now rotate to the helicity frame of X so the z axis is along the X momentum  
  L1.set(Y1.phi(),Y1.theta(),0.0);
  kp1_1 *=L1;
  kp2_1 *=L1;
  Y1 *=L1;

  // Now Boost to Y1 rest frame - since y-axis (above) is normal - will not change direction of y
  L1.set(Y1);
  kp1_1 *=L1;
  kp2_1 *=L1;
  output<<kp2_1.cosTheta()<<" "<<kp2_1.phi()/M_PI<<" ";

  //for cascadem-Lambda events, assume Kp2 is on the meson vertex
  L2.set(fixbeam2_2.phi(), fixbeam2_2.theta(),0.0); 
  kp1_2 *=L2;
  kp2_2 *=L2;
  fixbeam2_2 *=L2;
  Y2 *=L2;
  threeVec Cross2;
  Cross2 = fixbeam2_2/kp2_2;
  //move this to align with the the y-axis
  L2.set(Cross2.phi(),Cross2.theta()-M_PI/2.0,-M_PI/2.0);
  kp1_2 *=L2;
  kp2_2 *=L2;
  Y2 *=L2;
  // Now rotate to the helicity frame of Y2 so the z axis is along the X momentum  
  L2.set(Y2.phi(),Y2.theta(),0.0);
  kp1_2 *=L2;
  kp2_2 *=L2;
  Y2 *=L2;

  // Now Boost to Y2 rest frame - since y-axis (above) is normal - will not change direction of y
  L2.set(Y2);
  kp1_2 *=L2;
  kp2_2 *=L2;
  output<<kp1_2.cosTheta()<<" "<<kp1_2.phi()/M_PI<<" ";

  threeVec Cross;
  Cross = beam/X;
 
  //move this to align with the the y-axis
  L.set(Cross.phi(),Cross.theta()-M_PI/2.0,-M_PI/2.0);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
  
  // Now rotate to the helicity frame of X so the z axis is along the X momentum 
  L.set(X.phi(),X.theta(),0.0);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  pim *= L;
  X *=L;

  // Now Boost to X rest frame - since y-axis (above) is normal - will not change direction of y
  
  L.set(X);
  beam *= L;
  target *= L;
  kp1 *= L;
  kp2 *= L;
  X *=L;
  pim *=L;
  //now we are in the X (cascade*) helicity rest frame , output the 2-body decay angles of Pi- in X rest frame
  
  double alpha, beta;
  double ctpim = -10, phipim = -10;

  alpha=pim.phi();
  beta=pim.theta();
  ctpim = pim.cosTheta();
  phipim = pim.phi()/M_PI;
  if(fabs(ctpim)>0&&fabs(phipim)>0)
  {
   //jb v06    output<<ctpim<<" "<<phipim<<endl;
   output<<ctpim<<" "<<phipim<<" ";   //jb v06
  }
  else
  {
   //jb   output<<" -10 "<<" "<<" -10 "<<endl;
   output<<" -10 "<<" "<<" -10 "<<" ";   //jb v06
  }
  //jb v10  the number of photons
  output<<npho(TAGR, tpho, 0)<<" "; 
  output<<npho(TAGR, tpho, 1)<<" "; 
  output<<npho(TAGR, tpho, 2)<<endl; 
 } //jb v35k  this is the filter re-enabled
 return(nReturnValue);
}   // this is the end of processevent


//===================================================jb npho======================================================

int  npho( clasTAGR_t *TAGR, float tpho, int nb)
{                                                                //jb npho func
 int nph=0; //jb npho
 int k;  

 for(k=0;k<TAGR->bank.nrow;k++)
 {  
  if (abs(tpho - TAGR->tagr[k].tpho) < (0.05+2.004*nb)) 
  {                                                             //jb npho  
   nph=nph+1;
  }           
 }
 return(nph);
}
//--------------------------------------------------------------------------------------------------------------




//=====================================jb  my_get_photon_tagr===================================================

//tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID){ 
tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID, threeVec myVert)
{                                                                                 //jb v13
  
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
    
 for (i=0;i<TBID->bank.nrow;i++)
 {
  int trk_ind=TBID->bid[i].track;
  if(trk_ind)
  {     
   //jb v13      tprop=(TBTR->tbtr[trk_ind-1].vert.z - g12targz)/SPEED_OF_LIGHT*1e9;  //jb v11 i think i need to take this out
   tprop=(myVert.z() - g12targz)/SPEED_OF_LIGHT*1e9;  //jb v13
   //cout<<"myVert.z()=" << myVert.z() <<" :  TBTR->tbtr[trk_ind-1].vert.z="<< TBTR->tbtr[trk_ind-1].vert.z<<endl; //jb v13 just a check
   if (TBID->bid[i].st.stat)
   {       
    float mytime=-1000;             //jb v14
    float myenergy=-1000;           //jb v14
  
    for(j=0;j<TAGR->bank.nrow;j++)
    {
     float diff=fabs(TBID->bid[i].st.vtime-(TAGR->tagr[j].tpho+tprop));
     //jb v14     if (diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff
	 //jb v14	&& (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15)){/////////////}    	   
	 //cout <<abs(TAGR->tagr[j].tpho - tagr->tpho)<<endl;
	
	 if (( diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff || (abs(TAGR->tagr[j].tpho - mytime)<0.011&& (TAGR->tagr[j].erg) > myenergy)  )  &&  (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15))
	 {                                                                                //jb v14
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
//--------------------------------------------------------------------------------------------------------------------------------------    






