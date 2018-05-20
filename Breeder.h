//====================================================================
// Breeder.h
// Interface file that performs the Mendalian Cross
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef BREEDER_H
#define BREEDER_H

#include "Organism.h"
#include "Gene.h"
#include <vector>
#include <string>

using namespace std;

class Breeder
{
	private:
		int m_iCrossovers;					//Number of crossovers that occur in the breeding
		bool m_bCross;						//Flag active when a cross occurs	
		int m_iMax;							//Max value for random number generator
		int m_iRandom;						//Random number generated
		int m_iGeneCounters[3];				//Stores the three counters for the different types of gene results
		vector<string> m_vGenotypes;		//Collection of the child organisms' genotypes
		vector<Gene> *m_vGenes;				//Collection of genes for the organism
		string m_sResults;

	public:
		Breeder();															//Constructor
		~Breeder();															//Destructor
		void breed(Organism *parent1, Organism *parent2, int numOffspring);	//Performs the Mendalian Cross to produce offspring genotypes
		int getHomoDom();													//Get the number of homozygous dominant results for a gene
		int getHeteroDom();													//Get the number of heterozygous dominant results for a gene
		int getHomoRec();													//Get the number of homozygous recessive results for a gene
		void determineCounters(int counter);								//Calculates the counters for the different types of gene results
		void print();														//Prints info regarding offspring
		void  setResults(CListBox *listBox);
		string getResults();
};
#endif