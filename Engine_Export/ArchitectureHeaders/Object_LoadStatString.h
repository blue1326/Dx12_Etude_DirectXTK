#ifndef Engine_Object_LoadStatString_h__
#define Engine_Object_LoadStatString_h__
#include "UIObject.h"

namespace Engine
{ 
	namespace Architecture
	{
		class CObject_LoadStatString : public CUIObject
		{
		public:
			explicit CObject_LoadStatString(const shared_ptr<DxDevice> _device);
			explicit CObject_LoadStatString(const CObject_LoadStatString& rhs) = delete;
			virtual ~CObject_LoadStatString();

		public:
			virtual HRESULT Init_Object()override;
			virtual void Update_Object(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer)override;
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist)override;

			void PushText(const wchar_t* _text);
			const wchar_t* GetLastText();

		private:
			list<shared_ptr<wstring>> m_Texts;
			wstring m_LoadStatText;
			wchar_t m_LastText[255];

		public:
			static shared_ptr<CObject> Create(const shared_ptr<DxDevice> _device);
		
		//private:
		//	void tmp(void *fp ());
		//	void (*fp)();

		};

	
	}
}

#endif // Object_LoadStatString_h__


