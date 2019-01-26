#include "stdafx.h"
#include "Core_Game.h"
#include "ComponentHolder.h"

#include "Export_Components.h"
//#include "Renderer.h"
//using namespace Engine::System;
//using namespace Engine::Components;
Engine::Architecture::AppCore_Game::AppCore_Game() noexcept(false)
{
	m_Device = DxDevice::CreateDevice();
	m_Device->RegisterDeviceNotify(this);
}

Engine::Architecture::AppCore_Game::~AppCore_Game()
{
	CComponentHolder::GetInstance()->Destroy();
	if (m_Device)
	{
		m_Device->WaitForGpu();
	}
}

shared_ptr<Engine::Architecture::AppCore_Game> Engine::Architecture::AppCore_Game::Create(HWND window, int width, int height)
{
	shared_ptr<AppCore_Game> inst = shared_ptr<Engine::Architecture::AppCore_Game>(new AppCore_Game);
	inst->Initialize(window, width, height);
	return inst;
}

void Engine::Architecture::AppCore_Game::Initialize(HWND window, int width, int height)
{
	m_MainTimer = CTimer::CreateTimer();
	//m_Gamepad = make_shared<DirectX::GamePad>();
	m_Keyboard = make_shared<DirectX::Keyboard>();
	m_Mouse = make_shared<DirectX::Mouse>();

	m_Mouse->SetWindow(window);

	m_Device->SetWindow(window, width, height);

	m_Device->CreateDeviceResources();
	CreateDeviceDependentResources();
	m_Device->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	CreateArchitecture();

}

void Engine::Architecture::AppCore_Game::Tick()
{
	m_MainTimer->Tick();
}

void Engine::Architecture::AppCore_Game::OnDeviceLost()
{

}

void Engine::Architecture::AppCore_Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

void Engine::Architecture::AppCore_Game::OnActivated()
{

}

void Engine::Architecture::AppCore_Game::OnDeactivated()
{

}

void Engine::Architecture::AppCore_Game::OnSuspending()
{

}

void Engine::Architecture::AppCore_Game::OnResuming()
{
	m_MainTimer->Start();
	//m_gamePadButtons.Reset();
	//m_keyboardButtons.Reset();
	//m_audEngine->Resume();
}

void Engine::Architecture::AppCore_Game::OnWindowMoved()
{
	auto size = m_Device->GetOutputSize();
	m_Device->WindowSizeChanged(size.right, size.bottom);
}

void Engine::Architecture::AppCore_Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_Device->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();
}

void Engine::Architecture::AppCore_Game::NewAudioDevice()
{

}

void Engine::Architecture::AppCore_Game::GetDefaultSize(int& width, int& height) const
{
	width = 800;
	height = 600;
}

void Engine::Architecture::AppCore_Game::Update()
{
	PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");
	PIXEndEvent();
}

void Engine::Architecture::AppCore_Game::LateUpdate()
{
	PIXBeginEvent(PIX_COLOR_DEFAULT, L"LateUpdate");
	PIXEndEvent();
}

void Engine::Architecture::AppCore_Game::Render()
{
	m_Device->Prepare();
	Clear();
	auto cmdlist = m_Device->GetCommandList();
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Render");
	
	dynamic_cast<CRenderer*>(m_Renderer.get())->Render();
	
	PIXEndEvent(cmdlist);



	PIXBeginEvent(m_Device->GetCommandQueue(), PIX_COLOR_DEFAULT, L"Present");
	m_Device->Present();
	m_graphicsMemory->Commit(m_Device->GetCommandQueue());
	PIXEndEvent(m_Device->GetCommandQueue());
}

void Engine::Architecture::AppCore_Game::Clear()
{
	
	auto commandList = m_Device->GetCommandList();
	//visual studio check..
	PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Clear");

	// Clear the views.
	auto rtvDescriptor = m_Device->GetRenderTargetView();
	auto dsvDescriptor = m_Device->GetDepthStencilView();

	commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);
	commandList->ClearRenderTargetView(rtvDescriptor, DirectX::Colors::CornflowerBlue, 0, nullptr);
	commandList->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// Set the viewport and scissor rect.
	auto viewport = m_Device->GetScreenViewport();
	auto scissorRect = m_Device->GetScissorRect();
	commandList->RSSetViewports(1, &viewport);
	commandList->RSSetScissorRects(1, &scissorRect);

	PIXEndEvent(commandList);
}

void Engine::Architecture::AppCore_Game::CreateDeviceDependentResources()
{
	auto device = m_Device->GetD3DDevice();
	m_graphicsMemory = make_unique<DirectX::GraphicsMemory>(device);
}

void Engine::Architecture::AppCore_Game::CreateWindowSizeDependentResources()
{
	auto size = m_Device->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);
	float fovAngleY = 70.0f * DirectX::XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView
	(fovAngleY,
		aspectRatio,
		0.01f,
		100.0f);
	//m_Device->GetScreenViewport();

}

void Engine::Architecture::AppCore_Game::CreateArchitecture()
{
	shared_ptr<CComponent> inst = CRenderer::Create(m_Device);
	m_Renderer = inst;
	CComponentHolder::GetInstance()->AddOriginComponent("Renderer", inst);
	
}
