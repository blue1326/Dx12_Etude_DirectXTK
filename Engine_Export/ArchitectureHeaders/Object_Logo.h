#ifndef Object_Logo_h__
#define Object_Logo_h__
#include "Object.h"
namespace Engine
{
	namespace Architecture
	{
		class CObject_Logo : public CObject
		{
			explicit CObject_Logo(const shared_ptr<DxDevice> _device);
			explicit CObject_Logo(const CObject& rhs) = delete;
			virtual ~CObject_Logo();



		public:
			virtual HRESULT Init_Object()override;
			virtual void Update_Object(const shared_ptr<CTimer> _timer)override;
			virtual void LateUpdate_Object(const shared_ptr<CTimer> _timer)override;
			virtual void Render_Object(ID3D12GraphicsCommandList* cmdlist)override;


		public:
			static shared_ptr<CObject> Create();
		};
	}
}

#endif // Object_Logo_h__
