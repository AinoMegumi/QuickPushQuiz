#pragma once
#include "Coordinate.hpp"

class GameController {
protected:
	Coordinate::Absolute Current;
public:
	GameController() : Current() {}
	virtual void UpdateCurrentPos() = 0;
	virtual bool Clicked() = 0;
	Coordinate::Absolute GetCurrentPos() const noexcept { return this->Current; }
};
