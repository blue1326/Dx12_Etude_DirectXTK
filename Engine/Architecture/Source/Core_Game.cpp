#include "stdafx.h"
#include "Core_Game.h"
#include "ComponentHolder.h"

#include "Export_Components.h"
#include "Font.h"
#include "DebugObject.h"
#include "Texture.h"
#include "Phase_Load.h"
//#include "Renderer.h"
//using namespace Engine::System;
//using namespace Engine::Components;
using namespace DirectX;
Engine::Architecture::AppCore_Game::AppCore_Game() noexcept(false)
	:m_fTimeAcc(0.f)
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

	LoadPreLoadComponents();

	m_DebugObjects[L"FPS"] = CDebugObject::Create(m_Device);
	m_DebugObjects[L"FPS"]->Init_Object();
	static_cast<CDebugObject*>(m_DebugObjects[L"FPS"].get())->SetDbgMessage(L"FPS");
	m_Phase[L"Load"] = CPhase_Load::Create(m_Device);
	m_Phase[L"Load"]->Prepare_Phase();
	
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
	m_Phase[L"Load"]->Update_Phase(m_MainTimer);
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
	
	for (const auto &j : m_DebugObjects)
	{
		j.second->Render_Object(cmdlist);
	}
	dynamic_cast<CRenderer*>(m_Renderer.get())->Render(cmdlist);
	
	m_Phase[L"Load"]->Render_Phase(cmdlist);


	/*CFont* font = dynamic_cast<CFont*>(CComponentHolder::GetInstance()->Get_Component("BasicFont").get());
	ID3D12DescriptorHeap* heaps[] = { font->GetHeap()->Heap() };
	cmdlist->SetDescriptorHeaps(_countof(heaps), heaps);
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Draw Sprite Font");

	font->GetBatch()->Begin(cmdlist);
	font->GetFont()->DrawString(font->GetBatch(), L"sample", XMFLOAT2(100, 10), Colors::Yellow);

	font->GetFont()->DrawString(font->GetBatch(), L"sample2", XMFLOAT2(100, 20), Colors::Yellow);
	font->GetBatch()->End();

	PIXEndEvent(cmdlist);*/


	//dynamic_cast<CFont*>(CComponentHolder::GetInstance()->Get_Component("BasicFont").get())->Render();
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

void Engine::Architecture::AppCore_Game::LoadPreLoadComponents()
{
	shared_ptr<CComponent> inst = CRenderer::Create(m_Device);
	m_Renderer = inst;
	CComponentHolder::GetInstance()->AddOriginComponent(L"Renderer", inst);
	//클라이언트 기준 상대경로
	inst = CFont::Create(m_Device, L"../../Font/Basic10.spritefont");
	inst->Init_Component();
	CComponentHolder::GetInstance()->AddOriginComponent(L"BasicFont", inst);

	inst.reset();
	inst = CTexture::Create(m_Device, L"../../Textures/windowslogo.dds");
	inst->Init_Component();
}

bool Engine::Architecture::AppCore_Game::CalculateFrameStats()
{
	bool isLimit = false;
	static int frameCnt = 0;
	static int FrameCntLimit = 0;
	static float timeElapsed = 0.0f;
	frameCnt++;
	m_fTimeAcc += m_MainTimer->DeltaTime();
	if (m_fTimeAcc > m_CallPerSec)
	{
		FrameCntLimit++;
		m_fTimeAcc = 0.f;
		isLimit = true;
	}


	if ((m_MainTimer->TotalTime() - timeElapsed) >= 1.0f)
	{
		int fps = frameCnt;
		int limitedfps = FrameCntLimit;
		float mspf = 1000.0f / fps;

		std::wstring limitfpsStr = std::to_wstring(limitedfps);
		std::wstring fpsStr = std::to_wstring(fps);
		std::wstring mspfStr = std::to_wstring(mspf);

		std::wstring dbgText = 
			L" Limited Fps: " + limitfpsStr +
			L"  Fps: " + fpsStr +
			L"  mspf: " + mspfStr;
		static_cast<CDebugObject*>(m_DebugObjects[L"FPS"].get())->SetDbgMessage(dbgText.c_str());
		// Reset for next average.
		frameCnt = 0;
		FrameCntLimit = 0;
		timeElapsed += 1.0f;
	}

	return isLimit;

}

void Engine::Architecture::AppCore_Game::SetFramelateLimit(const float& _Limit)
{
	m_CallPerSec = 1.f / _Limit;
}
