//====================================================================
// Breeder.cpp
// Implementation file that performs the Mendalian Cross
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================
#include "stdafx.h"
#pragma warning(disable:4996)
#pragma warning(disable:4018)


#include "Breeder.h"
#include "Gene.h"
#include "Chromosome.h"
#include "Organism.h"
#include "GeneInfo.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

//-----------------------------------
// Constructor
//-----------------------------------
Breeder::Breeder()
{
	m_iCrossovers = 0;
	m_bCross = false;
	m_iMax = 2;
	srand((unsigned int)(time(NULL)));
	m_iRandom = rand() % m_iMax;
	m_vGenes = new vector<Gene>();
	m_sResults = "";
}

//-----------------------------------
// Destructor
//-----------------------------------
Breeder::~Breeder()
{

}

//-----------------------------------
// Performs the Mendalian Cross to produce offspring genotypes
//-----------------------------------
void Breeder::breed(Organism *parent1, Organism *parent2, int numOffspring)
{
	vector<Chromosome> *parent1Chromos = parent1->getChromosomes();
	vector<Chromosome> *parent2Chromos = parent2->getChromosomes();
	string p1strands1[10];
	string p1strands2[10];
	string p2strands1[10];
	string p2strands2[10];

	//Stores the genes of the parent organism in a collection
	for(vector<Chromosome>::iterator itr = parent1Chromos->begin(); itr != parent1Chromos->end(); itr++)
	{
		vector<Gene> *genes = itr->getGenes();
		
		for(vector<Gene>::iterator geneItr  = genes->begin(); geneItr != genes->end(); geneItr++)
		{
			int c = 0;
			m_vGenes->push_back(geneItr[c]);
			c++;
		}
	}

	//Performs cross for each desired offspring
	for(int i = 0; i < numOffspring; i++)
	{
		int max = 10000;
		int random = rand() % max;

		string genotype = "";
		string s1 = "";
		string s2 = "";
		int p1counter = 0;
		int p2counter = 0;
		m_bCross = false;

		//Iterates through chromosomes and genes to create the strands from the first parent
		for(vector<Chromosome>::iterator itr = parent1Chromos->begin(); itr != parent1Chromos->end(); itr++)
		{
			
			string strand1 = "";
			string strand2 = "";
			string genotype = "";
			vector<Gene> *genes = itr->getGenes();
		
			for(vector<Gene>::iterator geneItr  = genes->begin(); geneItr != genes->end(); geneItr++)
			{
				random = rand() % max;
				GeneInfo *master = geneItr->getMaster();
				if((master->getCrossover() * 100) > random) //Perform gene crossover if based on probability
				{
					geneItr->crossover();
					m_bCross = true;
				}
				strand1 += geneItr->getAllele1();
				strand2 += geneItr->getAllele2();
			}

			//Store the strands
			p1strands1[p1counter] = strand1;
			p1strands2[p1counter] = strand2;	
			p1counter++;
		}

		//Iterates through chromosomes and genes to create the strands from the second parent
		for(vector<Chromosome>::iterator itr = parent2Chromos->begin(); itr != parent2Chromos->end(); itr++)
		{
			string strand1 = "";
			string strand2 = "";
			vector<Gene> *genes = itr->getGenes();
			

			for(vector<Gene>::iterator geneItr  = genes->begin(); geneItr != genes->end(); geneItr++)
			{
				random = rand() % max;
				GeneInfo *master = geneItr->getMaster();
				if((master->getCrossover() * 100) > random) //Perform gene crossover if based on probability
				{
					geneItr->crossover();
					m_bCross = true;
				}
				strand1 += geneItr->getAllele1();
				strand2 += geneItr->getAllele2();
			}

			//Store the strands
			p2strands1[p2counter] = strand1;
			p2strands2[p2counter] = strand2;
			p2counter++;
		}
		

		int counter = 0;
		
		//Randomly select an allele for a gene from a randomly selected strand
		while(p1strands1[counter] != "")
		{
			m_iRandom = rand() % m_iMax;
			if(m_iRandom == 0)
				s1 = p1strands1[counter];
			else
				s1 = p1strands2[counter];

			m_iRandom = rand() % m_iMax;
			if(m_iRandom == 0)
				s2 = p2strands1[counter];
			else
				s2 = p2strands2[counter];
			
			//Add the selected alleles to the offspring's genotype
			for(string::size_type i = 0; i < s1.size(); ++i)
			{
				if(s1[i] < s2[i] || s1[i] == s2[i])
				{
					genotype += s1[i];
					genotype += s2[i];
					genotype += " ";
				}
				else
				{
					genotype += s2[i];
					genotype += s1[i];
					genotype += " ";
				}
			}
			counter++;
			
		}
		if(m_bCross) //Increment counter if a crossover occured
			m_iCrossovers++;
		m_vGenotypes.push_back(genotype); //Add the offspring genotype to the collection
	}
}

//-----------------------------------
//Calculates the counters for the different types of gene results
//-----------------------------------
void Breeder::determineCounters(int counter)
{
	int homoDom = 0;
	int heteroDom = 0;
	int homoRec = 0;

	for(int i = 0; i < 3; i++)
		m_iGeneCounters[i] = 0;

	for(string childGeno : m_vGenotypes)
	{
		char alleles[3] = "";
		string alls = childGeno.substr(counter, 2);
		strcpy_s(alleles, alls.c_str());

		if(alleles[0] != 0)
		{
			if(alleles[0] != alleles[1])
				heteroDom++;	
			else if(alleles[0] == toupper(alleles[0]))
				homoDom++;
			else 
				homoRec++;
		}
	}
		m_iGeneCounters[0] = homoDom;
		m_iGeneCounters[1] = heteroDom;;
		m_iGeneCounters[2] = homoRec;
	
}

//-----------------------------------
//Get the number of homozygous dominant results for a gene
//-----------------------------------
int Breeder::getHomoDom()
{
	return m_iGeneCounters[0];
}
//-----------------------------------
//Get the number of heterozygous dominant results for a gene
//-----------------------------------
int Breeder::getHeteroDom()
{
	return m_iGeneCounters[1];
}

//-----------------------------------
//Get the number of homozygous recessive results for a gene
//-----------------------------------
int Breeder:: getHomoRec()
{
	return m_iGeneCounters[2];
}
/*
//-----------------------------------
//Prints info regarding offspring
//-----------------------------------
void Breeder::print()
{
	int counter = 0;
	string sampleGeno = m_vGenotypes[0];
	GeneInfo *master = NULL;;

	for(int i = 0; i < m_vGenes->size(); i++)
	{
		for(vector<Gene>::iterator itr = m_vGenes->begin(); itr != m_vGenes->end(); itr++)
		{
			if(sampleGeno[counter] == itr->getAllele1() || sampleGeno[counter] == itr->getAllele2())
				master = itr->getMaster();
		}

		determineCounters(counter);
		
		cout << "Gene: " << master->getTraitDesc() << "\n\t";
		cout << this->getHomoDom() << " homozygous dominant (" 
			<< master->getDomDesc() << " " << master->getDomSymbol() << master->getDomSymbol() << ")" << endl;

		cout << "\t" << this->getHeteroDom() << " heterozygous dominant (" 
			<< master->getDomDesc() << " " << master->getDomSymbol() << master->getRecSymbol() << ")" << endl;

		cout << "\t" << this->getHomoRec() << " homozygous recessive (" 
			<< master->getRecDesc() << " " << master->getRecSymbol() << master->getRecSymbol() << ")\n" << endl;

		counter += 3;
	}
	
	cout << "There were " << m_iCrossovers << " offspring organisms that had at least 1 crossover.\n" << endl;
}*/

void Breeder::setResults(CListBox *listBox)
{
	int c = 1;
	int counter = 0;
	string sampleGeno = m_vGenotypes[0];
	GeneInfo *master = NULL;;

	char line[128];
	sprintf(line, " There were %d offspring organisms that had a crossover", m_iCrossovers);
	listBox->AddString(line);
	m_sResults += line;
	m_sResults += "\n";

	for(int i = 0; i < m_vGenes->size(); i++)
	{
		for(vector<Gene>::iterator itr = m_vGenes->begin(); itr != m_vGenes->end(); itr++)
		{
			if(sampleGeno[counter] == itr->getAllele1() || sampleGeno[counter] == itr->getAllele2())
				master = itr->getMaster();
		}

		determineCounters(counter);
		
		if(c < 10)
		{
			sprintf(line, "%d) Gene: %s", c, master->getTraitDesc());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";

			sprintf(line, "%d.      %d Homozygous Dominant (%s %c%c)", c, this->getHomoDom(), master->getDomDesc(), master->getDomSymbol(), master->getDomSymbol());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";

			sprintf(line, "%d.      %d Heterozygous Dominant (%s %c%c)", c, this->getHeteroDom(), master->getDomDesc(), master->getDomSymbol(), master->getRecSymbol());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";

			sprintf(line, "%d.      %d Homozygous Recessive (%s %c%c)", c, this->getHomoRec(), master->getRecDesc(), master->getRecSymbol(), master->getRecSymbol());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";
		}
		else
		{
			sprintf(line, "a) Gene: %s", master->getTraitDesc());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";

			sprintf(line, "a.      %d Homozygous Dominant (%s %c%c)", this->getHomoDom(), master->getDomDesc(), master->getDomSymbol(), master->getDomSymbol());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";

			sprintf(line, "a.      %d Heterozygous Dominant (%s %c%c)", this->getHeteroDom(), master->getDomDesc(), master->getDomSymbol(), master->getRecSymbol());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";

			sprintf(line, "a.      %d Homozygous Recessive (%s %c%c)", this->getHomoRec(), master->getRecDesc(), master->getRecSymbol(), master->getRecSymbol());
			listBox->AddString(line);
			m_sResults += line;
			m_sResults += "\n";
		}

		//strcpy(line, "");
		//listBox->AddString(line);
		//m_sResults += "\n";
		c++;
		counter += 3;
	}
}

string Breeder::getResults()
{
	return m_sResults;
}
