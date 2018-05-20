//====================================================================
// Chromosome.h
// Interface file for a chromosome object which holds a collecion of genes
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Gene.h"
#include <vector>
#include <string>

using namespace std;

class Chromosome
{
	private:
		vector<Gene> *m_vGenes;				//Collection of genes on the chromosome

	public:
		Chromosome();						//Private constructor
		~Chromosome();						//Destructor
		void addGene(Gene *gene);			//Adds a gene to the collection
		vector<Gene> *getGenes();			//Get the collection of genes
		string printGenes();					//Print the info for each gene on the chromosome
};
#endif

