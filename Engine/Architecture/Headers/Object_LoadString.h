#ifndef Engine_Object_LoadString_h__
#define Engine_Object_LoadString_h__
#include "UIObject.h"

namespace Engine
{
	namespace Architecture
	{
		class CObject_LoadString : public CUIObject
		{
		public:
			explicit CObject_LoadString(const shared_ptr<DxDevice> _device);
			explicit CObject_LoadString(const CObject_LoadString& rhs) = delete;
			virtual ~CObject_LoadString();

		public:
			virtual HRESULT Init_Object()override;
			virtual void Update_Object(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer)override;
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist)override;

			void PushText(const wchar_t* _text);
			const wchar_t* GetLastText();

		
		public:
			static shared_ptr<CObject> Create(const shared_ptr<DxDevice> _device);
		private:

		};


	}
}

#endif // Object_LoadString_h__
