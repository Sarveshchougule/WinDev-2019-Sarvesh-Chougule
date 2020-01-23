class IRead : public IUnknown {

public:
	// IRead specific method declarations 
	virtual HRESULT __stdcall ReadFileOperation(HANDLE,WCHAR *,DWORD *, BOOL *) = 0;				// pure virtual function 
};
class IWrite : public IUnknown {

public:
	// IWrite speciic method declarations
	virtual HRESULT __stdcall WriteFileOperation(HANDLE,WCHAR *,DWORD *, BOOL *) = 0;				// pure virtual function 
};

// CLSID CLSID_ReadWrite Component {329E9E9C-5CA3-4541-B35A-0F4E4A5F67AF}

const CLSID CLSID_ReadWrite = { 0x329e9e9c, 0x5ca3, 0x4541, 0xb3, 0x5a, 0xf, 0x4e, 0x4a, 0x5f, 0x67, 0xaf };

// IID of IRead interface {1C451D2A-47AE-422C-A4FA-7A28820F9398}

const IID IID_IRead = { 0x1c451d2a, 0x47ae, 0x422c, 0xa4, 0xfa, 0x7a, 0x28, 0x82, 0xf, 0x93, 0x98 };

// IID of IWrite interface {723B8904-E16F-43C0-BEED-68CC72D7069C}

const IID IID_IWrite = { 0x723b8904, 0xe16f, 0x43c0, 0xbe, 0xed, 0x68, 0xcc, 0x72, 0xd7, 0x6, 0x9c };


