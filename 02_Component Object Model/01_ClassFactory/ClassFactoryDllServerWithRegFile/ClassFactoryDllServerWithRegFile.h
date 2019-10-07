
class ISum :public IUnknown {

public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;			// pure virtual function
};

class ISubtract :public IUnknown {

public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;	// pure virtual function
};

// CLSID CLSID_SumSubtract Component {BD096D65-5DAF-4FAE-B0A4-E1001C24A28A}

const CLSID CLSID_SumSubtract = { 0xbd096d65, 0x5daf, 0x4fae, 0xb0, 0xa4, 0xe1, 0x0, 0x1c, 0x24, 0xa2, 0x8a };

// IID of ISum interface {A509E255-7E3C-4561-817F-E7BA57AB886C}

const IID IID_ISum = { 0xa509e255, 0x7e3c, 0x4561, 0x81, 0x7f, 0xe7, 0xba, 0x57, 0xab, 0x88, 0x6c };

// IID of ISubtract interface {FF8767DF-C015-46A6-8472-EF1081A21404}

const IID IID_ISubtract = { 0xff8767df, 0xc015, 0x46a6, 0x84, 0x72, 0xef, 0x10, 0x81, 0xa2, 0x14, 0x4 };


