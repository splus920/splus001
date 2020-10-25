// TRichEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "..\SVisualApp\SVisualApp.h"
#include "TRichEditCtrl.h"


// CTRichEditCtrl

IMPLEMENT_DYNAMIC(CTRichEditCtrl, CRichEditCtrl)

CTRichEditCtrl::CTRichEditCtrl()
{

}

CTRichEditCtrl::~CTRichEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CTRichEditCtrl, CRichEditCtrl)
//	ON_CONTROL_REFLECT(EN_SETFOCUS, &CTRichEditCtrl::OnEnSetfocus)
//ON_CONTROL_REFLECT(EN_CHANGE, &CTRichEditCtrl::OnEnChange)
END_MESSAGE_MAP()



// CTRichEditCtrl message handlers


void CTRichEditCtrl::TSetFont(CString fontname, int size, bool bFocus)
{
	if(fontname.IsEmpty()) fontname = _T("Arial");
	if(size == 0 ) size = 48;

	CHARFORMAT Cfm;
	GetDefaultCharFormat(Cfm);

	//GetSelectionCharFormat(Cfm);
	Cfm.cbSize = sizeof(CHARFORMAT);
	_tcscpy(Cfm.szFaceName, fontname);
	Cfm.yHeight = 300;
	//SetSelectionCharFormat(Cfm); 
	SetDefaultCharFormat(Cfm);
	if(bFocus) 
		SetFocus();
	
}

int CTRichEditCtrl::TGetStyle()
{
	CHARFORMAT Cfm;
	GetSelectionCharFormat(Cfm);
	Cfm.cbSize = sizeof(CHARFORMAT);
	return Cfm.dwEffects;

}
void CTRichEditCtrl::TSetStyle02(int nStyle, int nForce, bool bFocus)
{
	CHARFORMAT2 Cfm;
	GetSelectionCharFormat(Cfm);

	if(nForce == 2) //clean it
	{
		Cfm.dwMask = CFM_UNDERLINE|CFM_UNDERLINETYPE;
		Cfm.dwEffects &= ~nStyle;
		Cfm.bUnderlineType = 0;
	}
	else if(nForce == 1) //set it
	{
		Cfm.dwMask = CFM_UNDERLINE|CFM_UNDERLINETYPE;
		Cfm.dwEffects |= nStyle;
		Cfm.bUnderlineType = CFU_UNDERLINEWAVE | 0x50;
	}
	SetSelectionCharFormat(Cfm); 

}
void CTRichEditCtrl::TSetStyle(int nStyle, int nForce, bool bFocus)
{
	CHARFORMAT Cfm;
	int nnStyle = nStyle;
	if(nForce == 1) // keep it is  
	{
		if(TGetStyle()&nStyle) return;
	}
	else if(nForce == 0)  //keep it is
	{
		if(!(TGetStyle()&nStyle)) return;
	}	
	GetSelectionCharFormat(Cfm);
	Cfm.cbSize = sizeof(CHARFORMAT);

	if(nStyle == CFE_BOLD) Cfm.dwMask = CFM_BOLD;
	else if(nStyle == CFE_ITALIC) Cfm.dwMask = CFM_ITALIC;
	else if(nStyle == CFE_UNDERLINE) Cfm.dwMask = CFM_UNDERLINE; 
	else if(nStyle == CFM_LINK) Cfm.dwMask = CFM_LINK; 
	
	if(nForce ==2) Cfm.dwEffects &= ~nStyle;  //like to force underline to move
	else Cfm.dwEffects ^= nStyle; 
	SetSelectionCharFormat(Cfm); 
	if(bFocus) 
		SetFocus();

	
}

//#define PFA_LEFT			 1
//#define PFA_RIGHT			 2
//#define PFA_CENTER			 3

int CTRichEditCtrl::TGetParagraph()
{
	PARAFORMAT Pfm;
	Pfm.cbSize = sizeof(PARAFORMAT);
	GetParaFormat(Pfm);
	Pfm.dwMask = PFM_ALIGNMENT;
	return Pfm.wAlignment;
}

void CTRichEditCtrl::TSetParagraph(int nAlignment, bool bFocus)
{
	PARAFORMAT Pfm;
	
	long nStart, nEnd;
	
	GetSel(nStart, nEnd);
	SetSel(0, -1);

	Pfm.cbSize = sizeof(PARAFORMAT);
	Pfm.dwMask = PFM_ALIGNMENT;
	Pfm.wAlignment = nAlignment;
	SetParaFormat(Pfm);
	SetSel(nStart, nEnd);

	if(bFocus) 
		SetFocus();
}
void CTRichEditCtrl::SpellReplace(int nIndex)
{
	long nStart, nEnd;
	GetSel(nStart,nEnd);

	CT2SCheck	theSpell;
	
	CString str;
	GetWindowText(str); 
	if(theSpell.CheckStr(true, str)) return;

	int nNew, nOld;
	int iIndex = 0;
	int iWordLen = -1; 
	for(;;)
	{
		iWordLen = theSpell.EnumCheck(iIndex);
		if(iWordLen == -1) break; 	
		
		if((nStart >= iIndex) && (nStart <= iIndex+iWordLen))
		{
			//SetSel(iIndex,iIndex+iWordLen);
			//str = GetSelText();
			GetTextRange(iIndex,iIndex+iWordLen, str);
			break;
		}
		iIndex = iIndex + iWordLen;
	}
	
	nNew = nOld = str.GetLength();
	
	CStringArray theStrList;
	theSpell.GetCorrections(str,theStrList);
	if(nIndex < theStrList.GetCount())
	{
		str = theStrList.GetAt(nIndex);
		nNew = str.GetLength();
		
		SetSel(iIndex,iIndex+iWordLen);
		ReplaceSel(str);				
	}
	//SpellCheck();
	SetSel(nStart + (nNew-nOld),nEnd+ (nNew-nOld));
}
void CTRichEditCtrl::SpellList(CStringArray& theStrList)
{
	long nStart, nEnd;
	GetSel(nStart,nEnd);

	CString str;
	CT2SCheck	theSpell;


	GetWindowText(str); 
	if(theSpell.CheckStr(true, str)) return;

	int iIndex = 0;
	int iWordLen = -1; 
	for(;;)
	{
		iWordLen = theSpell.EnumCheck(iIndex);
		if(iWordLen == -1) break; 	
		
		if((nStart >= iIndex) && (nStart <= iIndex+iWordLen))
		{
			//SetSel(iIndex,iIndex+iWordLen);
			//str = GetSelText();
			GetTextRange(iIndex,iIndex+iWordLen, str);
			theSpell.GetCorrections(str,theStrList);
			break;
		}
		iIndex = iIndex + iWordLen;
	}
	SetSel(nStart,nEnd);
}

void CTRichEditCtrl::SpellCheck()
{
	CString str;
	CT2SCheck	theSpell;
	
	long nStart, nEnd;
	GetSel(nStart,nEnd);
	
	//clean up and rebuild
	SetSel(0,-1);
	TSetStyle02(CFE_UNDERLINE, 2, false);
	
	SetSel(nStart,nEnd);
	GetWindowText(str); 
	if(theSpell.CheckStr(true, str)) return;
	
	int iIndex = 0;
	int iWordLen = -1; 
	for(;;)
	{
		iWordLen = theSpell.EnumCheck(iIndex);
		if(iWordLen == -1) break; 	
		SetSel(iIndex,iIndex+iWordLen);
		TSetStyle02(CFE_UNDERLINE, 1, false);
		iIndex = iIndex + iWordLen;
	}
	SetSel(nStart,nEnd);
	//str = GetSelText();
	//CStringArray theStrList;
	//m_theSpell.GetCorrections(str,theStrList);
	//for(UINT ii = 0; ii < theStrList.GetCount(); ii++)
	//	m_strlist.AddString(theStrList.GetAt(ii));
	//m_iIndex = iIndex+m_iWordLen;
	//return true;
	return;
}

//void CTRichEditCtrl::OnEnSetfocus()
//{
//	// TODO: Add your control notification handler code here
//	
//
//}

//void CTRichEditCtrl::OnEnChange()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CRichEditCtrl::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//	SpellCheck();
//}
