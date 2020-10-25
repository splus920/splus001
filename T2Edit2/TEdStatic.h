#pragma once


// CTEdStatic

class CTEdStatic : public CStatic
{
	DECLARE_DYNAMIC(CTEdStatic)
public:
	static int		s_seleced_id;


public:
	CTEdStatic();
	virtual ~CTEdStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
//	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
protected:
	virtual void PreSubclassWindow();
};


