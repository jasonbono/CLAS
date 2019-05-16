/* 
Author: Jason Bono
Date: April 30 2014:
Purpose: To integrate nakayamas results over all energy
*/



using namespace std;
const int nangles = 16;
const int nenergys = 23;


struct MyStruct
{
	//following nakayamas convention
	float T_lb;
	float Theta_cm;
	float xsc;
	float Sigma;
	float Sigma_c;
	float T_x;
	float T_y;
	float T_z;
	float P_x;
	float P_y;
	float P_z;
	float C_x;
	float C_y;
	float C_z;
};

//function prototype
bool ReadALine(ifstream &, MyStruct &);

void IntegrateEnergy()
{
	StyleUp();
	MyStruct ALine;
	ifstream myfile;
	//myfile.open("./mybono_sp_ps.out");
	//myfile.open("mybono_sp_pv.out");	
	myfile.open("mybono_sp_pv_2011.out");
	
	//setup vectors for pushback
	vector<double> vxi[nangles];
	vector<double> vp[nangles];
	vector<double> vcx[nangles];
	vector<double> vcz[nangles];
	
	
	
	int line=0;
	int b=0; //beam
	int a=0; //angle
	while (ReadALine(myfile, ALine)) 
	{	
		//fill the struct
		float T_lb = ALine.T_lb;
		float Theta_cm = ALine.Theta_cm;
		float P_y = ALine.P_y;
		float C_x = ALine.C_x;
		float C_z = ALine.C_z;
		//fill the angle "bin" number
		a = line - nangles*b; 
		//test indexs
		cout << "line = "<<line<<"  b = " <<b<< "  a = "<<a<<"  beam = " << T_lb<< "  angle = "<<Theta_cm<<endl;
		//fill the angle-array of vector-doubles
		vxi[a].push_back(Theta_cm);
		vp[a].push_back(P_y);
		vcx[a].push_back(C_x);
		vcz[a].push_back(C_z);
		//count the line number being read in, as well as the beam "bin"
		line+=1;
		if (line % 16 == 0)
		{
			b+=1;
		}
	}
	
	//average the numbers
	double Xi[nangles]={0};
	double P[nangles]={0};
	double Cx[nangles]={0};
	double Cz[nangles]={0};
	float nen = nenergys;
	for(int a = 0; a < nangles; a++)
	{
		for(int b = 0; b < nenergys; b++)
		{
			Xi[a] += vxi[a][b];
			P[a] += vp[a][b];
			Cx[a] += vcx[a][b];
		 	Cz[a] += vcz[a][b];
		}
		Xi[a] = Xi[a]/nen;
		P[a] = P[a]/nen;
	    Cx[a] = Cx[a]/nen;
	 	Cz[a] = Cz[a]/nen;
		cout <<"Xi["<<a<<"]="<<Xi[a]
		<<"  P["<<a<<"]="<<P[a]
		<<"  Cx["<<a<<"]="<<Cx[a]
		<<"  Cz["<<a<<"]="<<Cz[a]<<endl;
	}
	
	for(int a = 0; a < nangles; a++)
	{	
		//cout<<Xi[a]<<" "<<P[a]<<endl;
		//cout<<Xi[a]<<" "<<Cx[a]<<endl;
		cout<<Xi[a]<<" "<<Cz[a]<<endl;
	}
	
	
	
	
	
}






bool ReadALine(ifstream & afile, MyStruct & ALine)
{
	float tempF;
	int tempI;
	bool result = false;
	//following nakayamas convention
	if (afile >> ALine.T_lb >> ALine.Theta_cm >> ALine.xsc >> ALine.Sigma >> ALine.Sigma_c >> ALine.T_x  >> ALine.T_y >> ALine.T_z >>
 		ALine.P_x >> ALine.P_y >> ALine.P_z >> ALine.C_x >> ALine.C_y >> ALine.C_z ) 
	{
 		result = true;
	}
	return result;
}


StyleUp()
{
	gStyle->SetTitleXOffset(0.4);
	gStyle->SetTitleYOffset(0.2);
	gStyle->SetTitleSize(0.09);
	gStyle->SetTitleYSize(0.13); 
	gStyle->SetPadTopMargin(0);
	gStyle->SetCanvasBorderMode(1);
	gStyle->SetPadBorderMode(100);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadColor(0); 
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFillStyle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);
	gStyle->SetTitleYSize(0.06);
	gStyle->SetTitleYOffset(0.7);
	gStyle->SetTitleXOffset(0.6);
	gStyle->SetPadBottomMargin(0.13);
	gStyle->SetPadRightMargin(0.01);
}









