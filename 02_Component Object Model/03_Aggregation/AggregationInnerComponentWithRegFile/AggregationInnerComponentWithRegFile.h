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

// CLSID of MultiplicationDivision Component {926CDC9F-3D32-4898-9312-F8CCB711D707}

const CLSID CLSID_MultiplicationDivision = { 0x926cdc9f, 0x3d32, 0x4898, 0x93, 0x12, 0xf8, 0xcc, 0xb7, 0x11, 0xd7, 0x7 };

// IID of IMultiplication Interface {D30A4304-815E-495F-9590-F2A5B5E6892E}

const IID IID_IMultiplication = { 0xd30a4304, 0x815e, 0x495f, 0x95, 0x90, 0xf2, 0xa5, 0xb5, 0xe6, 0x89, 0x2e };

// IID of IDivision Interface {9B00D987-82DD-46A3-AC0B-4A0C8BBAAFDF}

const IID IID_IDivision = { 0x9b00d987, 0x82dd, 0x46a3, 0xac, 0xb, 0x4a, 0xc, 0x8b, 0xba, 0xaf, 0xdf };

