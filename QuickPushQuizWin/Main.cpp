#include "Core.hpp"
#include "DxInit.hpp"
#include <stdexcept>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	Core::InsanceHandle = hInstance;
	try {
		InitDxLib(Core::DisplayWidth, Core::DisplayHeight);
	}
	catch (const std::exception & er) {
		Core::MessageBox(er.what(), "エラー", MB_ICONERROR | MB_OK);
	}
	CoUninitialize();
}

