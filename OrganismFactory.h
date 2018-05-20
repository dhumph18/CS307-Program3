//====================================================================
// OrganismFacroty.h
// 
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================


#ifndef ORGANISMFACTORY_H
#define ORGANISMFACTORY_H

#include "Organism.h"

using namespace std;

class OrganismFactory
{
	private:
		OrganismFactory();				//Constructor

	public:
		~OrganismFactory();						//Destructor
		static OrganismFactory *getInstance();	//Get the singleton instance
		Organism *createOrganism(int parent);	//Create one of the parent organisms to be bred

};
#endif