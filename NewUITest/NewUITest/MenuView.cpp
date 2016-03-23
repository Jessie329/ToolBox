
#include "stdafx.h"
#include "MainFrm.h"
#include "MenuView.h"
#include "Resource.h"
#include "NewUITest.h"
class CMenuViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CMenuView;

	DECLARE_SERIAL(CMenuViewMenuButton)

public:
	CMenuViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CMenuViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuView::CMenuView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CMenuView::~CMenuView()
{
}

BEGIN_MESSAGE_MAP(CMenuView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)

    ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY, OnMenuItemClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuView message handlers

int CMenuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
    if (!m_wndMenuPanel.GetSafeHwnd())
    {
        if (!m_wndMenuPanel.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, CRect(0, 0, 0, 0), this, 0))
            return FALSE;

        m_wndMenuPanel.SetOwner(this);

        m_wndMenuPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
        m_wndMenuPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer);
        m_wndMenuPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
        m_wndMenuPanel.SetHotTrackStyle(xtpTaskPanelHighlightItem);
        m_wndMenuPanel.SetSelectItemOnFocus(TRUE);
        m_wndMenuPanel.SetSingleSelection();
        m_wndMenuPanel.AllowDrag(TRUE);
    }

	OnChangeVisualStyle();

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillMenuView();

	return 0;
}

void CMenuView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

CXTPTaskPanelGroup* CMenuView::CreateMenuGroup(UINT nID)
{
    CXTPTaskPanelGroup* pFolder = m_wndMenuPanel.AddGroup(nID);
    pFolder->SetCaption(_T("Menu"));

    CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(ID_MENU_FUNCTION, 0);
    pPointer->SetItemSelected(TRUE);
    pPointer->AllowDrag(FALSE);
    pPointer->AllowDrop(FALSE);

    return pFolder;
}

void CMenuView::FillMenuView()
{
    // get path of executable
    TCHAR szBuff[_MAX_PATH];
    VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

    LPTSTR lpszExt = _tcsrchr(szBuff, '.');
    lstrcpy(lpszExt, _T(".xml"));

    CString m_strIniFileName = szBuff;
    //CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));   // To serialize to XML file

    //if (px.LoadFromFile(m_strIniFileName))
    //{
    //    CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
    //    m_wndMenuPanel.GetGroups()->DoPropExchange(&pxTaskPanel);
    //}
    //else
    {
        m_wndMenuPanel.GetGroups()->Clear(FALSE);
        CString szText;
        szText.LoadString(ID_WINDOW_AMS);
        CXTPTaskPanelGroup* pFolderMenuPanes = m_wndMenuPanel.AddGroup(ID_MENU_FUNCTION);
        pFolderMenuPanes->SetCaption(_T("Menu"));

        pFolderMenuPanes->AddLinkItem(ID_WINDOW_AMS, 1)->SetCaption(_T("AMS"));
        pFolderMenuPanes->AddLinkItem(ID_WINDOW_CNAMS, 2)->SetCaption(_T("CNAMS"));
        pFolderMenuPanes->AddLinkItem(ID_WINDOW_NEWS, 3)->SetCaption(_T("NEWS"));

        CXTPTaskPanelGroup* pFolderWndPanes = m_wndMenuPanel.AddGroup(ID_WINDOW_MANAGER);
        pFolderWndPanes->SetCaption(_T("Window"));

        pFolderWndPanes->AddLinkItem(ID_FILE_NEW, 1)->SetCaption(_T("NEW"));
        pFolderWndPanes->AddLinkItem(ID_FILE_OPEN, 2)->SetCaption(_T("OPEN"));
    }
}

void CMenuView::OnContextMenu(CWnd* pWnd, CPoint point)
{
}

void CMenuView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
    m_wndMenuPanel.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CMenuView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CMenuView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CMenuView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("Add member function..."));
}

void CMenuView::OnClassAddMemberVariable()
{
	// TODO: Add your command handler code here
}

void CMenuView::OnClassDefinition()
{
	// TODO: Add your command handler code here
}

void CMenuView::OnClassProperties()
{
	// TODO: Add your command handler code here
}

void CMenuView::OnNewFolder()
{
	AfxMessageBox(_T("New Folder..."));
}

void CMenuView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
    m_wndMenuPanel.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CMenuView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

    m_wndMenuPanel.SetFocus();
}

void CMenuView::OnChangeVisualStyle()
{
	m_MenuViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_MenuViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_MenuViewImages.Add(&bmp, RGB(255, 0, 0));

    m_wndMenuPanel.SetImageList(&m_MenuViewImages, TVSIL_NORMAL);
}

LRESULT CMenuView::OnMenuItemClick(WPARAM wParam, LPARAM lParam)
{
    if (wParam == XTP_TPN_DBLCLICK)
    {
        CXTPTaskPanelGroupItem* m_pItemPressed = (CXTPTaskPanelGroupItem*)lParam;
        int iSel = m_pItemPressed->GetID();
        switch (iSel)
        {
        case ID_FILE_NEW:
            AfxMessageBox(_T("New Folder..."));
            {
                CDocTemplate* pTemplate = NULL;

                POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
                while (pos)
                {
                    pTemplate = AfxGetApp()->GetNextDocTemplate(pos);

                    ASSERT(pTemplate != NULL);
                    ASSERT_KINDOF(CDocTemplate, pTemplate);

                    //pTemplate->CloseAllDocuments(TRUE);//close the current layout at the same time
                    pTemplate->OpenDocumentFile(NULL);
                    //Load different view
                }
            }
            break;
        }
        return 1;
    }
    return 0;
}
