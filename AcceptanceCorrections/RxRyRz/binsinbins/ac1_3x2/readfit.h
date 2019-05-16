#ifndef READFIT_H
#define READFIT_H


#include "./constants.h"


void GetFitAndMatrix(float *P,float *covMatrix)
{	

	///*//interactive question
	cout << "enter where you would like to have had the acceptance derived from ( NoPol, PosPol or NegPol):";
	const string choiceAC;
	cin >> choiceAC;
	cout << "Fiducial cuts? (type yes or no):";
	const string fidchoice;
	cin >> fidchoice;
	if (fidchoice == "yes"){const string fid = "-Fid";}
	else if (fidchoice == "no"){const string fid = "";}
	else{cout << "fidchoice bad"<<endl;exit(1);}
	//--------read in the acceptance correction parameters and error matrix observables------
	ifstream myParFile(Form("./txt/RxRyRz-%s-%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nq,fid.c_str()));
	ifstream myCovMatrixFile(Form("./txt/CovMatrixfile-%s-%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nq,fid.c_str()));
	///*///
	if( !myParFile || !myCovMatrixFile) 
	{
		cout << "Cannot open one of the text files. \n";
		cout << Form("./txt/RxRyRz-%s-%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nq,fit.c_str()) <<endl;
		cout << Form("./txt/CovMatrixfile-%s-%i_%ibins%s.txt",choiceAC.c_str(),Nk,Nq,fid.c_str()) <<endl;
		gROOT->ProcessLine(".q");
	}


	//float P[Nb][Nq][Nd][Ne] = {0};  //fit parameters
	float eP[Nb][Nq][Nd][Ne] = {0}; //this is needed just to comply with the par file format


	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			for (int d = 0; d < Nd; d++)
			{
				//cout << "--------- b = "<<b<<", q = "<<q<<", d = "<<d<<" ------------"<<endl;
				for (int e = 0; e < Ne; e++)
				{	
				//	cout << "  -- e = " << e <<"  --" << endl;
					myParFile >> P[b][q][d][e] >> eP[b][q][d][e]; //the error eP is not actualy used
					//cout << "   P = " << P[b][q][d][e] << "  eP = " << eP[b][q][d][e] <<endl;
					for (int j = 0; j < Ne; j++)
					{
						myCovMatrixFile>>covMatrix[b][q][d][e][j];
					//	cout <<" covMatrix = " << covMatrix[b][q][d][e][j];

					}
					//cout <<endl<<endl;
				}
			}
		}
	}

}
