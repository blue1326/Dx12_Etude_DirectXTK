#include "stdafx.h"
#include "Object_LoadString.h"
#include "ComponentHolder.h"
//components
#include "Font.h"
#include "Renderer.h"

Engine::Architecture::CObject_LoadString::CObject_LoadString(const shared_ptr<DxDevice> _device)
	:CUIObject(_device)
{

}

Engine::Architecture::CObject_LoadString::~CObject_LoadString()
{

}

HRESULT Engine::Architecture::CObject_LoadString::Init_Object()
{
	m_Components[L"Font"] = CComponentHolder::GetInstance()->Clone_Component(L"BasicFont");
	if (m_Components[L"Font"] == nullptr)return E_FAIL;
	m_Components[L"Renderer"] = CComponentHolder::GetInstance()->Clone_Component(L"Renderer");
	if (m_Components[L"Renderer"] == nullptr)return E_FAIL;

	if (FAILED(Prepare_Object()))
		return E_FAIL;

	return S_OK;
}

void Engine::Architecture::CObject_LoadString::Update_Object(const shared_ptr<CTimer> _timer)
{

}

void Engine::Architecture::CObject_LoadString::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{

}

void Engine::Architecture::CObject_LoadString::Render_Object(ID3D12GraphicsCommandList* cmdlist)
{

}

void Engine::Architecture::CObject_LoadString::PushText(const wchar_t* _text)
{

}

const wchar_t* Engine::Architecture::CObject_LoadString::GetLastText()
{
	return nullptr;
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CObject_LoadString::Create(const shared_ptr<DxDevice> _device)
{
	shared_ptr<CObject> inst = shared_ptr<CObject>(new CObject_LoadString(_device));
	return inst;
}
