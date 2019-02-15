#ifndef Engine_Object_h__
#define Engine_Object_h__
#include "Export_System.h"

using namespace Engine::System;
namespace Engine
{
		class  CObject :public std::enable_shared_from_this<CObject>
		{
		public:
			_declspec(dllexport)explicit CObject(const shared_ptr<DxDevice> _device);
			_declspec(dllexport)explicit CObject(const CObject& rhs) = delete;
			_declspec(dllexport)virtual ~CObject();


			
		public:
			_declspec(dllexport)virtual HRESULT Init_Object()=0;
			_declspec(dllexport)virtual void Update_Object(const shared_ptr<CTimer> _timer) = 0;
			_declspec(dllexport)virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer) = 0;
			_declspec(dllexport)virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist) =0 ;
			
		protected:
			//_declspec(dllexport) virtual shared_ptr<CObject> Share() = 0;

		protected:
			const shared_ptr<DxDevice> m_DxDevice;

		};

}

#endif // Object_h__
