#ifndef Engine_WinSetUp_h__
#define Engine_WinSetUp_h__
//#include <string>
using namespace std;
namespace WinSet
{
	class _declspec(dllexport) CMainWinSetUp
	{
	public:
		CMainWinSetUp(HINSTANCE hinstance);
		CMainWinSetUp(HINSTANCE hinstance, WNDCLASSEXW _wc,const wchar_t* _caption);
		CMainWinSetUp(const CMainWinSetUp& rhs) = delete;
		CMainWinSetUp& operator = (const CMainWinSetUp& rhs) = delete;
		virtual ~CMainWinSetUp();


		bool InitWindow();

		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


		virtual int Run();

		int GetClientWidth(){ return m_ClientWidth; }
		int GetClientHeight() { return m_ClientHeight; }
	protected:
		HINSTANCE m_hAppinst;
		HWND m_hWnd;
		WNDCLASSEXW m_WC;
		bool isWcCustomize;
		int m_SubSysIdx;
		bool isPaused;
		wchar_t m_WndCaption[255];

		int m_ClientWidth, m_ClientHeight;

		bool isSizemove;
		bool isSuspend;
		bool isMinimized;
		bool isfullscreen;
		//wstring m_WndCaption;
	};
}

#endif // WinSetUp_h__
