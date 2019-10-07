#include<windows.h>
#include "Pledge.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hPrevInstance, HINSTANCE hInstance, LPSTR lpszCmdLine, int iCmdShow) {
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(100));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(100));
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	
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
	
	while(GetMessage(&msg,NULL,0,0)){
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,WPARAM wParam,LPARAM lParam) {
	
	HDC hdc;
	TEXTMETRIC tm;
	RECT rc;
	static int cyChar;
	int i,x,y;
	PAINTSTRUCT ps;
	const char *str[] = { "PLEDGE ",
		"India is my country. ",
		"All indian are my bothers and sisters. ",
		"I love my country and ",
		"I am proud of its rich and varied heritage. ",
		"I shall strive to be worthy of it. ",
		"I shall respect my parents, teachers and all elders and ",
		"treat everyone with courtesy. ",
		"To my country and all my people, I pledge my devotion. ",
		"In their well beign and ",
		"prosperity alone lies my happiness. ",
		"JAI HIND. "
	};
	switch(iMsg) {
		
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		case WM_KEYDOWN:
			switch(LOWORD(wParam)) {
				
				case VK_ESCAPE:
					DestroyWindow(hwnd);
				break;
			}
		break;
		
		case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		ReleaseDC(hwnd,hdc);
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		break;
		
		case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc = BeginPaint(hwnd,&ps);
		x = (rc.right/2)-90;
		y = (rc.bottom/2)-50;
		SetBkColor(hdc,RGB(0,0,0));
		for(i = 0;i<=11; ++i) {
			
			if(i<4) {
				
				SetTextColor(hdc,RGB(255,200,0));
			}
			else if(i<8) {
				
				SetTextColor(hdc,RGB(255,255,255));
			}
			else if(i<12) {
				
				SetTextColor(hdc,RGB(0,255,0));
			}
			TextOutA(hdc,x,y,str[i],strlen(str[i]));
			y = y + cyChar;
		}
		EndPaint(hwnd,&ps);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
