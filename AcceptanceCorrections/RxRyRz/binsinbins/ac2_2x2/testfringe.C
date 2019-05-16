#include "./Fringe.h"

void testfringe()
{	
	cout << "passed"<<endl;
	
	bool f = false;
	bool t = true;
	cout <<" false = "<<f<<"  true = "<<t<<endl;
	
	bool result = NoFringe(4,0,0,0);
	cout << "the first results is " << result<<endl;

	result = NoFringe(4,-0.9,0,0);
	cout << "the second results is " << result<<endl;


	
}

