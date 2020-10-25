// TEdStatic.cpp : implementation file
//

#include "stdafx.h"
#include "..\SVisualApp\SVisualApp.h"
#include "TEdStatic.h"


// CTEdStatic

IMPLEMENT_DYNAMIC(CTEdStatic, CStatic)

CTEdStatic::CTEdStatic()
{
	CTEdStatic::s_seleced_id = IDC_ED_N03;

}

CTEdStatic::~CTEdStatic()
{
}


BEGIN_MESSAGE_MAP(CTEdStatic, CStatic)
END_MESSAGE_MAP()



// CTEdStatic message handlers


int CTEdStatic::s_seleced_id = 0;



void CTEdStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct /*lpDrawItemStruct*/)
{
	CBrush br;
	CBrush br1;
	if(lpDrawItemStruct->CtlID == IDC_ED_N03) 
	{
		//::SetBkMode(lpDrawItemStruct->hDC ,TRANSPARENT);
		br.CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
		br1.CreateSolidBrush(RGB(0x20, 0x00, 0x00));
		::FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br1);
		::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
		//::FillRect(
  
		return;
	
		
	}
	else if(lpDrawItemStruct->itemState & ODS_FOCUS)
	{
		//need post drawitem for old select
		
		CWnd* pWin = GetParent()->GetDlgItem(s_seleced_id);
		if(pWin) pWin->Invalidate(); //(WM_DRAWITEM);
		s_seleced_id = lpDrawItemStruct->CtlID; 

		br.CreateSolidBrush(RGB(0xE0, 0x20, 0x20));
		br1.CreateSolidBrush(RGB(0xFF, 0xE0, 0xE0));
		
		::FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br1);
		::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
			
		return;
	}
	else 
	{
		//::SetBkColor(lpDrawItemStruct->hDC,RGB(255, 0, 0));
		//::SetBkMode(lpDrawItemStruct->hDC ,TRANSPARENT);
		//if(lpDrawItemStruct->CtlID == s_seleced_id) return;
		if(lpDrawItemStruct->CtlID == IDC_ED_N02 ||lpDrawItemStruct->CtlID == IDC_ED_N04) 
		{
			br.CreateSolidBrush(RGB(0xFF, 0xFF,0x00));
			br1.CreateSolidBrush(RGB(0x20, 0x20,0x00));
			::FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br1);
			::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
		}
		else if(lpDrawItemStruct->CtlID == IDC_ED_N01 ||lpDrawItemStruct->CtlID == IDC_ED_N05) 
		{
			br.CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
			br1.CreateSolidBrush(RGB(0x40, 0x40, 0x40));
			::FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br1);
			::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
		}
	}

	// TODO:  Add your code to draw the specified item
}

//BOOL CTEdStatic::Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	bReturn = CStatic::Create(lpszText, dwStyle, rect, pParentWnd, nID);
//	this->dwStyle |= SS_OWNERDRAW;
//	
//}

void CTEdStatic::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	CStatic::PreSubclassWindow();
	ModifyStyle(0, SS_OWNERDRAW);
}
