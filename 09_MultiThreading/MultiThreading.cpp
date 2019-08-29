#include<windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;

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

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
	
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	TCHAR str[255];
	switch (iMsg) {

	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_KEYDOWN:

		switch (LOWORD(wParam)) {
		
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		default:
			wsprintf(str, TEXT("WM_KEYDOWN is arrived..."));
			MessageBox(NULL, str, TEXT("Message"), MB_OK);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {

	HDC hdc;
	TCHAR str[255];
	unsigned long int i;

	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 0; i <= 4294967295; i++) {
	
		wsprintf(str,TEXT("Thread One -> Increasing Order : %lu"),i);
		TextOut(hdc, 5, 5, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {

	HDC hdc;
	TCHAR str[255];
	unsigned long int i;

	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 4294967295; i >= 0; i--) {
	
		wsprintf(str, TEXT("Thread Two -> Decreasing Order : %lu"),i);
		TextOut(hdc, 5, 20, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}
