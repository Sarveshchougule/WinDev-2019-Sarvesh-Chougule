#include<windows.h>
#include "MyDialog.h"
#include "MySplashScreen.h"

BOOL CALLBACK MyDlgProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

struct INP {
	
	int age, mstatus;
	float salary;
	WCHAR name[50], address[50];
}in;

int WINAPI WinMain(HINSTANCE hPrevInstance, HINSTANCE hInstance, LPSTR lpsziCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(109));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(109));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("SKC APPLICATION"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
	
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HBITMAP hBitmap;
	HDC hdc,hMemdc;
	BITMAP bitmap;
	PAINTSTRUCT ps;
	RECT rc;
	TEXTMETRIC tm;
	static int cyChar;
	int X, Y;
	const char *str[] = { "ASTRO-MEDI-COMP ","\n","\n","\n","        GURUKUL ","\n","\n"," SPACE to Proceed" };
	//TCHAR str1[] = TEXT("");
	HINSTANCE hInst;
	switch (iMsg) {
	
	case WM_CREATE:
		hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(110));

		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		hInst = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
		// call to Dialog Box
		CreateDialog(hInst, TEXT("DataEntry"), hwnd,(DLGPROC) MyDlgProc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
			
		switch (LOWORD(wParam)) {

		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		case VK_SPACE:

			MessageBox(hwnd, TEXT("VK_SPACE is arrived ....."), TEXT("Interupt Occured"),MB_OK);
			//DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		
		
		/*hMemdc = CreateCompatibleDC(hdc);
		SelectObject(hMemdc, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemdc, 0, 0, SRCCOPY);
		//StretchBlt(hdc, 0, 0, 1366, 768, hMemdc, 0, 0, 1366, 768, SRCCOPY);
		DeleteDC(hMemdc);
		*/
		//EndPaint(hwnd, &ps);
		
		X = (rc.right / 2) - 70;
		Y = (rc.bottom / 2) - 50;
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		for (int i = 0; i <8; i++) {
			
			TextOutA(hdc, X, Y, str[i], strlen(str[i]));
			Y = Y + cyChar;
		}
		EndPaint(hwnd, &ps);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	WCHAR salrs[6], salps[3];
	WCHAR aGe[2];
	switch (iMsg) {
	
	case WM_INITDIALOG:
		// set focus in name Edit Box.
		SetFocus(GetDlgItem(hDlg, ID_ETNAME));
		// keep married Radio Button checked.
		SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_SETCHECK, 1, 0);
		return (TRUE);

	case WM_COMMAND:

		switch (LOWORD(wParam)) {
		
		case ID_PBCONTINUE:
			// whatever task you want....

			EndDialog(hDlg, 0);
			break;

		case IDOK:

			// Get the user-entered name
			GetDlgItemText(hDlg, ID_ETNAME,  in.name, 50);
			// Get the user-entered address
			GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			// Get the user-entered age
			in.age = (hDlg, ID_ETAGE, NULL, TRUE);
			//in.age =  atoi((char *)aGe);
			// Get the user-entered salary
			GetDlgItemText(hDlg, ID_ETSALRS, salrs, 6);
			GetDlgItemText(hDlg, ID_ETSALPS, salps, 3);
			in.salary = atoi((char *)salrs) + (float) ( (atoi( (char *) salps) )/100 );
			// Get-user-entered marital status
			in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);
			EndDialog(hDlg, 0);
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		return(TRUE);
	}
	return(FALSE);
}	// End of Dialog Procdure



