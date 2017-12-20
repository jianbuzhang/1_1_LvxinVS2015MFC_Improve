#define  _CRT_NON_CONFORMING_SWPRINTFS
#define  _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
#include <	comutil.h>

//... _PTR ����32λ��64λ������Ӧ����
//hInstance��Դ�ܹܾ��
//WM_.. Windows Message
//MB_.. Message Box
//ID_ Identify
//�ַ���ת���� (ato.. _wto..
//����ת�����֣�wprintf (itoa ,_itow ����)

/*
���Ϊ�˰�float����CString,
ֻ��:
CString s;
float f= 5.345;
s.Format( "%f", f );
�����õ�
wsprintf��Windows API����֧�ָ����͸�ʽ�����
swprintf��C����ʱ������֧�ָ����͸�ʽ�������
*/

LPCTSTR MtoU(LPCSTR s)
{
	int nLenOfWideCharStr = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	//MultiByteToWideChar()�Ƕ��ֽ��ַ�����ַ�ת�����Ⱥ���;
		PWSTR pWideCharStr = new TCHAR[(nLenOfWideCharStr+1) *sizeof(WCHAR)];  //PWSTR�ǿ��ַ�ָ�����ͣ�HeadAlloc()�Ƕ��������ڴ棬GetProcessHeap()�ǻ�ȡ��ǰ���;
	MultiByteToWideChar(CP_ACP, 0, s, -1,  pWideCharStr, nLenOfWideCharStr);
	//wcscpy(lpUnicode, pWideCharStr);

	return pWideCharStr;
}

INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR s[256];
	wsprintf(s, _T("uMsg=%d,wParam=%d,lParam=%d\n"),uMsg, wParam, lParam);
	OutputDebugString(s);
	switch (uMsg)
	{
	case WM_COMMAND://���� ��ť �˵��� ��������ť ����ݼ���
		if (LOWORD(wParam) == IDCANCEL)
			EndDialog(hwndDlg, IDCANCEL);
		if (LOWORD(wParam) == IDC_CALC)
		{//minus sign
			TCHAR s[32];
			GetDlgItemText(hwndDlg, IDC_LEFT, s, _countof(s));
			double fLeft = _wtof(s);
			GetDlgItemText(hwndDlg, IDC_RIGHT, s, _countof(s));
			double fRight = _wtof(s);
			_stprintf(s,_T("%lf"), (fLeft + fRight));
			SetDlgItemText(hwndDlg, IDC_RESULT, s);
			//SetDlgItemInt(hwndDlg, IDC_RESULT, 1, TRUE);
		}
		if (LOWORD(wParam) == IDC_CALC2)
		{
			int nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT2, NULL, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT2, NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT2, nLeft - nRight, TRUE);
		}
		if (LOWORD(wParam) == IDC_CALC3)
		{
			int nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT3, NULL, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT3, NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT3, nLeft * nRight, TRUE);
		}
		if (LOWORD(wParam) == IDC_CALC4)
		{
			int nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT4, NULL, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT4, NULL, TRUE);
			if(nRight)
				SetDlgItemInt(hwndDlg, IDC_RESULT4, nLeft / nRight, TRUE);
		}
		break;
	}
	return FALSE;
}

int WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	char s[20] = "������ʦ";
	TCHAR s1[20];
	LPCTSTR p = MtoU(s);
	_stprintf(s1, _T("%0.3lf"), 9832.5324234);


	INT_PTR n = DialogBox( hInstance,(LPCTSTR)IDD_MAIN_DLG,NULL,	theProc	);
	return 0;
}
