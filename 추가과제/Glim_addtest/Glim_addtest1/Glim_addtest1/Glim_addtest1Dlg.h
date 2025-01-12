
// Glim_addtest1Dlg.h: 헤더 파일
//

#pragma once


// CGlimaddtest1Dlg 대화 상자
class CGlimaddtest1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimaddtest1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_ADDTEST1_DIALOG };
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
	DECLARE_MESSAGE_MAP()

	int cx1, cy1;
	int cx2, cy2;
	int cx3, cy3;
	
	CPoint m_Pos;
	CImage m_image;

private:
	void UpdateDisplay();
	void drawCircle(int x, int y, int radius);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnMove();
private:
	int m_nRadius;
	int m_nEdge;
	CString m_cx1;
	CString m_cy1;
	CString m_cx2;
	CString m_cy2;
	CString m_cx3;
	CString m_cy3;
	
	void OnOK();
	bool isInsideCircle(CPoint point, int centerX, int centerY, int radius);
	void clearCircle(); 
	void edgeCircle();


};
