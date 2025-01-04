
// Glim_CodingTest_1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Glim_CodingTest_1.h"
#include "Glim_CodingTest_1Dlg.h"
#include "afxdialogex.h"

#include <thread>
#include <direct.h> // _mkdir 사용
#include <map>
#include <io.h> // _access 함수 사용을 위한 헤더
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
// 콘솔 출력 확인
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

using namespace std;
bool m_bAction; 
map<CString, CPoint> posMap; // 파일명과 중심점 저장

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


// CGlimCodingTest1Dlg 대화 상자



CGlimCodingTest1Dlg::CGlimCodingTest1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_CODINGTEST_1_DIALOG, pParent)
	, m_nX1(0)
	, m_nY1(0)
	, m_nY2(0)
	, m_nX2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimCodingTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_nX1);
	DDX_Text(pDX, IDC_EDIT1, m_nY1);
	DDX_Text(pDX, IDC_EDIT3, m_nY2);
	DDX_Text(pDX, IDC_EDIT4, m_nX2);
}

BEGIN_MESSAGE_MAP(CGlimCodingTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_END, &CGlimCodingTest1Dlg::OnBnClickedBtnEnd)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGlimCodingTest1Dlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimCodingTest1Dlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGlimCodingTest1Dlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CGlimCodingTest1Dlg 메시지 처리기

BOOL CGlimCodingTest1Dlg::OnInitDialog()
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

void CGlimCodingTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGlimCodingTest1Dlg::OnPaint()
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
HCURSOR CGlimCodingTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


///////////////////////화면종료 버튼///////////////////////////// 
void CGlimCodingTest1Dlg::OnBnClickedBtnEnd()
{
	// 창 종료 확인 메시지
	if (AfxMessageBox(_T("프로그램을 종료하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		// 프로그램 종료
		CDialogEx::OnOK();
	}
}

///////////////////////원 그리기///////////////////////////// 
void CGlimCodingTest1Dlg::OnBnClickedBtnDraw()
{
	try
	{	
		UpdateData(); // UI에서 좌표 가져오기

		  // 유효성 검사
        if (!validImgPos(m_nX1, m_nY1) || !validImgPos(m_nX2, m_nY2))
        {           			
            return; 
        }

		// 이미지 초기화
		if (m_image != NULL) 
		{
			m_image.Destroy();
		}


		if (m_image.Create(640, -480, 8) == NULL) {
			AfxMessageBox(_T("이미지를 생성할 수 없습니다!"));
			return;
		}

		int radius = rand() % 50 + 10; // 랜덤 반지름 (10~60)
		
		drawCircle(m_nX1, m_nY1, radius);

		//UpdateDisplay();
	}
	catch (exception ex)
	{
		CString errorMsg;
		errorMsg.Format(_T("Draw 오류 발생: %S"), ex.what());
		AfxMessageBox(errorMsg);
	}

}

///////////////////////원 이동 후 이미지 저장///////////////////////////// 
void CGlimCodingTest1Dlg::OnBnClickedBtnAction()
{	
	// 화면 초기화
	Invalidate(); 
	UpdateWindow(); 

	UpdateData();

	if (m_bAction) // 이미 실행 중인 경우
	{
		AfxMessageBox(_T("Action 작업이 이미 실행 중입니다."));		
		return;
	}

	if (!validImgPos(m_nX1, m_nY1) || !validImgPos(m_nX2, m_nY2)) 
	{
		return; 
	}

	m_bAction = true;
	GetDlgItem(IDC_BTN_ACTION)->EnableWindow(false); // Action 버튼 비활성화
	GetDlgItem(IDC_BTN_DRAW)->EnableWindow(false); // Draw 버튼 비활성화
	GetDlgItem(IDC_BTN_OPEN)->EnableWindow(false); // Open 버튼 비활성화

	try {

		thread([this]()
		{
			int x = m_nX1, y = m_nY1;
			int dx = (m_nX2 - m_nX1) / 20, dy = (m_nY2 - m_nY1) / 20; // 이동 간격

			// "image" 폴더 생성
			_mkdir("image");

			for (int i = 0; i <= 20; i++)
			{
				CString fileName, filePath;
				fileName.Format(_T("frame_%02d.bmp"), i); // 파일명만 생성
				filePath.Format(_T("image\\%s"), fileName); // 파일 경로 생성

				drawCircle(x, y, rand() % 50 + 10); // 이동하며 원 그리기
				m_image.Save(filePath);        // 이미지 저장

				// 중심 좌표를 맵에 저장
				posMap[fileName] = CPoint(x, y);

				x += dx;
				y += dy;
				Sleep(200); // 0.2초 대기
			}
				
			m_bAction = false;
			GetDlgItem(IDC_BTN_ACTION)->EnableWindow(true); // Action 버튼 활성화
			GetDlgItem(IDC_BTN_DRAW)->EnableWindow(true); // Action 버튼 비활성화
			GetDlgItem(IDC_BTN_OPEN)->EnableWindow(true); // Action 버튼 비활성화
			// posMap 출력 
			for (auto pair : posMap)
			{					
				cout << "pair.first>>" << pair.first.GetString()<< " X>> " << pair.second.x << " Y>> " << pair.second.y << endl;				
			}
		}).detach(); // UI 프리징 방지
	}
	catch (exception ex)
	{
		CString errorMsg;
		errorMsg.Format(_T("Action오류: %s"),ex.what());
		AfxMessageBox(errorMsg);
	}
}

///////////////////////원 이미지 불러오고 중심좌표 출력///////////////////////////// 
void CGlimCodingTest1Dlg::OnBnClickedBtnOpen()
{
	CString folderPath = _T("image");

	// CStringA로 ANSI 문자열 변환
	CStringA folderPathA(folderPath);

	// "image" 폴더 존재 확인
	if (_access(folderPathA, 0) != 0)
	{
		AfxMessageBox(_T("\"image\" 폴더가 존재하지 않습니다!"));
		return;
	}

	// 폴더가 비어 있는지 확인
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(folderPath + _T("\\*.*"), &findFileData);
	bool hasFiles = false;

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do {
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			{
				hasFiles = true;
				break;
			}
		} while (FindNextFile(hFind, &findFileData));
		FindClose(hFind);
	}

	if (!hasFiles) 
	{
		AfxMessageBox(_T("\"image\" 폴더에 파일이 없습니다!"));
		return;
	}

	// 파일 탐색기 대화상자
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg||"));

	if (dlg.DoModal() == IDOK) 
	{
		CString filePath = dlg.GetPathName();
		CString fileName = dlg.GetFileName(); // 선택한 파일명 저장		

		// 파일명이 "frame_"으로 시작하는지 확인
		if (fileName.Left(6).CompareNoCase(_T("frame_")) != 0)
		{
			AfxMessageBox(_T("파일 이름이 'frame_'로 시작하지 않습니다. 올바른 파일을 선택해주세요."));
			// 파일 확장자 검사
			CString extension = filePath.Right(4).MakeLower(); // 마지막 4글자를 소문자로 변환
			if (extension != _T(".bmp"))
			{
				AfxMessageBox(_T("해당 파일은 .bmp 형식이 아닙니다. 올바른 .bmp 파일을 선택해주세요."));				
			}
			return;
		}

		CImage img;
		if (FAILED(img.Load(filePath))) 
		{
			AfxMessageBox(_T("이미지 로드 실패!"));
			return;
		}

		CClientDC dc(this);
		img.Draw(dc.GetSafeHdc(), 0, 0, img.GetWidth(), img.GetHeight());


		// posMap에서 중심 좌표 검색
		auto it = posMap.find(fileName);
		if (it != posMap.end()) 
		{
			// 중심 좌표를 가져옴
			CPoint center = it->second;

			// 중심 좌표에 X 표시
			CBrush brush(RGB(255, 0, 0)); // 빨간색
			CBrush* oldBrush = dc.SelectObject(&brush);

			dc.MoveTo(center.x - 5, center.y - 5);
			dc.LineTo(center.x + 5, center.y + 5);
			dc.MoveTo(center.x - 5, center.y + 5);
			dc.LineTo(center.x + 5, center.y - 5);

			// 중심 좌표값 표시
			CString text;
			text.Format(_T("(%d, %d)"), center.x, center.y);
			dc.TextOut(center.x + 10, center.y + 10, text);

			dc.SelectObject(oldBrush);

			// StaticText에 중심좌표 출력
			CString centerXText, centerYText;
			centerXText.Format(_T("%d"), center.x);
			centerYText.Format(_T("%d"), center.y);

			SetDlgItemText(IDC_STATIC_CENTERX, centerXText); // X 좌표 출력
			SetDlgItemText(IDC_STATIC_CENTERY, centerYText); // Y 좌표 출력
		}
		else 
		{
			AfxMessageBox(_T("중심 좌표 정보를 찾을 수 없습니다!"));
		}
	}
}

void CGlimCodingTest1Dlg::drawCircle(int x, int y, int radius)
{
	int nWidth = 640, nHeight = 480, nBpp = 8;
	try 
	{
		// 기존 이미지 제거 후 생성
		if (m_image != NULL)
		{
			m_image.Destroy();
		}
		
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

		// 원 그리기
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
	}
	catch (exception ex)
	{
		CString errorMsg;
		errorMsg.Format(_T("drawCircle오류: %s"),ex.what());
		AfxMessageBox(errorMsg);
	}
}
BOOL CGlimCodingTest1Dlg::validImgPos(int x, int y)
{
	int nWidth = 640;
	int nHeight = 480;
	
	try
	{
		// 시작 좌표와 종료 좌표 예외 처리
		if (m_nX1 < 0 || m_nX1 >= nWidth || m_nY1 < 0 || m_nY1 >= nHeight)
		{
			AfxMessageBox(_T("시작 좌표가 이미지 범위(640 * 480)를 벗어났습니다."));
			return false;
		}

		if (m_nX2 < 0 || m_nX2 >= nWidth || m_nY2 < 0 || m_nY2 >= nHeight)
		{
			AfxMessageBox(_T("종료 좌표가 이미지 범위(640 * 480)를 벗어났습니다."));
			return false;
		}

		if (m_nX1 == m_nX2 && m_nY1 == m_nY2)
		{
			AfxMessageBox(_T("시작 좌표와 종료 좌표는 동일할 수 없습니다."));
			return false;
		}

		return true; 
	}
	catch (exception ex)
	{
		CString errorMsg;
		errorMsg.Format(_T("validImgPos오류: %s"),ex.what());
		AfxMessageBox(errorMsg);
	}
}

void CGlimCodingTest1Dlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
	CString initText; // 중심 좌표 초기화
	initText = "0";
	SetDlgItemText(IDC_STATIC_CENTERX, initText); // X 좌표 출력
	SetDlgItemText(IDC_STATIC_CENTERY, initText); // Y 좌표 출력
}

void CGlimCodingTest1Dlg::OnOK()
{
	// Enter 키가 눌렸을 때 아무 작업도 하지 않도록 재정의
	// CDialogEx::OnOK();를 호출하지 않습니다.
}