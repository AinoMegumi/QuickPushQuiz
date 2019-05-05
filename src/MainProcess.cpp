#include "MainProcess.hpp"
#include "AnswerManager.hpp"
#include "Core.hpp"
#include "DxInit.hpp"

MainProcess::MainProcess() : Graph() {
#ifdef __ANDROID__
	InitDxLib();
	Core::LoadScreenSizeInfo();
	this->NativeActivity = DxLib::GetNativeActivity();
	if (JNI_OK != this->NativeActivity->vm->AttachCurrentThreadAsDaemon(&this->env, nullptr))
		throw std::runtime_error("Failed to associate Java VM with thread of software execution");
#else
	Core::LoadScreenSizeInfo();
	InitDxLib(Core::DisplayWidth, Core::DisplayHeight);
#endif
}

MainProcess::~MainProcess() { 
#ifdef __ANDROID__
	this->NativeActivity->vm->DetachCurrentThread();
#endif
	DxLib_End();
}

void MainProcess::run() {

}

void MainProcess::GameMain() {
	AnswerManager answer{};

}
