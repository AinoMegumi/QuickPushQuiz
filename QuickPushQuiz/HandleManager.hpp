#pragma once
#include <Windows.h>
#include <functional>
typedef void (*ReleaseFunc)(HANDLE);

class HandleManager {
private:
	HANDLE handle;
	ReleaseFunc ReleaseFunction;
public:
	HandleManager(const ReleaseFunc& release = [](HANDLE handle) { CloseHandle(handle); })
		: handle(), ReleaseFunction(release) {}
	HandleManager(const HANDLE& HandleData, const ReleaseFunc& release = [](HANDLE handle) { CloseHandle(handle); }) 
		: handle(HandleData), ReleaseFunction(release) {}
	~HandleManager() { this->ReleaseFunction(this->handle); }
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

bool operator == (const HANDLE& a, const HandleManager& b) { return a == b.Get(); }
bool operator != (const HANDLE & a, const HandleManager & b) { return a != b.Get(); }
