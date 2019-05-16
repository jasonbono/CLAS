#ifndef DATAEXIBINS_H
#define DATAEXIBINS_H

//for 8 and 8 binning
const int Nb = 2; //nuber of bin types
const int Nc = 8; //number of e and xi bins
TCut EXibin[Nb][Nc];
const char* EXibinString[Nb][Nc];
//Double_t EVal[Nb + 1][Nc];
Double_t XVal[Nb][Nc + 1];
XVal[0][0] = 1000;

EXibin[0][0] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -1.000000 && Xcmtheta < -0.850000 " ; 
EXibin[0][1] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.850000 && Xcmtheta < -0.730000 " ; 
EXibin[0][2] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.730000 && Xcmtheta < -0.630000 " ; 
EXibin[0][3] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.630000 && Xcmtheta < -0.530000 " ; 
EXibin[0][4] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.530000 && Xcmtheta < -0.390000 " ; 
EXibin[0][5] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.390000 && Xcmtheta < -0.230000 " ; 
EXibin[0][6] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.230000 && Xcmtheta < -0.030000 " ; 
EXibin[0][7] = " beam > 2.800000 && beam < 3.407500 && Xcmtheta > -0.030000 && Xcmtheta < 1.000000 " ; 
EXibin[1][0] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -1.000000 && Xcmtheta < -0.830000 " ; 
EXibin[1][1] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.830000 && Xcmtheta < -0.710000 " ; 
EXibin[1][2] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.710000 && Xcmtheta < -0.590000 " ; 
EXibin[1][3] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.590000 && Xcmtheta < -0.470000 " ; 
EXibin[1][4] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.470000 && Xcmtheta < -0.350000 " ; 
EXibin[1][5] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.350000 && Xcmtheta < -0.190000 " ; 
EXibin[1][6] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.190000 && Xcmtheta < -0.050000 " ; 
EXibin[1][7] = " beam > 3.407500 && beam < 3.650500 && Xcmtheta > -0.050000 && Xcmtheta < 1.000000 " ; 
EXibin[2][0] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -1.000000 && Xcmtheta < -0.830000 " ; 
EXibin[2][1] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -0.830000 && Xcmtheta < -0.710000 " ; 
EXibin[2][2] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -0.710000 && Xcmtheta < -0.590000 " ; 
EXibin[2][3] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -0.590000 && Xcmtheta < -0.450000 " ; 
EXibin[2][4] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -0.450000 && Xcmtheta < -0.270000 " ; 
EXibin[2][5] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -0.270000 && Xcmtheta < -0.130000 " ; 
EXibin[2][6] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > -0.130000 && Xcmtheta < 0.070000 " ; 
EXibin[2][7] = " beam > 3.650500 && beam < 3.839500 && Xcmtheta > 0.070000 && Xcmtheta < 1.000000 " ; 
EXibin[3][0] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -1.000000 && Xcmtheta < -0.850000 " ; 
EXibin[3][1] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -0.850000 && Xcmtheta < -0.730000 " ; 
EXibin[3][2] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -0.730000 && Xcmtheta < -0.630000 " ; 
EXibin[3][3] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -0.630000 && Xcmtheta < -0.490000 " ; 
EXibin[3][4] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -0.490000 && Xcmtheta < -0.330000 " ; 
EXibin[3][5] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -0.330000 && Xcmtheta < -0.170000 " ; 
EXibin[3][6] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > -0.170000 && Xcmtheta < 0.070000 " ; 
EXibin[3][7] = " beam > 3.839500 && beam < 4.028500 && Xcmtheta > 0.070000 && Xcmtheta < 1.000000 " ; 
EXibin[4][0] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -1.000000 && Xcmtheta < -0.830000 " ; 
EXibin[4][1] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -0.830000 && Xcmtheta < -0.710000 " ; 
EXibin[4][2] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -0.710000 && Xcmtheta < -0.590000 " ; 
EXibin[4][3] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -0.590000 && Xcmtheta < -0.450000 " ; 
EXibin[4][4] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -0.450000 && Xcmtheta < -0.310000 " ; 
EXibin[4][5] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -0.310000 && Xcmtheta < -0.130000 " ; 
EXibin[4][6] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > -0.130000 && Xcmtheta < 0.110000 " ; 
EXibin[4][7] = " beam > 4.028500 && beam < 4.271500 && Xcmtheta > 0.110000 && Xcmtheta < 1.000000 " ; 
EXibin[5][0] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -1.000000 && Xcmtheta < -0.810000 " ; 
EXibin[5][1] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -0.810000 && Xcmtheta < -0.670000 " ; 
EXibin[5][2] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -0.670000 && Xcmtheta < -0.530000 " ; 
EXibin[5][3] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -0.530000 && Xcmtheta < -0.390000 " ; 
EXibin[5][4] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -0.390000 && Xcmtheta < -0.250000 " ; 
EXibin[5][5] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -0.250000 && Xcmtheta < -0.050000 " ; 
EXibin[5][6] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > -0.050000 && Xcmtheta < 0.190000 " ; 
EXibin[5][7] = " beam > 4.271500 && beam < 4.541500 && Xcmtheta > 0.190000 && Xcmtheta < 1.000000 " ; 
EXibin[6][0] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -1.000000 && Xcmtheta < -0.810000 " ; 
EXibin[6][1] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -0.810000 && Xcmtheta < -0.690000 " ; 
EXibin[6][2] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -0.690000 && Xcmtheta < -0.530000 " ; 
EXibin[6][3] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -0.530000 && Xcmtheta < -0.410000 " ; 
EXibin[6][4] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -0.410000 && Xcmtheta < -0.250000 " ; 
EXibin[6][5] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -0.250000 && Xcmtheta < -0.030000 " ; 
EXibin[6][6] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > -0.030000 && Xcmtheta < 0.210000 " ; 
EXibin[6][7] = " beam > 4.541500 && beam < 4.838500 && Xcmtheta > 0.210000 && Xcmtheta < 1.000000 " ; 
EXibin[7][0] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -1.000000 && Xcmtheta < -0.810000 " ; 
EXibin[7][1] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -0.810000 && Xcmtheta < -0.670000 " ; 
EXibin[7][2] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -0.670000 && Xcmtheta < -0.550000 " ; 
EXibin[7][3] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -0.550000 && Xcmtheta < -0.430000 " ; 
EXibin[7][4] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -0.430000 && Xcmtheta < -0.270000 " ; 
EXibin[7][5] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -0.270000 && Xcmtheta < -0.050000 " ; 
EXibin[7][6] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > -0.050000 && Xcmtheta < 0.190000 " ; 
EXibin[7][7] = " beam > 4.838500 && beam < 5.500000 && Xcmtheta > 0.190000 && Xcmtheta < 1.000000 " ; 


Double_t PhotonPol[Nb][Nc];
PhotonPol[0][0] = 0.5;
PhotonPol[0][1] = 0.5;
PhotonPol[0][2] = 0.5;
PhotonPol[0][3] = 0.5;
PhotonPol[0][4] = 0.5;
PhotonPol[0][5] = 0.5;
PhotonPol[0][6] = 0.5;
PhotonPol[0][7] = 0.5;
PhotonPol[1][0] = 0.5;
PhotonPol[1][1] = 0.5;
PhotonPol[1][2] = 0.5;
PhotonPol[1][3] = 0.5;
PhotonPol[1][4] = 0.5;
PhotonPol[1][5] = 0.5;
PhotonPol[1][6] = 0.5;
PhotonPol[1][7] = 0.5;



const char* EString[Nb][Nc];
EString[0][0] = "2.8000 <  E_{#gamma} < 3.8125" ; 
EString[0][1] = "3.8125 <  E_{#gamma} < 4.4335"; 
EString[0][2] = "4.4335 <  E_{#gamma} < 5.5000"; 
EString[0][0] = "2.8000 <  E_{#gamma} < 3.8125" ; 
EString[0][1] = "3.8125 <  E_{#gamma} < 4.4335"; 
EString[0][2] = "4.4335 <  E_{#gamma} < 5.5000";
EString[0][0] = "2.8000 <  E_{#gamma} < 3.8125" ; 
EString[0][1] = "3.8125 <  E_{#gamma} < 4.4335"; 
EString[0][2] = "4.4335 <  E_{#gamma} < 5.5000";


EString[1][0] = "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][1] =  "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][2] =  "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][3] = "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][4] =  "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][5] =  "2.8000 <  E_{#gamma} < 5.5000" ;
EString[1][6] =  "2.8000 <  E_{#gamma} < 5.5000" ; 
EString[1][7] =  "2.8000 <  E_{#gamma} < 5.5000" ;

const char* XString[Nb][Nc];
XString[0][0] = "-1 < cos(#theta_{#Xi}^{cm}) < 1" ;
XString[0][1] = "-1 < cos(#theta_{#Xi}^{cm}) < 1" ;
XString[0][2] = "-1 < cos(#theta_{#Xi}^{cm}) < 1" ;
XString[1][0] = "-1.0000 < cos(#theta_{#Xi}^{cm}) < -0.6100" ; 
XString[1][1] = "-0.6100 < cos(#theta_{#Xi}^{cm}) < -0.1900 " ; 
XString[1][2] = "-0.1900 < cos(#theta_{#Xi}^{cm}) < 1.0000 " ;



