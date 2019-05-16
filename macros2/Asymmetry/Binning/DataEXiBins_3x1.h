#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H

//for 1x3 binning
const int Nb = 3; //nuber of beam bins
const int Nc = 1; //number of xi bins
TCut EXibin[Nb][Nc];
Double_t EVal[Nb + 1];
Double_t XVal[Nb][Nc + 1];
EXibin[0][0] = " beam > 2.800000 && beam < 3.812500 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 " ; 
EXibin[1][0] = " beam > 3.812500 && beam < 4.433500 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 " ; 
EXibin[2][0] = " beam > 4.433500 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < 1.000000 " ; 
EVal[0] = 2.8;
EVal[1] = 3.8125;
EVal[2] = 4.4335;
EVal[3] = 5.5;
XVal[0][0] = -1;
XVal[0][1] = 1;
XVal[1][0] = -1;
XVal[1][1] = 1;
XVal[2][0] = -1;
XVal[2][1] = 1;