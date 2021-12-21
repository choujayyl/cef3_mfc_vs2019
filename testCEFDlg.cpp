
// testCEFDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "testCEF.h"
#include "testCEFDlg.h"
#include "afxdialogex.h"
#include "include/cef_app.h"
#include "CSimpleClient.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestCEFDlg 对话框



CtestCEFDlg::CtestCEFDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTCEF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestCEFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestCEFDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CtestCEFDlg 消息处理程序

BOOL CtestCEFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CefRefPtr<CSimpleClient> client(new CSimpleClient());

	//CefSettings settings;
	//CefSettingsTraits::init(&settings);
	//settings.multi_threaded_message_loop = true;
	//CefMainArgs mainArgs;
	//CefRefPtr<CefApp> cefApp;
	//CefInitialize(mainArgs, settings, cefApp, NULL);

	CRect rect;
	GetWindowRect(&rect);

	CefWindowInfo info;
	CefBrowserSettings b_settings;
	
	
	info.SetAsChild(GetSafeHwnd(), CefRect(0, 0, rect.Width(), rect.Height()));
	CefBrowserHost::CreateBrowser(info, client, CefString("file:///./sample/index.html"), b_settings, nullptr, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestCEFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtestCEFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

