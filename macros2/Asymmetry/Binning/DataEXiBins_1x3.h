#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H

//for 1x3 binning
const int Nb = 1; //nuber of beam bins
const int Nc = 3; //number of xi bins
TCut EXibin[Nb][Nc];
Double_t EVal[Nb + 1];
Double_t XVal[Nb][Nc + 1];
EXibin[0][0] = " beam > 2.800000 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < -0.610000 " ; 
EXibin[0][1] = " beam > 2.800000 && beam < 5.500000 && Xcmtheta > -0.610000 && Xcmtheta < -0.190000 " ; 
EXibin[0][2] = " beam > 2.800000 && beam < 5.500000 && Xcmtheta > -0.190000 && Xcmtheta < 1.000000 " ; 
EVal[0] = 2.8;
EVal[1] = 5.5;
XVal[0][0] = -1;
XVal[0][1] = -0.61;
XVal[0][2] = -0.19;
XVal[0][3] = 1;