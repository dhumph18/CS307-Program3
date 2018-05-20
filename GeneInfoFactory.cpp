//====================================================================
// GeneFactory.cpp
// Implementation file that builds the collection of genes
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#include "stdafx.h"
#include "GeneInfoFactory.h"
#include "GeneInfo.h"
#include "Gene.h"
#include <vector>

using namespace std;

//-----------------------------------
// Constructor
//-----------------------------------
GeneInfoFactory::GeneInfoFactory()
{
	m_parser = GeneticsSimDataParser::getInstance();
}

//-----------------------------------
// Destructor
//-----------------------------------
GeneInfoFactory::~GeneInfoFactory()
{
	m_parser = NULL;
	delete m_parser;
}

//-----------------------------------
// Get the singleton instance
//-----------------------------------
GeneInfoFactory *GeneInfoFactory::getInstance()
{
	static GeneInfoFactory *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new GeneInfoFactory();
	}
	return theInstance;
}

//-----------------------------------
// Builds and returns a collection of genes
//-----------------------------------
vector<GeneInfo> GeneInfoFactory::buildGene(char *fileName)
{
	m_parser = GeneticsSimDataParser::getInstance();
	//cout << "\nGenes: " << endl;
	//vector<GeneInfo*> *masters = new vector<GeneInfo*>();
	vector<GeneInfo> masters;
	masters.reserve(10);
	//m_parser->initDataFile(fileName);
	for(int i = 0; i < m_parser->getGeneCount(); i++)
	{
		m_parser->getGeneData(m_sTraitDesc, m_sDomDesc, m_sDomSymbol, m_sRecDesc, m_sRecSymbol, &m_dCrossover);
		GeneInfo *master = new GeneInfo(m_sTraitDesc, m_sDomDesc, m_sDomSymbol, m_sRecDesc, m_sRecSymbol, m_dCrossover);	
		masters.push_back(*master);
		//masters[i] = *master;
		//master->print();
		master = NULL;
		delete master;
	}

	return masters;
}