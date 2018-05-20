//====================================================================
// GeneFactory.h
// Interface file that builds the collection of genes
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef GENEINFOFACTORY_H
#define GENEINFOFACTORY_H

#include "GeneInfo.h"
#include "GeneticsSimDataParser.h"
#include "Gene.h"
#include <vector>

using namespace std;

class GeneInfoFactory
{
	private:
		char m_sTraitDesc[32];				//Description of what the specific trait is (phenotype)
		char m_sDomDesc[32];				//Description of the dominant trait
		char m_sDomSymbol[1];				//Character that represents the dominant trait
		char m_sRecDesc[32];				//Description of the recessive trait
		char m_sRecSymbol[1];				//Character that represents the recessive trait
		double m_dCrossover;				//Crossover chance
		GeneticsSimDataParser *m_parser;
		vector<Gene> m_vGenes;				//Collection of genes that point to their master genes

		GeneInfoFactory();					//Private constructor

	public:
		~GeneInfoFactory();						//Destructor
		static GeneInfoFactory *getInstance();	//Get the singleton instance
		vector<GeneInfo> buildGene(char *fileName);	//Builds and returns a collection of genes


};
#endif