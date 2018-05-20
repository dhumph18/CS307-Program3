//====================================================================
// Organism.h
// Interface file for the organism's information
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef ORGANISM_H
#define ORGANISM_H

#include "GeneInfo.h"
#include "GeneticsSimDataParser.h"
#include "Chromosome.h"
#include <vector>
#include <string>

class Organism
{
	private:
		char m_sScientificName[64];			//Scientific name (genus & species) of the organism
		char m_sCommonName[32];				//Common name of the organism
		vector<Chromosome> *m_vChromos;		//Collection of the organism's chromosomes


	public:
		Organism();							//Constructor
		~Organism();						//Destructor
		void setNames(char *sciName, char *comName);	//Set the scientific and common names
		char *getSciName();					//Get the scientific name
		char *getCommonName();				//Get the common name
		void addChromosome(Chromosome *chromo);	//Add a chromosome to the collection of chromosomes
		vector<Chromosome> *Organism::getChromosomes();	//Get the collection of chromosomes
		void print();						//Print the organism's information
		string printGeneralGenes();
};
#endif