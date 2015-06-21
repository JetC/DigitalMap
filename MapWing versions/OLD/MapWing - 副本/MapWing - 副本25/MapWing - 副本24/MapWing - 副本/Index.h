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
	int *LayerID;  //�洢һ���ռ��������е�Ŀ����
	long *ObjectID;    //�洢һ���ռ��������е�Ŀ��id��
	CRect m_IndexRect;   //�������
	BOOL m_IsSelected;  //�Ƿ�ѡ��
	int m_RecordNum;     //�ø����еļ�¼��


public:
	void DrawRect(CDC *pDC);  //����һ������

};

#endif // !defined(AFX_INDEX_H__F454F9E8_2893_4B36_9EAE_AFCBC9953A35__INCLUDED_)
