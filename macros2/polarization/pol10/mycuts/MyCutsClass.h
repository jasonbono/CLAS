#ifndef MYCUTSCLASS_H
#define MYCUTSCLASS_H

#include <vector>
#include <assert.h>
#include <iostream>
#include "TCut.h"

class MyCutsClass {
public:
	// Constructors and destructors 
	MyCutsClass();
	MyCutsClass(const std::vector<TCut> &);   // cuts
	~MyCutsClass();	
	
	// modifiers
	void AddCut(const TCut &);               // cut
	void AddCut(const char *);               // cut string
	
	// accessors
	TCut GetCut(const unsigned int &) const; // bin number
	void Print(const unsigned int &) const;  // bin number
	
private:
	// private data memebers
	std::vector<TCut> cuts;
};

#endif