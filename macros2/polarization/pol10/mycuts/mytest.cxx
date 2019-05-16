#include <iostream>
#include "MyCutsClass.h"
#include "TCut.h"

using namespace std;

int main() {
	MyCutsClass mycuts;
	
	mycuts.AddCut(TCut("beam > 2.8 && beam < 4.08 "));
	
	mycuts.AddCut("beam > 4.08 && beam < 5.5 ");
	
	mycuts.Print(2);
	
	TCut aCut = mycuts.GetCut(1);
	
	aCut.Print();
	
	return 0;
}