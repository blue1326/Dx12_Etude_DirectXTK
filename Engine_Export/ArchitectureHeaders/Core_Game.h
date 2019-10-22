#ifndef Engine_Core_Game_h__
#define Engine_Core_Game_h__
#include "AppCore.h"
#include "DxDevice.h"
#include "Timer.h"
//#include "Renderer.h"
#include "Control.h"
#include "Component.h"
#include "Object.h"
#include "Phase.h"
#include "CThreadHolder.h"
using namespace Engine::System;
using namespace Engine::Components;

using namespace ThreadPool;

namespace Engine
{
	namespace Architecture
	{
		class AppCore_Game :public AppCore
		{
		public:
			explicit AppCore_Game()noexcept(false);
			virtual ~AppCore_Game();

			_declspec(dllexport) static shared_ptr<AppCore_Game> Create(HWND window, int width, int height);

			void Initialize(HWND window, int width, int height);
			_declspec(dllexport)void ResizeWindow(HWND window, int width, int height);

			static _declspec(dllexport) LRESULT AdditionalMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

			// Basic game loop
			_declspec(dllexport) void Tick();

			// IDeviceNotify
			_declspec(dllexport) virtual void OnDeviceLost() override;
			_declspec(dllexport) virtual void OnDeviceRestored() override;

			// Messages
			_declspec(dllexport) void OnActivated();
			_declspec(dllexport) void OnDeactivated();
			_declspec(dllexport) void OnSuspending();
			_declspec(dllexport) void OnResuming();
			_declspec(dllexport) void OnWindowMoved();
			_declspec(dllexport) void OnWindowSizeChanged(int width, int height);
			_declspec(dllexport) void NewAudioDevice();

			// Properties
			_declspec(dllexport) void GetDefaultSize(int& width, int& height) const;

		public:
			_declspec(dllexport) void Update();
			_declspec(dllexport) void LateUpdate();
			_declspec(dllexport) void Render();
			void Clear();
		private:
			void CreateDeviceDependentResources();
			void CreateWindowSizeDependentResources();

		private:
			void LoadPreLoadComponents();

		public:
			_declspec(dllexport) bool CalculateFrameStats();

		private:
			shared_ptr<DxDevice> m_Device;
			//unique_ptr<DirectX::GamePad> m_Gamepad;
			unique_ptr<DirectX::Keyboard> m_Keyboard;
			unique_ptr<DirectX::Mouse> m_Mouse;
	/*		shared_ptr<CPad> m_Gamepad;
			shared_ptr<CKeyboard> m_Keyboard;
			shared_ptr<CMouse> m_Mouse;*/
			
			shared_ptr<CTimer> m_MainTimer;
			///shared_ptr<void> tmp;

			shared_ptr<CComponent> m_Renderer;
			shared_ptr<CComponent> m_Control;

			typedef map<const wchar_t*, shared_ptr<CObject>> MAPOBJCTS;
			MAPOBJCTS m_DebugObjects;
			typedef map<const wchar_t*, shared_ptr<CPhase>> MAPPHASE;
			MAPPHASE m_Phase;
			shared_ptr<CPhase> m_ActivePhase;
			std::unique_ptr<DirectX::GraphicsMemory> m_graphicsMemory;
			
			shared_ptr<CThreadHolder> m_ThreadPool;

		private://for FrameLimits
			float m_fTimeAcc;
			float m_CallPerSec;
		public:
			_declspec(dllexport) void SetFramelateLimit(const float& _Limit);
			int frameCnt;
			int frameCntLimit;
			float timeElapsed;

		private:
			bool Check_OneLivePhase();
			void SetUp_ActivePhase();

		private://matrix
			DirectX::SimpleMath::Matrix                                             m_world;
			DirectX::SimpleMath::Matrix                                             m_view;
			DirectX::SimpleMath::Matrix                                             m_projection;
		};
	}
}
#endif // Engine_Core_Game_h__
