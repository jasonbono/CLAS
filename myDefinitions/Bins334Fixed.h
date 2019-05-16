#ifndef BINS334FIXED_H
#define BINS334FIXED_H


	const string bintype ("fixed"); //for if statments other option is "var"

	const int NEBins = 3;
	const int NXiBins = 3;
	const int NPiBins = 4;


	//energy bins
	TCut EBin[NEBins];
	EBin[0] = "beam > 2.8 && beam < 3.6 ";
	EBin[1] = "beam > 3.6 && beam < 4.5 ";
	EBin[2] = "beam > 4.5 && beam < 5.5 ";			
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = "Xcmtheta > -1.0 && Xcmtheta < -0.333";
	XiBin[1] = "Xcmtheta > -0.333 && Xcmtheta < 0.333";
	XiBin[2] = "Xcmtheta > 0.333 && Xcmtheta < 1.0";
	
	
	//pion bins
	TCut  PixBin[NPiBins];
	PixBin[0] = "COS_pi_x > -1.0 && COS_pi_x < -0.5";
	PixBin[1] = "COS_pi_x > -0.5 && COS_pi_x < 0.0";
	PixBin[2] = "COS_pi_x > 0.0 && COS_pi_x < 0.5";
	PixBin[3] = "COS_pi_x > 0.5 && COS_pi_x < 1.0";	
	TCut  PiyBin[NPiBins];
	PiyBin[0] = "COS_pi_y > -1.0 && COS_pi_y < -0.5";
	PiyBin[1] = "COS_pi_y > -0.5 && COS_pi_y < 0.0";
	PiyBin[2] = "COS_pi_y > 0.0 && COS_pi_y < 0.5";
	PiyBin[3] = "COS_pi_y > 0.5 && COS_pi_y < 1.0";
	TCut  PizBin[NPiBins];
	PizBin[0] = "COS_pi_z > -1.0 && COS_pi_z < -0.5";
	PizBin[1] = "COS_pi_z > -0.5 && COS_pi_z < 0.0";
	PizBin[2] = "COS_pi_z > 0.0 && COS_pi_z < 0.5";
	PizBin[3] = "COS_pi_z > 0.5 && COS_pi_z < 1.0";






#endif