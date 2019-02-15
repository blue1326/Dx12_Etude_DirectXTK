#include "stdafx.h"
#include "Object_LoadStatString.h"
#include "ComponentHolder.h"
#include "Font.h"
using namespace DirectX;
Engine::Architecture::CObject_LoadStatString::CObject_LoadStatString(const shared_ptr<DxDevice> _device)
	:CUIObject(_device)
	,m_LastText(L"")
{

}

Engine::Architecture::CObject_LoadStatString::~CObject_LoadStatString()
{

}

HRESULT Engine::Architecture::CObject_LoadStatString::Init_Object()
{
	m_Components[L"Font"] = CComponentHolder::GetInstance()->Clone_Component(L"BasicFont");
	//m_Components[L"Renderer"];
	/*if (FAILED(m_Components[L"Font"]->Prepare_Component()))
		return E_FAIL;*/

	if (FAILED(Prepare_Object()))
		return E_FAIL;

	return S_OK;
}

void Engine::Architecture::CObject_LoadStatString::Update_Object(const shared_ptr<CTimer> _timer)
{
	
	if (m_Texts.size() > 4)
	{
		m_Texts.pop_front();
	}

	m_LoadStatText = L"";
	for (const auto &j : m_Texts)
	{
		
		m_LoadStatText += *j.get();
		m_LoadStatText += L"  Loaded \n";
	}

	
	CUIObject::Update_Object(_timer);
}

void Engine::Architecture::CObject_LoadStatString::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{
	
}

void Engine::Architecture::CObject_LoadStatString::Render_Object(ID3D12GraphicsCommandList* cmdlist)
{
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Render_LoadStatText");
	CFont* font = static_cast<CFont*>(m_Components[L"Font"].get());
	ID3D12DescriptorHeap* heaps[] = { font->GetHeap()->Heap() };
	cmdlist->SetDescriptorHeaps(_countof(heaps), heaps);
	font->GetBatch()->Begin(cmdlist);
	font->GetFont()->DrawString(font->GetBatch(), m_LoadStatText.c_str(), XMFLOAT2(0, 0), DirectX::Colors::LightPink, DirectX::XMConvertToRadians(0));
	font->GetBatch()->End();
	PIXEndEvent(cmdlist);
}

void Engine::Architecture::CObject_LoadStatString::PushText(const wchar_t* _text)
{
	
	shared_ptr<wstring> tmptext = make_shared<wstring>(_text);
	
	m_Texts.push_back(tmptext);
	wcscpy_s(m_LastText, _text);
}

const wchar_t* Engine::Architecture::CObject_LoadStatString::GetLastText()
{
	return m_LastText;
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CObject_LoadStatString::Create(const shared_ptr<DxDevice> _device)
{
	shared_ptr<CObject> inst = shared_ptr<CObject>(new CObject_LoadStatString(_device));
	return inst;
}
