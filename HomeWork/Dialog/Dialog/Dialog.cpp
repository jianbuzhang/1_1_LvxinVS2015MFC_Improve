#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
//... _PTR 关于32位和64位的自适应变量
//hInstance资源总管句柄
//WM_.. Windows Message
//MB_.. Message Box
//ID_ Identify

INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR s[256];
	wsprintf(s, _T("uMsg=%d,wParam=%d,lParam=%d\n"),uMsg, wParam, lParam);
	OutputDebugString(s);
	switch (uMsg)
	{
	case WM_COMMAND://命令 按钮 菜单项 工具栏按钮 （快捷键）
		if (LOWORD(wParam) == IDCANCEL)
			EndDialog(hwndDlg, IDCANCEL);
		if (LOWORD(wParam) == IDC_CALC)
		{//minus sign
			BOOL bRet = FALSE;
			int nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT, &bRet, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT, &bRet, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT,  nLeft + nRight, TRUE);
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
	INT_PTR n = DialogBox( hInstance,(LPCTSTR)IDD_MAIN_DLG,NULL,	theProc	);
	return 0;
}
