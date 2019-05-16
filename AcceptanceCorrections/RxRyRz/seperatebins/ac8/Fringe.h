#ifndef FRINGE_H
#define FRINGE_H

#include "./DataEXiBins.h"



//this function is for smart cuts (looks at the data binning and defines cuts by that)
bool NoFringe_smart(Float_t x ,Float_t y, Int_t bintype, Int_t axis) 
{	
	bool f = true; //initize with true to fill events by default
	if( (bintype == 0) && (axis == 0)) //energy and x
	{

		if (((x >= EVal[0] )&&(x <= EVal[1] ))&&(y <= 0))
		{
			f = false;
		}
		if (((x >= EVal[1] )&&(x <= EVal[2] ))&&(y <= 0))
		{
			f = false;
		}
		if (((x >= EVal[2] )&&(x <= EVal[3] ))&&(y <= 0.2))
		{
			f = false;
		}
	}
	if( (bintype == 0) && (axis == 1)) //energy and y
	{
		if ((x <= 3))
		{
			f = false;
		}
		if ((x >= 5.3))
		{
			f = false;
		}
	}
	
	if( (bintype == 0) && (axis == 2)) //energy and z
	{

		if (((x >= EVal[0] )&&(x <= EVal[1] ))&&( (y >= 0.2) || (y <= -0.8) ) )
		{
			f = false;
		}
		if (((x >= EVal[1] )&&(x <= EVal[2] ))&&(y >= 0.4))
		{
			f = false;
		}
		if (((x >= EVal[2] )&&(x <= EVal[3] ))&&(y >= 0.2))
		{
			f = false;
		}
		
		//if (y <= 0.5)
		//{
		//	f = false;
		//}
	}
	
	if( (bintype == 1) && (axis == 0) ) //cosXitheta and x
	{	
		if (((x >= XVal[0] )&&(x <= XVal[1] ))&&(y <= 0.2))
		{
			f = false;
		}
		if (((x >= XVal[1] )&&(x <= XVal[2] ))&&(y <= 0))
		{
			f = false;
		}
		if (((x >= XVal[2] )&&(x <= XVal[3] ))&&(y <= 0.2))
		{
			f = false;
		}
		if ((x >= 0.4))
		{
			f = false;
		}
	}
	if( (bintype == 1) && (axis == 1)) //cosXitheta and y
	{	
		if ((x >= 0.4))
		{
			f = false;
		}
	}
	
	if( (bintype == 1) && (axis == 2)) //cosXitheta and z
	{	
		if (((x >= XVal[0] )&&(x <= XVal[1] ))&&( (y >= 0.4) || (y <= -0.8) ))
		{
			f = false;
		}
		if (((x >= XVal[1] )&&(x <= XVal[2] ))&&(y >= 0.4))
		{
			f = false;
		}
		if (((x >= XVal[2] )&&(x <= XVal[3] ))&&( (y >= 0.2) || (y <= -0.8) ))
		{
			f = false;
		}
		if ((x >= 0.4))
		{
			f = false;
		}
		
	}
	return 	f;
}


//this function is for tight cuts
bool NoFringe_tight(Float_t x ,Float_t y, Int_t bintype, Int_t axis) 
{	
	bool f = true; //initize with true to fill events by default
	if( (bintype == 0) && (axis == 0)) //energy and x
	{
		if ((x <= 3))
		{
			f = false;
		}
		if ((x >= 4.9))
		{
			f = false;
		}
		if (((x >= 3)&&(x <= 3.3))&&(y <= 0.6))
		{
			f = false;
		}
		if (((x >= 3.3)&&(x <= 3.8))&&(y <= 0.3))
		{
			f = false;
		}
		if (((x >= 3.8)&&(x <= 5))&&(y <= 0))
		{
			f = false;
		}

	}
	if( (bintype == 0) && (axis == 1)) //energy and y
	{
		if ((x <= 3.2))
		{
			f = false;
		}
		if ((x >= 5))
		{
			f = false;
		}
	}
	
	if( (bintype == 0) && (axis == 2)) //energy and z
	{
		if ((x <= 3.3))
		{
			f = false;
		}
		if ((x >= 4.9))
		{
			f = false;
		}

		if (((x >= 3.2)&&(x <= 5))&&(y >= 0.2))
		{
			f = false;
		}
		if (((x >= 3.2)&&(x <= 3.9))&&(y <= -0.8))
		{
			f = false;
		}
	}
	
	if( (bintype == 1) && (axis == 0) ) //cosXitheta and x
	{	
		if (((x >= -1)&&(x <= -0.8))&&(y <= 0.3))
		{
			f = false;
		}
		if (((x >= -0.8)&&(x <= 0))&&(y <= 0))
		{
			f = false;
		}
		if (((x >= 0)&&(x <= 0.2))&&(y <= 0.2))
		{
			f = false;
		}
		if (((x >= 0.2)&&(x <= 0.4))&&(y <= 0.5))
		{
			f = false;
		}
		if ((x >= 0.4))
		{
			f = false;
		}
	}
	if( (bintype == 1) && (axis == 1)) //cosXitheta and y
	{	
		if ((x >= 0.4))
		{
			f = false;
		}
	}
	
	if( (bintype == 1) && (axis == 2)) //cosXitheta and z
	{	
		if (((x >= -1)&&(x <= -0.8))&&(y <= -0.6))
		{
			f = false;
		}
		if (((x >= -0.8)&&(x <= -0.6))&&(y <= -0.8))
		{
			f = false;
		}
		if (((x >= -1)&&(x <= -0.2))&&(y >= 0.4))
		{
			f = false;
		}
		if (((x >= -0.2)&&(x <= 0))&&(y >= 0.2))
		{
			f = false;
		}
		if (((x >= 0)&&(x <= 0.3))&&(y >= 0.1))
		{
			f = false;
		}
		//if (((x >= 0.4)&&(x <= 0.4))&&(y >= -0.1))
		//{
		//	f = false;
		//}
		if ((x >= 0.2))
		{
			f = false;
		}
		
	}
	return 	f;
}











