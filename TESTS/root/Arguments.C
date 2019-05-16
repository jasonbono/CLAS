






void Arguments(TString passed)
{
	
	string input(passed);
	string filename = input.substr(0,input.find_last_of("."));
	string extention = input.substr(input.find_last_of("."));
	string tackon("_Basic");
	string output = filename + tackon + extention;
	cout <<"input = "<< input <<"   output = " <<output<<endl;

}


