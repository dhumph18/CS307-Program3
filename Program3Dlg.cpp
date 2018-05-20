
// Program3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Program3.h"
#include "Program3Dlg.h"
#include "afxdialogex.h"
#include "Simulation.h"
#include "GeneticsSimDataParser.h"
#include "Gene.h"
#include "Chromosome.h"
#include "Breeder.h"
#include <vector>
#include <iostream>
#include <fstream>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProgram3Dlg dialog



CProgram3Dlg::CProgram3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgram3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgram3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_NumOffspringTF);
	DDX_Control(pDX, IDC_EDIT1, m_DataFileNameTF);
	DDX_Control(pDX, IDC_LIST7, m_ExpResultsListBox);
	DDX_Control(pDX, IDC_LIST3, m_GenSpecNameTF);
	DDX_Control(pDX, IDC_LIST2, m_CommonNameTF);
	DDX_Control(pDX, IDC_LIST5, m_NumChromosomesTF);
	DDX_Control(pDX, IDC_LIST1, m_GeneDataListBox);
	DDX_Control(pDX, IDC_LIST6, m_ParentListBox1);
	DDX_Control(pDX, IDC_LIST4, m_ParentListBox2);
	DDX_Control(pDX, IDC_EDIT3, m_OutputFile);
}

BEGIN_MESSAGE_MAP(CProgram3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RunSim, &CProgram3Dlg::OnBnClickedRunsim)
	ON_BN_CLICKED(IDC_InitSim, &CProgram3Dlg::OnBnClickedInitsim)
	ON_BN_CLICKED(IDC_Save, &CProgram3Dlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CProgram3Dlg message handlers

BOOL CProgram3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->SetWindowText("Program3 - Drew Humphrey");

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProgram3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProgram3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProgram3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProgram3Dlg::OnBnClickedRunsim()
{
	char line[32];
	
	m_NumOffspringTF.GetWindowText(line, 31);
	int numOffspring = atoi(line);
	if(numOffspring <= 0 || numOffspring > 1000)
	{
		MessageBoxA("You must enter the number of offspring (1-1000).",
			"Invalid Offspring Count", MB_OK | MB_ICONWARNING);
		return;
	}

	m_TheSim = Simulation::getInstance();
	m_TheSim->runSimulation(numOffspring);
	m_TheSim->printResults(&m_ExpResultsListBox);
	
	//strcpy(line, "Test\nPart2");
	//m_NumOffspringTF.SetWindowTextA(line);
}


void CProgram3Dlg::OnBnClickedInitsim()
{
	char fileName[64]; // Data file name
	char line[64];
	int count;
	Organism *org;
	GeneInfo *mGene;
	count = 1;
	vector<Gene> *gVec;
	char allele1, allele2;
	
	// Get name of the data file
	m_DataFileNameTF.GetWindowText(fileName, 63); 
	
	// Instantiate the data parser
	m_DataParser = GeneticsSimDataParser::getInstance();
	// Give the data parser the name of the data file and initialize the data
	if(!m_DataParser->initDataFile(fileName))
	{
		MessageBoxA("Failed to open data file.  Application terminating.", 
			"Data File Failure", MB_OK | MB_ICONERROR);
		exit(0);
	}
	// Create the simulation and create the organisms
	m_TheSim = Simulation::getInstance();
	m_TheSim->initSim(fileName);

	//----------------------------------------
	// Get the data and write it to the GUI
	//----------------------------------------
	// Set genius-species name
	m_GenSpecNameTF.AddString(m_DataParser->getScientificName());
	// Set common name
	m_CommonNameTF.AddString(m_DataParser->getCommonName());
	//m_CommonNameTF.AddString("ZAdded");
	// Set chromosome count
	sprintf(line, "%d", m_DataParser->getChromosomeCount());
	m_NumChromosomesTF.AddString(line);
	// List gene/chromosome data 
	m_GeneDataListBox.ResetContent();
	org = m_TheSim->getParent1(); // Get a parent
	vector<Chromosome> *chVec = org->getChromosomes(); // Get the vector of chromosomes
	
	int chromeCount = 1;
	int counter = 1;
	for(vector<Chromosome>::iterator cItr = chVec->begin(); cItr != chVec->end(); cItr++)
	{
		
		
		// Add a chrosoome number
		sprintf(line, "%d) Chromosome %d", counter, count);
		count++;
		m_GeneDataListBox.AddString(line);
		gVec = cItr->getGenes();
		// List all the genes in this chromosome
		for(vector<Gene>::iterator gItr = gVec->begin(); gItr != gVec->end(); gItr++)
		{
			if(counter < 10)
			{
				mGene = gItr->getMaster();
				sprintf(line, "%d.    Trait Name: %s", counter, mGene->getTraitDesc());
				m_GeneDataListBox.AddString(line);
				sprintf(line, "%d.%d        Dominant Name: %s (%c)", counter, chromeCount,  mGene->getDomDesc(),
					mGene->getDomSymbol());
				m_GeneDataListBox.AddString(line);
				sprintf(line, "%d.%d        Recessive Name: %s (%c)", counter, chromeCount, mGene->getRecDesc(),
					mGene->getRecSymbol());
				m_GeneDataListBox.AddString(line);
				sprintf(line, "%d.%d       Chance of crossover: %.2f", counter, chromeCount, mGene->getCrossover());
				m_GeneDataListBox.AddString(line);

				counter++;
			}
			else
			{
				mGene = gItr->getMaster();
				sprintf(line, "a.    Trait Name: %s", mGene->getTraitDesc());
				m_GeneDataListBox.AddString(line);
				sprintf(line, "a.%d        Dominant Name: %s (%c)", chromeCount,  mGene->getDomDesc(),
					mGene->getDomSymbol());
				m_GeneDataListBox.AddString(line);
				sprintf(line, "a.%d        Recessive Name: %s (%c)", chromeCount, mGene->getRecDesc(),
					mGene->getRecSymbol());
				m_GeneDataListBox.AddString(line);
				sprintf(line, "a.%d       Chance of crossover: %.2f", chromeCount, mGene->getCrossover());
				m_GeneDataListBox.AddString(line);

				counter++;
			}
		}
		chromeCount++;
	} // End for all chromosomes

	// List parent 1 data (already have org pointing to it)
	m_ParentListBox1.ResetContent();
	org = m_TheSim->getParent1(); 
	chVec = org->getChromosomes(); // Get the vector of chromosomes
	for(vector<Chromosome>::iterator cItr = chVec->begin(); cItr != chVec->end(); cItr++)
	{
		gVec = cItr->getGenes();
		// List all the genes in this chromosome
		for(vector<Gene>::iterator gItr = gVec->begin(); gItr != gVec->end(); gItr++)
		{
			allele1 = gItr->getAllele1();
			allele2 = gItr->getAllele2();
			mGene = gItr->getMaster();
			if(allele1 == allele2) // Its homozygous
			{
				if(isupper(allele1)) // Its dominant
				{
					sprintf(line, "%c%c - Homozygous Dominant - %s = %s",
						allele1, allele2, mGene->getTraitDesc(), mGene->getDomDesc());
					m_ParentListBox1.AddString(line);
				}
				else // Its recessive
				{
					sprintf(line, "%c%c - Homozygous Recessive - %s = %s",
						allele1, allele2, mGene->getTraitDesc(), mGene->getRecDesc());
					m_ParentListBox1.AddString(line);
				}
			}
			else // Its heterozygous
			{
				if(isupper(allele1)) // Allele1 is the upper case letter
				{
					sprintf(line, "%c%c - Heterozygous Dominant - %s = %s",
						allele1, allele2, mGene->getTraitDesc(), mGene->getDomDesc());
					m_ParentListBox1.AddString(line);
				}
				else // Allele2 is the upper case letter
				{
					sprintf(line, "%c%c - Heterozygous Dominant - %s = %s",
						allele2, allele1, mGene->getTraitDesc(), mGene->getDomDesc());
					m_ParentListBox1.AddString(line);
				}
			}
		}
	}

	// List parent 2 data (already have org pointing to it)
	m_ParentListBox2.ResetContent();
	org = m_TheSim->getParent2(); 
	chVec = org->getChromosomes(); // Get the vector of chromosomes
	for(vector<Chromosome>::iterator cItr = chVec->begin(); cItr != chVec->end(); cItr++)
	{
		gVec = cItr->getGenes();
		// List all the genes in this chromosome
		for(vector<Gene>::iterator gItr = gVec->begin(); gItr != gVec->end(); gItr++)
		{
			allele1 = gItr->getAllele1();
			allele2 = gItr->getAllele2();
			mGene = gItr->getMaster();
			if(allele1 == allele2) // Its homozygous
			{
				if(isupper(allele1)) // Its dominant
				{
					sprintf(line, "%c%c - Homozygous Dominant - %s = %s",
						allele1, allele2, mGene->getTraitDesc(), mGene->getDomDesc());
					m_ParentListBox2.AddString(line);
				}
				else // Its recessive
				{
					sprintf(line, "%c%c - Homozygous Recessive - %s = %s",
						allele1, allele2, mGene->getTraitDesc(), mGene->getRecDesc());
					m_ParentListBox2.AddString(line);
				}
			}
			else // Its heterozygous
			{
				if(isupper(allele1)) // Allele1 is the upper case letter
				{
					sprintf(line, "%c%c - Heterozygous Dominant - %s = %s",
						allele1, allele2, mGene->getTraitDesc(), mGene->getDomDesc());
					m_ParentListBox2.AddString(line);
				}
				else // Allele2 is the upper case letter
				{
					sprintf(line, "%c%c - Heterozygous Dominant - %s = %s",
						allele2, allele1, mGene->getTraitDesc(), mGene->getDomDesc());
					m_ParentListBox2.AddString(line);
				}
			}
		}
	}

	//system("pause");
}


void CProgram3Dlg::OnBnClickedSave()
{
	char filename[64];
	ofstream output;
	string str = m_TheSim->getResults();

	m_OutputFile.GetWindowTextA(filename, 63);
	output.open(filename);
	output << str;
	output.close();

}
