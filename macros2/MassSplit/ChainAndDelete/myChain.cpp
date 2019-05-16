/*

Date: Feb 6 2012
Author: Jason Bono
Purpose: To Create a list of the 


*/

#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <string>
#include <cmath>
#include "TSystem.h"
#include "TChain.h"
#include "TObjString.h"
#include "TFile.h"
#include "TStreamerInfo.h"


using namespace std;



//prototypes
int AddFilesToChain(const TString &,TChain *);

int MakeZombieList(const TString &, TChain *);


//main program
int main(){
	
	TString mypath = "/Users/Bono/clas/rootfiles/g12/kppippim/v00";
	
	int Nfiles = 0;
	TChain *mychain = new TChain("mychain");
	//Nfiles = AddFilesToChain(mypath,mychain);
	cout << " Nfiles before deleting =  " << Nfiles << endl;
	
	int Nremoved = 0;
	TChain *mynewchain = new TChain("mynewchain");
	Nremoved = MakeZombieList(mypath,mynewchain);
	//Delete()
	//IsZombie() 
	
	
}












//function definitions
// preconditions: the input path is viable
// postconditions: the input path is searched for .root files and sorted and
//    added to chain
int AddFilesToChain(const TString & inputPath, TChain *chain) {
 // local variables
 int numFiles = 0;
 const char *aFile;
 vector <string> filesArray;
 struct dirent *dirp;

 // statements
 // open directory and read its contents
 DIR *dir = opendir(inputPath.Data());
 // read contents while not end of directory
 while ((dirp = readdir(dir)) != NULL) {
   TString dirFile = dirp->d_name;
   // check current file for root extension
   if (dirFile.Contains(".root")) {
     // add input path in front of file name
     const char
       *fullName = gSystem->PrependPathName(inputPath.Data(), dirFile);
     // add file to the array
     filesArray.push_back(string(fullName));
     numFiles++;
   }
 }
 closedir(dir);

 // sort files for reading in ascending order
 sort(filesArray.begin(), filesArray.end());

 // loop through the files and add them to the chain
 cout << "Input files to read: \n";
 for (int i = 0; i < filesArray.size(); i++) {
   chain->Add(filesArray[i].c_str());
   cout << "\t" << filesArray[i].c_str() << endl;
 }

 return numFiles;
}







int MakeZombieList(const TString & inputPath, TChain *chain) {
	ofstream ZombieFile;
	ZombieFile.open ("./ZombieList.txt");
	ofstream BadStreamFile;
	BadStreamFile.open ("./BadStreamList.txt");
	
	// local variables
 	int numFiles = 0;
 	const char *aFile;
 	vector <string> filesArray;
 	struct dirent *dirp;

 	// statements
 	// open directory and read its contents
 	DIR *dir = opendir(inputPath.Data());
 	// read contents while not end of directory
 	while ((dirp = readdir(dir)) != NULL) {
   		TString dirFile = dirp->d_name;
   		// check current file for root extension
   		if (dirFile.Contains(".root")) {
			//if (dirFile.IsZombie()){
				cout << dirFile << "is being examined" <<endl;
			//}
     		// add input path in front of file name
     		const char *fullName = gSystem->PrependPathName(inputPath.Data(), dirFile);
     		// add file to the array
			cout << "full name = " <<fullName << endl;
     		filesArray.push_back(string(fullName));
     		numFiles++;
			TFile *file = new TFile(fullName);
			
			if (!file->IsZombie())
			{
				cout << "number of bytes in streamer is " << file->GetNbytesInfo()  << endl;
				if (file->GetNbytesInfo() == 0)
				{
					cout << "THIS IS A BAD FILE TO ADD TO THE LIST!" << endl;
					BadStreamFile << fullName <<endl;
				}
				file->Close();
			}
			
			else if (file->IsZombie()) 
			{
				cout << dirFile << " File is a zombie! adding to list" <<endl;
				ZombieFile << fullName <<endl;
				file->Close();	
			}
	

			
			
			//make a list of bad files
			
			
   		}
 	}
 	closedir(dir);
/*
 	// sort files for reading in ascending order
 	sort(filesArray.begin(), filesArray.end());

 	// loop through the files and add them to the chain
 	cout << "Input files to read: \n";
 	for (int i = 0; i < filesArray.size(); i++) {
   		//cout << "\t" << filesArray[i].c_str() << endl;
		TFile *file = new TFile(filesArray[i].c_str());
		if (!file->IsZombie()) {
			file->Close();
     		chain->Add(filesArray[i].c_str());
		} else {
			cout << filesArray[i].c_str() << ">> file is a zombie! adding to list" <<endl;
			ZombieFile << filesArray[i].c_str() <<endl;
			file->Close();
		}
 	}
	
	
 	return numFiles;
*/
}












