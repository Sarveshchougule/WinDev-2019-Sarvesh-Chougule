#include<windows.h>
#define MYTIMER 101

LRESULT CALLBACK WndProc(HWND ,UINT ,WPARAM ,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow) {
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	
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
	
	while(GetMessage(&msg,NULL,0,0)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	RECT rc,rctemp;
	HDC hdc;
	HBRUSH hBrush;
	static int rcright = 0;
	TCHAR str[255];
	static int iPaintFlag=1;
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
			wsprintf(str,TEXT("WM_CREATE is Created..."));
			MessageBox(hwnd,str,TEXT("Message"),MB_OK | MB_ICONEXCLAMATION);
			SetTimer(hwnd,MYTIMER,1000,NULL);
		break;
		case WM_TIMER:
			
			KillTimer(hwnd,MYTIMER);
			iPaintFlag++;
			if(iPaintFlag>13) {
				
				rcright=0;
				iPaintFlag = 1;
				InvalidateRect(hwnd,NULL,TRUE);
			}
			InvalidateRect(hwnd,NULL,FALSE);
			SetTimer(hwnd,MYTIMER,1000,NULL);
		break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			GetClientRect(hwnd,&rc);
			
			rctemp.left = rc.left + rcright;
			rctemp.top = rc.top;
			rctemp.right = (rc.right/12)+rcright;
			rctemp.bottom = rc.bottom;
			rcright = rctemp.right;
			
			switch(iPaintFlag) {
				case 1:
					hBrush = CreateSolidBrush(RGB(255,0,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 2:
					hBrush = CreateSolidBrush(RGB(0,255,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 3:
					hBrush = CreateSolidBrush(RGB(0,0,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 4:
					hBrush = CreateSolidBrush(RGB(255,255,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 5:
					hBrush = CreateSolidBrush(RGB(255,0,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 6:
					hBrush = CreateSolidBrush(RGB(0,255,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 7:
					hBrush = CreateSolidBrush(RGB(255,255,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 8:
				default:
					hBrush = CreateSolidBrush(RGB(0,0,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 9:
					hBrush = CreateSolidBrush(RGB(255,125,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 10:
					hBrush = CreateSolidBrush(RGB(64,64,64));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 11:
					hBrush = CreateSolidBrush(RGB(128,128,128));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
				case 12:
					hBrush = CreateSolidBrush(RGB(192,192,192));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rctemp,hBrush);
				break;
			}
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}