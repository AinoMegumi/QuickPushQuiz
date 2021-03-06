﻿#pragma once
#ifdef _WINDOWS
#include <Windows.h>
#undef MessageBox
#endif

namespace Core {
	extern int DisplayWidth;
	extern int DisplayHeight;
	void LoadGameConfig();
#ifdef _WINDOWS
	extern HINSTANCE InsanceHandle;
	extern bool LeftHandMouse;
	int MessageBox(LPCSTR lpMessage, LPCSTR Caption, const DWORD dwStyle);
#endif
}
