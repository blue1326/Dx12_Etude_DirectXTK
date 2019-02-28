#include "stdafx.h"
#include "Phase.h"
#include "Functor.h"
Engine::Architecture::CPhase::CPhase(const shared_ptr<DxDevice> _device)
	:m_DxDevice(_device)
	, isReserved(false)
	, isLive(false)
	,m_NextPhase(nullptr)
{

}

Engine::Architecture::CPhase::~CPhase()
{
	
}

void Engine::Architecture::CPhase::Update_Phase(const shared_ptr<CTimer> _timer)
{
	for (const auto &i : vecLayer)
	{
		for (const auto &j : *i.get())
		{
			j.second->Update_Object(_timer);
		}
	}
}

void Engine::Architecture::CPhase::LateUpdate_Phase(const shared_ptr<CTimer> _timer)
{
	for (const auto &i : vecLayer)
	{
		for (const auto &j : *i.get())
		{
			j.second->LateUpdate_Object(_timer);
		}
	}

}

HRESULT Engine::Architecture::CPhase::AddObject(const unsigned int _LayerIdx, const wchar_t* _Objtag, shared_ptr<CObject> _Object)
{
	if (isReserved)
	{
		if (vecLayer.size() <= _LayerIdx)
		{
			vecLayer.resize(_LayerIdx+1);
			/*		for (int i = vecLayer.size(); i < _LayerIdx + 1; i++)
					{
						vecLayer.push_back(make_shared<MAPOBJECTS>());
					}*/
			for (auto &j : vecLayer)
			{
				if (j == nullptr)j = make_shared<MAPOBJECTS>();
			}
		}
	}
	else
	{
		ReserveLayer(_LayerIdx + 1);
	}
	shared_ptr<CObject> FoundedObject = Find_Object(_LayerIdx, _Objtag);
	if (nullptr != FoundedObject)
		return E_FAIL;

	(*(vecLayer[_LayerIdx].get()))[_Objtag] = _Object;

	return S_OK;
}

HRESULT Engine::Architecture::CPhase::InitObjects()
{
	for (const auto &i : vecLayer)
	{
		for (const auto &j : *i.get())
		{
			if (FAILED(j.second->Init_Object()))
				return E_FAIL;
		}
	}
	
	return S_OK;
}



std::shared_ptr<Engine::CObject> Engine::Architecture::CPhase::Find_Object(const unsigned int _LayerIdx, const wchar_t* _Objtag)
{
	MAPOBJECTS::iterator finder = find_if(vecLayer[_LayerIdx]->begin(), vecLayer[_LayerIdx]->end(), Engine::CTag_Finder(_Objtag));
	if (finder == vecLayer[_LayerIdx]->end())
		return nullptr;
	return finder->second;
}

void Engine::Architecture::CPhase::ReserveLayer(const unsigned int _size)
{
	vecLayer.reserve(_size);
	
	for(unsigned int i =0;i<_size;i++)
	{
		vecLayer.push_back(make_shared<MAPOBJECTS>());
	}
	isReserved = true;
}

HRESULT Engine::Architecture::CPhase::Prepare_NextPhase()
{
	HRESULT res = S_OK;
	if (m_NextPhase != nullptr)
	{
		res = m_NextPhase->Prepare_NextPhase();
	}
	return res;
}

void Engine::Architecture::CPhase::SetNextPhase(const shared_ptr<CPhase> _nextphase)
{
	m_NextPhase = _nextphase;
}

