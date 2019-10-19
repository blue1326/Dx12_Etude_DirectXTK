#include "stdafx.h"
#include "Phase_Load.h"
//#include <thread>
//#include <chrono>
//#include <mutex>
#include "Renderer.h"
//mutex mtx;
#include "Object_LoadStatString.h"
#include "Object_LoadString.h"
#include "Object_Logo.h"

Engine::Architecture::CPhase_Load::CPhase_Load(const shared_ptr<DxDevice> _device)
	:CPhase::CPhase(_device)
{

}

Engine::Architecture::CPhase_Load::~CPhase_Load()
{
}

HRESULT Engine::Architecture::CPhase_Load::Prepare_Phase()
{

	shared_ptr<CObject> obj;
	ReserveLayer(2);
	obj.reset();
	obj = CObject_Logo::Create(m_DxDevice);
	AddObject(0,L"LogoSprite", obj);

	

	obj.reset();
	obj = CObject_LoadString::Create(m_DxDevice);
	AddObject(1,L"LoadText", obj);

	obj.reset();
	obj = CObject_LoadStatString::Create(m_DxDevice);
	AddObject(1,L"LoadStatText", obj);
	


	InitObjects();

	m_Loader = CResourceLoader::Create();

	CResourceLoader::LoadElements tmpElements;
	tmpElements[L"1"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"2"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"3"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"4"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"5"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"6"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"7"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"8"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"9"] = CRenderer::Create(m_DxDevice);
	tmpElements[L"10"] = CRenderer::Create(m_DxDevice);

	m_Loader->SetLoadElements(tmpElements);
	m_Loader->LoadStart();
	
	return S_OK;
}

void Engine::Architecture::CPhase_Load::Update_Phase(const shared_ptr<CTimer> _timer)
{

	auto statText = static_cast<CObject_LoadStatString*>((*(vecLayer[1].get()))[L"LoadStatText"].get());
	const wchar_t* tmptext = m_Loader->GetLoadText();
	if(wcscmp(tmptext, statText->GetLastText()) !=0 )
	{
		statText->PushText(tmptext);
	}
	
	auto loadtext = static_cast<CObject_LoadString*>((*(vecLayer[1].get()))[L"LoadText"].get());
	loadtext->SetLoadingPercentage(m_Loader->GetLoadingPercentage());
	if (m_Loader->GetLoadFlag())
	{
		loadtext->SetFlag(true);
	}

if (loadtext->GetPhaseFlag())
{
	m_NextPhase->Prepare_Phase();
	isLive = false;
	m_NextPhase->isLive = true;
}
	CPhase::Update_Phase(_timer);
}

void Engine::Architecture::CPhase_Load::LateUpdate_Phase(const shared_ptr<CTimer> _timer)
{
	
}

void Engine::Architecture::CPhase_Load::Render_Phase(ID3D12GraphicsCommandList* cmdlist)
{
	//m_Objects[L"LoadStatText"]->Render_Object(cmdlist);
}

std::shared_ptr<Engine::Architecture::CPhase> Engine::Architecture::CPhase_Load::Create(const shared_ptr<DxDevice> _device)
{
	return shared_ptr<CPhase>(new CPhase_Load(_device));
}
