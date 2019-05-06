#include "Core.hpp"
#ifdef _WINDOWS
#include "CppIniRead.hpp"
#else
#include "DxLib.h"
#endif

namespace Core {
	int DisplayWidth;
	int DisplayHeight;
	void LoadGameConfig() {
#ifdef _WINDOWS
		const IniReadA ini(".\\System\\config.ini");
		DisplayWidth = ini.GetNum<int>("Display", "Width", 800);
		DisplayHeight = ini.GetNum<int>("Display", "Height", 600);
		LeftHandMouse = ini.GetString("Input", "MouseInputHand", "right") == "left";
#else
		int ColorBit = 0;
		DxLib::GetScreenState(&DisplayWidth, &DisplayHeight, &ColorBit);
#endif
	}
#ifdef _WINDOWS
	HINSTANCE InsanceHandle;
	bool LeftHandMouse;
	int MessageBox(LPCSTR lpMessage, LPCSTR Caption, const DWORD dwStyle) {
		MSGBOXPARAMSA mbp{};
		mbp.cbSize = sizeof(mbp);
		mbp.hInstance = InsanceHandle;
		mbp.lpszCaption = Caption;
		mbp.lpszText = lpMessage;
		mbp.dwStyle = dwStyle;
		return MessageBoxIndirectA(&mbp);
	}
#endif
}
