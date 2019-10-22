#ifndef Engine_Phase_h__
#define Engine_Phase_h__

#include "DxDevice.h"
#include "Timer.h"
#include "Object.h"
#include "CThreadHolder.h"
using namespace ThreadPool;
using namespace Engine::System;
namespace Engine
{
	namespace Architecture
	{
		class CPhase
		{
		public:
			explicit CPhase(const shared_ptr<DxDevice> _device);
			virtual ~CPhase();
		public:
			virtual HRESULT Prepare_Phase()=0;
			virtual void Update_Phase(const shared_ptr<CTimer> _timer);
			virtual void LateUpdate_Phase(const shared_ptr<CTimer> _timer);
			virtual void Render_Phase(ID3D12GraphicsCommandList* cmdlist)=0;

		protected:
			HRESULT AddObject(const unsigned int _LayerIdx, const wchar_t* _Objtag, shared_ptr<CObject> _Object);
			HRESULT InitObjects();
		private:
			//shared_ptr<CObject> Find_Object(const wchar_t* _Objtag);
			shared_ptr<CObject> Find_Object(const unsigned int _LayerIdx, const wchar_t* _Objtag);
		protected:
			shared_ptr<DxDevice> m_DxDevice;
		protected:
			typedef map<const wchar_t*, shared_ptr<CObject>> MAPOBJECTS;
			//MAPOBJECTS m_Objects;
			vector<shared_ptr<MAPOBJECTS>> vecLayer;
			void ReserveLayer(const unsigned int _size);
		private:
			bool isReserved;
		public:
			bool isLive;
		protected:
			shared_ptr<CPhase> m_NextPhase;
			HRESULT Prepare_NextPhase();
		public:
			void SetNextPhase(const shared_ptr<CPhase> _nextphase);
		private:
			shared_ptr<CThreadHolder> m_ThreadPool;
		};

		
	}
}

#endif // Phase_h__
