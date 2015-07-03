// GeoObject.cpp: implementation of the CGeoObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapManager.h"
#include "GeoObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoObject::CGeoObject()
{
	m_ObjectID=-1;
	m_ObjectName="";
	m_bBlink=false;

}

CGeoObject::~CGeoObject()
{

}
void CGeoObject::SetObjectID(int id_only)
{
	m_ObjectID=id_only;
}

int CGeoObject::GetObjectID()
{
	return m_ObjectID;
}
void CGeoObject::SetObjectName(CString ObjectName)
{
	m_ObjectName=ObjectName;
}
CString CGeoObject::GetObjectName()
{
	return m_ObjectName;
}
