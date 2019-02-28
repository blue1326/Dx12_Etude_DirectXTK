#include "stdafx.h"
#include "Object_LoadString.h"
#include "ComponentHolder.h"
//components
#include "Font.h"
#include "Renderer.h"
#include "Control.h"

using namespace DirectX;
Engine::Architecture::CObject_LoadString::CObject_LoadString(const shared_ptr<DxDevice> _device)
	:CUIObject(_device)
	,m_LoadText(L"")
	,m_TimeAcc(0)
	,m_iRunningCnt(0)
	,m_fPercentage(0)
	,isLoadCompleate(false)
	,isStateChanged(false)
	,isPhaseChage(false)
{

}

Engine::Architecture::CObject_LoadString::~CObject_LoadString()
{

}

HRESULT Engine::Architecture::CObject_LoadString::Init_Object()
{
	auto holder = CComponentHolder::GetInstance();
	m_Components[L"Font"] = holder->Clone_Component(L"BasicFont");
	if (m_Components[L"Font"] == nullptr)return E_FAIL;
	m_Components[L"Renderer"] = holder->Clone_Component(L"Renderer");
	if (m_Components[L"Renderer"] == nullptr)return E_FAIL;
	m_Components[L"Control"] = holder->Clone_Component(L"Control");
	if (m_Components[L"Control"] == nullptr) return E_FAIL;
	if(FAILED(CheckComponentNullptr()))
		return E_FAIL;

	if (FAILED(Prepare_Object()))
		return E_FAIL;

	return S_OK;
}

void Engine::Architecture::CObject_LoadString::Update_Object(const shared_ptr<CTimer> _timer)
{
	if (!isLoadCompleate)
	{
		ChangeLoadString(_timer);
	}
	else
	{
		if (!isStateChanged)
		{
			ChangeLoadString();
			isStateChanged = true;
		}
	}

	if (isStateChanged)
	{
		if (static_cast<CControl*>(m_Components[L"Control"].get())->GetKeyTracker().IsKeyPressed(Keyboard::Enter))
		{
			isPhaseChage = true;
		}
	}


	static_cast<CRenderer*>(m_Components[L"Renderer"].get())->Add_RenderList(CRenderer::RENDER_UI, shared_from_this());
	CUIObject::Update_Object(_timer);
}

void Engine::Architecture::CObject_LoadString::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{

}

void Engine::Architecture::CObject_LoadString::Render_Object(ID3D12GraphicsCommandList* cmdlist)
{
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Render_LoadingText");
	CFont* font = static_cast<CFont*>(m_Components[L"Font"].get());
	ID3D12DescriptorHeap* heaps[] = { font->GetHeap()->Heap() };
	cmdlist->SetDescriptorHeaps(_countof(heaps), heaps);
	font->GetBatch()->Begin(cmdlist);
	font->GetFont()->DrawString(font->GetBatch(), m_LoadText, XMFLOAT2(300, 550), DirectX::Colors::Black, DirectX::XMConvertToRadians(0));
	font->GetBatch()->End();
	PIXEndEvent(cmdlist);
}

void Engine::Architecture::CObject_LoadString::SetFlag(const bool _flag)
{
		isLoadCompleate = _flag;
}

void Engine::Architecture::CObject_LoadString::SetLoadingPercentage(const float _percentage)
{
	m_fPercentage = _percentage;
}

void Engine::Architecture::CObject_LoadString::ChangeLoadString(const shared_ptr<CTimer> _timer)
{
	m_TimeAcc += _timer->DeltaTime() * 1000;
	if (m_TimeAcc >= 0.1f)
	{
		m_TimeAcc = 0;
		m_iRunningCnt++;
	}
	if (m_iRunningCnt > 3)
	{
		m_iRunningCnt = 0;
	}
	wcscpy_s(m_LoadText, L"Now Loading");
	for (int i = 0; i < m_iRunningCnt; i++)
	{
		wcscat_s(m_LoadText, L".");
	}
	for (int i = 0; i < 3-m_iRunningCnt; i++)
	{
		wcscat_s(m_LoadText, L" ");
	}
	
	wcscat_s(m_LoadText, to_wstring(int(m_fPercentage)).c_str());
	wcscat_s(m_LoadText, L" %");
}

void Engine::Architecture::CObject_LoadString::ChangeLoadString()
{
	wcscpy_s(m_LoadText, L"Load Complete. Press Enter Key.");
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CObject_LoadString::Create(const shared_ptr<DxDevice> _device)
{
	shared_ptr<CObject> inst = shared_ptr<CObject>(new CObject_LoadString(_device));
	return inst;
}
