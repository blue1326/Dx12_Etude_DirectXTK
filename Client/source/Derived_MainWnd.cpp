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
	MSG msg = { 0 };
	shared_ptr<Engine::System::AppCore_Game> inst =  Engine::System::AppCore_Game::Create(m_hWnd, m_ClientWidth, m_ClientHeight);
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
			inst->Tick();

			if (!isPaused)
			{
				inst->Update();
				inst->Render();
				inst->LateUpdate();

			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int)msg.wParam;
}


