#ifndef Engine_PlexibleObject_h__
#define Engine_PlexibleObject_h__
#include "GameObject.h"

namespace Engine
{
	namespace Architecture
	{
		class CPlexibleObject : public CGameObject
		{
		public:
			explicit CPlexibleObject(const shared_ptr<DxDevice> _device);
			explicit CPlexibleObject(const CPlexibleObject& rhs) = delete;
			virtual ~CPlexibleObject();

		public:
			virtual HRESULT Init_Object()override;
			virtual void Update_Object(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer)override;
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist)override;
			

		public:
			static shared_ptr<CObject> Create(const shared_ptr<DxDevice> _device);
		public:
			enum UPDATESIGN{UP_BASIC,UP_LATE,UP_END};
		protected:
			HRESULT(*m_init)(MAPCOMPONENT _components);
			void(*m_update[UP_END])(const shared_ptr<CTimer> _timer, MAPCOMPONENT _components);
			//void(*lateupdate)(const shared_ptr<CTimer> _timer, MAPCOMPONENT _components);
			void(*m_render)(ID3D12GraphicsCommandList* cmdlist, MAPCOMPONENT _components);
		public:
			void SetFunction(HRESULT(*_init)(MAPCOMPONENT ));
			void SetFunction(void(*_update)(const shared_ptr<CTimer> , MAPCOMPONENT ), UPDATESIGN _sign);
			void SetFunction(void(*_render)(ID3D12GraphicsCommandList* , MAPCOMPONENT ));
		protected:
			void ResetFunctions();

		};


	}
}

#endif // PlexibleObject_h__
