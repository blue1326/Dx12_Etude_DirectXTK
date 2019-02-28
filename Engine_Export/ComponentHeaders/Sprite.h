#ifndef Engine_Sprite_h__
#define Engine_Sprite_h__
#include "Component.h"
#include "Component_OnDevice.h"
namespace Engine
{
	namespace Components
	{
		class CSprite : public CComponent_Device
		{
		public:
			explicit CSprite(const shared_ptr<DxDevice> _device, const wchar_t* FileLocation);
			virtual ~CSprite();
		public:
			virtual HRESULT Init_Component()override;
			virtual HRESULT Prepare_Component()override;

			virtual void Update_Component(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Component(const shared_ptr<CTimer> _timer)override;
		public:
			virtual shared_ptr<CComponent>Clone();

			_declspec(dllexport) static shared_ptr<CComponent> Create(const shared_ptr<DxDevice> _device,const wchar_t* _FileLocation);
		private:
			shared_ptr<DirectX::SpriteBatch> m_SpriteBatch;
			shared_ptr<DirectX::DescriptorHeap> m_Heap;
			Microsoft::WRL::ComPtr<ID3D12Resource>                                  m_texture;
		public:
			_declspec(dllexport) DirectX::DescriptorHeap* GetHeap() { return m_Heap.get(); }
			_declspec(dllexport) DirectX::SpriteBatch* GetBatch() { return m_SpriteBatch.get(); }
			_declspec(dllexport) ID3D12Resource* GetResource() { return m_texture.Get(); }
		private:
			const wchar_t* m_FileLocation;
		};


	}
}

#endif // Sprite_h__
