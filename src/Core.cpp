#include "Core.hpp"
#ifdef WIN32
#include "CppIniRead.hpp"
#else
#include "DxLib.h"
#endif

namespace Core {
	int DisplayWidth;
	int DisplayHeight;
	void LoadScreenSizeInfo() {
#ifdef WIN32
		const IniReadA ini(".\\System\\config.ini");
		DisplayWidth = ini.GetNum<int>("Display", "Width", 800);
		DisplayHeight = ini.GetNum<int>("Display", "Height", 600);
#else
		int ColorBit = 0;
		GetScreenState(&DisplayWidth, &DisplayHeight, &ColorBit);
#endif
	}
#ifdef WIN32
	HINSTANCE InsanceHandle;
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
