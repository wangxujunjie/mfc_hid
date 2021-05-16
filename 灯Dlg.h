// 灯Dlg.h : header file
//
#include "hhh.h"

#if !defined(AFX_DLG_H__F4802002_932E_4E8C_8012_17B2B8DB457C__INCLUDED_)
#define AFX_DLG_H__F4802002_932E_4E8C_8012_17B2B8DB457C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CButton	m_waikaiguan;
	CButton	m_zhongkaiguan;
	CButton	m_neikaiguan;
	CButton	m_zongkaiguan;
	CSpinButtonCtrl	m_jiaospin2;
	CSpinButtonCtrl	m_jiaospin1;
	CSpinButtonCtrl	m_lightspin3;
	CSpinButtonCtrl	m_lightspin2;
	CSliderCtrl	m_lightslider3;
	CSliderCtrl	m_lightslider2;
	CSpinButtonCtrl	m_lightspin1;
	CSliderCtrl	m_lightslider1;
	int		m_lightvalue;
	int		m_lightvalue3;
	int		m_lightvalue2;
	int		m_lightjiao1;
	int		m_lightjiao2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	int m_lightjiaorun;
	void Setlightzero();
	int ScrollType;   //鼠标滚轮操作的是1:环面光,2:白光,3:绿光
	void SetLightValue(int channel);
	void StatusInit();
       hhh m_h;
// Implementation
protected:
	HANDLE userHidFileHandle;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onlightkaiguan();
	afx_msg void Onlightbegin();
	afx_msg void Onlightmiddle();
	afx_msg void Onlightend();
	afx_msg void OnLightSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLightSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLightSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLightSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLightSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLightSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnJiaoSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnJiaoSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__F4802002_932E_4E8C_8012_17B2B8DB457C__INCLUDED_)
