#ifndef Derived_MainWnd_h__
#define Derived_MainWnd_h__

#include "GenericHeader.h"

class Derived_MainWnd:public WinSet::CMainWinSetUp
{
public:
	explicit Derived_MainWnd(HINSTANCE hinstance);
	explicit Derived_MainWnd(HINSTANCE hinstance, WNDCLASSEXW _wc, const wchar_t* _caption) = delete;
	virtual ~Derived_MainWnd();
	Derived_MainWnd(const Derived_MainWnd& rhs) = delete;
	Derived_MainWnd& operator = (const Derived_MainWnd& rhs) = delete;


	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int Run();

public:

	void DeviceInitialize();

private:



};

#endif // Derived_MainWnd_h__
