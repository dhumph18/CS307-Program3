//====================================================================
// Gene.h
// Interface file for specific genes and the alleles that a current organism has
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef GENE_H
#define GENE_H

#include "GeneInfo.h"
#include "string"

using namespace std;

class Gene
{
	private:
		GeneInfo *m_gMaster;			//The master gene of the given gene
		char m_sAllele1;				//The first allele of the given gene
		char m_sAllele2;				//The second allele of the given gene
		
	public:
		Gene(GeneInfo *master, char allele1, char allele2);			//Private constructor
		~Gene();						//Destructor
		char getAllele1();				//Get the allele from the first strand for this gene
		char getAllele2();				//Get the allele from the second strand for this gene
		GeneInfo *getMaster();			//Get the master gene associated with this gene
		void crossover();				//Performs the crossover of the two alleles on the chromosome
		void printGeneInfo();			//Print the information of the given gene
		string printMaster();
};
#endif
