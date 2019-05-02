#pragma once
#include "Coordinate.hpp"

class GameController {
protected:
	Coordinate Current;
public:
	GameController() : Current() {}
	virtual void UpdateCurrentPos() = 0;
	virtual int Clicked() = 0;
	Coordinate GetCurrentPos() const noexcept { return this->Current; }
};
