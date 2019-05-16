

//to prove the coresponding generation function to t(x) = 1/tau*(exp(-x/tau))  is (-tau)*log(1-x);


void ExpoDecay(){
	
	double count = 0;
	TRandom3 r(0);
	double tau = 0.000003;
	tau = 1.639e-10;
	tau = 1;
	double events = 100000;
	

	double binh=0.000000001;
	binh=3;
	double binl=0;
	double nbins=250;
	
	double binwidth = (binh -  binl)/nbins;
	double normfactor = binwidth*events;
	
	TH1F *h = new TH1F("h","expo decay",nbins,binl,binh);
	for (int i == 0; i < events; i++)
	{
		double x = r.Rndm();
		double t = expodist(x,tau);
		h->Fill(t);
		//cout <<"x="<< x <<" ";
		//cout << " t=" << t <<endl;
	}
	h->Draw("E");
	TF1 *fdecay=new TF1("fdecay",Form("%f/%e*(exp(-x/%e))",normfactor,tau,tau),0,15);
	fdecay->Draw("same");
}






//the probability distribtuion coresponding to exponential decay t(x) = 1/tau*(exp(-x/tau)) is given by
double expodist(double x,double tau)
{
	double t = 0;
	t = (-tau)*log(1-x);
	return t;
}



