#ifndef Engine_Object_h__
#define Engine_Object_h__
#include "Export_System.h"

using namespace Engine::System;
namespace Engine
{
	namespace Architecture
	{
		class CObject
		{
		public:
			explicit CObject(const shared_ptr<DxDevice> _device);
			explicit CObject(const CObject& rhs) = delete;
			virtual ~CObject();


			
		public:
			virtual HRESULT Init_Object()=0;
			virtual void Update_Object(const shared_ptr<CTimer> _timer) = 0;
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer) = 0;
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist) =0 ;

			
		protected:
			const shared_ptr<DxDevice> m_DxDevice;

		};

		
	}
}

#endif // Object_h__
