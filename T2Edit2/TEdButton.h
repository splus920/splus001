#pragma once


// CTPlayerButton

class CTEdButton : public CButton
{
	DECLARE_DYNAMIC(CTEdButton)
public:
	static int		s_seleced_id;

public:
	CTEdButton();
//	virtual ~CTEdButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


