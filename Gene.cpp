//====================================================================
// Gene.cpp
// Implementation file for specific genes and the alleles that a current organism has
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#include "stdafx.h"
#include "Gene.h"
#include "GeneInfo.h"
#include <string>

//-----------------------------------
// Constructor
//-----------------------------------
Gene::Gene(GeneInfo *master, char allele1, char allele2)
{
	m_gMaster = master;
	m_sAllele1 = allele1;
	m_sAllele2 = allele2;
}

//-----------------------------------
// Destructor
//-----------------------------------
Gene::~Gene()
{
	m_gMaster = NULL;
	delete m_gMaster;
}

//-----------------------------------
//Get the allele from the first strand for this gene
//-----------------------------------
char Gene::getAllele1()
{
	return m_sAllele1;
}

//-----------------------------------
//Get the allele from the second strand for this gene
//-----------------------------------
char Gene::getAllele2()
{
	return m_sAllele2;
}

//-----------------------------------
//Performs the crossover of the two alleles on the chromosome
//-----------------------------------
GeneInfo *Gene::getMaster()
{
	return m_gMaster;
}

//-----------------------------------
//Performs the crossover of the two alleles on the chromosome
//-----------------------------------
void Gene::crossover()
{
	char temp;
	temp = m_sAllele1;
	m_sAllele1 = m_sAllele2;
	m_sAllele2 = temp;
}

//-----------------------------------
//Print the information of the given gene
//-----------------------------------
void Gene::printGeneInfo()
{
	char tempAl1;
	char tempAl2;
	string str = "";
	//Orders alleles so that a capital letter goes first
	if(m_sAllele1 == toupper(m_sAllele1))
	{
		tempAl1 = m_sAllele1;
		tempAl2 = m_sAllele2;
	}
	else
	{
		tempAl1 = m_sAllele1;
		tempAl2 = m_sAllele2;
	}
	/*
	str += " Trait Name: ";
	str += m_gMaster->getTraitDesc();
	str += "\nDominant Name: ";
	str += */
	
		
	cout << m_gMaster->getTraitDesc() << endl;
	cout << "\t\t\t\tAllele 1: ";

	if(tempAl1 == toupper(tempAl1)) //Evaltuates whether to print the dominant or recessive traits/symbols
	{
		cout << m_gMaster->getDomDesc() << "(" << m_gMaster->getDomSymbol() << ")" << endl;
		cout << "\t\t\t\tAllele 2: ";
		if(tempAl2 == toupper(tempAl2))
			cout << m_gMaster->getDomDesc() << "(" << m_gMaster->getDomSymbol() << ")" << endl;
		else
			cout << m_gMaster->getRecDesc() << "(" << m_gMaster->getRecSymbol() << ")" << endl;
	}
	else
	{
		cout << m_gMaster->getRecDesc() << "(" << m_gMaster->getRecSymbol() << ")" << endl;
		cout << "\t\t\t\tAllele 2: ";
		cout << m_gMaster->getRecDesc() << "(" << m_gMaster->getRecSymbol() << ")" << endl;
	}
	
}

string Gene::printMaster()
{
	string str = "";
	str += " Trait Name: ";
	str += m_gMaster->getTraitDesc();
	str += "   Dominant Name: ";
	str += m_gMaster->getDomDesc();
	str += "(";
	str += m_gMaster->getDomSymbol();
	str += ")\n";
	str += "   Recessive Name: ";
	str += m_gMaster->getRecDesc();
	str += "(";
	str += m_gMaster->getRecSymbol();
	str += ")\n";
	str += "   Chance of Crossover: ";
	str += m_gMaster->getCrossover();

	return str;
}
