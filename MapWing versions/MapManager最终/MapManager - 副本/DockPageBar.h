/////////////////////////////////////////////////////////////////////////
// CDockPageBar

#if !defined(AFX_DOCKPAGEBAR_H__5125E626_E472_4F93_AC8E_20F121A6D1B9__INCLUDED_)
#define AFX_DOCKPAGEBAR_H__5125E626_E472_4F93_AC8E_20F121A6D1B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sizecbar.h"

// DockPageBar.h : header file
//
#define HTSTUD				22
#define HTHIDE				23
///////////////////////////////////////////////////////////////////////////
//  ��������ť
class CMyButton
{
public:
    CMyButton();

    void Move(CPoint ptTo) {ptOrg = ptTo; };
    virtual CRect GetRect() { return CRect(ptOrg, CSize(13, 13)); };
    virtual void Paint(CDC* pDC, BOOL isActive);

    BOOL    bPushed;
    BOOL    bRaised;

protected:
    CPoint  ptOrg;
};
//�رհ�ť
class CCloseButton : public CMyButton
{
public:
	virtual void Paint(CDC* pDC, BOOL isActive);
};
//ͼ����ť
class CStudButton : public CMyButton
{
public:
	CStudButton();
	BOOL	bFloat;
	virtual void Paint(CDC* pDC, BOOL isActive);
};

///////////////////////////////////////////////////////////////////////////
//  ��ǩҳ
class CPageItem
{
public:
	CWnd*		m_pWnd;			//����,����ΪNULL
	CString		m_sText;		//����
	HICON		m_hIcon;		//ͼ��
	UINT		m_TabWidth;		//��ǩ���
	CRect		m_rect;			//��ǩλ��
	CPageItem() { m_pWnd = NULL; }
public:
	void Draw(CDC *pDC,BOOL bActive);
};

/////////////////////////////////////////////////////////////////////////////
// CDockPageBar control bar

#ifndef baseCDockPageBar
#define baseCDockPageBar CSizingControlBar
#endif

class CDockPageBar : public baseCDockPageBar
{
	DECLARE_DYNAMIC(CDockPageBar);
// Construction
public:
	CDockPageBar();

// Attributes
public:
	int m_cyGripper;
// Operations
public:
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockPageBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnStudClick();
	void EnableDocking(DWORD dwDockStyle);
	CPageItem* DeletePage();
	BOOL AddPage(CDockPageBar* dockPageBar);
	BOOL AddPage(CPageItem *pPageItem);
	BOOL AddPage(CWnd *pWnd, LPCTSTR sText, UINT IconID);

	virtual BOOL HasGripper() const;
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual ~CDockPageBar();

	CPtrList		m_PageList;
	CPtrList		m_pDPBContext;	//hengai
	int				m_nActivePage;
	CPageItem*		GetPageItem(int nIndex);
	virtual void UpdateSize();
	// Generated message map functions
protected:
	void Move(CPoint pt);
	void CanDrag(CPoint pt);
	void StartDrag(CPoint pt);
	void UpdateWindow();
	
	void GetClientRect(LPRECT lpRect, BOOL isMulti);
	void SetActivePage(int nIndex);
	
	// implementation helpers
	virtual void NcCalcClient(LPRECT pRc, UINT nDockBarID);
	virtual void NcPaintGripper(CDC* pDC, CRect rcClient);

	
	CString			m_Title;
	BOOL			m_isActive;
	//{{AFX_MSG(CDockPageBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	CFont			m_font;

	CCloseButton	m_biHide;
	CStudButton		m_stud;
};

/////////////////////////////////////////////////////////////////////////////
// CDockPageBarContext dockcontext
#ifndef LAYOUT_LTR
#define LAYOUT_LTR			0x00000000
#endif

class CDockPageBarContext : public CDockContext
{
public:
	void FreeAll();
// Construction
	CDockPageBarContext(CControlBar* pBar) : CDockContext(pBar) {}
	~CDockPageBarContext(void);
	BOOL			m_isMe;
	BOOL			m_isPage;
	CDockPageBar*	m_pTgDockPage;

// Drag Operations
	virtual void StartDrag(CPoint pt);
	virtual BOOL Track();
	virtual void Move(CPoint pt);
	virtual void EndDrag();
	void DrawFocusRect(BOOL bRemoveRect = FALSE);
protected:
	CPtrList		m_pDPBar;	//hengai
	CDockPageBar* CreateNewBar();
	BOOL isDockPage(CPoint pt);
	CRect	m_addRect;
};

#endif // !defined(AFX_DOCKPAGEBAR_H__5125E626_E472_4F93_AC8E_20F121A6D1B9__INCLUDED_)
