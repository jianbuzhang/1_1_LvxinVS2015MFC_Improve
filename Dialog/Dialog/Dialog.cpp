#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
//... _PTR ����32λ��64λ������Ӧ����
//hInstance��Դ�ܹܾ��

INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR s[256];
	wsprintf(s, _T("uMsg=%d,wParam=%d,lParam=%d\n"),uMsg, wParam, lParam);
	OutputDebugString(s);
	switch (uMsg)
	{
	case WM_COMMAND://�Ӵ��ڵĽ��� ���� ��ť �˵���
		if (LOWORD(wParam) == IDCANCEL)
			EndDialog(hwndDlg, IDCANCEL);
		if (LOWORD(wParam) == IDC_CALC)
		{
		//	MessageBox(NULL, _T("����"), _T("��ʾ��"), 0);
		}
		break;
	}
	return FALSE;
}

int WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	INT_PTR n = DialogBox( hInstance,(LPCTSTR)IDD_MAIN_DLG,
		NULL,		 theProc	);
	//if(n == ...�������ˡ�����
	return 0;
}
