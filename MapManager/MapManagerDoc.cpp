// MapManagerDoc.cpp : implementation of the CMapManagerDoc class
//

#include "stdafx.h"
#include "MapManager.h"
#include "time.h"

#include "MapManagerView.h"
#include "MapManagerDoc.h"
#include "MainFrm.h"

#include "GeoPoint.h"
#include "GeoLine.h"
#include "GeoPolygon.h"
#include "GeoAnno.h"
#include "Grid.h"
#include "ChangeFormat.h"
#include "LayerChooseDlg.h"
#include "ViewBitmap.h"

#include "math.h"
#include <dos.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapManagerDoc

IMPLEMENT_DYNCREATE(CMapManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CMapManagerDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_CHANGEFORMAT, OnChangeformat)
	ON_COMMAND(ID_LAYERSELECT, OnLayerselect)
	ON_COMMAND(ID_BMPSAVE, OnBmpsave)
	ON_COMMAND(ID_FILESAVE, OnFilesave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapManagerDoc construction/destruction

CMapManagerDoc::CMapManagerDoc()
{
	// TODO: add one-time construction code here
	m_strFullPath="";
	map1=NULL;

}

CMapManagerDoc::~CMapManagerDoc()
{
}

BOOL CMapManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMapManagerDoc serialization

void CMapManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapManagerDoc diagnostics

#ifdef _DEBUG
void CMapManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapManagerDoc commands

void CMapManagerDoc::OnFileOpen() 
{
	CFileDialog dlg(TRUE,"*.Manager",NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,"数据文件(*.Manager)|*.Manager|任意文件(*.*)|*.*||",NULL);
	if(dlg.DoModal() == IDOK)
	{
	    if(NULL!=map1)
		{
			delete map1;
			map1=NULL;
		}
		map1=new CGeoMap;		

		m_strFullPath = dlg.GetPathName();//得到文件完整路径
		
        CRect mapRt(0,0,0,0);
		ReadManagerData(m_strFullPath);
        
		CMapManagerView * pView =(CMapManagerView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
		map1->GetMinRect(mapRt);  //得到地图外接矩形
        pView->m_CurWinScope=pView->m_rtMapRange=mapRt;
		pView->m_IsLoadMap = TRUE;
		
		((CMainFrame*)AfxGetMainWnd())->m_wndHawkeyeDlg.Invalidate();
		pView->Invalidate();
        WriteTree();

	}
}

void CMapManagerDoc::ReadManagerData(CString FileName)
{
	FILE *fp;
	if((fp=fopen(FileName,"r"))==NULL)
	{
		AfxMessageBox("Can't Open!");
        exit(0);
	}
	char buffer[80];
	fscanf(fp,"%s",&buffer);
	if(strcmp(buffer,"自定义Manager格式")!=0)
	{
         AfxMessageBox("文件格式不对");
         return;
	}

    long Xmin,Ymin,Xmax,Ymax;
	fscanf(fp,"%d,%d",&Xmin,&Ymin);
	fscanf(fp,"%d,%d",&Xmax,&Ymax); 
    map1->SetRect(Xmin,Ymin,Xmax,Ymax);  //设置map1的外接矩形
	int LayerNum;

	fscanf(fp,"%d",&LayerNum);
	map1->SetLayerNum(LayerNum);
	char LayerName[80];
	CGeoLayer *tempLayer=NULL;
    srand( time(0));  //随机值种子

	for(int j=0;j<LayerNum;j++)
	{  
	
		tempLayer=new CGeoLayer();
		tempLayer->SetLayerID(j);
	 
	    fscanf(fp,"%s",&LayerName);
		CString name;
		name.Format("%s",LayerName);
		tempLayer->SetLayerName(name);
		fscanf(fp,"%s",&buffer);


        CPoint *points;
	    long x,y;
        int ID;
		if(strcmp(buffer,"POINT")==0)
		{    
			  
			  int PointType;
			  long PointRadius,PointColor;
			  
			  fscanf(fp,"%d",&PointType);
			  fscanf(fp,"%d",&PointRadius);
	          fscanf(fp,"%d",&PointColor);

			  do
			  {
				  
				   fscanf(fp,"%s",buffer);
				   
                  if(strcmp(buffer,"ENDLAYER")!=0)
				   {
				
					   CString strName;
					   strName.Format("%s",buffer);
                       fscanf(fp,"%s",&buffer);
                        ID=atoi(buffer);
                       fscanf(fp,"%s",&buffer);
					   points=new CPoint[1];
                       fscanf(fp,"%d,%d",&x,&y);
			           points[0].x=x;
			           points[0].y=y;
	                   CGeoPoint *pGeoPoint=NULL;
		               pGeoPoint=new CGeoPoint();
					  
                       pGeoPoint->SetPoint(points[0].x,points[0].y);
					   pGeoPoint->SetObjectName(strName);
                       pGeoPoint->SetObjectID(ID);
				       tempLayer->AddObject(pGeoPoint);
	                   delete []points;
				       points=NULL;
				   }
			  }while(strcmp(buffer,"ENDLAYER")!=0);

              tempLayer->SetLayerType(1);
		      tempLayer->SetPointParameter(1,PointColor,PointRadius);
		}

		else if(strcmp(buffer,"LINE")==0)
		{
            
			int LineType;
			long LineColor,LineWidth;
     
			fscanf(fp,"%d",&LineType);
			fscanf(fp,"%d",&LineWidth);
			fscanf(fp,"%d",&LineColor);

           	do
			{


				fscanf(fp,"%s",&buffer);
				if(strcmp(buffer,"ENDLAYER")!=0)
				{
				
                  CString strName;
			      strName.Format("%s",buffer);
                            
        	       fscanf(fp,"%s",&buffer);
	              ID=atoi(buffer);

                   fscanf(fp,"%s",&buffer);
                   points=new CPoint[2000];
				   int  num=atoi(buffer);
			       for(int i=0;i<num;i++)
				   {   
				       fscanf(fp,"%d,%d",&x,&y);
				       points[i].x=x;
				       points[i].y=y;
				   }
			   	   CGeoLine *pGeoLine=NULL;
		           pGeoLine=new CGeoLine();
				   pGeoLine->SetObjectID(ID);
                    pGeoLine->SetObjectName(strName);
 
                   for(i=0;i<num;i++)
				   {
			          pGeoLine->AddPoint(points[i]);
				   }
                   tempLayer->AddObject(pGeoLine);
                   delete []points;
				   points=NULL;
				}
			}while(strcmp(buffer,"ENDLAYER")!=0);

             tempLayer->SetLayerType(3);
		    tempLayer->SetLineParameter(LineType,LineColor,LineWidth);
		}

		else if(strcmp(buffer,"POLYGON")==0)
		{
   
		  long BondColor,FillColor;

		  fscanf(fp,"%d",&BondColor);
		  fscanf(fp,"%d",&FillColor);

          do
			{   
				fscanf(fp,"%s",&buffer);
				if(strcmp(buffer,"ENDLAYER")!=0)
				{
				
                    CString strName;
				    strName.Format("%s",buffer);
                      


                	fscanf(fp,"%s",&buffer);
					ID=atoi(buffer);
                    fscanf(fp,"%s",&buffer);
			        points=new CPoint[2000];
			        int num=atoi(buffer);
                
			        for(int k=0;k<num;k++)
					{   
				        fscanf(fp,"%d,%d",&x,&y);
			    	    points[k].x=x;
				        points[k].y=y;
				
					}
			   	    CGeoPolygon *pGeoPolygon=NULL;
		            pGeoPolygon=new CGeoPolygon();
			        pGeoPolygon->SetObjectName(strName);
				    pGeoPolygon->SetObjectID(ID);
		            for(int i=0;i<num;i++)
					{
			             pGeoPolygon->AddPoint(points[i]);
					}
                    tempLayer->AddObject(pGeoPolygon);
                    delete []points;
			        points=NULL;
				}
			}while(strcmp(buffer,"ENDLAYER")!=0);
            tempLayer->SetLayerType(5);
		    tempLayer->SetPolygonParameter(BondColor,FillColor);

		}
		else if(strcmp(buffer,"TEXT")==0)
		{ 
          
			long TextColor;
			CString  TextFont;
	        fscanf(fp,"%d",&TextColor);
			fscanf(fp,"%s",&buffer);
			TextFont.Format("%s",buffer);
			tempLayer->SetLayerType(7);
			do
			{
	            fscanf(fp,"%s",&buffer); 
                
                if(strcmp(buffer,"ENDLAYER")!=0)
				{  
					
                   CString strName;
				   strName.Format("%s",buffer);
                      


                	fscanf(fp,"%s",&buffer);
					ID=atoi(buffer);
                    fscanf(fp,"%s",&buffer);
			        points=new CPoint[2000];
			   

					CGeoAnno *pGeoAnno=NULL;
		            pGeoAnno=new CGeoAnno();
                    pGeoAnno->SetObjectName(strName);
					fscanf(fp,"%d,%d",&x,&y);
					pGeoAnno->SetTextPosition(x,y);
					long height;
					fscanf(fp,"%d",&height);
					pGeoAnno->SetTextHeight(height);
					fscanf(fp,"%s",&buffer);
					CString str;
					str.Format("%s",buffer);
					pGeoAnno->SetTextContent(str);
				    fscanf(fp,"%d,%d",&x,&y);
					pGeoAnno->SetTextEndPosition(x,y);
                    pGeoAnno->SetObjectID(ID);
                    tempLayer->AddObject(pGeoAnno);
				}
			}while(strcmp(buffer,"ENDLAYER")!=0);
            tempLayer->SetLayerType(7);
            tempLayer->SetTextParameter(TextColor,TextFont);

		}
	

     map1->m_parLayers.Add(tempLayer);  //添加图层
	   
	}

    map1->m_GridLayer->BuildIndex(map1);  //设置格网
	fclose(fp);

	/*
	FILE *fp;
	if((fp=fopen(FileName,"r"))==NULL)
	{
		AfxMessageBox("Can't Open!");
        exit(0);
	}
	char buffer[80];
	fscanf(fp,"%s",&buffer);
	if(strcmp(buffer,"我们定义的文件")!=0)
	{
         AfxMessageBox("文件格式不对");
         return;
	}

    long Xmin,Ymin,Xmax,Ymax;
	fscanf(fp,"%d,%d",&Xmin,&Ymin);
	fscanf(fp,"%d,%d",&Xmax,&Ymax); 
    map1->SetRect(Xmin,Ymin,Xmax,Ymax);  //设置map1的外接矩形
	int LayerNum;

	fscanf(fp,"%d",&LayerNum);
	map1->SetLayerNum(LayerNum);
	char LayerName[80];
	CGeoLayer *tempLayer=NULL;
    srand( time(0));  //随机值种子

	for(int j=0;j<LayerNum;j++)
	{  
	
		tempLayer=new CGeoLayer();
		tempLayer->SetLayerID(j);
	 
	    fscanf(fp,"%s",&LayerName);
		CString name;
		name.Format("%s",LayerName);
		tempLayer->SetLayerName(name);
		fscanf(fp,"%s",&buffer);


        CPoint *points;
	    long x,y;
        int ID;
		if(strcmp(buffer,"POINT")==0)
		{    
			  long RandColor=RGB(rand()%256,rand()%256,rand()%256);
			  int PointType;
			  long PointRadius,PointColor;
			 
			  fscanf(fp,"%d",&PointType);
			  fscanf(fp,"%d",&PointRadius);
	          fscanf(fp,"%d",&PointColor);

			  do
			  {				  
				   fscanf(fp,"%s",buffer);				   
                  if(strcmp(buffer,"ENDLAYER")!=0)
				   {
					   CString strName;
					   strName.Format("%s",buffer);
                       fscanf(fp,"%s",&buffer);
                        ID=atoi(buffer);
                       fscanf(fp,"%s",&buffer);
					   points=new CPoint[1];
                       fscanf(fp,"%d,%d",&x,&y);
			           points[0].x=x;
			           points[0].y=y;
	                   CGeoPoint *pGeoPoint=NULL;
		               pGeoPoint=new CGeoPoint();
					 
                       pGeoPoint->SetPoint(points[0].x,points[0].y);
					   pGeoPoint->SetObjectName(strName);
                       pGeoPoint->SetObjectID(ID);
				       tempLayer->AddObject(pGeoPoint);
	                   delete []points;
				       points=NULL;
				   }
			  }while(strcmp(buffer,"ENDLAYER")!=0);

              tempLayer->SetLayerType(1);
		      tempLayer->SetPointParameter(PointType,RandColor,PointRadius);
		}

		else if(strcmp(buffer,"LINE")==0)
		{
            long RandColor=RGB(rand()%256,rand()%256,rand()%256); 
			int LineType;
			long LineColor,LineWidth;
          
			fscanf(fp,"%d",&LineType);
			fscanf(fp,"%d",&LineWidth);
			fscanf(fp,"%d",&LineColor);

           	do
			{


				fscanf(fp,"%s",&buffer);
				if(strcmp(buffer,"ENDLAYER")!=0)
				{
			
                  CString strName;
			      strName.Format("%s",buffer);
                            
        	       fscanf(fp,"%s",&buffer);
	              ID=atoi(buffer);

                   fscanf(fp,"%s",&buffer);
				   int  num=atoi(buffer);
                   points=new CPoint[num];
				   
			       for(int i=0;i<num;i++)
				   {   
				       fscanf(fp,"%d,%d",&x,&y);
				       points[i].x=x;
				       points[i].y=y;
				   }
			   	   CGeoLine *pGeoLine=NULL;
		           pGeoLine=new CGeoLine();
				   pGeoLine->SetObjectID(ID);
                    pGeoLine->SetObjectName(strName);
 
                   for(i=0;i<num;i++)
				   {
			          pGeoLine->AddPoint(points[i]);
				   }
                   tempLayer->AddObject(pGeoLine);
                   delete []points;
				   points=NULL;
				}
			}while(strcmp(buffer,"ENDLAYER")!=0);

             tempLayer->SetLayerType(3);
		    tempLayer->SetLineParameter(LineType,RandColor,LineWidth);
		}

		else if(strcmp(buffer,"POLYGON")==0)
		{
   

          long RandColor1=RGB(rand()%256,rand()%256,rand()%256); 
          long RandColor2=RGB(rand()%256,rand()%256,rand()%256);         
		  long BondColor,FillColor;

		  fscanf(fp,"%d",&BondColor);
		  fscanf(fp,"%d",&FillColor);

          do
			{   
				fscanf(fp,"%s",&buffer);
				if(strcmp(buffer,"ENDLAYER")!=0)
				{
                    CString strName;
				    strName.Format("%s",buffer);
                      
                    fscanf(fp,"%s",&buffer);
					ID=atoi(buffer);
                    fscanf(fp,"%s",&buffer);
			        points=new CPoint[2000];
			        int num=atoi(buffer);
                
			        for(int k=0;k<num;k++)
					{   
				        fscanf(fp,"%d,%d",&x,&y);
			    	    points[k].x=x;
				        points[k].y=y;
				
					}
			   	    CGeoPolygon *pGeoPolygon=NULL;
		            pGeoPolygon=new CGeoPolygon();
			        pGeoPolygon->SetObjectName(strName);
				    pGeoPolygon->SetObjectID(ID);
		            for(int i=0;i<num;i++)
					{
			             pGeoPolygon->AddPoint(points[i]);
					}
                    tempLayer->AddObject(pGeoPolygon);
                    delete []points;
			        points=NULL;
				}
			}while(strcmp(buffer,"ENDLAYER")!=0);
            tempLayer->SetLayerType(5);
		    tempLayer->SetPolygonParameter(RandColor1,RandColor2);
		}


		else if(strcmp(buffer,"TEXT")==0)
		{ 
           long RandColor1=RGB(rand()%256,rand()%256,rand()%256); 
			long TextColor;
			CString  TextFont;
	        fscanf(fp,"%d",&TextColor);
			fscanf(fp,"%s",&buffer);
			TextFont.Format("%s",buffer);
			tempLayer->SetLayerType(7);
			do
			{
	            fscanf(fp,"%s",&buffer); 
             
                if(strcmp(buffer,"ENDLAYER")!=0)
				{  
					
                   CString strName;
				   strName.Format("%s",buffer);
                      


                	fscanf(fp,"%s",&buffer);
					ID=atoi(buffer);
                    fscanf(fp,"%s",&buffer);
			        points=new CPoint[2000];
			   

					CGeoAnno *pGeoAnno=NULL;
		            pGeoAnno=new CGeoAnno();
                    pGeoAnno->SetObjectName(strName);
					fscanf(fp,"%d,%d",&x,&y);
					pGeoAnno->SetTextPosition(x,y);
					long height;
					fscanf(fp,"%d",&height);
					pGeoAnno->SetTextHeight(height);
					fscanf(fp,"%s",&buffer);
					CString str;
					str.Format("%s",buffer);
					pGeoAnno->SetTextContent(str);
				    fscanf(fp,"%d,%d",&x,&y);
					pGeoAnno->SetTextEndPosition(x,y);
                    pGeoAnno->SetObjectID(ID);
                    tempLayer->AddObject(pGeoAnno);
				}
			}while(strcmp(buffer,"ENDLAYER")!=0);
            tempLayer->SetLayerType(7);
            tempLayer->SetTextParameter(RandColor1,TextFont);

		}
	

     map1->m_parLayers.Add(tempLayer);  //添加图层
	   
	}
    map1->m_GridLayer->BuildIndex(map1);  //设置格网

	fclose(fp);
	*/
}

void CMapManagerDoc::OnChangeformat() 
{
	// TODO: Add your command handler code here
	CChangeFormat dlg;
	if (dlg.DoModal()==IDOK)
	{
		m_strSouceFile=dlg.m_strSourcePath;
		m_strOutFile=dlg.m_strOutPath;
		ChangeDxfToManager(m_strSouceFile,m_strOutFile);
		AfxMessageBox("转换成功！");		
	}
}
void CMapManagerDoc::ChangeDxfToManager(CString s_FileName,CString o_FileName)
{
	FILE *fp1,*fp2;
	//打开转换源文件与自定义文件
	if((fp1=fopen(s_FileName,"r"))==NULL)
	{
		AfxMessageBox("Can't Open 1!");
        exit(0);
	}
	if((fp2=fopen(o_FileName,"w"))==NULL)
	{
		AfxMessageBox("Can't Open 2!");
        exit(0);
	}
	fprintf(fp2,"自定义Manager格式\n");
	char buffer[80];
  
	long temp;
    do
	{
		fscanf(fp1,"%s",&buffer);
		if(strcmp(buffer,"10")==0)
		{
			fscanf(fp1,"%s",&buffer);
			temp=atof(buffer)*1000000;
			fprintf(fp2,"%d,",temp);
		}
	    if(strcmp(buffer,"20")==0)
		{
			fscanf(fp1,"%s",&buffer);
			temp=atof(buffer)*1000000;
			fprintf(fp2,"%d\n",temp);
		}
	}while(strcmp(buffer,"$EXTMAX")!=0);
    do
	{
        fscanf(fp1,"%s",&buffer);
		if(strcmp(buffer,"10")==0)
		{
			fscanf(fp1,"%s",&buffer);
			temp=atof(buffer)*1000000;
			fprintf(fp2,"%d,",temp);
		}
	    if(strcmp(buffer,"20")==0)
		{
			fscanf(fp1,"%s",&buffer);
			temp=atof(buffer)*1000000;
			fprintf(fp2,"%d\n",temp);
		}
	}while(strcmp(buffer,"ENDSEC")!=0); //最小外接矩形记录完毕


    do
	{
		fscanf(fp1,"%s",&buffer);
	}while(strcmp(buffer,"LAYER")!=0);//开始记录层信息
	do
	{
		fscanf(fp1,"%s",&buffer);
	}while(strcmp(buffer,"70")!=0);
	fscanf(fp1,"%s",&buffer);
	
	int LayerNum=atoi(buffer);
	LayerNum=LayerNum-2;
	fprintf(fp2,"%d\n",LayerNum); //写入图层数信息
	
    do
	{
		fscanf(fp1,"%s",&buffer);
		if(strcmp(buffer,"2")==0)
		{
            fscanf(fp1,"%s",&buffer);
		
		}
	}while(strcmp(buffer,"ENDSEC")!=0);
    do
	{
		fscanf(fp1,"%s",&buffer);
	}while(strcmp(buffer,"ENTITIES")!=0);
	char PrevName[80];
	strcpy(PrevName,"");
    srand( time(0));  //随机值种子
	do
	{
		fscanf(fp1,"%s",&buffer);
		if(strcmp(buffer,"TEXT")==0)  //如果读到文本数据
		{
            
	        fscanf(fp1,"%s",&buffer);
			fscanf(fp1,"%s",&buffer); //读入图层名
            long ID_Num;
			if(strcmp(buffer,PrevName)!=0) //如果当前读入图层和前面图层名不同
			{   
				
				if(strcmp(PrevName,"")!=0)
				{
					fprintf(fp2,"ENDLAYER\n"); 
				//第一图层不写ENDLAYER
					   
				}
                fprintf(fp2,"%s\n",buffer);
				fprintf(fp2,"TEXT\n");	//写上TEXT表示该层为文本层
				
				fprintf(fp2,"%d\n",RGB(rand()%255,rand()%255,rand()%255));
				fprintf(fp2,"隶书\n");
			    ID_Num=0; 
				strcpy(PrevName,buffer);
			}
            fscanf(fp1,"%s",&buffer);
			fscanf(fp1,"%s",&buffer);

	        do
			{
				fscanf(fp1,"%s",&buffer);

				if(strcmp(buffer,"10")==0)  //写入文本起始定位点坐标
				{
					fprintf(fp2,"un-name\n");
					  
                    fprintf(fp2,"%d\n",ID_Num++);
					fprintf(fp2,"000\n");
					
                  
					fscanf(fp1,"%s",&buffer);

		         	temp=atof(buffer)*1000000;
					fprintf(fp2,"%d,",temp);
				}
				if(strcmp(buffer,"20")==0)
				{
                    fscanf(fp1,"%s",&buffer);
				
		         	temp=atof(buffer)*1000000;
					fprintf(fp2,"%d\n",temp);
				}
				if(strcmp(buffer,"40")==0)  //记录文本高度
				{ 
					fscanf(fp1,"%s",&buffer);
				
		         	temp=atof(buffer)*1000000;
					fprintf(fp2,"%d\n",temp);
				}
				if(strcmp(buffer,"1")==0)  //写入文本内容
				{
                    fscanf(fp1,"%s",&buffer);
					fprintf(fp2,"%s\n",buffer);
					
					
				}
                if(strcmp(buffer,"11")==0)  //写入文本末点定位坐标
				{
                    fscanf(fp1,"%s",&buffer);
				
		         	temp=atof(buffer)*1000000;
					fprintf(fp2,"%d,",temp);
				}
            }while(strcmp(buffer,"21")!=0);
			if(strcmp(buffer,"21")==0)
			{
                fscanf(fp1,"%s",&buffer);
		        temp=atof(buffer)*1000000;
				fprintf(fp2,"%d\n",temp);
			}

		}

        if(strcmp(buffer,"POLYLINE")==0)  //如果读到图形数据
		{
            long x[2000],y[2000];
			int num=0;
			fscanf(fp1,"%s",&buffer);
			fscanf(fp1,"%s",&buffer);
			BOOL IsFirst=false;
			int ID_Num;
			if(strcmp(buffer,PrevName)!=0) //如果当前读入图层和前面图层名不同
			{  
				ID_Num=0;
				IsFirst=TRUE;
				if(strcmp(PrevName,"")!=0)
				{
					fprintf(fp2,"ENDLAYER\n"); //第一图层不写ENDLAYER
					    
				}
                fprintf(fp2,"%s\n",buffer);
				strcpy(PrevName,buffer);
			}
			fscanf(fp1,"%s",&buffer);
           
			int tag=0;
			do
			{
				fscanf(fp1,"%s",&buffer);  

				if(strcmp(buffer,"70")==0)  //判断是否封闭
				{
					fscanf(fp1,"%s",&buffer);
					if(strcmp(buffer,"1")==0)
					{
						tag=5;
					}
					
				}

			    if(strcmp(buffer,"VERTEX")==0)  //读到一个点时记录该点信息
				{  
				    do
					{ 
						fscanf(fp1,"%s",&buffer);
					    if(strcmp(buffer,"10")==0)
						{
						 
						    fscanf(fp1,"%s",&buffer);
							x[num]=atof(buffer)*1000000;
							
						}
						
						if(strcmp(buffer,"20")==0)
						{
                            
							 fscanf(fp1,"%s",&buffer);
                            y[num++]=atof(buffer)*1000000;
	                        
						}

					}while(strcmp(buffer,"0")!=0);  //一个点读完
				}
			}while(strcmp(buffer,"SEQEND")!=0); //当读到SEQEND时表示一个实体读完
            //以下判断实体类型——点/线/面
      
			if(num==2&&y[0]==y[1])  
			{  
				if(IsFirst)
				{
					fprintf(fp2,"POINT\n");
				 
                 	fprintf(fp2,"1\n"); 
					fprintf(fp2,"50000\n");
                   
					fprintf(fp2,"%d\n",RGB(rand()%255,rand()%255,rand()%255));
				    IsFirst=false;
				}
			
				num--;
			}
            else if(tag==5)
			{
				if(IsFirst)
				{
					fprintf(fp2,"POLYGON\n");
				
                    fprintf(fp2,"%d\n",RGB(rand()%255,rand()%255,rand()%255));
					fprintf(fp2,"%d\n",RGB(rand()%255,rand()%255,rand()%255));
				 
					IsFirst=false;
				}
			
				x[num]=x[0];
				y[num++]=y[0];
			}
			else 
			{
	            if(IsFirst)
				{
					fprintf(fp2,"LINE\n");
	               
					fprintf(fp2,"1\n"); //线型代号
					fprintf(fp2,"2000\n"); //线宽
          
					fprintf(fp2,"%d\n",RGB(rand()%255,rand()%255,rand()%255)); //线色（随机）
				
					IsFirst=false;
				}
			
			}
            fprintf(fp2,"un-name\n");
            fprintf(fp2,"%d\n",ID_Num++);
			fprintf(fp2,"%d\n",num);
		
			for(int i=0;i<num;i++)
			{ 
		
		        fprintf(fp2,"%d,",x[i]);
				fprintf(fp2,"%d\n",y[i]);

             }
		}
	}while(strcmp(buffer,"ENDSEC")!=0);  //读到ENDSEC时表示实体段读完，同时整个文件也读完
    fprintf(fp2,"ENDLAYER\n");
    fprintf(fp2,"ENDFILE");
	fclose(fp1);
	fclose(fp2);

}

void CMapManagerDoc::OnLayerselect() 
{
	// TODO: Add your command handler code here
	CLayerChooseDlg dlg;
	dlg.DoModal();
	
}

void CMapManagerDoc::OnBmpsave() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(false,"*.bmp",NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,
		"数据文件(*.bmp)|*.bmp|任意文件(*.*)|*.*||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		m_strBmpPath=dlg.GetPathName();
		dlg.DestroyWindow();

	}	
	if (m_strBmpPath=="")
	{
		return;
	}
	else
	{
		BmpSave(m_strBmpPath);
		m_strBmpPath="";
	}
}
void CMapManagerDoc::BmpSave(CString FileName)
{
	
	CViewBitmap bmp;
	CMapManagerView *pView=(CMapManagerView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	CRect rect;
	pView->GetWindowRect(&rect);
	DWORD dwStart = GetTickCount(); 
	DWORD dwEnd  = dwStart; 
	do 
	{ 
	dwEnd = GetTickCount()-dwStart; 
	}while(dwEnd <1*1000); 
	bmp.Capture(rect);
	bmp.SaveBitmapEx(FileName);
}

void CMapManagerDoc::OnFilesave() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(false,"*.Manager",NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,
		"数据文件(*.Manager)|*.Manager|任意文件(*.*)|*.*||",NULL);
	if (dlg.DoModal()==IDOK)
	{
		m_strBmpPath=dlg.GetPathName();
		WriteManagerData(m_strBmpPath);
	}
	
}

void CMapManagerDoc::WriteManagerData(CString FileName)
{
	FILE *fp;
	if((fp=fopen(FileName,"w"))==NULL)
	{
		AfxMessageBox("Can't Open 2!");
        exit(0);
	}
	fprintf(fp,"自定义Manager格式\n");
	CRect rect;
	map1->GetMinRect(rect);
	fprintf(fp,"%d,%d\n",rect.left,rect.bottom);
	fprintf(fp,"%d,%d\n",rect.right,rect.top);
	fprintf(fp,"%d\n",map1->GetLayerNum());
	for(int i=0;i<map1->GetLayerNum();i++)
	{
		fprintf(fp,"%s\n",map1->m_parLayers.GetAt(i)->GetLayerName());
		int LayerType=map1->m_parLayers.GetAt(i)->GetLayerType();
		if(LayerType==1)
		{
			fprintf(fp,"POINT\n");
			int PointType;
			long PointRadius;
			long PointColor;
			map1->m_parLayers.GetAt(i)->GetPointParameter(&PointType,&PointColor,&PointRadius);
			fprintf(fp,"%d\n%d\n%d\n",PointType,PointRadius,PointColor);
			int ObjectNum;
			ObjectNum=	map1->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();
			for(int j=0;j<ObjectNum;j++)
			{
				CString str;
				str=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectName();
				fprintf(fp,"%s\n",str);
				int ID=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectID();
				fprintf(fp,"%d\n",ID);
			    fprintf(fp,"1\n");
				long x,y;
		       ((CGeoPoint *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->GetPoint(x,y);
			   fprintf(fp,"%d,%d\n",x,y);
			}
		}
		if(LayerType==3)
		{
			fprintf(fp,"LINE\n");
			int LineType;
			long LineWidth;
			long LineColor;
			map1->m_parLayers.GetAt(i)->GetLineParameter(&LineType,&LineColor,&LineWidth);
               	fprintf(fp,"%d\n%d\n%d\n",LineType,LineWidth,LineColor);
         	int ObjectNum;
			ObjectNum=	map1->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();
			for(int j=0;j<ObjectNum;j++)
			{
					CString str;
				str=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectName();
				fprintf(fp,"%s\n",str);
					int ID=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectID();
				fprintf(fp,"%d\n",ID);
				int PointNum;
				PointNum=  ((CGeoLine *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetSize();
                fprintf(fp,"%d\n", PointNum);
				for(int k=0;k<PointNum;k++)
				{
					 long x=((CGeoLine *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->x;
                     long y=((CGeoLine *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->y;
					 fprintf(fp,"%d,%d\n",x,y);
				}
			}
		}

		if(LayerType==5)
		{
			fprintf(fp,"POLYGON\n");
		
			long BondColor;
			long FillColor;
			map1->m_parLayers.GetAt(i)->GetPolygonParameter(&BondColor,&FillColor);//,&LineWidth);
               	fprintf(fp,"%d\n%d\n",BondColor,FillColor);
         	int ObjectNum;
			ObjectNum=	map1->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();
			for(int j=0;j<ObjectNum;j++)
			{
					CString str;
				str=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectName();
				fprintf(fp,"%s\n",str);
					int ID=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectID();
				fprintf(fp,"%d\n",ID);
				int PointNum;
				PointNum= ((CGeoLine *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetSize();
                fprintf(fp,"%d\n", PointNum);
				for(int k=0;k<PointNum;k++)
				{
					 long x=((CGeoPolygon *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->x;
                     long y=((CGeoPolygon *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->y;
					 fprintf(fp,"%d,%d\n",x,y);
				}
			}
		}
		if(LayerType==7)
		{
			fprintf(fp,"TEXT\n");
			long  TextColor;
			CString TextFont;
	      	map1->m_parLayers.GetAt(i)->GetTextParameter(&TextColor,&TextFont);//,&LineWidth);
            fprintf(fp,"%d\n%s\n",TextColor,TextFont);
				int ObjectNum;
			ObjectNum=	map1->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();
			for(int j=0;j<ObjectNum;j++)
			{
			  CString str;
			 str=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectName();
			 fprintf(fp,"%s\n",str);
			 int ID=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectID();
             fprintf(fp,"%d\n",ID);
			 fprintf(fp,"000\n");
			long x,y;
		    ((CGeoAnno *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->GetTextPosition(&x,&y);
			fprintf(fp,"%d,%d\n",x,y);
			long height;
			height= ((CGeoAnno *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->GetTextHeight();
		    fprintf(fp,"%d\n",height);
			CString content;
			((CGeoAnno *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->GetTextContent(content);
			fprintf(fp,"%s\n",content);
		    ((CGeoAnno *)(map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->GetTextEndPosition(&x,&y);
			fprintf(fp,"%d,%d\n",x,y);
			}
		}
		fprintf(fp,"ENDLAYER\n");
		}
		fprintf(fp,"ENDFILE\n");

        fclose(fp);
	
}
void CMapManagerDoc::WriteTree()
{
		((CMainFrame*)AfxGetMainWnd())->m_wndTree.DeleteAllItems();  //清空

	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent=NULL;
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
	tvinsert.item.hItem=NULL;

	tvinsert.item.stateMask=TVIS_STATEIMAGEMASK;
	tvinsert.item.cchTextMax=6;
	tvinsert.item.iSelectedImage=1;

	tvinsert.item.pszText="图层管理";
	tvinsert.item.iImage=1;
	HTREEITEM hRoot=((CMainFrame*)AfxGetMainWnd())->m_wndTree.InsertItem(&tvinsert);
	((CMainFrame*)AfxGetMainWnd())->m_wndTree.SetItemState( hRoot, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK );
	
    for(int i=0;i<map1->GetLayerNum();i++)
	{
		  CString LayerName;
		  LayerName=map1->m_parLayers.GetAt(i)->GetLayerName();

          tvinsert.item.pszText=LayerName.GetBuffer(10);
          tvinsert.hParent=hRoot;
	      tvinsert.item.iImage=1;
	      HTREEITEM SubHti=((CMainFrame*)AfxGetMainWnd())->m_wndTree.InsertItem(&tvinsert);
	      ((CMainFrame*)AfxGetMainWnd())->m_wndTree.SetItemState( SubHti, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
	
		  for(int j=0;j<map1->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();j++)
		  {
			  CString ObjID;
			  int id_only=map1->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)->GetObjectID();
              ObjID.Format("%d",id_only);
              ((CMainFrame*)AfxGetMainWnd())->m_wndTree.InsertItem(_T(ObjID),SubHti);
		  }

	}
        
    tvinsert.item.pszText="格网层";
    tvinsert.hParent=hRoot;
	tvinsert.item.iImage=1;
	HTREEITEM SubHti=((CMainFrame*)AfxGetMainWnd())->m_wndTree.InsertItem(&tvinsert);
	((CMainFrame*)AfxGetMainWnd())->m_wndTree.SetItemState( SubHti, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
    ((CMainFrame*)AfxGetMainWnd())->m_wndTree.Expand(hRoot,TVE_EXPAND);
}
