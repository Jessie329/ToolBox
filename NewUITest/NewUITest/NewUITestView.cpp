
// NewUITestView.cpp : implementation of the CNewUITestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "NewUITest.h"
#endif

#include "NewUITestDoc.h"
#include "NewUITestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewUITestView

IMPLEMENT_DYNCREATE(CNewUITestView, CView)

BEGIN_MESSAGE_MAP(CNewUITestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNewUITestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CNewUITestView construction/destruction

CNewUITestView::CNewUITestView()
{
	// TODO: add construction code here

}

CNewUITestView::~CNewUITestView()
{
}

BOOL CNewUITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CNewUITestView drawing

void CNewUITestView::OnDraw(CDC* /*pDC*/)
{
	CNewUITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CNewUITestView printing


void CNewUITestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNewUITestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNewUITestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNewUITestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CNewUITestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNewUITestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNewUITestView diagnostics

#ifdef _DEBUG
void CNewUITestView::AssertValid() const
{
	CView::AssertValid();
}

void CNewUITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNewUITestDoc* CNewUITestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewUITestDoc)));
	return (CNewUITestDoc*)m_pDocument;
}
#endif //_DEBUG


// CNewUITestView message handlers
