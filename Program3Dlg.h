
// Program3Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Simulation.h"
#include "GeneticsSimDataParser.h"

// CProgram3Dlg dialog
class CProgram3Dlg : public CDialogEx
{
// Construction
public:
	CProgram3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROGRAM3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Simulation *m_TheSim;
	GeneticsSimDataParser *m_DataParser;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRunsim();
	CEdit m_NumOffspringTF;
	CEdit m_DataFileNameTF;
	CListBox m_ExpResultsListBox;
	afx_msg void OnBnClickedInitsim();
	CListBox m_GenSpecNameTF;
	CListBox m_CommonNameTF;
	CListBox m_NumChromosomesTF;
	CListBox m_GeneDataListBox;
	CListBox m_ParentListBox1;
	CListBox m_ParentListBox2;
	afx_msg void OnBnClickedSave();
	CEdit m_OutputFile;
};
