#include "stdafx.h"
#include "DebugObject.h"
#include "ComponentHolder.h"
#include "Font.h"
using namespace DirectX;
Engine::Architecture::CDebugObject::CDebugObject(const shared_ptr<DxDevice> _device)
	:CObject::CObject(_device)
	,DbgMessage(L"")
{

}

Engine::Architecture::CDebugObject::~CDebugObject()
{

}

HRESULT Engine::Architecture::CDebugObject::Init_Object()
{
	m_Components[L"Font"] = CComponentHolder::GetInstance()->Clone_Component(L"BasicFont");
	if (FAILED(m_Components[L"Font"]->Prepare_Component()))
		return E_FAIL;
	return S_OK;
}

void Engine::Architecture::CDebugObject::Update_Object(const shared_ptr<CTimer> _timer)
{
	
}

void Engine::Architecture::CDebugObject::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{
	
}

void Engine::Architecture::CDebugObject::Render_Object(ID3D12GraphicsCommandList* cmdlist)
{
	
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Render_DBG_FPS");
	CFont* font = static_cast<CFont*>(m_Components[L"Font"].get());
	ID3D12DescriptorHeap* heaps[] = { font->GetHeap()->Heap() };
	cmdlist->SetDescriptorHeaps(_countof(heaps),heaps);
	font->GetBatch()->Begin(cmdlist);
	font->GetFont()->DrawString(font->GetBatch(), DbgMessage, XMFLOAT2(400, 10), DirectX::Colors::LightPink, DirectX::XMConvertToRadians(0));
	font->GetBatch()->End();
	PIXEndEvent(cmdlist);
	//m_Components[L"Font"]->Render(cmdlist);
}

void Engine::Architecture::CDebugObject::SetDbgMessage(const wchar_t* _msg)
{
	wcscpy_s(DbgMessage, _msg);
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CDebugObject::Create(const shared_ptr<DxDevice> _device)
{
	shared_ptr<CObject> inst = shared_ptr<CObject>(new CDebugObject(_device));
	return move(inst);
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CDebugObject::Share()
{
	return nullptr;
}
