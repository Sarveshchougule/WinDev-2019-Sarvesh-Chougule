class ISum :public IUnknown {

public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;	// pure virtual
};

class ISubtract :public IUnknown {

public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;	// pure virtual
};

class IMultiplication :public IUnknown {

public:
	// IMultiplication specific method declarations 
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;	// pure virtual
};

class IDivision :public IUnknown {

public:
	// IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;	// pure virtual
};

// CLSID of SumSubtract Component {52C223FD-6AD8-4953-AD94-3D3FBFBDCEB6}

const CLSID CLSID_SumSubtract = { 0x52c223fd, 0x6ad8, 0x4953, 0xad, 0x94, 0x3d, 0x3f, 0xbf, 0xbd, 0xce, 0xb6 };

// IID of ISum Interface {B97D22EA-0C6C-4E5D-9C2E-2F52D6745B32}

const IID IID_ISum = { 0xb97d22ea, 0xc6c, 0x4e5d, 0x9c, 0x2e, 0x2f, 0x52, 0xd6, 0x74, 0x5b, 0x32 };

// IID of ISubtract Interface {751A0660-1E32-452A-94D4-E38B1AD026DC}

const IID IID_ISubtract = { 0x751a0660, 0x1e32, 0x452a, 0x94, 0xd4, 0xe3, 0x8b, 0x1a, 0xd0, 0x26, 0xdc };

// CLSID of MultiplicationDivision Component {926CDC9F-3D32-4898-9312-F8CCB711D707}

const CLSID CLSID_MultiplicationDivision = { 0x926cdc9f, 0x3d32, 0x4898, 0x93, 0x12, 0xf8, 0xcc, 0xb7, 0x11, 0xd7, 0x7 };

// IID of IMultiplication Interface {D30A4304-815E-495F-9590-F2A5B5E6892E}

const IID IID_IMultiplication = { 0xd30a4304, 0x815e, 0x495f, 0x95, 0x90, 0xf2, 0xa5, 0xb5, 0xe6, 0x89, 0x2e };

// IID of IDivision Interface {9B00D987-82DD-46A3-AC0B-4A0C8BBAAFDF}

const IID IID_IDivision = { 0x9b00d987, 0x82dd, 0x46a3, 0xac, 0xb, 0x4a, 0xc, 0x8b, 0xba, 0xaf, 0xdf };

