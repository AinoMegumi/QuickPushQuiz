#include <Windows.h>
#include <stdexcept>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	try {
		const HRESULT hr = CoInitialize(nullptr);
		
	}
	catch (const std::exception & er) {

	}
	CoUninitialize();
}
