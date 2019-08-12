#include<windows.h>
#include "MySplashScreen.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(100) );
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(101) );

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

	ShowWindow(hwnd, iCmdShow);
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
	RECT rc;
	PAINTSTRUCT ps;
	TCHAR str[] = TEXT("Hello World !!!");
	switch (iMsg) {

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(101));
		//GetModuleHandle(MAKEINTRESOURCE(100));
		break;
	
	case WM_KEYDOWN:

		switch (LOWORD(wParam)) {
		
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		hMemdc = CreateCompatibleDC(hdc);
		SelectObject(hMemdc,hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc,0,0,1024,768,hMemdc,0,0,800,600,SRCCOPY);	
		//BitBlt(hdc,100,100,bitmap.bmWidth,bitmap.bmHeight,hMemdc,0,0,SRCCOPY);
		DeleteDC(hMemdc);
		
		EndPaint(hwnd, &ps);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
