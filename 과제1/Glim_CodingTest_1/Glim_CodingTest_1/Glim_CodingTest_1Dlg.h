
// Glim_CodingTest_1Dlg.h: 헤더 파일
//

#pragma once


// CGlimCodingTest1Dlg 대화 상자
class CGlimCodingTest1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimCodingTest1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_CODINGTEST_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	CImage m_image; // 이미지 객체
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
private:
	int m_nX1;
	int m_nY1;
	int m_nY2;
	int m_nX2;
	

	void drawCircle(int x, int y, int radius); 
	BOOL validImgPos(int x, int y);            
	void UpdateDisplay();                      
	void OnOK();

};
