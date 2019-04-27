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
#endif

}
