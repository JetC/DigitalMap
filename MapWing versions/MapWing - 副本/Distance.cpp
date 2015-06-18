#include "stdafx.h"
#include "tool_distance.h"
#include "MapWingView.h"
#include "MapWingDoc.h"
#include "mainfrm.h"
#include "math.h"

Distance::Distance() : erase(FALSE) , pen(PS_SOLID, 2, RGB(255, 0, 0)) {
}

Distance::~Distance() {
	pen.DeleteObject();
}

void Distance::OnLButtonDown(UINT nFlags, CPoint point) {
	if (!isMouseCaptured) {
		isMouseCaptured = true;
		GetView()->SetCapture();
	}

	pm = mousePosition = point;
	line.Add(new Point(GetDoc()->map_->GetMatrix()->UnScaleTrans_xy(point.x, point.y)));
}

void Distance::OnMouseMove(UINT nFlags, CPoint point) {
	if (isMouseCaptured) {
		//SetCursor(LoadCursor(NULL, IDC_CROSS);
		CMapWingView* pView = GetView();
		CDC* pDC = pView->GetDC();
		CPen* old_pen = pDC->SelectObject(&pen);
		pDC->SetROP2(R2_XORPEN);
		if (erase) {
			pDC->MoveTo(mousePosition);
			pDC->LineTo(pm);
		} else {
			erase = TRUE;
		}
		pDC->MoveTo(mousePosition);
		pDC->LineTo(point);
		pm = point;
		pDC->SelectObject(old_pen);
		pView->ReleaseDC(pDC);
	}
}

void Distance::OnLButtonDblClk(UINT nFlags, CPoint point) {
	if (isMouseCaptured)
	{
		ReleaseCapture();
		isMouseCaptured = false;
		double sum = 0;
		if(line.Count() > 1) {
			for(int i = 1; i < line.Count(); i++) {
				double dx = line.GetAt(i)->x - line.GetAt(i - 1)->x;
				double dy = line.GetAt(i)->y - line.GetAt(i - 1)->y;
				sum += sqrt(dx * dx + dy * dy);
			}
		}
		line.RemoveAll();
		char text[128];
		sprintf(text, "总长度为：%.6lf", sum);
		GetView()->MessageBox(text, "距离", MB_OK);
		GetView()->Invalidate();
	}
}