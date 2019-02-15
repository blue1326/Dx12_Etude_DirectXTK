#include "stdafx.h"
#include "Phase.h"
#include "Functor.h"
Engine::Architecture::CPhase::CPhase(const shared_ptr<DxDevice> _device)
	:m_DxDevice(_device)
{

}

Engine::Architecture::CPhase::~CPhase()
{

}

void Engine::Architecture::CPhase::Update_Phase(const shared_ptr<CTimer> _timer)
{
	for (const auto &j : m_Objects)
	{
		j.second->Update_Object(_timer);
	}
}

void Engine::Architecture::CPhase::LateUpdate_Phase(const shared_ptr<CTimer> _timer)
{
	for (const auto &j : m_Objects)
	{
		j.second->LateUpdate_Object(_timer);
	}
}

HRESULT Engine::Architecture::CPhase::AddObject(const wchar_t* _Objtag, shared_ptr<CObject> _Object)
{
	shared_ptr<CObject> FoundedObject = Find_Object(_Objtag);
	if (nullptr != FoundedObject)
		return E_FAIL;

	m_Objects[_Objtag] = _Object;
	return S_OK;
}

HRESULT Engine::Architecture::CPhase::InitObjects()
{
	for (const auto &j : m_Objects)
	{
		if (FAILED(j.second->Init_Object()))
			return E_FAIL;
	}
	return S_OK;
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CPhase::Find_Object(const wchar_t* _Objtag)
{
	MAPOBJECTS::iterator finder = find_if(m_Objects.begin(), m_Objects.end(), Engine::CTag_Finder(_Objtag));
	if (finder == m_Objects.end())
		return nullptr;
	return finder->second;
}

