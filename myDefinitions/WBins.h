#ifndef WBINS_H
#define WBINS_H

//same as wbins 27 but using tcut object rather than tstring

	const Int_t NWBins = 27;
	TCut WBin[NWBins];
	WBin[0] = "beam > 2.80 && beam < 2.90";
	WBin[1] = "beam > 2.90 && beam < 3.00";
	WBin[2] = "beam > 3.00 && beam < 3.10";
	WBin[3] = "beam > 3.10 && beam < 3.20";
	WBin[4] = "beam > 3.20 && beam < 3.30";
	WBin[5] = "beam > 3.30 && beam < 3.40";
	WBin[6] = "beam > 3.40 && beam < 3.50";
	WBin[7] = "beam > 3.50 && beam < 3.60";
	WBin[8] = "beam > 3.60 && beam < 3.70";
	WBin[9] = "beam > 3.70 && beam < 3.80";
	WBin[10] = "beam > 3.80 && beam < 3.90";
	WBin[11] = "beam > 3.90 && beam < 4.00";
	WBin[12] = "beam > 4.00 && beam < 4.10";
	WBin[13] = "beam > 4.10 && beam < 4.20";
	WBin[14] = "beam > 4.20 && beam < 4.30";
	WBin[15] = "beam > 4.30 && beam < 4.40";
	WBin[16] = "beam > 4.40 && beam < 4.50";
	WBin[17] = "beam > 4.50 && beam < 4.60";
	WBin[18] = "beam > 4.60 && beam < 4.70";
	WBin[19] = "beam > 4.70 && beam < 4.80";
	WBin[20] = "beam > 4.80 && beam < 4.90";
	WBin[21] = "beam > 4.90 && beam < 5.00";
	WBin[22] = "beam > 5.00 && beam < 5.10";
	WBin[23] = "beam > 5.10 && beam < 5.20";
	WBin[24] = "beam > 5.20 && beam < 5.30";
	WBin[25] = "beam > 5.30 && beam < 5.40";
	WBin[26] = "beam > 5.40 && beam < 5.50";


	


#endif