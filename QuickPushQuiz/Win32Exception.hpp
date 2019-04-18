#pragma once
#include "Number.hpp"
#include <Windows.h>
#include <stdexcept>

class Win32Exception : public std::exception {
public:
	Win32Exception();
	Win32Exception(const standard::number<DWORD> ErrorCode);
	Win32Exception(const HRESULT ErrorCode);
};
