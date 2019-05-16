

void DrawFunction()
{	
	const int Dim = 3;
	TCanvas *can=new TCanvas("can","",800,600);
	can->Divide(2,2);
	can->cd(1);
	DrawStuff(2);
	can->cd(2);
	DrawStuff2(0,1,1,0,0);
	float array[2][Dim] = {0};
	float array[0][0] = 3;
	float array[0][1] = 2;
	float array[0][2] = 1;
	
	float matrix[2][Dim][Dim] = {0};
	
	DrawStuff3(Dim,array[0],matrix[1]);



	
}

///////////////////////////////
void DrawStuff(int n)
{
	cout <<"ok n = "<<n<<endl;
	TF1 *f1 = new TF1("f1",Form("pow(x,%i)",n),-100,100);
	f1->Draw();	
}
////////////////////////////////////////////////////
void DrawStuff2(float P0,float P1,float P2,float P3,float P4)
{
	cout <<"input is: " << P0 << " "<< P1 << " "<< P2 << " "<< P3 << " " <<P4 << endl;
	TF1 *basef = new TF1("basef",Form("%f + %f*x + %f*x*x + %f*x*x*x + %f*x*x*x*x",P0,P1,P2,P3,P4),-1.0,1.0);
  	basef->Draw();
	TF1 *errorf = new TF1("errorf","0.2 + 0.04*x*x",-1.0,1.0);
	TF1 *highf = new TF1("highf","basef + errorf");
	highf->SetRange(-1,1);
	highf->Draw("SAME");
	TF1 *lowf = new TF1("lowf","basef - errorf");
	lowf->SetRange(-1,1);
	lowf->Draw("SAME");
}
	
////////////////////////////////////////////////////
void DrawStuff3(const int dim,float Vec[dim],float Matrix[dim][dim])
{
		cout << " dim = " <<dim<<endl;
		cout <<"Vec components are: " << Vec[0] << " "<< Vec[1] << " "<< Vec[2] << endl;
		cout <<"some matrix components are: " << Matrix[0][0] << " "<< Matrix[0][1] << endl;

		float myFunc(Float_t x) {
		      return x+sin(x)*x;
		}
		TF1 *fa3 = new TF1("fa3","myFunc(x)",-15,15);
	   	fa3->Draw();
	
	
	/*
		TF1 *basef = new TF1("basef",Form("%f + %f*x + %f*x*x + %f*x*x*x + %f*x*x*x*x",P0,P1,P2,P3,P4),-1.0,1.0);
	  	basef->Draw();
		TF1 *errorf = new TF1("errorf","0.2 + 0.04*x*x",-1.0,1.0);
		TF1 *highf = new TF1("highf","basef + errorf");
		highf->SetRange(-1,1);
		highf->Draw("SAME");
		TF1 *lowf = new TF1("lowf","basef - errorf");
		lowf->SetRange(-1,1);
		lowf->Draw("SAME");
	*/
	}
