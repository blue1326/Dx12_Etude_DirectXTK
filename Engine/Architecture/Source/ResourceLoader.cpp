#include "stdafx.h"
#include "ResourceLoader.h"
#include "ComponentHolder.h"
Engine::Architecture::CResourceLoader::CResourceLoader()
	:m_iMaxLoadElements(0)
	,m_iLoadedElements(0)
	,m_LoadedText(L"")
	,isLoadFlag(false)
{

}

Engine::Architecture::CResourceLoader::~CResourceLoader()
{
	m_Thread->join();
	m_LoadElements.clear();
}

HRESULT Engine::Architecture::CResourceLoader::LoadStart()
{
	if (m_LoadElements.size() == 0)
	{
		return E_FAIL;
	}
	m_Thread = make_unique<thread>(&CResourceLoader::Load, this);
	return S_OK;
}

void Engine::Architecture::CResourceLoader::SetLoadElements(const LoadElements& _elements)
{
	m_LoadElements = _elements;
	m_iMaxLoadElements = static_cast<int>(m_LoadElements.size());
}

HRESULT Engine::Architecture::CResourceLoader::Load_Resource()
{
	//m_iMaxLoadElements = m_LoadElements.size();
	for (const auto &j : m_LoadElements)
	{
		if (FAILED(j.second->Init_Component()))
			return E_FAIL;
		
		CComponentHolder::GetInstance()->AddOriginComponent(j.first, j.second);
		wcscpy_s(m_LoadedText, j.first);
		m_iLoadedElements++;

		std::this_thread::sleep_for(chrono::duration<int>(1));
	}
	m_LoadElements.clear();
	//for (int i = 0; i < 10; i++)
	//{
	//	//mtx.lock();
	//	iLoadedElements += 10;
	//	std::this_thread::sleep_for(chrono::duration<int>(1));
	//	//mtx.unlock();
	//}
	isLoadFlag = true;
	return S_OK;
}

float Engine::Architecture::CResourceLoader::GetLoadingPercentage()
{
	if (m_iMaxLoadElements == 0)
		return 100;
	float percentage = static_cast<float>(m_iLoadedElements) / static_cast<float>(m_iMaxLoadElements) * 100;
	return percentage;
}

unique_ptr<Engine::Architecture::CResourceLoader> Engine::Architecture::CResourceLoader::Create()
{
	return move(make_unique<Engine::Architecture::CResourceLoader>());
}

void Engine::Architecture::CResourceLoader::Load(void* pArgs)
{
	CResourceLoader* load = static_cast<CResourceLoader*>(pArgs);
	load->Load_Resource();
}
