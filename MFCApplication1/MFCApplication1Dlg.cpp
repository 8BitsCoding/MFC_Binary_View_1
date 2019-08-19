
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BIN_DATA_LIST, m_bin_data_list);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_BTN, &CMFCApplication1Dlg::OnBnClickedSelectBtn)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_font.CreatePointFont(128, L"굴림체");
	m_bin_data_list.SetFont(&m_font);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
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
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedSelectBtn()
{
	CFileDialog ins_dlg(TRUE);
	// TRUE : 파일열기
	// FALSE : 다른이름으로 저장

	if (IDOK == ins_dlg.DoModal()) {
		SetDlgItemText(IDC_PATH_STATIC, ins_dlg.GetPathName());
		m_bin_data_list.ResetContent();

		FILE * p_file = NULL;
		if (_wfopen_s(&p_file, ins_dlg.GetPathName(), L"rb") == 0) {
			unsigned char temp[24];
			//CString total_str, str;
			wchar_t str[128];

			int len = 24, line = 0, str_len;
			while (len == 24) {
				len = fread(temp, 1, 24, p_file);		// fread는 실제로 읽은 바이트만큼 리턴됨
				if (len > 0) {
					//total_str.Empty();
					str_len = swprintf_s(str, 128, L"%06d : ", line++);
					//total_str.Format(L"%06d : ", line++);
					for (int i = 0; i < 24; i++) {
						str_len += swprintf_s(str + str_len, 128 - str_len, L"%02X ", temp[i]);
					}
					m_bin_data_list.InsertString(-1, str);
				}
			}
			
			/*
			// CString Style
			unsigned char temp[24];
			CString total_str, str;

			int len = 24, line = 0;
			while (len == 24) {
				len = fread(temp, 1, 24, p_file);		// fread는 실제로 읽은 바이트만큼 리턴됨
				if (len > 0) {
					//total_str.Empty();
					total_str.Format(L"%06d : ", line++);
					for (int i = 0; i < 24; i++) {
						str.Format(L"%02X ", temp[i]);
						total_str += str;
					}
					m_bin_data_list.InsertString(-1, total_str);
				}
			}
			*/
			
			fclose(p_file);
		}
	}
}
