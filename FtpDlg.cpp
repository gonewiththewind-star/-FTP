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

	//域名初始化
	m_strFtpSite=_T("58.192.112.20");
	//登陆名初始化
	m_strName=_T("anonymous");
	//口令初始化
	m_strPwd=_T("");
	//更新界面
	UpdateData(FALSE);
   	//禁用下载和上传按钮
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

	//获得当前输入
	UpdateData(TRUE);
	//判断ftp地址栏是否为空
	if(m_strFtpSite.IsEmpty())
	{
		MessageBox("请输入ftp服务器地址！ ");		
		return;
	}           
	//清除列表框内容
	while(m_ListFile.GetCount()!=0)
			m_ListFile.DeleteString(0);

	//TRACE("strConnect:%s",strConnect);
	//AfxMessageBox(strConnect);

	if(strConnect=="连接")
	{
	
	
		//创建Internet会话
	    pSession=new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
		try
		{
			//试图建立FTP连接
		    pConnection=pSession->GetFtpConnection(m_strFtpSite,m_strName,m_strPwd);
		}
		catch (CInternetException* e)
		{
			//错误处理
			e->Delete();
			pConnection=NULL;
			AfxMessageBox("连接错误，请检查地址和用户名密码");
			return;
		}
		if (pConnection!=NULL)
		{
			//创建CFtpFileFind对象
			//传递CFtpConnection对象的指针
			pFileFind=new CFtpFileFind(pConnection);
		m_BtnUpLoad.EnableWindow(TRUE);
		}
		if(Find())
		{
			m_BtnConnect.SetWindowText("断开连接");
			if(m_strName=="")
			{
				m_strName=_T("anonymous");
				m_strPwd=_T("anonymous");
				UpdateData(FALSE);
			}

		}

		else
			AfxMessageBox("不能正确初始化！");
   

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
	
		m_BtnConnect.SetWindowText("连接");
		m_cancel.EnableWindow(TRUE);
		m_BtnUpLoad.EnableWindow(FALSE);
		   //激活用来输入的文本和编辑框控件
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

	//获得当前输入
	UpdateData(TRUE);
	if(strConnect=="断开连接")
     CFtpDlg::OnConnect();
	CDialog::OnCancel();
}

void CFtpDlg::OnSelchangeListFile() 
{
	//获得当前输入
	UpdateData(TRUE);
	int nSel = m_ListFile.GetCurSel();
	CString strSourceName;
	//获得用户在列表框中的选择
	m_ListFile.GetText(nSel,strSourceName);
	if(strSourceName.GetAt(0)!='[')
	{
		//禁止用来输入的文本和编辑框控件
	    m_EditFtp.EnableWindow(FALSE);
	    m_EditName.EnableWindow(FALSE);
	    m_EditPwd.EnableWindow(FALSE);
	    m_StaFtp.EnableWindow(FALSE);
	    m_StaName.EnableWindow(FALSE);
	    m_StaPwd.EnableWindow(FALSE);
	    //禁用查询和上传按钮

	    //激活下载按钮
	    m_BtnDownLoad.EnableWindow(TRUE);
		return;
	}
	else
	{
		//禁用下载按钮
	    m_BtnDownLoad.EnableWindow(FALSE);
	    //激活查询和上传按钮
	    //m_BtnUpLoad.EnableWindow(TRUE);
	    m_BtnConnect.EnableWindow(TRUE);
	    //激活用来输入的文本和编辑框控件
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
	//获得当前输入
	UpdateData(TRUE);
	int nSel = m_ListFile.GetCurSel();
	CString strSourceName;
	
	//获得用户在列表框中的选择
	m_ListFile.GetText(nSel,strSourceName);
	if(strSourceName.GetAt(0)!='[')
	{
		//选择的是文件
        CString strDestName;
		CFileDialog dlg(FALSE,"",strSourceName);
		if(dlg.DoModal()==IDOK)
		{
			//获得下载文件在本地机上存储的路径和名称
			strDestName = dlg.GetPathName();
			//下载文件
			if(pConnection->GetFile(strSourceName,strDestName))
			{
				AfxMessageBox("下载成功! ",MB_OK|MB_ICONINFORMATION);
				//禁用下载按钮
				m_BtnDownLoad.EnableWindow(FALSE);

			}
				
			else
				AfxMessageBox("下载失败! ",MB_OK|MB_ICONSTOP);
		}
		else
		{	
			if(strSourceName=="")
				AfxMessageBox("请写入文件名! ",MB_OK|MB_ICONSTOP);
			
		}
	}
	else
	{
		//选择的是目录
        AfxMessageBox("不能下载目录! ",MB_OK|MB_ICONSTOP);
	}

	//激活查询和上传按钮
	m_BtnUpLoad.EnableWindow(TRUE);
	//m_BtnQuery.EnableWindow(TRUE);
	//激活用来输入的文本和编辑框控件
    m_EditFtp.EnableWindow(TRUE);
	m_EditName.EnableWindow(TRUE);
	m_EditPwd.EnableWindow(TRUE);
	m_StaFtp.EnableWindow(TRUE);
	m_StaName.EnableWindow(TRUE);
	m_StaPwd.EnableWindow(TRUE);		
}

void CFtpDlg::OnUpload() 
{
	//获得当前输入
	UpdateData(TRUE);
	//禁止用来输入的文本和编辑框控件
	m_EditFtp.EnableWindow(FALSE);
	m_EditName.EnableWindow(FALSE);
	m_EditPwd.EnableWindow(FALSE);
	m_StaFtp.EnableWindow(FALSE);
	m_StaName.EnableWindow(FALSE);
	m_StaPwd.EnableWindow(FALSE);
	//禁止查询按钮
	m_BtnConnect.EnableWindow(FALSE);
	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,"","*.*");
	if(dlg.DoModal()==IDOK)
		{
			//获得待上传得本地机文件的路径和名称
		    strSourceName = dlg.GetPathName();
			strDestName = dlg.GetFileName();
			//调用函数上传文件
			if(pConnection->PutFile(strSourceName,strDestName))
			{
                
				AfxMessageBox("上传成功! ",MB_OK|MB_ICONINFORMATION);
				while(m_ListFile.GetCount()!=0)
					m_ListFile.DeleteString(0);
				Find();
			}

			else
				AfxMessageBox("上传失败! ",MB_OK|MB_ICONSTOP);
		}
	else
		{
			//文件选择错误
			AfxMessageBox("请选择文件! ",MB_OK|MB_ICONSTOP);
		}

	//激活用来输入的文本和编辑框控件
    m_EditFtp.EnableWindow(TRUE);
	m_EditName.EnableWindow(TRUE);
	m_EditPwd.EnableWindow(TRUE);
	m_StaFtp.EnableWindow(TRUE);
	m_StaName.EnableWindow(TRUE);
	m_StaPwd.EnableWindow(TRUE);
    //激活查询按钮
	m_BtnConnect.EnableWindow(TRUE);	
}

BOOL CFtpDlg::Find()
{
	CString strFileName;
	BOOL bContinue;
	if (pFileFind!=NULL)
	{
		//创建CFtpFileFind对象
		//传递CFtpConnection对象的指针
		//pFileFind=new CFtpFileFind(pConnection);
	
		//查找任意文件
		bContinue=pFileFind->FindFile("*");
		while (bContinue)
		{
			//查找下一个文件
			bContinue=pFileFind->FindNextFile();
			//获得找到的文件的文件名
			strFileName=pFileFind->GetFileName();

			if (pFileFind->IsDirectory())
			{
				//找到的是否目录
				//标记目录名
				strFileName="["+strFileName;
				strFileName+="]";
			}
			//显示查找的内容
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

	//获得用户在列表框中的选择
	m_ListFile.GetText(nSel,strSourceName);
	if(strSourceName.GetAt(0)=='[')
	{
		//选择的是目录
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
