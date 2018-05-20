//====================================================================
// GeneticsSimDataParser.h
// Interface file for the data parser.
// Author: Dr. Rick Coleman
// Date: December 2009
//====================================================================
#ifndef GENETICSSIMDATAPARSER_H
#define GENETICSSIMDATAPARSER_H

#include <fstream>
#include <iostream>

using namespace std;

class GeneticsSimDataParser
{
	private:
		ifstream	*inFile;				// Genetics sim data definition file
		int			m_iNumChromosomes;		// Number of chromosomes in the test organism
		int			m_iNumGenes;			// Number of master genes
		int			m_iNextGeneNumber;		// Next master gene number
		int			m_iNextChNumP1;			// Next chromosome number for parent 1
		int			m_iNextChNumP2;			// Next chromosome number for parent 2
		char        m_sFileName[64];		// Data file name
		char		m_sGenus[32];			// Genus name of this test organism
		char		m_sSpecies[32];			// Species name of this test organism
		char		m_sSciName[64];			// Full scientific name of the test organism
		char		m_sCommonName[32];		// Common use name of the test organism

		GeneticsSimDataParser();			// Private Constructor

	public:
		~GeneticsSimDataParser();				// Destructor
		static GeneticsSimDataParser *getInstance();	// Get the singleton instance
		bool initDataFile(char *fileName);
		int getChromosomeCount();
		int getGeneCount();
		char *getGenus();
		char *getSpecies();
		char *getScientificName();
		char *getCommonName();
		bool getP1Chromosome(char *strand1, char *strand2);		
		bool getP2Chromosome(char *strand1, char *strand2);		
		bool getGeneData(char *trait, char *domDesc, char *domSymbol, 
			char *recDesc, char *recSymbol, double *coChance);
	private:
		bool getNextLine(char *buffer, int n);

};
#endif