#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
//... _PTR 关于32位和64位的自适应变量
//hInstance资源总管句柄
//WM..	Windows Message
//MB..	Windows Box
//ID..	identifer
INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR s[256];
	wsprintf(s, _T("uMsg=%d,wParam=%d,lParam=%d\n"),uMsg, wParam, lParam);
	OutputDebugString(s);
	switch (uMsg)
	{
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>待完善
	//分支：丢文件操作
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		hDrop = hDrop;
	}
		MessageBox(hwndDlg,_T("好"),_T("提示："),0);
		
	case WM_COMMAND://命令 按钮 菜单项  工具栏按钮  （快捷键）
		if (LOWORD(wParam) == IDCANCEL)
			EndDialog(hwndDlg, IDCANCEL);
		switch (LOWORD(wParam))
		{
		//case IDC_CALC:
		//case IDC_CALC2:
		//case IDC_CALC3:
		case IDC_CALC4:
			// 加
			//	MessageBox(NULL, _T("计算"), _T("提示："), 0);
			int nLeft = GetDlgItemInt(hwndDlg, IDC_LEFT, NULL, TRUE);
			int nRight = GetDlgItemInt(hwndDlg, IDC_RIGHT, NULL, TRUE);
			int nRes = nLeft + nRight;
			SetDlgItemInt(hwndDlg, IDC_RESULT, nRes, TRUE);

			//减
			//	MessageBox(NULL, _T("计算"), _T("提示："), 0);
			int nLeft2 = GetDlgItemInt(hwndDlg, IDC_LEFT2, NULL, TRUE);
			int nRight2 = GetDlgItemInt(hwndDlg, IDC_RIGHT2, NULL, TRUE);
			int nRes2 = nLeft2 - nRight2;
			SetDlgItemInt(hwndDlg, IDC_RESULT2, nRes2, TRUE);

			//乘
			//	MessageBox(NULL, _T("计算"), _T("提示："), 0);
			int nLeft3 = GetDlgItemInt(hwndDlg, IDC_LEFT3, NULL, TRUE);
			int nRight3 = GetDlgItemInt(hwndDlg, IDC_RIGHT3, NULL, TRUE);
			int nRes3 = nLeft3 * nRight3;
			SetDlgItemInt(hwndDlg, IDC_RESULT3, nRes3, TRUE);

			//除
			//	MessageBox(NULL, _T("计算"), _T("提示："), 0);
			int nLeft4 = GetDlgItemInt(hwndDlg, IDC_LEFT4, NULL, TRUE);
			int nRight4 = GetDlgItemInt(hwndDlg, IDC_RIGHT4, NULL, TRUE);
			int nRes4 = nLeft4 / nRight4;
			SetDlgItemInt(hwndDlg, IDC_RESULT4, nRes4, TRUE);
		break;
		}
		break;
	}
	return FALSE;
}

int WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	INT_PTR n = DialogBox( hInstance,(LPCTSTR)IDD_MAIN_DLG,NULL,theProc);
	//if(n == ...）你点击了。。。
	return 0;
}
