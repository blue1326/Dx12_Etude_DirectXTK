#ifndef Engine_Component_OnDevice_h__
#define Engine_Component_OnDevice_h__

#include "Export_System.h"
#include "Component.h"
using namespace Engine::System;
namespace Engine
{
	namespace Components
	{
		class CComponent_Device : public CComponent
		{
		public:
			explicit CComponent_Device(const shared_ptr<DxDevice> _device);
			explicit CComponent_Device(const CComponent_Device& rhs);
			virtual ~CComponent_Device();
		public:
			_declspec(dllexport) virtual HRESULT Init_Component() = 0;
			_declspec(dllexport) virtual HRESULT Prepare_Component() = 0;

			_declspec(dllexport) virtual void Update_Component(const shared_ptr<CTimer> _timer) = 0;
			_declspec(dllexport) virtual void LateUpdate_Component(const shared_ptr<CTimer> _timer) = 0;

		public:
			_declspec(dllexport) virtual shared_ptr<CComponent>Clone() = 0;
		private:

		protected:
			shared_ptr<DxDevice> m_DxDevice;
		};

	}
}




#endif // Component_OnDevice_h__
