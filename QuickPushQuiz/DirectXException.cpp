#include "DirectXException.hpp"
#include <DxErr.h>
#include <string>
#pragma comment(lib, "dxerr.lib")

DirectXException::DirectXException(const HRESULT hr)
	: std::exception(("DirectX Error\nCode : " + std::to_string(hr) + "\n" + DXGetErrorStringA(hr)).c_str()) {}
