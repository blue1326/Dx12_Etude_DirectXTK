#include "stdafx.h"
#include "Font.h"
using namespace DirectX;

Engine::Components::CFont::CFont(shared_ptr<DxDevice> _device, const wchar_t* FileLocation)
	:CComponent_Device::CComponent_Device(_device)
	, m_FileLocation(FileLocation)
{

}

Engine::Components::CFont::~CFont()
{

}

HRESULT Engine::Components::CFont::Init_Component()
{
	auto device = m_DxDevice->GetD3DDevice();

	//m_State = make_shared<DirectX::CommonStates>(device);
	m_Heap = make_shared<DirectX::DescriptorHeap>(device,
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		256);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();

	RenderTargetState rts(m_DxDevice->GetBackBufferFormat(), m_DxDevice->GetDepthBufferFormat());
	
	
	SpriteBatchPipelineStateDescription pd(rts);
	m_SpriteBatch = make_shared<DirectX::SpriteBatch>(device, resourceUpload, pd);
	

	m_font = make_shared<SpriteFont>(device,
		resourceUpload,
		m_FileLocation,
		m_Heap->GetFirstCpuHandle(),
		m_Heap->GetFirstGpuHandle());

	auto uploadFin = resourceUpload.End(m_DxDevice->GetCommandQueue());
	m_DxDevice->WaitForGpu();
	uploadFin.wait();
	m_SpriteBatch->SetViewport(m_DxDevice->GetScreenViewport());
	return S_OK;
}

HRESULT Engine::Components::CFont::Prepare_Component()
{
	return S_OK;
}

void Engine::Components::CFont::Update_Component(const shared_ptr<CTimer> _timer)
{

}

void Engine::Components::CFont::LateUpdate_Component(const shared_ptr<CTimer> _timer)
{

}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CFont::Clone()
{
	return this->shared_from_this();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CFont::Create(const shared_ptr<DxDevice> _device, const wchar_t* _FileLocation)
{
	auto inst = shared_ptr<CComponent>(new CFont(_device,_FileLocation));
	return inst;
}
