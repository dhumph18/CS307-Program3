//====================================================================
// ChromosomeFacory.h
// Interface file that builds chromosomes
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef CHROMOSOMEFACTORY_H
#define CHROMOSOMEFACTORY_H

#include "Chromosome.h"

using namespace std;

class ChromosomeFactory
{
	private:
		ChromosomeFactory();				//Constructor

	public:
		~ChromosomeFactory();						//Destructor
		static ChromosomeFactory *getInstance();	//Get the singleton instance
		Chromosome *buildChromosome(char *strand1, char *strand2); //Builds a chromosome given the two strands from the parser

};
#endif