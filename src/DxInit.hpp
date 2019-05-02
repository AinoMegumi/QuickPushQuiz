#pragma once
#ifdef __ANDROID__
void InitDxLib();
#else
void InitDxLib(const int WindowWidth, const int WindowHeight);
#endif
