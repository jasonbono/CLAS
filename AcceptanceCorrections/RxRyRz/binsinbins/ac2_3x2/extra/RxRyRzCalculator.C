
void RxRyRzCalculator()
{

	const int Nb = 2,Nd = 3; 	//b=bintype, c=binnumber, d=piaxis
	const int Ne=10; //number of paremters for polynomial
	int Nk = 40; //# of pion bins used to get the acceptance parameters
	const int Nq = 10; //number of energy and Xi bins for acceptance corrections
	
	
	Double_t emin = 2.8;
    Double_t emax = 5.5;
    Double_t estep = (emax - emin)/Nq;
	Double_t ximin = -1;
	Double_t ximax = 1;
	Double_t xistep = (ximax - ximin)/Nq;
 	TString exibin[2][Nq];
	for (int q=0;q<Nq;q++)
	{
		exibin[0][q] = Form("beam >= 2.8 + %f && beam <= 2.8 + %f",q*estep,(q+1)*estep);
		cout << Form("beam >= 2.8 + %f && beam <= 2.8 + %f",q*estep,(q+1)*estep) <<endl;
		
		exibin[1][q] = Form("Xcmtheta >= -1 + %f && Xcmtheta <= -1 + %f",q*xistep,(q+1)*xistep);
		cout << Form("Xcmtheta >= -1 + %f && Xcmtheta <= -1 + %f",q*xistep,(q+1)*xistep) <<endl;
	}
	
	
	float R[Nb][Nq][Nd] = {0};
	float eR[Nb][Nq][Nd] = {0};
	float X[Nd] = {0.650869,-0.718129,-0.246293};
	
	
	
	cout << "enter where you would like to have had the acceptance derived from ( NoPol, or PosPol):";
	const string choiceAC;
	cin >> choiceAC;
	ifstream myParFile(Form("../txt/RxRyRz-%s-%i_%ibins.txt",choiceAC.c_str(),Nk,Nq));
	ifstream myCovMatrixFile(Form("../txt/CovMatrixfile-%s-%i_%ibins.txt",choiceAC.c_str(),Nk,Nq));
	if( !myParFile || !myCovMatrixFile) 
	{
		cout << "Cannot open one of the text files. \n";
		cout << Form("../txt/RxRyRz-%s-%i_%ibins.txt",choiceAC.c_str(),Nk,Nq) <<endl;
		cout << Form("../txt/CovMatrixfile-%s-%i_%ibins.txt",choiceAC.c_str(),Nk,Nq) <<endl;
		gROOT->ProcessLine(".q");
	}
	float P[Nb][Nq][Nd][Ne] = {0};  //fit parameters
	float eP[Nb][Nq][Nd][Ne] = {0};
	float covMatrix[Nb][Nq][Nd][Ne][Ne] = {0};  //array of NeXNe matrixes representing the error in the fitting
	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			for (int d = 0; d < Nd; d++)
			{
				cout << "--------- b = "<<b<<", q = "<<q<<", d = "<<d<<" ------------"<<endl;
				for (int e = 0; e < Ne; e++)
				{	
					cout << "  -- e = " << e <<"  --" << endl;
					myParFile >> P[b][q][d][e] >> eP[b][q][d][e]; //the error eP is not actualy used
					cout << "   P = " << P[b][q][d][e] << "  eP = " << eP[b][q][d][e] <<endl;
					for (int j = 0; j < Ne; j++)
					{
						myCovMatrixFile>>covMatrix[b][q][d][e][j];	
						cout <<"   " << covMatrix[b][q][d][e][j];
					
					}
					cout <<endl<<endl;
				}
			}
		}
	}





	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			cout << "Bin: " <<exibin[b][q] <<endl;
			
			for (int d = 0; d < Nd; d++)
			{
				//compute the R and eR values for all energys and Xi bins
				for (int e = 0; e < Ne; e++)
				{
					R[b][q][d] += P[b][q][d][e]*pow(X[d],e); 
					for (int j = 0; j < Ne; j++)
					{
						eR[b][q][d] += covMatrix[b][q][d][e][j]*pow(X[d],e)*pow(X[d],j); //this equals the error squared
					}
					eR[b][q][d] = eR[b][q][d]*eR[b][q][d]; //square to get a positve number
					eR[b][q][d] =  sqrt(sqrt(eR[b][q][d])); // finaly get the error.
				}
				cout << R[b][q][d] << " " << eR[b][q][d] <<endl;
			}
		}
	}


	
}