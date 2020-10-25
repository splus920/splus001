// TPlayerButton.cpp : implementation file
//

#include "stdafx.h"
#include "..\SVisualApp\SVisualApp.h"
#include "TEdButton.h"

//this is GitHub test001
// CTPlayerButton

IMPLEMENT_DYNAMIC(CTEdButton, CButton)

CTEdButton::CTEdButton()
{
	CTEdButton::s_seleced_id = IDC_ED_N3;
}

//CTEdButton::~CTEdButton()
//{
//}


BEGIN_MESSAGE_MAP(CTEdButton, CButton)
	//ON_WM_DRAWITEM_REFLECT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CTPlayerButton message handlers


int CTEdButton::s_seleced_id = 0;
//CRect CTPlayerButton::s_update_rect;
void CTEdButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct /*lpDrawItemStruct*/)
{
	if(lpDrawItemStruct->CtlID == s_seleced_id) 
	{
		::SetBkMode(lpDrawItemStruct->hDC ,TRANSPARENT);
		
		CBrush br(RGB(255, 0, 0));
		::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
		return;
	
		
	}
	else if(lpDrawItemStruct->itemState & ODS_FOCUS)
	{
		//need post drawitem for old select
		
		CWnd* pWin = GetParent()->GetDlgItem(s_seleced_id);
		if(pWin) pWin->Invalidate(); //(WM_DRAWITEM);
		s_seleced_id = lpDrawItemStruct->CtlID; 

		CBrush br(RGB(255, 0, 0));
		::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
		return;
	}
	else
	{
		::SetBkMode(lpDrawItemStruct->hDC ,TRANSPARENT);
		if(lpDrawItemStruct->CtlID == s_seleced_id) return;
	
		CBrush br(RGB(0, 0, 255));
		::FrameRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, br);
	}
}

void CTEdButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

