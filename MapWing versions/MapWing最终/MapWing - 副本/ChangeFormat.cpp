// ChangeFormat.cpp : implementation file
//

#include "stdafx.h"
#include "MapWing.h"
#include "ChangeFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeFormat dialog


CChangeFormat::CChangeFormat(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeFormat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeFormat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChangeFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,  IDC_EDIT1, m_Edit1);
    DDX_Control(pDX,  IDC_EDIT2, m_Edit2);
	//{{AFX_DATA_MAP(CChangeFormat)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeFormat, CDialog)
	//{{AFX_MSG_MAP(CChangeFormat)
	ON_BN_CLICKED(IDC_SOURCE, OnSource)
	ON_BN_CLICKED(IDC_GOAL, OnGoal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeFormat message handlers


void CChangeFormat::OnSource() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,"*.dxf",NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,
	"�����ļ�(*.dxf)|*.dxf|�����ļ�(*.*)|*.*||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		m_strSourcePath=dlg.GetPathName();
		strExt=dlg.GetFileExt();
		m_Edit1.SetWindowText(m_strSourcePath);		
	}
	
}

void CChangeFormat::OnGoal() 
{
	if (m_strSourcePath.IsEmpty())
	{
		AfxMessageBox("�������ת���ļ�λ�ã�");
		return;
	}
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE,"*.wing",NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,
		"�����ļ�(*.wing)|*.wing|�����ļ�(*.*)|*.*||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		m_strOutPath=dlg.GetPathName();
		m_Edit2.SetWindowText(m_strOutPath);
	}
}
void CChangeFormat::OnOK() 
{
	if (m_strSourcePath.IsEmpty())
	{
		AfxMessageBox("�������ת���ļ�λ�ã�");
		return;
	}
	else if(m_strOutPath.IsEmpty())
	{
		AfxMessageBox("������洢λ�ã�");
		return;
	}
	char buffer[100];
	int code;
	FILE *dxf;
	dxf=fopen(m_strSourcePath,"r");
	
	if (strExt.CompareNoCase("dxf")!=0)
	{
		AfxMessageBox("����ȷѡ��DXF�ļ���");
		return;
	}
	while(!feof(dxf))
	{
		fscanf(dxf,"%d",&code);
		fscanf(dxf,"%s",buffer);            

		if(code == 2 && strcmp(buffer,"HEADER")==0)
		{
			fscanf(dxf,"%d",&code);
			fscanf(dxf,"%s",buffer);
			if(strcmp(buffer,"$ACADVER")==0)
			{
				fscanf(dxf,"%d",&code);
				fscanf(dxf,"%s",buffer);
				if(strcmp(buffer,"AC1006")==0)
				{
					AfxMessageBox("��ʽ��ȷ����ʼת����");
					goto loop;
				}
			}
		}
	}
	AfxMessageBox("�Ǳ�׼R10�汾��������ѡ���ļ���");
	return;
	loop:
	m_Edit1.GetWindowText(buffer,100);
	m_strSourcePath.Format("%s",buffer);	
	m_Edit2.GetWindowText(buffer,100);
	m_strOutPath.Format("%s",buffer);
	
	CDialog::OnOK();
}