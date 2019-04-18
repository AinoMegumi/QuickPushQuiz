#include <Windows.h>
#include <stdexcept>
#pragma warning(disable: 6031)

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int CmdShow) {
	MSG msg{};
	try {
		const HRESULT hr = CoInitialize(nullptr);
		
	}
	catch (const std::exception & er) {

	}
	CoUninitialize();
	return static_cast<int>(msg.wParam);
}
