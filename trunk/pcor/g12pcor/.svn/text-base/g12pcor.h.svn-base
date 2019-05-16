// g12pcor package header file -*- C++ -*-
#ifndef _g12pcor_H
#define _g12pcor_H

// For more detailed descriptions of the functions, see g12pcor.cc

extern "C" { // 'dumb it down' for c and fortran
//_____________________________________________________________________________
  // Tagger Correction:
  /* C/C++ Function:
   * Parameters: eg         Measured photon energy
   *             e_beam     Beam energy
   *             eid        E-paddle id in the tagger
   *             runNumber  CLAS run number
   *
   * Returns: Corrected photon energy
   */
  float g12TaggerCor(float __eg,int __eid,int __runNumber);

  /* FORTRAN Subroutine:
   * Parameters: eg         Measured photon energy
   *             e_beam     Beam energy
   *             eid        E-paddle id in the tagger
   *             runNumber  CLAS run number
   *             egCor      Corrected photon energy
   */
  void g12TaggerCor_(float *__eg,int *__eid,int *__runNumber,
             float *__egCor);
//_____________________________________________________________________________
  // Momentum Corrections:
  /* C/C++ Function:
   * Parameters: p3[3]    Measured 3-momentum [x,y,z]
   *             q        Charge (ex. -1 for pi-)
   *             p3cor[3] Corrected 3-momentum [x,y,z]
   */
  void g12MomCor(float __p3[3],int __q,float __p3cor[3]);

  /* FORTRAN Subroutine:
   * Parameters: p3[3]    Measured 3-momentum [x,y,z]
   *             q        Charge (ex. -1 for pi-)
   *             p3cor[3] Corrected 3-momentum [x,y,z]
   */
  void g12MomCor_(float __p3[3],int *__q,float __p3cor[3]);
//_____________________________________________________________________________
  // Fiducial Cuts:
  /* C/C++ Function:
   * Parameters: p3[3]  Measured 3-momentum [x,y,z]
   *             q      Charge (ex 1 for proton)
   *
   * Returns: true = good fiducial region, false otherwise
   */
  bool g12FiducialCut(float __p3[3],int __q);

  /* FORTRAN Subroutine:
   * Parameters: p3[3]   Measured 3-momentum [x,y,z]
   *             q       Charge (ex 1 for pi+)
   *             cut     Set to 1 if good fiducial region, 0 otherwise
   */
  void g12FiducialCut_(float __p3[3],int *__q,int *__cut);
//_____________________________________________________________________________
}

#endif /* _g12pcor_H */
