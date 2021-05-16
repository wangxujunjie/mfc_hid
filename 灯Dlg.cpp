// 灯Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "hhh.h"
#include "灯.h"
#include "灯Dlg.h"
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
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_lightvalue = 0;
	m_lightvalue3 = 0;
	m_lightvalue2 = 0;
	m_lightjiao1 = 0;
	m_lightjiao2 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_BUTTON6, m_waikaiguan);
	DDX_Control(pDX, IDC_BUTTON5, m_zhongkaiguan);
	DDX_Control(pDX, IDC_BUTTON4, m_neikaiguan);
	DDX_Control(pDX, IDC_BUTTON3, m_zongkaiguan);
	DDX_Control(pDX, IDC_SPIN5, m_jiaospin2);
	DDX_Control(pDX, IDC_SPIN4, m_jiaospin1);
	DDX_Control(pDX, IDC_SPIN3, m_lightspin3);
	DDX_Control(pDX, IDC_SPIN2, m_lightspin2);
	DDX_Control(pDX, IDC_SLIDER3, m_lightslider3);
	DDX_Control(pDX, IDC_SLIDER2, m_lightslider2);
	DDX_Control(pDX, IDC_SPIN1, m_lightspin1);
	DDX_Control(pDX, IDC_SLIDER1, m_lightslider1);
	DDX_Text(pDX, IDC_EDIT_LIGHT, m_lightvalue);
	DDX_Text(pDX, IDC_EDIT_LIGHT3, m_lightvalue3);
	DDX_Text(pDX, IDC_EDIT_LIGHT2, m_lightvalue2);
	DDX_Text(pDX, IDC_EDIT_JIAO1, m_lightjiao1);
	DDX_Text(pDX, IDC_EDIT_JIAO2, m_lightjiao2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, Onlightkaiguan)
	ON_BN_CLICKED(IDC_BUTTON4, Onlightbegin)
	ON_BN_CLICKED(IDC_BUTTON5, Onlightmiddle)
	ON_BN_CLICKED(IDC_BUTTON6, Onlightend)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnLightSlider1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnLightSpin1)
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnLightSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnLightSpin3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnLightSlider2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER3, OnLightSlider3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnJiaoSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnJiaoSpin2)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    

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
	StatusInit();
	//开始按钮状态
    m_h.m_lightrun=false;
	m_h.m_lightjiaorun=false;
    m_h.m_lightrunnei=false;
    m_h.m_lightrunzhong=false;
    m_h.m_lightrunwai=false;
	m_h.writebuf[0] = 0;
	m_h.writebuf[62] = 0;
	m_h.writebuf[63] = 0;
	m_h.writebuf[64] = 0;
	//m_zongkaiguan.SetBitmaps(IDB_LIGHTOFF,RGB(0,0,0));
	//m_neikaiguan.SetBitmaps(IDB_LIGHTOFF,RGB(0,0,0)); 
	//m_zhongkaiguan.SetBitmaps(IDB_LIGHTOFF,RGB(0,0,0)); 
	//m_waikaiguan.SetBitmaps(IDB_LIGHTOFF,RGB(0,0,0)); 
    uint8_t n = 5;
			while (n--) {
				m_h.writebuf[1] = n;
				for (uint8_t i = 2; i < 62; i++)
					m_h.writebuf[i] = 0;
			}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDlg::OnPaint() 
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
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMyDlg::Onlightkaiguan() 
{
   CString str;
   GetDlgItemText(IDC_BUTTON3,str);
   if(str=="开灯"){
	m_h.zongkaiguan();
	if(m_h.m_lightrun){
	m_lightvalue=510;
	m_lightvalue2=510;
	m_lightvalue3=510;
	m_lightslider1.SetPos(510);
	m_lightslider2.SetPos(510);
	m_lightslider3.SetPos(510);
    UpdateData(FALSE);
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("关灯"));
	GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("关内环灯"));
	GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("关中环灯"));
	GetDlgItem(IDC_BUTTON6)->SetWindowText(_T("关外环灯"));}
   }
   else if(str=="关灯"){
	 m_h.zongkaiguan();
	 if(!m_h.m_lightrun){
	m_lightvalue=0;
	m_lightvalue2=0;
	m_lightvalue3=0;
	m_lightslider1.SetPos(0);
	m_lightslider2.SetPos(0);
	m_lightslider3.SetPos(0);
    UpdateData(FALSE);
	 GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯"));
	 GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("开内环灯"));
	 GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("开中环灯"));
	 GetDlgItem(IDC_BUTTON6)->SetWindowText(_T("开外环灯"));
	 }
   }

	
}

void CMyDlg::Onlightbegin() 
{
	// TODO: Add your control notification handler code here
	CString str;
   GetDlgItemText(IDC_BUTTON4,str);
   if(str=="开内环灯"){
	m_h.neikaiguan();
	if(m_h.m_lightrunnei){
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("关灯"));
	GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("关内环灯"));
	     m_lightvalue=510;
	     m_lightvalue2=510;
	     m_lightvalue3=510;
	     m_lightslider1.SetPos(510);
	     m_lightslider2.SetPos(510);
	     m_lightslider3.SetPos(510);
		 UpdateData(FALSE);
	}
   }
   else if(str=="关内环灯"){
	 m_h.neikaiguan();
	 GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("开内环灯"));
	 if(!m_h.m_lightrun){
         m_lightvalue=0;
	     m_lightvalue2=0;
	     m_lightvalue3=0;
	     m_lightslider1.SetPos(0);
	     m_lightslider2.SetPos(0);
	     m_lightslider3.SetPos(0);
		 UpdateData(FALSE);
		 GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯"));
	 }
   }
}

void CMyDlg::Onlightmiddle() 
{
	// TODO: Add your control notification handler code here
	CString str;
   GetDlgItemText(IDC_BUTTON5,str);
   if(str=="开中环灯"){
	m_h.zhongkaiguan();
	if(m_h.m_lightrunzhong){
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("关灯"));
	GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("关中环灯"));
	m_lightvalue=510;
	     m_lightvalue2=510;
	     m_lightvalue3=510;
	     m_lightslider1.SetPos(510);
	     m_lightslider2.SetPos(510);
	     m_lightslider3.SetPos(510);
		 UpdateData(FALSE);
	}
   }
   else if(str=="关中环灯"){
	 m_h.zhongkaiguan();
	 GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("开中环灯"));
	 if(!m_h.m_lightrun){		
	 GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯")); 
	     m_lightvalue=0;
	     m_lightvalue2=0;
	     m_lightvalue3=0;
	     m_lightslider1.SetPos(0);
	     m_lightslider2.SetPos(0);
	     m_lightslider3.SetPos(0);
		 UpdateData(FALSE);
	 }
   }
}

 void CMyDlg::Onlightend() 
 {
 	// TODO: Add your control notification handler code here
   CString str;
   GetDlgItemText(IDC_BUTTON6,str);
   if(str=="开外环灯"){
	m_h.waikaiguan();
	if(m_h.m_lightrunwai){
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("关灯"));
	GetDlgItem(IDC_BUTTON6)->SetWindowText(_T("关外环灯"));
	m_lightvalue=510;
	     m_lightvalue2=510;
	     m_lightvalue3=510;
	     m_lightslider1.SetPos(510);
	     m_lightslider2.SetPos(510);
	     m_lightslider3.SetPos(510);
		 UpdateData(FALSE);
	}
   }
   else if(str=="关外环灯"){
	 m_h.waikaiguan();
	 GetDlgItem(IDC_BUTTON6)->SetWindowText(_T("开外环灯"));
	 if(!m_h.m_lightrun){
	 GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯"));
         m_lightvalue=0;
	     m_lightvalue2=0;
	     m_lightvalue3=0;
	     m_lightslider1.SetPos(0);
	     m_lightslider2.SetPos(0);
	     m_lightslider3.SetPos(0);
		 UpdateData(FALSE);
	 }
   }
 }

void CMyDlg::StatusInit()
{
   //控件初始化
	m_lightspin1.SetRange(0,510);
    m_lightspin1.SetBuddy((CWnd*)GetDlgItem(IDC_EDIT_LIGHT));
	m_lightspin1.SetPos(0);
	m_lightslider1.SetRange(0,510);
	m_lightslider1.SetPos(0);
	m_lightslider1.SetLineSize(1);
	
    m_lightspin2.SetRange(0,510);
    m_lightspin2.SetBuddy((CWnd*)GetDlgItem(IDC_EDIT_LIGHT2));
	m_lightspin2.SetPos(0);
	m_lightslider2.SetRange(0,510);
	m_lightslider2.SetPos(0);
	m_lightslider2.SetLineSize(1);

	m_lightspin3.SetRange(0,510);
    m_lightspin3.SetBuddy((CWnd*)GetDlgItem(IDC_EDIT_LIGHT3));
	m_lightspin3.SetPos(0);
	m_lightslider3.SetRange(0,510);
	m_lightslider3.SetPos(0);
	m_lightslider3.SetLineSize(1);
    
    m_jiaospin1.SetRange(0,360);
    m_jiaospin1.SetBuddy((CWnd*)GetDlgItem(IDC_EDIT_JIAO1));
	m_jiaospin1.SetPos(0);

	m_jiaospin2.SetRange(0,360);
    m_jiaospin2.SetBuddy((CWnd*)GetDlgItem(IDC_EDIT_JIAO2));
	m_jiaospin2.SetPos(0);
    

	m_lightvalue=0;
	m_lightvalue2=0;
	m_lightvalue3=0;
	m_lightjiao1=0;
	m_lightjiao2=0;
}

void CMyDlg::OnLightSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ScrollType=1;
	*pResult = 0;
}

void CMyDlg::OnLightSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ScrollType=2;
	*pResult = 0;
}

void CMyDlg::OnLightSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ScrollType=3;
	*pResult = 0;
}


void CMyDlg::OnLightSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;	

	UpdateData();
	int max,min;
	m_lightslider1.GetRange(min,max);
	if(pNMUpDown->iDelta ==1)		 //点击往上按钮
	{
		if(m_lightvalue>=max)
			return;
		m_lightvalue++;
	       
    }	
    else if(pNMUpDown->iDelta== - 1) //点击往下按钮
	{
		if(m_lightvalue<=min)
			return;
		m_lightvalue--;
    }
	SetLightValue(1);
	m_lightslider1.SetPos(m_lightvalue);
	m_lightslider2.SetPos(m_lightvalue);
	m_lightslider3.SetPos(m_lightvalue);
    m_lightvalue2=m_lightvalue;
	m_lightvalue3=m_lightvalue;

	UpdateData(FALSE);
    m_h.updatalight(m_lightvalue,1);
	*pResult = 0;
}

void CMyDlg::OnLightSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;	

	UpdateData();
	int max,min;
	m_lightslider2.GetRange(min,max);
	if(pNMUpDown->iDelta ==1)		 //点击往上按钮
	{
		if(m_lightvalue2>=max)
			return;
		m_lightvalue2++;
	      
    }	
    else if(pNMUpDown->iDelta== - 1) //点击往下按钮
	{
		if(m_lightvalue2<=min)
			return;
		m_lightvalue2--;
    }
	SetLightValue(2);
	m_lightslider2.SetPos(m_lightvalue2);

	UpdateData(FALSE);

    m_h.updatalight(m_lightvalue2,2);
	*pResult = 0;
}

void CMyDlg::OnLightSpin3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;	

	UpdateData();
	int max,min;
	m_lightslider3.GetRange(min,max);
	if(pNMUpDown->iDelta ==1)		 //点击往上按钮
	{
		if(m_lightvalue3>=max)
			return;
		m_lightvalue3++;
	
        
    }	
    else if(pNMUpDown->iDelta== - 1) //点击往下按钮
	{
		if(m_lightvalue3<=min)
			return;
		m_lightvalue3--;
    }
	SetLightValue(3);
	m_lightslider3.SetPos(m_lightvalue3);

	UpdateData(FALSE);
    m_h.updatalight(m_lightvalue3,3);
	
	*pResult = 0;
}

void CMyDlg::SetLightValue(int channel)
{
   
	if(m_h.find_device()==FALSE)
		return;
	int value;
	if(channel==1)		//环面光
		value = m_lightvalue;
	if(channel==2)		//白光
		value = m_lightvalue2;
	if(channel==3)		//绿光
		value = m_lightvalue3;
}

void CMyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateData();
	int type;
	if( pScrollBar== GetDlgItem(IDC_SLIDER1) )
	{
		type=1;
		m_lightvalue=m_lightslider1.GetPos();
		m_lightspin1.SetPos(m_lightvalue);

 	    m_lightslider2.SetPos(m_lightvalue);
	    m_lightslider3.SetPos(m_lightvalue);
        m_lightvalue2=m_lightvalue;
	    m_lightvalue3=m_lightvalue;

		SetLightValue(1);
	}
	else if( pScrollBar== GetDlgItem(IDC_SLIDER2) )
	{
		type=2;
		m_lightvalue2=m_lightslider2.GetPos();
		m_lightspin2.SetPos(m_lightvalue2);
		SetLightValue(2);
	}
	else if( pScrollBar== GetDlgItem(IDC_SLIDER3) )
	{
		type=3;
		m_lightvalue3=m_lightslider3.GetPos();
		m_lightspin3.SetPos(m_lightvalue3);
		SetLightValue(3);
	}
	UpdateData(FALSE);

	if(!m_lightvalue)
		Setlightzero();
	
	if(type==1)
	    m_h.updatalight(m_lightvalue,type);
	else if(type==2)
		m_h.updatalight(m_lightvalue2,type);
	else if(type==3)
		m_h.updatalight(m_lightvalue3,type);
	//if(m_h.m_lightjiaorun)
		//m_h.updatejiaodu(m_lightjiao1,m_lightjiao2,m_lightvalue);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMyDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_MOUSEWHEEL)
	{
		if(ScrollType==1)		m_lightslider1.SetFocus();
		else if(ScrollType==2)	m_lightslider2.SetFocus();
		else if(ScrollType==3)	m_lightslider3.SetFocus();
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMyDlg::Setlightzero()
{
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯"));
    GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("开内环灯"));
    GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("开中环灯"));
	GetDlgItem(IDC_BUTTON6)->SetWindowText(_T("开外环灯"));
	m_h.m_lightrun=false;
	m_h.m_lightrunnei=false;
	m_h.m_lightrunzhong=false;
	m_h.m_lightrunwai=false;
}


void CMyDlg::OnJiaoSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;	

	UpdateData();
	int max,min;
	min=0,max=360;
	//m_lightslider2.GetRange(min,max);
	if(pNMUpDown->iDelta ==1)		 //点击往上按钮
	{
		if(m_lightjiao1>=max)
			return;
		m_lightjiao1+=9;
	      
    }	
    else if(pNMUpDown->iDelta== - 1) //点击往下按钮
	{
		if(m_lightjiao1<=min)
			return;
		m_lightjiao1-=9;
    }
	//SetLightValue(2);
	//m_lightslider2.SetPos(m_lightvalue2);

	UpdateData(FALSE);

    m_h.updatejiaodu(m_lightjiao1,m_lightjiao2,m_lightvalue);
	if(m_lightjiao1!=m_lightjiao2){
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("关灯"));
	m_lightvalue=m_lightvalue;
	m_lightvalue2=m_lightvalue;
	m_lightvalue3=m_lightvalue;
	m_lightslider1.SetPos(m_lightvalue);
	m_lightslider2.SetPos(m_lightvalue);
	m_lightslider3.SetPos(m_lightvalue);
    UpdateData(FALSE);
	}
	else{
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯"));
	m_lightvalue=0;
	m_lightvalue2=0;
	m_lightvalue3=0;
	m_lightslider1.SetPos(0);
	m_lightslider2.SetPos(0);
	m_lightslider3.SetPos(0);
    UpdateData(FALSE);
	}
	*pResult = 0;
}

void CMyDlg::OnJiaoSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;	

	UpdateData();
	int max,min;
	//m_lightslider2.GetRange(min,max);
	min=0,max=360;
	if(pNMUpDown->iDelta ==1)		 //点击往上按钮
	{
		if(m_lightjiao2>=max)
			return;
		m_lightjiao2+=9;
	      
    }	
    else if(pNMUpDown->iDelta== - 1) //点击往下按钮
	{
		if(m_lightjiao2<=min)
			return;
		m_lightjiao2-=9;
    }
	//SetLightValue(2);
	//m_lightslider2.SetPos(m_lightvalue2);

	UpdateData(FALSE);

    m_h.updatejiaodu(m_lightjiao1,m_lightjiao2,m_lightvalue);
	if(m_lightjiao1!=m_lightjiao2){
		GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("关灯"));
		m_lightvalue=m_lightvalue;
	m_lightvalue2=m_lightvalue;
	m_lightvalue3=m_lightvalue;
	m_lightslider1.SetPos(m_lightvalue);
	m_lightslider2.SetPos(m_lightvalue);
	m_lightslider3.SetPos(m_lightvalue);
    UpdateData(FALSE);
	}
	else{
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("开灯"));
	m_lightvalue=0;
	m_lightvalue2=0;
	m_lightvalue3=0;
	m_lightslider1.SetPos(0);
	m_lightslider2.SetPos(0);
	m_lightslider3.SetPos(0);
    UpdateData(FALSE);
	}
	*pResult = 0;
}

void CMyDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	m_h.guandeng();
		
}
