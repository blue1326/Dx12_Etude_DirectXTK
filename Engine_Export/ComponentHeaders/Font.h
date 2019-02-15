#ifndef Engine_Font_h__
#define Engine_Font_h__
#include "Component.h"
#include "Component_OnDevice.h"
namespace Engine
{
	namespace Components
	{
		class CFont :public CComponent_Device
		{
		public:
			explicit CFont(shared_ptr<DxDevice> _device, const wchar_t* FileLocation);
			virtual ~CFont();
		public:
			virtual HRESULT Init_Component()override;
			virtual HRESULT Prepare_Component()override;

			virtual void Update_Component(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Component(const shared_ptr<CTimer> _timer)override;

			
		public:
			virtual shared_ptr<CComponent>Clone();
			_declspec(dllexport) static shared_ptr<CComponent> Create(const shared_ptr<DxDevice> _device, const wchar_t* _FileLocation);
		private:

			shared_ptr<DirectX::SpriteBatch> m_SpriteBatch;
			shared_ptr<DirectX::SpriteFont> m_font;
			shared_ptr<DirectX::DescriptorHeap> m_Heap;
		public:
			_declspec(dllexport) DirectX::DescriptorHeap* GetHeap() { return m_Heap.get(); }
			_declspec(dllexport) DirectX::SpriteFont* GetFont() { return m_font.get(); }
			_declspec(dllexport) DirectX::SpriteBatch* GetBatch() { return m_SpriteBatch.get(); }
			//shared_ptr<DirectX::CommonStates> m_State;
		private:
			const wchar_t* m_FileLocation;

		};


	}
}

#endif // Font_h__
