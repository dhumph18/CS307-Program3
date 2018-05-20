//====================================================================
// OrganismFactory.cpp
// 
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#include "stdafx.h"
#include "OrganismFactory.h"
#include "GeneticsSimDataParser.h"
#include "ChromosomeFactory.h"

//-----------------------------------
// Constructor
//-----------------------------------
OrganismFactory::OrganismFactory()
{

}

//-----------------------------------
// Destructor
//-----------------------------------
OrganismFactory::~OrganismFactory()
{

}

//-----------------------------------
// Get the singleton instance
//-----------------------------------
OrganismFactory *OrganismFactory::getInstance()
{
	static OrganismFactory *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new OrganismFactory();
	}
	return theInstance;
}

//-----------------------------------
//Create one of the parent organisms to be bred
//-----------------------------------
Organism *OrganismFactory::createOrganism(int parent)
{
	GeneticsSimDataParser *parser = GeneticsSimDataParser::getInstance();
	ChromosomeFactory *chromofact = ChromosomeFactory::getInstance();
	Organism *org = new Organism();
	Chromosome *chromo;
	
	char strand1[32] = "";
	char strand2[32] = "";

	org->setNames(parser->getScientificName(), parser->getCommonName());
	for(int i = 0; i < parser->getChromosomeCount(); i++)
	{
		chromo = new Chromosome();
		if(parent == 1)
		{
			//Build and add the chromosomes to the first parent organism
			parser->getP1Chromosome(strand1, strand2);
			chromo = chromofact->buildChromosome(strand1, strand2);
			org->addChromosome(chromo);
		}
		else
		{
			//Build and add the chromosomes to the second parent organism
			parser->getP2Chromosome(strand1, strand2);
			chromo = chromofact->buildChromosome(strand1, strand2);
			org->addChromosome(chromo);
		}
	}

	return org;

}
