#include<windows.h>

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID dwReserved) {

	switch (dwReason) {

	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" int MakeSquare(int num) {		// __declspec(dllexport)

	return num * num;
}

extern "C" BOOL IsNumberNegative(int num) {

	if (num < 0)
		return TRUE;
	else
		return FALSE;
}


