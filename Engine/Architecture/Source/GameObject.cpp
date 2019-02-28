#include "stdafx.h"
#include "GameObject.h"

Engine::Architecture::CGameObject::CGameObject(const shared_ptr<DxDevice> _device)
	:CObject(_device)
{

}

Engine::Architecture::CGameObject::~CGameObject()
{
	Free();
}


void Engine::Architecture::CGameObject::Update_Object(const shared_ptr<CTimer> _timer)
{
	for (const auto &j : m_Components)
	{
		j.second->Update_Component(_timer);
	}
}

void Engine::Architecture::CGameObject::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{
	for (const auto &j : m_Components)
	{
		j.second->LateUpdate_Component(_timer);
	}
}


HRESULT Engine::Architecture::CGameObject::Prepare_Object()
{
	for (const auto &j : m_Components)
	{
		if (FAILED(j.second->Prepare_Component()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT Engine::Architecture::CGameObject::AddComponent(const wchar_t* _tag, shared_ptr<CComponent> _component)
{
	if (Find_Component(_tag) == nullptr)
		m_Components[_tag] = _component;
	else
		return E_FAIL;

	return S_OK;
}

HRESULT Engine::Architecture::CGameObject::CheckComponentNullptr()
{
	for (const auto &j : m_Components)
	{
		if (j.second == nullptr)
			return E_FAIL;
	}

	return S_OK;
}

void Engine::Architecture::CGameObject::Free()
{
	m_Components.clear();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Architecture::CGameObject::Find_Component(const wchar_t* _ComponentName)
{
	MAPCOMPONENT::iterator iter = m_Components.find(_ComponentName);
	if (iter == m_Components.end())
		return nullptr;
	else
		return iter->second;
}
