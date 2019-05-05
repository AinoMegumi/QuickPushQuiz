#include "MainProcess.hpp"
#include "Core.hpp"
#include <stdexcept>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	Core::InsanceHandle = hInstance;
	try {
		MainProcess main{};
		main.run();
	}
	catch (const std::exception & er) {
		Core::MessageBox(er.what(), "エラー", MB_ICONERROR | MB_OK);
	}
	CoUninitialize();
	return 0;
}

