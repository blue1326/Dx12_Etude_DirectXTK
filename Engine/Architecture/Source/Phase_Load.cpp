#include "stdafx.h"
#include "Phase_Load.h"
//#include <thread>
//#include <chrono>
//#include <mutex>
#include "Renderer.h"
//mutex mtx;
#include "Object_LoadStatString.h"
#include "Object_LoadString.h"
Engine::Architecture::CPhase_Load::CPhase_Load(const shared_ptr<DxDevice> _device)
	:CPhase::CPhase(_device)
{

}

Engine::Architecture::CPhase_Load::~CPhase_Load()
{
		
}

HRESULT Engine::Architecture::CPhase_Load::Prepare_Phase()
{

	shared_ptr<CObject> obj = CObject_LoadStatString::Create(m_DxDevice);
	AddObject(L"LoadStatText", obj);
	obj.reset();
	obj = CObject_LoadString::Create(m_DxDevice);
	AddObject(L"LoadText", obj);
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

	auto statText = static_cast<CObject_LoadStatString*>(m_Objects[L"LoadStatText"].get());
	const wchar_t* tmptext = m_Loader->GetLoadText();
	if(wcscmp(tmptext, statText->GetLastText()) !=0 )
	{
		statText->PushText(tmptext);
	}
	

	float tmp = m_Loader->GetLoadingPercentage();
	bool tmp2 = m_Loader->GetLoadFlag();
	if (tmp2 == true)
	{
		int i = 0;
	}
	CPhase::Update_Phase(_timer);
}

void Engine::Architecture::CPhase_Load::LateUpdate_Phase(const shared_ptr<CTimer> _timer)
{
	
}

void Engine::Architecture::CPhase_Load::Render_Phase(ID3D12GraphicsCommandList* cmdlist)
{
	m_Objects[L"LoadStatText"]->Render_Object(cmdlist);
}

std::shared_ptr<Engine::Architecture::CPhase> Engine::Architecture::CPhase_Load::Create(const shared_ptr<DxDevice> _device)
{
	return shared_ptr<CPhase>(new CPhase_Load(_device));
}
