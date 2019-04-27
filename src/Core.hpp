#pragma once
#ifdef WIN32
#include <Windows.h>
#endif

namespace Core {
	extern int DisplayWidth;
	extern int DisplayHeight;
#ifdef WIN32
	extern HINSTANCE InsanceHandle;
#endif
}
