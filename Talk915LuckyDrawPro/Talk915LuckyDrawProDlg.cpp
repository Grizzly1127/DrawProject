
// Talk915LuckyDrawProDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Talk915LuckyDrawPro.h"
#include "Talk915LuckyDrawProDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTalk915LuckyDrawProDlg �Ի���


#define WM_DISPLAYNAME (WM_USER+100)
CTalk915LuckyDrawProDlg::CTalk915LuckyDrawProDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTalk915LuckyDrawProDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CString strPath = GetModuleDir();
	m_strBkgndPath.Format(_T("%s\\background.jpg"), strPath);//���ñ���·��
	m_strNamePath.Format(_T("%s\\names.txt"), strPath);//��������·��
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


// CTalk915LuckyDrawProDlg ��Ϣ�������

BOOL CTalk915LuckyDrawProDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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

	m_font.CreatePointFont(500, _T("΢���ź�"));
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&m_font);
	m_fontBt.CreatePointFont(200, _T("΢���ź�"));
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

	m_btRoll.SetWindowText(_T("��  ʼ"));

	if (!ReadNameFromTxt())
	{
		OnClose();
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTalk915LuckyDrawProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		substr = strtok(NULL, szSplit);/*�ڵ�һ�ε���ʱ��strtok()����������str�ַ�����
								   ����ĵ����򽫲���str���ó�NULL��ÿ�ε��óɹ��򷵻ر��ָ��Ƭ�ε�ָ�롣*/
	}

	return TRUE;
}

void CTalk915LuckyDrawProDlg::OnBnClickedButtonStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
		EraseNameList();
		m_btRoll.SetWindowText(_T("��  ʼ"));
	}
	else
	{
		m_bRoll = TRUE;
		StartThread();
		m_btRoll.SetWindowText(_T("ͣ  ֹ"));
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_NAME:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(248, 227, 192));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	//ת��Ϊ�������
	ScreenToClient(&crc);
	//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���  
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
	// TODO:  �ڴ����ר�ô����/����û���
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	//��ֹ��С�ĵ㵽ESC�˳�
	//__super::OnCancel();
}


void CTalk915LuckyDrawProDlg::OnBnClickedButtonClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	__super::OnCancel();
}


void CTalk915LuckyDrawProDlg::OnBnClickedButtonMin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bRoll)
	{
		m_bRoll = FALSE;
		WaitForStop();
	}
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(_T(""));
	CRect crc;
	GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(&crc);
	//ת��Ϊ�������
	ScreenToClient(&crc);
	//ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���  
	InvalidateRect(&crc, TRUE);
	//�ж��Ƿ���С��
	if (!IsIconic())
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}
