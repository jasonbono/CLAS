#include "KinLine.C"
#include "Kstream.C"

using namespace std;

int main() {

cout << "Kstream.C included" << endl;
cout << "jlab" <<endl;

/* Here is a general setup example for 1C and 4C fits
Here we are only using 3-component track fitting
without vertex constraints.  The example uses the
channel pi+ pi- p with the pi+ missing. 	  	  
*/
const int nparts = 2;  //number of particles in fit
	 		
vector<TLorentzVector> Vin4(nparts);  //set of 4-Vectors use in the fit
std::vector<TVector3> Vert(nparts);  //set of verties 
std::vector<string> p_names(nparts);  // string names
		      
/*This next bool sets the multiple scattering and energy spread correction
algorithm on (true) or off (false).  If off is used the CMU averaging
technique is employed that reads files form the ./parms directory for
particular particle types.  If tuned correctly the averaging method can 
work well for a reaction that has all final decay 
products starting at the primary interaction vertex.  Anything that decays 
from a secondary decay vertex can lead to inconsistent covariance and flag 
(true) is required.  Option false requires that you have tuned parameters
for you particle species.  These parms are called in KinLine.C and needs
to point to your copy of parms: 
*/

String fileName_base = "parms/";	

cout << "4 vectors and filename base defined" << endl;

			      
bool Multi = true; 
	  		      
/*This next bool tell the fitter to use either the covariance matrix
for data (false) or MC (true).  Ideally the MC sould be tuned well
enough that they are the same and so MC should remains false.*/
	  		      
bool MC = false;
			     
//This is for extra constraints not used in this example
     
std::vector<bool> set(nparts);
set[0] = false;
set[1] = false;			      
	
Double_t pho4 = 2.5;

Double_t m_targ = 0.93828;  //target mass
Double_t e_gamma = pho4;   //tagged photon energy
const int dim = 3*nparts+1;  //dimension of covariance matrix
TMatrixD covMatrix(dim,dim);  //Matrix you will use	  
TMatrixD covTrack(dim,dim);   // Matrix from CLAS TBER  
/* To fill covTrack you need the first three
components of the TBER information c11,c22,c33,c12,c13,c23,23
	
//covTrack(0,0) don't need to fill. 
//for each charged particle
covTrack(1,1) = c11*pow(p_mag,4);
covTrack(2,2) = c22;
covTrack(3,3) = c33;
covTrack(1,2) = -c12*q*p_mag*p_mag;
covTrack(2,1) = -c12*q*p_mag*p_mag;
covTrack(1,3) = -c13*q*p_mag*p_mag;
covTrack(3,1) = -c13*q*p_mag*p_mag;
covTrack(2,3) = c23;
covTrack(3,2) = c23; 
*/	  
	
// detected 4-Vectors
TLorentzVector P4pro(1,0,0,sqrt(1+pow(.938,2)));
TLorentzVector P4pim(0,1,0,sqrt(1+pow(.139,2)));

Vin4[0] = P4pro;
Vin4[1] = P4pim;

// vertex information or best guess
// this is used in Multiple Scattering and energy spread
TVector3 Vpro(0.,0.,0.);
TVector3 Vpim = Vpro;
Vert[0] = Vpro;
Vert[1] = Vpim;
// for particle names use pi-, pi+,e+,e-,k+,k-,(for gamma see HowToPhotons.txt)
//These must be filled in the array in the same order
//as the covariance matrix for each particle	  
p_names[0] = "p";
p_names[1] = "pi-";

// Get The full covariance for your fit
string experiment = "g12"; //options  g10a,g11a,g12,g13a
covMatrix = CorrectCLAS_V(covTrack,p_names,Vin4,Vert,Multi,MC,experiment);

// Declare your fit	  
Kstream yourfit;
/*yourfit.StringNames(p_names);
yourfit.FitInput(e_gamma,Vin4,covMatrix,m_targ);	  

// Declare the fit Hypothesis (use particle names a listed)
yourfit.Fit("pi+"); 	  // missing pi+

//you can also use numeric value for the mass
yourfit.Fit(0.13957); 	  // missing pi+
*/

//or you could try a 4C fit with nothing missing if you
//had detected the pi+ and fed it in as well
//yourfit.Fit();  //nothing missing

//Note you should only have one Fit hypothesis 
//declared in a scope.

//now take a confidence level here we used 5%	  
//The cut should be decided based on the relavant
//systematics for you analysis.

// Get Chi Squared and Confidence Level for fit.
/*
plot_1->Fill(yourfit.Prob());  //x:0-1
plot_2->Fill(yourfit.Chi2());	 //x:0-20 (or more)
*/

if(yourfit.Prob() > 0.05){
//plot histos
}

//If you want to reset the detected 4vectors
//based on the fit you done 
/*
if(yourfit.Prob() > 0.05){	  
e_gamma = yourfit.FitPhotonEnergy();  //resets tagger photon energy
for(int i = 0; i < 2; i++) Vin4[i] = yourfit.FitP4(i);
P4pho.SetPxPyPzE(0.,0.,e_gamma,e_gamma);  //new photon 4vector
P4pro = Vin4[0];  // new proton
P4pim =  Vin4[1]; // new pion
		   
P4_tot = P4pho + P4target;  //new total incoming
P4_mis = P4_tot - P4pro - P4pim;  // new high quality missing 4vector      			      
		   
}	  	  
*/



 return 0;
}
