//====================================================================
// GeneticsSimDataParser.cpp
// Implementation file for the data parser.
// Author: Dr. Rick Coleman
// Date: December 2009
//====================================================================

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable:4996)


#include "GeneticsSimDataParser.h"
#include <string.h>


//-----------------------------------
// Constructor
//-----------------------------------
GeneticsSimDataParser::GeneticsSimDataParser()
{
	// Initialize everything
	m_iNumChromosomes = 0;
	m_iNumGenes = 0;
	m_iNextGeneNumber = 0;
	m_iNextChNumP1 = 0;
	m_iNextChNumP2 = 0;
}

//-----------------------------------
// Destructor
//-----------------------------------
GeneticsSimDataParser::~GeneticsSimDataParser()
{
}

//-----------------------------------
// Get the singleton instance
//-----------------------------------
GeneticsSimDataParser *GeneticsSimDataParser::getInstance()
{
	static GeneticsSimDataParser *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new GeneticsSimDataParser();
	}
	return theInstance;
}

//-----------------------------------
// Initialize the data file
//-----------------------------------
bool GeneticsSimDataParser::initDataFile(char *fileName)
{
	bool flag = false;
	char line[128];
	strcpy(m_sFileName, fileName);

	// Open the data file for reading
	inFile = new ifstream();				// Create an ifstream object
	inFile->open(fileName, fstream::in);	// Open it
	if(inFile->is_open())					// Make sure it is open
	{
		flag = true;
		// Get the basic information
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<GENE>") == 0)
			{
				m_iNumGenes++;	// Count all genes
			}
			else if(strcmp(line, "<GENUS>") == 0)
			{
				getNextLine(line, 127); // Read the genus string
				strcpy(m_sGenus, line); // Save the genus name
			}
			else if(strcmp(line, "<SPECIES>") == 0)
			{
				getNextLine(line, 127); // Read the species string
				strcpy(m_sSpecies, line); // Save the species name
			}
			else if(strcmp(line, "<CHROMOSOME_COUNT>") == 0)
			{
				getNextLine(line, 127); // Read the chromosome count string
				m_iNumChromosomes = atoi(line); // Save the count
			}
			else if(strcmp(line, "<COMMON_NAME>") == 0)
			{
				getNextLine(line, 127); // Read the common name string
				strcpy(m_sCommonName, line); // Save the common name
			}
		}
		inFile->close();	// Close the file
		delete inFile;		// Destroy the ifstream object
	}
	else
	{
		//cout << "Failed to open file\n";
		//cout << "Program terminated.\n\n";
		//exit(0);
	}
	return flag;
}

//-----------------------------------
// Get the number of genes
//-----------------------------------
int GeneticsSimDataParser::getGeneCount()
{
	return m_iNumGenes;
}

//-----------------------------------
// Get the number of chromosomes
//-----------------------------------
int GeneticsSimDataParser::getChromosomeCount()
{
	return m_iNumChromosomes;
}

//-----------------------------------
// Get the genus name
//-----------------------------------
char *GeneticsSimDataParser::getGenus()
{
	return m_sGenus;
}

//-----------------------------------
// Get the species name
//-----------------------------------
char *GeneticsSimDataParser::getSpecies()
{
	return m_sSpecies;
}

//-----------------------------------
// Get the full scientific name
//-----------------------------------
char *GeneticsSimDataParser::getScientificName()
{
	// Build the full name just in case it hasn't been done
	sprintf(m_sSciName, "%s %s", m_sGenus, m_sSpecies);
	return m_sSciName;
}

//-----------------------------------
// Get the common name
//-----------------------------------
char *GeneticsSimDataParser::getCommonName()
{
	return m_sCommonName;
}

//--------------------------------------------------------------------------
// Get data on the next gene
// Args:	*trait - pointer to a character array to hold the trait name
//			*domDesc - pointer to a character array to hold the name of the
//						dominant allele name
//			*domSymbol - pointer to a char variable to hold the dominant
//						trait letter symbol
//			*recDesc - pointer to a character array to hold the name of the
//						recessive allele name
//			*recSymbol - pointer to a char variable to hold the recessive
//						trait letter symbol
//			*coChance - pointer to double variable to hold the cross-over
//						probability (range 0.0 to 100.0)
//--------------------------------------------------------------------------
bool GeneticsSimDataParser::getGeneData(char *trait, char *domDesc, char *domSymbol, 
										char *recDesc, char *recSymbol, double *coChance)
{
	int gNum = 0;
	char line[128];

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current Gene count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<GENE>") == 0) // Got one
			{
				if(gNum == m_iNextGeneNumber)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the gene trait name
						if(strcmp(line, "<GENE_TRAIT>") == 0)
						{
							if(getNextLine(line, 127))
							{
								strcpy(trait, line); // Set the trait name
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<DOMINANT_ALLELE>") == 0)
						{
							if(getNextLine(line, 127))
							{
								strcpy(domDesc, line); // Set the dominant allele name
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<DOMINANT_SYMBOL>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*domSymbol = line[0]; // Set the dominant allele symbol
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<RECESSIVE_ALLELE>") == 0)
						{
							if(getNextLine(line, 127))
							{
								strcpy(recDesc, line); // Set the recessive allele name
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<RECESSIVE_SYMBOL>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*recSymbol = line[0]; // Set the dominant allele symbol
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<CROSSOVER_CHANCE>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*coChance = atof(line); // Set the cross-over chance
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</GENE>") == 0)
						{
							m_iNextGeneNumber++; // Increment for next call to this function
							inFile->close();
							delete inFile; // Delete the istream object not the file
							return true; // Got it
						}
					} // end while
				} // end if(gNum == nextGene)
				else
				{
					gNum++; // Check the next one
				}
			}
		}
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the genes
}

//--------------------------------------------------------------------------
// Get data on the next chromosome for parent1
// Args:	*strand1 - pointer to a character array to hold the stand1
//						genotype description as a string, e.g. "T S".  
//			*strand2 - pointer to a character array to hold the stand2
//						genotype description as a string, e.g. "t s".
//  
//						If this is a pea plant with the phenotype of tall 
//						with green seeds.  Its phenotype is heterozygous 
//						tall, and heterozygous green seeds, but these two
//						genes are linked because they are on the same
//						chromosome.
//--------------------------------------------------------------------------
bool GeneticsSimDataParser::getP1Chromosome(char *strand1, char *strand2)
{
	int cNum = 0;
	char line[128];

	// If we have already gotten all the chromosomes for P1 then return false
	if(m_iNextChNumP1 >= m_iNumChromosomes) return false;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the first parent
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<PARENT>") == 0) // Got it
			{
				// Get the next chromosome
				while(getNextLine(line, 127))
				{
					// Get the sensor type
					if(strcmp(line, "<CHROMOSOME>") == 0)
					{
						if(cNum == m_iNextChNumP1) // get this one
						{
							while(getNextLine(line, 127))
							{
								if(strcmp(line, "<STRAND1>") == 0)
								{
									if(getNextLine(line, 127)) // Read the genotype string
									{
										strcpy(strand1, line); 
									}
									else
										return false; // Oops!
								}
								else if(strcmp(line, "<STRAND2>") == 0)
								{
									if(getNextLine(line, 127)) // Read the genotype string
									{
										strcpy(strand2, line); 
									}
									else
										return false; // Oops!
								}
								else if(strcmp(line, "</CHROMOSOME>") == 0)
								{
									m_iNextChNumP1++;
									inFile->close();
									delete inFile; // Delete the istream object not the file
									return true; // Got one
								}
							}
						}
						else
						{
							cNum++;
						}
					}
				} // End while(getNextLine 
			} // end if PARENT tag
		} // End while(getNextLine
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the chromosomes or failed to open file
}

//--------------------------------------------------------------------------
// Get data on the next chromosome for parent2
// Args:	*strand1 - pointer to a character array to hold the stand1
//						genotype description as a string, e.g. "T S".  
//			*strand2 - pointer to a character array to hold the stand2
//						genotype description as a string, e.g. "t s".
//  
//						If this is a pea plant with the phenotype of tall 
//						with green seeds.  Its phenotype is heterozygous 
//						tall, and heterozygous green seeds, but these two
//						genes are linked because they are on the same
//						chromosome.
//--------------------------------------------------------------------------
bool GeneticsSimDataParser::getP2Chromosome(char *strand1, char *strand2)
{
	int cNum = 0;
	char line[128];
	bool foundFirst = false;

	// If we have already gotten all the chromosomes for P2 then return false
	if(m_iNextChNumP2 >= m_iNumChromosomes) return false;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the first parent
		while(getNextLine(line, 127) && !foundFirst)
		{
			if(strcmp(line, "<PARENT>") == 0) // Got it
			{
				foundFirst = true;
			}
		}
		// Now Read to the the second parent
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<PARENT>") == 0) // Got it
			{
				// Get the next chromosome
				while(getNextLine(line, 127))
				{
					// Get the sensor type
					if(strcmp(line, "<CHROMOSOME>") == 0)
					{
						if(cNum == m_iNextChNumP2) // get this one
						{
							while(getNextLine(line, 127))
							{
								if(strcmp(line, "<STRAND1>") == 0)
								{
									if(getNextLine(line, 127)) // Read the genotype string
									{
										strcpy(strand1, line); 
									}
									else
										return false; // Oops!
								}
								else if(strcmp(line, "<STRAND2>") == 0)
								{
									if(getNextLine(line, 127)) // Read the genotype string
									{
										strcpy(strand2, line); 
									}
									else
										return false; // Oops!
								}
								else if(strcmp(line, "</CHROMOSOME>") == 0)
								{
									m_iNextChNumP2++;
									inFile->close();
									delete inFile; // Delete the istream object not the file
									return true; // Got one
								}
							}
						}
						else
						{
							cNum++;
						}
					}
				} // End while(getNextLine 
			} // end if PARENT tag
		} // End while(getNextLine
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the chromosomes or failed to open file
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and places
//   them in buffer, removing any leading white
//   space.  Skips blank lines. Ignors comment
//   lines starting with <!-- and ending with -->
//   
// Args:  buffer -- char array to read line into.
//        n -- length of buffer.
// Returns: True if a line was successfully read,
//    false if the end of file was encountered.
// Notes: Function provided by instructor.
//------------------------------------------------
bool GeneticsSimDataParser::getNextLine(char *buffer, int n)
{
    bool    done = false;
	char    tempBuf[128];
	char	*temp;
    while(!done)
    {
        inFile->getline(tempBuf, n); // Read a line from the file

        if(inFile->good())          // If a line was successfully read check it
        {
           if(strlen(tempBuf) == 0)     // Skip any blank lines
               continue;
		   else if(strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
			   continue;
           else done = true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(buffer, "");  // Clear the buffer array
            return false;        // Flag end of file
        }
    } // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while(isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while(isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
    return true;  // Flag a successful read
}




