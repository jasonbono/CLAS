#ifndef _IMassFit_H
#define _IMassFit_H


#include <vector>
#include <string>
#include <iostream>
#include "TMatrixD.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TString.h"
#include "TPRegexp.h"
#include "KinLine.h"


typedef std::string String;

class IMassFit {
  
private:
  // Data Members (private):
  
    /* names for particle id in kinematic fit  added for neutral test*/
  std::vector<String> _p_names;  //Particle names  

  /* kinematic fitting statistical quantities */
  std::vector<double> _pulls; // Pull quantities of last fit
  double _chi2; ///< \f$ \chi^2 \f$ of last fit
  int _ndf; ///< Number of degrees-of-freedom of last fit

  /* kinematic quantities */
  std::vector<TLorentzVector> _p4in; ///< Particle 4-momenta (in)
  std::vector<TLorentzVector> _p4out; ///< Particle 4-momenta (out)
  std::vector<TVector3> _VERTin;
  TLorentzVector _pfout;  

  /* Variance matrix info */
  TMatrixD _V; ///< Variance matrix
  TMatrixD _VFit; ///< New fit Particle covariance matrix 
  double _sigma_fit[3]; ///< Fit errors on fit quantities

  /* missing particle info */
  double _invariantMass; ///< Invariant Mass in the hypothesis

  /* extra mass constraint info */

  // Functions (private):

  void _MainFitter();

  void _ResetForNewFit();

  void _Copy(const IMassFit &__kfit);

  void _ZeroOutFit();

  void _SetFitParticleErrors(const TMatrixD &__fittedV,
				 const TVectorD &__x);
				 
  void _SetNewFitV(const TMatrixD &__fittedV,
				 const TVectorD &__x);
public:
  // Create/Copy/Destroy:
  IMassFit();

  IMassFit(const IMassFit &__kfit){ 
    /// Copy Constructor
    this->_Copy(__kfit);
  }

  virtual ~IMassFit(){ 
    /// Destructor
    _pulls.clear();
    _p4in.clear();
    _p4out.clear();
  }

  IMassFit& operator=(const IMassFit &__kfit){
    /// Assignment operator
    this->_Copy(__kfit);
    return *this;
  }

  // Setters:

  inline void SetVMatrix(const TMatrixD &__VMat){ 
    /// Set the Variance matrix.
    _V.ResizeTo(__VMat);
    _V = __VMat;
  }

  inline void SetP4(const std::vector<TLorentzVector> &__p4){
    /// Set the input 4-momenta.
    _p4in = __p4;
  }

  inline void FitInput(const std::vector<String> &__p_names,const std::vector<TVector3> &__VERT,
  const std::vector<TLorentzVector> &__p4,
		       const TMatrixD &__VMat){
    //	 Info needed to fit      
    _p4in = __p4;
    _VERTin = __VERT;
    _V.ResizeTo(__VMat);
    _V = __VMat;
    _p_names = __p_names;    
  }

  inline double Chi2() const {
    // Return \f$ \chi^2 \f$ of the last fit.
    return _chi2;
  }

  inline int Ndf() const {
    // Return the number of degrees of freedom of the last fit
    return _ndf;
  }

  inline double GetPull(int __n) const {
    // Returns the n pull quantity
    return _pulls[__n];
  }

  inline TLorentzVector GetFinalP4() const {
    return _pfout;
  }
  
  inline const TLorentzVector& FitP4(int __n) const {
    return _p4out[__n];
  }

  inline const TMatrixD& GetFitVMat() const {
    return _VFit;
  }

  inline double GetFitParticleError(int __n) const {
    return _sigma_fit[__n];
  }

  inline const TMatrixD& GetVMat() const {
    return _V;
  }

  // Functions:

  double Prob() const {
    return TMath::Prob(_chi2,_ndf);
  }
 
  double Fit(double __invariantMass = -1.);
};
//_____________________________________________________________________________

#endif /* _IMassFit_H */


