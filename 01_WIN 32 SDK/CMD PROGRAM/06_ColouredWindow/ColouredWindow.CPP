#include<windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hPrevInstance, HINSTANCE hInstance, LPSTR lpszCmdLine, int iCmdShow){
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
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
	
	while(GetMessage(&msg,NULL,0,0)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam) {
	
	static int iPaintFlag = 0;
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[255];
	
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
		case WM_CHAR:
			switch(LOWORD(wParam)) {
				
				case 'R':
				case 'r':
					iPaintFlag = 1;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'G':
				case 'g':
					iPaintFlag = 2;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'B':
				case 'b':
					iPaintFlag = 3;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'C':
				case 'c':
					iPaintFlag = 4;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'M':
				case 'm':
					iPaintFlag = 5;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'Y':
				case 'y':
					iPaintFlag = 6;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'W':
				case 'w':
					iPaintFlag = 7;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'O':
				case 'o':
					iPaintFlag = 8;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'U':
				case 'u':
					iPaintFlag = 9;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'I':
				case 'i':
					iPaintFlag = 10;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'P':
				case 'p':
					iPaintFlag = 11;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
				case 'K':
				case 'k':
				default :
					iPaintFlag = 0;
					InvalidateRect(hwnd,NULL,TRUE);
				break;
			}
		break;
		case WM_PAINT:
			GetClientRect(hwnd,&rc);
			hdc = BeginPaint(hwnd,&ps);
			switch(iPaintFlag) {
				
				case 1:
					hBrush = CreateSolidBrush(RGB(255,0,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 2:
					hBrush = CreateSolidBrush(RGB(0,255,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 3:
					hBrush = CreateSolidBrush(RGB(0,0,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 4:
					hBrush = CreateSolidBrush(RGB(0,255,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 5:
					hBrush = CreateSolidBrush(RGB(255,0,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 6:
				hBrush = CreateSolidBrush(RGB(255,255,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 7:
				hBrush = CreateSolidBrush(RGB(255,255,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 8:
				hBrush = CreateSolidBrush(RGB(255,128,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 9:
				hBrush = CreateSolidBrush(RGB(64,64,64));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 10:
				hBrush = CreateSolidBrush(RGB(128,128,128));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 11:
				hBrush = CreateSolidBrush(RGB(192,192,192));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
				case 0:
				default:
				hBrush = CreateSolidBrush(RGB(0,0,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);
				break;
			}
			EndPaint(hwnd,&ps);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
