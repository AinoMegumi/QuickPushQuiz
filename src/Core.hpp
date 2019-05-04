#pragma once
#ifdef _WINDOWS
#include <Windows.h>
#undef MessageBox
#endif

namespace Core {
	extern int DisplayWidth;
	extern int DisplayHeight;
	void LoadScreenSizeInfo();
#ifdef _WINDOWS
	extern HINSTANCE InsanceHandle;
	int MessageBox(LPCSTR lpMessage, LPCSTR Caption, const DWORD dwStyle);
#endif
}
