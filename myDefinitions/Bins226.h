#ifndef BINS226_H
#define BINS226_H



	const string bintype ("var"); //for if statments other option is "fixed"
	const int NEBins = 2; 
	const int NXiBins = 2;
	const int NPiBins = 6;
	
	//energy bins
	TCut EBin[NEBins];
	EBin[0] = "beam > 2.8 && beam < 4.08 ";
	EBin[1] = "beam > 4.08 && beam < 5.5 ";		
	//Xicm bins
	TCut XiBin[NXiBins];
	XiBin[0] = "Xcmtheta > -1.0 && Xcmtheta < -0.41";
	XiBin[1] = "Xcmtheta > -0.41 && Xcmtheta < 1.0";
				
				
	//want 370 events per pi bin
	//pi bins
	TCut  PixBin[NPiBins];
	PixBin[0] = "COS_pi_x > -1.0 && COS_pi_x < 0.0";  //-0.5 pm .25
	PixBin[1] = "COS_pi_x > 0.0 && COS_pi_x < 0.4";  // 0.2 pm .2
	PixBin[2] = "COS_pi_x > 0.4 && COS_pi_x < 0.7";  // 0.55 pm .15
	PixBin[3] = "COS_pi_x > 0.7 && COS_pi_x < 0.8";  // 0.75 pm .05
	PixBin[4] = "COS_pi_x > 0.8 && COS_pi_x < 0.9";  // 0.85 pm .05
	PixBin[5] = "COS_pi_x > 0.9 && COS_pi_x < 1.0";  // 0.95 pm .05
	
	TCut  PiyBin[NPiBins];
	PiyBin[0] = "COS_pi_y > -1.0 && COS_pi_y < -0.7";  //-0.85 pm .15
	PiyBin[1] = "COS_pi_y > -0.7 && COS_pi_y < -0.4";  //-0.45 pm .15
	PiyBin[2] = "COS_pi_y > -0.4 && COS_pi_y < -0.1";  //-0.25 pm .15
	PiyBin[3] = "COS_pi_y > -0.1 && COS_pi_y < 0.2";   //0.05 pm .15
	PiyBin[4] = "COS_pi_y > 0.2 && COS_pi_y < 0.5";    //0.35 pm .15
	PiyBin[5] = "COS_pi_y > 0.5 && COS_pi_y < 1.0";    //0.75 pm .25

	TCut  PizBin[NPiBins];
	PizBin[0] = "COS_pi_z > -1.0 && COS_pi_z < -0.75"; //-0.875 pm .125
	PizBin[1] = "COS_pi_z > -0.75 && COS_pi_z < -0.5"; //-0.625 pm .125
	PizBin[2] = "COS_pi_z > -0.5 && COS_pi_z < -0.25"; //-0.375 pm .125
	PizBin[3] = "COS_pi_z > -0.25 && COS_pi_z < -0.1"; //-0.175 pm .075
	PizBin[4] = "COS_pi_z > -0.1 && COS_pi_z < 0.1";   //-0.0   pm .1
	PizBin[5] = "COS_pi_z > 0.1 && COS_pi_z < 1.0";    //-0.55 pm .45
	
	
#endif