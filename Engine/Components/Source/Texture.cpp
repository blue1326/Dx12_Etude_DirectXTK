#include "stdafx.h"
#include "Texture.h"
#include "Exception.h"
using namespace Engine;
using namespace DirectX;
Engine::Components::CTexture::CTexture(const shared_ptr<DxDevice> _device, const wchar_t* FileLocation)
	:CComponent_Device::CComponent_Device(_device)
	,m_FileLocation(FileLocation)
{

}

Engine::Components::CTexture::~CTexture()
{

}

HRESULT Engine::Components::CTexture::Init_Component()
{
	
	wchar_t FileFormat[20];
	{
		const wchar_t* picker = wcsrchr(m_FileLocation, '.');
		wcsncpy_s(FileFormat, picker + 1, sizeof(picker));
	}
	auto device = m_DxDevice->GetD3DDevice();
	m_Heap = make_shared<DirectX::DescriptorHeap>(device,
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		256);

	ResourceUploadBatch resourceUpload(device);
	resourceUpload.Begin();
	if (_wcsicmp(FileFormat, L"DDS") == 0)
	{
		ThrowIfFailed(
			CreateDDSTextureFromFile(device, resourceUpload, m_FileLocation, m_texture.ReleaseAndGetAddressOf())
		);
	}
	else
	{
		ThrowIfFailed(
			CreateWICTextureFromFile(device, resourceUpload, m_FileLocation, m_texture.ReleaseAndGetAddressOf())
			);
	}
	
	RenderTargetState rts(m_DxDevice->GetBackBufferFormat(), m_DxDevice->GetDepthBufferFormat());

	SpriteBatchPipelineStateDescription pd(rts);
	m_SpriteBatch = make_shared<DirectX::SpriteBatch>(device, resourceUpload, pd);

	auto uploadFin = resourceUpload.End(m_DxDevice->GetCommandQueue());
	m_DxDevice->WaitForGpu();
	uploadFin.wait();

	m_SpriteBatch->SetViewport(m_DxDevice->GetScreenViewport());
	return S_OK;
}

HRESULT Engine::Components::CTexture::Prepare_Component()
{
	return S_OK;
}

void Engine::Components::CTexture::Update_Component(const shared_ptr<CTimer> _timer)
{

}

void Engine::Components::CTexture::LateUpdate_Component(const shared_ptr<CTimer> _timer)
{

}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CTexture::Clone()
{
	return this->shared_from_this();
}

std::shared_ptr<Engine::Components::CComponent> Engine::Components::CTexture::Create(const shared_ptr<DxDevice> _device, const wchar_t* _FileLocation)
{
	auto inst = shared_ptr<CComponent>(new CTexture(_device, _FileLocation));
	return inst;
}
