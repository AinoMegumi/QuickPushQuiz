#include "DxLib.h"
#include <stdexcept>

#ifdef __ANDROID__
void InitDxLib() {
	SetOutApplicationLogValidFlag(FALSE);
	SetBackgroundColor(255, 255, 255);
	SetAlwaysRunFlag(TRUE);
	if (-1 == DxLib_Init()) throw std::runtime_error("Failed to init DxLib");
	SetTransColor(255, 255, 255);
	SetDrawScreen(DX_SCREEN_BACK);
#else
void InitDxLib(const int WindowWidth, const int WindowHeight) {
	SetMultiThreadFlag(TRUE);
	SetMainWindowText("もぎ取れ！慰謝料");
	SetOutApplicationLogValidFlag(FALSE);
	SetDoubleStartValidFlag(TRUE);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	ChangeWindowMode(TRUE);
	if (-1 == DxLib_Init()) throw std::runtime_error("Failed to init DxLib");
	SetTransColor(255, 255, 255);
	SetDrawScreen(DX_SCREEN_BACK);
#endif
}
