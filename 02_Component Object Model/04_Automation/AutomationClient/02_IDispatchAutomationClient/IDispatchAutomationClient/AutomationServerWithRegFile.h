
class IMyMath :public IDispatch {

public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *)=0;		// pure virtual function 
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0; // pure virtual function

};

// CLSID Of MyMath Component  : {72F41EB2-0CD2-4A49-8E9D-18716E90B80C}

const CLSID  CLSID_MyMath = { 0x72f41eb2, 0xcd2, 0x4a49, 0x8e, 0x9d, 0x18, 0x71, 0x6e, 0x90, 0xb8, 0xc };		// ---1

// IID Of IMyMath Interface : {B0FE292F-19A0-4902-BCAA-F3003C3DC3A1}

const IID IID_IMyMath = { 0xb0fe292f, 0x19a0, 0x4902, 0xbc, 0xaa, 0xf3, 0x0, 0x3c, 0x3d, 0xc3, 0xa1 };			// ---3

