class IMultiplication :public IUnknown {

public:
	// IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0; // pure virutal function
};

class IDivision :public IUnknown {

public:
	// IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0; // pure virtual function
};

// CLSID of MultiplicationDivision Component {CEFE9859-CB5A-413D-854C-336DCEAE45CA}

const CLSID CLSID_MultiplicationDivision = { 0xcefe9859, 0xcb5a, 0x413d, 0x85, 0x4c, 0x33, 0x6d, 0xce, 0xae, 0x45, 0xca };

// IID of IMultiplication Interface {95BEB606-428C-4E4B-BB67-D12F094B7003}

const IID IID_IMultiplication = { 0x95beb606, 0x428c, 0x4e4b, 0xbb, 0x67, 0xd1, 0x2f, 0x9, 0x4b, 0x70, 0x3 };

// IID of IDivision Interface {BBA39E4C-C9C2-4F99-BC50-96BC19162A3A}

const IID IID_IDivision = { 0xbba39e4c, 0xc9c2, 0x4f99, 0xbc, 0x50, 0x96, 0xbc, 0x19, 0x16, 0x2a, 0x3a };


