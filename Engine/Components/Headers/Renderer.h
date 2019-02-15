#ifndef Engine_Renderer_h__
#define Engine_Renderer_h__
#include "Component.h"
#include "Component_OnDevice.h"
#include "DxDevice.h"
#include "Object.h"
using namespace Engine::System;
namespace Engine
{
	namespace Components
	{
		class CRenderer : public CComponent_Device
		{
		public:
			enum RENDER {
				RENDER_DEBUG,
				RENDER_PRIORITY, RENDER_NONEALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END
			};
		public:
			explicit CRenderer(const shared_ptr<DxDevice> _device);
			explicit CRenderer(const CRenderer& rhs) = delete;
			virtual ~CRenderer();
		public:
			virtual HRESULT Init_Component()override;
			virtual HRESULT Prepare_Component()override;

			virtual void Update_Component(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Component(const shared_ptr<CTimer> _timer)override;
			_declspec(dllexport) void Render(ID3D12GraphicsCommandList* cmdlist);


		public:
			HRESULT Add_RenderList(RENDER eType, shared_ptr<CObject> object);
		private:
			void RenderNoneAlpha(ID3D12GraphicsCommandList* cmdlist);
			void RenderUI(ID3D12GraphicsCommandList* cmdlist);
			void Clear_RenderList();
		public:
			virtual shared_ptr<CComponent>Clone()override;
			_declspec(dllexport) static shared_ptr<CComponent>Create(const shared_ptr<DxDevice> _device);
		/*private:
			const shared_ptr<DxDevice> m_DxDevice;*/

		private:
			typedef list<shared_ptr<CObject>>		RENDERLIST;
			RENDERLIST				m_RenderList[RENDER_END];
			
		};
	}
}

#endif // Renderer_h__
