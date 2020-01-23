#include<windows.h>
#include"ReadWriteServerWithRegFile.h"
#include"MyDialog.h"
#include"MySplashScreen.h"
#include<string.h>
#include<CommCtrl.h>
#define C_COLUMNS 8
#define IDS_FIRSTCOLUMN 1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProcInsert(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProcMenu(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProcDisplay(HWND, UINT, WPARAM, LPARAM);

HWND hwndClose;
HINSTANCE g_hInst;
HWND CreateListView(HWND);
BOOL InitListViewColumns(HWND);
BOOL InsertListViewItems(HWND);
BOOL SearchListViewItems(HWND, WCHAR *);
int strcmpW(const char *, const char *);
BOOL ReadOperationOfFile(HANDLE,WCHAR *,DWORD *);
BOOL WriteOperationOfFile(HANDLE,WCHAR *,DWORD *);
BOOL strCompareAlphabet(WCHAR *);
BOOL strCompareDigit(WCHAR *);

IRead *pIRead = NULL;				// Object declaration ...
IWrite *pIWrite = NULL;				// Object declaration ...


struct DATABase {

	int age = 0, mstatus, day, month, year, gendstatus;
	double sal;
	WCHAR name[50], address[50], department[40];
}in;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	HRESULT hr;

	// COM Initailiazation ....
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {

		MessageBox(NULL, TEXT("COM Library Can Not Be Initailized. \nProgram Will Now Exit. "), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(123));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(123));
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

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
	// COM Un-initialization
	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	void SafeInterfaceRelease(void);
	HRESULT hr;
	static HBITMAP hBitmap;
	HDC hdc, hMemdc;
	BITMAP bitmap;
	PAINTSTRUCT ps;
	RECT rc;
	TEXTMETRIC tm;
	static int cyChar;
	int X, Y;
	HINSTANCE hInst;

	hwndClose = hwnd;

	switch (iMsg) {
	
	case WM_CREATE:
	
		
		hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(124));
		if (hBitmap == NULL) {

			MessageBox(hwnd, TEXT("Bitmap Loading Error"), TEXT("Error"), MB_OK);
		}

		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		// any dialog related work
		hr = CoCreateInstance(CLSID_ReadWrite, NULL, CLSCTX_INPROC_SERVER, IID_IRead, (void **)&pIRead);
		if (FAILED(hr)) {

			MessageBox(hwnd, TEXT("IRead Interface Can Not Be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pIRead->QueryInterface(IID_IWrite, (void **)&pIWrite);
		if (FAILED(hr)) {

			MessageBox(hwnd, TEXT("IWrite Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (LOWORD(wParam)) {
		
		case VK_ESCAPE:
			SafeInterfaceRelease();
			DestroyWindow(hwnd);
		break;

		case VK_SPACE:

			hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_MENU), hwnd, (DLGPROC)MyDlgProcMenu, WM_INITDIALOG);
		break;
		}
	break;
	
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);


		hMemdc = CreateCompatibleDC(hdc);
		SelectObject(hMemdc, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemdc, 0, 0, SRCCOPY);

		DeleteDC(hMemdc);
		EndPaint(hwnd, &ps);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


BOOL CALLBACK MyDlgProcMenu(HWND hDlgM, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HWND hDlgDis, hDlgEnt;
	HINSTANCE hIns;
	switch (iMsg) {

	case WM_INITDIALOG:
		// set focus in name Edit Box
		SetFocus(GetDlgItem(hDlgM, ID_PBDATAENTRY));
		return(TRUE);
	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_PBDATAENTRY:
			EndDialog(hDlgM, 0);
			hDlgEnt = hDlgM;
			hIns = (HINSTANCE)GetWindowLong(hDlgEnt, GWL_HINSTANCE);
			DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DATAENTRY), hDlgEnt, (DLGPROC)MyDlgProcInsert, WM_INITDIALOG);
			break;

		case ID_PBDATADISPLAY:
			EndDialog(hDlgM, 0);
			hDlgDis = hDlgM;
			hIns = (HINSTANCE)GetWindowLong(hDlgDis, GWL_HINSTANCE);
			DialogBoxParam(hIns, MAKEINTRESOURCE(IDD_DATADISPLAY), hDlgDis, (DLGPROC)MyDlgProcDisplay, WM_INITDIALOG);
			break;
		case IDCANCEL:
			EndDialog(hDlgM, 0);
			DestroyWindow(hwndClose);
			break;
		}
		return(TRUE);
	}
	return(FALSE);
}


BOOL CALLBACK MyDlgProcInsert(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	HWND hDlgDis;
	HINSTANCE hInstan;
	int iage = 0,imstatus,iday=0,imonth = 0,iyear=0,nday=31,igendstatus;
	double fsalary;
	int salrs, salps;
	WCHAR strage[255],strmstatus[255],strname[255],straddress[255],strsalary[255],strdepartment[255],strday[255],strmonth[255],stryear[255],strgendstatus[255];
	int flagerrorwrite = 0;


	HANDLE hFile;
	DWORD wmWritten = 0;
	WCHAR strWrite[255];
	TCHAR strTemp[4] = {NULL}, T1[4] = { NULL };
	WCHAR strData[255];



	switch (iMsg) {

	case WM_INITDIALOG:
		// set focus in name Edit Box
		SetFocus(GetDlgItem(hDlg, ID_ETNAME));
		
		// keep married Radio Button checked
		SendDlgItemMessage(hDlg, ID_RBMALE, BM_SETCHECK, 1, 0);
		SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_SETCHECK, 1, 0);
		return(TRUE);

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_PBDISPLAY:
			EndDialog(hDlg, 0);
			hDlgDis = hDlg;
			hInstan = (HINSTANCE)GetWindowLong(hDlgDis, GWL_HINSTANCE);
			DialogBoxParam(hInstan, MAKEINTRESOURCE(IDD_DATADISPLAY), hDlgDis, (DLGPROC)MyDlgProcDisplay, WM_INITDIALOG);

			//  do any thing
			break;

		case IDOK:

			// Get the user entered Name
			GetDlgItemText(hDlg, ID_ETNAME, in.name, 50);
			// Get the user entered Address
			GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			// Get the user entered Gender
			in.gendstatus = SendDlgItemMessage(hDlg, ID_RBMALE, BM_GETCHECK, 0, 0);
			// Get the user entered Age 
			in.age = GetDlgItemInt(hDlg, ID_ETAGE, NULL, TRUE);

			// Get the user entered Day
			in.day = GetDlgItemInt(hDlg, ID_CBDAY, NULL, TRUE);
			// Get the user entered Month
			in.month = GetDlgItemInt(hDlg, ID_CBMONTH, NULL, TRUE);
			// Get the user entered Year
			in.year = GetDlgItemInt(hDlg, ID_CBYEAR, NULL, TRUE);

			// Get the user entered Department 
			GetDlgItemText(hDlg, ID_ETDEPARTMENT, in.department, 40);

			// Get the user entered Salary
			salrs = GetDlgItemInt(hDlg, ID_ETSALRS, NULL, TRUE );
			salps = GetDlgItemInt(hDlg, ID_ETSALPS, NULL, TRUE );

			in.sal = (salrs + (salps / 100));
			// Get the user entered marital status
			in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);


			wsprintf(strname, in.name);
			wsprintf(straddress, in.address);
			igendstatus = in.gendstatus;
			iage = in.age;

			iday = in.day;
			imonth = in.month;
			iyear = in.year;
			wsprintf(strdepartment, in.department);

			fsalary = in.sal;
			imstatus = in.mstatus;


			if ((strlen((char *)strname) == 0) && (strlen((char *)straddress) == 0) && (iage == 0) && (iday == 0) && (imonth == 0) && (iyear == 0) && (strlen((char *)strdepartment) == 0) && fsalary == 0) {
			
				wsprintf(strname, TEXT("Every TextBox is Empty... Please Enter Again Starting With Name... "));
				MessageBox(NULL, strname, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
 			else if ((strlen((char *)strname) == 0)) {

				wsprintf(strname, TEXT("Name is Empty... Please enter again ... Error code : %s"), in.name);
				MessageBox(NULL, strname, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if ((strlen((char *)straddress) == 0)) {

				wsprintf(straddress, TEXT("Address is Empty... Please enter again... Error code : %s"), in.address);
				MessageBox(NULL, straddress, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if (iage == 0) {

				wsprintf(strage, TEXT("Age is Notvalid... Please enter again ... Error code : %d"), iage);
				MessageBox(NULL, strage, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if (iday == 0) {
				
				wsprintf(strday, TEXT("Day is Notvalid... Please enter again ... Error code : %d"), iday);
				MessageBox(NULL, strday, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if (imonth == 0) {
			
				wsprintf(strmonth, TEXT("Month is Notvalid... Please enter again ... Error code : %d"), imonth);
				MessageBox(NULL, strmonth, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if (iyear == 0) {
			
				wsprintf(stryear, TEXT("Year is Notvalid... Please enter again... Error code : %d"), iyear);
				MessageBox(NULL, stryear, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if ((strlen((char *)strdepartment) == 0)) {
			
				wsprintf(strdepartment, TEXT("Department is Notvalid... Please enter again... Error code : %s"), in.department);
				MessageBox(NULL, strdepartment, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else if (fsalary == 0.0) {

				wsprintf(strsalary, TEXT("Salary is Empty... Please enter again ... Error code : %d.0"), fsalary);
				MessageBox(NULL, strsalary, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			}
			else {
				
				wsprintf(strname, TEXT("%s"), in.name);
				if (!strCompareAlphabet(strname)) {

					MessageBox(NULL, TEXT("Name Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}
				wsprintf(straddress, TEXT("%s"), in.address);
				if (!strCompareAlphabet(straddress)) {
				
					MessageBox(NULL, TEXT("Address Value is incorrect  ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}
				if (igendstatus)
					wsprintf(strgendstatus, TEXT("Male"));
				else
					wsprintf(strgendstatus, TEXT("Female"));
				if (!strCompareAlphabet(strgendstatus)) {
				
					MessageBox(NULL, TEXT("Gender status Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}
				wsprintf(strage, TEXT("%d"), iage);
				if (!strCompareDigit(strage)) {
				
					MessageBox(NULL, TEXT("Age Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}
				wsprintf(strTemp, TEXT("%d"), (iyear % 4));
				wsprintf(T1, TEXT("0.0"));
				if ( (iyear <= 2020) ){
				
					if ( (strcmp((const char *)strTemp, (const char *)T1) != 0) && imonth <= 12 ) {
					
						if (imonth == 1 || imonth == 3 || imonth == 5 || imonth == 7 || imonth == 8 || imonth == 10 || imonth == 12) {
							
							if (iday <= 31) {

								wsprintf(strday, TEXT("%d/%d/%d"), iday,imonth,iyear);
							}
							else {
							
								MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
								break;
							}
						}
						else if (imonth == 4 || imonth == 6 || imonth == 9 || imonth == 11) {
						
							if (iday <= 30) {
							
								wsprintf(strday, TEXT("%d/%d/%d"), iday, imonth, iyear);
							}
							else {
								MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
								break;
							}
						}
						else if (imonth == 2) {
						
							if (iday <= 28) {

								wsprintf(strday, TEXT("%d/%d/%d"), iday, imonth, iyear);
							}
							else {

								MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
								break;
							}
						}
					}
					else if( (strcmp( (const char *)strTemp, (const char *)T1 ) == 0) && imonth <= 12){
					
						if (imonth == 1 || imonth == 3 || imonth == 5 || imonth == 7 || imonth == 8 || imonth == 10 || imonth == 12) {

							if (iday <= 31) {

								wsprintf(strday, TEXT("%d/%d/%d"), iday, imonth, iyear);
							}
							else {

								MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
								break;
							}
						}
						else if (imonth == 4 || imonth == 6 || imonth == 9 || imonth == 11) {

							if (iday <= 30) {

								wsprintf(strday, TEXT("%d/%d/%d"), iday, imonth, iyear);
							}
							else {

								MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
								break;
							}
						}
						else if (imonth == 2) {

							if (iday <= 29) {

								wsprintf(strday, TEXT("%d/%d/%d"), iday, imonth, iyear);
							}
							else {

								MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
								break;
							}
						}
					}
					else {
					
						MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
						break;
					}
				}
				else {

					MessageBox(NULL, TEXT("Date is Incorrect... Please check again..."), TEXT("Error"), MB_OK);
					break;
				}

				if (!strCompareDigit(strday)) {
				
					MessageBox(NULL, TEXT("Date Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}

				wsprintf(strdepartment, TEXT("%s"), in.department);
				if (!strCompareAlphabet(strdepartment)) {
				
					MessageBox(NULL, TEXT("Department Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}
				wsprintf(strsalary, TEXT("%d.%d"), salrs,salps);
				if (!strCompareDigit(strsalary)) {
				
					MessageBox(NULL, TEXT("Salary Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}
				if (imstatus)
					wsprintf(strmstatus, TEXT("Married"));
				else
					wsprintf(strmstatus, TEXT("Unmarried"));

				if (!strCompareAlphabet(strmstatus)) {
				
					MessageBox(NULL, TEXT("Maritial Status Value is incorrect ..."), TEXT("Error"), MB_OK);
					flagerrorwrite++;
				}

				wsprintf(strData, TEXT("|%s| %s| %s| %d| %s| %s| %s| %s|"), in.name, in.address, strgendstatus, iage, strday, in.department, strsalary, strmstatus);

				hFile = CreateFile(TEXT("test.txt"), FILE_APPEND_DATA ,
					FILE_SHARE_WRITE , NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

				if (hFile == INVALID_HANDLE_VALUE) {

					MessageBox(NULL, TEXT("CreateFile Error ... For write"), TEXT("Error"), MB_OK);
				}
				if (flagerrorwrite == 0) {
					if (WriteOperationOfFile(hFile, strData, &wmWritten)) {	   

						wsprintf(strWrite, TEXT("Operation is Successfull ..."));
						MessageBox(NULL, strWrite, TEXT("Output"), MB_OK);
					}
				}
				flagerrorwrite = 0;
				CloseHandle(hFile);
			}
			EndDialog(hDlg, 0);
			DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DATAENTRY), hDlg, (DLGPROC)MyDlgProcInsert, WM_INITDIALOG);

			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			
			hInstan = (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE);
			DialogBoxParam(hInstan, MAKEINTRESOURCE(IDD_MENU), hDlg, (DLGPROC)MyDlgProcMenu, WM_INITDIALOG);


			break;
		}
		return(TRUE);
	}
	return(FALSE);
}	// End of Dialog Procedure

BOOL strCompareAlphabet(WCHAR * str) {

	int countloopj=0;
	for (int i = 0; i < 255; i++) {
		
		if ( ((int)str[i] >= 65) && ((int)str[i] <= 90) || ((int)str[i] >= 97 ) && ((int)str[i]<= 122)) {
			
			countloopj++;
		}
		if (str[i] == ',' || str[i] == '.') {
		
			countloopj++;
		}
	}
	if (countloopj > 0) {
		countloopj = 0;
		return(TRUE);
	}
	else {
		countloopj = 0;
		return(FALSE);
	}
}

BOOL strCompareDigit(WCHAR * str) {

	int countloopi = 0;
	for (int i = 0; i < 255; i++) {

		if (str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i]=='4' || str[i]=='5' || str[i] =='6' || str[i] =='7' || str[i] == '8' || str[i] == '9' || str[i]== '0') {

			countloopi++;
		}
		else if (str[i] == '.' || str[i] == '/') {

			countloopi++;
		}
		
	}

	if (countloopi > 0) {
		countloopi = 0;
		return(TRUE);
	}
	else {
		countloopi = 0;
		return(FALSE);
	}

}



BOOL CALLBACK MyDlgProcDisplay(HWND hDlgD, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	LVFINDINFO lplvfindinfo;
	LVITEM lvItems;
	BOOLEAN bResult;
	WCHAR szText[255];
	HWND hDlgDis, hwndList;
	static HWND hwndlv;
	HINSTANCE hInstan;
	int iage = 0, imstatus, iday = 0, imonth = 0, iyear = 0, nday = 31, igendstatus;
	double fsalary;
	int salrs, salps;
	WCHAR strage[255], strmstatus[255], strname[255], straddress[255], strsalary[255], strdepartment[255], strday[255], strmonth[255], stryear[255], strgender[255];

	TCHAR strTemp[4] = { NULL }, T1[4] = { NULL };
	switch (iMsg) {

	case WM_INITDIALOG:
		// set focus in name Edit Box
		SetFocus(GetDlgItem(hDlgD, ID_ETSEARCHNAME));

		hwndlv = CreateListView(hDlgD);

		bResult = InitListViewColumns(hwndlv);
		if (bResult == 0) {
			MessageBox(NULL, TEXT("Column are not inserted in List View .... "), TEXT("Error"), MB_OK);
		}
		bResult = 0;
		bResult = InsertListViewItems(hwndlv);
		if (bResult == 0) {
			MessageBox(NULL, TEXT("Items are not inserted in List View .... "), TEXT("Error"), MB_OK);
		}
		
		return(TRUE);

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_PBINSERT:

			EndDialog(hDlgD, 0);
			hDlgDis = hDlgD;
			hInstan = (HINSTANCE)GetWindowLong(hDlgDis, GWL_HINSTANCE);
			DialogBoxParam(hInstan, MAKEINTRESOURCE(IDD_DATAENTRY), hDlgDis, (DLGPROC)MyDlgProcInsert, WM_INITDIALOG);

			//  do any thing
			break;

		case ID_PBDISPLAYALL:

			SetFocus(GetDlgItem(hDlgD, ID_ETSEARCHNAME));

			hwndlv = CreateListView(hDlgD);

			bResult = InitListViewColumns(hwndlv);
			if (bResult == 0) {
				MessageBox(NULL, TEXT("Column are not inserted in List View .... "), TEXT("Error"), MB_OK);
			}
			bResult = 0;
			bResult = InsertListViewItems(hwndlv);
			if (bResult == 0) {
				MessageBox(NULL, TEXT("Items are not inserted in List View .... "), TEXT("Error"), MB_OK);
			}
			break;
		
		case ID_PBSEARCH:
			
			GetDlgItemText(hDlgD, ID_ETSEARCHNAME, in.name, 50);

			wsprintf(strname, in.name);
			if ((strlen((char *)strname) == 0) ) {

				wsprintf(strname, TEXT("TextBox is Empty... Please Enter Again Starting With Name "));
				MessageBox(NULL, strname, TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);

			}
			else if ((strlen((char *)strname) != 0)) {
				
				wsprintf(szText,in.name);

				bResult = 0;
				bResult = SearchListViewItems(hwndlv, szText);
				if (bResult == 0) {
					MessageBox(NULL, TEXT("Items are not Searched in List View .... "), TEXT("Error"), MB_OK);
				}

			}
			break;

		case IDCANCEL:
			EndDialog(hDlgD, 0);

			hInstan = (HINSTANCE)GetWindowLong(hDlgD, GWL_HINSTANCE);
			DialogBoxParam(hInstan, MAKEINTRESOURCE(IDD_MENU), hDlgD, (DLGPROC)MyDlgProcMenu, WM_INITDIALOG);
			break;

		}
		return(TRUE);
	}
	return(FALSE);
}


HWND CreateListView(HWND hwndParent)
{
	HWND hWndListView;
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(hwndParent, &rcClient);

	// Create the list-view window in report view with label editing enabled.
	hWndListView = CreateWindow(WC_LISTVIEW,
		TEXT(""),
		WS_CHILD | LVS_REPORT | WS_VISIBLE | LVS_EDITLABELS ,
		40, 145, 1115, 420,
		hwndParent,
		NULL,
		NULL,
		NULL);

	return (hWndListView);
}

BOOL InitListViewColumns(HWND hWndListView)
{
	int count = 0;
	LPWSTR szText = { NULL };     // Temporary buffer.
	LVCOLUMN lvc;
	int iCol;
	
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT ;

	// Add the columns.
	for (iCol = 0,count = 0; iCol < C_COLUMNS; iCol++,count++)
	{

		if (count == 0) {

			szText = (LPWSTR) TEXT("Name");
		}
		else if (count == 1) {

			szText = (LPWSTR) TEXT("Address");
		}
		else if (count == 2) {

			szText = (LPWSTR) TEXT( "Gender");
		}
		else if (count == 3) {
		
			szText = (LPWSTR)TEXT("Age");
		}
		else if (count == 4) {

			szText = (LPWSTR) TEXT("Joining Data");
		}
		else if (count == 5) {

			szText = (LPWSTR) TEXT("Department");
		}
		else if (count == 6) {

			szText = (LPWSTR) TEXT("Salary");
		}
		else if (count == 7) {

			szText = (LPWSTR) TEXT("Maritial Status");
		}

		lvc.iSubItem = iCol;
		lvc.pszText = (LPWSTR) szText;
		lvc.cx = 139;               // Width of column in pixels.
		
		lvc.fmt = LVCFMT_CENTER;  // Center-aligned column.
		szText = { NULL };

		// Insert the columns into the list view.
		if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1)
			return FALSE;
	}

	return TRUE;
}

BOOL InsertListViewItems(HWND hWndListView)
{
	LVITEM lvI;
	PWSTR szText = { NULL };
	TCHAR strT[255], strR[255];
	int index = 0;

	static int loopCount = 0, endLineCount = 0;
	HANDLE hFileInsert;
	DWORD wmWritten = 0;
	WCHAR strRead[255];
	WCHAR strVal[255];

	WCHAR str1[255] = { NULL };
	WCHAR str2[255] = { NULL };
	WCHAR str3[255] = { NULL };
	WCHAR str4[255] = { NULL };
	WCHAR str5[255] = { NULL };
	WCHAR str6[255] = { NULL };
	WCHAR str7[255] = { NULL };
	WCHAR str8[255] = { NULL };
	
	hFileInsert = CreateFile(TEXT("test.txt"), FILE_READ_DATA,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileInsert == INVALID_HANDLE_VALUE) {

		MessageBox(NULL, TEXT("CreateFile Error ... For Read"), TEXT("Error"), MB_OK);
	}

	lvI.mask = LVIF_TEXT;
	while(ReadOperationOfFile(hFileInsert, strVal, &wmWritten) && wmWritten > 0) {	
		
		for (int i = 0, j = 0,loopCount = 0; i < (DWORD)255; i++) {

			if (strVal[i] != '|') {	

				if (loopCount == 1) {

					str1[j] = strVal[i];
					j++;
				}
				if (loopCount == 2) {

					str2[j] = strVal[i];
					j++;
				}
				if (loopCount == 3) {

					str3[j] = strVal[i];
					j++;
				}
				if (loopCount == 4) {

					str4[j] = strVal[i];
					j++;
				}
				if (loopCount == 5) {

					str5[j] = strVal[i];
					j++;
				}
				if (loopCount == 6) {

					str6[j] = strVal[i];
					j++;
				}
				if (loopCount == 7) {

					str7[j] = strVal[i];
					j++;
				}
				if (loopCount == 8) {

					str8[j] = strVal[i];
					j++;
					endLineCount=1;
				}
			}
			else if (strVal[i] == '|') {

				loopCount++;
				j = 0;


				if (endLineCount > 0) {
					loopCount = 0;

					//		List View Display Part Started ....
					lvI.iItem = index;

					for (int iCol = 0; iCol < C_COLUMNS; iCol++) {

						lvI.iSubItem = iCol;
						if (lvI.iSubItem == 0) {

							lvI.pszText = (LPWSTR)str1;
							ListView_InsertItem(hWndListView, &lvI);
						}
						else if (lvI.iSubItem == 1) {

							lvI.pszText = (LPWSTR)str2;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
						else if (lvI.iSubItem == 2) {

							lvI.pszText = (LPWSTR)str3;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
						else if (lvI.iSubItem == 3) {

							lvI.pszText = (LPWSTR)str4;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
						else if (lvI.iSubItem == 4) {

							lvI.pszText = (LPWSTR)str5;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
						else if (lvI.iSubItem == 5) {

							lvI.pszText = (LPWSTR)str6;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
						else if (lvI.iSubItem == 6) {

							lvI.pszText = (LPWSTR)str7;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
						else if (lvI.iSubItem == 7) {

							lvI.pszText = (LPWSTR)str8;
							SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						}
					}
					index++;
					//		List View Display Part Ended ....

					for (j = 0; j < 254; j++) {

						str1[j] = { NULL };
						str2[j] = { NULL };
						str3[j] = { NULL };
						str4[j] = { NULL };
						str5[j] = { NULL };
						str6[j] = { NULL };
						str7[j] = { NULL };
						str8[j] = { NULL };
					}

					j = 0;
					endLineCount = 0;
				}
			}
		}			//end of for;
	}//end of While loop from Reading File
	loopCount = 0;
	endLineCount = 0;
	CloseHandle(hFileInsert);
	return TRUE;
}

BOOL SearchListViewItems(HWND hWndListView,WCHAR *szText)
{
	LVITEM lvI;
	TCHAR strT[255], strR[255];
	int index = 0,countMessage=0;
	int resultName, resultDateOfJoin;

	static int loopCount = 0, endLineCount = 0;
	HANDLE hFileSearch;
	DWORD wmWritten = 0;
	WCHAR strVal[255];

	WCHAR str1[255] = { NULL };
	WCHAR str2[255] = { NULL };
	WCHAR str3[255] = { NULL };
	WCHAR str4[255] = { NULL };
	WCHAR str5[255] = { NULL };
	WCHAR str6[255] = { NULL };
	WCHAR str7[255] = { NULL };
	WCHAR str8[255] = { NULL };

	hFileSearch = CreateFile(TEXT("test.txt"), FILE_READ_DATA,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSearch == INVALID_HANDLE_VALUE) {

		MessageBox(NULL, TEXT("CreateFile Error ... For Read"), TEXT("Error"), MB_OK);
	}

	lvI.mask = LVIF_TEXT;
	while (ReadOperationOfFile(hFileSearch, strVal, &wmWritten)  && wmWritten > 0) {	

		for (int i = 0, j = 0, loopCount = 0; i < (DWORD)255; i++) {

			if (strVal[i] != '|') {		

				if (loopCount == 1) {

					str1[j] = strVal[i];
					j++;
				}
				if (loopCount == 2) {

					str2[j] = strVal[i];
					j++;
				}
				if (loopCount == 3) {

					str3[j] = strVal[i];
					j++;
				}
				if (loopCount == 4) {

					str4[j] = strVal[i];
					j++;
				}
				if (loopCount == 5) {

					str5[j] = strVal[i];
					j++;
				}
				if (loopCount == 6) {

					str6[j] = strVal[i];
					j++;
				}
				if (loopCount == 7) {

					str7[j] = strVal[i];
					j++;
				}
				if (loopCount == 8) {

					str8[j] = strVal[i];
					j++;
					endLineCount = 1;
				}
			}
			else if (strVal[i] == '|') {

				loopCount++;
				j = 0;

				if (endLineCount > 0) {
					loopCount = 0;

					if (strcmpW((const char *)str1, (const char *)szText) == 0  ) { 
					countMessage++;

					//		List View Display Part Started ....
					ListView_DeleteAllItems(hWndListView);
						lvI.iItem = index;

						for (int iCol = 0; iCol < C_COLUMNS; iCol++) {

							lvI.iSubItem = iCol;
							if (lvI.iSubItem == 0) {

								lvI.pszText = (LPWSTR)str1;
								ListView_InsertItem(hWndListView, &lvI);
							}
							else if (lvI.iSubItem == 1) {

								lvI.pszText = (LPWSTR)str2;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
							else if (lvI.iSubItem == 2) {

								lvI.pszText = (LPWSTR)str3;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
							else if (lvI.iSubItem == 3) {

								lvI.pszText = (LPWSTR)str4;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
							else if (lvI.iSubItem == 4) {

								lvI.pszText = (LPWSTR)str5;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
							else if (lvI.iSubItem == 5) {

								lvI.pszText = (LPWSTR)str6;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
							else if (lvI.iSubItem == 6) {

								lvI.pszText = (LPWSTR)str7;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
							else if (lvI.iSubItem == 7) {

								lvI.pszText = (LPWSTR)str8;
								SendMessage(hWndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
							}
						}
						index++;
						//		List View Display Part Ended ....
					}			// After checking and displaying
					for (j = 0; j < 254; j++) {

						str1[j] = { NULL };
						str2[j] = { NULL };
						str3[j] = { NULL };
						str4[j] = { NULL };
						str5[j] = { NULL };
						str6[j] = { NULL };
						str7[j] = { NULL };
						str8[j] = { NULL };
					}
					
					j = 0;
					endLineCount = 0;
				}
			}
		}			//end of for;
	}//end of While loop from Reading File
	if (countMessage == 0) {
		ListView_DeleteAllItems(hWndListView);
		MessageBox(NULL, TEXT("No Entry Are Available With This Name ...."), TEXT("Message"), MB_ICONEXCLAMATION | MB_OK);
	}

	loopCount = 0;
	countMessage = 0;
	endLineCount = 0;
	CloseHandle(hFileSearch);
	return TRUE;
}

int strcmpW(const char *Abuff, const char *Bbuff) {

	BOOL flag = FALSE;
	for (int i = 0; i < (DWORD)sizeof(Abuff); i++) {
	
		if (Abuff[i] == Bbuff[i]) {
		
			flag = TRUE;
		}
		else if (Abuff[i] != Bbuff[i]) {
		
			flag = FALSE;
		}
		if (flag == FALSE) {
		
			return (-1);
		}
	}
	return (0);
}


void SafeInterfaceRelease(void) {

	// code
	if (pIWrite) {

		pIWrite->Release();
		pIWrite = NULL;
	}
	else if (pIRead) {

		pIRead->Release();
		pIRead = NULL;
	}
}

BOOL ReadOperationOfFile(HANDLE hFile,WCHAR * StrVal,DWORD *wmWritten) {

	BOOL Var = NULL;
	if (pIRead->ReadFileOperation(hFile, StrVal, wmWritten, &Var))
		return(Var);
	else
		return(Var);
}

BOOL WriteOperationOfFile(HANDLE hFile, WCHAR * StrData, DWORD *wmWritten) {

	BOOL Var = NULL;
	if (pIWrite->WriteFileOperation(hFile, StrData, wmWritten, &Var))
		return(Var);
	else
		return(Var);
}






