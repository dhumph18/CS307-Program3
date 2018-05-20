//====================================================================
// Chromosome.cpp
// Interface file for a chromosome object which holds a collecion of genes
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#include "stdafx.h"
#include "Chromosome.h"
#include "Gene.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <string>

using namespace std;

//-----------------------------------
// Constructor
//-----------------------------------
Chromosome::Chromosome()
{
	m_vGenes = new vector<Gene>();
}

//-----------------------------------
// Destructor
//-----------------------------------
Chromosome::~Chromosome()
{

}

//-----------------------------------
//Adds a gene to the collection
//-----------------------------------
void Chromosome::addGene(Gene *gene)
{
	m_vGenes->push_back(*gene);
}

//-----------------------------------
//Get the collection of genes
//-----------------------------------
vector<Gene> *Chromosome::getGenes()
{
	return m_vGenes;
}

//-----------------------------------
//Print the info for each gene on the chromosome
//-----------------------------------
string Chromosome::printGenes()
{
	string str = "";
	for(vector<Gene>::iterator itr = m_vGenes->begin(); itr != m_vGenes->end(); itr++)
	{
		str += itr->printMaster();
		str += "\n";
		/*
		cout << "\t\t\tGene Type: ";
		itr->printGeneInfo();
		*/
	}
	return str;
}
