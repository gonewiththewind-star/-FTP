// FtpDlg.h : header file
//

#if !defined(AFX_FTPDLG_H__60E0DDD2_8629_46A9_B9DA_E1F140BB4C22__INCLUDED_)
#define AFX_FTPDLG_H__60E0DDD2_8629_46A9_B9DA_E1F140BB4C22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg dialog
#include "afxinet.h"

class CFtpDlg : public CDialog
{
// Construction
public:
	CFtpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFtpDlg)
	enum { IDD = IDD_FTP_DIALOG };
	CButton	m_cancel;
	CButton	m_BtnDownLoad;
	CButton	m_BtnUpLoad;
	CButton	m_BtnConnect;
	CListBox	m_ListFile;
	CEdit	m_EditPwd;
	CEdit	m_EditName;
	CEdit	m_EditFtp;
	CStatic	m_StaPwd;
	CStatic	m_StaName;
	CStatic	m_StaFtp;
	CString	m_strFtpSite;
	CString	m_strName;
	CString	m_strPwd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFtpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	virtual void OnCancel();
	afx_msg void OnSelchangeListFile();
	afx_msg void OnDownload();
	afx_msg void OnUpload();
	afx_msg void OnDblclkListFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL Find();
    CInternetSession* pSession;
	CFtpConnection* pConnection;
	CFtpFileFind* pFileFind;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPDLG_H__60E0DDD2_8629_46A9_B9DA_E1F140BB4C22__INCLUDED_)
