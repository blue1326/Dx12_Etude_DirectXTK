#include "stdafx.h"
#include "Object_Logo.h"
#include "ComponentHolder.h"
#include "Sprite.h"
#include "Renderer.h"
using namespace DirectX;
Engine::Architecture::CObject_Logo::CObject_Logo(const shared_ptr<DxDevice> _device)
	:CUIObject(_device)
{

}

Engine::Architecture::CObject_Logo::~CObject_Logo()
{

}

HRESULT Engine::Architecture::CObject_Logo::Init_Object()
{
	auto holder = CComponentHolder::GetInstance();
	m_Components[L"Sprite"] = holder->Clone_Component(L"Sprite_Logo");
	
	m_Components[L"Renderer"] = holder->Clone_Component(L"Renderer");
	

	if (FAILED(CheckComponentNullptr()))
		return E_FAIL;

	if (FAILED(Prepare_Object()))
		return E_FAIL;

	return S_OK;
}

void Engine::Architecture::CObject_Logo::Update_Object(const shared_ptr<CTimer> _timer)
{
	static_cast<CRenderer*>(m_Components[L"Renderer"].get())->Add_RenderList(CRenderer::RENDER_UI, shared_from_this());
	CUIObject::Update_Object(_timer);
}

void Engine::Architecture::CObject_Logo::LateUpdate_Object(const shared_ptr<CTimer> _timer)
{

}

void Engine::Architecture::CObject_Logo::Render_Object(ID3D12GraphicsCommandList* cmdlist)
{
	PIXBeginEvent(cmdlist, PIX_COLOR_DEFAULT, L"Render_LoadLogoSprite");
	CSprite* sprite = static_cast<CSprite*>(m_Components[L"Sprite"].get());
	ID3D12DescriptorHeap* heaps[] = { sprite->GetHeap()->Heap() };
	cmdlist->SetDescriptorHeaps(_countof(heaps), heaps);
	sprite->GetBatch()->Begin(cmdlist);
	
	
	sprite->GetBatch()->Draw(sprite->GetHeap()->GetFirstGpuHandle(),XMUINT2(800,600),XMFLOAT2(0,0));
	//XMUINT2 tmp = GetTextureSize(sprite->GetResource());
	sprite->GetBatch()->End();
	PIXEndEvent(cmdlist);
}

std::shared_ptr<Engine::CObject> Engine::Architecture::CObject_Logo::Create(const shared_ptr<DxDevice> _device)
{
	shared_ptr<CObject> inst = shared_ptr<CObject>(new CObject_Logo(_device));
	
	return inst;
}
