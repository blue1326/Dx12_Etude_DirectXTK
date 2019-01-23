#include "stdafx.h"
#include "Core_Game.h"

Engine::System::AppCore_Game::AppCore_Game() noexcept(false)
{
	m_Device = DxDevice::CreateDevice();
	m_Device->RegisterDeviceNotify(this);
}

Engine::System::AppCore_Game::~AppCore_Game()
{
	if (m_Device)
	{
		m_Device->WaitForGpu();
	}
}

shared_ptr<Engine::System::AppCore_Game> Engine::System::AppCore_Game::Create(HWND window, int width, int height)
{
	shared_ptr<AppCore_Game> inst = shared_ptr<Engine::System::AppCore_Game>(new AppCore_Game);
	inst->Initialize(window, width, height);
	return inst;
}

void Engine::System::AppCore_Game::Initialize(HWND window, int width, int height)
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


}

void Engine::System::AppCore_Game::Tick()
{
	m_MainTimer->Tick();
}

void Engine::System::AppCore_Game::OnDeviceLost()
{

}

void Engine::System::AppCore_Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

void Engine::System::AppCore_Game::OnActivated()
{

}

void Engine::System::AppCore_Game::OnDeactivated()
{

}

void Engine::System::AppCore_Game::OnSuspending()
{

}

void Engine::System::AppCore_Game::OnResuming()
{
	m_MainTimer->Start();
	//m_gamePadButtons.Reset();
	//m_keyboardButtons.Reset();
	//m_audEngine->Resume();
}

void Engine::System::AppCore_Game::OnWindowMoved()
{
	auto size = m_Device->GetOutputSize();
	m_Device->WindowSizeChanged(size.right, size.bottom);
}

void Engine::System::AppCore_Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_Device->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();
}

void Engine::System::AppCore_Game::NewAudioDevice()
{

}

void Engine::System::AppCore_Game::GetDefaultSize(int& width, int& height) const
{
	width = 800;
	height = 600;
}

void Engine::System::AppCore_Game::Update()
{
	PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");
	PIXEndEvent();
}

void Engine::System::AppCore_Game::LateUpdate()
{
	PIXBeginEvent(PIX_COLOR_DEFAULT, L"LateUpdate");
	PIXEndEvent();
}

void Engine::System::AppCore_Game::Render()
{
	m_Device->Prepare();
	Clear();
	auto cmdlist = m_Device->GetCommandList();
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Render");
	
	PIXEndEvent(cmdlist);



	PIXBeginEvent(m_Device->GetCommandQueue(), PIX_COLOR_DEFAULT, L"Present");
	m_Device->Present();
	m_graphicsMemory->Commit(m_Device->GetCommandQueue());
	PIXEndEvent(m_Device->GetCommandQueue());
}

void Engine::System::AppCore_Game::Clear()
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

void Engine::System::AppCore_Game::CreateDeviceDependentResources()
{
	auto device = m_Device->GetD3DDevice();
	m_graphicsMemory = make_unique<DirectX::GraphicsMemory>(device);
}

void Engine::System::AppCore_Game::CreateWindowSizeDependentResources()
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
