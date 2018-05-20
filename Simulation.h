//====================================================================
// Simulation.h
// Interface file to run the simulation
// Author: Drew Humphrey
// Date: April 2018
// CS307 Program 2
// This program is entirely my own work
//====================================================================

#ifndef SIMUTATION_H
#define SIMUTATION_H

#include <vector>
#include "GeneInfo.h"
#include "GeneticsSimDataParser.h"
#include "Organism.h"
#include "Breeder.h"
#include <string>


class Simulation
{
	private:
		Organism *m_Parent1;
		Organism *m_Parent2;
		Breeder *m_Breeder;
		char m_sFileName[64];		//Name of input file
		GeneticsSimDataParser *parser;
		vector<GeneInfo> m_vGenes;	//Collection of master genes
		Simulation();				//Constructor

	public:
		~Simulation();				//Destructor
		void setDataFile(char *fileName);
		char* getDataFile();
		void initSim(char *fileName);
		Organism *getParent1();
		Organism *getParent2();
		string getResults();
		Breeder *getBreeder();
		void printGenes(CListBox *listBox);
		void printParent1(CListBox *listBox);
		void printParent2(CListBox *listBox);
		void printResults(CListBox *listBox);
		void runSimulation(int numOffspring);		//Runs the simulation
		static Simulation *getInstance(); //Get the singleton instance
		GeneInfo *getMasterGene(char allele); //Return the master gene corresponding to the given allele
};
#endif