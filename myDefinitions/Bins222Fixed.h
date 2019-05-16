#ifndef BINS222FIXED_H
#define BINS222FIXED_H


	const string bintype ("fixed"); //for if statments other option is "var"

	const int NEBins = 2;
	const int NXiBins = 2;
	const int NPiBins = 2; 

	TCut EBin[NEBins];
	EBin[0] = "beam > 2.8 && beam < 4.15 ";
	EBin[1] = "beam > 4.15 && beam < 5.5 ";	
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = "Xcmtheta > -1.0 && Xcmtheta < 0";
	XiBin[1] = "Xcmtheta > 0 && Xcmtheta < 1.0";

	TCut  PixBin[NPiBins];
	PixBin[0] = "COS_pi_x > -1.0 && COS_pi_x < 0.0";
	PixBin[1] = "COS_pi_x > 0.0 && COS_pi_x < 1.0";	
	TCut  PiyBin[NPiBins];
	PiyBin[0] = "COS_pi_y > -1.0 && COS_pi_y < 0.0";
	PiyBin[1] = "COS_pi_y > 0.0 && COS_pi_y < 1.0";
	TCut  PizBin[NPiBins];
	PizBin[0] = "COS_pi_z > -1.0 && COS_pi_z < 0.0";
	PizBin[1] = "COS_pi_z > 0.0 && COS_pi_z < 1.0";





#endif