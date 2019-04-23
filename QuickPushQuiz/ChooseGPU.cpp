#include "ChooseGPU.hpp"
#include <wrl/client.h>
#include <d3d11.h>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

std::vector<std::pair<unsigned int, std::wstring>> GetSupportedGPU() {
	std::vector<std::pair<unsigned int, std::wstring>> List{};
	ComPtr<IDXGIFactory> DxgiFactory{};
	if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(&DxgiFactory))))
		throw std::runtime_error("Failed to create factory.");
	ComPtr<IDXGIAdapter> Adapter{};
	ComPtr<ID3D11Device> Device{};
	ComPtr<ID3D11DeviceContext> DevContext{};
	UINT CreationFlags =
#ifdef _DEBUG
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#else
		D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#endif
	const D3D_FEATURE_LEVEL Levels[] = { D3D_FEATURE_LEVEL_11_0 };
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != DxgiFactory->EnumAdapters(i, &Adapter); i++) {
		if (FAILED(
			D3D11CreateDevice(
				Adapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				NULL,
				CreationFlags,
				Levels,
				ARRAYSIZE(Levels),
				D3D11_SDK_VERSION,
				&Device,
				nullptr,
				&DevContext
			)
		)) continue;
		DXGI_ADAPTER_DESC AdapterDesc{};
		Adapter->GetDesc(&AdapterDesc);
		List.emplace_back(i, AdapterDesc.Description);
	}
	return List;
}
