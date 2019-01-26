#ifndef Engine_Component_h__
#define Engine_Component_h__
#include "Export_System.h"
using namespace Engine::System;
namespace Engine
{
	namespace Components
	{
		class CComponent : public std::enable_shared_from_this<CComponent>
		{
		public:
			explicit CComponent();
			explicit CComponent(const CComponent& rhs) = delete;
			virtual ~CComponent();
		public:
			_declspec(dllexport) virtual HRESULT Init_Component()=0;
			_declspec(dllexport) virtual HRESULT Prepare_Component() = 0;

			_declspec(dllexport) virtual void Update_Component(const shared_ptr<CTimer> _timer) = 0;

		public:
			_declspec(dllexport) virtual shared_ptr<CComponent>Clone() = 0;
		private:

		};

	}
}





#endif // Component_h__
