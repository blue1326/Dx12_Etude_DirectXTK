#include "stdafx.h"
#include "DebugObject.h"
#include "ComponentHolder.h"
#include "Font.h"
#include "CThreadHolder.h"
using namespace ThreadPool;
using namespace DirectX;
Engine::Architecture::CDebugObject::CDebugObject(const shared_ptr<DxDevice> _device)
	:CObject::CObject(_device)
	,FPSDbgMessage(L"")
	,MouseDbgMessage(L"")
	,ThreadDbgMessage(L"")
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
	std::wstring dbgText =
		L" RunningThreadCnt: " + to_wstring(CThreadHolder::GetInstance()->GetRunningThreadCnt(CThreadHolder::TASK_MAIN)) +
		L"  ReservedTaskCnt: " + to_wstring(CThreadHolder::GetInstance()->GetTaskCnt(CThreadHolder::TASK_MAIN));
	wcscpy_s(ThreadDbgMessage, dbgText.c_str());
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

	font->GetFont()->DrawString(font->GetBatch(), FPSDbgMessage, XMFLOAT2(400, 10), DirectX::Colors::Red, DirectX::XMConvertToRadians(0));
	font->GetFont()->DrawString(font->GetBatch(), MouseDbgMessage, XMFLOAT2(400, 20), DirectX::Colors::Red, DirectX::XMConvertToRadians(0));
	font->GetFont()->DrawString(font->GetBatch(), ThreadDbgMessage, XMFLOAT2(400, 30), DirectX::Colors::Red, DirectX::XMConvertToRadians(0));

	font->GetBatch()->End();
	PIXEndEvent(cmdlist);
	//m_Components[L"Font"]->Render(cmdlist);
}

void Engine::Architecture::CDebugObject::SetFPSDbgMessage(const wchar_t* _msg)
{
	wcscpy_s(FPSDbgMessage, _msg);
}

void Engine::Architecture::CDebugObject::SetMouseDbgMessage(const wchar_t* _msg)
{
	wcscpy_s(MouseDbgMessage, _msg);
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
