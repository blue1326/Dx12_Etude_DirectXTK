#include "stdafx.h"
#include "UIObject.h"

Engine::Architecture::CUIObject::CUIObject(const shared_ptr<DxDevice> _device)
	:CObject(_device)
{

}

Engine::Architecture::CUIObject::~CUIObject()
{
	
	Free();
}

void Engine::Architecture::CUIObject::Update_Object(const shared_ptr<CTimer> _timer)
{
	for (const auto &j : m_Components)
	{
		j.second->Update_Component(_timer);
	}
}

void Engine::Architecture::CUIObject::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{
	for (const auto &j : m_Components)
	{
		j.second->LateUpdate_Component(_timer);
	}
}

HRESULT Engine::Architecture::CUIObject::Prepare_Object()
{
	for (const auto &j : m_Components)
	{
		if (FAILED(j.second->Prepare_Component()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT Engine::Architecture::CUIObject::AddComponent(const wchar_t* _tag, shared_ptr<CComponent> _component)
{
	if (Find_Component(_tag) == nullptr)
		m_Components[_tag] = _component;
	else
		return E_FAIL;

	return S_OK;
}

void Engine::Architecture::CUIObject::Free()
{
	m_Components.clear();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Architecture::CUIObject::Find_Component(const wchar_t* _ComponentName)
{
	MAPCOMPONENT::iterator iter = m_Components.find(_ComponentName);
	if (iter == m_Components.end())
		return nullptr;
	else
		return iter->second;
}
