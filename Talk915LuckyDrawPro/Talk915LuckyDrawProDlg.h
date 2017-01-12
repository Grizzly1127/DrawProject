
// Talk915LuckyDrawProDlg.h : 头文件
//

#pragma once
#include <list>
#include "ThreadEx.h"
#include "BtnST.h"
#include "CharCode.h"
using namespace std;

typedef struct tag_Winning
{
	CString strWinner;
	int nRank;
}WINNING, *P_WINNING;
typedef list<P_WINNING> LIST_WINNING;
// CTalk915LuckyDrawProDlg 对话框
class CTalk915LuckyDrawProDlg : public CDialog, public ThreadEx
{
// 构造
public:
	CTalk915LuckyDrawProDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TALK915LUCKYDRAWPRO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	virtual void ThreadProcMain(void);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void DrawBkgnd(CDC* pDC);
	CString m_strBkgndPath;
	CString m_strNamePath;
	CFont m_font;
	CFont m_fontBt;
	BOOL m_bRoll;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	CButtonST m_btRoll;
	list<CString> m_listNames;
	LIST_WINNING m_listWinner;//获奖者名单
	CString m_strLuckyMan;

	BOOL ReadNameFromTxt();
	void EraseNameList();
	CString GetModuleDir();
	afx_msg LRESULT RollName(WPARAM wParam, LPARAM lParam);
	virtual void OnCancel();
	CButtonST m_btClose;
	afx_msg void OnBnClickedButtonClose();
	CButtonST m_btMin;
	afx_msg void OnBnClickedButtonMin();
};
