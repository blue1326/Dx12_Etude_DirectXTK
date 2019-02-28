#ifndef Engine_Control_h__
#define Engine_Control_h__
#include "Component.h"

using namespace DirectX;
namespace Engine
{
	namespace Components
	{
		class CControl : public CComponent
		{
		public:
			explicit CControl();
			explicit CControl(const CControl& rhs) = delete;
			virtual ~CControl();
		public:
			_declspec(dllexport) virtual HRESULT Init_Component()override;
			_declspec(dllexport) virtual HRESULT Prepare_Component()override;

			_declspec(dllexport) virtual void Update_Component(const shared_ptr<CTimer> _timer)override;
			_declspec(dllexport) virtual void LateUpdate_Component(const shared_ptr<CTimer> _timer)override;

			//_declspec(dllexport) void UpdateTracker(const GamePad::State& _pad,const Keyboard::State& _keyboard, const Mouse::State& _mouse);
			_declspec(dllexport) void UpdateTracker(const GamePad::State& _pad);
			_declspec(dllexport) void UpdateTracker(const Keyboard::State& _keyboard);
			_declspec(dllexport) void UpdateTracker(const Mouse::State& _mouse);
		public:
			_declspec(dllexport) virtual shared_ptr<CComponent>Clone();
			_declspec(dllexport) static shared_ptr<CComponent> Create();
		public:
			_declspec(dllexport) GamePad::ButtonStateTracker GetPadTracker() { return m_PadTracker; }
			_declspec(dllexport) Keyboard::KeyboardStateTracker GetKeyTracker() { return m_KeybordTracker; }
			_declspec(dllexport) Mouse::ButtonStateTracker GetMouseTracker() { return m_MouseTracker; }

			_declspec(dllexport) void Reset();
		private:
			GamePad::ButtonStateTracker m_PadTracker;
			Keyboard::KeyboardStateTracker m_KeybordTracker;
			Mouse::ButtonStateTracker m_MouseTracker;
		};

	}
}

#endif // Control_h__
