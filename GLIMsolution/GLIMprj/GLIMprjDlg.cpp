
// GLIMprjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIMprj.h"
#include "GLIMprjDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <ctime>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGLIMprjDlg 대화 상자



CGLIMprjDlg::CGLIMprjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMPRJ_DIALOG, pParent)
	, m_nStartX(0)
	, m_nStartY(0)
	, m_nEndX(0)
	, m_nEndY(0)
	, m_nNowX(0)
	, m_nNowY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMprjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_START_X, m_nStartX);
	DDX_Text(pDX, IDC_EDIT_START_Y, m_nStartY);
	DDX_Text(pDX, IDC_EDIT_END_X, m_nEndX);
	DDX_Text(pDX, IDC_EDIT_END_Y, m_nEndY);
	DDX_Text(pDX, IDC_EDIT_NOW_X, m_nNowX);
	DDX_Text(pDX, IDC_EDIT_NOW_Y, m_nNowY);
}

BEGIN_MESSAGE_MAP(CGLIMprjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGLIMprjDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGLIMprjDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGLIMprjDlg::OnBnClickedBtnOpen)
	
END_MESSAGE_MAP()


// CGLIMprjDlg 메시지 처리기

BOOL CGLIMprjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMprjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGLIMprjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGLIMprjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGLIMprjDlg::OnBnClickedBtnDraw()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}

	UpdateData();
	nWidth = 650;
	nHeight = 650;
	nBpp = 8;
	srand(time(NULL));
	nRadius = rand() % 50 + 10;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
	DrawCircle(fm, m_nStartX, m_nStartY, nGray);
	UpdateDisplay();
}



void CGLIMprjDlg::OnBnClickedBtnAction()
{
	
	UpdateData(true);
	while (true)
	{
		if (m_nStartX != m_nEndX && m_nStartY != m_nEndY) 
		{
			MoveToDotX();
			MoveToDotY();
			Sleep(10);
		}		
		else if (m_nStartX != m_nEndX)
		{
			MoveToDotX();
			Sleep(10);
		}
		else if (m_nStartY != m_nEndY)
		{
			MoveToDotY();
			Sleep(10);
		}
		else
		{
			break;
		}

		srand(time(NULL));
		int nRandNum = rand() % 10000;
		CString strFile;
		strFile.Format(_T("../image/image%d(%d, %d).bmp"), nRandNum, m_nStartX, m_nStartY);
		m_image.Save(strFile);
	}
}



void CGLIMprjDlg::OnBnClickedBtnOpen()
{		
	TCHAR szFile[] = _T("모든파일(*.*)|*.*||");
	CClientDC dc(this);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFile);

	int nCount = 0;
	int nTotalX = 0;
	int nTotalY = 0;
	int nResultX = 0;
	int nResultY = 0;

	if (IDOK == dlg.DoModal())
	{
		CString PathName = dlg.GetPathName();

		if (m_image != NULL) 
		{
			m_image.Destroy();
		}
		m_image.Load(PathName);
		m_image.Draw(dc, 0, 0);

		unsigned char* fm = (unsigned char*)m_image.GetBits();
		int nPitch = m_image.GetPitch();
		for (int j = 0; j < 650; j++)
		{
			for (int i = 0; i < 650; i++)
			{
				if (fm[j * nPitch + i] == nGray)
				{
					nCount++;
					nTotalX += i;
					nTotalY += j;
					nResultX = nTotalX / nCount;
					nResultY = nTotalY / nCount;
				}
			}
		}

		CString strX;
		strX.Format(_T("%d"), nResultX);

		CString strY;
		strY.Format(_T("%d"), nResultY);

		SetDlgItemText(IDC_EDIT_NOW_X, strX);
		SetDlgItemText(IDC_EDIT_NOW_Y, strY);
		
		
		int nValueX = 0;
		int nValueY = 0;
		
		for (int j = nResultY - 5; j <= nResultY + 5; j++)
		{
			for (int i = nResultX - 5; i <= nResultX + 5; i++)
			{
				if (nValueY == nValueX)
				{
					UpdateDisplay();
					fm[j * nPitch + i] = 0xff;
				}
				nValueX++;
			}
			nValueX = 0;
			nValueY++;
		}

		nValueY = 0;
		nValueX = 0;

		for (int j = nResultY + 5; j >= nResultY - 6; j--)
		{
			for (int i = nResultX - 5; i <= nResultX + 6; i++)
			{
				if (nValueY == nValueX)
				{
					UpdateDisplay();
					fm[j * nPitch + i] = 0xff;
					
				}
				nValueX++;
			}
			nValueX = 0;
			nValueY++;
		}
		nValueY = 0;
		nValueX = 0;
	}
}



void CGLIMprjDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}



void CGLIMprjDlg::MoveToDotX()
{	
	nWidth = m_image.GetWidth();
	nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	DrawCircle(fm, m_nStartX, m_nStartY, 0xff);
	DrawCircle(fm, ++m_nStartX, m_nStartY, nGray);
	UpdateDisplay();
}



void CGLIMprjDlg::MoveToDotY()
{
	nWidth = m_image.GetWidth();
	nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	DrawCircle(fm, m_nStartX, m_nStartY, 0xff);
	DrawCircle(fm, m_nStartX, ++m_nStartY, nGray);
	UpdateDisplay();
}



void CGLIMprjDlg::DrawCircle(unsigned char* fm, int x, int y, int nGray)
{
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_image.GetPitch();

	for (int j = y - nRadius; j < y + nRadius; j++) {
		for (int i = x - nRadius; i < x + nRadius; i++) {
			if (j >= 0 && i >= 0 && j <652 && i < 652)
			{
				if (CheckinCircle(i, j, nCenterX, nCenterY, nRadius))
					fm[j * nPitch + i] = nGray;
			}
		}
	}	
}



bool CGLIMprjDlg::CheckinCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}