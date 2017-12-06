#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
//... _PTR 关于32位和64位的自适应变量
//hInstance资源总管句柄
//WM_.. Windows Message
//MB_.. Message Box
//ID_ Identify
//H Handle （HWND HDROP HICON HCURSOR HDC...）
INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		TCHAR s[256];
		wsprintf(s, _T("uMsg=0x%08xwParam=%d,lParam=%d\n"), uMsg, wParam, lParam);
		OutputDebugString(s);
		return TRUE;

	case WM_CREATE://在窗口还未显示出来的时候执行
		MessageBox(hwndDlg, _T("Create"), _T("提示："), 0);
		return TRUE;
	case WM_MOUSEMOVE:
	{
		TCHAR s[64];
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		wsprintf(s, _T("x=%d,y=%d"), x, y);
		if (MK_SHIFT & wParam)//混合 | 判断某个位是否为1 &
			lstrcat(s, _T(" - Shift按下"));
		if (MK_CONTROL & wParam)//混合 | 判断某个位是否为1 &
			lstrcat(s, _T(" - Ctrl按下"));
		if (MK_LBUTTON & wParam)//混合 | 判断某个位是否为1 &
			lstrcat(s, _T(" - 左键拖动"));

		SetWindowText(hwndDlg, s);

		return TRUE;
	}
	case WM_LBUTTONDOWN:
	{
		TCHAR s[32];
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		wsprintf(s,_T("x=%d,y=%d"), x, y);
	//	MessageBox(hwndDlg, s ,_T("提示："), 0);
		return TRUE;
	}
	case WM_INITDIALOG://对话框专用
		//MoveWindow（居中）
	//	MessageBox(hwndDlg, _T("InitDialog"), _T("提示："), 0);
		return TRUE;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;//findfirst(..) ->记录集
		UINT nCount = DragQueryFile(hDrop, -1, NULL, 0);
			
		TCHAR s[256];
		if (nCount > 0)
		{
			DragQueryFile(hDrop,0, s, sizeof(s));
			hDrop = hDrop;
		}
	}
		break;
	case WM_COMMAND://命令 按钮 菜单项 工具栏按钮 （快捷键）
		if (LOWORD(wParam) == IDCANCEL)
			EndDialog(hwndDlg, IDCANCEL);
		switch (LOWORD(wParam))
		{
		case IDC_CALC:
		case IDC_CALC2:
		case IDC_CALC3:
		case IDC_CALC4:
			int nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT,NULL, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT,NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT, nLeft + nRight, TRUE);
			nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT2, NULL, TRUE);
			nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT2, NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT2, nLeft - nRight, TRUE);
			nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT3, NULL, TRUE);
			nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT3, NULL, TRUE);
			SetDlgItemInt(hwndDlg, IDC_RESULT3, nLeft * nRight, TRUE);
			nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT4, NULL, TRUE);
			nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT4, NULL, TRUE);
			if (nRight)
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
