
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "NewUITest.h"

#include "ChildFrm.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers
int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    CMenu* pMenu = GetSystemMenu(FALSE);

    pMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);
    pMenu->RemoveMenu(SC_MINIMIZE, MF_BYCOMMAND);
    pMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
    pMenu->RemoveMenu(SC_MOVE, MF_BYCOMMAND);
    pMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);

    return 0;
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs,
    CCreateContext* pContext)
{
    DragAcceptFiles();
    return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}