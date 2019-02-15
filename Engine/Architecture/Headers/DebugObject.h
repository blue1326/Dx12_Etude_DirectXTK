#ifndef Engine_DebugObject_h__
#define Engine_DebugObject_h__
#include "Object.h"
#include "Component.h"
using namespace Engine::Components;
namespace Engine
{
	namespace Architecture
	{
		class CDebugObject : public CObject
		{
		public:
			explicit CDebugObject(const shared_ptr<DxDevice> _device);
			explicit CDebugObject(const CDebugObject& rhs) = delete;
			virtual ~CDebugObject();

		public:
			virtual HRESULT Init_Object();
			virtual void Update_Object(const shared_ptr<CTimer> _timer);
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer);
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist);


		public:
			void SetDbgMessage(const wchar_t* _msg);
		public:
			_declspec(dllexport) static shared_ptr<CObject> Create(const shared_ptr<DxDevice> _device);
		private:
			typedef map<const wchar_t*,shared_ptr<CComponent>> MAPCOMPONENTS;
			MAPCOMPONENTS m_Components;

		private:
			wchar_t DbgMessage[255];
		};

		
	}
}

#endif // DebugObject_h__
