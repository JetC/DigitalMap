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
   
	int m_ObjectID;  //目标id
	BOOL m_bBlink;  //闪烁显示标志


	CString m_ObjectName;  //目标名称
public:
	virtual void Draw(CDC *pDC)=0;



	void SetObjectID(int id_only); //设置目标ID  
	int GetObjectID(); //得到目标ID
	
    void SetObjectName(CString ObjectName);//设置目标名称
    CString GetObjectName();//得到目标名称

	virtual double GetDistance(CPoint MousePoint)=0; //计算目标和鼠标点的距离
    virtual CRect GetMaxRect()=0; //得到目标最小外界矩形
    virtual void SetHotPot(BOOL IsBlink)  //设置闪烁
	{
		m_bBlink=IsBlink;
	}


};

#endif // !defined(AFX_GEOOBJECT_H__D4A3B4F2_4288_4B4F_B255_E256E53B8984__INCLUDED_)
