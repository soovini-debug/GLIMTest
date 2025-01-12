
// Glim_addtest1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Glim_addtest1.h"
#include "Glim_addtest1Dlg.h"
#include "afxdialogex.h"

#include <typeinfo>
#include <iostream>
#include <string>
#include <thread>


#ifdef _DEBUG
#define new DEBUG_NEW
// 콘솔 출력 확인
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif



using namespace std;

int m_nClick=0;
int nWidth = 720, nHeight = 540, nBpp = 8;
bool m_bThread = false;

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


// CGlimaddtest1Dlg 대화 상자



CGlimaddtest1Dlg::CGlimaddtest1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_ADDTEST1_DIALOG, pParent)
	, m_nRadius(0)
	, m_nEdge(0)
	, m_cx1(_T(""))
	, m_cy1(_T(""))
	, m_cx2(_T(""))
	, m_cy2(_T(""))
	, m_cx3(_T(""))
	, m_cy3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimaddtest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_nRadius);
	DDX_Text(pDX, IDC_EDIT_EDGE, m_nEdge);
	DDX_Text(pDX, IDC_STATIC_CX1, m_cx1);
	DDX_Text(pDX, IDC_STATIC_CY1, m_cy1);
	DDX_Text(pDX, IDC_STATIC_CX2, m_cx2);
	DDX_Text(pDX, IDC_STATIC_CY2, m_cy2);
	DDX_Text(pDX, IDC_STATIC_CX3, m_cx3);
	DDX_Text(pDX, IDC_STATIC_CY3, m_cy3);
}

BEGIN_MESSAGE_MAP(CGlimaddtest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_INIT, &CGlimaddtest1Dlg::OnBnClickedBtnInit)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_MOVE, &CGlimaddtest1Dlg::OnBnClickedBtnMove)
	END_MESSAGE_MAP()


// CGlimaddtest1Dlg 메시지 처리기 Dialog 초기실행 

BOOL CGlimaddtest1Dlg::OnInitDialog()
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

void CGlimaddtest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGlimaddtest1Dlg::OnPaint()
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
HCURSOR CGlimaddtest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGlimaddtest1Dlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

//////////////////////////////////////////////////////////////// 마우스 왼쪽 버튼 클릭으로 정원 그리기
void CGlimaddtest1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	UpdateData();

	if (m_bThread)
	{
		// 쓰레드 실행 중일 때는 이벤트 무시
		return;
	}

	if (m_nRadius <= 0)
	{
		AfxMessageBox(_T("반지름 크기를 입력하세요."));
		// Edit Control에 Focus 주기
		GetDlgItem(IDC_EDIT_RADIUS)->SetFocus();

		return;
	}

	if (m_nEdge <= 0)
	{
		AfxMessageBox(_T("가장자리 두께를 입력하세요."));
		// Edit Control에 Focus 주기
		GetDlgItem(IDC_EDIT_EDGE)->SetFocus();

		return;
	}
	else if (m_nEdge > 20)
	{
		AfxMessageBox(_T("가장자리 두께는 20 이하로 입력하세요."));
		// Edit Control에 Focus 주기
		GetDlgItem(IDC_EDIT_EDGE)->SetFocus();

		return;
	}

	if (point.x < 0 || point.x >= nWidth || point.y < 0 || point.y >= nHeight)
	{
		AfxMessageBox(_T("클릭한 좌표가 화면 범위(720 * 540)를 벗어났습니다."));
		return;
	}

	m_nClick++;

	
	int x1, y1;

	if (m_nClick == 1)
	{
		m_cx1.Format(_T("%d"), point.x);
		m_cy1.Format(_T("%d"), point.y);

		cout << "클릭 1 cx1 >> " << m_cx1 << ", cy1 >>" << m_cy1 << endl;

		SetDlgItemText(IDC_STATIC_CX1, m_cx1);
		SetDlgItemText(IDC_STATIC_CY1, m_cy1);

		x1 = _ttoi(m_cx1); // Cstring -> int 형변환
		y1 = _ttoi(m_cy1);		

		drawCircle(x1, y1, m_nRadius);
	}
	else if (m_nClick == 2)
	{
		m_cx2.Format(_T("%d"), point.x);
		m_cy2.Format(_T("%d"), point.y);

		cout << "클릭 2 cx2 >> " << m_cx2 << ", cy2 >>" << m_cy2 << endl;

		SetDlgItemText(IDC_STATIC_CX2, m_cx2);
		SetDlgItemText(IDC_STATIC_CY2, m_cy2);
		x1 = _ttoi(m_cx2); // Cstring -> int 형변환
		y1 = _ttoi(m_cy2);

		drawCircle(x1, y1, m_nRadius);
	}
	else if (m_nClick == 3)
	{
		m_cx3.Format(_T("%d"), point.x);
		m_cy3.Format(_T("%d"), point.y);

		cout << "클릭 3 cx3 >> " << m_cx3 << ", cy3 >>" << m_cy3 << endl;

		SetDlgItemText(IDC_STATIC_CX3, m_cx3);
		SetDlgItemText(IDC_STATIC_CY3, m_cy3);
		x1 = _ttoi(m_cx3); // Cstring -> int 형변환
		y1 = _ttoi(m_cy3);

		drawCircle(x1, y1, m_nRadius);
	}
	
	
	CDialogEx::OnLButtonDown(nFlags, point); 
}
//////////////////////////////////////////////////////////////// 클릭한 정원 그리기
void CGlimaddtest1Dlg::drawCircle(int x, int y, int radius)
{
	// cout << "m_nRadius >> " << m_nRadius << " m_nEdge >> " << m_nEdge << endl;
	
	if (m_image == NULL)
	{		
		// 이미지 생성 및 초기화
		m_image.Create(nWidth, -nHeight, nBpp);

		// 색상 테이블 설정
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);

		unsigned char* fm = (unsigned char*)m_image.GetBits();
		memset(fm, 0xff, nWidth * nHeight); // 전체 흰색
	}
	
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int nPitch = m_image.GetPitch();

	for (int j = y - radius; j <= y + radius; j++)
	{
		for (int i = x - radius; i <= x + radius; i++)
		{
			// 배열 접근 방어
			if (j < 0 || j >= nHeight || i < 0 || i >= nWidth)
				continue;
			// 원 내부인지 확인
			if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
			{
				fm[j * nPitch + i] = 80; // 회색
			}
		}
	}
	UpdateDisplay();
	
	if (m_nClick >= 3)
	{
		edgeCircle();
	}
	
}
//////////////////////////////////////////////////////////////// 세점을 지나는 정원 그리기
void CGlimaddtest1Dlg::edgeCircle()
{
	//UpdateData();

	int x1, y1, x2, y2, x3, y3;
	x1 = _ttoi(m_cx1);
	y1 = _ttoi(m_cy1);
	x2 = _ttoi(m_cx2);
	y2 = _ttoi(m_cy2);
	x3 = _ttoi(m_cx3);
	y3 = _ttoi(m_cy3);

	cout << "x1 >>" << x1 << "y2 >> " << y1 << endl;
	cout << "x2 >>" << x2 << "y3 >> " << y2 << endl;
	cout << "x3 >>" << x3 << "y3 >> " << y3 << endl;

	/*	double d1 = (x2-x1) / (y2-y1);
		double d2 = (x3 - x2) / (y3 - y2);
		cout << "d1 기울기 >> " << d1 << endl;
		cout << "d2 기울기 >> " << d2 << endl;*/


		// 원의 중점 구하기		
	double dca = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

	double dcx = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) +
		(x3 * x3 + y3 * y3) * (y1 - y2)) / (2 * dca);
	double dcy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) +
		(x3 * x3 + y3 * y3) * (x2 - x1)) / (2 * dca);

	cout << "cx >> " << dcx << " cy >> " << dcy << endl;

	// 원의 반지름 구하기 r은 루트 
	double r = sqrt((x2 - dcx) * (x2 - dcx) + (y2 - dcy) * (y2 - dcy));
	cout << "원의 반지름 >> " << r << endl;

	int radius = r;
	int cx = dcx;
	int cy = dcy;
	cout << "radius 의 값은 >> " << radius << endl;

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int nPitch = m_image.GetPitch();

	// 가장자리 그리기
	for (int j = cy - radius; j <= cy + radius; j++)
	{
		for (int i = cx - radius; i <= cx + radius; i++)
		{
			// 배열 접근 방어
			if (j < 0 || j >= nHeight || i < 0 || i >= nWidth)
				continue;
			// 원 내부인지 확인
			if ((i - cx) * (i - cx) + (j - cy) * (j - cy) <= radius * radius
				&& (i - cx) * (i - cx) + (j - cy) * (j - cy) >= (radius - m_nEdge) * (radius - m_nEdge))
			{
				fm[j * nPitch + i] = 80;
			}

		}
	}
	UpdateDisplay();
}

void CGlimaddtest1Dlg::OnOK()
{
	// Enter 키가 눌렸을 때 아무 작업도 하지 않도록 재정의
	// CDialogEx::OnOK();를 호출하지 않습니다.
}
//////////////////////////////////////////////////////////////// 초기화 버튼 클릭 이벤트
void CGlimaddtest1Dlg::OnBnClickedBtnInit()
{
	UpdateData();

	if (AfxMessageBox(_T("초기화 하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (m_bThread)
		{
			m_bThread = false; 

			Sleep(1000); 
		}

		GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_EDGE)->EnableWindow(true);

		m_cx1.Format(_T("%d"), 0);
		m_cy1.Format(_T("%d"), 0);
		m_cx2.Format(_T("%d"), 0);
		m_cy2.Format(_T("%d"), 0);
		m_cx3.Format(_T("%d"), 0);
		m_cy3.Format(_T("%d"), 0);

		clearCircle();
		m_image.Destroy();

		m_nClick = 0;
		m_nRadius = 0;
		m_nEdge = 0;

		UpdateData(FALSE);
	}
}
//////////////////////////////////////////////////////////////// 클릭한 정원 드래그 이벤트 
void CGlimaddtest1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	UpdateData();

	if (m_nClick >= 3)
	{
		/*CString sPoint;
		sPoint.Format(_T("클릭한 좌표 값: (%d, %d)"), point.x, point.y);
		AfxMessageBox(sPoint);*/

		if (isInsideCircle(point, _ttoi(m_cx1), _ttoi(m_cy1), m_nRadius))
		{
			//AfxMessageBox(_T("첫 번째 원 안에 포함됩니다."));

			m_cx1.Format(_T("%d"), point.x);
			m_cy1.Format(_T("%d"), point.y);
			
			//drawCircle(_ttoi(m_cx1), _ttoi(m_cy1), m_nRadius);
			UpdateData(FALSE);

			clearCircle();
			drawCircle(_ttoi(m_cx1), _ttoi(m_cy1), m_nRadius);
			drawCircle(_ttoi(m_cx2), _ttoi(m_cy2), m_nRadius);
			drawCircle(_ttoi(m_cx3), _ttoi(m_cy3), m_nRadius);
		}
		else if (isInsideCircle(point, _ttoi(m_cx2), _ttoi(m_cy2), m_nRadius))
		{
			//AfxMessageBox(_T("두 번째 원 안에 포함됩니다."));

			m_cx2.Format(_T("%d"), point.x);
			m_cy2.Format(_T("%d"), point.y);

			UpdateData(FALSE);

			clearCircle();
			drawCircle(_ttoi(m_cx1), _ttoi(m_cy1), m_nRadius);
			drawCircle(_ttoi(m_cx2), _ttoi(m_cy2), m_nRadius);
			drawCircle(_ttoi(m_cx3), _ttoi(m_cy3), m_nRadius);

		}
		else if (isInsideCircle(point, _ttoi(m_cx3), _ttoi(m_cy3), m_nRadius))
		{
			//AfxMessageBox(_T("세 번째 원 안에 포함됩니다."));

			m_cx3.Format(_T("%d"), point.x);
			m_cy3.Format(_T("%d"), point.y);

			UpdateData(FALSE);

			clearCircle();
			drawCircle(_ttoi(m_cx1), _ttoi(m_cy1), m_nRadius);
			drawCircle(_ttoi(m_cx2), _ttoi(m_cy2), m_nRadius);
			drawCircle(_ttoi(m_cx3), _ttoi(m_cy3), m_nRadius);

		}
		
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}
//////////////////////////////////////////////////////////////// 원 안의 좌표인지 검사 => 유클리드 거리 
bool CGlimaddtest1Dlg::isInsideCircle(CPoint point, int centerX, int centerY, int radius)
{
	int dx = point.x - centerX;
	int dy = point.y - centerY;
	int distance = dx * dx + dy * dy;

	return distance <= (radius * radius);
}
//////////////////////////////////////////////////////////////// 원 지우기
void CGlimaddtest1Dlg::clearCircle()
{
	// 색상 테이블 설정
	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	}
	m_image.SetColorTable(0, 256, rgb);

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, nWidth * nHeight); // 전체 흰색

	UpdateDisplay(); // 화면 업데이트
}
//////////////////////////////////////////////////////////////// 랜덤 이동 버튼 이벤트 
void CGlimaddtest1Dlg::OnBnClickedBtnMove()
{
	UpdateData();
	
	if (m_image != NULL)
	{
		m_cx1.Format(_T("%d"), 0);
		m_cy1.Format(_T("%d"), 0);
		m_cx2.Format(_T("%d"), 0);
		m_cy2.Format(_T("%d"), 0);
		m_cx3.Format(_T("%d"), 0);
		m_cy3.Format(_T("%d"), 0);

		clearCircle();
		m_image.Destroy();

		m_nClick = 0;
		UpdateData(FALSE);
	}

	if (m_nRadius <= 0)
	{
		AfxMessageBox(_T("반지름 크기를 입력하세요."));
		// Edit Control에 Focus 주기
		GetDlgItem(IDC_EDIT_RADIUS)->SetFocus();

		return;
	}

	if (m_nEdge <= 0)
	{
		AfxMessageBox(_T("가장자리 두께를 입력하세요."));
		// Edit Control에 Focus 주기
		GetDlgItem(IDC_EDIT_EDGE)->SetFocus();

		return;
	}
	else if (m_nEdge > 20)
	{
		AfxMessageBox(_T("가장자리 두께는 20 이하로 입력하세요."));
		// Edit Control에 Focus 주기
		GetDlgItem(IDC_EDIT_EDGE)->SetFocus();

		return;
	}

	thread([this]()
		{
			GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(false); // 반지름 비활성화
			GetDlgItem(IDC_EDIT_EDGE)->EnableWindow(false); // 가장자리 비활성화

			m_bThread = true;

			for (int i = 0; i < 10 && m_bThread; i++)
			{
				//cout << "i >> " << i << endl;

				/*CString x1, y1;*/
				int randx = rand() % nWidth;
				int randy = rand() % nHeight;
				m_cx1.Format(_T("%d"), randx);
				m_cy1.Format(_T("%d"), randy);
			/*	x1.Format(_T("%d"), randx);
				y1.Format(_T("%d"), randy);*/
				cout << "랜덤 x1 >> " << _ttoi(m_cx1) << endl;
				cout << "랜덤 y1 >> " << _ttoi(m_cy1) << endl;
				SetDlgItemText(IDC_STATIC_CX1, m_cx1);
				SetDlgItemText(IDC_STATIC_CY1, m_cy1);

				drawCircle(_ttoi(m_cx1), _ttoi(m_cy1), m_nRadius);

				randx = rand() % nWidth;
				randy = rand() % nHeight;
				m_cx2.Format(_T("%d"), randx);
				m_cy2.Format(_T("%d"), randy);
				/*x1.Format(_T("%d"), randx);
				y1.Format(_T("%d"), randy);*/
				cout << "랜덤 x1 >> " << _ttoi(m_cx2) << endl;
				cout << "랜덤 y1 >> " << _ttoi(m_cy2) << endl;
				SetDlgItemText(IDC_STATIC_CX2, m_cx2);
				SetDlgItemText(IDC_STATIC_CY2, m_cy2);

				drawCircle(_ttoi(m_cx2), _ttoi(m_cy2), m_nRadius);


				randx = rand() % nWidth;
				randy = rand() % nHeight;
				m_cx3.Format(_T("%d"), randx);
				m_cy3.Format(_T("%d"), randy);
				/*x1.Format(_T("%d"), randx);
				y1.Format(_T("%d"), randy);*/
				cout << "랜덤 x1 >> " << _ttoi(m_cx3) << endl;
				cout << "랜덤 y1 >> " << _ttoi(m_cy3) << endl;
				SetDlgItemText(IDC_STATIC_CX3, m_cx3);
				SetDlgItemText(IDC_STATIC_CY3, m_cy3);

				drawCircle(_ttoi(m_cx3), _ttoi(m_cy3), m_nRadius);

				edgeCircle();
				
				Sleep(2000);
				clearCircle();				
			}
			m_bThread = false;
			clearCircle();
		}).detach();
	GetDlgItem(IDC_EDIT_RADIUS)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_EDGE)->EnableWindow(true);
}
