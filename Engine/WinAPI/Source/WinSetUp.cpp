#include "stdafx.h"
#include "WinSetUp.h"
#include "GlobalFunc.h"
using namespace WinSet;
using namespace std;


//_declspec(dllexport) int g_ClientWidth = 800, g_ClientHeight = 600;
_declspec(dllexport) HINSTANCE g_hInst;
_declspec(dllexport) HWND g_hWnd;
_declspec(dllexport) void* g_MainWnd = nullptr;
//void** g_Wnds = nullptr; //나중에 추가할 것

//int wndCount = 0;
//int maxWnd = 10;


CMainWinSetUp::CMainWinSetUp(HINSTANCE hinstance)
	:m_hAppinst(nullptr)
	, m_hWnd(nullptr)
	, isWcCustomize(false)
	, isPaused(false)
	, m_ClientHeight(600)
	, m_ClientWidth(800)
	, isSizemove(false)
	, isSuspend(false)
	, isMinimized(false)
	, isfullscreen(false)
	,AdditionalMsgProc(nullptr)
{
	wcscpy_s(m_WndCaption, L"d3d App");
	g_MainWnd = this;

}

WinSet::CMainWinSetUp::CMainWinSetUp(HINSTANCE hinstance, WNDCLASSEXW _wc, const wchar_t* _caption)
	:m_hAppinst(nullptr)
	, m_hWnd(nullptr)
	, m_WC(_wc)
	, isWcCustomize(true)
	, isPaused(false)
	, m_SubSysIdx(0)
{
	wcscpy_s(m_WndCaption, _caption);
	/*if (ClientGlobals::g_Wnds == nullptr)
	{
		ClientGlobals::g_Wnds = new void*[ClientGlobals::maxWnd];
	}
	ClientGlobals::g_Wnds[ClientGlobals::wndCount] = this;
	m_SubSysIdx = ClientGlobals::wndCount;
	ClientGlobals::wndCount++;*/
}

CMainWinSetUp::~CMainWinSetUp()
{
	g_MainWnd = nullptr;
	/*if (ClientGlobals::g_Wnds != nullptr)
	{
		for (int i = 0; i < ClientGlobals::maxWnd; i++)
		{
			ClientGlobals::g_Wnds[i] = nullptr;
		}
		delete(ClientGlobals::g_Wnds);
		ClientGlobals::g_Wnds = nullptr;
	}*/
}

bool WinSet::CMainWinSetUp::InitWindow()
{
	if (!isWcCustomize)
	{
		m_WC.cbSize = sizeof(WNDCLASSEX);

		m_WC.style = CS_HREDRAW | CS_VREDRAW;
		m_WC.lpfnWndProc = MainWndProc;
		m_WC.cbClsExtra = 0;
		m_WC.cbWndExtra = 0;
		m_WC.hInstance = m_hAppinst;
		m_WC.hIcon = LoadIcon(0, IDI_APPLICATION);
		m_WC.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		m_WC.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_CLIENT);
		m_WC.lpszClassName = m_WndCaption;
		m_WC.hIconSm = LoadIcon(m_WC.hInstance, IDI_APPLICATION);
	}
	else
	{



		m_WC.lpfnWndProc = SubWndProc;
	}
	if (!RegisterClassExW(&m_WC))
	{
		MessageBox(0, L"RegisterClass Fail", 0, 0);
		return false;
	}

	RECT R = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;
	m_hWnd = CreateWindow(m_WC.lpszClassName, m_WndCaption,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hAppinst, 0);
	if (!m_hWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	if (!isWcCustomize)
	{
		g_hInst = m_hAppinst;
		g_hWnd = m_hWnd;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	return true;
}

LRESULT WinSet::CMainWinSetUp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	if (AdditionalMsgProc != nullptr)
		AdditionalMsgProc(hwnd,msg,wParam,lParam);
	return 0;
}




void WinSet::CMainWinSetUp::SetAdditionalMsgProc(LRESULT(*_msgproc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam))
{
	AdditionalMsgProc = _msgproc;
}

int WinSet::CMainWinSetUp::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		//peeking Windows Message
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//OtherWise aonther actions
		else
		{


			if (!isPaused)
			{


			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int)msg.wParam;

}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return static_cast<CMainWinSetUp*>(g_MainWnd)->MsgProc(hwnd, msg, wParam, lParam);
	//CApiSetUP::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK SubWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}