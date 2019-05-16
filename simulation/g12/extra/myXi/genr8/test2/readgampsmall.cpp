#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main() 
{

	//--------------------function prototypes------------------
	int countlines(ifstream *);
	//string fillstring(ifstream *, string *);
	
	
	//open the file of intrest
	ifstream myfile;
	myfile.open("myXismall.gamp");
	int dim = countlines(&myfile); 
	myfile.close();
	
	cout << "the lenth of the file is: " <<dim << " lines. " <<endl;
	
	
	string line[dim];
	int i=0;
	
	myfile.open("myXismall.gamp");
	if (myfile.is_open()) 
	{
		while(!myfile.eof())
		{
			getline(myfile,line[i]);
			i = i++;
		}
	}
	
	for(i=0;i<dim;i++)
	{
		cout <<"i="<<i<<" line[i]="<<line[i]<<endl;		
		
	}

	
	

	
/*	
	string line;
	int nlines=0;

	
	//open file
	ifstream myfile ("myXismall.gamp");
	
	//make sure file is opened
	if (myfile.is_open()) 
	{
		while(!myfile.eof())
		{
			getline(myfile,line);
			cout << line << endl;
			nlines = nlines++;
		}		
	}	
	cout << nlines <<endl;


*/
}

//--------------------------------------functions-----------------------------


//--------------------------------------count lines-----------------------------
int countlines(ifstream *f)
{
	string s;
	int nlines=0;	
	if (f->is_open()) 
	{
		while(!f->eof())
		{
			getline(*f,s);
			nlines = nlines++;
		}	
		return nlines - 1;
	}
	else 
	{

		return -10000;
	}
}
//------------------------------------------------------------------------------

//-----------------------------------fill string array--------------
/*
string fillstring(ifstream *f,string *s)
{
	string *s;
	if (!f->eof())
	{	
		getline(*f,*s);
		return s;			
	}
	else 
	{
		cout <<"error! reading file after end of line" << endl;
		return "bad string";}
}


	
/*		
	}
	//get a line
    getline(myfile,line);  // this reads the first line and writes it to the string "line", if done sequentialy it will read the next line and redefine
    //the first line is the number, so set it to num
    num=atoi(line.c_str());
	cout << "the first line is: " << line <<endl;
    while(!myfile.eof()) {
      getline(myfile,line);
      //if there is a space in the line we have gotten
      while((end=line.find(' ',0))!=string::npos) {
        //get the number before the space
        tempnum=line.substr(0,end);
        myarray[firstarg][secondarg]=atoi(tempnum.c_str());
        secondarg++;
        //erase the part of the line we have gotten
        line.erase(0,end+1);
      }
      //we will have an extra number at the end after that loop
      //this gets that last number
      tempnum=line.substr(0,line.length());
      myarray[firstarg][secondarg]=atoi(tempnum.c_str());
      //set the number of args to our array
      totalargs[firstarg]=secondarg;
      firstarg++;
      //reset arg.
      secondarg=0;
    }
  } else {
    cout << "cannot open";
  }

  //this is extra, but it just shows you your variables and that
  //they really do have numbers in them.
  cout << "num: " << num << endl;
  for (int x=0;x<firstarg;x++) {
    cout << "Array " << x+1 << ": " << myarray[x][0];
    for (int y=1;y<=totalargs[x];y++) {
      cout << "," << myarray[x][y];
    }
    cout << endl;
  }
*/
