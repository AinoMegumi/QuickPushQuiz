#pragma once
#include "DxInit.hpp"
#include "DxGraphic.hpp"
#include "DxLib.h"

class MainProcess {
private:
	GraphicManager Graph;
#ifdef __ANDROID__
	JNIEnv* env;
	const ANativeActivity* NativeActivity;
#endif
public:
	MainProcess();
	~MainProcess();
	MainProcess(const MainProcess&) = delete;
	MainProcess(MainProcess&&) = delete;
	MainProcess& operator = (const MainProcess&) = delete;
	MainProcess& operator = (MainProcess&&) = delete;
	void run();
	void GameMain();
};
