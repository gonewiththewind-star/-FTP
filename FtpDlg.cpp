// FtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ftp.h"
#include "afxinet.h"
#include "FtpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg dialog

CFtpDlg::CFtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFtpDlg)
	m_strFtpSite = _T("");
	m_strName = _T("");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFtpDlg)
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_DOWNLOAD, m_BtnDownLoad);
	DDX_Control(pDX, IDC_UPLOAD, m_BtnUpLoad);
	DDX_Control(pDX, IDOK, m_BtnConnect);
	DDX_Control(pDX, IDC_LIST_FILE, m_ListFile);
	DDX_Control(pDX, IDC_EDIT_PWD, m_EditPwd);
	DDX_Control(pDX, IDC_EDIT_NAME, m_EditName);
	DDX_Control(pDX, IDC_EDIT_FTP, m_EditFtp);
	DDX_Control(pDX, IDC_STATIC_PWD, m_StaPwd);
	DDX_Control(pDX, IDC_STATIC_NAME, m_StaName);
	DDX_Control(pDX, IDC_STATIC_FTP, m_StaFtp);
	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtpSite);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFtpDlg, CDialog)
	//{{AFX_MSG_MAP(CFtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnConnect)
	ON_LBN_SELCHANGE(IDC_LIST_FILE, OnSelchangeListFile)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_LBN_DBLCLK(IDC_LIST_FILE, OnDblclkListFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg message handlers

BOOL CFtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	//������ʼ��
	m_strFtpSite=_T("58.192.112.20");
	//��½����ʼ��
	m_strName=_T("anonymous");
	//�����ʼ��
	m_strPwd=_T("");
	//���½���
	UpdateData(FALSE);
   	//�������غ��ϴ���ť
	m_BtnDownLoad.EnableWindow(FALSE);
	m_BtnUpLoad.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFtpDlg::OnConnect() 
{ 

	CString strConnect;
	m_BtnConnect.GetWindowText(strConnect);

	//��õ�ǰ����
	UpdateData(TRUE);
	//�ж�ftp��ַ���Ƿ�Ϊ��
	if(m_strFtpSite.IsEmpty())
	{
		MessageBox("������ftp��������ַ�� ");		
		return;
	}           
	//����б������
	while(m_ListFile.GetCount()!=0)
			m_ListFile.DeleteString(0);

	//TRACE("strConnect:%s",strConnect);
	//AfxMessageBox(strConnect);

	if(strConnect=="����")
	{
	
	
		//����Internet�Ự
	    pSession=new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
		try
		{
			//��ͼ����FTP����
		    pConnection=pSession->GetFtpConnection(m_strFtpSite,m_strName,m_strPwd);
		}
		catch (CInternetException* e)
		{
			//������
			e->Delete();
			pConnection=NULL;
			AfxMessageBox("���Ӵ��������ַ���û�������");
			return;
		}
		if (pConnection!=NULL)
		{
			//����CFtpFileFind����
			//����CFtpConnection�����ָ��
			pFileFind=new CFtpFileFind(pConnection);
		m_BtnUpLoad.EnableWindow(TRUE);
		}
		if(Find())
		{
			m_BtnConnect.SetWindowText("�Ͽ�����");
			if(m_strName=="")
			{
				m_strName=_T("anonymous");
				m_strPwd=_T("anonymous");
				UpdateData(FALSE);
			}

		}

		else
			AfxMessageBox("������ȷ��ʼ����");
   

	}
	else
	{
		if (pFileFind)
		{
			pFileFind->Close();
			delete pFileFind;
		}
	
    	if (pSession)
		{
		pSession->Close();
		delete pSession;
		}
	
		m_BtnConnect.SetWindowText("����");
		m_cancel.EnableWindow(TRUE);
		m_BtnUpLoad.EnableWindow(FALSE);
		   //��������������ı��ͱ༭��ؼ�
        m_EditFtp.EnableWindow(TRUE);
	    m_EditName.EnableWindow(TRUE);
	    m_EditPwd.EnableWindow(TRUE);
	   	m_StaFtp.EnableWindow(TRUE);
	    m_StaName.EnableWindow(TRUE);
	    m_StaPwd.EnableWindow(TRUE);
	}


	
}

void CFtpDlg::OnCancel() 
{	CString strConnect;
	m_BtnConnect.GetWindowText(strConnect);

	//��õ�ǰ����
	UpdateData(TRUE);
	if(strConnect=="�Ͽ�����")
     CFtpDlg::OnConnect();
	CDialog::OnCancel();
}

void CFtpDlg::OnSelchangeListFile() 
{
	//��õ�ǰ����
	UpdateData(TRUE);
	int nSel = m_ListFile.GetCurSel();
	CString strSourceName;
	//����û����б���е�ѡ��
	m_ListFile.GetText(nSel,strSourceName);
	if(strSourceName.GetAt(0)!='[')
	{
		//��ֹ����������ı��ͱ༭��ؼ�
	    m_EditFtp.EnableWindow(FALSE);
	    m_EditName.EnableWindow(FALSE);
	    m_EditPwd.EnableWindow(FALSE);
	    m_StaFtp.EnableWindow(FALSE);
	    m_StaName.EnableWindow(FALSE);
	    m_StaPwd.EnableWindow(FALSE);
	    //���ò�ѯ���ϴ���ť

	    //�������ذ�ť
	    m_BtnDownLoad.EnableWindow(TRUE);
		return;
	}
	else
	{
		//�������ذ�ť
	    m_BtnDownLoad.EnableWindow(FALSE);
	    //�����ѯ���ϴ���ť
	    //m_BtnUpLoad.EnableWindow(TRUE);
	    m_BtnConnect.EnableWindow(TRUE);
	    //��������������ı��ͱ༭��ؼ�
        m_EditFtp.EnableWindow(TRUE);
	    m_EditName.EnableWindow(TRUE);
	    m_EditPwd.EnableWindow(TRUE);
	    m_StaFtp.EnableWindow(TRUE);
	    m_StaName.EnableWindow(TRUE);
	    m_StaPwd.EnableWindow(TRUE);

	}
}


void CFtpDlg::OnDownload() 
{
	//��õ�ǰ����
	UpdateData(TRUE);
	int nSel = m_ListFile.GetCurSel();
	CString strSourceName;
	
	//����û����б���е�ѡ��
	m_ListFile.GetText(nSel,strSourceName);
	if(strSourceName.GetAt(0)!='[')
	{
		//ѡ������ļ�
        CString strDestName;
		CFileDialog dlg(FALSE,"",strSourceName);
		if(dlg.DoModal()==IDOK)
		{
			//��������ļ��ڱ��ػ��ϴ洢��·��������
			strDestName = dlg.GetPathName();
			//�����ļ�
			if(pConnection->GetFile(strSourceName,strDestName))
			{
				AfxMessageBox("���سɹ�! ",MB_OK|MB_ICONINFORMATION);
				//�������ذ�ť
				m_BtnDownLoad.EnableWindow(FALSE);

			}
				
			else
				AfxMessageBox("����ʧ��! ",MB_OK|MB_ICONSTOP);
		}
		else
		{	
			if(strSourceName=="")
				AfxMessageBox("��д���ļ���! ",MB_OK|MB_ICONSTOP);
			
		}
	}
	else
	{
		//ѡ�����Ŀ¼
        AfxMessageBox("��������Ŀ¼! ",MB_OK|MB_ICONSTOP);
	}

	//�����ѯ���ϴ���ť
	m_BtnUpLoad.EnableWindow(TRUE);
	//m_BtnQuery.EnableWindow(TRUE);
	//��������������ı��ͱ༭��ؼ�
    m_EditFtp.EnableWindow(TRUE);
	m_EditName.EnableWindow(TRUE);
	m_EditPwd.EnableWindow(TRUE);
	m_StaFtp.EnableWindow(TRUE);
	m_StaName.EnableWindow(TRUE);
	m_StaPwd.EnableWindow(TRUE);		
}

void CFtpDlg::OnUpload() 
{
	//��õ�ǰ����
	UpdateData(TRUE);
	//��ֹ����������ı��ͱ༭��ؼ�
	m_EditFtp.EnableWindow(FALSE);
	m_EditName.EnableWindow(FALSE);
	m_EditPwd.EnableWindow(FALSE);
	m_StaFtp.EnableWindow(FALSE);
	m_StaName.EnableWindow(FALSE);
	m_StaPwd.EnableWindow(FALSE);
	//��ֹ��ѯ��ť
	m_BtnConnect.EnableWindow(FALSE);
	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,"","*.*");
	if(dlg.DoModal()==IDOK)
		{
			//��ô��ϴ��ñ��ػ��ļ���·��������
		    strSourceName = dlg.GetPathName();
			strDestName = dlg.GetFileName();
			//���ú����ϴ��ļ�
			if(pConnection->PutFile(strSourceName,strDestName))
			{
                
				AfxMessageBox("�ϴ��ɹ�! ",MB_OK|MB_ICONINFORMATION);
				while(m_ListFile.GetCount()!=0)
					m_ListFile.DeleteString(0);
				Find();
			}

			else
				AfxMessageBox("�ϴ�ʧ��! ",MB_OK|MB_ICONSTOP);
		}
	else
		{
			//�ļ�ѡ�����
			AfxMessageBox("��ѡ���ļ�! ",MB_OK|MB_ICONSTOP);
		}

	//��������������ı��ͱ༭��ؼ�
    m_EditFtp.EnableWindow(TRUE);
	m_EditName.EnableWindow(TRUE);
	m_EditPwd.EnableWindow(TRUE);
	m_StaFtp.EnableWindow(TRUE);
	m_StaName.EnableWindow(TRUE);
	m_StaPwd.EnableWindow(TRUE);
    //�����ѯ��ť
	m_BtnConnect.EnableWindow(TRUE);	
}

BOOL CFtpDlg::Find()
{
	CString strFileName;
	BOOL bContinue;
	if (pFileFind!=NULL)
	{
		//����CFtpFileFind����
		//����CFtpConnection�����ָ��
		//pFileFind=new CFtpFileFind(pConnection);
	
		//���������ļ�
		bContinue=pFileFind->FindFile("*");
		while (bContinue)
		{
			//������һ���ļ�
			bContinue=pFileFind->FindNextFile();
			//����ҵ����ļ����ļ���
			strFileName=pFileFind->GetFileName();

			if (pFileFind->IsDirectory())
			{
				//�ҵ����Ƿ�Ŀ¼
				//���Ŀ¼��
				strFileName="["+strFileName;
				strFileName+="]";
			}
			//��ʾ���ҵ�����
			m_ListFile.AddString(strFileName);
		}
		return TRUE;
	}
	
	else
		 return FALSE;
		 
}

void CFtpDlg::OnDblclkListFile() 
{
    UpdateData(TRUE);
	int nSel = m_ListFile.GetCurSel();
	CString strSourceName;

	//����û����б���е�ѡ��
	m_ListFile.GetText(nSel,strSourceName);
	if(strSourceName.GetAt(0)=='[')
	{
		//ѡ�����Ŀ¼
		strSourceName.Delete(0,1);
		strSourceName.Delete(strSourceName.GetLength()-1,1);
		if(pConnection->SetCurrentDirectory(strSourceName))
		{
			while(m_ListFile.GetCount()!=0)
			m_ListFile.DeleteString(0);
			Find();
		}
	}
	//AfxMessageBox(strSourceName);

	
}
