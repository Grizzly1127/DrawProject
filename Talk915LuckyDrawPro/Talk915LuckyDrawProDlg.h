
// Talk915LuckyDrawProDlg.h : ͷ�ļ�
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
// CTalk915LuckyDrawProDlg �Ի���
class CTalk915LuckyDrawProDlg : public CDialog, public ThreadEx
{
// ����
public:
	CTalk915LuckyDrawProDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TALK915LUCKYDRAWPRO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	virtual void ThreadProcMain(void);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	LIST_WINNING m_listWinner;//��������
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
