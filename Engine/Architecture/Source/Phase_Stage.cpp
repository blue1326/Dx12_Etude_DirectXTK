#include "stdafx.h"
#include "Phase_Stage.h"

Engine::Architecture::CPhase_Stage::CPhase_Stage(const shared_ptr<DxDevice> _device)
	:CPhase::CPhase(_device)
{

}

Engine::Architecture::CPhase_Stage::~CPhase_Stage()
{

}

HRESULT Engine::Architecture::CPhase_Stage::Prepare_Phase()
{
	return S_OK;
}

void Engine::Architecture::CPhase_Stage::Update_Phase(const shared_ptr<CTimer> _timer)
{
	CPhase::Update_Phase(_timer);
}

void Engine::Architecture::CPhase_Stage::LateUpdate_Phase(const shared_ptr<CTimer> _timer)
{
	
}

void Engine::Architecture::CPhase_Stage::Render_Phase(ID3D12GraphicsCommandList* cmdlist)
{

}

std::shared_ptr<Engine::Architecture::CPhase> Engine::Architecture::CPhase_Stage::Create(const shared_ptr<DxDevice> _device)
{
	return shared_ptr<CPhase>(new CPhase_Stage(_device));
}
