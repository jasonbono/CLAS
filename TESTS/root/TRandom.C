

void TRandom(){
	
	float count = 0;
	TRandom3 r(0);
	for (int i == 0; i < 100000; i++)
	{
		double a = r.Rndm();
		cout << a <<endl;
		if (a < 0.8)
		{	
			cout <<"good"<<endl;
			count += 1;
			cout << "count = "<<count<<endl; 
		}
	}
	
	cout <<"Probibility of sucess = " << count/100000 <<endl;
	
}