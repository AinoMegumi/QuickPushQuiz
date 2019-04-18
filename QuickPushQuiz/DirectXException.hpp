#pragma once
#include <Windows.h>
#include <stdexcept>

class DirectXException : public std::exception {
public:
	DirectXException() : std::exception() {}
	DirectXException(const HRESULT hr);
};
