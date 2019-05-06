#pragma once
#include "Coordinate::Absolute.hpp"

class GameController {
protected:
	Coordinate::Absolute Current;
public:
	GameController() : Current() {}
	virtual void UpdateCurrentPos() = 0;
	Coordinate::Absolute GetCurrentPos() const noexcept { return this->Current; }
};
