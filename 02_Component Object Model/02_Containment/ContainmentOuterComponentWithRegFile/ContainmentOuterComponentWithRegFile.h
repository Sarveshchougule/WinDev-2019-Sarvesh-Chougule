class ISum : public IUnknown {

public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0; // pure virtual function
};
class ISubtract : public IUnknown {

public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0; // pure virtual function
};

// CLSID of SumSubtract Component {E3978A9A-3D04-4EC2-8D51-2FA7E963C735}

const CLSID CLSID_SumSubtract = { 0xe3978a9a, 0x3d04, 0x4ec2, 0x8d, 0x51, 0x2f, 0xa7, 0xe9, 0x63, 0xc7, 0x35 };

// IID of ISum Interface {09A6096E-3055-4545-90C5-A6A6BF1B994A}

const IID IID_ISum = { 0x9a6096e, 0x3055, 0x4545, 0x90, 0xc5, 0xa6, 0xa6, 0xbf, 0x1b, 0x99, 0x4a };

// IID of ISubtract Interface {A7A64CC1-C6D5-4A8D-ABC0-0CE537506CD7}

const IID IID_ISubtract = { 0xa7a64cc1, 0xc6d5, 0x4a8d, 0xab, 0xc0, 0xc, 0xe5, 0x37, 0x50, 0x6c, 0xd7 };



