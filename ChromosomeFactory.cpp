//====================================================================
// ChromosomeFactory.cpp
// Implementation file that builds chromosomes
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#include "stdafx.h"
#include "ChromosomeFactory.h"
#include "Chromosome.h"
#include "Gene.h"
#include "GeneInfo.h"
#include "Simulation.h"

//-----------------------------------
// Constructor
//-----------------------------------
ChromosomeFactory::ChromosomeFactory()
{

}

//-----------------------------------
// Destructor
//-----------------------------------
ChromosomeFactory::~ChromosomeFactory()
{

}

//-----------------------------------
// Get the singleton instance
//-----------------------------------
ChromosomeFactory *ChromosomeFactory::getInstance()
{
	static ChromosomeFactory *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new ChromosomeFactory();
	}
	return theInstance;
}

//-----------------------------------
// Builds a chromosome given the two strands from the parser
//-----------------------------------
Chromosome *ChromosomeFactory::buildChromosome(char *strand1, char *strand2)
{
	Chromosome *theChromo = NULL;
	char *ch1, *ch2;
	bool done = false;

	Simulation *sim = Simulation::getInstance();
	GeneInfo *master;
	Gene *theGene;

	ch1 = strand1;
	ch2 = strand2;
	theChromo = new Chromosome();

	while(!done)
	{
		master = sim->getMasterGene(*ch1);
		if(master == NULL)
			return NULL;
		theGene = new Gene(master, *ch1, *ch2);
		theChromo->addGene(theGene);

		ch1++;
		if(*ch1 =='\0')
			done = true;
		ch2++;
		ch1++;
		ch2++;
	}
	return theChromo;
}