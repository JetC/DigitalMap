// GeoObject.h: interface for the CGeoObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOOBJECT_H__D4A3B4F2_4288_4B4F_B255_E256E53B8984__INCLUDED_)
#define AFX_GEOOBJECT_H__D4A3B4F2_4288_4B4F_B255_E256E53B8984__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeoObject  
{
public:
   	CGeoObject();
	virtual ~CGeoObject();
protected:
   
	int m_ObjectID;  //Ŀ��id
	BOOL m_bBlink;  //��˸��ʾ��־


	CString m_ObjectName;  //Ŀ������
public:
	virtual void Draw(CDC *pDC)=0;



	void SetObjectID(int id_only); //����Ŀ��ID  
	int GetObjectID(); //�õ�Ŀ��ID
	
    void SetObjectName(CString ObjectName);//����Ŀ������
    CString GetObjectName();//�õ�Ŀ������

	virtual double GetDistance(CPoint MousePoint)=0; //����Ŀ�������ľ���
    virtual CRect GetMaxRect()=0; //�õ�Ŀ����С������
    virtual void SetHotPot(BOOL IsBlink)  //������˸
	{
		m_bBlink=IsBlink;
	}


};

#endif // !defined(AFX_GEOOBJECT_H__D4A3B4F2_4288_4B4F_B255_E256E53B8984__INCLUDED_)
