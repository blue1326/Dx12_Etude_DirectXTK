#include "stdafx.h"
#include "Derived_MainWnd.h"

Derived_MainWnd::Derived_MainWnd(HINSTANCE hinstance)
	:CMainWinSetUp(hinstance)
{

}

Derived_MainWnd::~Derived_MainWnd()
{

}

LRESULT Derived_MainWnd::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return CMainWinSetUp::MsgProc(hwnd, msg, wParam, lParam);
}

int Derived_MainWnd::Run()
{
	return CMainWinSetUp::Run();
}


