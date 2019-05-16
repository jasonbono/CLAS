#include "MyCutsClass.h"

// constructors and destructors /////////////////////////////////////////////
MyCutsClass::MyCutsClass() {
}

MyCutsClass::MyCutsClass(const std::vector<TCut> & aCuts) {
	cuts = aCuts;
}   

MyCutsClass::~MyCutsClass() {
	
}

// modifiers ////////////////////////////////////////////////////////////////

void MyCutsClass::AddCut(const TCut & aCut) {
	cuts.push_back(aCut);
}

void MyCutsClass::AddCut(const char * aCutStr) {
	cuts.push_back(TCut(aCutStr));
}


// accessors ////////////////////////////////////////////////////////////////

TCut MyCutsClass::GetCut(const unsigned int & bin) const {
	assert (bin > 0 && bin <= cuts.size());
	  
	return cuts[bin];
}


void MyCutsClass::Print(const unsigned int & bin) const {
	assert (bin > 0 && bin <= cuts.size());
	
	std::cout << "The cut for bin " << bin << " is: ";
	cuts[bin-1].Print();
}
