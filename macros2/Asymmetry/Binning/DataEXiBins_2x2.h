#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H

//for 1x3 binning
const int Nb = 2; //nuber of beam bins
const int Nc = 2; //number of xi bins
TCut EXibin[Nb][Nc];
Double_t EVal[Nb + 1];
Double_t XVal[Nb][Nc + 1];
EXibin[0][0] = " beam > 2.800000 && beam < 4.082500 && Xcmtheta > -1.000000 && Xcmtheta < -0.430000 " ; 
EXibin[0][1] = " beam > 2.800000 && beam < 4.082500 && Xcmtheta > -0.430000 && Xcmtheta < 1.000000 " ; 
EXibin[1][0] = " beam > 4.082500 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < -0.390000 " ; 
EXibin[1][1] = " beam > 4.082500 && beam < 5.500000 && Xcmtheta > -0.390000 && Xcmtheta < 1.000000 " ; 
EVal[0] = 2.8;
EVal[1] = 4.0825;
EVal[2] = 5.5;
XVal[0][0] = -1;
XVal[0][1] = -0.43;
XVal[0][2] = 1;
XVal[1][0] = -1;
XVal[1][1] = -0.39;
XVal[1][2] = 1;