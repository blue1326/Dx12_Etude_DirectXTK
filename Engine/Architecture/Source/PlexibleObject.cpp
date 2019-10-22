
#include "stdafx.h"
#include "PlexibleObject.h"

Engine::Architecture::CPlexibleObject::CPlexibleObject(const shared_ptr<DxDevice> _device)
	:CGameObject(_device)
{
	ResetFunctions();
}

Engine::Architecture::CPlexibleObject::~CPlexibleObject()
{
	ResetFunctions();
}

HRESULT Engine::Architecture::CPlexibleObject::Init_Object()
{
	if (m_init != nullptr)
		return m_init(m_Components);
	return S_OK;
}

void Engine::Architecture::CPlexibleObject::Update_Object(const shared_ptr<CTimer> _timer)
{
	CGameObject::Update_Object(_timer);
	if (m_update[UP_BASIC] != nullptr)
		m_update[UP_BASIC](_timer, m_Components);
	
}

void Engine::Architecture::CPlexibleObject::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{
	CGameObject::LateUpdate_Object(_timer);
	if (m_update[UP_LATE] != nullptr)
		m_update[UP_LATE](_timer, m_Components);
}

void Engine::Architecture::CPlexibleObject::Render_Object(ID3D12GraphicsCommandList* cmdlist)
{
	if (m_render != nullptr)
		m_render(cmdlist, m_Components);
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CPlexibleObject::Create(const shared_ptr<DxDevice> _device)
{
	shared_ptr<CObject> inst = shared_ptr<CObject>(new CPlexibleObject(_device));
	return inst;
}

void Engine::Architecture::CPlexibleObject::SetFunction(HRESULT(*_init)(MAPCOMPONENT))
{
	m_init = _init;
}

void Engine::Architecture::CPlexibleObject::SetFunction(void(*_render)(ID3D12GraphicsCommandList*, MAPCOMPONENT))
{
	m_render = _render;
}

void Engine::Architecture::CPlexibleObject::SetFunction(void(*_update)(const shared_ptr<CTimer>, MAPCOMPONENT), UPDATESIGN _sign)
{
	m_update[_sign] = _update;
}

void Engine::Architecture::CPlexibleObject::ResetFunctions()
{
	m_init = nullptr;
	for (int i = 0; i < UP_END; i++)
		m_update[i] = nullptr;
	m_render = nullptr;
}
