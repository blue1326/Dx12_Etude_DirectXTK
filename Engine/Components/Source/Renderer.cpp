#include "stdafx.h"
#include "Renderer.h"

Engine::Components::CRenderer::CRenderer(const shared_ptr<DxDevice> _device)
	:m_DxDevice(_device)
{

}

Engine::Components::CRenderer::~CRenderer()
{

}

HRESULT Engine::Components::CRenderer::Init_Component()
{
	return S_OK;
}

HRESULT Engine::Components::CRenderer::Prepare_Component()
{
	return S_OK;
}

void Engine::Components::CRenderer::Update_Component(const shared_ptr<CTimer> _timer)
{

}

void Engine::Components::CRenderer::Render()
{
	int i = 0;
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CRenderer::Clone()
{
	return this->shared_from_this();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CRenderer::Create(const shared_ptr<DxDevice> _device)
{
	return shared_ptr<CComponent>(new CRenderer(_device));
}
