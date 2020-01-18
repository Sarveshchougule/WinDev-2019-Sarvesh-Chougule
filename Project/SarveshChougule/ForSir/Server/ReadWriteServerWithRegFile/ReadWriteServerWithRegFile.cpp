
#include<windows.h>
#include"ReadWriteServerWithRegFile.h"
// class declarations

class CReadWrite : public IRead, IWrite {

private:
	long m_cRef;
public:
	// constructor method declarations
	CReadWrite(void);
	// destructor method declarations 
	~CReadWrite(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IRead specific method declarations (inherited)
	HRESULT __stdcall ReadFileOperation(HANDLE, WCHAR *,DWORD *,BOOL *);
	// IWrite specific method declarations (inherited)
	HRESULT __stdcall WriteFileOperation(HANDLE, WCHAR *, DWORD *,BOOL *);

};

class CReadWriteClassFactory : public IClassFactory {

private:
	long m_cRef;
public:
	// construction method declarations 
	CReadWriteClassFactory(void);
	// destruction method declarations 
	~CReadWriteClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFacotory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};

// global variable declarations 
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this dll

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {

	// code 
	switch (dwReason) {
	
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

// Implementation Of CReadWrite's Constructor Method

CReadWrite::CReadWrite(void) {

	// code
	m_cRef = 1; // harcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);	// increment global counter
}
CReadWrite::~CReadWrite(void) {

	// code 
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter 
}
// Impelementation of CReadWrite's IUnknown's Methods
HRESULT CReadWrite::QueryInterface(REFIID riid, void ** ppv) {

	// code 
	if (riid == IID_IUnknown)
		*ppv = static_cast<IRead *>(this);
	else if (riid == IID_IRead)
		*ppv = static_cast<IRead *>(this);
	else if (riid == IID_IWrite)
		*ppv = static_cast<IWrite *>(this);
	else {
	
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CReadWrite::AddRef(void) {

	// code 
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CReadWrite::Release(void) {

	// code 
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
	
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of IRead's Methods
HRESULT CReadWrite::ReadFileOperation(HANDLE handleFile,WCHAR * strVal,DWORD * wmWritten, BOOL * Variable) {

	//WCHAR STR[255];
	// code 
	*Variable = ReadFile(handleFile, strVal, (DWORD)255, wmWritten, NULL);			// (DWORD)(sizeof(strValue))
	//wsprintf(STR, TEXT("YOUR ANSWER :-  %s"), strVal);
	//MessageBox(NULL, STR, TEXT("Output ....."), MB_OK);
	return(S_OK);
}
// Implementation Of IWrite's Methods
HRESULT CReadWrite::WriteFileOperation(HANDLE handleFile,WCHAR * strData,DWORD * wmWritten, BOOL * Variable) {

	// code 
	*Variable = WriteFile(handleFile, strData, (DWORD)255, wmWritten, NULL);
	return(S_OK);
}
// Implementation Of CReadWriteClassFactory's Constructor Method
CReadWriteClassFactory::CReadWriteClassFactory(void) {

	// code 
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}
CReadWriteClassFactory::~CReadWriteClassFactory(void) {

	// code
}
// Implementation Of CReadWriteClassFactory's IClassFactory's IUnknown's Methods
HRESULT CReadWriteClassFactory::QueryInterface(REFIID riid, void ** ppv) {

	// code 
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
	
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CReadWriteClassFactory::AddRef(void) {

	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CReadWriteClassFactory::Release(void) {

	// code 
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
	
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of CReadWriteClassFactory's IClassFactory's Methods
HRESULT CReadWriteClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {

	// variable declarations
	CReadWrite *pCReadWrite = NULL;
	HRESULT hr;
	// code 
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CReadWrite class
	pCReadWrite = new CReadWrite;
	if (pCReadWrite == NULL)
		return(E_OUTOFMEMORY);
	// get the requested interface
	hr = pCReadWrite->QueryInterface(riid, ppv);
	pCReadWrite->Release();	// anticipate possible failure of QueryInterface() 
	return(hr);
}
HRESULT CReadWriteClassFactory::LockServer(BOOL fLock) {

	// code
	if (fLock)
		InterlockedIncrement(&glNumberOfActiveComponents);
	else
		InterlockedDecrement(&glNumberOfActiveComponents);
	return(S_OK);
}
 HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID  riid, void **ppv) {

	// variable declarations 
	CReadWriteClassFactory *pCReadWriteClassFactory = NULL;
	HRESULT hr;
	// code 
	if (rclsid != CLSID_ReadWrite)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//	create class factory
	pCReadWriteClassFactory = new CReadWriteClassFactory;
	if (pCReadWriteClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCReadWriteClassFactory->QueryInterface(riid, ppv);
	pCReadWriteClassFactory->Release(); // anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {

	// code 
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}



