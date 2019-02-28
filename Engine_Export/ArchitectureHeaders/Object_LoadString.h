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

			void SetFlag(const bool _flag);
			const bool GetFlag() { return isLoadCompleate; }
			void SetLoadingPercentage(const float _percentage);
			const bool GetPhaseFlag() { return isPhaseChage; }

		private:
			wchar_t m_LoadText[255];
			float m_TimeAcc;
			int m_iRunningCnt;

			bool isLoadCompleate;
			bool isStateChanged;
			bool isPhaseChage;
			float m_fPercentage;
		private:
			
			void ChangeLoadString(const shared_ptr<CTimer> _timer);
			void ChangeLoadString();

		
		public:
			static shared_ptr<CObject> Create(const shared_ptr<DxDevice> _device);
		private:

		};


	}
}

#endif // Object_LoadString_h__
