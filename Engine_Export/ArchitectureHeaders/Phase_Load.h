#ifndef Engine_Phase_Load_h__
#define Engine_Phase_Load_h__

#include "DxDevice.h"
#include "Phase.h"
#include "ResourceLoader.h"


using namespace std;
using namespace Engine::System;

namespace Engine
{
	namespace Architecture
	{
		class CPhase_Load : public CPhase
		{
		public:
			explicit CPhase_Load(const shared_ptr<DxDevice> _device);
			virtual ~CPhase_Load();
		public:
			virtual HRESULT Prepare_Phase();
			virtual void Update_Phase(const shared_ptr<CTimer> _timer);
			virtual void LateUpdate_Phase(const shared_ptr<CTimer> _timer);
			virtual void Render_Phase(ID3D12GraphicsCommandList* cmdlist);
		private:
			unique_ptr<CResourceLoader> m_Loader;

		public:
			static shared_ptr<CPhase> Create(const shared_ptr<DxDevice> _device);
		};
	}
}

#endif // Phase_Load_h__