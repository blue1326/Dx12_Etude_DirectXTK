#ifndef Engine_Phase_Stage_h__
#define Engine_Phase_Stage_h__

#include "DxDevice.h"
#include "Phase.h"


using namespace std;
using namespace Engine::System;

namespace Engine
{
	namespace Architecture
	{
		class CPhase_Stage : public CPhase
		{
		public:
			explicit CPhase_Stage(const shared_ptr<DxDevice> _device);
			virtual ~CPhase_Stage();
		public:
			enum LAYER
			{
				LAYER_PLAYER,
				LAYER_END
			};
		public:
			virtual HRESULT Prepare_Phase();
			virtual void Update_Phase(const shared_ptr<CTimer> _timer);
			virtual void LateUpdate_Phase(const shared_ptr<CTimer> _timer);
			virtual void Render_Phase(ID3D12GraphicsCommandList* cmdlist);
		

		public:
			static shared_ptr<CPhase> Create(const shared_ptr<DxDevice> _device);
		};
	}
}

#endif // Phase_Stage_h__