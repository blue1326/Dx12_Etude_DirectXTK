#ifndef Engine_Renderer_h__
#define Engine_Renderer_h__
#include "Component.h"
#include "DxDevice.h"
using namespace Engine::System;
namespace Engine
{
	namespace Components
	{
		class CRenderer : public CComponent
		{
		public:
			enum RENDER {
				RENDER_PRIORITY, RENDER_NONEALPHA, RENDER_ALPHA, RENDER_UI, RENDER_DEBUG,RENDER_END
			};
		public:
			explicit CRenderer(const shared_ptr<DxDevice> _device);
			explicit CRenderer(const CRenderer& rhs) = delete;
			virtual ~CRenderer();
		public:
			virtual HRESULT Init_Component()override;
			virtual HRESULT Prepare_Component()override;

			virtual void Update_Component(const shared_ptr<CTimer> _timer)override;
			_declspec(dllexport) void Render();
		public:
			virtual shared_ptr<CComponent>Clone()override;
			_declspec(dllexport) static shared_ptr<CComponent>Create(const shared_ptr<DxDevice> _device);
		private:
			const shared_ptr<DxDevice> m_DxDevice;

		private:
			list<shared_ptr<void>>				m_RenderList[RENDER_END];
			typedef list<shared_ptr<void>>		RENDERLIST;
		};
	}
}

#endif // Renderer_h__
