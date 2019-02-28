#include "stdafx.h"
#include "Component_OnDevice.h"

Engine::Components::CComponent_Device::CComponent_Device(const shared_ptr<DxDevice> _device)
	:m_DxDevice(_device)
{

}

Engine::Components::CComponent_Device::~CComponent_Device()
{
	m_DxDevice.reset();
}

Engine::Components::CComponent_Device::CComponent_Device(const CComponent_Device& rhs)
{

}
