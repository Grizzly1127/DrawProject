
// Talk915LuckyDrawProDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Talk915LuckyDrawPro.h"
#include "Talk915LuckyDrawProDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTalk915LuckyDrawProDlg 对话框


#define WM_DISPLAYNAME (WM_USER+100)
CTalk915LuckyDrawProDlg::CTalk915LuckyDrawProDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTalk915LuckyDrawProDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CString strPath = GetModuleDir();
	m_strBkgndPath.Format(_T("%s\\background.jpg"), strPath);//设置背景路径
	m_strNamePath.Format(_T("%s\\names.txt"), strPath);//设置名字路径
	m_bRoll = FALSE;
	m_listNames.clear();
}

void CTalk915LuckyDrawProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_btRoll);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btClose);
	DDX_Control(pDX, IDC_BUTTON_MIN, m_btMin);
}

BEGIN_MESSAGE_MAP(CTalk915LuckyDrawProDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTalk915LuckyDrawProDlg::OnBnClickedButtonStart)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_DISPLAYNAME, RollName)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CTalk915LuckyDrawProDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CTalk915LuckyDrawProDlg::OnBnClickedButtonMin)
END_MESSAGE_MAP()


// CTalk915LuckyDrawProDlg 消息处理程序

BOOL CTalk915LuckyDrawProDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CRect rcDesk(0,0,0,0);
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	rcDesk.right = cx;
	rcDesk.bottom = cy;
	MoveWindow(rcDesk);
	
	CRect rcClient;
	GetClientRect(&rcClient);
	int nBtnW = rcClient.Width() * 0.103;
	int nBtnH = rcClient.Height() * 0.055;
	int nNameW = rcClient.Width() * 0.16;
	int nNameH = rcClient.Height() * 0.087;
	int nBtnClose = 20;

	GetDlgItem(IDC_BUTTON_START)->SetWindowPos(NULL, (rcClient.Width() - nBtnW) / 2, rcClient.Height() * 0.85, nBtnW, nBtnH, SWP_SHOWWINDOW);
	GetDlgItem(IDC_STATIC_NAME)->SetWindowPos(NULL, (rcClient.Width() - nNameW) / 2, rcClient.Height() * 0.611, nNameW, nNameH, SWP_SHOWWINDOW);
	GetDlgItem(IDC_BUTTON_CLOSE)->SetWindowPos(NULL, rcClient.Width() - nBtnClose, 0, nBtnClose, nBtnClose, SWP_SHOWWINDOW);
	GetDlgItem(IDC_BUTTON_MIN)->SetWindowPos(NULL, 0, 0, nBtnClose, nBtnClose, SWP_SHOWWINDOW);

	m_font.CreatePointFont(500, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&m_font);
	m_fontBt.CreatePointFont(200, _T("微软雅黑"));
	m_btRoll.SetFont(&m_fontBt);
	m_btRoll.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(248, 227, 192));
	m_btRoll.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(187, 15, 23));
	m_btRoll.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(248, 227, 192));
	m_btRoll.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(187, 15, 23));
	m_btRoll.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(248, 227, 192));
	m_btRoll.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(187, 15, 23));
	m_btRoll.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btClose.DrawTransparent(TRUE);
	m_btMin.DrawTransparent(TRUE);

	m_btRoll.SetWindowText(_T("开  始"));

	if (!ReadNameFromTxt())
	{
		OnClose();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTalk915LuckyDrawProDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTalk915LuckyDrawProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTalk915LuckyDrawProDlg::ReadNameFromTxt()
{
	CFile file;
	if (!file.Open(m_strNamePath.GetBuffer(0), CFile::modeRead))
		return false;

	int nCount = file.GetLength();
	char *ptchBuffer = new char[nCount + 1];
	ptchBuffer[nCount] = '\0';
	if (file.Read(ptchBuffer, nCount) <= 0)
		return FALSE;
	file.Close();

	char* szSplit = "\r\n";
	char *substr = strtok(ptchBuffer, szSplit);
	while (substr != NULL) {
		CharCode szName(substr);
		m_listNames.push_back(szName.GetStringW());
		substr = strtok(NULL, szSplit);/*在第一次调用时，strtok()必需给予参数str字符串，
								   往后的调用则将参数str设置成NULL。每次调用成功则返回被分割出片段的指针。*/
	}

	return TRUE;
}

void CTalk915LuckyDrawProDlg::OnBnClickedButtonStart()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
		EraseNameList();
		m_btRoll.SetWindowText(_T("开  始"));
	}
	else
	{
		m_bRoll = TRUE;
		StartThread();
		m_btRoll.SetWindowText(_T("停  止"));
	}
}

void CTalk915LuckyDrawProDlg::EraseNameList()
{
	if (m_listNames.size() <= 1)
	{
		return;
	}
	P_WINNING pWinner = new WINNING();
	pWinner->strWinner = m_strLuckyMan;
	pWinner->nRank = 1;
	m_listWinner.push_back(pWinner);
	list<CString>::iterator iter = m_listNames.begin();
	for (; iter != m_listNames.end(); ++iter)
	{
		if (m_strLuckyMan == *iter)
		{
			m_listNames.erase(iter);
			return;
		}
	}
}

BOOL CTalk915LuckyDrawProDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	DrawBkgnd(pDC);

	return TRUE;// CDialog::OnEraseBkgnd(pDC);
}

void CTalk915LuckyDrawProDlg::DrawBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);

	CImage m_Image;
	HRESULT hResult;
	hResult = m_Image.Load(m_strBkgndPath.GetBuffer(0));
	if (FAILED(hResult))
		return;

	HBITMAP hBitmap = m_Image.Detach();
	if (!hBitmap)
		return;

	BITMAP bmInfo;
	::GetObject(hBitmap, sizeof(BITMAP), &bmInfo);

	HDC hMemDC = NULL;
	hMemDC = CreateCompatibleDC(pDC->m_hDC);
	if (!hMemDC)
		return;

	HBITMAP hOldBitmap = NULL;
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	if (!hOldBitmap)
		return;

	BOOL bResult = FALSE;
	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	if (StretchBlt(pDC->m_hDC, rc.left, rc.top, rc.Width(), rc.Height(), hMemDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY))
		bResult = TRUE;

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
}

HBRUSH CTalk915LuckyDrawProDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_NAME:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(248, 227, 192));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CTalk915LuckyDrawProDlg::ThreadProcMain(void)
{
	while (true)
	{
		for (auto & name : m_listNames)
		{
			PostMessage(WM_DISPLAYNAME, (WPARAM)name.AllocSysString());
			if (!m_bRoll)
			{
				m_strLuckyMan = name;
				return;
			}
			Sleep(67);
		}
	}
}

void CTalk915LuckyDrawProDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	//__super::OnClose();
}

LRESULT CTalk915LuckyDrawProDlg::RollName(WPARAM wParam, LPARAM lParam)
{
	BSTR bName = (BSTR)wParam;
	CString name(bName);
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(name);
	CRect crc;
	GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(&crc);
	//转换为相对坐标
	ScreenToClient(&crc);
	//刷新指定区域,注意第2个参数为真,即刷新背景  
	InvalidateRect(&crc, TRUE);
	return S_OK;
}

CString CTalk915LuckyDrawProDlg::GetModuleDir()
{
	HMODULE module = GetModuleHandle(0);
	TCHAR pFileName[MAX_PATH] = { 0 };
	GetModuleFileName(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos);
}


void CTalk915LuckyDrawProDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	//防止不小心点到ESC退出
	//__super::OnCancel();
}


void CTalk915LuckyDrawProDlg::OnBnClickedButtonClose()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	__super::OnCancel();
}


void CTalk915LuckyDrawProDlg::OnBnClickedButtonMin()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(_T(""));
	CRect crc;
	GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(&crc);
	//转换为相对坐标
	ScreenToClient(&crc);
	//刷新指定区域,注意第2个参数为真,即刷新背景  
	InvalidateRect(&crc, TRUE);
	//判断是否最小化
	if (!IsIconic())
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}
