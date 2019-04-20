#pragma once
#include <Windows.h>
#include <functional>
typedef void (*ReleaseFunc)(HANDLE);

template<ReleaseFunc release = [](HANDLE handle) { CloseHandle(handle); } >
class HandleManager {
private:
	HANDLE handle;
public:
	HandleManager() = default;
	HandleManager(const HANDLE& HandleData) : handle(HandleData) {}
	~HandleManager() { release(this->handle); }
	HandleManager(const HandleManager&) = delete;
	HandleManager(HandleManager&&) = default;
	HandleManager& operator = (const HandleManager&) = delete;
	HandleManager& operator = (HandleManager&&) = default;
	bool operator == (const HANDLE& comparehandle) const noexcept { return this->handle == comparehandle; }
	bool operator != (const HANDLE& comparehandle) const noexcept { return this->handle != comparehandle; }
	bool operator == (const HandleManager& comparehandle) const noexcept { return this->handle == comparehandle.handle; }
	bool operator != (const HandleManager& comparehandle) const noexcept { return this->handle != comparehandle.handle; }
	const HANDLE& Get() const noexcept { return this->handle; }
	HANDLE& Get() { return this->handle; }
};

template<ReleaseFunc release = [](HANDLE handle) { CloseHandle(handle); } >
bool operator == (const HANDLE& a, const HandleManager<release>& b) { return a == b.Get(); }
template<ReleaseFunc release = [](HANDLE handle) { CloseHandle(handle); } >
bool operator != (const HANDLE & a, const HandleManager<release> & b) { return a != b.Get(); }
