//====================================================================
// GeneInfo.h
// Interface file for the class that holds each gene's master information
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef GENEINFO_H
#define GENEINFO_H

#include "GeneticsSimDataParser.h"

class GeneInfo
{
	private:
		char m_sTraitDesc[32];				//Description of what the specific trait is (phenotype)
		char m_sDomDesc[32];				//Description of the dominant trait
		char m_sDomSymbol[1];				//Character that represents the dominant trait
		char m_sRecDesc[32];				//Description of the recessive trait
		char m_sRecSymbol[1];				//Character that represents the recessive trait
		double m_dCrossover;				//Crossover chance

	public:
		GeneInfo(char *trait, char *domDesc, char *domSymbol, 
			char *recDesc, char *recSymbol, double coChance);		//Constructor
		~GeneInfo();					//Destructor
		char *getTraitDesc();			//Get the trait description
		char *getDomDesc();				//Get the dominant allele’s trait description
		char getDomSymbol();			//Get the dominant allele’s symbol
		char *getRecDesc();				//Get the recessive allele’s trait description
		char getRecSymbol();			//Get the recessive allele’s symbol
		double getCrossover();			//Get the crossover chance
		void print();					//Print the gene's master info
};
#endif