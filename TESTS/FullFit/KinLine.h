#ifndef _KinLine_H
#define _KinLine_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMatrixD.h"

typedef std::string String; 
// Full 3 x 3 covaraiance matrix from CLAS tracking 
TMatrixD CorrectCLAS_V(const TMatrixD &__covTrack,
		       const std::vector<String> &__p_names,
		       const std::vector<TLorentzVector> &__p4,
		       const std::vector<TVector3> &__vert,
		       bool __multi,bool __isMC, String &__xid);
// Full 5 X 5 covaraiance matrix from CLAS two track fitting 
TMatrixD CorrectCLAS_V5(const TMatrixD &__covTrack,
			const std::vector<String> &__p_names,
			const std::vector<TLorentzVector> &__p4,
			const std::vector<TVector3> &__vert,
			bool __multi,bool __isMC, String &__xid);
// Full 3 X 3 covaraiance matrix from CLAS two track fitting 
TMatrixD CorrectCLAS_V3(const TMatrixD &__covTrack,
			const std::vector<String> &__p_names,
			const std::vector<TLorentzVector> &__p4,
			const std::vector<TVector3> &__vert,
			bool __multi,bool __isMC, String &__xid);		      

// Full 2 X 2 covaraiance matrix from CLAS two track vertex fitting 
TMatrixD CorrectVert_V(const TMatrixD &__VTrack,
		       const std::vector<String> &__p_names,
                       const std::vector<TLorentzVector> &__p4,
                       const std::vector<TVector3> &__vert);

TMatrixD ReduceFromFit(const TMatrixD &__VMat,const TMatrixD &__FitV);

const std::vector<TVector3> VertConvert(const std::vector<TVector3> &__vert);
const std::vector<TVector3> SmearVector(const std::vector<TVector3> &__vert); 		      
// functions to get tracking parameters from 4-momentum
double LambdaTrack(const TLorentzVector &__p4);
double PhiTrack(const TLorentzVector &__p4);
double AlphaTrack(const TLorentzVector &__p4);

Double_t SmearUtility();
Double_t SmearUtility(Double_t var,Double_t parm_a, Double_t parm_b, Double_t parm_c);
TVector3 TrackToCLAS(Double_t p,Double_t lam,Double_t phi,Double_t alpha);

// reads in resolution parameters
bool ReadInResParams(double __pPars[2][6][15][3],double __lamPars[2][6][15],
		     double __phiPars[2][6][15]);

//_____________________________________________________________________________

// inline functions:

// Get CLAS sector number from 4-momentum
inline int GetSectorFromP4(const TLorentzVector &__p4){
  
  int sector = 0;
  double pi = 3.14159;
  double phi_lab = __p4.Phi();
  double phi = (180./pi)*phi_lab;
  
  if(std::abs(phi) <= 30.) sector = 1;
  else if(phi > 0.){
    if(phi <= 90.) sector = 2;
    else if(phi <= 150) sector = 3;
    else sector = 4;
  }
  else {
    if(std::abs(phi) <= 90.) sector = 6;
    else if(std::abs(phi) <= 150.) sector = 5;
    else sector = 4;
  }
  return sector;
}
//_____________________________________________________________________________

/// Returns the \f$ \theta \f$ bin (for resolution parameters)
inline int GetThetaBin(double __theta){
  
  double theta = __theta*180./3.14159;
  if(theta < 10.) return 0;
  else if(theta < 15) return 1;
  else if(theta < 20) return 2;
  else if(theta < 25) return 3;
  else if(theta < 30) return 4;
  else if(theta < 35) return 5;
  else if(theta < 40) return 6;
  else if(theta < 45) return 7;
  else if(theta < 50) return 8;
  else if(theta < 60) return 9;
  else if(theta < 70) return 10;
  else if(theta < 80) return 11;
  else if(theta < 90) return 12;
  else if(theta < 110) return 13;
  else return 14;
}
//_____________________________________________________________________________

/// Checks to see if resolution parameter file was read correctly
inline bool CheckRowsRead(const String &__fileName,int __rowsRead){
  
  if(__rowsRead != 90){ // should be 6 sectors X 15 rows/sector = 90 rows
    std::cout << "Error! <ReadInResParams> File read error: " << __fileName
	      << " Read in incorrect number of rows (" << __rowsRead 
	      << " instead of 90)" << std::endl;
    return false;
  }
  return true;
}
//_____________________________________________________________________________

#endif
