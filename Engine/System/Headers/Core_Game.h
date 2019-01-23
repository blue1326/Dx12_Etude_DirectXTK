#ifndef Engine_Core_Game_h__
#define Engine_Core_Game_h__
#include "AppCore.h"
#include "DxDevice.h"
#include "Timer.h"
namespace Engine
{
	namespace System
	{
		class AppCore_Game :public AppCore
		{
		public:
			explicit AppCore_Game()noexcept(false);
			virtual ~AppCore_Game();

			_declspec(dllexport) static shared_ptr<AppCore_Game> Create(HWND window, int width, int height);

			void Initialize(HWND window, int width, int height);

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

			void CreateDeviceDependentResources();
			void CreateWindowSizeDependentResources();



		private:
			shared_ptr<DxDevice> m_Device;
			shared_ptr<DirectX::GamePad> m_Gamepad;
			shared_ptr<DirectX::Keyboard> m_Keyboard;
			shared_ptr<DirectX::Mouse> m_Mouse;
			shared_ptr<CTimer> m_MainTimer;
			///shared_ptr<void> tmp;

			std::unique_ptr<DirectX::GraphicsMemory> m_graphicsMemory;
			



		private://matrix
			DirectX::SimpleMath::Matrix                                             m_world;
			DirectX::SimpleMath::Matrix                                             m_view;
			DirectX::SimpleMath::Matrix                                             m_projection;
		};
	}
}
#endif // Engine_Core_Game_h__
