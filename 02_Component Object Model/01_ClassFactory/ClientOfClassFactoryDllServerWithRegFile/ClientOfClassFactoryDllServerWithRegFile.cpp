
#include<windows.h>
#include "ClassFactoryDllServerWithRegFile.h"
// global function declarations 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// global variable declarations
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ComClient");
	HRESULT hr;
	// code
	// COM Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		
		MessageBox(NULL, TEXT("COM Library Can Not Be Initialized.\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	// register window class
	RegisterClassEx(&wndclass);
	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("SKC APPLICATIONS"),
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
	// Message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
	
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	// COM Un-initialization
	CoUninitialize();
	return((int)msg.wParam);
}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	//static ISum *pISum = NULL;
	//static ISubtract *pISubtract = NULL;
	// function declarations
	void SafeInterfaceRelease(void);
	// variable declarations
	HRESULT hr;
	int iNum1 = 55, iNum2 = 45, iSum;
	TCHAR str[255];
	// code
	switch (iMsg) {
	
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr)) {
		
			MessageBox(hwnd, TEXT("ISum Interface Can Not Be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// initialize arguments hardcoded
		//call SumOfTwoIntegers() of, ISum to get the sum 
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		// display the result 
		wsprintf(str, TEXT("Sum Of %d And %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		// call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr)) {
		
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		// as ISum is now not needed onwords, release it
		pISum->Release();
		pISum = NULL;// make released interface NULL
		// again initialize arguments hardcoded
		iNum1 = 1390;
		iNum2 = 1893;
		// again call SumOfTwoIntegers() of ISum to get the new sum 
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);
		// as ISum is now not needed onwords, release it 
		pISubtract->Release();
		pISubtract = NULL; // make released interface NULL.
		// display the result
		wsprintf(str, TEXT("Subtraction of %d And %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		// exit the application
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
void SafeInterfaceRelease(void) {

	// code
	if (pISubtract) {

		pISubtract->Release();
		pISubtract = NULL;
	}
	else if (pISum) {

		pISum->Release();
		pISum = NULL;
	}
}
