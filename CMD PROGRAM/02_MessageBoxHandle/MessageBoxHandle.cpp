#include<windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hPrevInstance,HINSTANCE hInstance,LPSTR lpszCmdLine, int iCmdShow) {
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	MessageBox(NULL,TEXT("Application is created ..."),TEXT("Message"),MB_OK | MB_ICONHAND);
	
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
	
	TCHAR str[255];
	switch(iMsg) {
		
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		case WM_CREATE:
			wsprintf(str,TEXT("WM_CREATE is arrived..."));
			MessageBox(hwnd,str,TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;
		case WM_LBUTTONDOWN:
			wsprintf(str,TEXT("WM_LBUTTONDOWN is arrived..."));
			MessageBox(hwnd,str,TEXT("Message"), MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		break;
		case WM_KEYDOWN:
			
			switch(LOWORD(wParam)) {
				
				case VK_ESCAPE:
					DestroyWindow(hwnd);
				break;
				default:
					wsprintf(str,TEXT("WM_KEYDOWN is arrived..."));
					MessageBox(hwnd,str,TEXT("Message"),MB_OK| MB_ICONERROR);
				break;
			}
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}