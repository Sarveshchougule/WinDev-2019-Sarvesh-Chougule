class ISum :public IUnknown {

public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *)=0;	// pure virtual
};
class ISubtract :public IUnknown {

public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;	// pure virtual
};

// CLSID of SumSubtract Component {52C223FD-6AD8-4953-AD94-3D3FBFBDCEB6}

const CLSID CLSID_SumSubtract = { 0x52c223fd, 0x6ad8, 0x4953, 0xad, 0x94, 0x3d, 0x3f, 0xbf, 0xbd, 0xce, 0xb6 };

// IID of ISum Interface {B97D22EA-0C6C-4E5D-9C2E-2F52D6745B32}

const IID IID_ISum = { 0xb97d22ea, 0xc6c, 0x4e5d, 0x9c, 0x2e, 0x2f, 0x52, 0xd6, 0x74, 0x5b, 0x32 };

// IID of ISubtract Interface {751A0660-1E32-452A-94D4-E38B1AD026DC}

const IID IID_ISubtract = { 0x751a0660, 0x1e32, 0x452a, 0x94, 0xd4, 0xe3, 0x8b, 0x1a, 0xd0, 0x26, 0xdc };


