#pragma once
#ifdef WIN32
#include <Windows.h>
#undef MessageBox
#endif

namespace Core {
	extern int DisplayWidth;
	extern int DisplayHeight;
#ifdef WIN32
	extern HINSTANCE InsanceHandle;
	int MessageBox(LPCSTR lpMessage, LPCSTR Caption, const DWORD dwStyle);
#endif
}
