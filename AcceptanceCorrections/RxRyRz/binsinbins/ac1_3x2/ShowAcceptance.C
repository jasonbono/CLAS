



#include "./SimEXiBins.h"
#include "./constants.h"
#include "./readfit.h"


void ShowAcceptance()
{
	//get the parameters and error matrix (from readfit.h)
	float P[Nb][Nq][Nd][Ne] = {0}; 
	float covMatrix[Nb][Nq][Nd][Ne][Ne]={0};
	GetFitAndMatrix(&P[][][][],&covMatrix[][][][][]);



	//
	for (int b = 0; b < Nb; b++)
	{
		for (int q = 0; q < Nq; q++)
		{
			for (int d = 0; d < Nd; d++)
			{
				cout << "----b = "<<b<<", q = "<<q<<", d = "<<d<<" ------"<<endl;
				for (int e = 0; e < Ne; e++)
				{	
					cout << " e = " << e <<" : ";
					cout << " P = " << P[b][q][d][e] <<endl;
					for (int j = 0; j < Ne; j++)
					{
						cout <<" mat = " << covMatrix[b][q][d][e][j];
					}
					cout <<endl<<endl;
				}
			}
		}
	}

	
	

	//DrawFitAndError(Ne,P[0][0][0],covMatrix2[0][0][0]);
	//DrawFit(P[0][0][0]);
	//cout <<P[0][0][0][1]<<endl;
}
























//void GetFitAndMatrix(float *P,float *covMatrix)
void DrawFit(float FuncPars[Ne])
{

	TF1 *basef = new TF1("basef",Form("%f + %f*x + %f*x*x + %f*x*x*x + %f*x*x*x*x + %f*x*x*x*x*x + %f*x*x*x*x*x*x + %f*x*x*x*x*x*x*x + %f*x*x*x*x*x*x*x*x + %f*x*x*x*x*x*x*x*x*x"
	,FuncPars[0],FuncPars[1],FuncPars[2],FuncPars[3],FuncPars[4],FuncPars[5],FuncPars[6],FuncPars[7],FuncPars[8],FuncPars[9]),-1.0,1.0);  //NO PROBLEMS HERE
  	basef->Draw();

}


void DrawFitandError(const int dim,float FuncPars[dim],float CovMat[dim*dim])   //this is called from int main to draw the results of a fit, the variables are being passed fine at this point.
{
		
		TF1 *basef = new TF1("basef",Form("%f + %f*x + %f*x*x + %f*x*x*x + %f*x*x*x*x + %f*x*x*x*x*x + %f*x*x*x*x*x*x + %f*x*x*x*x*x*x*x + %f*x*x*x*x*x*x*x*x + %f*x*x*x*x*x*x*x*x*x"
		,FuncPars[0],FuncPars[1],FuncPars[2],FuncPars[3],FuncPars[4],FuncPars[5],FuncPars[6],FuncPars[7],FuncPars[8],FuncPars[9]),-1.0,1.0);  //NO PROBLEMS HERE
	  	basef->Draw();  

		cout <<"val " <<CovMat[0]<<endl;





		//------------make the function for the error       		/ISSUE1: I WANT "dim" AND "CovMat" TO BE PASSED TO THIS FUNCTION.... (see next issue)
		float errorfunc(Float_t x, int dim)
		{			
			float result = 0;
			for (int i = 0; i < dim; i++)
			{	
				for (int j = 0; j < dim; j++)
				{
					int index = i*j;
					//cout <<"stuff"<<endl;
					//cout << "CovMat[" <<i<<"]["<<j<<"] = " << CovMat[index] << endl;
					//result += CovMat[index]*pow(x,i)*pow(x,j);
					//result += 1;
					cout <<"dim = " <<dim<<endl;
				}
			}
			cout << " final result = " << result <<endl; 
			return result;	
		}

	
        // create a wrapper function around error function to pass dimension as a parameter
        Double_t wrapperfunc(Double_t *x, Double_t *par) 
		{
        	Int_t dim = par[0];  // store the first paraterm as dimension
         	Double_t result = errorfunc(x[0], dim);   // call the error function that you really want
          	return result;
      	}

		//---------------------------------------------------
		// you now call the wrapper function with 1 parameter (last argument)
		TF1 *errorf = new TF1("errorf",wrapperfunc,-1,1,1);   //ISSUE2: BUT THIS IS THE WAY THAT THE FUNCTION IS CALLED.  
        // fix the first parameter of the errorf to be the dimension
		errorf->FixParameter(0, dim);



																											
	//	TF1 *highf = new TF1("highf","basef + errorf");
	//	highf->SetRange(-1,1);

	//	TF1 *lowf = new TF1("lowf","basef - errorf");
	//	lowf->SetRange(-1,1);
	
	
		TCanvas *can=new TCanvas("can","",800,600);
		//basef->Draw();
		errorf->Draw();
		//lowf->Draw("SAME");
		//highf->Draw("SAME");

}
