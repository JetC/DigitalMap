#ifndef TOOL_DISTANCE_H
#define TOOL_DISTANCE_H

#include "tool.h"

class Distance : public Tool {
public:
	Distance();
	virtual ~Distance();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);

private:
	BOOL erase;
	CPoint pm;
	CPen pen;
	map::LineString line;
};

#endif