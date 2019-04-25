#pragma once
class GameEnd {
private:
	int RetVal;
public:
	GameEnd(const int ReturnValue = 0) : RetVal(ReturnValue) {}
	int End() const noexcept { return this->RetVal; }
};
