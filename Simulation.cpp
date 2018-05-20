//====================================================================
// Simulation.cpp
// Implementation file to run the simulation
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#include "stdafx.h"
#pragma warning(disable:4996)

#include "Simulation.h"
#include "Organism.h"
#include "OrganismFactory.h"
#include "Breeder.h"
#include "GeneticsSimDataParser.h"
#include "GeneInfoFactory.h"
#include <string>

using namespace std;

//-----------------------------------
// Constructor
//-----------------------------------
Simulation::Simulation()
{
	m_Parent1 = NULL;
	m_Parent2 = NULL;
	m_Breeder = new Breeder();
}

//-----------------------------------
// Destructor
//-----------------------------------
Simulation::~Simulation()
{
	m_Parent1 = NULL;
	m_Parent2 = NULL;
	m_Breeder = NULL;
	delete m_Parent1;
	delete m_Parent2;
	delete m_Breeder;
}

void Simulation::initSim(char *fileName)
{
	GeneInfoFactory *geneFact = GeneInfoFactory::getInstance();
	m_vGenes = geneFact->buildGene(fileName);

	OrganismFactory *orgFact = OrganismFactory::getInstance();
	m_Parent1 = orgFact->createOrganism(1);
	m_Parent2 = orgFact->createOrganism(2);
}

//-----------------------------------
// Runs the simulation
//-----------------------------------
void Simulation::runSimulation(int numOffspring)
{
	m_Breeder->breed(m_Parent1, m_Parent2, numOffspring);
}

Organism *Simulation::getParent1()
{
	return m_Parent1;
}

Organism *Simulation::getParent2()
{
	return m_Parent2;
}

void Simulation::printResults(CListBox *listBox)
{
	m_Breeder->setResults(listBox);
}

string Simulation::getResults()
{
	return m_Breeder->getResults();
}

void Simulation::setDataFile(char *fileName)
{
	strcpy_s(m_sFileName, fileName);
}

char *Simulation::getDataFile()
{
	return m_sFileName;
}

Breeder *Simulation::getBreeder()
{
	return m_Breeder;
}

//-----------------------------------
// Get the singleton instance
//-----------------------------------
Simulation *Simulation::getInstance()
{
	static Simulation *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new Simulation();
	}
	return theInstance;
}

//-----------------------------------
// Return the master gene corresponding to the given allele 
//-----------------------------------
GeneInfo *Simulation::getMasterGene(char allele)
{
	for(GeneInfo &master : m_vGenes)
	{
		if(allele == master.getDomSymbol() || allele == master.getRecSymbol())
			return &master;
	}

	return NULL;
}

