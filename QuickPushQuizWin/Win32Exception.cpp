#include "Win32Exception.hpp"

std::string GetErrorMessage(const DWORD ErrorCode) {
	char* lpMessageBuffer = nullptr;
	const DWORD length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrorCode, LANG_USER_DEFAULT, (LPSTR)& lpMessageBuffer, 0, NULL);
	if (length == 0) throw std::runtime_error("Failed to get error code.\nCode : " + std::to_string(GetLastError()));
	DWORD i = length - 3;
	for (; '\r' != lpMessageBuffer[i] && '\n' != lpMessageBuffer[i] && '\0' != lpMessageBuffer[i]; i++);//改行文字削除
	lpMessageBuffer[i] = '\0';
	const std::string s = "Win32 Exception\nCode : " + std::to_string(ErrorCode) + "\n" + lpMessageBuffer;
	LocalFree(lpMessageBuffer);
	return s;
}

Win32Exception::Win32Exception() : Win32Exception(standard::number<DWORD>(GetLastError())) {}

Win32Exception::Win32Exception(const standard::number<DWORD>& ErrorCode)
	: std::exception(GetErrorMessage(ErrorCode.Get()).c_str()) {}

Win32Exception::Win32Exception(const standard::number<HRESULT>& ErrorCode)
	: std::exception(GetErrorMessage(ErrorCode.Get()).c_str()) {}
