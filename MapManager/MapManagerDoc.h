// MapManagerDoc.h : interface of the CMapManagerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MapManagerDOC_H__A375EB11_3FDC_411E_879C_674E0A7D9F0D__INCLUDED_)
#define AFX_MapManagerDOC_H__A375EB11_3FDC_411E_879C_674E0A7D9F0D__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeoMap.h"
//#include "PointInfo.h"

class CMapManagerDoc : public CDocument
{
protected: // create from serialization only
	CMapManagerDoc();
	DECLARE_DYNCREATE(CMapManagerDoc)

// Attributes
public:
//	CPointInfo *PointInfoSet;
	CGeoMap *map1;
	SIZE m_MapSize;
	int m_WindowOrgX;
	int m_WindowOrgY;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReadManagerData(CString FileName);
	void BmpSave(CString FileName);
	void ChangeDxfToManager(CString s_FileName,CString o_FileName);
	void WriteManagerData(CString FileName);
	void WriteTree();
	virtual ~CMapManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CString m_strFullPath;//读入文件名
	CString fileName;
	boolean isOpenDxf;
	boolean isOpenManager;
	CString m_strSouceFile;
	CString m_strOutFile;
	CString m_strBmpPath; //位图存放路径
	//{{AFX_MSG(CMapManagerDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnChangeformat();
	afx_msg void OnLayerselect();
	afx_msg void OnBmpsave();
	afx_msg void OnFilesave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MapManagerDOC_H__A375EB11_3FDC_411E_879C_674E0A7D9F0D__INCLUDED_)
