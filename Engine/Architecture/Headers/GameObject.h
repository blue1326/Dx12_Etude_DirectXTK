#ifndef Engine_GameObject_h__
#define Engine_GameObject_h__

#include "Object.h"
#include "Component.h"
using namespace Engine::Components;
namespace Engine
{
	namespace Architecture
	{
		class CGameObject : public CObject
		{
		public:
			explicit CGameObject(const shared_ptr<DxDevice> _device);
			explicit CGameObject(const CGameObject& rhs) = delete;
			virtual ~CGameObject();

		public:
			virtual HRESULT Init_Object() = 0;
			virtual void Update_Object(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer)override;
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist) = 0;

		protected:
			HRESULT Prepare_Object();

		protected:
			HRESULT AddComponent(const wchar_t* _tag, shared_ptr<CComponent> _component);
			typedef map<const wchar_t*, shared_ptr<CComponent>> MAPCOMPONENT;
			MAPCOMPONENT m_Components;

			HRESULT CheckComponentNullptr();

			void Free();


		private:
			std::shared_ptr<CComponent> Find_Component(const wchar_t* _ComponentName);
		};
	}
}


#endif // GameObject_h__
