// Index.h: interface for the CIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEX_H__F454F9E8_2893_4B36_9EAE_AFCBC9953A35__INCLUDED_)
#define AFX_INDEX_H__F454F9E8_2893_4B36_9EAE_AFCBC9953A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIndex  
{
public:
	CIndex();
	virtual ~CIndex();
public:
	int *LayerID;  //存储一个空间索引格中的目标层号
	long *ObjectID;    //存储一个空间索引格中的目标id号
	CRect m_IndexRect;   //网格矩形
	BOOL m_IsSelected;  //是否选中
	int m_RecordNum;     //该格网中的记录数


public:
	void DrawRect(CDC *pDC);  //画出一个网格

};

#endif // !defined(AFX_INDEX_H__F454F9E8_2893_4B36_9EAE_AFCBC9953A35__INCLUDED_)
