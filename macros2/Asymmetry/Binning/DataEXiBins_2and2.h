#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H

//for 1x3 binning
const int Nb = 2; //nuber of beam bins
const int Nc = 2; //number of xi bins
TCut EXibin[Nb][Nc];
const char* EXibinString[Nb][Nc];
//Double_t EVal[Nb + 1][Nc];
Double_t XVal[Nb][Nc + 1];
XVal[0][0] = 1000;

EXibin[0][0] = " beam > 2.800000 && beam < 4.082500 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 " ; 
EXibin[0][1] = " beam > 4.082500 && beam < 5.500000  && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 " ; 
EXibin[1][0] = " beam > 2.800000 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < -0.410000 " ; 
EXibin[1][1] = " beam > 2.800000 && beam < 5.500000 && Xcmtheta > -0.410000 && Xcmtheta < -0.190000 " ; 


EXibinString[0][0] = " 2.8 <  E_{#gamma} < 4.0825 ::  -1 < cos(#theta_{#Xi}^{cm}) < 1 " ; 
EXibinString[0][1] = " 4.0825 <  E_{#gamma} < 5.5 ::  -1 < cos(#theta_{#Xi}^{cm}) < 1 " ; 
EXibinString[1][0] = " 2.8 <  E_{#gamma} < 5.5 ::  -1 < cos(#theta_{#Xi}^{cm}) < -0.41 " ; 
EXibinString[1][1] = " 2.8 <  E_{#gamma} < 5.5 ::  -0.41 < cos(#theta_{#Xi}^{cm}) < 1 " ; 









