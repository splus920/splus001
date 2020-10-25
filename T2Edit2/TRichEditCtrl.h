#pragma once


// CTRichEditCtrl

class CTRichEditCtrl : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CTRichEditCtrl)

public:
	CTRichEditCtrl();
	virtual ~CTRichEditCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void	TSetFont(CString fontname, int size, bool bFocus = true);
	void	TSetStyle(int nStyle, int nForce = -1, bool bFocus = true);
	void	TSetStyle02(int nStyle, int nForce = -1, bool bFocus = true);
	void	TSetParagraph(int nAlignment, bool bFocus = true);

	int		TGetParagraph();
	int		TGetStyle();
	void	SpellCheck();
	void	SpellList(CStringArray& theStrList);
	void	SpellReplace(int nID);
public:
//	afx_msg void OnEnSetfocus();
//	afx_msg void OnEnChange();
};


