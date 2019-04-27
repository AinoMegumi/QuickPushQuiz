#include "Core.hpp"
#include <stdexcept>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	Core::InsanceHandle = hInstance;
	try {
		
	}
	catch (const std::exception & er) {

	}
	CoUninitialize();
}

