#include "stdafx.h"
#include "Control.h"


Engine::Components::CControl::CControl()
{

}

Engine::Components::CControl::~CControl()
{
	m_PadTracker.Reset();
	m_KeybordTracker.Reset();
	m_MouseTracker.Reset();
}

HRESULT Engine::Components::CControl::Init_Component()
{
	m_PadTracker.Reset();
	m_KeybordTracker.Reset();
	m_MouseTracker.Reset();
	return S_OK;
}

HRESULT Engine::Components::CControl::Prepare_Component()
{
	return S_OK;
}

void Engine::Components::CControl::Update_Component(const shared_ptr<CTimer> _timer)
{

}

void Engine::Components::CControl::LateUpdate_Component(const shared_ptr<CTimer> _timer)
{

}
//
//void Engine::Components::CControl::UpdateTracker(const GamePad::State& _pad,const Keyboard::State& _keyboard,const Mouse::State& _mouse)
//{
//	if (_pad.IsConnected())
//	{
//		m_PadTracker.Update(_pad);
//	}
//	m_KeybordTracker.Update(_keyboard);
//	m_MouseTracker.Update(_mouse);
//}

void Engine::Components::CControl::UpdateTracker(const Mouse::State& _mouse)
{
	m_MouseTracker.Update(_mouse);
}

void Engine::Components::CControl::UpdateTracker(const Keyboard::State& _keyboard)
{
	m_KeybordTracker.Update(_keyboard);
}

void Engine::Components::CControl::UpdateTracker(const GamePad::State& _pad)
{
	if (_pad.IsConnected())
	{
		m_PadTracker.Update(_pad);
	}
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CControl::Clone()
{
	return shared_from_this();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CControl::Create()
{
	shared_ptr<CComponent> inst = shared_ptr<CComponent>(new CControl());
	return inst;
}

void Engine::Components::CControl::Reset()
{
	m_PadTracker.Reset();
	m_KeybordTracker.Reset();
	m_MouseTracker.Reset();
}
