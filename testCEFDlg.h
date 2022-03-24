
// testCEFDlg.h: 头文件
//

#pragma once
#include "simple_handler.h"
#include "httplib.h"
using namespace httplib;
// CtestCEFDlg 对话框
class CtestCEFDlg : public CDialogEx
{
// 构造
public:
	CtestCEFDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTCEF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	Server httplibSever;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
