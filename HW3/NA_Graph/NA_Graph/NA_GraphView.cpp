
// NA_GraphView.cpp: CNAGraphView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "NA_Graph.h"
#endif

#include "NA_GraphDoc.h"
#include "NA_GraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNAGraphView

IMPLEMENT_DYNCREATE(CNAGraphView, CView)

BEGIN_MESSAGE_MAP(CNAGraphView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CNAGraphView 생성/소멸

CNAGraphView::CNAGraphView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNAGraphView::~CNAGraphView()
{
}

BOOL CNAGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CNAGraphView 그리기

void CNAGraphView::OnDraw(CDC* pDC)
{
	CNAGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen penAxis(PS_DOT, 2, RGB(0, 0, 255));
	pDC->SelectObject(&penAxis);

	pDC->MoveTo(50, 100);
	pDC->LineTo(500, 100);

	pDC->MoveTo(100, 20);
	pDC->LineTo(100, 200);

	int res;
	CString text = _T("bessj0");
	pDC->TextOutW(50, 50, text);
	for (int i = 10; i < 100; i++) {
		res = (int)(50 * bessj0(0.1 * (double)i));
		pDC->SetPixel(i + 100, res + 100, RGB(255, 0, 0));
	}
	

}


// CNAGraphView 인쇄

BOOL CNAGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CNAGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CNAGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CNAGraphView 진단

#ifdef _DEBUG
void CNAGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CNAGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNAGraphDoc* CNAGraphView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNAGraphDoc)));
	return (CNAGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CNAGraphView 메시지 처리기
