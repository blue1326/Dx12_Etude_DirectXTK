#include "stdafx.h"
#include "Core_Game.h"
#include "ComponentHolder.h"

#include "Export_Components.h"
#include "Font.h"
#include "Sprite.h"

#include "DebugObject.h"

#include "Phase_Load.h"
#include "Phase_Stage.h"
//#include "Renderer.h"
//using namespace Engine::System;
using namespace Engine::Components;
using namespace DirectX;
Engine::Architecture::AppCore_Game::AppCore_Game() noexcept(false)
	:m_fTimeAcc(0.f)
	,frameCnt(0)
	,frameCntLimit(0)
	,timeElapsed(0)
	,m_ActivePhase(nullptr)
{
	m_Device = DxDevice::CreateDevice();
	m_Device->RegisterDeviceNotify(this);
}

Engine::Architecture::AppCore_Game::~AppCore_Game()
{

	//static_cast<CControl*>(m_Control.get())->Reset();
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
	m_MainTimer->Reset();


	//m_Gamepad = make_unique<DirectX::GamePad>();
	
	m_Keyboard = make_unique<DirectX::Keyboard>();
	m_Mouse = make_unique<DirectX::Mouse>();
	

	m_Mouse->SetWindow(window);
	

	

	m_Device->SetWindow(window, width, height);

	m_Device->CreateDeviceResources();
	CreateDeviceDependentResources();
	m_Device->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	LoadPreLoadComponents();

	m_DebugObjects[L"Main"] = CDebugObject::Create(m_Device);
	m_DebugObjects[L"Main"]->Init_Object();
	//static_cast<CDebugObject*>(m_DebugObjects[L"Main"].get())->SetFPSDbgMessage(L"FPS");
	m_Phase[L"Load"] = CPhase_Load::Create(m_Device);
	m_Phase[L"Load"]->isLive = true;
	m_Phase[L"Load"]->Prepare_Phase();

	m_Phase[L"Stage"] = CPhase_Stage::Create(m_Device);
	m_Phase[L"Load"]->SetNextPhase(m_Phase[L"Stage"]);
	
}

void Engine::Architecture::AppCore_Game::ResizeWindow(HWND window, int width, int height)
{
	m_Device->SetWindow(window, width, height);
}

LRESULT Engine::Architecture::AppCore_Game::AdditionalMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATEAPP:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		Mouse::ProcessMessage(msg, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		break;
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(msg, wParam, lParam);
		break;
	}

	return 0;
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
	//
	auto control = static_cast<CControl*>(m_Control.get());
	auto keystate = m_Keyboard->GetState();
	

	auto mousestate = m_Mouse->GetState();
	
	

	
	control->UpdateTracker(keystate);
	

	control->UpdateTracker(mousestate);
	if (control->GetMouseTracker().leftButton == GamePad::ButtonStateTracker::HELD)
	{
		m_Mouse->SetMode(Mouse::MODE_RELATIVE);
	}
	else
		m_Mouse->SetMode(Mouse::MODE_ABSOLUTE);
		

	wstring mousepos = L"MousePos X : "+ to_wstring(mousestate.x) + L" Y : " + to_wstring(mousestate.y);
	
	
	//
	static_cast<CDebugObject*>(m_DebugObjects[L"Main"].get())->SetMouseDbgMessage(mousepos.c_str());

	//m_Phase[L"Load"]->Update_Phase(m_MainTimer);
	if (m_ActivePhase == nullptr)
	{
		SetUp_ActivePhase();
	}
	else
	{
		if (m_ActivePhase->isLive)
		{
			m_ActivePhase->Update_Phase(m_MainTimer);
		}
		else
		{
			SetUp_ActivePhase();
		}
	}
	
	//
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
	
	
	dynamic_cast<CRenderer*>(m_Renderer.get())->Render(cmdlist);
	for (const auto &j : m_DebugObjects)
	{
		j.second->Render_Object(cmdlist);
	}
	//m_Phase[L"Load"]->Render_Phase(cmdlist);


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
	auto holder = CComponentHolder::GetInstance();
	shared_ptr<CComponent> inst = CRenderer::Create(m_Device);
	m_Renderer = inst;
	inst->Init_Component();
	holder->AddOriginComponent(L"Renderer", inst);
	
	//클라이언트 기준 상대경로
	inst.reset();
	inst = CFont::Create(m_Device, L"../../Font/Basic10.spritefont");
	inst->Init_Component();
	holder->AddOriginComponent(L"BasicFont", inst);

	inst.reset();
	inst = CSprite::Create(m_Device, L"../../Textures/test.jpg");
	inst->Init_Component();
	holder->AddOriginComponent(L"Sprite_Logo", inst);

	inst.reset();
	inst = CControl::Create();
	m_Control = inst;
	inst->Init_Component();
	holder->AddOriginComponent(L"Control", inst);

}

bool Engine::Architecture::AppCore_Game::CalculateFrameStats()
{
	bool isLimit = false;

	frameCnt++;
	m_fTimeAcc += m_MainTimer->DeltaTime();
	if (m_fTimeAcc > m_CallPerSec)
	{
		frameCntLimit++;
		m_fTimeAcc = 0.f;
		isLimit = true;
	}

	
	if ((m_MainTimer->TotalTime() - timeElapsed) >= 1.0f)
	{
		int fps = frameCnt;
		int limitedfps = frameCntLimit;
		float mspf = 1000.0f / fps;
	
		std::wstring limitfpsStr = std::to_wstring(limitedfps);
		std::wstring fpsStr = std::to_wstring(fps);
		std::wstring mspfStr = std::to_wstring(mspf);

		std::wstring dbgText = 
			L" Limited Fps: " + limitfpsStr +
			L"  Fps: " + fpsStr +
			L"  mspf: " + mspfStr;
		static_cast<CDebugObject*>(m_DebugObjects[L"Main"].get())->SetFPSDbgMessage(dbgText.c_str());
		// Reset for next average.
		frameCnt = 0;
		frameCntLimit = 0;
		timeElapsed += 1.0f;
	}

	return isLimit;

}

void Engine::Architecture::AppCore_Game::SetFramelateLimit(const float& _Limit)
{
	m_CallPerSec = 1.f / _Limit;
}

bool Engine::Architecture::AppCore_Game::Check_OneLivePhase()
{
	///not yet
	return true;
}

void Engine::Architecture::AppCore_Game::SetUp_ActivePhase()
{
	for (const auto &j : m_Phase)
	{
		if (j.second->isLive)
		{
			m_ActivePhase = j.second;
			break;
		}
	}
}
