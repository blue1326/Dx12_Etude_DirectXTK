#include "stdafx.h"
#include "Derived_MainWnd.h"

Derived_MainWnd::Derived_MainWnd(HINSTANCE hinstance)
	:CMainWinSetUp(hinstance)
	,m_AppInst(nullptr)
{

}

Derived_MainWnd::~Derived_MainWnd()
{
	AdditionalMsgProc = nullptr;
 }

LRESULT Derived_MainWnd::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;

	case WM_CLOSE:
		/*if (g_hNewAudio)
		{
			UnregisterDeviceNotification(g_hNewAudio);
			g_hNewAudio = nullptr;
		}*/
		DestroyWindow(hwnd);
		break;

	case WM_DEVICECHANGE:

		return 0;

	case WM_PAINT:

		break;

	case WM_MOVE:
		if (m_AppInst)
		{
			m_AppInst->OnWindowMoved();
		}
		break;

	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
		{
			if (!isMinimized)
			{
				isMinimized = true;
				if (!isSuspend && m_AppInst)
					m_AppInst->OnSuspending();
				isSuspend = true;
			}
		}
		else if (isMinimized)
		{
			isMinimized = false;
			if (isSuspend && m_AppInst)
				m_AppInst->OnResuming();
			isSuspend = false;
		}
		else if (!isSizemove && m_AppInst)
		{
			m_AppInst->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
		}
		break;

	case WM_ENTERSIZEMOVE:
		isSizemove = true;
		break;

	case WM_EXITSIZEMOVE:
		isSizemove = false;
		if (m_AppInst)
		{
			RECT rc;
			GetClientRect(hwnd, &rc);

			m_AppInst->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
		}
		break;

	case WM_GETMINMAXINFO:
	{
		auto info = reinterpret_cast<MINMAXINFO*>(lParam);
		info->ptMinTrackSize.x = 320;
		info->ptMinTrackSize.y = 200;
	}
	break;

	case WM_ACTIVATEAPP:
		if (m_AppInst)
		{
			if (wParam)
			{
				m_AppInst->OnActivated();
			}
			else
			{
				m_AppInst->OnDeactivated();
			}
		}
		break;

	case WM_POWERBROADCAST:
		switch (wParam)
		{
		case PBT_APMQUERYSUSPEND:
			if (!isSuspend && m_AppInst)
				m_AppInst->OnSuspending();
			isSuspend = true;
			return TRUE;

		case PBT_APMRESUMESUSPEND:
			if (!isMinimized)
			{
				if (isSuspend && m_AppInst)
					m_AppInst->OnResuming();
				isSuspend = false;
			}
			return TRUE;
		}
		break;

		/*case WM_DESTROY:
			PostQuitMessage(0);
			break;*/

	case WM_SYSKEYDOWN:
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// Implements the classic ALT+ENTER fullscreen toggle
			if (isfullscreen)
			{
				SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowLongPtr(hwnd, GWL_EXSTYLE, 0);

				int width = 800;
				int height = 600;
				if (m_AppInst)
					m_AppInst->GetDefaultSize(width, height);

				ShowWindow(hwnd, SW_SHOWNORMAL);

				SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			else
			{
				SetWindowLongPtr(hwnd, GWL_STYLE, 0);
				SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);

				SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

		

				ShowWindow(hwnd, SW_SHOWMAXIMIZED);
			}

			isfullscreen = !isfullscreen;
		}
		break;

	case WM_MENUCHAR:
		// A menu is active and the user presses a key that does not correspond
		// to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
		return MAKELRESULT(0, MNC_CLOSE);
	}
	CMainWinSetUp::MsgProc(hwnd, msg, wParam, lParam);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int Derived_MainWnd::Run()
{
	MSG msg = { 0 };
	m_AppInst =  Engine::Architecture::AppCore_Game::Create(m_hWnd, m_ClientWidth, m_ClientHeight);
	m_AppInst->SetFramelateLimit(60.f);
	CMainWinSetUp::SetAdditionalMsgProc(Engine::Architecture::AppCore_Game::AdditionalMsgProc);
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
			m_AppInst->Tick();

			if (!isPaused)
			{
				if (m_AppInst->CalculateFrameStats())
				{
					m_AppInst->Update();
					m_AppInst->Render();
					m_AppInst->LateUpdate();
				}
				else
				{
					int i = 0;
				}
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int)msg.wParam;
}


