#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
//... _PTR ����32λ��64λ������Ӧ����
//hInstance��Դ�ܹܾ��
//WM_.. Windows Message
//MB_.. Message Box
//ID_ Identify
//H Handle ��HWND HDROP HICON HCURSOR HDC...��
INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		TCHAR s[256];
		wsprintf(s, _T("uMsg=0x%08xwParam=%d,lParam=%d\n"), uMsg, wParam, lParam);
		OutputDebugString(s);
		return TRUE;

	case WM_CREATE://�ڴ��ڻ�δ��ʾ������ʱ��ִ��
		MessageBox(hwndDlg, _T("Create"), _T("��ʾ��"), 0);
		return TRUE;
	case WM_MOUSEMOVE:
	{
		TCHAR s[64];
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		wsprintf(s, _T("x=%d,y=%d"), x, y);
		if (MK_SHIFT & wParam)//��� | �ж�ĳ��λ�Ƿ�Ϊ1 &
			lstrcat(s, _T(" - Shift����"));
		if (MK_CONTROL & wParam)//��� | �ж�ĳ��λ�Ƿ�Ϊ1 &
			lstrcat(s, _T(" - Ctrl����"));
		if (MK_LBUTTON & wParam)//��� | �ж�ĳ��λ�Ƿ�Ϊ1 &
			lstrcat(s, _T(" - ����϶�"));

		SetWindowText(hwndDlg, s);

		return TRUE;
	}
	case WM_LBUTTONDOWN:
	{
		TCHAR s[32];
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		wsprintf(s,_T("x=%d,y=%d"), x, y);
	//	MessageBox(hwndDlg, s ,_T("��ʾ��"), 0);
		return TRUE;
	}
	case WM_INITDIALOG://�Ի���ר��
		//MoveWindow�����У�
	//	MessageBox(hwndDlg, _T("InitDialog"), _T("��ʾ��"), 0);
		return TRUE;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;//findfirst(..) ->��¼��
		UINT nCount = DragQueryFile(hDrop, -1, NULL, 0);
			
		TCHAR s[256];
		if (nCount > 0)
		{
			DragQueryFile(hDrop,0, s, sizeof(s));
			hDrop = hDrop;
		}
	}
		break;
	case WM_COMMAND://���� ��ť �˵��� ��������ť ����ݼ���
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
