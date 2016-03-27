// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "CalendarBar.h"
#include "MFCApplication2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 10;

/////////////////////////////////////////////////////////////////////////////
// CCalendarBar

CCalendarBar::CCalendarBar()
{
}

CCalendarBar::~CCalendarBar()
{
}

BEGIN_MESSAGE_MAP(CCalendarBar, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarBar message handlers

int CCalendarBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBitmap bmp;
	bmp.LoadBitmap(IDB_PAGES_SMALL_HC);

	m_Images.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add(&bmp, RGB(255, 0, 255));

	return 0;
}

BOOL CCalendarBar::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		AfxMessageBox(_T(""));
	}

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CCalendarBar::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CCalendarBar::OnSetFocus(CWnd *pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
}

void CCalendarBar::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
}

BOOL CCalendarBar::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID);
}

void CCalendarBar::ConstructMenu()
{
	menuItemsMap[ID_MENU_LAYOUT_NEW] = IDS_MENU_LAYOUT_NEW;
	menuItemsMap[ID_MENU_LAYOUT_OPEN] = IDS_MENU_LAYOUT_OPEN;
	menuItemsMap[ID_MENU_LAYOUT_SAVE] = IDS_MENU_LAYOUT_SAVE;
	for (int i = 0; i < LayoutItems::ID_MENU_LAYOUT_COUNT; i++)
	{
		int iStringID = menuItemsMap.find(i)->second;
		menuSubItemMap[iStringID] = CRect(0, 0, 0, 0);
	}
}

void CCalendarBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect(rectClient);

	dc.FillRect(rectClient, &afxGlobalData.brWindow);

	{
		COLORREF clrText = CMFCVisualManager::GetInstance()->OnDrawPaneCaption(&dc, NULL, FALSE, CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&afxGlobalData.penBarShadow);
		dc.SelectStockObject(BLACK_PEN);
		dc.SelectObject(pOldPen);
		dc.SetBkMode(TRANSPARENT);

		CString szText;
		CRect rectCalendar = rectClient;

		rectCalendar.bottom = rectCalendar.top + afxGlobalData.GetTextHeight(TRUE) * 3 / 2 - 10;
		rectCalendar.DeflateRect(15, 0);
		for (int i = 0; i < LayoutItems::ID_MENU_LAYOUT_COUNT; i++)
		{
			rectCalendar.top = rectCalendar.bottom + 5;
			rectCalendar.bottom = rectCalendar.top + afxGlobalData.GetTextHeight(TRUE) * 3 / 2 - 5;
			rectCalendar.left -= 20;
			dc.FillSolidRect(rectCalendar, RGB(255, 255, 213));
			m_Images.Draw(&dc, 3, rectCalendar.TopLeft(), 0);
			rectCalendar.left += 20;
			dc.SetTextColor(afxGlobalData.clrHotLinkNormalText);
			dc.DrawText(_T("OPEN"), rectCalendar, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
		}
		dc.FillSolidRect(rectCalendar, RGB(255, 255, 213));
		m_Images.Draw(&dc, 3, rectCalendar.TopLeft(), 0);
		rectCalendar.left += 20;
		dc.SetTextColor(afxGlobalData.clrHotLinkNormalText);
		dc.DrawText(_T("NEW"), rectCalendar, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

		rectCalendar.top = rectCalendar.bottom + 5;
		rectCalendar.bottom = rectCalendar.top + afxGlobalData.GetTextHeight(TRUE) * 3 / 2 - 5;
		rectCalendar.left -= 20;
		dc.FillSolidRect(rectCalendar, RGB(255, 255, 213));
		m_Images.Draw(&dc, 3, rectCalendar.TopLeft(), 0);
		rectCalendar.left += 20;
		dc.SetTextColor(afxGlobalData.clrHotLinkNormalText);
		dc.DrawText(_T("OPEN"), rectCalendar, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

		rectCalendar.top = rectCalendar.bottom + 5;
		rectCalendar.bottom = rectCalendar.top + afxGlobalData.GetTextHeight(TRUE) * 3 / 2 - 5;
		rectCalendar.left -= 20;
		dc.FillSolidRect(rectCalendar, RGB(255, 255, 213));
		m_Images.Draw(&dc, 3, rectCalendar.TopLeft(), 0);
		rectCalendar.left += 20;
		dc.SetTextColor(afxGlobalData.clrHotLinkNormalText);
		dc.DrawText(_T("SAVE"), rectCalendar, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

		CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);
		dc.SelectObject(pOldFont);
	}
}


