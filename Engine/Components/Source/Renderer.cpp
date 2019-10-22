#include "stdafx.h"
#include "Renderer.h"

Engine::Components::CRenderer::CRenderer(const shared_ptr<DxDevice> _device)
	:CComponent_Device::CComponent_Device(_device)
{
	m_ThreadPool = CThreadHolder::GetInstance();
}

Engine::Components::CRenderer::~CRenderer()
{
	Clear_RenderList();
}

HRESULT Engine::Components::CRenderer::Init_Component()
{
	return S_OK;
}

HRESULT Engine::Components::CRenderer::Prepare_Component()
{
	return S_OK;
}

void Engine::Components::CRenderer::Update_Component(const shared_ptr<CTimer> _timer)
{

}

void Engine::Components::CRenderer::LateUpdate_Component(const shared_ptr<CTimer> _timer)
{

}

void Engine::Components::CRenderer::Render(ID3D12GraphicsCommandList* cmdlist)
{
	RenderNoneAlpha(cmdlist);
	RenderUI(cmdlist);
	Clear_RenderList();
}

HRESULT Engine::Components::CRenderer::Add_RenderList(RENDER eType, shared_ptr<CObject> object)
{
	if (nullptr == object)
		return E_FAIL;
	m_RenderList[eType].push_back(object);
	return S_OK;
}

void Engine::Components::CRenderer::RenderNoneAlpha(ID3D12GraphicsCommandList* cmdlist)
{
	for (const auto &j : m_RenderList[RENDER_NONEALPHA])
	{
		j->Render_Object(cmdlist);
		/*	m_ThreadPool->SetTask(CThreadHolder::TASK_MAIN, std::bind(&CObject::Render_Object, j.get(), cmdlist));
		}
		m_ThreadPool->Awake_all();
		while (true)
		{
			if (m_ThreadPool->GetTaskCnt(CThreadHolder::TASK_MAIN) == 0 && m_ThreadPool->GetRunningThreadCnt(CThreadHolder::TASK_MAIN) == 0)
			{
				break;
			}*/
		}
}

void Engine::Components::CRenderer::RenderUI(ID3D12GraphicsCommandList* cmdlist)
{
	for (const auto &j : m_RenderList[RENDER_UI])
	{
		j->Render_Object(cmdlist);
		/*	m_ThreadPool->SetTask(CThreadHolder::TASK_MAIN, std::bind(&CObject::Render_Object, j.get(), cmdlist));
		}
		m_ThreadPool->Awake_all();
		while (true)
		{
			if (m_ThreadPool->GetTaskCnt(CThreadHolder::TASK_MAIN) == 0 && m_ThreadPool->GetRunningThreadCnt(CThreadHolder::TASK_MAIN) == 0)
			{
				break;
			}*/
	}
}

void Engine::Components::CRenderer::Clear_RenderList()
{
	for (unsigned long i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].clear();
	}
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CRenderer::Clone()
{
	return this->shared_from_this();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CRenderer::Create(const shared_ptr<DxDevice> _device)
{
	return shared_ptr<CComponent>(new CRenderer(_device));
}
