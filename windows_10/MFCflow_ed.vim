// MFC 프로그램이 시작되면서 호출하는 프로그램 흐름 순서도입니다
    CApp::CApp(void)   
    CApp::InitInstance(void)   
    CDoc::CDoc(void)   
    CMainFrame::CMainFrame(void)   
    CMainFrame::LoadFrame(unsigned int, unsigned long, CWnd *, CCreateContext *)   
    CMainFrame::PreCreateWindow(tagCREATESTRUCTW &)   
    CMainFrame::PreCreateWindow(tagCREATESTRUCTW &)   
    CMainFrame::OnCreate(tagCREATESTRUCTW *)   
        CMainFrame::OnCreateClient(tagCREATESTRUCTW *, CCreateContext *)   
        CView::CView(void)   
        CView::Create(const wchar_t *, const wchar_t *, unsigned long, const tagRECT &, CWnd *, unsigned int, CCreateContext *)   
        CView::PreCreateWindow(tagCREATESTRUCTW &)   
        CView::OnCreate(tagCREATESTRUCTW *)   
        CView::OnShowWindow(int, unsigned int)   
    CMainFrame::OnCreateClient() - return
    CMainFrame::OnCreate() - return
    CDoc::OnNewDocument(void)   
    CView::OnInitialUpdate(void)   
    CMainFrame::OnActivateApp(int, unsigned long)   
    CMainFrame::OnActivate(unsigned int, CWnd *, int)   
    CMainFrame::OnShowWindow(int, unsigned int)   
    CView::GetDocument(void)   
    CApp::Run(void)   
        CMainFrame::OnActivate(unsigned int, CWnd *, int)   
        CMainFrame::OnActivateApp(int, unsigned long)   
        CMainFrame::OnActivateApp(int, unsigned long)   
        CMainFrame::OnActivate(unsigned int, CWnd *, int)   
        CMainFrame::OnClose(void)   
            CMainFrame::OnShowWindow(int, unsigned int)   
            CMainFrame::OnActivate(unsigned int, CWnd *, int)   
            CMainFrame::OnActivateApp(int, unsigned long)   
            CMainFrame::DestroyWindow(void)   
            CMainFrame::OnDestroy(void)   
            CView::OnDestroy(void)   
            CView::PostNcDestroy(void)   
            CView::~CView(void)   
            CMainFrame::OnNcDestroy(void)   
                CMainFrame::PostNcDestroy(void)   
            CMainFrame::OnNcDestroy() - return
            CDoc::~CDoc(void)   
       MainFrame::OnClose() - return
       CApp::ExitInstance(void)   
    CApp::Run() - return
    '[6464] .exe' 프로그램이 종료되었습니다(코드: 0 (0x0)).

