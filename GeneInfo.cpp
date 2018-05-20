//====================================================================
// GeneInfo.cpp
// Implementation file for the class that holds each gene's master information
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================
#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


#include "GeneInfo.h"
#include "GeneticsSimDataParser.h"

using namespace std;

//-----------------------------------
// Constructor
//-----------------------------------
GeneInfo::GeneInfo(char *trait, char *domDesc, char *domSymbol, 
			char *recDesc, char *recSymbol, double coChance)
{
	
	strcpy(m_sTraitDesc, trait);
	strcpy(m_sDomDesc, domDesc);
	strcpy(m_sDomSymbol, domSymbol);
	strcpy(m_sRecDesc, recDesc);
	strcpy(m_sRecSymbol, recSymbol);
	m_dCrossover = coChance;
}

//-----------------------------------
// Destructor
//-----------------------------------
GeneInfo::~GeneInfo()
{
}

//-----------------------------------
// Get the trait description
//-----------------------------------
char *GeneInfo::getTraitDesc()
{
	return m_sTraitDesc;
}

//-----------------------------------
// Get the dominant trait description
//-----------------------------------
char *GeneInfo::getDomDesc()
{
	return m_sDomDesc;
}

//-----------------------------------
// Get the dominant trait symbol
//-----------------------------------
char GeneInfo::getDomSymbol()
{
	return m_sDomSymbol[0];
}

//-----------------------------------
// Get the recessive trait description
//-----------------------------------
char *GeneInfo::getRecDesc()
{
	return m_sRecDesc;
}

//-----------------------------------
// Get the recessive trait symbol
//-----------------------------------
char GeneInfo::getRecSymbol()
{
	return m_sRecSymbol[0];
}

//-----------------------------------
// Get the crossover chance
//-----------------------------------
double GeneInfo::getCrossover()
{
	return m_dCrossover;
}

//-----------------------------------
// Print the gene's master info
//-----------------------------------
void GeneInfo::print()
{/*
	string str = "";
	str += " Trait Name: ";
	str += this->getTraitDesc();*/
/*
	cout << "\tTrait Name: " << this->getTraitDesc() << endl;
	cout << "\t\t Dominant Name: " << this->getDomDesc() << "(" << this->getDomSymbol() << ")" << endl;
	cout << "\t\t Recessive Name: " << this->getRecDesc() << "(" << this->getRecSymbol() << ")" << endl;
	cout << "\t\t Crossover Chance: " << this->getCrossover() << "\n" << endl;
	*/
}
