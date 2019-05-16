/*

L: associated with the lower limit on phi
H: associated with the upper limit on phi
Pos: associated with positive tracks
Neg: associated with negitive tracks

the sector convention used is:
sector 1 centered at 0, sector 2 centered at 60
sector 3 centered at 120, sector 4 centered at 180/-180
sector 5 centered at -120, sector 6 centered at -60,


The cut critera obtained is in "phi" meaning the phi distance from the center of the sector (with a range from {-30,30} )
*/
void Fiducial()
{


//read in the parameters obtained through fitting
ifstream infile_Pos("./FitParams_Pos.txt");
Float_t	ParL_Pos[6][3][3];
Float_t	ParH_Pos[6][3][3]; 
Float_t parL_Pos[6][9] = {0};	
Float_t parH_Pos[6][9] = {0};	
for (int s=0; s<6; s++)
{
	for (int ii=0; ii<3; ii++)
	{	
		for (int j=0; j<3; j++)
		{	
			infile_Pos >> ParL_Pos[s][ii][j]; 
			infile_Pos >> ParH_Pos[s][ii][j]; 
			parL_Pos[s][3*ii + j] = ParL_Pos[s][ii][j];
			parH_Pos[s][3*ii + j] = ParH_Pos[s][ii][j];
		}
	}
}	
infile_Pos.close();
ifstream infile_Neg("./FitParams_Neg.txt");
Float_t	ParL_Neg[6][3][3];
Float_t	ParH_Neg[6][3][3];	
Float_t parL_Neg[6][9] = {0};	
Float_t parH_Neg[6][9] = {0};	
for (int s=0; s<6; s++)
{
	for (int ii=0; ii<3; ii++)
	{	
		for (int j=0; j<3; j++)
		{	
			infile_Neg >> ParL_Neg[s][ii][j]; 
			infile_Neg >> ParH_Neg[s][ii][j]; 
			parL_Neg[s][3*ii + j] = ParL_Neg[s][ii][j];
			parH_Neg[s][3*ii + j] = ParH_Neg[s][ii][j];
		}
	}
}	
infile_Neg.close();


//to get cut critera for a single track you need the momentum,theta,charge and sector of that track
// an example of typical values
float myParticleMomentum = 0.5;
float myParticleTheta = 30; 
float myParticlePhi = 12;
float myParticleSector = 3;


Float_t myInput[2] = {myParticleMomentum,myParticleTheta}; //needed to call FidFunc
float myLowPhi = FidFunc(myInput,parL_Neg[myParticleSector - 1]); //if track is positive use parL_Neg[mySector - 1]
float myHighPhi = FidFunc(myInput,parH_Neg[myParticleSector - 1]);



//can filter a single track by
if ( (myParticlePhi > myLowPhi) && (myParticlePhi < myHighPhi) )
{
	//accept event
	cout << "myParticlePhi = " << myParticlePhi << "  myLowPhi = " << myLowPhi << "  myHighPhi =  " << myHighPhi <<endl;
	cout << "track ok"<<endl;
}
else
{
	cout << "myParticlePhi = " << myParticlePhi << "  myLowPhi = " << myLowPhi << "  myHighPhi =  " << myHighPhi <<endl;
	cout << "event filtered out " <<endl;
	
}


}


Float_t FidFunc(Float_t *x, Float_t *par) 
{
	Float_t xx = x[0]; //momentum
	Float_t yy = x[1]; //theta
	Float_t a = (par[0]*pow(xx,par[1]) + par[2]);
	Float_t b = (par[3]*pow(xx,par[4]) + par[5]);
	Float_t c = (par[6]*pow(xx,par[7]) + par[8]);
 	Float_t f =  a -  b/(yy - c);
	return 	f;
}

