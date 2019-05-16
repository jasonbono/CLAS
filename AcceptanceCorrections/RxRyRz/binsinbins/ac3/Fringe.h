#ifndef FRINGE_H
#define FRINGE_H

#include "./DataEXiBins.h"

//for 3x3 exi bins. get z lims from DefineFringe.C
bool NoFringe_6bins(Float_t x ,Float_t y, Float_t z, Int_t axis) //x is energy, y is xi angle, z is pi angle 
{	
//	cout << "x = " << x << "y = " << y << "z = " << z <<endl;
	bool f = true;
	if( ( (x >= EVal[0] )&&(x < EVal[1] ) )&&(axis == 0) ) //xaxis
	{	
		if (((y >= XVal[0][0] )&&(y < XVal[0][1] ))&&( (z < 0.300000)||(z > 1.000000) ))
		{
			f = false;
		}
		if (((y >= XVal[0][1] )&&(y < XVal[0][2] ))&&( (z < 0.100000)||(z > 1.000000) ))
		{
			f = false;
		}
	}
	if( ( (x >= EVal[0] )&&(x < EVal[1] ) )&&(axis == 1) ) //yaxis
	{	
		if (((y >= XVal[0][0] )&&(y < XVal[0][1] ))&&( (z < -0.950000)||(z > 0.950000) ))
		{
			f = false;
		}
		if (((y >= XVal[0][1] )&&(y < XVal[0][2] ))&&( (z < -0.950000)||(z > 0.950000) ))
		{
			f = false;
		}
	}
	if( ( (x >= EVal[0] )&&(x < EVal[1] ) )&&(axis == 2) ) //zaxis
	{	
		if (((y >= XVal[0][0] )&&(y < XVal[0][1] ))&&( (z < -0.700000)||(z > 0.366667) ))
		{
			f = false;
		}
		if (((y >= XVal[0][1] )&&(y < XVal[0][2] ))&&( (z < -0.966667)||(z > 0.300000) ))
		{
			f = false;
		}
	}
	
	
	
	//second energy bin
	if( ( (x >= EVal[1] )&&(x < EVal[2] ) )&&(axis == 0) ) //xaxis
	{	
		if (((y >= XVal[1][0] )&&(y < XVal[1][1] ))&&( (z < 0.233333)||(z > 1.000000) ))
		{
			f = false;
		}
		if (((y >= XVal[1][1] )&&(y < XVal[1][2] ))&&( (z < -0.100000)||(z > 1.000000) ))
		{
			f = false;
		}
	}
	if( ( (x >= EVal[1] )&&(x < EVal[2] ) )&&(axis == 1) ) //yaxis
	{	
		if (((y >= XVal[1][0] )&&(y < XVal[1][1] ))&&( (z < -0.950000)||(z > 0.950000) ))
		{
			f = false;
		}
		if (((y >= XVal[1][1] )&&(y < XVal[1][2] ))&&( (z < -0.950000)||(z > 0.950000) ))
		{
			f = false;
		}
	}
	if( ( (x >= EVal[1] )&&(x < EVal[2] ) )&&(axis == 2) ) //zaxis
	{	
		if (((y >= XVal[1][0] )&&(y < XVal[1][1] ))&&( (z < -0.833333)||(z > 0.366667) ))
		{
			f = false;
		}
		if (((y >= XVal[1][1] )&&(y < XVal[1][2] ))&&( (z < -0.966667)||(z > 0.233333) ))
		{
			f = false;
		}
	}
	
	
	
	
	if( ( (x >= EVal[2] )&&(x < EVal[3] ) )&&(axis == 0) ) //xaxis
	{	
		if (((y >= XVal[2][0] )&&(y < XVal[2][1] ))&&( (z < 0.100000)||(z > 1.000000) ))
		{
			f = false;
		}
		if (((y >= XVal[2][1] )&&(y < XVal[2][2] ))&&( (z < -0.233333)||(z > 1.000000) ))
		{
			f = false;
		}
	}
	if( ( (x >= EVal[2] )&&(x < EVal[3] ) )&&(axis == 1) ) //yaxis
	{	
		if (((y >= XVal[2][0] )&&(y < XVal[2][1] ))&&( (z < -0.950000)||(z > 0.950000) ))
		{
			f = false;
		}
		if (((y >= XVal[2][1] )&&(y < XVal[2][2] ))&&( (z < -0.950000)||(z > 0.950000) ))
		{
			f = false;
		}
	}
	if( ( (x >= EVal[2] )&&(x < EVal[3] ) )&&(axis == 2) ) //zaxis
	{	
		if (((y >= XVal[2][0] )&&(y < XVal[2][1] ))&&( (z < -0.966667)||(z > 0.433333) ))
		{
			f = false;
		}
		if (((y >= XVal[2][1] )&&(y < XVal[2][2] ))&&( (z < -0.966667)||(z > 0.233333) ))
		{
			f = false;
		}

	}

	return 	f;
}

